# StarExec-ARC <br>(Automated Reasoning Containerisation)

This folder contains code for the containerization of Automated Theorem Provering (ATP) systems. 
It also contains code for the deployment of these ATP containers within a containerized StarExec 
(in podman, or kubernetes using microk8s or Amazon EKS).

The following steps are required to get it all working
* Deploy StarExec in microk8s or EKS
  - That is done in the `starexec-kubernetes` directory.
  - The README file has instructions.
* Build containerised proxy-prover versions of the ATP systems.
  - That requires containerised (non-proxy-versions) versions of the ATP systems.
    * Those are built in the `provers-containerised` directory.
    * The README file has instructions.
  - The proxy-prover versions are then built in the `starexec-proxy-provers` directory.
  - The README file has instructions.
* Navigate to the StarExec website, upload your ATP system and problem files, and away you go.
  - The URL for the website depends how you deployed StarExec
    * For microk8s
      - WHAT?
    * For EKS but without a Route53 domain
      - WHAT
    * For EKS with a Route53 domain
      - `https:`*your_Route53_domain*`/starexec`
  - MOre about uploading here.

## Repository Subdirectories

- [Provers Containerised](provers-containerised/README.md) - Stuff for building the podman images corresponding with specific ATP systems.
- [StarExec Containerised](starexec-containerised/README.md) - Stuff for building the podman image of the [StarExec head node software](https://github.com/StarExecMiami/StarExec/).
- [StarExec Proxy Provers](starexec-proxy-provers/README.md) - Stuff for building StarExec-compatible `.tar.gz` archives that enable the use of containerized provers within StarExec.
- [StarExec Kubernetes](starexec-kubernetes/README.md) - Stuff for deploying StarExec in Kubernetes (using microk8s or Amazon EKS).
- [StarExec Provers](starexec-provers/README.md) - Source code for example provers.
- [StarExec TPTP](starexec-tptp/README.md) - Various code necessary for supporting TPTP.

## Documentation

- [A workshop paper about this project](https://www.eprover.org/EVENTS/IWIL-2024/IWIL-24-Preproceedings.pdf)

- [The ARA proposal](https://www.amazon.science/research-awards/recipients/geoffrey-sutcliffe)
