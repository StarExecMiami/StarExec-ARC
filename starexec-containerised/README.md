STAREXEC DOCKER

Directory "bashS" contains all the bash scripts for the dependencies and building the app

deploy.sh runs at docker build time and is responsible for building the app
start.sh runs at docker run time and is responsible for soft-deploy of app to tomcat

To run, first make sure you have docker installed on your system.

In the CLI, first navigate to the cloned starexec-docker folder.
Start the docker daemon and then type in:

	"podman build -t starexec . "

This will build the image from the Dockerfile.

Make sure that you can use port 80 without sudo/root.
(On linux, add "net.ipv4.ip_unprivileged_port_start=80" to `/etc/sysctl.conf`)

Once done, type in:

	"podman run -it -v volDB:/var/lib/mysql \
			-v volStar:/home/starexec \
			-v volPro:/project \
			-v volSandbox:/home/sandbox \
			-p 80:80 -p 443:443 starexec "

In your browser, visit http://localhost/starexec

Default username: admin
Default password: admin

On Geoff's Mac:
---------------
# Running StarExec in Podman
cd starexec-docker
# If VM not running ...
podman machine start
# One time ... 
podman build -t starexec .
# Every time
podman run -it -v volDB:/var/lib/mysql -v volStar:/home/starexec -v volPro:/project -v volSandbox:/home/sandbox -p 8080:8080 starexec
# -p 80:80 -p 443:443 gives an error that I still have to fix

