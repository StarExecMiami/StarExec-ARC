# StarExec Containerized - Basic Use Instructions

If you have been given a saved state, place the saved state directory in the current directory. It will normally be named `starexec_saved_state`.
If it is named anything else, set the `STAREXEC_SAVED_STATE_DIR` environment variable to the absolute path of the saved state directory.

Start the StarExec container with **make start**.
This will take a minute or two, at the end of which you will be prompted to open the URL `https://localhost:7827`
(if the container is running on a different computer to the browser, you'll need to redirect `localhost:7827` to that computer, with  `ssh -f -N -L 7827:remote.computer.running.starexec.com:7827 user@remote.computer.running.starexec.com`).
That will take you to the StarExec login page.
The default adminstrative login credentials are `admin:admin`.
If you have been given a saved state, you might have been given a user login to use instead.

When you are done, stop the container with **make stop**.
That will save the state in the same place it was read from, or in the current directory if there was no saved state when you started the container.

# StarExec Containerized - Advanced Use Documentation

## Persistent Runs and State Management

StarExec supports persistent state management through backup directories, allowing you to save, share, and restore complete system states.

### Basic Operations

- **Temporary Run (for testing/dev)**: Run `make run`. The container and its state will be removed upon exit.
- **Start Persistently**: Use `make start` to launch the StarExec container in detached mode. The container will run in the background and persist its state in `./starexec_backup/` by default.
- **Stop Persistently**: Use `make stop`. This command stops the container without removing its state.

### State Directory Management

You can work with multiple state directories using the `BACKUP_DIR` parameter:
# StarExec Containerized - Developer Documentation

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


