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
# Helper command to get any container (running or stopped) ID by name
GET_ANY_CONTAINER_ID_CMD = podman ps -a --filter name=$(CONTAINER_NAME) --format '{{.ID}}'

.PHONY: all local k8s starexec clean cleanVolumes connect start stop backup-state restore-state kill run ssh-setup mkcert-setup push microk8s-import list-microk8s microk8s-clean real-clean help

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
	# This target is for temporary runs. Use 'make start' for persistent runs with state.
	@podman run --rm -it --name $(CONTAINER_NAME) \
			--cap-add=NET_RAW \
			--network slirp4netns:allow_host_loopback=true \
			-v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-v $(HOME)/.local/share/mkcert/localhost.key:/etc/ssl/private/localhost.key \
			-v $(HOME)/.local/share/mkcert/localhost.crt:/etc/ssl/certs/localhost.crt \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=host.containers.internal \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			--healthcheck-interval=60s \
			--healthcheck-timeout=15s \
			--healthcheck-retries=5 \
			--healthcheck-start-period=180s \
			--healthcheck-command "bash -c 'mysqladmin ping -u root --silent --connect-timeout=5 && (service apache2 status | grep -q \"running\" || pgrep apache2 >/dev/null) && (ps -ef | grep -v grep | grep -q \"org.apache.catalina.startup.Bootstrap\" || pgrep -f catalina >/dev/null) && (curl -s -k --max-time 10 -I https://localhost:7827/starexec/ | grep -q \"200\\|302\\|301\" || curl -s -k --max-time 10 https://localhost:7827/ >/dev/null)'" \
			-p 7827:443 starexec:${VERSION}

start-container: ## Start the starexec container (internal use)
	@echo "Starting the starexec container persistently..."
	@container_id=$$($(GET_CONTAINER_ID_CMD)); \
	if [ -n "$$container_id" ]; then \
		echo "Container $(CONTAINER_NAME) is already running with ID: $$container_id"; \
		echo "Use 'make stop' to stop it first if you want to restart it."; \
		exit 0; \
	fi
	@# Check for stopped container with same name and remove it
	@stopped_container_id=$$($(GET_ANY_CONTAINER_ID_CMD)); \
	if [ -n "$$stopped_container_id" ]; then \
		echo "Found stopped container $(CONTAINER_NAME) with ID: $$stopped_container_id. Removing it..."; \
		podman rm $$stopped_container_id; \
	fi
	@echo "Launching container $(CONTAINER_NAME)..."
	@podman run -d --name $(CONTAINER_NAME) \
			--cap-add=NET_RAW \
			--network slirp4netns:allow_host_loopback=true \
			-v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-v $(HOME)/.local/share/mkcert/localhost.key:/etc/ssl/private/localhost.key \
			-v $(HOME)/.local/share/mkcert/localhost.crt:/etc/ssl/certs/localhost.crt \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=host.containers.internal \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			--healthcheck-interval=60s \
			--healthcheck-timeout=15s \
			--healthcheck-retries=5 \
			--healthcheck-start-period=180s \
			--healthcheck-command "bash -c 'mysqladmin ping -u root --silent --connect-timeout=5 && (service apache2 status | grep -q \"running\" || pgrep apache2 >/dev/null) && (ps -ef | grep -v grep | grep -q \"org.apache.catalina.startup.Bootstrap\" || pgrep -f catalina >/dev/null) && (curl -s -k --max-time 10 -I http://localhost/ | grep -q \"200\\|302\\|301\" || curl -s -k --max-time 10 http://localhost/ >/dev/null)'" \
			-p 7827:443 starexec:${VERSION}
	@echo "Waiting for container to initialize (approx 60 seconds)..."
	@sleep 60

