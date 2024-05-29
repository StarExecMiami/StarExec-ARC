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

# kills the container only.
kill:
	podman rm -f `podman ps -a -q --filter ancestor=starexec`


cleanVolumes:
	podman volume rm -f volDB volStar volPro volSandbox


connect:
	podman exec -it `podman ps -a -q --filter ancestor=starexec` bash



