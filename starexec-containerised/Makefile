# ---------------------------------------------------------------------------
# StarExec persistent volumes (host -> container):
#   volDB       -> /var/lib/mysql
#       MariaDB data directory (system tables, ibdata1, ib_logfile*, user DBs).
#       Must be initialized atomically. Wiped/recreated only by state-create.
#   volExport   -> /export
#       Shared/exportable artifacts (job outputs, downloadable bundles, etc.).
#       Preserved across DB resets. Removed only by state-delete.
#   volStarexec -> /home/starexec
#       Application runtime home: configs, logs, unpacked solvers/benchmarks,
#       job input/output staging, processor scripts.
#       Preserved across DB resets. Removed only by state-delete.
#
# Lifecycle summary:
#   make start / state-init : creates dirs; initializes DB only if missing.
#   make state-create       : forces NEW database (volDB only).
#   make state-pack         : archives all three volumes.
#   make state-restore      : restores all three.
#   make state-delete       : destroys all three (irreversible).
#
# Ownership (container UIDs/GIDs):
#   mysql:        999:999        (volDB)
#   export user:  153:160        (volExport)
#   starexec user 152:160        (volStarexec)
#
# Host cleanup note:
#   Direct 'rm -rf starexec_saved_state' may fail due to shifted subuids.
#   Use: make state-delete
#   Or: make state-fix-perms (reclaim) then rm -rf
# ---------------------------------------------------------------------------

SHELL := /bin/bash

.ONESHELL:

USER=$(shell whoami)
PODMAN_SOCKET_PATH="/run/user/$(shell id -u)/podman/podman.sock" # Use id -u for portability
REGISTRY ?= ghcr.io
VERSION ?= latest
CONTAINER_NAME := starexec-app
STAREXEC_IMAGE := ghcr.io/starexecmiami/starexec-arc:${VERSION}
# Allow SAVED_STATE_DIR to be provided via the environment variable STAREXEC_SAVED_STATE_DIR,
# otherwise default to $(CURDIR)/starexec_saved_state
ifndef SAVED_STATE_DIR
	ifdef STAREXEC_SAVED_STATE_DIR
		SAVED_STATE_DIR := $(STAREXEC_SAVED_STATE_DIR)
	else
		SAVED_STATE_DIR := $(CURDIR)/starexec_saved_state
	endif
endif

# Ensure SAVED_STATE_DIR is always an absolute path and export it for subprocesses
override SAVED_STATE_DIR := $(abspath $(SAVED_STATE_DIR))
export SAVED_STATE_DIR

# Reusable test to determine if DB state is uninitialized
DB_INIT_TEST = [ ! -d "$(SAVED_STATE_DIR)/volDB/mysql" ] || [ ! -f "$(SAVED_STATE_DIR)/volDB/ibdata1" ] || [ -z "$$(ls -A $(SAVED_STATE_DIR)/volDB/mysql 2>/dev/null)" ]

# Helper command to get the running container ID by name
GET_CONTAINER_ID_CMD = podman ps --filter name=$(CONTAINER_NAME) --format '{{.ID}}'
# Helper command to get any container (running or stopped) ID by name
GET_ANY_CONTAINER_ID_CMD = podman ps -a --filter name=$(CONTAINER_NAME) --format '{{.ID}}'

# Internal helper targets (not listed in help)
.state-mkdirs:
	@mkdir -p $(SAVED_STATE_DIR)/volDB $(SAVED_STATE_DIR)/volExport $(SAVED_STATE_DIR)/volStarexec

.state-chown-container:
	@podman unshare chown -R 999:999 $(SAVED_STATE_DIR)/volDB 2>/dev/null || true
	@podman unshare chown -R 153:160 $(SAVED_STATE_DIR)/volExport 2>/dev/null || true
	@podman unshare chown -R 152:160 $(SAVED_STATE_DIR)/volStarexec 2>/dev/null || true

.state-fix-perms:
	@$(MAKE) .state-chown-container

.PHONY: all local k8s starexec pull clean connect start stop kill run ssh-setup mkcert-setup push microk8s-import list-microk8s microk8s-clean real-clean help state-init state-pack state-unpack state-restore state-create image state-fix-perms state-delete 

