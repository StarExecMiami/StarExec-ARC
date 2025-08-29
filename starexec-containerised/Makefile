SHELL := /bin/bash

.ONESHELL:

USER=$(shell whoami)
PODMAN_SOCKET_PATH="/run/user/$(shell id -u)/podman/podman.sock" # Use id -u for portability
REGISTRY ?= ghcr.io
VERSION ?= latest
CONTAINER_NAME := starexec-app
STAREXEC_IMAGE := ghcr.io/starexecmiami/starexec-arc:${VERSION}
# Allow BACKUP_DIR to be provided via environment (or fallback to STAREXEC_BACKUP_DIR),
# otherwise default to $(CURDIR)/starexec_backup
ifndef BACKUP_DIR
	ifdef STAREXEC_BACKUP_DIR
		BACKUP_DIR := $(STAREXEC_BACKUP_DIR)
	else
		BACKUP_DIR := $(CURDIR)/starexec_backup
	endif
endif

# Ensure BACKUP_DIR is always an absolute path and export it for subprocesses
override BACKUP_DIR := $(abspath $(BACKUP_DIR))
export BACKUP_DIR

# Helper command to get the running container ID by name
GET_CONTAINER_ID_CMD = podman ps --filter name=$(CONTAINER_NAME) --format '{{.ID}}'
# Helper command to get any container (running or stopped) ID by name
GET_ANY_CONTAINER_ID_CMD = podman ps -a --filter name=$(CONTAINER_NAME) --format '{{.ID}}'

.PHONY: all local k8s starexec pull clean cleanVolumes connect start stop kill run ssh-setup mkcert-setup push microk8s-import list-microk8s microk8s-clean real-clean help state-init state-pack state-unpack state-restore state-create

all: ## Prompt for backend type
	@echo "Choose backend type:"
	@echo " 1) local"
	@echo " 2) k8s"
	@read -p "Enter choice [1-2]: " choice; \
	case "$$choice" in \
	  1) $(MAKE) local ;; \
	  2) $(MAKE) k8s ;; \
	  *) echo "Invalid choice. Please run 'make' again and choose 1 or 2." ;; \
	esac

local: ## Set backend type to local and prepare for building
	@echo "Setting backend type to local..."
	@sed -i "s/^Backend.Type:.*/Backend.Type: local/" dockerPackage/allScripts/starexecScripts/overrides.properties
	@echo "Backend type set to local. You can now run 'make starexec' to build the container."
	@$(MAKE) starexec

k8s: ## Set backend type to k8s and prepare for building
	@echo "Setting backend type to k8s..."
	@sed -i "s/^Backend.Type:.*/Backend.Type: k8s/" dockerPackage/allScripts/starexecScripts/overrides.properties
	@echo "Backend type set to k8s. You can now run 'make starexec' to build the container."
	@$(MAKE) starexec

starexec: ## Build the starexec container image (deprecated - use pull instead)
	@echo "Warning: Building locally is deprecated. Use 'make pull' to get the pre-built image."
	@echo "If you still want to build locally, the build process remains the same but is not recommended."
	VERSION=${VERSION} && \
	START_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build started at: $$START_TIME" | tee build-$$VERSION.log && \
	time podman build \
			-t starexec:$$VERSION . \
			2> >(tee -a build-$$VERSION.log >&2) && \
	END_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build finished at: $$END_TIME" | tee -a build-$$VERSION.log && \
	echo "Build duration: $$(date -u -d @$$(( $$(date -d "$$END_TIME" +%s) - $$(date -d "$$START_TIME" +%s) )) +%H:%M:%S)" | tee -a build-$$VERSION.log

pull: ## Pull the pre-built starexec image from GitHub Container Registry
	@echo "Pulling starexec image from ${STAREXEC_IMAGE}..."
	@podman pull ${STAREXEC_IMAGE}
	@podman tag ${STAREXEC_IMAGE} starexec:${VERSION}
	@echo "Image pulled and tagged as starexec:${VERSION}"

