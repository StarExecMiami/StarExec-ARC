SHELL := /bin/bash

.ONESHELL:

USER=$(shell whoami)
PODMAN_SOCKET_PATH="/run/user/$(shell id -u)/podman/podman.sock" # Use id -u for portability
REGISTRY ?= docker.io
VERSION ?= latest
CONTAINER_NAME := starexec-app

# State Backup Configuration
BACKUP_DIR := $(CURDIR)/state-backup
# Paths inside the container to backup/restore
STATE_PATHS := /var/lib/mysql /home/starexec

# Helper command to get the running container ID by name
GET_CONTAINER_ID_CMD = podman ps --filter name=$(CONTAINER_NAME) --format '{{.ID}}'

.PHONY: all starexec clean cleanVolumes connect start stop backup-state restore-state kill run ssh-setup mkcert-setup push microk8s-import list-microk8s microk8s-clean real-clean help
all: starexec

starexec: ## Build the starexec container image
	@echo "Building the starexec image..."
	@echo "Make sure to run 'make mkcert-setup' and 'ssh-setup' first."
	@echo "Building starexec image with version: ${VERSION}..."

	VERSION=${VERSION} && \
	START_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build started at: $$START_TIME" | tee build-$$VERSION.log && \
	time podman build \
			-t starexec:$$VERSION . \
			2> >(tee -a build-$$VERSION.log >&2) && \
	END_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build finished at: $$END_TIME" | tee -a build-$$VERSION.log && \
	echo "Build duration: $$(date -u -d @$$(( $$(date -d "$$END_TIME" +%s) - $$(date -d "$$START_TIME" +%s) )) +%H:%M:%S)" | tee -a build-$$VERSION.log

ssh-setup: ## Setup SSH keys for podman communication
	@echo "Setting up SSH keys..."
	echo "using ssh-keygen to make pub/priv keys in the current directory"; \
	echo "(only if they don't already exist)"; \
	[ -f starexec_podman_key ] || ssh-keygen -t ed25519 -N '' -f starexec_podman_key; \
	ssh-keyscan -H localhost >> ~/.ssh/known_hosts; \
	chmod 600 starexec_podman_key;

	@if [ "$(USER)" != "jenkins" ]; then \
		echo "Setting up SSH key for $(USER) user."; \
		if [ -f starexec_podman_key.pub ]; then \
			cat starexec_podman_key.pub >> ~/.ssh/authorized_keys; \
		fi \
	else \
		echo "Skipping SSH key setup for Jenkins user."; \
	fi

mkcert-setup: ## Setup mkcert and generate localhost TLS certificates
	@echo "Setting up mkcert and localhost certificates..."
	@echo "Run this only if certificates are missing."
	@echo "Checking for mkcert and libnss3-tools..."
	@if [ "$$(uname)" = "Linux" ]; then \
		if ! command -v mkcert > /dev/null 2>&1 || ! dpkg -l | grep -q libnss3-tools; then \
			echo >&2 "mkcert or libnss3-tools is not installed. Installing..."; \
			sudo apt update && sudo apt install -y mkcert libnss3-tools; \
			echo "mkcert and libnss3-tools installed successfully."; \
		else \
			echo "mkcert and libnss3-tools are already installed."; \
		fi \
	elif [ "$$(uname)" = "Darwin" ]; then \
		if ! command -v mkcert > /dev/null 2>&1; then \
			brew install mkcert; \
		fi \
	else \
		echo "Unsupported OS. Please install mkcert and libnss3-tools manually."; \
		exit 1; \
	fi
	
	@echo "Creating mkcert configuration directory..."
	@mkdir -p $(HOME)/.local/share/mkcert > /dev/null 2>&1
	
	@echo "Setting up certificates..."
	@mkcert -install
	@mkdir -p $(HOME)/.local/share/mkcert
	@if [ ! -f "$(HOME)/.local/share/mkcert/localhost.crt" ] || [ ! -f "$(HOME)/.local/share/mkcert/localhost.key" ]; then \
		echo "Generating localhost certificates..."; \
		cd $(HOME)/.local/share/mkcert && mkcert -cert-file localhost.crt -key-file localhost.key localhost; \
	fi
	
	@echo "Done. Certificates are ready in $(HOME)/.local/share/mkcert:"
	@echo "  - localhost.crt"
	@echo "  - localhost.key"

