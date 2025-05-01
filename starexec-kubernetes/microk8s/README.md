# Using MicroK8s to Deploy StarExec Head Node

This document describes how to deploy a StarExec head node using MicroK8s, configured with a local backend for job execution via Podman over SSH.

## Prerequisites

* MicroK8s installed and running.
* `kubectl` configured to interact with your MicroK8s cluster (usually aliased via `microk8s kubectl`).
* SSH client available on the machine where you run `make apply`.
* Podman installed and running on the host machine.
* **SSH Access Configuration:** The StarExec container needs to SSH into the host machine to interact with Podman. The Makefile attempts to configure this automatically:
  * **SSH User:** By default, it uses your current logged-in user (`$USER`). You can override this by setting the `STAREXEC_SSH_USER` environment variable before running `make` (e.g., `export STAREXEC_SSH_USER=myuser`).
  * **SSH Key:** `make apply` generates an SSH key pair (`starexec-ssh-key`, `starexec-ssh-key.pub`) in the current directory and configures it as a Kubernetes secret for the pod. You might need to ensure the public key (`starexec-ssh-key.pub`) is added to the target user's `~/.ssh/authorized_keys` file on the host machine for passwordless SSH access.
  * **Podman Socket:** The Makefile attempts to detect the Podman socket path based on your user ID (e.g., `/run/user/1000/podman/podman.sock`). If your setup differs, you might need to adjust the `SSH_SOCKET_PATH` variable in the Makefile or override it via an environment variable.

## Makefile Targets

The following targets are available in the `Makefile`:

* `make help`
  * Displays a summary of all available Makefile targets and their descriptions.

* `make apply`
  * Ensures the MicroK8s ingress addon is enabled.
  * Applies all Kubernetes resource definitions located in the `YAMLFiles` directory.
  * Ensures an SSH key pair (`starexec-ssh-key`, `starexec-ssh-key.pub`) exists (generates if not).
  * Creates/updates Kubernetes secrets (`starexec-ssh-key`, `starexec-ssh-key-pub`) from the key pair.
  * Ensures TLS certificate and secret (`starexec-tls-secret`) exist using `mkcert` (runs `make mkcert-setup`).
  * Displays instructions on how to access the deployed StarExec service.

* `make start`
  * Deploys the application using `make apply`.
  * Waits for the StarExec pod to become ready.
  * If a state backup exists in `./state-backup`, restores it using `make restore-state`.

* `make stop`
  * Backs up the current application state using `make backup-state`.
  * Removes all deployed application resources using `make clean`.

* `make clean`
  * Deletes all Kubernetes resources defined in the `YAMLFiles` directory.
  * Deletes the Kubernetes secrets created for SSH keys and TLS certificates.
  * Removes the generated SSH key pair files and TLS certificate files from the local directory.

* `make connect`
  * Opens an interactive bash shell inside the running StarExec pod. Useful for debugging.

* `make backup-state`
  * Backs up specified application state directories (`/var/lib/mysql`, `/home/starexec`) from the running pod to the local `./state-backup` directory.

* `make restore-state`
  * Restores application state from the local `./state-backup` directory to the running pod.
  * Attempts to gracefully restart MySQL, Apache, and Tomcat services within the pod after restoring data.

* `make check-health`
  * Performs basic health checks on the running application pod, including checking process status (Tomcat, Apache), testing HTTPS endpoints, and showing recent logs.

* `make describe-pod`
  * Shows detailed information (`kubectl describe pod`) about the running StarExec pod.

* `make check-volumes`
  * Displays information about Persistent Volume Claims (PVCs), Persistent Volumes (PVs), and Storage Classes related to the application.

* `make info`
  * Displays a summary of all Kubernetes resources in the application's namespace (`default`).

* `make list-pods`
  * Lists all pods in the application's namespace.

* `make list-services`
  * Lists all services in the application's namespace.

* `make list-deployments`
  * Lists all deployments in the application's namespace.

* `make list-nodes`
  * Lists all nodes in the MicroK8s cluster.

* `make ssh-setup`
  * Generates an SSH key pair (`starexec-ssh-key`, `starexec-ssh-key.pub`) in the current directory if it doesn't already exist.

* `make mkcert-setup`
  * Checks if `mkcert` is installed.
  * Installs the local `mkcert` CA if needed.
  * Generates a TLS certificate (`starexec-tls.crt`, `starexec-tls.key`) for specified hosts (default: localhost).
  * Creates/updates the Kubernetes TLS secret (`starexec-tls-secret`).

* `make cert-refresh`
  * Regenerates the TLS certificate using `mkcert`.
  * Updates the Kubernetes TLS secret (`starexec-tls-secret`).

* `make mkcert-clean`
  * Removes the locally generated TLS certificate files (`starexec-tls.crt`, `starexec-tls.key`).
  * Deletes the Kubernetes TLS secret (`starexec-tls-secret`).
