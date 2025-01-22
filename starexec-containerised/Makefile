SHELL := /bin/bash

USER=$(shell whoami)
PODMAN_SOCKET_PATH="/run/user/1000/podman/podman.sock"
VERSION ?= latest

.PHONY: all starexec clean cleanVolumes connect
all: starexec

starexec:
	@if [ ! -f .env ]; then \
			echo "Error: .env file not found. Please create it with required credentials."; \
			echo "Example contents:"; \
			echo "DB_USER=se_admin"; \
			echo "DB_PASS=your_password_here"; \
			exit 1; \
	fi

	@if [ "$(USER)" != "jenkins" ]; then \
		echo "using ssh-keygen to make pub/priv keys in the current directory"; \
		echo "(only if they don't already exist)"; \
		[ -f starexec_podman_key ] || ssh-keygen -t ed25519 -N '' -f starexec_podman_key; \
		ssh-keyscan -H localhost >> ~/.ssh/known_hosts; \
		ssh-copy-id -i starexec_podman_key.pub ${USER}@localhost; \
	else \
		echo "Skipping SSH key setup for Jenkins user."; \
	fi

	VERSION=${VERSION} && \
	START_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build started at: $$START_TIME" | tee build-$$VERSION.log && \
	time podman build \
			--build-arg DB_USER=$$(grep DB_USER .env | cut -d '=' -f2) \
			--build-arg DB_PASS=$$(grep DB_PASS .env | cut -d '=' -f2) \
			-t starexec:$$VERSION . \
			--no-cache \
			--ulimit="nofile=100000:100000" 2> >(tee -a build-$$VERSION.log >&2) && \
	END_TIME=$$(date +%Y-%m-%d\ %H:%M:%S) && echo "Build finished at: $$END_TIME" | tee -a build-$$VERSION.log && \
	echo "Build duration: $$(date -u -d @$$(( $$(date -d "$$END_TIME" +%s) - $$(date -d "$$START_TIME" +%s) )) +%H:%M:%S)" | tee -a build-$$VERSION.log

run:
	podman run --network=host --rm -it -v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volExport:/export \
			-v ./starexec_podman_key:/root/.ssh/starexec_podman_key \
			-e SSH_USERNAME=${USER} \
			-e HOST_MACHINE=localhost \
			-e SSH_PORT=22 \
			-e SSH_SOCKET_PATH=${PODMAN_SOCKET_PATH} \
			-p 80:80 -p 443:443 starexec

	# ${SSH_USERNAME}@${HOST_MACHINE}:${SSH_PORT}${SOCKET_PATH}
clean:
	podman rmi -f starexec

	# Also clear cached parts of the image:
	podman rmi -f `podman images -q --filter ancestor=starexec`

# kills the container only.
kill:
	podman rm -f `podman ps -a -q --filter ancestor=starexec`

cleanVolumes:
	podman volume rm -f volDB volStar volPro volExport

connect:
	podman exec -it `podman ps -a -q --filter ancestor=starexec` bash

push:
	podman push starexec docker.io/tptpstarexec/starexec
