# StarExec Containerized

- `dockerPackage` contains shell scripts used by the Dockerfile for building the application image.
- `dockerPackage/configFiles` contains network configuration files.
- `dockerPackage/allScripts/starexecScripts/overridesproperties.txt` contains StarExec configuration files.

### Build the Image
1. Ensure you have Podman installed, as explained [here](../README.md).
2. Ensure that `$HOME/.ssh` exists and you have read-write permission.
3. Ensure that the `sshd` daemon is running with `systemctl status sshd.service`.
   - If necessary start it with `sudo service sshd restart`.
   - On Fedora, this step needs to be done before every new start of StarExec.
4. Run `make` (refer to the `Makefile` for details).
   - This step typically needs to be done only once.

### Run the Image
1. Configure port 80 for non-root usage:
  - **Mac**: To Be Announced (TBA).
  - **Ubuntu**:
    - Add `net.ipv4.ip_unprivileged_port_start=80` to `/etc/sysctl.conf`.
    - Execute `sudo sysctl --system` to reload the configuration.
  - **Fedora**:
    - Add `net.ipv4.ip_unprivileged_port_start=80` to a file in
      `/etc/sysctl.d` directory, e.g., create a file
      `/etc/sysctl.d/80-override.conf` with that line.
    - Execute `sudo sysctl --system` to reload the configuration.
      On Fedora, this must be done before every `make run`.
2. Run `make run` (refer to the `Makefile` for details).

### Accessing StarExec
- Navigate to [https://localhost](https://localhost).
  - The interface may take about a minute to become available as the StarExec `tomcat` app redeploys on each restart.
- For remote server access, use:
  `ssh -f -N -L 8080:starexec_server.domain:80 your_account@starexec_server.domain`
  - If necessary, add jump host options, ala `-J your_account@jumphost.domain`
- Default Username: `admin`  
  Default Password: `admin`

### Debugging
- Run `make connect` to open a bash shell within the container.

### Managing the Image
- **Kill the Running Image**:
  - Execute `make kill` if you need to stop the running image.
- **Destroy the Image**:
  - If you encounter issues and wish to remove all configurations, execute:
   ```bash
   make clean
   make cleanVolumes
   ```
  - _Note_: This will erase all state, and you will need to rebuild the container.

## How It Works

The local backend in StarExec executes `run_image.py` with specific arguments to run a prover container on the host.

- **Containerized StarExec** is designed to support:
  - Local execution of a prover.
  - Execution of a proxy prover via Podman or Kubernetes.
- **Proxy Prover for Podman**:
  - Containerized StarExec detects `run_image.py` script.
  - It utilizes Podman to run the container.
- **Proxy Prover for Kubernetes**:
  - Containerized StarExec detects `run_image_k8s.py` script.
  - It uses `kubectl` to manage the container within Kubernetes.
- **Non-Proxy Prover**:
  - If neither script is present, it's treated as a regular StarExec `.tgz` package.
  - Containerized StarExec utilizes `runsolver` to execute the prover.