all: ## Prompt for backend type and build
	@echo "Choose backend type:"
	@echo "  1) local"
	@echo "  2) k8s"
	@read -r -p "Enter choice [1-2]: " choice; \
	case "$$choice" in \
	  1) $(MAKE) local ;; \
	  2) $(MAKE) k8s ;; \
	  *) echo "Invalid choice. Please run 'make' again and choose 1 or 2." ;; \
	esac

local: ## Set backend type to local and build
	@echo "Setting backend type to local..."
	@sed -i "s/^Backend.Type:.*/Backend.Type: local/" dockerPackage/allScripts/starexecScripts/overrides.properties
	@echo "Backend type set to local. You can now run 'make starexec' to build the container."
	@$(MAKE) starexec

k8s: ## Set backend type to k8s and build
	@echo "Setting backend type to k8s..."
	@sed -i "s/^Backend.Type:.*/Backend.Type: k8s/" dockerPackage/allScripts/starexecScripts/overrides.properties
	@echo "Backend type set to k8s. You can now run 'make starexec' to build the container."
	@$(MAKE) starexec

starexec: ## Build the StarExec container image (internal use)
	@echo "Warning: Building locally is deprecated. Use 'make pull' to get the pre-built image."
	@echo "If you still want to build locally, the build process remains the same but is not recommended."
	VERSION=${VERSION} && \
	START_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build started at: $$START_TIME" | tee build-$$VERSION.log && \
	time podman build \
			-t starexec:$$VERSION . \
			2> >(tee -a build-$$VERSION.log >&2) && \
	END_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build finished at: $$END_TIME" | tee -a build-$$VERSION.log && \
	echo "Build duration: $$(date -u -d @$$(( $$(date -d "$$END_TIME" +%s) - $$(date -d "$$START_TIME" +%s) )) +%H:%M:%S)" | tee -a build-$$VERSION.log

pull: ## Pull the pre-built StarExec image from GitHub Container Registry
	@echo "Pulling StarExec image from ${STAREXEC_IMAGE}..."
	@podman pull ${STAREXEC_IMAGE}
	@podman tag ${STAREXEC_IMAGE} starexec:${VERSION}
	@echo "Image pulled and tagged as starexec:${VERSION}"

# Add image target to ensure image availability
image: ## Ensure the StarExec image is available locally
	@if ! podman image exists starexec:${VERSION}; then \
		echo "Image starexec:${VERSION} not found locally. Pulling from registry..."; \
		$(MAKE) pull; \
	fi

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
		fi; \
	else \
		echo "Skipping SSH key setup for Jenkins user."; \
	fi

mkcert-setup: ## Ensure mkcert and localhost TLS certificates are present (does NOT auto-install packages)
	@echo "Checking mkcert and localhost certificates (no automatic system package installs performed)..."
	@if ! command -v mkcert > /dev/null 2>&1; then \
		echo "Error: 'mkcert' is not installed. Please install mkcert (see README) or run: make software_install"; \
		exit 1; \
	fi
	@if [ "$$(uname)" = "Linux" ]; then \
		if ! dpkg -l | grep -q libnss3-tools; then \
			echo "Error: 'libnss3-tools' is not installed. Please install it (see README) or run: make software_install"; \
			exit 1; \
		fi \
	fi
	
	@echo "Creating mkcert configuration directory..."
	@mkdir -p $(HOME)/.local/share/mkcert > /dev/null 2>&1

	@echo "Setting up certificates (mkcert must already be installed)..."
	@mkcert -install
	@mkdir -p $(HOME)/.local/share/mkcert
	@if [ ! -f "$(HOME)/.local/share/mkcert/localhost.crt" ] || [ ! -f "$(HOME)/.local/share/mkcert/localhost.key" ]; then \
		echo "Generating localhost certificates..."; \
		cd $(HOME)/.local/share/mkcert && mkcert -cert-file localhost.crt -key-file localhost.key localhost; \
	fi
	
	@echo "Done. Certificates are ready in $(HOME)/.local/share/mkcert:"
	@echo "  - localhost.crt"
	@echo "  - localhost.key"

