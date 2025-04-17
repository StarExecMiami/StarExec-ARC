# Provers Containerised

This folder contains all the necessary components to containerize an Automated Theorem Prover (ATP) system (a "prover") for execution using `podman`.

## Directory Structure

- **`ubuntu-arc`**
  - Contains a `Dockerfile` to build an Ubuntu image upon which all other components are built.

- **`tptp-world`**
  - Contains a `Dockerfile` to build a container with various TPTP World software required by provers and necessary for running them.

- **`provers`**
  - Contains individual prover folders, each with sources and related files. The directory name follows the pattern `Prover---Version` (e.g., `E---3.0.03`).
  - Includes the `start_RLR` script used to execute a prover under the control of a Resource Limited Run program (currently `runsolver`) with appropriate logging for the TPTP World.
  - Contains a `Dockerfile` for building containers for each specified prover (refer to the comments in the `Dockerfile`).
    - Each prover's folder includes a `Dockerfile` for building the prover in a container.
    - **Tag Naming Convention:**
      - **Prover Containers:** `prover:version`
        - *Prover* must be lowercase (due to docker/podman requirements). The prover name and version are typically defined in the `Makefile`.
        - The tag name is provided as the `--build-arg PROVER_IMAGE` value when building the resource limited prover container.
      - **Resource Limited Prover Containers:** `prover:version-RLR`

- **`run_image.py`**
  - Script for running a resource-limited prover container on a specified ATP problem with necessary parameters.
  - Run `run_image.py -h` for detailed usage instructions.

- **`Makefile`**
  - Builds `ubuntu-arc`, `tptp-world`, and selected resource-limited prover containers (defined by the `PROVERS` variable).
  - Defines prover versions (e.g., `EPROVER_VERSION`) and directory names (e.g., `E_RAW_DIR`).
  - Provides targets for building base images (`make base`), individual prover images (`make eprover-RAW`), and resource-limited prover images (`make eprover` or `make eprover-RLR`). Run `make` or `make all` to build everything defined in `PROVERS`.
  - Refer to the `Makefile` to see the currently supported provers and their versions.

## Building and Running a TPTP Docker Image (Example: E prover using Makefile variables)

> *Note: The `Makefile` automates these steps. You can run `make eprover` to build the E prover RLR image directly, or `make all` to build all defined provers.*
> *The example below shows the manual steps, using placeholders like `<EPROVER_VERSION>` which correspond to variables defined in the `Makefile` (e.g., `EPROVER_VERSION=3.0.03`).*

1. **Clone the Repository and Build the `ubuntu-arc` Image:**
    > *(Or run `make ubuntu-arc`)*

    ```shell
    git clone https://github.com/StarExecMiami/starexec-arc
    cd starexec-arc/provers-containerised/ubuntu-arc
    podman build --no-cache -t ubuntu-arc .
    ```

2. **Build the `tptp-world` Image:**
    > *(Or run `make tptp-world`)*

    ```shell
    cd ../tptp-world
    podman build --no-cache -t tptp-world .
    ```

3. **Build the `eprover` Image:**
    > *Note: The prover name is lowercase (`eprover`) to comply with docker/podman naming conventions. The directory name and version tag should match the `Makefile` definitions (e.g., `E---<EPROVER_VERSION>` and `eprover:<EPROVER_VERSION>`).*
    > *(Or run `make eprover-RAW`)*

    ```shell
    # Replace <EPROVER_VERSION> with the actual version from the Makefile (e.g., 3.0.03)
    cd ../provers/E---<EPROVER_VERSION> 
    podman build --no-cache -t eprover:<EPROVER_VERSION> .
    ```

4. **Build the `eprover:<EPROVER_VERSION>-RLR` Resource Limited Prover Container:**
    > *(Or run `make eprover-RLR` or simply `make eprover`)*

    ```shell
    cd .. 
    # Replace <EPROVER_VERSION> with the actual version from the Makefile (e.g., 3.0.03)
    podman build -t eprover:<EPROVER_VERSION>-RLR --build-arg PROVER_IMAGE=eprover:<EPROVER_VERSION> .
    ```

5. **Test Using the `run_image.py` Script on PUZ001+1 (provided):**

    ```shell
    cd ..
    # Replace <EPROVER_VERSION> with the actual version from the Makefile (e.g., 3.0.03)
    ./run_image.py eprover:<EPROVER_VERSION>-RLR -P PUZ001+1.p -W 60 -I THM
    ```

6. **Push to Docker Hub:**

    ```shell
    podman login docker.io 
    # (Provide credentials as prompted)
    # Replace <EPROVER_VERSION> with the actual version from the Makefile (e.g., 3.0.03)
    podman tag eprover:<EPROVER_VERSION>-RLR docker.io/tptpstarexec/eprover:<EPROVER_VERSION>-RLR-your_architecture (e.g., arm64, amd64)
    podman push docker.io/tptpstarexec/eprover:<EPROVER_VERSION>-RLR-your_architecture
    ```

    - **Pulling from Docker Hub:**
  
      ```shell
      # Replace <EPROVER_VERSION> with the actual version (e.g., 3.0.03)
      podman pull tptpstarexec/eprover:<EPROVER_VERSION>-RLR-your_architecture
      ```
