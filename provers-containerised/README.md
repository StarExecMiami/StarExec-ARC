# Provers Containerised

This folder contains all the necessary components to containerize an Automated Theorem Prover (ATP) system (a "prover") for execution using `podman`.

## Directory Structure

- **`ubuntu-arc`**
  - Contains a `Dockerfile` to build an Ubuntu image upon which all other components are built.

- **`tptp-world`**
  - Contains a `Dockerfile` to build a container with various TPTP World software required by provers and necessary for running them.

- **`provers`**
  - Contains individual prover folders, each with sources and related files.
  - Includes the `start_RLR` script used to execute a prover under the control of a Resource Limited Run program (currently `runsolver`) with appropriate logging for the TPTP World.
  - Contains a `Dockerfile` for building containers for each specified prover (refer to the comments in the `Dockerfile`).
    - Each prover's folder includes a `Dockerfile` for building the prover in a container.
    - **Tag Naming Convention:**
      - **Prover Containers:** `prover:version`
        - *Prover* must be lowercase (due to docker/podman requirements).
        - The tag name is provided as the `--build-arg PROVER_IMAGE` value when building the resource limited prover container.
      - **Resource Limited Prover Containers:** `prover:version-RLR`

- **`run_image.py`**
  - Script for running a resource-limited prover container on a specified ATP problem with necessary parameters.
  - Run `run_image.py -h` for detailed usage instructions.

- **`Makefile`**
  - Builds `ubuntu-arc`, `tptp-world`, and selected resource-limited prover containers.
  - Refer to the `Makefile` to see the currently supported provers.

## Building and Running a TPTP Docker Image (Example: E 3.0.03)

1. **Clone the Repository and Build the `ubuntu-arc` Image:**
    ```shell
    git clone https://github.com/StarExecMiami/starexec-arc
    cd starexec-arc/provers-containerised/ubuntu-arc
    podman build --no-cache -t ubuntu-arc .
    ```

2. **Build the `tptp-world` Image:**
    ```shell
    cd ../tptp-world
    podman build --no-cache -t tptp-world .
    ```

3. **Build the `eprover` Image:**
    > *Note: The prover name is lowercase (`eprover`) to comply with docker/podman naming conventions.*
    ```shell
    cd ../provers/E---3.0.03
    podman build --no-cache -t eprover:3.0.03 .
    ```

4. **Build the `eprover:3.0.03-RLR` Resource Limited Prover Container:**
    ```shell
    cd ..
    podman build -t eprover:3.0.03-RLR --build-arg PROVER_IMAGE=eprover:3.0.03 .
    ```

5. **Test Using the `run_image.py` Script:**
    ```shell
    cd ..
    run_image.py eprover:3.0.03-RLR -P ../../TPTP-problems/PUZ001+1.p -W 60 -I THM
    ```

6. **Push to Docker Hub:**
    ```shell
    podman login docker.io 
    # (Provide credentials as prompted)
    podman tag eprover:3.0.03-RLR docker.io/tptpstarexec/eprover:3.0.03-RLR-your_architecture (e.g., arm64, amd64)
    podman push docker.io/tptpstarexec/eprover:3.0.03-RLR-your_architecture
    ```

    - **Pulling from Docker Hub:**
      ```shell
      podman pull tptpstarexec/eprover:3.0.03-RLR-your_architecture
      ```

