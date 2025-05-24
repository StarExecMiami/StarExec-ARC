# Provers Containerised

This folder contains all the necessary components to containerize an Automated Theorem Prover
(ATP) system (a "prover") for execution using `podman`.

## Directory Structure

- `ubuntu-arc`
  - Contains a `Dockerfile` to build an Ubuntu image upon which all other components are built.

- `tptp-world`
  - Contains a `Dockerfile` to build a container with various TPTP World software required by
    provers and necessary for running them.

- `provers`
  - Contains individual prover folders, each with sources and related files.
    The directory name follows the pattern `Prover---Version` (e.g., `E---3.0.03`).
  - Includes the `start_RLR` script used to execute a prover under the control of a Resource
    Limited Run program (currently `runsolver`) with appropriate logging for the TPTP World.
  - Contains a `Dockerfile` for building the container for a specified prover (refer to the
    comments in the `Dockerfile`), with resource control.
    - Each prover's folder includes a `Dockerfile` for building the prover in a container (without
      resource control, e.g., just the prover binary).
    - Tag Naming Convention:
      - Prover containers: *`prover:version`*
        - *`prover`* must be lowercase (due to docker/podman requirements).
        - The tag name is provided as the `--build-arg PROVER_IMAGE` value when building the
          resource limited prover container.
      - Resource limited prover containers: *`prover:version-RLR`*

- `run_image.py`
  - Script for running a resource-limited prover container on a specified ATP problem with
    necessary parameters.
  - Run `run_image.py -h` for detailed usage instructions.

- `Makefile`
  - Builds `ubuntu-arc`, `tptp-world`, and selected resource-limited prover containers (defined
    by the `PROVERS` variable).
  - Defines prover versions (e.g., `EPROVER_VERSION`) and directory names (e.g., `E_RAW_DIR`).
  - Provides targets for building base images (`make base`), individual prover images
    (e.g., `make eprover-RAW`), and resource-limited prover images (e.g., `make eprover` or 
    `make eprover-RLR`). Run `make` or `make all` to build everything defined in `PROVERS`.
  - Refer to the `Makefile` to see the currently supported provers and their versions.

## Building and running a containerised prover

Note: The `Makefile` automates these steps.
You can run `make eprover` to build the E prover RLR image directly, or `make all` to build all
defined provers.
The example below shows the manual steps.

1. Clone the repository and build the `ubuntu-arc` image:  
    `git clone https://github.com/StarExecMiami/starexec-arc`  
    `cd starexec-arc/provers-containerised/ubuntu-arc`  
    `podman build --no-cache -t ubuntu-arc .`
    > *(Or run `make ubuntu-arc`)*

2. Build the `tptp-world` image:  
    `cd ../tptp-world`  
    `podman build --no-cache -t tptp-world .`  
    > *(Or run `make tptp-world`)*

3. Build the `prover` image:  
   *Note: The prover name is lowercase (e.g., `eprover`) to comply with docker/podman naming
   conventions.*
    `cd ../provers/Prover---Version`  
    `podman build --no-cache -t prover:version .`  
    > (Or run `make prover-RAW`)

4. Build the `prover:version-RLR` resource limited prover container:  
    `cd ..`  
    `podman build -t prover:version-RLR --build-arg PROVER_IMAGE=prover:version .`  
    > (Or run `make prover-RLR` or simply `make eprover`)

5. Test using the `run_image.py` script on PUZ001+1 (provided):  
    `cd ..`  
    `./run_image.py eprover:<EPROVER_VERSION>-RLR -P PUZ001+1.p -W 60 -I THM`  

6. Push to DockerHub:  
    `podman login docker.io`  
    `podman tag prover:version-RLR docker.io/tptpstarexec/prover:version-RLR-your_architecture`  
     (e.g., arm64, amd64)  
    `podman push docker.io/tptpstarexec/eprover:<EPROVER_VERSION>-RLR-your_architecture`  

    - Pulling from DockerHub:  
      `podman pull tptpstarexec/prover:version-RLR-your_architecture`
