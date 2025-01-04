# StarExec-ARC <BR>(Automated Reasoning Containerization)

This repository contains code for the containerization of Automated Theorem Proving (ATP) systems. It also includes deployment scripts for these ATP containers within a containerized StarExec environment, utilizing Podman or Kubernetes with MicroK8s or Amazon EKS. The following guide explains how to set up the system.

### Prerequisites for All Use Cases:
* **Install `podman`**: Follow the [installation guide](https://podman.io/docs/installation).
  - Ensure that you own `$HOME/.config` and you have read-write permission.
  - Check if you already have it installed with `podman --version`.
  - **macOS**: Run `brew install podman` and start the Podman daemon with `podman machine start`.
  - **Ubuntu**: Execute `sudo apt install podman` or `snap install podman --classic`.
  - **Fedora**: Execute `sudo dnf install podman`.
  - Verify installation with `podman --version`.
* **Containerize StarExec**: Navigate to the [`starexec-containerised`](starexec-containerised) directory.
  - Test the containerized StarExec using traditional StarExec `.tgz` ATP system packages.

### Building Containerized Proxy-Prover ATP Systems

Containerized proxy-prover ATP systems operate within a containerized StarExec on Kubernetes. They can also run directly within containerized StarExec.

* **Build Plain Containerized ATP Systems**: Necessary for proxy-prover ATP systems.
  - Navigate to the [`provers-containerised`](provers-containerised) directory and build the ATP systems.
* **Build Proxy-Prover ATP Systems**:
  - Access the [`starexec-proxy-provers`](starexec-proxy-provers) directory to build proxy-prover ATP systems.
  - Test the proxy-prover ATP systems using [containerized StarExec](starexec-containerised).

### Deploying StarExec on Kubernetes

* **Using EKS**:
  * **Install `kubectl`**:
    - **macOS**: Run `brew install kubectl`.
    - **Ubuntu**: Execute `snap install kubectl --classic`.
    - Verify installation with `kubectl version`.
* **Using MicroK8s**:
  * **Installation**:
    - **macOS**: MicroK8s is not natively supported. Install via a Multipass virtual machine as per the [MicroK8s macOS installation guide](https://microk8s.io/docs/install-macos).
    - **Ubuntu**:
      - Run `snap install microk8s --classic`.
      - Add your user to the `microk8s` group: `sudo usermod -aG microk8s $USER`.
      - Change ownership: `sudo chown -f -R $USER ~/.kube`.
      - Reload group memberships: `newgrp microk8s`.
      - Optionally, add `alias kubectl='microk8s kubectl'` to your shell configuration file.
  * **Verification**:
    - Check status with `microk8s status --wait-ready`.
    - List nodes using `microk8s kubectl get nodes`.
* **Deploy StarExec**:
  - Navigate to the [`starexec-kubernetes`](starexec-kubernetes) directory to deploy StarExec on MicroK8s or EKS.
  - Access the deployed StarExec website to upload your proxy-prover ATP systems and problem files.
    - **URL Access**:
      * **MicroK8s**: Run `microk8s kubectl get svc` to obtain the URL.
      * **EKS without Route53**: Execute `kubectl get svc` to get the URL.
      * **EKS with Route53**: The URL follows the format `https://your_Route53_domain`.
    - Open the URL in your browser to start using StarExec.

## Documentation

- [Workshop Paper on This Project](https://www.eprover.org/EVENTS/IWIL-2024/IWIL-24-Preproceedings.pdf)
- [ARA Proposal](https://www.amazon.science/research-awards/recipients/geoffrey-sutcliffe)

## Managing Podman/Docker Containers

**Building a Container Image:**
```shell
podman/docker build -t <TAG_NAME> <PATH_TO_DIRECTORY_WITH_DOCKERFILE>
```
**Running a Container (Entrypoint):**
```shell
podman/docker run --rm [--entrypoint <ENTRYPOINT_FILE>] <TAG_NAME> <ARGS>
```
**Running a Container (Interactive Shell):**
```shell
podman/docker run --rm -it <TAG_NAME>
```
**Cleanup (Podman):**
```shell
podman system prune --all --force && podman rmi --all
```
**Forced Cleanup (Podman):**
```shell
podman rmi --all --force
```
**Cleanup (Docker):**
```shell
docker system prune --all --force && docker rmi $(docker images -a -q)
```
