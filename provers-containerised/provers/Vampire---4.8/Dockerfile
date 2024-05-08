#------------------------------------------------------------
#----To build: podman build -t vampire:4.8 .

FROM ubuntu-arc

#----Clone repository
RUN git clone --depth 1 --recurse-submodules --shallow-submodules https://github.com/vprover/vampire.git

#----Set working directory to cloned sources directory
WORKDIR vampire

#----Build Z3 
RUN mkdir -p z3/build 
WORKDIR z3/build
#----Configure single-threaded build, no debug symbols
RUN cmake .. -DZ3_BUILD_LIBZ3_SHARED=FALSE -DZ3_SINGLE_THREADED=1 -DCMAKE_BUILD_TYPE=Release 
# ; cat /vampire/z3/build/CMakeFiles/CMakeOutput.log
RUN make

WORKDIR vampire
RUN mkdir -p /tmp/build && cd /tmp/build
RUN cmake /vampire -DBUILD_SHARED_LIBS=0
RUN make
RUN cp bin/vampire* /artifacts/vampire

#----Static binaries as an alternative
ADD vampire_rel_static_ahmed-new-hol_6848 /artifacts/
ADD vampire_z3_rel_static_master_6827 /artifacts/

#----Add run_system script 
ADD run_system /artifacts/

#------------------------------------------------------------
