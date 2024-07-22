# General Information: ##
The container images in the folder "provers" depend on (some of) the images in the folder 
"base-build".

We recommend using Podman (which is intended to work as a drop-in replacement for Docker).
See Podman installation instructions: https://podman.io/docs/installation

<br><br>

# How to do podman/docker actions

Building a container image with Podman/Docker:
```bash
podman/docker build -t <TAG_NAME> <PATH_TO_DIRECTORY_WHERE_DOCKERFILE_LIES>
```

Running a container (from an image) with Podman/Docker (entrypoint):
```bash
podman/docker run --rm [--entrypoint <ENTRYPOINT_FILE>] <TAG_NAME> <ARGS>
```

Running a container with Podman/Docker (interactive shell):
```bash
podman/docker run --rm -it <TAG_NAME>
```



Cleanup everything (Podman):
```bash
podman system prune --all --force && podman rmi --all
```
Forced cleanup (Podman):
```bash
podman rmi --all --force
```
Cleanup everything (Docker):
```bash
docker system prune --all --force &&  docker rmi $(docker images -a -q)
```




<br><br>
<br><br>





# To build and run a TPTP docker image for E (example)

1. First clone this repo and build `ubuntu-arc` image:
    ```shell
    git clone https://github.com/StarExecMiami/starexec-arc
    cd starexec-ARC/provers-containerised/ubuntu-arc
    podman build -t ubuntu-arc .
    ```

2. Now build `tptp-world` image:
    ```shell
    cd ../tptp-world
    podman build -t tptp-world .
    ```

3. Now build `eprover` image. 
    ```shell
    cd ../provers/E---3.0.03 
    podman build -t eprover:3.0.03 .
    ```

4. Now build `eprover:version-RLR` image using the generic RLR Dockerfile
    ```shell
    cd ..
    podman build -t eprover:3.0.03-RLR --build-arg PROVER_IMAGE=eprover:3.0.03 .
    ```

<br><br><br>
# To run using the `run_image.py` script
```shell
cd provers-containerised/provers
run_image.py eprover:3.0.03-RLR -P ../../TPTP-problems/PUZ001+1.p -W 60 -I THM
```


<br><br><br>
# To put it in dockerhub
```bash
podman login docker.io 
# (tptpstarexec, German greeting with money-in-middle and zeros-at-the-end)
podman tag eprover:3.0.03-RLR docker.io/tptpstarexec/eprover:3.0.03-RLR-your_architecture (e.g., arm64, amd64)
podman push docker.io/tptpstarexec/eprover:3.0.03-RLR-your_architecture
```

<br><br>
# To pull it from dockerhub

podman pull tptpstarexec/eprover:3.0.03-RLR-your_architecture

