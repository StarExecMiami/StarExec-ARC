# Using containerized provers in containerized StarExec...
This is done by having the local backend run `run_image.py`<br>
with special args to run a prover container in the host.

1. `starexec-containerized` is built to support podman and connecting to the host using `make withPodman`
2. `starexec-containerized` is run using `make run`
3. A proxy prover is created using `make_proxy.py` in this directory (`starexecy-proxy-provers`).
4. The proxy prover is uploaded to the starexec using the web interface.
5. The proxy prover can be used to run the corresponding previously-installed containerized prover in the host.


---
## Example Usage:
```bash
# Using kubernetes to run the images:
python make_proxy.py docker.io/tptpstarexec/eprover:3.0.03-RLR-amd64 E---3.0.03-K8sProxy

# Alternatively, using podman to run the images:
python make_proxy.py docker.io/tptpstarexec/eprover:3.0.03-RLR-amd64 E---3.0.03-PodmanProxy --local
```

