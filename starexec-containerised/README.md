# StarExec Containerized

- `dockerPackage` contains shell scripts used by the Dockerfile for building the application image.
- `dockerPackage/configFiles` contains network configuration files.
- `dockerPackage/allScripts/starexecScripts/overridesproperties.txt` contains StarExec configuration files.

## Build the Image

1. Ensure you have Podman installed, as explained [here](../README.md).
2. Ensure that `$HOME/.ssh` exists and you have read-write permission.
3. Ensure that the `sshd` daemon is running with `systemctl status sshd.service`.
    - If necessary start it with `sudo service sshd restart`.
    - On Fedora, this step needs to be done before every new start of StarExec.
4. Run `make` (refer to the `Makefile` for details).
    - This step typically needs to be done only once.

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

2. Run `make mkcert-setup` to generate and install localhost certificates.
    - This will create the necessary certificates in `~/.local/share/mkcert/`:
      - `localhost.crt`
      - `localhost.key`

## Run the Image

1. Choose how to run the container:
    - **Temporary Run (for testing/dev)**: Run `make run`. The container and its state will be removed upon exit.
    - **Persistent Run**: Run `make start`. The container will run in the background and persist its state. See the "Persistent Runs and State Management" section below.

## Persistent Runs and State Management

- **Start Persistently**: Use `make start` to launch the StarExec container in detached mode. It will automatically create necessary volumes (`volDB`, `volStar`, `volPro`, `volExport`) to persist data. If a backup exists in `./state-backup`, it will attempt to restore it automatically after starting.
- **Stop Persistently**: Use `make stop`. This command first backs up the current state of the running container to `./state-backup` and then stops the container.
- **Backup State**: Use `make backup-state` to manually back up the state from the running persistent container to `./state-backup`. This includes MySQL data and StarExec home directories.
- **Restore State**: Use `make restore-state` to manually restore the state from `./state-backup` to the running persistent container. This stops relevant services, restores files, and restarts services. *Note*: The container must be running (started with `make start`) for restore to work.

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
  - Execute `make kill` if you need to stop and remove the *persistent* running image (`starexec-app`). Use this if `make stop` fails or if you want to stop without backing up state.
- **Destroy the Image**:
  - If you encounter issues and wish to remove all configurations, execute:

   ```bash
   make clean
   make cleanVolumes
   ```

  - *Note*: This will erase all state, and you will need to rebuild the container.
  - To do a complete cleanup of your podman life do `make real-clean`
- **Pushing to Registries**:
  - Use `make push` to push the built image (`starexec:latest`) to Docker Hub (`docker.io/tptpstarexec/starexec:latest`).
  - Use `make push REGISTRY=microk8s` to push the image to a local MicroK8s registry (`localhost:32000`). This also involves importing the image into MicroK8s. Related targets: `make list-microk8s`, `make microk8s-clean`.
