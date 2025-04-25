# StarExec Helm Chart for MicroK8s Deployment

This directory contains a Helm chart and a Makefile designed to simplify the deployment of StarExec onto a local MicroK8s cluster.

## Prerequisites

* **MicroK8s:** You must have MicroK8s installed and running on your system. Verify its status with `microk8s status --wait-ready`.
* **Secret Files:** The deployment requires TLS certificate/key files and an SSH private key file. The Makefile expects these files at the following relative paths:
  * TLS Certificate: `../starexec-kubernetes/microk8s/starexec-tls.crt`
  * TLS Key: `../starexec-kubernetes/microk8s/starexec-tls.key`
  * SSH Key: `../starexec-kubernetes/microk8s/starexec-ssh-key`
    Ensure these files exist before creating secrets.

## Setup

The Makefile provides targets to prepare your MicroK8s environment:

1. **Check MicroK8s Status:**

    ```bash
    make check-microk8s
    ```

2. **Enable Required Addons:** This enables `dns`, `hostpath-storage`, `ingress`, and `helm3`.

    ```bash
    make enable-addons
    ```

3. **Create Namespace:** Creates the Kubernetes namespace (default: `starexec`).

    ```bash
    make create-namespace
    ```

4. **Create Secrets:** Creates the necessary TLS and SSH secrets in the namespace from the files specified in the Prerequisites section.

    ```bash
    make create-secrets
    ```

## Usage

The Makefile provides several targets for managing the Helm release:

* **`make lint`**: Lints the Helm chart for potential issues.
* **`make template`**: Generates the Kubernetes YAML manifest from the chart and saves it to `starexec-local-templated.yaml`. This is useful for debugging the generated resources without actually deploying.
* **`make install`**: Installs the StarExec Helm chart into the MicroK8s cluster. This depends on the setup targets (`enable-addons`, `create-namespace`, `create-secrets`, `lint`). It uses `microk8s-hostpath` storage and disables readiness probes by default.
* **`make upgrade`**: Upgrades an existing StarExec release or installs it if it doesn't exist. Uses the same settings as `make install`.
* **`make uninstall`**: Uninstalls the StarExec Helm release.
* **`make status`**: Shows the status of the Helm release, related pods, and ingress.
* **`make debug-probes`**: Installs the chart with all health probes (readiness, liveness, startup) disabled. This is helpful for troubleshooting startup issues where probes might be failing prematurely.
* **`make get-url`**: Displays the likely URL to access the StarExec web interface ([https://localhost/starexec](https://localhost/starexec)).
* **`make clean-secrets`**: Deletes the TLS and SSH secrets created by `make create-secrets`.
* **`make clean-namespace`**: Deletes the Kubernetes namespace.
* **`make clean`**: Performs a full cleanup: uninstalls the chart, deletes secrets, and deletes the namespace.
* **`make help`**: Shows a summary of available Makefile targets.

## Configuration

Key configuration options are defined at the top of the `Makefile`:

* `NAMESPACE`: Kubernetes namespace for deployment (default: `starexec`).
* `RELEASE_NAME`: Helm release name (default: `starexec-local`).
* `TLS_CERT_PATH`, `TLS_KEY_PATH`, `SSH_KEY_PATH`: Paths to the required secret files.
* `TLS_SECRET_NAME`, `SSH_SECRET_NAME`: Names for the Kubernetes secrets.

The `install`, `upgrade`, `template`, and `debug-probes` targets override some default chart values using `--set` flags, notably:

* Setting the `storageClassName` to `microk8s-hostpath`.
* Configuring ingress for `localhost`.
* Using existing secrets instead of creating new ones via the chart.
* Disabling readiness probes (`install`, `upgrade`) or all probes (`debug-probes`).

Refer to the `values.yaml` file for all available chart configuration options.

## Accessing StarExec

Once the pods are running (check with `make status` or `microk8s kubectl get pods -n starexec`), you should be able to access StarExec at:

[https://localhost/starexec](https://localhost/starexec)

You will likely need to accept warnings about the self-signed certificate in your browser.