ssh-setup: ## Setup SSH keys for podman communication
	@echo "Setting up SSH keys..."
	echo "using ssh-keygen to make pub/priv keys in the current directory"; \
	echo "(only if they don't already exist)"; \
	[ -f starexec_podman_key ] || ssh-keygen -t ed25519 -N '' -f starexec_podman_key; \
	ssh-keyscan -H localhost >> ~/.ssh/known_hosts; \
	chmod 600 starexec_podman_key;

	@if [ "$(USER)" != "jenkins" ]; then \
		echo "Setting up SSH key for $(USER) user."; \
		mkdir -p ~/.ssh; \
		chmod 700 ~/.ssh; \
		if [ -f starexec_podman_key.pub ]; then \
			cat starexec_podman_key.pub >> ~/.ssh/authorized_keys; \
			chmod 600 ~/.ssh/authorized_keys; \
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
	@if ! podman image exists starexec:${VERSION}; then \
		echo "Image starexec:${VERSION} not found locally. Pulling from registry..."; \
		$(MAKE) pull; \
	fi
	@mkdir -p $(BACKUP_DIR)/volDB
	@mkdir -p $(BACKUP_DIR)/volExport
	@podman run --rm -it --name $(CONTAINER_NAME) \
			--workdir /home/starexec/StarExec-deploy \
			--cap-add=NET_RAW \
			--network slirp4netns:allow_host_loopback=true \
			--tmpfs /var/run/mysqld:rw,size=128m,mode=775 \
			-v $(BACKUP_DIR)/volDB:/var/lib/mysql:U \
			-v $(BACKUP_DIR)/volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-v $(HOME)/.local/share/mkcert/localhost.key:/etc/ssl/private/localhost.key \
			-v $(HOME)/.local/share/mkcert/localhost.crt:/etc/ssl/certs/localhost.crt \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=host.containers.internal \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			-e MYSQL_START_TIMEOUT=180 \
			--healthcheck-interval=60s \
			--healthcheck-timeout=15s \
			--healthcheck-retries=5 \
			--healthcheck-start-period=180s \
			--healthcheck-command "bash -c 'mysqladmin ping -u root --silent --connect-timeout=5 && (service apache2 status | grep -q \"running\" || pgrep apache2 >/dev/null) && (ps -ef | grep -v grep | grep -q \"org.apache.catalina.startup.Bootstrap\" || pgrep -f catalina >/dev/null) && (curl -s -k --max-time 10 -I https://localhost/starexec/ | grep -q \"200\\|302\\|301\" || curl -s -k --max-time 10 https://localhost/starexec/ >/dev/null)'" \
			-p 7827:443 -p 7826:80 starexec:${VERSION}

start-container: ## Start the starexec container (internal use)
	@echo "Starting the starexec container persistently..."
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -n "$$container_id" ]; then \
		echo "Container $(CONTAINER_NAME) is already running with ID: $$container_id"; \
		echo "Use 'make stop' to stop it first if you want to restart it."; \
		exit 0; \
	fi
	@stopped_container_id=$$($(GET_ANY_CONTAINER_ID_CMD)); \
	if [ -n "$$stopped_container_id" ]; then \
		echo "Found stopped container $(CONTAINER_NAME) with ID: $$stopped_container_id. Removing it..."; \
		podman rm $$stopped_container_id; \
	fi
	@if ! podman image exists starexec:${VERSION}; then \
		echo "Image starexec:${VERSION} not found locally. Pulling from registry..."; \
		$(MAKE) pull; \
	fi
	@mkdir -p $(BACKUP_DIR)/volDB
	@mkdir -p $(BACKUP_DIR)/volExport
	@echo "Launching container $(CONTAINER_NAME)..."
	@podman run -d --name $(CONTAINER_NAME) \
			--cap-add=NET_RAW \
			--network slirp4netns:allow_host_loopback=true \
			--tmpfs /var/run/mysqld:rw,size=128m,mode=775 \
			-v $(BACKUP_DIR)/volDB:/var/lib/mysql:U \
			-v $(BACKUP_DIR)/volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-v $(HOME)/.local/share/mkcert/localhost.key:/etc/ssl/private/localhost.key \
			-v $(HOME)/.local/share/mkcert/localhost.crt:/etc/ssl/certs/localhost.crt \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=host.containers.internal \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			-e MYSQL_START_TIMEOUT=180 \
			--healthcheck-interval=60s \
			--healthcheck-timeout=15s \
			--healthcheck-retries=5 \
			--healthcheck-start-period=180s \
			--healthcheck-command "bash -c 'mysqladmin ping -u root --silent --connect-timeout=5 && (service apache2 status | grep -q \"running\" || pgrep apache2 >/dev/null) && (ps -ef | grep -v grep | grep -q \"org.apache.catalina.startup.Bootstrap\" || pgrep -f catalina >/dev/null) && (curl -s -k --max-time 10 -I https://localhost/starexec/ | grep -q \"200\\|302\\|301\" || curl -s -k --max-time 10 https://localhost/starexec/ >/dev/null)'" \
			-p 7827:443 -p 7826:80 starexec:${VERSION}
	@echo "Waiting for container to initialize (approx 60 seconds)..."
	@sleep 60
	@printf "SUCCESS! VISIT IN YOUR BROWSER: https://localhost:7827\n\nuser: admin\npassword: admin\n\n"