software_install: ## Optionally install host software (podman, mkcert, libnss3-tools) - interactive and opt-in
	@echo "This target will attempt to install podman, mkcert and libnss3-tools on supported systems (opt-in)."
	@read -r -p "Proceed with installation? [y/N] " answer && case "$$answer" in [yY]) true ;; *) echo "Cancelled."; exit 1 ;; esac
	@if [ "$$(uname)" = "Linux" ]; then \
		echo "Installing podman, mkcert and libnss3-tools on Linux (requires sudo)..."; \
		sudo apt update && sudo apt install -y podman mkcert libnss3-tools || { echo "Install failed; please install podman, mkcert and libnss3-tools manually."; exit 1; }; \
		echo "Installation complete."; \
	elif [ "$$(uname)" = "Darwin" ]; then \
		echo "Installing podman and mkcert on macOS via Homebrew..."; \
		brew install podman mkcert || { echo "Homebrew install failed; please install podman and mkcert manually."; exit 1; }; \
		echo "Note: macOS requires Podman machine (podman machine init && podman machine start) to run the StarExec container in a Linux VM."; \
	else \
		echo "Unsupported OS for automated installation. Please install podman, mkcert and libnss3-tools manually."; \
		exit 1; \
	fi

preflight-check: ## Verify required host tools (podman, mkcert, libnss3-tools) and instruct to run software_install if missing
	@echo "Checking required host tools..."
	@missing=""
	@if ! command -v podman >/dev/null 2>&1; then \
		echo "  - podman: MISSING"; \
		missing="$$missing podman"; \
	else \
		echo "  - podman: OK"; \
	fi
	@if ! command -v mkcert >/dev/null 2>&1; then \
		echo "  - mkcert: MISSING"; \
		missing="$$missing mkcert"; \
	else \
		echo "  - mkcert: OK"; \
	fi
	@if [ "$$(uname)" = "Linux" ]; then \
		if ! dpkg -l | grep -q libnss3-tools; then \
			echo "  - libnss3-tools: MISSING"; \
			missing="$$missing libnss3-tools"; \
		else \
			echo "  - libnss3-tools: OK"; \
		fi; \
	fi
	@if [ -n "$$missing" ]; then \
		echo ""; \
		echo "One or more prerequisites are missing:$$missing"; \
		echo "Please run: make software_install"; \
		exit 1; \
	else \
		echo "All prerequisites present."; \
	fi

run: ssh-setup mkcert-setup ## Run the StarExec container interactively (for testing/dev)
	@echo "Running the StarExec container interactively (will be removed on exit)..."
	@echo "Make sure to run 'make mkcert-setup' and 'ssh-setup' first."
	@if ! podman image exists starexec:${VERSION}; then \
		echo "Image starexec:${VERSION} not found locally. Pulling from registry..."; \
		$(MAKE) pull; \
	fi
	@mkdir -p $(SAVED_STATE_DIR)/volDB
	@mkdir -p $(SAVED_STATE_DIR)/volExport
	@mkdir -p $(SAVED_STATE_DIR)/volStarexec
	@podman run --rm -it --name $(CONTAINER_NAME) \
			--cap-add=NET_RAW \
			--network slirp4netns:allow_host_loopback=true \
			--tmpfs /var/run/mysqld:rw,size=128m,mode=775 \
			-v $(SAVED_STATE_DIR)/volDB:/var/lib/mysql:U \
			-v $(SAVED_STATE_DIR)/volExport:/export \
			-v $(SAVED_STATE_DIR)/volStarexec:/home/starexec \
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

start: preflight-check state-init image mkcert-setup ## Start the StarExec container, restoring any saved state
	@echo "Starting StarExec..."
	@echo "Note: Podman and mkcert are prerequisites; if missing see README or run: make software_install (opt-in)."
	@echo "Starting the StarExec container persistently..."
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
	@mkdir -p $(SAVED_STATE_DIR)/volDB
	@mkdir -p $(SAVED_STATE_DIR)/volExport
	@mkdir -p $(SAVED_STATE_DIR)/volStarexec
	@echo "Launching container $(CONTAINER_NAME)..."
	@podman run -d --name $(CONTAINER_NAME) \
			--cap-add=NET_RAW \
			--network slirp4netns:allow_host_loopback=true \
			--tmpfs /var/run/mysqld:rw,size=128m,mode=775 \
			-v $(SAVED_STATE_DIR)/volDB:/var/lib/mysql:U \
			-v $(SAVED_STATE_DIR)/volExport:/export \
			-v $(SAVED_STATE_DIR)/volStarexec:/home/starexec \
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

