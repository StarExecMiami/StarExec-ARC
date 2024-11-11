# StarExec Containerized

- `dockerPackage` contains a
bunch of shell scripts used by the dockerfile for building the app image.
Additionally some config can be found in here for instance in `dockerPackage/configFiles` and `dockerPackage/allScripts/starexecScripts/overridesproperties.txt`.


To run, first make sure you have podman (or maybe docker will still work) installed on your system.<br>
**__NOTE__: On a mac, you have to start a podman daemon using
`podman machine start` before using podman .

## 1. Building the Image - `make` (see Makefile for details)
You should only have to do this once.
## 2. Running the Image - `make run` (see Makefile for details)
For this to work, make sure that you can use port 80 without sudo/root.<br>
(On linux, add "net.ipv4.ip_unprivileged_port_start=80" to `/etc/sysctl.conf` outside the container)


### After `make run`, login at https://localhost
(The interface may take about a minute to become stable because
the starexec tomcat app is being redeployed on every restart.)

Default username: **admin**<br>
Default password: **admin**


## 3. For debugging - `make connect` (runs shell in the container)
If you are having trouble, but aren't afraid of erasing any state you've
set up, you can do `make clean` and `make cleanVolumes` to totally reset
and start over with step 1.

## 4. The container can be killed by running `make kill`

# Here's how the magic works
This is done by having the local backend in starexec run `run_image.py` with special args to 
run a prover container in the host.

- Containerised StarExec is built to support local execution of a prover, and also execution 
  of a proxy-prover directly in podman or via Kubernetes.
- If the proxy prover is built for podman then containerised StarExec sees the 
  `run_image.py` script.
  Containerised StarExec then runs podman to run the container.
- If the proxy prover is built for Kubernetes then containerised StarExec sees the 
  `run_image_k8s.py` script.
  Containerised StarExec then runs kubectl to run the container in Kubernetes.
- If neither script is there then it's not a proxy prover (just a regular StarExec `.tgz`).
  Containerised StarExec then runs `runsolver` to run the prover.

