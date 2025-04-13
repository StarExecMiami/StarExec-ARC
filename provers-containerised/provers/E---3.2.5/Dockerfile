#------------------------------------------------------------
#----To build: podman build --no-cache -t eprover:3.2.5 .
FROM ubuntu-arc

#----Clone repository
ARG E_VERSION=E-3.2.5
RUN git clone --depth 1 --branch $E_VERSION https://github.com/eprover/eprover.git

#----Set working directory to cloned sources directory
WORKDIR /eprover

#----Builds first-order executable
RUN ./configure --bindir=/artifacts && \
    make && \
    make install && \
    cp PROVER/eprover /artifacts/eprover

#----Builds higher-order executable
RUN ./configure --enable-ho && \
    make rebuild && \
    cp PROVER/eprover-ho /artifacts/eprover-ho

#----Add run_system script 
ADD run_system /artifacts/

#------------------------------------------------------------
