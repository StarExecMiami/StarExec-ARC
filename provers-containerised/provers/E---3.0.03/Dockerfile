#------------------------------------------------------------
#----To build: podman build -t eprover:3.0.03 .
FROM ubuntu-arc

#----Clones repository
ARG E_VERSION=E-3.0.03
RUN git clone --depth 1 --branch $E_VERSION https://github.com/eprover/eprover.git

#----Set working directory to cloned sources directory
WORKDIR /eprover

#----Builds first-order executable
RUN ./configure --bindir=/artifacts && \
    make && \
    make install
RUN cp PROVER/eprover /artifacts/eprover

#----Builds higher-order executable
RUN ./configure --enable-ho && \
    make rebuild
RUN cp PROVER/eprover-ho /artifacts/eprover-ho

#----Add run_system script 
ADD run_system /artifacts/

#------------------------------------------------------------
