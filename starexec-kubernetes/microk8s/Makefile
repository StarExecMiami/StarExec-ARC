# ==============================================================================
# Makefile for StarExec on MicroK8s (Helm-based deployment)
# ==============================================================================

# Shell to use
SHELL := /usr/bin/env bash

# Kubernetes Configuration
KUBECTL := microk8s kubectl
HELM := microk8s helm3

NAMESPACE := default
APP_NAME := starexec
CHART_PATH := ../../starexec-helm
VALUES_FILE := $(CHART_PATH)/values-microk8s.yaml

# Pod selector for Helm-deployed resources
POD_SELECTOR := app.kubernetes.io/name=$(APP_NAME)

# Secrets and Keys Configuration
SSH_KEY_NAME := starexec-ssh-key
SSH_KEY_FILE := $(CURDIR)/$(SSH_KEY_NAME)
TLS_SECRET_NAME := starexec-tls-secret
TLS_CERT_KEY_FILE := $(CURDIR)/starexec-tls.key
TLS_CERT_CRT_FILE := $(CURDIR)/starexec-tls.crt
TLS_HOSTS := localhost # Add other hosts if needed, space-separated

# State Backup Configuration
BACKUP_DIR := $(CURDIR)/state-backup
STATE_PATHS := /var/lib/mysql /home/starexec # Paths inside the container to backup

