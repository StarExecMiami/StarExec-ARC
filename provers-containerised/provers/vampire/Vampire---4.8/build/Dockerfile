FROM ubuntu-build

RUN git clone --depth 1 --recurse-submodules --shallow-submodules https://github.com/vprover/vampire.git

# Set working directory to cloned sources directory
WORKDIR vampire

# Build Z3 into vampire/z3/build
RUN mkdir -p z3/build 
WORKDIR z3/build

# Configure single-threaded build, no debug symbols
RUN cmake .. -DZ3_BUILD_LIBZ3_SHARED=FALSE -DZ3_SINGLE_THREADED=1 -DCMAKE_BUILD_TYPE=Release ; cat /vampire/z3/build/CMakeFiles/CMakeOutput.log

# Build Z3, in this case with make(1)
RUN make

WORKDIR vampire

RUN mkdir -p /tmp/build && cd /tmp/build

RUN cmake /vampire -DBUILD_SHARED_LIBS=0

RUN make

RUN cp bin/vampire* /artifacts/vampire

# Smoke tests
RUN echo "############ Smoke tests ############" && \
    /artifacts/vampire* /vampire/regressions/problems/tptp_out_intro_ssat.p | grep "SZS status Unsatisfiable"

RUN echo "### Working directory [$PWD] content:" && echo "$(ls $PWD)" && \
    echo "### Artifacts directory content:" && echo "$(ls /artifacts/)" && \
    echo -n "!!! " && /artifacts/vampire --version