run: ssh-setup mkcert-setup ## Run the starexec container interactively (for testing/dev)
	@echo "Running the starexec container interactively (will be removed on exit)..."
	@echo "Make sure to run 'make mkcert-setup' and 'ssh-setup' first."
	# This target is for temporary runs. Use 'make start' for persistent runs with state.
	@podman run --rm -it -v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-v $(HOME)/.local/share/mkcert/localhost.key:/etc/ssl/private/localhost.key \
			-v $(HOME)/.local/share/mkcert/localhost.crt:/etc/ssl/certs/localhost.crt \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=localhost \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			--healthcheck-interval=30s \
			--healthcheck-timeout=10s \
			--healthcheck-retries=3 \
			--healthcheck-start-period=120s \
			--healthcheck-command "bash -c 'mysqladmin ping -u root --silent --connect-timeout=3 && service apache2 status | grep -q \"running\" && ps -ef | grep -v grep | grep -q \"org.apache.catalina.startup.Bootstrap\" && curl -s -k --max-time 5 -I https://localhost/starexec/ | grep -q \"200 OK\"'" \
			-p 7827:443 starexec:${VERSION}

start: ssh-setup mkcert-setup ## Start the starexec container persistently and restore state if available
	@echo "Starting the starexec container persistently..."
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -n "$$container_id" ]; then \
		echo "Container $(CONTAINER_NAME) is already running with ID: $$container_id"; \
		echo "Use 'make stop' to stop it first if you want to restart it."; \
		exit 0; \
	fi
	@echo "Launching container $(CONTAINER_NAME)..."
	@podman run -d --name $(CONTAINER_NAME) \
			-v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-v $(HOME)/.local/share/mkcert/localhost.key:/etc/ssl/private/localhost.key \
			-v $(HOME)/.local/share/mkcert/localhost.crt:/etc/ssl/certs/localhost.crt \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=localhost \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			--healthcheck-interval=30s \
			--healthcheck-timeout=10s \
			--healthcheck-retries=3 \
			--healthcheck-start-period=120s \
			--healthcheck-command "bash -c 'mysqladmin ping -u root --silent --connect-timeout=3 && service apache2 status | grep -q \"running\" && ps -ef | grep -v grep | grep -q \"org.apache.catalina.startup.Bootstrap\" && curl -s -k --max-time 5 -I https://localhost/starexec/ | grep -q \"200 OK\"'" \
			-p 7827:443 starexec:${VERSION}
	@echo "Waiting for container to initialize (approx 60 seconds)..."
	@sleep 60
	@if [ -d "$(BACKUP_DIR)" ]; then \
		echo "Backup directory found. Restoring state..."; \
		$(MAKE) restore-state; \
	else \
		echo "No backup directory found. Starting with fresh state."; \
	fi
	@echo "StarExec container started. Access at https://localhost:7827"

stop: ## Backup state and stop the persistent starexec container
	@echo "Stopping the starexec container..."
	@if [ -z "$$($(GET_CONTAINER_ID_CMD))" ]; then \
		echo "Container $(CONTAINER_NAME) is not running."; \
		exit 0; \
	fi
	$(MAKE) backup-state
	$(MAKE) kill
	@echo "StarExec container stopped. State backed up to $(BACKUP_DIR)."

