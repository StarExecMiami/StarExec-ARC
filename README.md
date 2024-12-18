# StarExec-ARC <BR>(Automated Reasoning Containerisation)

This folder contains code for the containerization of Automated Theorem Provering (ATP) systems. 
It also contains code for the deployment of these ATP containers within a containerized StarExec 
(in podman, or kubernetes using microk8s or Amazon EKS).

The following steps are required to get it all working
* Install `podman`, [as explained here](https://podman.io/docs/installation).
  - On a Mac: `brew install podman` 
  - In Ubuntu `sudo apt install podman` or `snap install podman --classic`
  - Check with `podman --version`
* If you will be using EKS, install kubectl:
  - On a Mac: `brew install kubectl` 
  - In Ubuntu `snap install kubectl --classic`
  - Check with `kubectl version`
* If you will be using microk8s, install microk8s:
  - On a Mac: MicroK8s is not natively supported on macOS. 
    However, you can install MicroK8s by running it inside a Multipass virtual machine.
    See [`https://microk8s.io/docs/install-macos`](https://microk8s.io/docs/install-macos).
  - In Ubuntu:
    * `snap install microk8s --classic`
    * `sudo usermod -aG microk8s $USER && sudo chown -f -R $USER ~/.kube && newgrp microk8s`
    * Optionally `alias kubectl='microk8s kubectl'` in your shell resource file.
  - Check with `microk8s status --wait-ready` and `microk8s kubectl get nodes`
* Build containerised proxy-prover versions of the ATP systems.
  - That requires containerised (non-proxy) versions of the ATP systems.
    * Those are built in the [`provers-containerised`](provers-containerised) directory.
  - The proxy-prover versions are then built in the 
    [`starexec-proxy-provers`](starexec-proxy-provers) directory.
* Deploy StarExec in microk8s or EKS
  - That is done in the [`starexec-kubernetes`](starexec-kubernetes) directory.
* Navigate to the StarExec website as deployed, upload your proxy-prover ATP system and problem 
  files, and away you go.
  - The URL for the website depends how you deployed StarExec
    * For microk8s
      - Run `microk8s kubectl get svc` to get the URL.
      - Put the URL plus `/starexec` in your browser.
    * For EKS but without a Route53 domain
      - Run `microk8s get svc` to get the URL.
      - Put the URL plus `/starexec` in your browser.
    * For EKS with a Route53 domain
      - `https://`*your_Route53_domain*`/starexec`
  - More about uploading here.

## Repository Subdirectories

- [`provers-containerised`](provers-containerised/README.md) - 
  Stuff for building the containers for individual ATP systems.
- [`starexec-containerised`](starexec-containerised/README.md) - 
  Stuff for building a containerized 
  [StarExec](https://github.com/StarExecMiami/StarExec/) (head node software only).
- [`starexec-proxy-provers`](starexec-proxy-provers/README.md) - 
  Stuff for building prover archives that can run in `starexec-containerised`.
- [`starexec-kubernetes`](starexec-kubernetes/README.md) - 
  Stuff for deploying `starexec-containerised` in Kubernetes (using microk8s or Amazon EKS).
- [`starexec-provers`](starexec-provers/README.md) - Source code for example provers.
- [`starExec-tptp`](starexec-tptp/README.md) - Code for supporting TPTP.

## How to do podman/docker actions

Building a container image:
```shell
podman/docker build -t <TAG_NAME> <PATH_TO_DIRECTORY_WHERE_DOCKERFILE_LIES>
```
Running a container (entrypoint):
```shell
podman/docker run --rm [--entrypoint <ENTRYPOINT_FILE>] <TAG_NAME> <ARGS>
```
Running a container (interactive shell):
```shell
podman/docker run --rm -it <TAG_NAME>
```
Cleanup everything (podman):
```shell
podman system prune --all --force && podman rmi --all
```
Forced cleanup (podman):
```shell
podman rmi --all --force
```
Cleanup everything (docker):
```shell
docker system prune --all --force &&  docker rmi $(docker images -a -q)
```

## Documentation

- [A workshop paper about this project](https://www.eprover.org/EVENTS/IWIL-2024/IWIL-24-Preproceedings.pdf)

- [The ARA proposal](https://www.amazon.science/research-awards/recipients/geoffrey-sutcliffe)
