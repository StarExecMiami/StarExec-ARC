# StarExec-ARC (Automated Reasoning Containerisation)
### This folder contains code for the containerization of Automated Theorem Provering (ATP) systems. It also contains code for the deployment of these ATP containers within a containerized StarExec (in podman, or kubernettes using microk8s or Amazon EKS).
https://www.eprover.org/EVENTS/IWIL-2024/IWIL-24-Preproceedings.pdf

## Repository Subdirectories

- [Provers Containerised](provers-containerised/README.md) - Stuff for building the podman images corresponding with specific ATP systems.
- [StarExec Containerised](starexec-containerised/README.md) - Stuff for building the podman image of the [StarExec head node software](https://github.com/StarExecMiami/StarExec/).
- [StarExec Dummy Provers](starexec-dummy-provers/README.md) - Stuff for building StarExec-compatible `.tar.gz` archives that enable the use of containerized provers within StarExec.
- [StarExec Kubernetes](starexec-kubernetes/README.md) - Stuff for deploying StarExec in Kubernetes (using microk8s or Amazon EKS).
- **StarExec Provers** - Source code for example provers.
- [StarExec TPTP](starexec-tptp/README.md) - Various code necessary for supporting TPTP.