start: ssh-setup mkcert-setup state-init ## Start the starexec container, preserving state
	@echo "Starting StarExec..."
	@# This will start a stopped container or create a new one if it does not exist.
	@$(MAKE) start-container
	
stop: ## Stop the persistent starexec container
	@echo "Stopping the starexec container..."
	@if [ -z "$$($(GET_CONTAINER_ID_CMD))" ]; then \
		echo "Container $(CONTAINER_NAME) is not running."; \
		exit 0; \
	fi
	$(MAKE) kill
	@echo "StarExec container stopped."

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
		# Try to find any container with the name (running or stopped)
		container_id=$$($(GET_ANY_CONTAINER_ID_CMD)); \
		if [ -n "$$container_id" ]; then \
			echo "Found stopped container $(CONTAINER_NAME), removing it..."; \
			podman rm $$container_id; \
		else \
			echo "Container $(CONTAINER_NAME) not found."; \
		fi; \
	fi

cleanVolumes: ## Remove starexec related volumes from BACKUP_DIR (WARNING: data loss)
	@echo "Removing volumes from: $(BACKUP_DIR)"
	@if [ ! -d "$(BACKUP_DIR)" ]; then \
		echo "Directory $(BACKUP_DIR) does not exist. Nothing to clean."; \
		exit 0; \
	fi
	@echo "WARNING: This will permanently delete all data in $(BACKUP_DIR)"
	@echo "Directory: $(BACKUP_DIR)"
	@read -r -p "Are you sure you want to continue? [y/N] " answer && \
	case "$$answer" in \
		[yY]) echo "Proceeding with deletion...";; \
		*) echo "Operation cancelled."; exit 0;; \
	esac
	@if [ -d "$(BACKUP_DIR)/volDB" ]; then \
		echo "Removing volDB..."; \
		podman unshare rm -rf $(BACKUP_DIR)/volDB 2>/dev/null || \
		sudo rm -rf $(BACKUP_DIR)/volDB 2>/dev/null || \
		{ echo "Cannot remove volDB. Use: sudo rm -rf $(BACKUP_DIR)/volDB"; exit 1; }; \
	fi
	@if [ -d "$(BACKUP_DIR)/volExport" ]; then \
		echo "Removing volExport..."; \
		podman unshare rm -rf $(BACKUP_DIR)/volExport 2>/dev/null || \
		sudo rm -rf $(BACKUP_DIR)/volExport 2>/dev/null || \
		{ echo "Cannot remove volExport. Use: sudo rm -rf $(BACKUP_DIR)/volExport"; exit 1; }; \
	fi
	@podman unshare rm -rf $(BACKUP_DIR) 2>/dev/null || sudo rm -rf $(BACKUP_DIR) 2>/dev/null || true
	@echo "Volumes removed successfully."

connect: ## Connect to the running starexec container via bash shell
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -n "$$container_id" ]; then \
		podman exec -it $$container_id /bin/bash; \
		exit 0; \
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
	@echo "MicroK8s image cleanup complete."

