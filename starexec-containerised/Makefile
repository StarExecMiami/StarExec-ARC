SHELL := /bin/bash

USER=`whoami`
PODMAN_SOCKET_PATH="/run/user/1000/podman/podman.sock"

.PHONY: all starexec clean cleanVolumes connect
all: starexec

starexec:
	podman build -f Dockerfile -t starexec . --ulimit="nofile=100000:100000"

withPodman:
	echo "using ssh-keygen to make pub/priv keys in the current directory"
	echo "(only if they don't already exist)"
	[ -f starexec_podman_key ] || ssh-keygen -t ed25519 -N '' -f starexec_podman_key 

	# Make this key is trusted by the host.
	ssh-copy-id -i starexec_podman_key.pub ${USER}@localhost
	
	podman build -f Dockerfile_with_podman -t starexec . --ulimit="nofile=100000:100000" \
		--build-arg SSH_USERNAME=${USER} \
		--build-arg SOCKET_PATH=${PODMAN_SOCKET_PATH}

run:
	podman run --network=host -it -v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volExport:/export \
			-p 80:80 -p 443:443 starexec

clean:
	podman rmi -f starexec

# kills the container only.
kill:
	podman rm -f `podman ps -a -q --filter ancestor=starexec`

cleanVolumes:
	podman volume rm -f volDB volStar volPro volExport

connect:
	podman exec -it `podman ps -a -q --filter ancestor=starexec` bash



