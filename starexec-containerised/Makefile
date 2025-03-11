SHELL := /bin/bash

USER=$(shell whoami)
PODMAN_SOCKET_PATH="/run/user/1000/podman/podman.sock"
VERSION ?= latest

.PHONY: all starexec clean cleanVolumes connect
all: starexec

starexec:
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

	VERSION=${VERSION} && \
	START_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build started at: $$START_TIME" | tee build-$$VERSION.log && \
	time podman build \
			-t starexec:$$VERSION . \
			--no-cache \
			--ulimit="nofile=100000:100000" 2> >(tee -a build-$$VERSION.log >&2) && \
	END_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build finished at: $$END_TIME" | tee -a build-$$VERSION.log && \
	echo "Build duration: $$(date -u -d @$$(( $$(date -d "$$END_TIME" +%s) - $$(date -d "$$START_TIME" +%s) )) +%H:%M:%S)" | tee -a build-$$VERSION.log

run:
	podman run --rm -it -v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=localhost \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			-p 8443:443 starexec:${VERSION}

	# ${SSH_USERNAME}@${HOST_MACHINE}:${SSH_PORT}${SOCKET_PATH}

clean:
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

real-clean:
	@echo "WARNING: This will reset Podman and remove ALL containers, images, and volumes."
	@read -r -p "Are you sure you want to continue? [y/N] " answer && \
	case "$$answer" in \
		[yY]) echo "Resetting Podman..."; podman system reset -f;; \
		*) echo "Operation cancelled.";; \
	esac

kill:
	@echo "Killing container(s) running the 'starexec' image..."
	@container_ids="$$(podman ps -q --filter ancestor=starexec)"; \
	if [ -n "$$container_ids" ]; then \
		podman rm -f $$container_ids; \
	else \
		echo "No containers based on 'starexec' are running."; \
	fi

cleanVolumes:
	@echo "Removing volumes: volDB, volStar, volPro, volExport"
	@podman volume rm -f volDB volStar volPro volExport

connect:
	@container_id=$$(podman ps -q --filter name=starexec --format '{{.ID}}' | head -n 1); \
	if [ -n "$$container_id" ]; then \
		podman exec -it $$container_id /bin/bash; \
	else \
		echo "Error: No running StarExec container found."; \
		exit 1; \
	fi

push:
	@echo "Pushing starexec image to Docker Hub..."
	@podman login docker.io
	@podman push starexec docker.io/tptpstarexec/starexec
