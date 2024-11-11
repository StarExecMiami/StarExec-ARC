# StarExec Proxy Provers

This folder contains things building to build `.tgz` prover archives that can be uploaded and 
run in [containerised StarExec](../starexec-containerised).
In order to make a proxy-prover you first need a 
[resource limited containerised prover](../provers-containerised).

## To make a proxy-prover that can run in containerised StarExec deployed in Kubernetes

`python make_proxy.py docker.io/tptpstarexec/`*prover*`:`*version*`-RLR-amd64 `*prover*`:`*version*`--K8sProxy`

That creates `*prover*`:`*version*`--K8sProxy.tgz` that can be uploaded to containerised 
StarExec to run in Kubernetes.
The `.tgz` contains a script `run_image_K8s.py`.

## To make a proxy-prover that can run in containerised StarExec using podman

`python make_proxy.py docker.io/tptpstarexec/`*prover*`:`*version*`-RLR-amd64 `*prover*`:`*version*`--PodmanProxy --local`

That creates `*prover*`:`*version*`--PodmanProxy.tgz` that can be uploaded to containerised 
StarExec to run in podman.
The `.tgz` contains a script `run_image.py`.

## To run a proxy-prover 

- Directly in containerised StarExec, see the [README](../starexec-containerised/README.md) in
  [`starexec-containerised`](../starexec-containerised).
- In containerised StarExec deployed in Kubernetes, see the 
  [README](../starexec-kubernetes/README.md) in
  [`starexec-kubernetes`](../starexec-kubernetes).

