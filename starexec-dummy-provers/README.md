# Using containerized provers in containerized StarExec...
This is done by having the local backend run `run_image.py`<br>
with special args to run a prover container in the host.

1. `starexec-containerized` is built to support podman and connecting to the host using `make withPodman`
2. `starexec-containerized` is run using `make run`
3. A dummy prover is created using `make_dummy.py` in this directory (`starexecy-dummy-provers`).
4. The dummy prover is uploaded to the starexec using the web interface.
5. The dummy prover can be used to run the corresponding previously-installed containerized prover in the host.


---
## Example Usage:
```bash
python make_dummy.py docker.io/tptpstarexec/eprover:3.0.03-RLR-amd64 dummy_k8s_eprover --k8s
```

