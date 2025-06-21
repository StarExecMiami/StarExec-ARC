# StarExec-ARC <BR>(Automated Reasoning Containerization)

[![GitHub Stars](https://img.shields.io/github/stars/StarExecMiami/starexec-arc?style=social)](https://github.com/StarExecMiami/starexec-arc/stargazers)
[![GitHub Issues](https://img.shields.io/github/issues/StarExecMiami/starexec-arc)](https://github.com/StarExecMiami/starexec-arc/issues)
[![GitHub Last Commit](https://img.shields.io/github/last-commit/StarExecMiami/starexec-arc)](https://github.com/StarExecMiami/starexec-arc/commits/main)

[![Build Status: starexec-containerised](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-containerised.yaml/badge.svg?branch=master)](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-containerised.yaml)
[![Build Status: Makefile Build](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-containerized-makefile-build.yaml/badge.svg?branch=master)](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-containerized-makefile-build.yaml)
[![Build Status: Helm](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-helm.yaml/badge.svg?branch=master)](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-helm.yaml)
[![Build Status: Kubernetes](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-kubernetes.yaml/badge.svg?branch=master)](https://github.com/StarExecMiami/starexec-arc/actions/workflows/starexec-kubernetes.yaml)

[![Docker Pulls](https://img.shields.io/docker/pulls/tptpstarexec/starexec)](https://hub.docker.com/r/starexecmiami/starexec)
[![GitHub Container Registry](https://img.shields.io/badge/GHCR-latest-blue)](https://github.com/StarExecMiami/starexec-arc/pkgs/container/starexec-arc)

This repository contains code for the containerization of Automated Theorem Proving (ATP) systems.
It also includes deployment scripts for these ATP containers within a containerized StarExec
environment, utilizing Podman or Kubernetes with MicroK8s or Amazon EKS.
The following guide explains how to set up the system.

<!-- ------------------------------------------------------------------------------------------ -->
## Papers etc. (only background information and motivation)

- [Workshop Paper on This Project](https://www.eprover.org/EVENTS/IWIL-2024/IWIL-24-Preproceedings.pdf)
- [ARA Proposal](https://www.amazon.science/research-awards/recipients/geoffrey-sutcliffe)

<!-- ------------------------------------------------------------------------------------------ -->
## Building and Running a Containerised StarExec

### Prerequisites for All Use Cases

- **Install `podman`**: Follow the [installation guide](https://podman.io/docs/installation).
  - Ensure that you own `$HOME/.config` and you have read-write permission.
  - Check if you already have it installed with `podman --version`.
  - **macOS**: Run `brew install podman` and start the Podman daemon with `podman machine start`.
  - **Ubuntu**: Execute `sudo apt install podman` or `snap install podman --classic`.
  - **Fedora**: Execute `sudo dnf install podman`.
  - Verify installation with `podman --version`.
- **Containerize StarExec**:
  - Go to the [`starexec-containerised`](starexec-containerised) directory to build containerised
    StarExec.
  - Test the containerized StarExec using traditional StarExec `.tgz`/`.zip` packages.

<!-- ------------------------------------------------------------------------------------------ -->
### Building Containerized ATP Systems

There are three types of ATP system packages that can be used in various ways in containerized
StarExec:

- **Traditional StarExec `.tgz`/`.zip` packages**:
  - Can run in containerized StarExec
  - This works because:
    - The `.tgz`/`.zip` contains neither `run_image.py` nor `run_image_k8s.py`
    - StarExec uses the local backend to start `runsolver` in the traditional StarExec way.
  - Cannot (or at least hould not) be used in containerized StarExec that is deployed in
    Kubernetes (microk8s or AWS)
- **Containerized ATP Systems**:
  - Go to the [`provers-containerised`](provers-containerised) directory to build
    containerised ATP systems.
  - Test in a terminal containerised ATP systems using the `run_image.py` script.
  - Cannot (or should not) be used in containerised StarExec.
- **Proxy-Prover ATP Systems**:
  - Build a plain containerised ATP system first.
  - Go to the [`starexec-proxy-provers`](starexec-proxy-provers) directory to build _local_
    proxy-prover ATP systems for podman.
  - Test local proxy-prover ATP systems using [containerized StarExec](starexec-containerised).
    - Containerized StarExec detects the `run_image.py` script.
    - It uses the local backend, which uses `run_image.py`, which uses podman to run the
      container.
  - Go to the [`starexec-proxy-provers`](starexec-proxy-provers) directory to build non-local
    proxy-prover ATP systems for Kubernetes.
  - Test the proxy-prover ATP systems using [containerized StarExec](starexec-containerised).
    - Containerized StarExec detects the `run_image_k8s.py` script.
    - It uses the Kubernetes backend, which uses `kubectl` to manage the container within
      Kubernetes.

<!-- ------------------------------------------------------------------------------------------ -->
### Deploying StarExec on Kubernetes

- **Using EKS**:
  - **Install `kubectl`**:
    - **macOS**: Run `brew install kubectl`.
    - **Ubuntu**: Execute `snap install kubectl --classic`.
    - Verify installation with `kubectl version`.
- **Using MicroK8s**:
  - **Installation**:
    - **macOS**: MicroK8s is not natively supported. Install via a Multipass virtual machine as per the [MicroK8s macOS installation guide](https://microk8s.io/docs/install-macos).
    - **Ubuntu**:
      - Run `snap install microk8s --classic`.
      - Add your user to the `microk8s` group: `sudo usermod -aG microk8s $USER`.
      - Change ownership: `sudo chown -f -R $USER ~/.kube`.
      - Reload group memberships: `newgrp microk8s`.
      - Optionally, add `alias kubectl='microk8s kubectl'` to your shell configuration file.
  - **Verification**:
    - Check status with `microk8s status --wait-ready`.
    - List nodes using `microk8s kubectl get nodes`.
- **Deploy StarExec**:
  - Navigate to the [`starexec-kubernetes`](starexec-kubernetes) directory to deploy StarExec on MicroK8s or EKS.
  - Access the deployed StarExec website to upload your proxy-prover ATP systems and problem files.
    - **URL Access**:
      - **MicroK8s**: Run `microk8s kubectl get svc` to obtain the URL.
      - **EKS without Route53**: Execute `kubectl get svc` to get the URL.
      - **EKS with Route53**: The URL follows the format `https://your_Route53_domain`.
    - Open the URL in your browser to start using StarExec.

<!-- ------------------------------------------------------------------------------------------ -->
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
<!-- ------------------------------------------------------------------------------------------ -->
