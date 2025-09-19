# StarExec Containerized - Basic Use Instructions

If you have been given a saved state in a `.tgz` file, use 
`make state-restore FILE=the.tgz SAVED_STATE_DIR=target_location` to expand `the.tgz` into the
`target_location` directory.
(You can also simply expand the `.tgz` yourself and place the saved state directory where ever
you want.)
The saved state directory is normally named `starexec_saved_state`.
Set the `STAREXEC_SAVED_STATE_DIR` environment variable to the absolute path of the saved state 
directory.

Start the StarExec container with **`make start`**.
This will take a minute or two, at the end of which you will be prompted to open the URL `https://localhost:7827`
(if the container is running on a different computer to the browser, you'll need to redirect `localhost:7827` to that computer, with  `ssh -f -N -L 7827:remote.computer.running.starexec.com:7827 user@remote.computer.running.starexec.com`).
That will take you to the StarExec login page.
The default administrative login credentials are `admin:admin`.
If you have been given a saved state, you might have been given a user login to use instead.

When you are done, stop the container with **`make stop`**.
That will save the state in the same place it was read from, or in the current directory if there was no saved state when you started the container.

# StarExec Containerized - Advanced Use Documentation

The `Makefile` contains many targets for use and development of StarExec in a container.
The full list can be seen in a summarized form with `make help`.
The targets that are useful for (advanced) use of StarExec in a container are:
- `start` -             Start the StarExec container, preserving state
- `stop` -              Stop the persistent StarExec container
- `kill` -              Stop and remove the persistent StarExec container
- `image` -             Ensure the StarExec image is available locally
- `clean` -             Remove the StarExec container image and dangling images
- `state-create` -      Force creation of a new database state, destroying existing data
- `state-init` -        Initialize local state folders and prepare DB/export for sharing
- `state-pack` -        Create a .tgz with the current backup state to share
- `state-restore` -     Restore state from a .tgz file (use: `make state-restore FILE=the.tgz SAVED_STATE_DIR=target_location`)
- `mkcert-setup` -      Setup mkcert and generate localhost TLS certificates
- `help` -              Display help for Makefile targets

# StarExec Containerized - Developer Documentation

The `Makefile` contains many targets for use and development of StarExec in a container.
The full list can be seen in a summarized form with `make help`.
The targets that are useful for development of StarExec in a container are:
- `all` -               Prompt for backend type and build
- `local` -             Set backend type to local and build
- `k8s` -               Set backend type to k8s and build
- `push` -              Push the StarExec image to a container registry
- `pull` -              Pull the pre-built StarExec image from GitHub Container Registry
- `run` -               Run the StarExec container interactively.
                        The container and its state will be removed upon exit.
- `connect` -           Connect to the running StarExec container via bash shell
- `starexec` -          Build the StarExec container image (internal use)
- `start-container` -   Start the StarExec container (internal use)
- `ssh-setup` -         Setup SSH keys for podman communication (internal use)
- `state-fix-perms` -   Fix ownership of `STAREXEC_SAVED_STATE_DIR` to current user
- `clean-volumes` -     Remove StarExec related volumes from `STAREXEC_SAVED_STATE_DIR`
- `real-clean` -        Reset Podman - removes ALL containers, images, volumes
- `help` -              Display help for Makefile targets

## Directory Contents
- `dockerPackage` contains shell scripts used by the Dockerfile for building the application image.
- `dockerPackage/configFiles` contains network configuration files.
- `dockerPackage/allScripts/starexecScripts/overrides.properties` contains StarExec configuration files.

## Building the Image

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


