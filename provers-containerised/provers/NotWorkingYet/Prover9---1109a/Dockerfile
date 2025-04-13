#------------------------------------------------------------
#----To build: podman build --no-cache -t prover9:1109a .
FROM ubuntu-arc

#----Get sources
RUN apt update && apt install -y wget make && \
    wget --no-check-certificate https://www.cs.unm.edu/~mccune/prover9/download/LADR-2009-11A.tar.gz && \
    tar xzf LADR-2009-11A.tar.gz && rm LADR-2009-11A.tar.gz && \
    cd LADR-2009-11A && \
    make all && \
    cp bin/prover9 /artifacts/

#----Add run_system script
ADD run_system /artifacts/

#------------------------------------------------------------