stop: ## Stop the StarExec container, saving the state
	@echo "Stopping the StarExec container..."
	@if [ -z "$$($(GET_CONTAINER_ID_CMD))" ]; then \
		echo "Container $(CONTAINER_NAME) is not running."; \
		exit 0; \
	fi
	$(MAKE) kill
	@echo "StarExec container stopped."

clean: ## Remove the StarExec container image and dangling images
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

real-clean: ## Reset Podman - removes ALL containers, images, volumes
	@echo "WARNING: This will reset Podman and remove ALL containers, images, and volumes."
	@read -r -p "Are you sure you want to continue? [y/N] " answer && \
	case "$$answer" in \
		[yY]) echo "Resetting Podman..."; podman system reset -f;; \
		*) echo "Operation cancelled.";; \
	esac

kill: ## Stop and remove the StarExec container
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

state-delete: ## Delete StarExec related volumes from STAREXEC_SAVED_STATE_DIR 
	@echo "Removing volumes from: $(SAVED_STATE_DIR)"
	@if [ ! -d "$(SAVED_STATE_DIR)" ]; then \
		echo "Directory $(SAVED_STATE_DIR) does not exist. Nothing to clean."; \
		exit 0; \
	fi
	@echo "WARNING: This will permanently delete all data in $(SAVED_STATE_DIR)"
	@echo "Directory: $(SAVED_STATE_DIR)"
	@read -r -p "Are you sure you want to continue? [y/N] " answer && \
	case "$$answer" in \
		[yY]) echo "Proceeding with deletion...";; \
		*) echo "Operation cancelled."; exit 0;; \
	esac
	@if [ -d "$(SAVED_STATE_DIR)/volDB" ]; then \
		echo "Removing volDB..."; \
		podman unshare rm -rf $(SAVED_STATE_DIR)/volDB 2>/dev/null || \
		sudo rm -rf $(SAVED_STATE_DIR)/volDB 2>/dev/null || \
		{ echo "Cannot remove volDB. Use: sudo rm -rf $(SAVED_STATE_DIR)/volDB"; exit 1; }; \
	fi
	@if [ -d "$(SAVED_STATE_DIR)/volExport" ]; then \
		echo "Removing volExport..."; \
		podman unshare rm -rf $(SAVED_STATE_DIR)/volExport 2>/dev/null || \
		sudo rm -rf $(SAVED_STATE_DIR)/volExport 2>/dev/null || \
		{ echo "Cannot remove volExport. Use: sudo rm -rf $(SAVED_STATE_DIR)/volExport"; exit 1; }; \
	fi
	@if [ -d "$(SAVED_STATE_DIR)/volStarexec" ]; then \
		echo "Removing volStarexec..."; \
		podman unshare rm -rf $(SAVED_STATE_DIR)/volStarexec 2>/dev/null || \
		sudo rm -rf $(SAVED_STATE_DIR)/volStarexec 2>/dev/null || \
		{ echo "Cannot remove volStarexec. Use: sudo rm -rf $(SAVED_STATE_DIR)/volStarexec"; exit 1; }; \
	fi
	@podman unshare rm -rf $(SAVED_STATE_DIR) 2>/dev/null || sudo rm -rf $(SAVED_STATE_DIR) 2>/dev/null || true
	@echo "Volumes removed successfully."

connect: ## Connect to the running StarExec container via bash shell
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -n "$$container_id" ]; then \
		podman exec -it $$container_id /bin/bash; \
		exit 0; \
	else \
		echo "Error: No running StarExec container found."; \
		exit 1; \
	fi

push: ## Push the StarExec image to a container registry
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

microk8s-import: ## Import the StarExec image into MicroK8s registry
	@echo "Importing starexec:${VERSION} image into MicroK8s..."
	@podman save localhost:32000/starexec:${VERSION} -o starexec-image.tar
	@microk8s ctr image import starexec-image.tar
	@rm starexec-image.tar
	@echo "Image imported into MicroK8s successfully."

list-microk8s: ## List StarExec images in the MicroK8s registry
	@echo "Listing images in MicroK8s registry..."
	@microk8s ctr images list | grep starexec
	@echo "Listing images in MicroK8s registry done."

