#------------------------------------------------------------
#----To build: podman build -t ubuntu-arc .

FROM ubuntu:latest

#----Install gcc, make & co, also GIT
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    tcsh \
    python3 \
    wget \
    curl \
    openjdk-8-jdk \
    dnsutils \
    inetutils-ping && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

#----Configure GIT to clone repos
RUN git config --global http.sslverify false

#----/artifacts is where we will put all relevant executables and will be the working dir.
RUN mkdir -p /artifacts

RUN mount | grep cgroup

ENTRYPOINT ["/bin/bash"]
#------------------------------------------------------------
