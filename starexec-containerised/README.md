# StarExec Containerized

- `dockerPackage` contains shell scripts used by the Dockerfile for building the application image.
- `dockerPackage/configFiles` contains network configuration files.
- `dockerPackage/allScripts/starexecScripts/overrides.properties` contains StarExec configuration files.

## Build the Image

1. Ensure you have Podman installed, as explained in the [installation guide](../README.md).
2. Ensure that `$HOME/.ssh` exists and you have read-write permission.
3. Ensure that the `sshd` daemon is running with `systemctl status sshd.service`.
    - If necessary, start it with `sudo service sshd restart`.
    - On Fedora, this step needs to be done before every new start of StarExec.
4. Run `make pull` to fetch the pre-built image from the GitHub Container Registry.
    - Alternatively, you can build the image locally using `make starexec`, though this is deprecated.

## Certificates Creation

1. Ensure `mkcert` and `libnss3-tools` are installed:

    - On **Linux**, run:

    ```bash
    sudo apt update && sudo apt install -y mkcert libnss3-tools
    ```

    - On **Mac**, run:

    ```bash
    brew install mkcert
    ```

    - For other operating systems, refer to the [mkcert documentation](https://github.com/FiloSottile/mkcert).

2. Run `make mkcert-setup` to generate localhost TLS certificates.

## Persistent Runs and State Management

- **Temporary Run (for testing/dev)**: Run `make run`. The container and its state will be removed upon exit.
- **Start Persistently**: Use `make start` to launch the StarExec container in detached mode. The container will run in the background and persist its state. It will automatically create necessary volumes (`volDB`, `volExport`) to persist data. If a backup exists in `./backup_starexec`, it will attempt to restore it automatically after starting.
- **Stop Persistently**: Use `make stop`. This command stops the container without removing its state.
- **Backup State**: Use `make state-pack` to create a tarball of the current state in `./backup_starexec`.
- **Restore State**: Use `make state-unpack FILE=/path/to/state.tar.gz` to unpack a previously backed-up state into the project directory. Then run `make state-init` and `make start` to restore the container.

## Accessing StarExec

- The interface may take about a minute to become available as the StarExec `tomcat` app redeploys on each restart.
- Navigate to [http://localhost:7827](http://localhost:7827).
- For remote server access, use:
  `ssh -f -N -L 7827:starexec_server.domain:7827 your_account@starexec_server.domain`
  - If necessary, add jump host options, ala `-J your_account@jumphost.domain`
- Default Username: `admin`  
  Default Password: `admin`

## Debugging

- Run `make connect` to open a bash shell within the container.

## Managing the Image

- **Kill the Running Image**:
  - Execute `make kill` if you need to stop and remove the *persistent* running image (`starexec-app`). Use this if `make stop` fails or if you want to stop without preserving state.
- **Destroy the Image**:
  - If you encounter issues and wish to remove all configurations, execute:

   ```bash
   make clean
   make cleanVolumes
   ```

  - *Note*: This will erase all state, and you will need to rebuild the container.
  - To do a complete cleanup of your Podman environment, execute `make real-clean`.
- **Pushing to Registries**:
  - Use `make push` to push the built image (`starexec:latest`) to Docker Hub (`docker.io/tptpstarexec/starexec:latest`).
  - Use `make push REGISTRY=microk8s` to push the image to a local MicroK8s registry (`localhost:32000`). This also involves importing the image into MicroK8s. Related targets: `make list-microk8s`, `make microk8s-clean`.

## Additional Commands

- **Initialize State**: Run `make state-init` to prepare local state folders and initialize MariaDB system tables.
- **Pack State**: Use `make state-pack` to create a tarball of the current state for sharing.
- **Unpack State**: Use `make state-unpack FILE=/path/to/state.tar.gz` to restore a shared state into the project directory.
- **Help**: Run `make help` to display a list of available Makefile targets.
