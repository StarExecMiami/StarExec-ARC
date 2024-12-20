# StarExec Containerized

* `dockerPackage` contains shell scripts used by the dockerfile for building the app image.
* `dockerPackage/configFiles` contains configuration files for 
* `dockerPackage/allScripts/starexecScripts/overridesproperties.txt` contains configuration files
   for StarExec.

Make sure you have podman installed.

## Build the image 
* `make` (see the `Makefile` for details)
* You should have to do this only once.

## Run the image 
* `make run` (see Makefile for details).
  You must be able to use port 80 without sudo/root:
  - On a Mac: TBA.
  - In Ubuntu, add "net.ipv4.ip_unprivileged_port_start=80" to `/etc/sysctl.conf` outside the 
    container)

## Login at https://localhost
The interface may take about a minute to become stable because the StarExec tomcat app is 
redeployed on every restart.

Default username: **admin**<br>
Default password: **admin**

## Kill the container 
* `make kill`

## For debugging 
* `make connect` (runs a bash shell in the container)

If you are having trouble, but aren't afraid of erasing any state you've set up, you can 
`make clean` and `make cleanVolumes` to totally remove everything - you have to rebuild the
container.

# Here's how the magic works

The local backend in StarExec runs `run_image.py` with special args to run a prover container 
in the host.

* Containerised StarExec is built to support local execution of a prover, and also execution 
  of a proxy-prover directly in podman or via Kubernetes.
* If the proxy prover is built for podman then containerised StarExec sees the 
  `run_image.py` script.
  Containerised StarExec then runs podman to run the container.
* If the proxy prover is built for Kubernetes then containerised StarExec sees the 
  `run_image_k8s.py` script.
  Containerised StarExec then runs kubectl to run the container in Kubernetes.
* If neither script is there then it's not a proxy prover (just a regular StarExec `.tgz`).
  Containerised StarExec then runs `runsolver` to run the prover.

