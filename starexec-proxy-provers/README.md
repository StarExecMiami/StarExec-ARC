# StarExec Proxy Provers

This directory contains resources for building `.tgz` prover archives that can be uploaded and run in [containerised StarExec](../starexec-containerised). To create a proxy-prover, you first need a [resource-limited prover container](../provers-containerised).

## Creating a Proxy-Prover for Kubernetes

To create a proxy-prover that can run in containerised StarExec deployed in Kubernetes, use the following command:

```sh
python make_proxy.py docker.io/tptpstarexec/<prover>:<version>-RLR-amd64 <prover>:<version>-K8sProxy
```

This command generates `<prover>:<version>-K8sProxy.tgz`, which can be uploaded to containerised StarExec and run using Kubernetes from within containerised StarExec. The `.tgz` file includes a script named `run_image_K8s.py`.

## Creating a Proxy-Prover for Podman

To create a proxy-prover that can run in containerised StarExec using Podman, use the following command:

```sh
python make_proxy.py docker.io/tptpstarexec/<prover>:<version>-RLR-amd64 <prover>:<version>--PodmanProxy --local
```

This command generates `<prover>:<version>--PodmanProxy.tgz`, which can be uploaded to containerised StarExec and run using Podman from within containerised StarExec. The `.tgz` file includes a script named `run_image.py`.

## Running a Proxy-Prover

- To run directly in containerised StarExec, refer to the [README](../starexec-containerised/README.md) in the [`starexec-containerised`](../starexec-containerised) directory.
- To run in containerised StarExec deployed in Kubernetes, refer to the [README](../starexec-kubernetes/README.md) in the [`starexec-kubernetes`](../starexec-kubernetes) directory.