# Colors for Output
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
NC := \033[0m # No Color

# Helper command to get the first running pod name
GET_POD_CMD = $(KUBECTL) get pods --selector=$(POD_SELECTOR) -n $(NAMESPACE) -o jsonpath='{.items[?(@.status.phase=="Running")].metadata.name}' | cut -d' ' -f1

# Determine SSH Username dynamically
DETECTED_SSH_USER ?= $(shell echo $$STAREXEC_SSH_USER)
ifeq ($(DETECTED_SSH_USER),)
  DETECTED_SSH_USER := $(USER)
  USER_SOURCE := current user '($(USER))'
else
  USER_SOURCE := environment variable STAREXEC_SSH_USER
endif

# Default values for other config map entries (can be overridden by env vars if needed)
HOST_MACHINE ?= localhost
SSH_PORT ?= 22
# Default socket path might vary, adjust if necessary or make dynamic too
SSH_SOCKET_PATH ?= "/run/podman/podman.sock"

# ==============================================================================
# Phony Targets Declaration
# ==============================================================================
.PHONY: help apply connect clean info list-pods list-services list-deployments \
		list-nodes cert-refresh mkcert-setup mkcert-clean check-health \
		backup-state restore-state start stop describe-pod check-volumes \
		ssh-setup

# Default target: Show help
default: help

# ==============================================================================
# Core Application Lifecycle Targets
# ==============================================================================

apply: ssh-setup mkcert-setup ## Deploy or update the application stack using Helm
	@echo -e "${YELLOW}Ensuring MicroK8s addons are enabled...${NC}"
	@microk8s status | grep -q 'ingress: enabled' || microk8s enable ingress
	@microk8s status | grep -q 'dns: enabled' || microk8s enable dns
	@microk8s status | grep -q 'storage: enabled' || microk8s enable storage
	@echo -e "${YELLOW}Updating SSH key secrets...${NC}"
# 	-$(KUBECTL) delete secret $(SSH_KEY_NAME) -n $(NAMESPACE) --ignore-not-found=true
# 	$(KUBECTL) create secret generic $(SSH_KEY_NAME) --from-file=starexec_podman_key=$(SSH_KEY_FILE) -n $(NAMESPACE)
	@echo -e "${YELLOW}Deploying StarExec using Helm...${NC}"
	@echo -e "  Using SSH_USERNAME: ${GREEN}$(DETECTED_SSH_USER)${NC} (Source: $(USER_SOURCE))"
	@echo -e "  Using HOST_MACHINE: ${GREEN}$(HOST_MACHINE)${NC}"
	@echo -e "  Using SSH_PORT: ${GREEN}$(SSH_PORT)${NC}"
	@echo -e "  Using SSH_SOCKET_PATH: ${GREEN}$(SSH_SOCKET_PATH)${NC}"
	$(HELM) upgrade --install $(APP_NAME) $(CHART_PATH) \
		-f $(VALUES_FILE) \
		--set starexecConfig.ssh.username="$(DETECTED_SSH_USER)" \
		--set starexecConfig.ssh.hostMachine="$(HOST_MACHINE)" \
		--set starexecConfig.ssh.port="$(SSH_PORT)" \
		--set starexecConfig.ssh.socketPath="$(SSH_SOCKET_PATH)" \
		-n $(NAMESPACE)
	$(KUBECTL) label node $$($(KUBECTL) get nodes | awk 'NR>1 {print $$1}') nodegroup=computenodes --overwrite
	@echo -e "${GREEN}Application deployment initiated using Helm.${NC}"
	@echo -e "${GREEN}=== Access Instructions ===${NC}"
	@echo -e "Wait for pods to be ready ('make list-pods'). Then:"
	@echo -e "${YELLOW}Option 1: Using ClusterIP (within cluster):${NC}"
	@cluster_ip=$$( $(KUBECTL) get svc $(APP_NAME) -n $(NAMESPACE) -o jsonpath='{.spec.clusterIP}' ); \
	 echo -e "  Access via https://$${cluster_ip}"
	@echo -e "${YELLOW}Option 2: Using Port Forward (from localhost):${NC}"
	@echo -e "  Run: $(KUBECTL) port-forward svc/$(APP_NAME) -n $(NAMESPACE) 8443:443"
	@echo -e "  Then visit: https://localhost:8443"

clean: mkcert-clean ## Remove all deployed application resources using Helm
	@echo -e "${YELLOW}Removing StarExec application using Helm...${NC}"
	$(HELM) uninstall $(APP_NAME) -n $(NAMESPACE) || true
	@echo -e "${YELLOW}Deleting SSH key secrets...${NC}"
	-$(KUBECTL) delete secret $(SSH_KEY_NAME) -n $(NAMESPACE) --ignore-not-found=true
	@echo -e "${YELLOW}Deleting local SSH key files...${NC}"
	-rm -f $(SSH_KEY_FILE) $(SSH_KEY_FILE).pub || true
	@echo "Forcing deletion of any remaining PVCs..."
	@microk8s kubectl delete pvc -l app.kubernetes.io/instance=starexec --ignore-not-found=true --wait
	@echo -e "${GREEN}Cleanup complete.${NC}"

start: ## Deploy the application and restore state if backup exists
	@echo -e "${YELLOW}Starting StarExec application...${NC}"
	@if [ -d "$(BACKUP_DIR)" ]; then \
		echo -e "${YELLOW}State backup found at $(BACKUP_DIR). Will restore after deployment.${NC}"; \
	else \
		echo -e "${YELLOW}No state backup found. Starting with a clean state.${NC}"; \
	fi
	$(MAKE) apply
	@echo -e "${YELLOW}Waiting for StarExec pod to be ready...${NC}"
	@timeout 180s bash -c '\
	  while ! $(KUBECTL) get pods --selector=$(POD_SELECTOR) -n $(NAMESPACE) -o jsonpath="{.items[*].status.phase}" | grep -q "Running"; do \
		echo -n "."; \
		sleep 5; \
	  done; echo " Pod is Running."' || (echo -e "\n${RED}Pod did not become ready in time.${NC}" && exit 1)
	@if [ -d "$(BACKUP_DIR)" ]; then \
		echo -e "${YELLOW}Restoring state from backup...${NC}"; \
		$(MAKE) restore-state; \
	fi
	@echo -e "${GREEN}StarExec start sequence complete.${NC}"
	@echo -e "${YELLOW}Access instructions provided during 'apply'. Run 'make apply' again to see them.${NC}"

stop: ## Backup application state and then remove all resources
	@echo -e "${YELLOW}Stopping StarExec application...${NC}"
	@if ! $(KUBECTL) get pods --selector=$(POD_SELECTOR) -n $(NAMESPACE) -o name | grep -q .; then \
		echo -e "${YELLOW}No StarExec pods found. Nothing to stop.${NC}"; \
		exit 0; \
	fi
	$(MAKE) backup-state
	$(MAKE) clean
	@echo -e "${GREEN}StarExec stopped. State backed up to $(BACKUP_DIR).${NC}"
	@echo -e "${YELLOW}Run 'make start' to redeploy and restore this state.${NC}"

# ==============================================================================
# State Management Targets
# ==============================================================================

backup-state: ## Backup application state from the running pod to local directory
	@echo -e "${YELLOW}Backing up StarExec state...${NC}"
	@mkdir -p $(BACKUP_DIR)
	@pod=$$($(GET_POD_CMD)); \
	if [ -z "$$pod" ]; then \
		echo -e "${RED}No running StarExec pod found. Cannot backup state.${NC}"; \
		exit 1; \
	fi; \
	echo -e "Using pod: $$pod"; \
	for path in $(STATE_PATHS); do \
		target_dir="$(BACKUP_DIR)$${path}"; \
		echo -e "${YELLOW}Backing up $$path to $${target_dir}...${NC}"; \
		mkdir -p "$${target_dir}"; \
		rm -rf "$${target_dir}/*"; \
		$(KUBECTL) exec -n $(NAMESPACE) $$pod -- bash -c "cd $${path} && tar cf - ." | tar xf - -C "$${target_dir}"; \
		if [ $$? -ne 0 ]; then echo -e "${RED}Error during backup of $$path.${NC}"; exit 1; fi; \
	done
	@echo -e "${GREEN}State backup completed successfully to $(BACKUP_DIR)${NC}"
	@echo -e "${YELLOW}Backup size:${NC}"
	@du -sh $(BACKUP_DIR)

restore-state: ## Restore application state from local BACKUP_DIR to the running pod
	@echo -e "${YELLOW}Restoring StarExec state...${NC}"
	@if [ ! -d "$(BACKUP_DIR)" ]; then \
		echo -e "${RED}Backup directory $(BACKUP_DIR) not found. Cannot restore state.${NC}"; \
		exit 1; \
	fi
	@pod=$$($(GET_POD_CMD)); \
	if [ -z "$$pod" ]; then \
		echo -e "${RED}No running StarExec pod found. Cannot restore state.${NC}"; \
		exit 1; \
	fi; \
	echo -e "${YELLOW}Found pod: $$pod. Restoring from $(BACKUP_DIR)...${NC}"; \
	for path in $(STATE_PATHS); do \
		source_item="$(BACKUP_DIR)$${path}"; \
		if [ ! -e "$$source_item" ]; then \
			echo -e "${YELLOW}Backup source '$$source_item' not found. Skipping restore for $$path.${NC}"; \
			continue; \
		fi; \
		echo -e "${YELLOW}Restoring $$path to pod $$pod from $$source_item...${NC}"; \
		cd $(BACKUP_DIR) && tar cf - .$$path | $(KUBECTL) exec -i -n $(NAMESPACE) $$pod -- tar xf - -C / || \
			{ echo -e "${RED}Failed to restore $$path.${NC}"; exit 1; }; \
	done; \
	echo -e "${YELLOW}Restarting services inside the pod after restore...${NC}"; \
	$(KUBECTL) exec -n $(NAMESPACE) $$pod -- bash -c ' \
		echo "Stopping web and Tomcat services gracefully..."; \
		apache2ctl -k graceful || true; \
		/project/apache-tomcat-7/bin/shutdown.sh || true; \
		echo "Stopping MySQL gracefully if running..."; \
		if [ -f /var/run/mysqld/mysqld.pid ]; then \
			if mysqladmin shutdown; then \
				echo "MySQL stopped gracefully"; \
			else \
				echo "Graceful shutdown failed, forcing stop..."; \
				pkill -9 mysqld || true; \
			fi; \
		fi; \
		sleep 5; \
		echo "Ensuring no MySQL processes are running..."; \
		pkill -9 mysqld || true; \
		sleep 2; \
		echo "Freeing up system caches..."; \
		echo 3 > /proc/sys/vm/drop_caches || true; \
		sync; \
		echo "Correcting permissions for /var/lib/mysql..."; \
		chown -R mysql:mysql /var/lib/mysql; \
		echo "Setting up MySQL runtime directory..."; \
		rm -rf /var/run/mysqld; \
		mkdir -p /var/run/mysqld; \
		chown mysql:mysql /var/run/mysqld; \
		chmod 777 /var/run/mysqld; \
		echo "Creating minimal MySQL config for startup..."; \
		echo "[mysqld]" > /tmp/minimal.cnf; \
		echo "innodb_buffer_pool_size=512M" >> /tmp/minimal.cnf; \
		echo "Starting MySQL with minimal config..."; \
		mysqld_safe --defaults-file=/tmp/minimal.cnf --user=mysql --skip-syslog & \
		echo "Waiting for MySQL to start (with timeouts)..."; \
		for i in $$(seq 1 30); do \
			if mysqladmin ping --silent; then \
				echo "MySQL is responding to ping"; \
				break; \
			fi; \
			if [ $$i -eq 30 ]; then \
				echo "ERROR: MySQL failed to start after 30 attempts"; \
				echo "Checking MySQL error log..."; \
				for logfile in /var/log/mysql/error.log /var/lib/mysql/*.err; do \
					if [ -f "$$logfile" ]; then \
						echo "=== Contents of $$logfile ==="; \
						tail -n 50 "$$logfile"; \
					fi; \
				done; \
				exit 1; \
			fi; \
			echo "Waiting for MySQL to start (attempt $$i/30)..."; \
			sleep 2; \
		done; \
		echo "MySQL started successfully."; \
		echo "Restarting Apache and Tomcat..."; \
		apache2ctl -k graceful || true; \
		sleep 2; \
		/project/apache-tomcat-7/bin/startup.sh' || \
	{ echo -e "${RED}Failed to restart services in the pod.${NC}"; exit 1; }; \
	echo -e "${GREEN}State restore and service restart completed successfully.${NC}"

# ==============================================================================
# Certificate Management Targets (using mkcert)
# ==============================================================================

mkcert-setup: ## Install mkcert CA and generate TLS certificate and secret
	@echo -e "${YELLOW}Setting up mkcert and generating TLS certificate...${NC}"
	@if ! command -v mkcert > /dev/null 2>&1; then \
		echo -e "${RED}mkcert is not installed.${NC} Please install it."; \
		echo "  Linux: sudo apt update && sudo apt install -y mkcert libnss3-tools"; \
		echo "  macOS: brew install mkcert"; \
		exit 1; \
	fi
	@echo "Ensuring local CA is installed (may require sudo password)..."
	@mkcert -install
	@echo "Generating TLS certificate for $(TLS_HOSTS)..."
	@mkcert -cert-file $(TLS_CERT_CRT_FILE) -key-file $(TLS_CERT_KEY_FILE) $(TLS_HOSTS)
	@echo "Creating/Updating Kubernetes TLS secret '$(TLS_SECRET_NAME)'..."
	-$(KUBECTL) delete secret tls $(TLS_SECRET_NAME) -n $(NAMESPACE) --ignore-not-found=true
	@$(KUBECTL) create secret tls $(TLS_SECRET_NAME) --cert=$(TLS_CERT_CRT_FILE) --key=$(TLS_CERT_KEY_FILE) -n $(NAMESPACE)
	@echo -e "${GREEN}mkcert setup complete. TLS secret '$(TLS_SECRET_NAME)' created/updated.${NC}"

cert-refresh: ## Regenerate TLS certificate and update the Kubernetes secret
	@echo -e "${YELLOW}Refreshing TLS certificate and secret using mkcert...${NC}"
	@if ! command -v mkcert > /dev/null 2>&1; then \
		echo -e "${RED}mkcert not found. Run 'make mkcert-setup' first.${NC}"; exit 1; \
	fi
	@if [ ! -f "$(HOME)/.local/share/mkcert/rootCA.pem" ]; then \
		echo -e "${RED}mkcert CA not found. Run 'make mkcert-setup' first.${NC}"; exit 1; \
	fi
	@echo "Generating new TLS certificate for $(TLS_HOSTS)..."
	@mkcert -cert-file $(TLS_CERT_CRT_FILE) -key-file $(TLS_CERT_KEY_FILE) $(TLS_HOSTS)
	@echo "Updating Kubernetes TLS secret '$(TLS_SECRET_NAME)'..."
	-$(KUBECTL) delete secret tls $(TLS_SECRET_NAME) -n $(NAMESPACE) --ignore-not-found=true
	@$(KUBECTL) create secret tls $(TLS_SECRET_NAME) --cert=$(TLS_CERT_CRT_FILE) --key=$(TLS_CERT_KEY_FILE) -n $(NAMESPACE)
	@echo -e "${GREEN}TLS certificate and secret '$(TLS_SECRET_NAME)' refreshed successfully.${NC}"
	# Consider keeping cert files: -rm -f $(TLS_CERT_CRT_FILE) $(TLS_CERT_KEY_FILE)

mkcert-clean: ## Remove generated TLS certificate files and Kubernetes secret
	@echo -e "${YELLOW}Removing generated TLS certificate files...${NC}"
	-rm -f $(TLS_CERT_CRT_FILE) $(TLS_CERT_KEY_FILE)
	@echo -e "${YELLOW}Removing Kubernetes TLS secret '$(TLS_SECRET_NAME)'...${NC}"
	-$(KUBECTL) delete secret tls $(TLS_SECRET_NAME) -n $(NAMESPACE) --ignore-not-found=true
	@echo -e "${GREEN}TLS cleanup complete.${NC}"

# ==============================================================================
# SSH Key Management Targets
# ==============================================================================

ssh-setup: ## Generate SSH key pair if it doesn't exist
	@echo -e "${YELLOW}Setting up SSH keys...${NC}"
	@if [ ! -f "$(SSH_KEY_FILE)" ]; then \
		echo "Generating SSH key pair: $(SSH_KEY_FILE)"; \
		ssh-keygen -t rsa -b 4096 -N "" -f $(SSH_KEY_FILE); \
		chmod 600 $(SSH_KEY_FILE); \
		echo -e "${GREEN}SSH key pair generated.${NC}"; \
	else \
		echo "SSH key file $(SSH_KEY_FILE) already exists."; \
	fi
	# The following lines might be specific to development setups
	# Consider if they are necessary for your deployment
	# @echo "Adding localhost to known_hosts..."
	# @ssh-keyscan -H localhost >> ~/.ssh/known_hosts 2>/dev/null || true
	# @if [ "$(USER)" != "jenkins" ]; then \
	# 	echo "Adding public key to authorized_keys for user $(USER)..."; \
	# 	mkdir -p ~/.ssh && chmod 700 ~/.ssh; \
	# 	cat $(SSH_KEY_FILE).pub >> ~/.ssh/authorized_keys; \
	# 	chmod 600 ~/.ssh/authorized_keys; \
	# else \
	# 	echo "Skipping adding public key to authorized_keys for Jenkins user."; \
	# fi
	@echo -e "${GREEN}SSH key setup checked/completed.${NC}"


# ==============================================================================
# Utility & Debugging Targets
# ==============================================================================

connect: ## Open a bash shell into the running application pod
	@pod=$$($(GET_POD_CMD)); \
	if [ -z "$$pod" ]; then \
		echo -e "${RED}No running StarExec pod found.${NC}"; \
		exit 1; \
	fi; \
	echo -e "${YELLOW}Connecting to pod: $$pod...${NC}"; \
	$(KUBECTL) exec -n $(NAMESPACE) -it $$pod -- /bin/bash

check-health: ## Perform basic health checks on the running application
	@echo -e "${YELLOW}Performing health checks...${NC}"
	@pod=$$($(GET_POD_CMD)); \
	if [ -z "$$pod" ]; then \
		echo -e "${RED}No running StarExec pod found. Cannot perform checks.${NC}"; \
		exit 1; \
	fi; \
	echo -e "Using pod: $$pod"; \
	echo -e "\n${YELLOW}--- Checking Pod Status ---${NC}"; \
	$(KUBECTL) get pod $$pod -n $(NAMESPACE) -o wide; \
	echo -e "\n${YELLOW}--- Checking Tomcat Process ---${NC}"; \
	$(KUBECTL) exec -n $(NAMESPACE) $$pod -- ps aux | grep '[t]omcat' || echo -e "${RED}Tomcat process not found!${NC}"; \
	echo -e "\n${YELLOW}--- Checking Apache Status ---${NC}"; \
	$(KUBECTL) exec -n $(NAMESPACE) $$pod -- service apache2 status || echo -e "${RED}Apache service not running or status check failed!${NC}"; \
	echo -e "\n${YELLOW}--- Testing HTTPS Root Redirect ---${NC}"; \
	$(KUBECTL) exec -n $(NAMESPACE) $$pod -- curl -s -k -I https://localhost/ | grep -i 'Location:.*\/starexec' || echo -e "${RED}Redirect from / to /starexec failed or not configured!${NC}"; \
	echo -e "\n${YELLOW}--- Testing /starexec Endpoint ---${NC}"; \
	$(KUBECTL) exec -n $(NAMESPACE) $$pod -- curl -s -k https://localhost/starexec/ | grep -iq "StarExec" && echo -e "${GREEN}StarExec application is responding.${NC}" || echo -e "${RED}StarExec application did NOT respond as expected!${NC}"; \
	echo -e "\n${YELLOW}--- Checking Recent Tomcat Logs (catalina.out) ---${NC}"; \
	$(KUBECTL) exec -n $(NAMESPACE) $$pod -- tail -n 20 /project/apache-tomcat-7/logs/catalina.out; \
	echo -e "\n${GREEN}Health checks complete.${NC}"

describe-pod: ## Show detailed information about the application pod
	@pod=$$($(GET_POD_CMD)); \
	if [ -z "$$pod" ]; then \
		echo -e "${RED}No running StarExec pod found.${NC}"; \
		exit 1; \
	fi; \
	echo -e "${YELLOW}Describing pod: $$pod...${NC}"; \
	$(KUBECTL) describe pod $$pod -n $(NAMESPACE)

check-volumes: ## Check status of Persistent Volumes and Claims in the namespace
	@echo -e "${YELLOW}--- Persistent Volume Claims (PVCs) in namespace $(NAMESPACE) ---${NC}"
	@$(KUBECTL) get pvc -n $(NAMESPACE)
	@echo -e "\n${YELLOW}--- Persistent Volumes (PVs) (Cluster-wide) ---${NC}"
	@$(KUBECTL) get pv
	@echo -e "\n${YELLOW}--- Storage Classes (Cluster-wide) ---${NC}"
	@$(KUBECTL) get storageclass
	@echo -e "\n${YELLOW}--- Detailed PVC Description ---${NC}"
	@for pvc in $$($(KUBECTL) get pvc -n $(NAMESPACE) -o jsonpath='{.items[*].metadata.name}'); do \
		echo -e "\n${YELLOW}=== Details for PVC $$pvc ===${NC}"; \
		$(KUBECTL) describe pvc $$pvc -n $(NAMESPACE); \
	done

# ==============================================================================
# Informational Targets
# ==============================================================================

info: ## Display all resources in the application namespace
	@echo -e "${YELLOW}Listing all resources in namespace: $(NAMESPACE)...${NC}"
	$(KUBECTL) get all -n $(NAMESPACE)

list-pods: ## List pods in the application namespace
	@echo -e "${YELLOW}Listing pods in namespace: $(NAMESPACE)...${NC}"
	$(KUBECTL) get pods -n $(NAMESPACE) -o wide

list-services: ## List services in the application namespace
	@echo -e "${YELLOW}Listing services in namespace: $(NAMESPACE)...${NC}"
	$(KUBECTL) get services -n $(NAMESPACE) -o wide

list-deployments: ## List deployments in the application namespace
	@echo -e "${YELLOW}Listing deployments in namespace: $(NAMESPACE)...${NC}"
	$(KUBECTL) get deployments -n $(NAMESPACE) -o wide

list-nodes: ## List all nodes in the cluster
	@echo -e "${YELLOW}Listing cluster nodes...${NC}"
	$(KUBECTL) get nodes -o wide

# ==============================================================================
# Help Target
# ==============================================================================

help: ## Display this help message
	@echo -e "${GREEN}Makefile Commands:${NC}"
	@echo "------------------"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "  ${YELLOW}%-20s${NC} %s\n", $$1, $$2}' | \
		sort
	@echo "------------------"
	@echo "Usage: make [target]"
	@echo "Example: make apply"

# ==============================================================================
# Settings
# ==============================================================================

# Prevent echoing of commands unless VERBOSE=true
# ifndef VERBOSE
# .SILENT:
# endif

# Ensure CURDIR is set correctly
ifeq ($(origin CURDIR), undefined)
	CURDIR := $(shell pwd)
endif
