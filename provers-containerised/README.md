# Provers Containerised

This folder contains all that is needed to containerise an ATP system (a "prover") so that 
it can be run in `podman`.
- `ubuntu-arc` contains a `Dockerfile` to build an Ubuntu image upon which everything else
  is built.
- `tptp-world` contains a `Dockerfile` to build a container with various pieces of TPTP World
  software that are needed by provers and used for running provers.
- `provers` contains folders for building individual provers (source, etc), the `start_RLR`
  script that is used to invoke a prover under the control of a "Resource Limited Run"
  program (currently `runsolver`) with appropriate leading output for the TPTP World, and
  a `Dockerfile` to build a containers for specified prover (see the comments in the `Dockerfile`).
  * Each prover's folder contains a `Dockerfile` for building the prover in a container.
  * The tag name convention for prover containers is *prover*`:`*version*s.
    - This has to be provided as the `--build-arg PROVER_IMAGE` value for building the resource
      limited prover container.
  * The tag name convention for resource limited prover containers is the prover container
    name plus the suffix `-RLR`.
- The `run_image.py` script for running a resource limited prover container on a given ATP
  problem, with other parameters as needed. Run `run_image.p -h` for all the details.
- A `Makefile` that builds `ubuntu-arc`, `tptp-world`, and some resource limited prover
  containers - look in the Makefile to see which provers are supported so far.

# To build and run a TPTP docker image for E (example)

1. First clone this repo and build `ubuntu-arc` image:
    ```shell
    git clone https://github.com/StarExecMiami/starexec-arc
    cd starexec-ARC/provers-containerised/ubuntu-arc
    podman build --no-cache -t ubuntu-arc .
    ```
2. Now build `tptp-world` image:
    ```shell
    cd ../tptp-world
    podman build --no-cache -t tptp-world .
    ```
3. Now build `eprover` image. 
    ```shell
    cd ../provers/E---3.0.03 
    podman build --no-cache -t eprover:3.0.03 .
    ```
4. Now build `eprover:version-RLR` image using the generic RLR Dockerfile
    ```shell
    cd ..
    podman build -t eprover:3.0.03-RLR --build-arg PROVER_IMAGE=eprover:3.0.03 .
    ```
5. Run using the `run_image.py` script
   ```shell
   cd ..
   run_image.py eprover:3.0.03-RLR -P ../../TPTP-problems/PUZ001+1.p -W 60 -I THM
   ```
6. Save it in `dockerhub`
   ```shell
   podman login docker.io 
   # (tptpstarexec, German greeting with money-in-middle and zeros-at-the-end)
   podman tag eprover:3.0.03-RLR docker.io/tptpstarexec/eprover:3.0.03-RLR-your_architecture (e.g., arm64, amd64)
   podman push docker.io/tptpstarexec/eprover:3.0.03-RLR-your_architecture
   ```
   - To pull it from dockerhub
     ```shell
     podman pull tptpstarexec/eprover:3.0.03-RLR-your_architecture
     ```
