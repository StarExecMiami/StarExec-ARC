SHELL := /bin/bash

.PHONY: all starexec clean cleanVolumes connect
all: starexec

starexec:
	podman build -t starexec . --ulimit="nofile=100000:100000"

run:
	podman run -it -v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volSandbox:/home/sandbox \
			-p 80:80 -p 443:443 starexec

clean:
	podman rmi -f starexec
	#podman rm -f $(podman ps -a -q --filter ancestor=starexec)

cleanVolumes:
	podman volume rm -f volDB volStar volPro volSandbox


# Assumes you only have one running container and it's starexec...
connect:
	podman exec -it $(shell podman container ls --format "{{.ID}}" | head -n 1) bash



