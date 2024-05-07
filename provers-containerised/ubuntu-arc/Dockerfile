#------------------------------------------------------------
#----To build: podman build -t ubuntu-arc .

FROM ubuntu:latest

#----Install gcc, make & co, also GIT
RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential cmake git tcsh python3 wget curl

#----Configure GIT to clone repos
RUN export GIT_SSL_NO_VERIFY=1 && \
    git config --global http.sslverify false

#----/artifacts is where we will put all relevant executables and will the working dir.
RUN mkdir -p /artifacts

ENTRYPOINT ["/bin/bash"]
#------------------------------------------------------------
