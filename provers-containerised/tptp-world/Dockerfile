#------------------------------------------------------------
#----To build: podman build -t tptp-world .

FROM ubuntu-arc

#----Install necessary packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    libcurl4 \
    libcurl4-gnutls-dev \
    numactl \
    libnuma-dev \
    git \
    make \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

#----Set environment variable
ENV TPTP_HOME /

#----Clone and build TPTP tools
RUN git clone --recurse-submodules https://github.com/TPTPWorld/ServiceTools.git && \
    git clone --recurse-submodules https://github.com/TPTPWorld/TPTP4X.git && \
    cd ServiceTools/JJUsers && make SPCForProblem && \
    cd ../../TPTP4X && make tptp4X && \
    cp ServiceTools/JJUsers/SPCForProblem /artifacts/ && \
    cp TPTP4X/tptp4X /artifacts/ && \
    rm -rf ServiceTools TPTP4X

#----Clone and build runsolver
RUN git clone -n --depth=1 --branch containerised --filter=tree:0 https://github.com/StarExecMiami/StarExec.git && \
    cd StarExec && \
    git sparse-checkout set --no-cone src/org/starexec/config/sge/RunSolverSource && \
    git checkout && \
    cd src/org/starexec/config/sge/RunSolverSource && make clean && make && \
    cp runsolver /artifacts/ && \
    cd / && rm -rf StarExec

#----Clone and build ResourceLimitedRun
RUN git clone https://github.com/StarExecMiami/ResourceLimitedRun.git && \
    cd ResourceLimitedRun && make ResourceLimitedRun && \
    cp ResourceLimitedRun /artifacts/ && \
    cd / && rm -rf ResourceLimitedRun

#----Create necessary directories
RUN mkdir -p /benchmark /artifacts

WORKDIR /artifacts

#------------------------------------------------------------
