# Using MicroK8s to Deploy StarExec Head Node

This document describes how to deploy a StarExec head node using MicroK8s, configured with a local backend for job execution via Podman over SSH.

## Prerequisites

* MicroK8s installed and running.
* `kubectl` configured to interact with your MicroK8s cluster (usually aliased via `microk8s kubectl`).
* SSH client available on the machine where you run `make apply`.
* Podman installed and configured for SSH access on the target host machine specified in `YAMLFiles/config.yaml`.

## Makefile Targets

The following targets are available in the `Makefile`:

* `make apply`
  * Enables the MicroK8s ingress addon if not already enabled.
  * Applies all Kubernetes resource definitions located in the `YAMLFiles` directory (ConfigMap, ServiceAccount, Roles, RoleBinding, PersistentVolumes, PersistentVolumeClaims, Service, Deployment, Ingress).
  * Generates an SSH key pair (`starexec-ssh-key` and `starexec-ssh-key.pub`) if it doesn't exist in the current directory.
  * Creates Kubernetes secrets (`starexec-ssh-key` and `starexec-ssh-key-pub`) from the generated key pair. The private key is mounted into the StarExec pod to allow SSH connections to the host machine for Podman job execution. The public key might be needed for authorizing access on the host.
  * Displays instructions on how to access the deployed StarExec service (via ClusterIP or Port Forwarding).

* `make connect`
  * Opens an interactive bash shell inside the running StarExec pod. Useful for debugging.

* `make clean`
  * Deletes all Kubernetes resources defined in the `YAMLFiles` directory.
  * Deletes the Kubernetes secrets created for the SSH keys.
  * Removes the generated SSH key pair files from the local directory.

* `make info`
  * Displays a summary of all Kubernetes resources across all namespaces in the cluster.

* `make list-pods`
  * Lists all pods across all namespaces.

* `make list-services`
  * Lists all services across all namespaces.

* `make list-deployments`
  * Lists all deployments across all namespaces.

* `make list-nodes`
  * Lists all nodes in the cluster.

* `make cert-refresh`
  * Attempts to refresh MicroK8s internal certificates. This might be necessary if cluster communication issues arise due to expired certificates. It also displays the Subject Alternative Names (SANs) for the server certificate.