backup-state: ## Backup application state from the running container to local directory
	@echo "Backing up StarExec state..."
	@mkdir -p $(BACKUP_DIR)
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -z "$$container_id" ]; then \
		echo "Error: Container $(CONTAINER_NAME) not found or not running."; \
		exit 1; \
	fi; \
	echo "Using container: $$container_id"; \
	for path in $(STATE_PATHS); do \
		target_dir="$(BACKUP_DIR)$${path}"; \
		echo "Backing up $$path to $${target_dir}..."; \
		mkdir -p "$${target_dir}"; \
		rm -rf "$${target_dir}/*"; \
		podman exec $$container_id bash -c "cd $${path} && tar cf - ." | tar xf - -C "$${target_dir}"; \
		if [ $$? -ne 0 ]; then echo "Error during backup of $$path."; exit 1; fi; \
	done
	@echo "State backup completed successfully to $(BACKUP_DIR)"
	@echo "Backup size:"
	@du -sh $(BACKUP_DIR)

restore-state: ## Restore application state from local backup to the running container
	@echo "Restoring StarExec state..."
	@if [ ! -d "$(BACKUP_DIR)" ]; then \
		echo "Error: Backup directory $(BACKUP_DIR) not found."; \
		exit 1; \
	fi
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -z "$$container_id" ]; then \
		echo "Error: Container $(CONTAINER_NAME) not found or not running."; \
		exit 1; \
	fi; \
	echo "Restoring state to container: $$container_id from $(BACKUP_DIR)..."; \
	# Stop services before restoring files
	@echo "Stopping services inside the container..."; \
	podman exec $$container_id /bin/bash -c "apache2ctl -k graceful-stop || true; \
		/project/apache-tomcat-7/bin/shutdown.sh || true; \
		if [ -f /var/run/mysqld/mysqld.pid ]; then mysqladmin shutdown || pkill -9 mysqld; fi; \
		sleep 5; pkill -9 mysqld || true; \
		echo 3 > /proc/sys/vm/drop_caches || true; sync" || \
		{ echo "Error stopping services in container."; exit 1; }
	
	# Restore files
	@for path in $(STATE_PATHS); do \
		source_dir="$(BACKUP_DIR)$${path}"; \
		if [ ! -d "$$source_dir" ]; then \
			echo "Warning: Backup source directory '$$source_dir' not found. Skipping restore for $$path."; \
			continue; \
		fi; \
		echo "Restoring $$path from $$source_dir..."; \
		tar cf - -C "$(BACKUP_DIR)" .$${path} | podman exec -i $$container_id tar xf - -C / ; \
		if [ $$? -ne 0 ]; then echo "Error restoring $$path."; exit 1; fi; \
	done
	
	# Restart services after restoring files
	@echo "Restarting services inside the container..."; \
	podman exec $$container_id /bin/bash -c "echo \"Fixing permissions...\"; \
		chown -R mysql:mysql /var/lib/mysql; \
		rm -rf /var/run/mysqld; mkdir -p /var/run/mysqld; chown mysql:mysql /var/run/mysqld; chmod 777 /var/run/mysqld; \
		echo \"[mysqld]\" > /tmp/minimal.cnf; \
		echo \"innodb_buffer_pool_size=512M\" >> /tmp/minimal.cnf; \
		echo \"Starting MySQL...\"; \
		mysqld_safe --defaults-file=/tmp/minimal.cnf --user=mysql --skip-syslog & \
		for i in \$$(seq 1 30); do \
		  if mysqladmin ping --silent; then echo \"MySQL is up\"; break; fi; \
		  if [ \$\$i -eq 30 ]; then echo \"ERROR: MySQL did not start\"; exit 1; fi; \
		  sleep 2; \
		done; \
		echo \"Restarting Apache and Tomcat...\"; \
		apache2ctl -k start || true; \
		sleep 2; \
		/project/apache-tomcat-7/bin/startup.sh" || \
		{ echo "Error restarting services in container."; exit 1; }
	@echo "State restore and service restart completed successfully."

clean: ## Remove the starexec container image and dangling images
	@echo "Checking for existing 'starexec' image..."
	@podman image inspect starexec > /dev/null 2>&1 && { \
		echo "Removing 'starexec' image..."; \
		podman image rm -f starexec; \
	} || echo "'starexec' image not found."

	@echo "Cleaning up dangling images..."
	@dangling="$$(podman images -q --filter dangling=true)"; \
	if [ -n "$$dangling" ]; then \
		echo "Removing dangling images: $$dangling"; \
		podman image rm -f $$dangling; \
	else \
		echo "No dangling images to remove."; \
	fi

