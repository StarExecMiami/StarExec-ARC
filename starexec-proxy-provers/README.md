# StarExec Proxy Provers

This folder contains the `make_proxy.py` script that makes a `.tgz` proxy-prover file for a given 
containerised (see provers-containerised) prover.
Containerised StarExec (see starexec-containerised) can run a proxy-prover in Kubernetes.

## To make a proxy-prover (example)
```shell
python make_proxy.py docker.io/tptpstarexec/eprover:3.0.03-RLR-amd64 E---3.0.03-K8sProxy
```
## To run a proxy-prover (example)

See the README in starexec-kubernetes

# Here's how the magic works
This is done by having the local backend in starexec run `run_image.py` with special args to 
run a prover container in the host.

1. `starexec-containerized` is built to support podman and connecting to the host using 
   `make withPodman`.
2. `starexec-containerized` is run using `make run`.
3. A proxy prover is created using `make_proxy.py` in this directory.
4. The proxy prover is uploaded to the starexec using the web interface.
5. The proxy prover can be used to run the corresponding containerized prover in the host.

---
<!--
# Alternatively, using podman to run the images:
python make_proxy.py docker.io/tptpstarexec/eprover:3.0.03-RLR-amd64 E---3.0.03-PodmanProxy --local
-->
```