start: ssh-setup mkcert-setup ## Start the starexec container with state restoration logic
	@echo "Starting StarExec with state restoration logic..."
	@# Step 1: Stop current container
	@$(MAKE) -s stop >/dev/null 2>&1 || true
	
	@# Step 2: Check for state-backup existence
	@if [ -d "$(BACKUP_DIR)" ] || [ -f "$(BACKUP_DIR)" ]; then \
		echo "State backup found. Restoring from $(BACKUP_DIR)..."; \
		$(MAKE) -s cleanVolumes >/dev/null 2>&1; \
		$(MAKE) -s start-container; \
		sleep 30; \
		$(MAKE) -s restore-state; \
	else \
		echo "No state backup found. Checking for existing container state..."; \
		if podman volume exists volDB >/dev/null 2>&1 && \
		   [ -n "$$(podman volume inspect volDB --format '{{.Mountpoint}}' 2>/dev/null | xargs ls -A 2>/dev/null)" ] || \
		   podman volume exists volStar >/dev/null 2>&1 && \
		   [ -n "$$(podman volume inspect volStar --format '{{.Mountpoint}}' 2>/dev/null | xargs ls -A 2>/dev/null)" ]; then \
			echo "Existing state found. Using current data..."; \
			$(MAKE) -s start-container; \
		else \
			echo "No existing state found. Starting clean..."; \
			$(MAKE) -s cleanVolumes >/dev/null 2>&1; \
			$(MAKE) -s start-container; \
		fi; \
	fi
	@echo "Startup process completed. Access at https://localhost:7827"
	@echo "Note: Container may show as 'unhealthy' initially while services fully initialize."
	@echo "Wait a few minutes and check with 'podman ps' - it should become healthy."

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
	
	# Create a mysqldump first (safer than stopping MySQL)
	echo "Creating MySQL dump for backup..."; \
	mkdir -p "$(BACKUP_DIR)/var/lib/mysql-dump"; \
	podman exec $$container_id /bin/bash -c "mysqldump --all-databases --single-transaction --quick > /tmp/all_databases.sql" || \
		echo "Warning: MySQL dump may not be complete. Will try direct file copy as well."; \
	podman cp $$container_id:/tmp/all_databases.sql "$(BACKUP_DIR)/var/lib/mysql-dump/" || \
		echo "Warning: MySQL dump copy failed. Proceeding with direct file backup."; \
	
	# Backup files one by one without stopping services
	for path in $(STATE_PATHS); do \
		target_dir="$(BACKUP_DIR)$${path}"; \
		echo "Backing up $$path to $${target_dir}..."; \
		mkdir -p "$${target_dir}"; \
		rm -rf "$${target_dir}"/*; \
		
		# Check if container is still running
		if ! podman inspect $$container_id >/dev/null 2>&1 || \
		   [ "$$(podman inspect --format '{{.State.Running}}' $$container_id 2>/dev/null)" != "true" ]; then \
			echo "Container is no longer running! Stopping backup process."; \
			break; \
		fi; \
		
		if [ "$$path" = "/var/lib/mysql" ]; then \
			echo "Using special handling for MySQL data directory..."; \
			# Copy MySQL files with rsync if available, otherwise use tar
			if podman exec $$container_id which rsync >/dev/null 2>&1; then \
				podman exec $$container_id rsync -a --exclude='*.sock' --exclude='performance_schema' \
					--exclude='lost+found' $$path/ /tmp/mysql_backup/ || true; \
				podman cp $$container_id:/tmp/mysql_backup/. "$${target_dir}/" || \
					echo "Warning: MySQL files backup via rsync failed"; \
			else \
				# Create archive with tar but exclude socket files
				podman exec $$container_id tar -C $$path -cf /tmp/mysql_backup.tar \
					--exclude='*.sock' --exclude='performance_schema' --exclude='lost+found' . || true; \
				podman cp $$container_id:/tmp/mysql_backup.tar "$${target_dir}.tar" && \
				mkdir -p "$${target_dir}" && \
				tar -xf "$${target_dir}.tar" -C "$${target_dir}" && \
				rm -f "$${target_dir}.tar" || \
					echo "Warning: MySQL files backup via tar failed"; \
			fi; \
		else \
			# For other directories, use same approach but check container state
			if podman exec $$container_id which rsync >/dev/null 2>&1; then \
				podman exec $$container_id rsync -a $$path/ /tmp/backup_$$(basename $$path)/ || true; \
				podman cp $$container_id:/tmp/backup_$$(basename $$path)/. "$${target_dir}/" || \
					echo "Warning: Files backup from $$path via rsync failed"; \
			else \
				# Create directory archive with tar
				podman exec $$container_id bash -c "cd $$path && tar cf /tmp/backup_$$(basename $$path).tar . || true"; \
				podman cp $$container_id:/tmp/backup_$$(basename $$path).tar "$${target_dir}.tar" && \
				mkdir -p "$${target_dir}" && \
				tar -xf "$${target_dir}.tar" -C "$${target_dir}" && \
				rm -f "$${target_dir}.tar" || \
					echo "Warning: Files backup from $$path via tar failed"; \
			fi; \
		fi; \
	done

	# No need to restart MySQL as we didn't stop it
	# Just check if container is still running at the end
	if podman inspect $$container_id >/dev/null 2>&1 && \
	   [ "$$(podman inspect --format '{{.State.Running}}' $$container_id 2>/dev/null)" = "true" ]; then \
		echo "Container is still running. Backup completed."; \
	else \
		echo "Note: Container exited during backup process."; \
	fi
	
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
		service mysql stop || service mariadb stop || true" || true
	@sleep 5
	
	# Check if container is still running after stopping services
	@if ! podman inspect $$container_id >/dev/null 2>&1 || \
	   [ "$$(podman inspect --format '{{.State.Running}}' $$container_id 2>/dev/null)" != "true" ]; then \
		echo "Container stopped during service shutdown. Restarting container..."; \
		podman start $$container_id; \
		sleep 10; \
	fi
	
	# Restore non-MySQL files first
	@for path in $(STATE_PATHS); do \
		if [ "$$path" = "/var/lib/mysql" ]; then \
			continue; \
		fi; \
		source_dir="$(BACKUP_DIR)$${path}"; \
		if [ ! -d "$$source_dir" ]; then \
			echo "Warning: Backup source '$$source_dir' missing. Skipping $$path."; \
			continue; \
		fi; \
		\
		# Check container is running before each restore operation \
		if ! podman inspect $$container_id >/dev/null 2>&1 || \
		   [ "$$(podman inspect --format '{{.State.Running}}' $$container_id 2>/dev/null)" != "true" ]; then \
			echo "Container not running. Restarting..."; \
			podman start $$container_id; \
			sleep 10; \
		fi; \
		\
		echo "Restoring $$path from $$source_dir..."; \
		if tar cf - -C "$$source_dir" . | podman exec -i $$container_id tar xf - -C "$$path" 2>/dev/null; then \
			echo "Successfully restored $$path using tar"; \
		else \
			echo "Error restoring $$path using tar. Trying alternative method..."; \
			# Check container is still running after tar failure \
			if ! podman inspect $$container_id >/dev/null 2>&1 || \
			   [ "$$(podman inspect --format '{{.State.Running}}' $$container_id 2>/dev/null)" != "true" ]; then \
				echo "Container stopped during tar operation. Restarting..."; \
				podman start $$container_id; \
				sleep 10; \
			fi; \
			\
			if podman exec $$container_id rm -rf "$$path"/* 2>/dev/null; then \
				echo "Cleared target directory $$path"; \
			fi; \
			\
			if podman cp "$$source_dir/." $$container_id:"$$path/" 2>/dev/null; then \
				echo "Successfully restored $$path using podman cp"; \
			else \
				echo "Warning: Could not restore $$path completely"; \
			fi; \
		fi; \
	done
	
	# Start MySQL service and restore data
	@echo "Starting MySQL service and restoring data..."
	@if ! podman inspect $$container_id >/dev/null 2>&1 || \
	   [ "$$(podman inspect --format '{{.State.Running}}' $$container_id 2>/dev/null)" != "true" ]; then \
		echo "Container not running. Restarting..."; \
		podman start $$container_id; \
		sleep 15; \
	fi
	@podman exec $$container_id /bin/bash -c '\
		echo "Ensuring MySQL/MariaDB service is running..."; \
		if ! mysqladmin ping --silent --connect-timeout=5 2>/dev/null; then \
			echo "MySQL not running. Attempting to start..."; \
			service mariadb start || service mysql start || true; \
			for i in $$(seq 1 15); do \
				if mysqladmin ping --silent --connect-timeout=2 2>/dev/null; then \
					echo "MySQL started successfully."; \
					break; \
				fi; \
				sleep 2; \
			done; \
		fi; \
		if ! mysqladmin ping --silent --connect-timeout=5 2>/dev/null; then \
			echo "Error: MySQL failed to start. Cannot restore database."; \
			exit 1; \
		fi'
	# Restore MySQL database from dump first, as it's the most reliable method
	@if [ -f "$(BACKUP_DIR)/var/lib/mysql-dump/all_databases.sql" ]; then \
		echo "Restoring MySQL database from dump..."; \
		if podman cp "$(BACKUP_DIR)/var/lib/mysql-dump/all_databases.sql" $$container_id:/tmp/restore_dump.sql; then \
			podman exec $$container_id /bin/bash -c '\
				echo "Importing SQL dump..."; \
				mysql < /tmp/restore_dump.sql || echo "Warning: SQL dump import may have had errors."; \
				rm -f /tmp/restore_dump.sql'; \
		else \
			echo "Warning: Failed to copy SQL dump to container. Will try file-based restore."; \
		fi; \
	else \
		echo "No MySQL dump found. Proceeding with file-based restore of /var/lib/mysql."; \
		source_dir="$(BACKUP_DIR)/var/lib/mysql"; \
		if [ -d "$$source_dir" ]; then \
			echo "Restoring /var/lib/mysql from $$source_dir..."; \
			podman exec $$container_id /bin/bash -c "service mariadb stop || service mysql stop || true"; \
			sleep 5; \
			if tar cf - -C "$$source_dir" . | podman exec -i $$container_id tar xf - -C "/var/lib/mysql"; then \
				echo "Successfully restored /var/lib/mysql files."; \
			else \
				echo "Warning: Failed to restore /var/lib/mysql files via tar."; \
			fi; \
			podman exec $$container_id /bin/bash -c "chown -R mysql:mysql /var/lib/mysql; service mariadb start || service mysql start || true"; \
			sleep 10; \
		else \
			echo "Warning: No backup files found for /var/lib/mysql."; \
		fi; \
	fi
	
	# Start remaining services
	@echo "Starting Apache and Tomcat..."
	@if ! podman inspect $$container_id >/dev/null 2>&1 || \
	   [ "$$(podman inspect --format '{{.State.Running}}' $$container_id 2>/dev/null)" != "true" ]; then \
		echo "Container not running. Restarting for service startup..."; \
		podman start $$container_id; \
		sleep 10; \
	fi
	@podman exec $$container_id /bin/bash -c '\
		echo "Starting Apache and Tomcat..."; \
		if command -v systemctl >/dev/null 2>&1; then \
			systemctl start apache2 || systemctl start httpd || true; \
		else \
			service apache2 start || apache2ctl -k start || true; \
		fi; \
		sleep 3; \
		if [ -f /project/apache-tomcat-7/bin/startup.sh ]; then \
			/project/apache-tomcat-7/bin/startup.sh || true; \
		fi; \
		echo "Services startup completed."' 2>/dev/null || { echo "Warning: Some services may not have started properly."; }
	@echo "State restore completed."
	@echo "Note: Container may take a few more minutes to become fully healthy."

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

cleanVolumes: ## Remove starexec related volumes (WARNING: data loss)
	@echo "Removing volumes: volDB, volStar, volPro, volExport"
	@podman volume rm -f volDB volStar volPro volExport

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