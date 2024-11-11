# StarExec Proxy Provers

This folder contains things building to build `.tgz` prover archives that can be uploaded and 
run in [a containerised version of StarExec](../starexec-containerised).
In order to make a proxy-prover you first need a 
[resource limited containerised prover](../provers-containerised).

## To make a proxy-prover that can run in Kubernetes

`python make_proxy.py docker.io/tptpstarexec/`*prover*`:`*version*`-RLR-amd64 `*prover*`:`*version*`--K8sProxy`

## To make a proxy-prover that can run in `podman`

`python make_proxy.py docker.io/tptpstarexec/`*prover*`:`*version*`-RLR-amd64 `*prover*`:`*version*`--PodmanProxy --local`

## To run a proxy-prover in Kubernetes

See the [README](../starexec-kubernetes/README.md) in
[`starexec-kubernetes`](../starexec-kubernetes).

# Here's how the magic works
This is done by having the local backend in starexec run `run_image.py` with special args to 
run a prover container in the host.

1. `starexec-containerised` is built to support podman and connecting to the host using 
   `make withPodman`.
2. `starexec-containerised` is run using `make run`.
3. A proxy prover is created using `make_proxy.py` in this directory.
4. The proxy prover is uploaded to the starexec using the web interface.
5. The proxy prover can be used to run the corresponding containerised prover in the host.