state-init: ## Initialize local state folders and prepare DB/export for sharing
	@echo "Initializing persistent state in $(BACKUP_DIR)..."
	@mkdir -p $(BACKUP_DIR)/volDB $(BACKUP_DIR)/volExport
	@echo "Fixing ownership for rootless Podman..."
	@podman unshare chown -R 999:999 $(BACKUP_DIR)/volDB 2>/dev/null || true
	@chmod 775 $(BACKUP_DIR)/volDB 2>/dev/null || true
	@podman unshare chown -R 153:160 $(BACKUP_DIR)/volExport 2>/dev/null || true
	@chmod -R 775 $(BACKUP_DIR)/volExport 2>/dev/null || true
	@# Check if database is already initialized by looking for key MariaDB files
	@if [ ! -d "$(BACKUP_DIR)/volDB/mysql" ] || [ ! -f "$(BACKUP_DIR)/volDB/ibdata1" ] || [ -z "$$(ls -A $(BACKUP_DIR)/volDB/mysql 2>/dev/null)" ]; then \
		echo "No existing database found. Creating new state..."; \
		$(MAKE) state-create; \
	else \
		echo "Database already exists in $(BACKUP_DIR). Using existing state."; \
		echo "To create a fresh state, use: make state-create"; \
		echo "To restore from a tar.gz, use: make state-restore FILE=path.tar.gz"; \
	fi
	@echo "State initialization complete."