state-init: ## Initialize local state folders and prepare DB/export for sharing
	@echo "Initializing persistent state in $(SAVED_STATE_DIR)..."
	@$(MAKE) .state-mkdirs
	@echo "Fixing ownership for rootless Podman..."
	@$(MAKE) .state-chown-container
	@chmod 775 $(SAVED_STATE_DIR)/volDB 2>/dev/null || true
	@chmod -R 775 $(SAVED_STATE_DIR)/volExport 2>/dev/null || true
	@chmod -R 775 $(SAVED_STATE_DIR)/volStarexec 2>/dev/null || true
	@# Check if database is already initialized by looking for key MariaDB files
	@if $(DB_INIT_TEST); then \
		echo "No existing database found. Creating new state..."; \
		$(MAKE) state-create; \
	else \
		echo "Database already exists in $(SAVED_STATE_DIR). Using existing state."; \
		echo "To create a fresh state, use: make state-create"; \
		echo "To restore from a tgz, use: make state-restore FILE=path.tgz"; \
	fi
	@echo "State initialization complete."

state-create: ## Force creation of a new database state
	@echo "Creating new database state in $(SAVED_STATE_DIR)..."
	@$(MAKE) .state-mkdirs
	@if ! podman image exists starexec:${VERSION}; then \
		echo "Image starexec:${VERSION} not found locally. Pulling..."; \
		$(MAKE) pull; \
	fi
	@echo "Removing existing database data..."
	@podman unshare rm -rf $(SAVED_STATE_DIR)/volDB/* 2>/dev/null || true
	@echo "Running database initialization..."
	@podman run --rm \
		--user 0 \
		--tmpfs /var/run/mysqld:rw,size=128m,mode=775 \
		-v $(SAVED_STATE_DIR)/volDB:/var/lib/mysql:U \
		starexec:${VERSION} bash -c '\
			chown -R mysql:mysql /var/lib/mysql && \
			mysql_install_db --user=mysql --datadir=/var/lib/mysql --basedir=/usr --force && \
			chown -R mysql:mysql /var/lib/mysql && \
			chmod -R 755 /var/lib/mysql && \
			find /var/lib/mysql -type d -exec chmod 755 {} \; && \
			find /var/lib/mysql -type f -exec chmod 644 {} \; \
		'
	@echo "Fixing final ownership after initialization..."
	@$(MAKE) .state-chown-container
	@if [ ! -d "$(SAVED_STATE_DIR)/volDB/mysql" ] || [ ! -f "$(SAVED_STATE_DIR)/volDB/ibdata1" ]; then \
		echo "ERROR: Database initialization failed!"; \
		exit 1; \
	fi
	@echo "New database state created successfully."

state-restore: ## Restore state from a .tgz file (use: make state-restore FILE=the.tgz SAVED_STATE_DIR=target_location)
	@if [ -z "$$FILE" ]; then \
		echo "Usage: make state-restore FILE=/path/to/starexec-state-*.tgz [SAVED_STATE_DIR=target_location]"; \
		echo "Example: make state-restore FILE=shared-state.tgz SAVED_STATE_DIR=starexec_restored_state"; \
		exit 1; \
	fi
	@if [ ! -f "$$FILE" ]; then \
		echo "Error: File $$FILE not found."; \
		exit 1; \
	fi
	@echo "Restoring state from $$FILE to $(SAVED_STATE_DIR)..."
	@if [ -d "$(SAVED_STATE_DIR)" ]; then \
		echo "WARNING: Target directory $(SAVED_STATE_DIR) already exists."; \
		read -r -p "Do you want to overwrite it? [y/N] " answer && \
		case "$$answer" in \
			[yY]) echo "Removing existing directory..."; \
				  podman unshare rm -rf $(SAVED_STATE_DIR) 2>/dev/null || \
				  sudo rm -rf $(SAVED_STATE_DIR) 2>/dev/null || \
				  { echo "Cannot remove existing directory. Use: sudo rm -rf $(SAVED_STATE_DIR)"; exit 1; };; \
			*) echo "Operation cancelled."; exit 1;; \
		esac; \
	fi
	@echo "Extracting state archive..."
	@mkdir -p $$(dirname $(SAVED_STATE_DIR))
	@tar -C $$(dirname $(SAVED_STATE_DIR)) -xzf "$$FILE"
	@extracted_dir=$$(tar -tzf "$$FILE" | head -1 | cut -f1 -d"/"); \
	if [ "$$extracted_dir" != "$$(basename $(SAVED_STATE_DIR))" ]; then \
		echo "Renaming extracted directory $$extracted_dir to $$(basename $(SAVED_STATE_DIR))..."; \
		mv "$$(dirname $(SAVED_STATE_DIR))/$$extracted_dir" "$(SAVED_STATE_DIR)"; \
	fi
	@echo "Fixing ownership for restored state..."
	@$(MAKE) .state-fix-perms
	@chmod 775 $(SAVED_STATE_DIR)/volDB 2>/dev/null || true
	@chmod -R 775 $(SAVED_STATE_DIR)/volExport 2>/dev/null || true
	@chmod -R 775 $(SAVED_STATE_DIR)/volStarexec 2>/dev/null || true
	@chmod 775 $(SAVED_STATE_DIR)/volDB 2>/dev/null || true
	@chmod -R 775 $(SAVED_STATE_DIR)/volExport 2>/dev/null || true
	@chmod -R 775 $(SAVED_STATE_DIR)/volStarexec 2>/dev/null || true
	@echo "State restored successfully to $(SAVED_STATE_DIR)"
	@echo "You can now start with: make start SAVED_STATE_DIR=$(SAVED_STATE_DIR)"

state-pack: ## Create a tgz with the current backup state to share
	@echo "Packing $(SAVED_STATE_DIR) into a tgz..."
	@if [ ! -d "$(SAVED_STATE_DIR)" ]; then \
		echo "Error: Directory $(SAVED_STATE_DIR) does not exist."; \
		echo "Create a state first with: make start"; \
		exit 1; \
	fi
	@ts=$$(date +%Y%m%d_%H%M%S); \
	out="starexec-saved-state-$$ts.tgz"; \
	echo "Creating archive: $$out"; \
	podman unshare tar -C $$(dirname $(SAVED_STATE_DIR)) -czf "$$out" $(notdir $(SAVED_STATE_DIR)); \
	if [ $$? -eq 0 ]; then \
		echo "Created: $$out"; \
		echo "Restore the state with: make state-restore FILE=$$out SAVED_STATE_DIR=target_location"; \
	else \
		echo "Error: Failed to create archive."; \
		exit 1; \
	fi

state-unpack: ## Unpack a state tgz into current project (DEPRECATED - use state-restore)
	@echo "WARNING: state-unpack is deprecated. Use 'make state-restore' instead."
	@echo "Usage: make state-restore FILE=/path/to/starexec-state-*.tgz SAVED_STATE_DIR=target_directory"
	@if [ -n "$$FILE" ]; then \
		echo "Calling state-restore with your parameters..."; \
		$(MAKE) state-restore FILE="$$FILE"; \
	fi

state-fix-perms: ## Fix ownership of SAVED_STATE_DIR to current user
	@echo "Reclaiming ownership of $(SAVED_STATE_DIR) to host user $(USER)..."
	@if [ -d "$(SAVED_STATE_DIR)" ]; then \
		podman unshare chown -R $(shell id -u):$(shell id -g) $(SAVED_STATE_DIR) 2>/dev/null || \
		sudo chown -R $(USER):$(USER) $(SAVED_STATE_DIR) 2>/dev/null || \
		{ echo "Cannot fix ownership. Please run: sudo chown -R $(USER):$(USER) $(SAVED_STATE_DIR)"; exit 1; }; \
		echo "Ownership fixed. You can now: rm -rf $(SAVED_STATE_DIR) (or use: make state-delete)"; \
	else \
		echo "Directory $(SAVED_STATE_DIR) does not exist."; \
	fi

help: ## Display help for Makefile targets
	@echo "Makefile Commands:"
	@echo "------------------"
	@grep -E '^[a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "  %-20s %s\n", $$1, $$2}' | \
		sort
	@echo "------------------"
	@echo "Usage: make [target]"
	@echo "Example: make start"
	@echo ""
	@echo "State Management Workflow:"
	@echo "  1. Create new state:     make start"
	@echo "  2. Pack for sharing:     make state-pack"
	@echo "  3. Restore shared state: make state-restore FILE=archive.tgz SAVED_STATE_DIR=my_backup"
	@echo "  4. Use restored state:   make start SAVED_STATE_DIR=my_backup"
	@echo ""


# Prevent echoing of commands unless VERBOSE=true
# ifndef VERBOSE
# .SILENT:
# endif

# Ensure CURDIR is set correctly
ifeq ($(origin CURDIR), undefined)
	CURDIR := $(shell pwd)
endif
