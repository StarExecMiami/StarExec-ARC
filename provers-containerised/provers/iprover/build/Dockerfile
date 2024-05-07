FROM ocaml-build

# Install python3
RUN sudo apt-get install -y --no-install-recommends python3

RUN opam install z3

# Update the current shell environment
RUN eval $(opam env)

ARG IPROVER_BRANCH=master

RUN git clone --depth 1 --branch $IPROVER_BRANCH https://gitlab.com/korovin/iprover.git

# Set working directory to cloned sources directory
WORKDIR iprover

#RUN ./configure
#RUN  make # version with z3
#RUN  make z3=false # version without z3

# Create "artifacts/" directory for build artifacts
#RUN sudo mkdir artifacts/

# Smoke tests
#RUN ./iproveropt Examples/problem.p | grep "SZS status Unsatisfiable"
#RUN echo "Working directory [$PWD] content:" && echo "$(ls $PWD)"