real-clean: ## WARNING: Reset Podman - removes ALL containers, images, volumes
	@echo "WARNING: This will reset Podman and remove ALL containers, images, and volumes."
	@read -r -p "Are you sure you want to continue? [y/N] " answer && \
	case "$$answer" in \
		[yY]) echo "Resetting Podman..."; podman system reset -f;; \
		*) echo "Operation cancelled.";; \
	esac

kill: ## Stop and remove the persistent starexec container
	@echo "Stopping and removing container $(CONTAINER_NAME)..."
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -n "$$container_id" ]; then \
		podman stop $$container_id && podman rm $$container_id; \
	else \
		echo "Container $(CONTAINER_NAME) not found or not running."; \
	fi

cleanVolumes: ## Remove starexec related volumes (WARNING: data loss)
	@echo "Removing volumes: volDB, volStar, volPro, volExport"
	@podman volume rm -f volDB volStar volPro volExport

connect: ## Connect to the running starexec container via bash shell
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -n "$$container_id" ]; then \
		podman exec -it $$container_id /bin/bash; \
	else \
		echo "Error: No running StarExec container found."; \
		exit 1; \
	fi

push: ## Push the starexec image to a container registry
	@echo "Pushing starexec:${VERSION} image..."
	@if [ "${REGISTRY}" = "microk8s" ]; then \
		echo "Pushing to MicroK8s registry at localhost:32000"; \
		microk8s enable registry; \
		podman login localhost:32000 --tls-verify=false; \
		podman tag starexec:${VERSION} localhost:32000/starexec:${VERSION}; \
		podman push localhost:32000/starexec:${VERSION} --tls-verify=false; \
		echo "Pushing to MicroK8s registry at localhost:32000 done."; \
		make microk8s-import; \
		make list-microk8s; \
		echo "Pushing to MicroK8s registry done."; \
	else \
		echo "Pushing to Docker Hub as tptpstarexec/starexec:${VERSION}"; \
		podman login docker.io; \
		podman tag starexec:${VERSION} docker.io/tptpstarexec/starexec:${VERSION}; \
		podman push docker.io/tptpstarexec/starexec:${VERSION}; \
		echo "Pushing to Docker Hub done."; \
	fi
	@echo "Image pushed successfully."

microk8s-import: ## Import the starexec image into MicroK8s registry
	@echo "Importing starexec:${VERSION} image into MicroK8s..."
	@podman save localhost:32000/starexec:${VERSION} -o starexec-image.tar
	@microk8s ctr image import starexec-image.tar
	@rm starexec-image.tar
	@echo "Image imported into MicroK8s successfully."

list-microk8s: ## List starexec images in the MicroK8s registry
	@echo "Listing images in MicroK8s registry..."
	@microk8s ctr images list | grep starexec
	@echo "Listing images in MicroK8s registry done."

microk8s-clean: ## Clean up starexec images from the MicroK8s registry
	@echo "Cleaning up MicroK8s images..."
	@for img in localhost:32000/starexec:${VERSION} localhost:32000/starexec:latest; do \
		if microk8s ctr images list | grep -q "$$img"; then \
			microk8s ctr images rm "$$img"; \
		fi; \
	done
	@echo "MicroK8s images cleaned up."

help: ## Display help for Makefile targets
	@echo "Makefile Commands:"
	@echo "------------------"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "  %-20s %s\n", $$1, $$2}' | \
		sort
	@echo "------------------"
	@echo "Usage: make [target]"
	@echo "Example: make start"

# Prevent echoing of commands unless VERBOSE=true
# ifndef VERBOSE
# .SILENT:
# endif

# Ensure CURDIR is set correctly
ifeq ($(origin CURDIR), undefined)
	CURDIR := $(shell pwd)
endif