state-create: ## Force creation of a new database state (WARNING: destroys existing data)
	@echo "Creating new database state in $(BACKUP_DIR)..."
	@mkdir -p $(BACKUP_DIR)/volDB $(BACKUP_DIR)/volExport
	@if ! podman image exists starexec:${VERSION}; then \
		echo "Image starexec:${VERSION} not found locally. Pulling..."; \
		$(MAKE) pull; \
	fi
	@echo "Removing existing database data...";
	@podman unshare rm -rf $(BACKUP_DIR)/volDB/* 2>/dev/null || true
	@echo "Running database initialization...";
	@podman run --rm \
		--user 0 \
		--tmpfs /var/run/mysqld:rw,size=128m,mode=775 \
		-v $(BACKUP_DIR)/volDB:/var/lib/mysql:U \
		starexec:${VERSION} bash -c '\
			chown -R mysql:mysql /var/lib/mysql && \
			mysql_install_db --user=mysql --datadir=/var/lib/mysql --basedir=/usr --force && \
			chown -R mysql:mysql /var/lib/mysql && \
			chmod -R 755 /var/lib/mysql && \
			find /var/lib/mysql -type d -exec chmod 755 {} \; && \
			find /var/lib/mysql -type f -exec chmod 644 {} \; \
		'
	@echo "Fixing final ownership after initialization..."
	@podman unshare chown -R 999:999 $(BACKUP_DIR)/volDB 2>/dev/null || true
	@podman unshare chown -R 153:160 $(BACKUP_DIR)/volExport 2>/dev/null || true
	@if [ ! -d "$(BACKUP_DIR)/volDB/mysql" ] || [ ! -f "$(BACKUP_DIR)/volDB/ibdata1" ]; then \
		echo "ERROR: Database initialization failed!"; \
		exit 1; \
	fi
	@echo "New database state created successfully."

state-restore: ## Restore state from a tar.gz file (use: make state-restore FILE=path.tar.gz BACKUP_DIR=target)
	@if [ -z "$$FILE" ]; then \
		echo "Usage: make state-restore FILE=/path/to/starexec-state-*.tar.gz [BACKUP_DIR=target_directory]"; \
		echo "Example: make state-restore FILE=shared-state.tar.gz BACKUP_DIR=restored_backup"; \
		exit 1; \
	fi
	@if [ ! -f "$$FILE" ]; then \
		echo "Error: File $$FILE not found."; \
		exit 1; \
	fi
	@echo "Restoring state from $$FILE to $(BACKUP_DIR)..."
	@if [ -d "$(BACKUP_DIR)" ]; then \
		echo "WARNING: Target directory $(BACKUP_DIR) already exists."; \
		read -r -p "Do you want to overwrite it? [y/N] " answer && \
		case "$$answer" in \
			[yY]) echo "Removing existing directory..."; \
				  podman unshare rm -rf $(BACKUP_DIR) 2>/dev/null || \
				  sudo rm -rf $(BACKUP_DIR) 2>/dev/null || \
				  { echo "Cannot remove existing directory. Use: sudo rm -rf $(BACKUP_DIR)"; exit 1; };; \
			*) echo "Operation cancelled."; exit 1;; \
		esac; \
	fi
	@echo "Extracting state archive..."
	@mkdir -p $$(dirname $(BACKUP_DIR))
	@tar -C $$(dirname $(BACKUP_DIR)) -xzf "$$FILE"
	@extracted_dir=$$(tar -tzf "$$FILE" | head -1 | cut -f1 -d"/"); \
	if [ "$$extracted_dir" != "$$(basename $(BACKUP_DIR))" ]; then \
		echo "Renaming extracted directory $$extracted_dir to $$(basename $(BACKUP_DIR))..."; \
		mv "$$(dirname $(BACKUP_DIR))/$$extracted_dir" "$(BACKUP_DIR)"; \
	fi
	@echo "Fixing ownership for restored state..."
	@podman unshare chown -R 999:999 $(BACKUP_DIR)/volDB 2>/dev/null || true
	@podman unshare chown -R 153:160 $(BACKUP_DIR)/volExport 2>/dev/null || true
	@chmod 775 $(BACKUP_DIR)/volDB 2>/dev/null || true
	@chmod -R 775 $(BACKUP_DIR)/volExport 2>/dev/null || true
	@echo "State restored successfully to $(BACKUP_DIR)"
	@echo "You can now start with: make start BACKUP_DIR=$(BACKUP_DIR)"

state-pack: ## Create a tar.gz with the current backup state to share
	@echo "Packing $(BACKUP_DIR) into a tar.gz..."
	@if [ ! -d "$(BACKUP_DIR)" ]; then \
		echo "Error: Directory $(BACKUP_DIR) does not exist."; \
		echo "Create a state first with: make start"; \
		exit 1; \
	fi
	@ts=$$(date +%Y%m%d_%H%M%S); \
	backup_name=$$(basename $(BACKUP_DIR)); \
	out="starexec-state-$$backup_name-$$ts.tar.gz"; \
	echo "Creating archive: $$out"; \
	tar -C $$(dirname $(BACKUP_DIR)) -czf "$$out" "$$backup_name"; \
	echo "Created: $$out"; \
	echo "Share this file with: make state-restore FILE=$$out BACKUP_DIR=target_directory"

state-unpack: ## Unpack a state tar.gz into current project (DEPRECATED - use state-restore)
	@echo "WARNING: state-unpack is deprecated. Use 'make state-restore' instead."
	@echo "Usage: make state-restore FILE=/path/to/starexec-state-*.tar.gz BACKUP_DIR=target_directory"
	@if [ -n "$$FILE" ]; then \
		echo "Calling state-restore with your parameters..."; \
		$(MAKE) state-restore FILE="$$FILE"; \
	fi

help: ## Display help for Makefile targets
	@echo "Makefile Commands:"
	@echo "------------------"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "  %-20s %s\n", $$1, $$2}' | \
		sort
	@echo "------------------"
	@echo "Usage: make [target]"
	@echo "Example: make start"
	@echo ""
	@echo "State Management Workflow:"
	@echo "  1. Create new state:     make start"
	@echo "  2. Pack for sharing:     make state-pack"
	@echo "  3. Restore shared state: make state-restore FILE=archive.tar.gz BACKUP_DIR=my_backup"
	@echo "  4. Use restored state:   make start BACKUP_DIR=my_backup"


# Prevent echoing of commands unless VERBOSE=true
# ifndef VERBOSE
# .SILENT:
# endif

# Ensure CURDIR is set correctly
ifeq ($(origin CURDIR), undefined)
	CURDIR := $(shell pwd)
endif

# Always ensure BACKUP_DIR is absolute
override BACKUP_DIR := $(abspath $(BACKUP_DIR))
ifeq ($(origin CURDIR), undefined)
	CURDIR := $(shell pwd)
endif
