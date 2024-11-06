#------------------------------------------------------------
#----To build: podman build -t tptp-world .

FROM ubuntu-arc

#----Installs 
RUN apt-get update && apt-get install -y --no-install-recommends libcurl4 libcurl4-gnutls-dev numactl libnuma-dev

#----Build tptp stuff. 
RUN git clone --recurse-submodules https://github.com/TPTPWorld/ServiceTools.git
RUN git clone --recurse-submodules https://github.com/TPTPWorld/TPTP4X.git

ENV TPTP_HOME /
RUN cd ServiceTools/JJUsers && make SPCForProblem 
RUN cd TPTP4X && make tptp4X
#----/artifacts is where we put all relevant executables and is the working dir.
#----It is created in ubuntu-build
RUN cp ServiceTools/JJUsers/SPCForProblem /artifacts/
RUN cp TPTP4X/tptp4X /artifacts/

#----Build runsolver
# RUN wget --no-check-certificate https://www.cril.univ-artois.fr/~roussel/runsolver/runsolver-3.4.1.tar.bz2
# RUN tar -xjf runsolver-3.4.1.tar.bz2 
# WORKDIR /runsolver/src
#----runsolver is old and broken - hacking workarounds
# RUN sed -i -e "s/CFLAGS=/CFLAGS=-fpermissive /" Makefile
# RUN make
# RUN cp /runsolver/src/runsolver /artifacts/

# Instead get it from here: https://github.com/StarExecMiami/StarExec/tree/pullingUpdates/src/org/starexec/config/sge/RunSolverSource
RUN git clone -n --depth=1 --branch pullingUpdates --filter=tree:0 https://github.com/StarExecMiami/StarExec.git
WORKDIR StarExec
RUN git sparse-checkout set --no-cone src/org/starexec/config/sge/RunSolverSource
RUN git checkout
RUN cd src/org/starexec/config/sge/RunSolverSource && make clean && make
RUN cp src/org/starexec/config/sge/RunSolverSource/runsolver /artifacts/

#----Build RLR
RUN git clone https://github.com/StarExecMiami/ResourceLimitedRun.git
RUN cd ResourceLimitedRun && make ResourceLimitedRun
RUN cp ResourceLimitedRun/ResourceLimitedRun /artifacts/

#----Cleanup - necessary because this is the base for all the -RLR container images
WORKDIR /
RUN rm -rf ServiceTools TPTP4X

#----/benchmark is where we put the TPTP problem.
RUN mkdir -p /benchmark

WORKDIR /artifacts

#------------------------------------------------------------
