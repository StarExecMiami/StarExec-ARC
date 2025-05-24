# StarExec Proxy-Provers

This directory contains resources for building `.tgz` proxy-prover archives that can be uploaded
and run in [containerised StarExec](../starexec-containerised).
Proxy-provers are intended for use in a StarExec Kubernetes deployment, but can also be configured
to run directly in containerised StarExec.

To create a proxy-prover, you first need a
[resource-limited prover container](../provers-containerised).

## A proxy-prover for Kubernetes

To create a proxy-prover that can run in a containerised StarExec Kubernetes deployment:  
`python make_proxy.py docker.io/tptpstarexec/prover:version-RLR-amd64 prover:version-K8sProxy`  
This generates `prover:version-K8sProxy.tgz`, which can be uploaded into a StarExec Kubernetes
deployment.
The `.tgz` file includes a script named `run_image_k8s.py` that is detected by the containerised
StarExec, which hence uses the Kubernetes backend to run the prover.

## A proxy-prover for containerised StarExec

To create a proxy-prover that can run directly in containerised StarExec:  
`python make_proxy.py docker.io/tptpstarexec/prover:version-RLR-amd64 prover:version--PodmanProxy --local`  
This generates `prover:version--PodmanProxy.tgz`, which can be uploaded into containerised 
StarExec.
The `.tgz` file includes a script named `run_image.py` that is detected by the containerised
StarExec, which hence uses `podman` to run the prover.
