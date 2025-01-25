SHELL := /bin/bash

USER=$(shell whoami)
PODMAN_SOCKET_PATH="/run/user/1000/podman/podman.sock"

.PHONY: all starexec clean cleanVolumes connect
all: starexec

starexec:
	echo "using ssh-keygen to make pub/priv keys in the current directory"; \
	echo "(only if they don't already exist)"; \
	[ -f starexec_podman_key ] || ssh-keygen -t ed25519 -N '' -f starexec_podman_key; \
	ssh-keyscan -H localhost >> ~/.ssh/known_hosts; \

	@if [ "$(USER)" != "jenkins" ]; then \
		echo "Setting up SSH key for $(USER) user."; \
		[ -f starexec_podman_key.pub ] && \
		ssh-copy-id -i starexec_podman_key.pub $(USER)@localhost; \
	else \
		echo "Skipping SSH key setup for Jenkins user."; \
	fi

	podman build --no-cache -t starexec . --ulimit="nofile=100000:100000"

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
	podman rmi -f `podman images -q --filter "dangling=true"`

# kills the container only.
kill:
	podman rm -f `podman ps -a -q --filter "ancestor=starexec"`

cleanVolumes:
	podman volume rm -f volDB volStar volPro volExport

connect:
	podman exec -it `podman ps -a -q --filter "ancestor=starexec"` /bin/bash

push:
	podman push starexec docker.io/tptpstarexec/starexec
