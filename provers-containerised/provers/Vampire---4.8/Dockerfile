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

#----Build Vampire
WORKDIR vampire
RUN mkdir -p build && cd build
RUN cmake /vampire -DBUILD_SHARED_LIBS=0
RUN make
RUN cp bin/vampire* /artifacts/vampire
RUN cd / && rm -rf build && rm -rf vampire

#----Build Vampire HO
WORKDIR /
RUN git clone --branch ahmed-new-hol --depth 1 --recurse-submodules --shallow-submodules https://github.com/vprover/vampire.git
WORKDIR vampire
RUN mkdir -p build && cd build
RUN cmake /vampire -DCMAKE_BUILD_HOL=On -DCMAKE_DISABLE_FIND_PACKAGE_Z3=ON
RUN make vampire
RUN cp bin/vampire* /artifacts/vampire-ho
RUN cd / && rm -rf build && rm -rf vampire

#----Add run_system script 
ADD run_system /artifacts/

#------------------------------------------------------------
