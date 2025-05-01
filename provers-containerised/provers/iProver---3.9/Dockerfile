#------------------------------------------------------------
#----To build: podman build --no-cache -t iprover:3.9.2 .
FROM ubuntu-arc

# Install python3
## RUN curl -fsSL https://pyenv.run | bash
## RUN export PYENV_ROOT="/root/.pyenv" && \
##     export PATH="$PYENV_ROOT/bin:$PATH" && \
##     echo "export PATH=$PYENV_ROOT/bin:$PATH" >> ~.bash_profile && \
##     echo "export PATH=$PYENV_ROOT/bin:$PATH" >> ~/.profile && \
##     echo "export PATH=$PYENV_ROOT/bin:$PATH" >> ~/.bashrc && \
##     eval "$(pyenv init - bash)" && \
##     # pyenv install -l
##     pyenv install 3.11.12 && \
##     pyenv global 3.11.12

# Install opam
RUN apt update && \
    apt install -y --no-install-recommends opam && \
    opam init && \
    eval $(opam env) && \
    opam update && \
    opam switch create 4.14.2+flambda ocaml-variants.4.14.2+options ocaml-option-flambda && \
    opam install ocamlfind ocamlgraph zarith yojson z3 && \
    eval $(opam env)

# Install iprover
RUN git clone https://gitlab.com/korovin/iprover.git
# Set working directory to cloned sources directory
WORKDIR iprover

RUN ./configure
RUN make

# Smoke test
RUN ./tests_run.sh
RUN ./tests_run.sh -c iproveropt-multi-core.sh -t 10 -o '-n'
#RUN  make # version with z3
#RUN  make z3=false # version without z3

#----Add SPCForProblem script 
ADD SPCForProblem /artifacts/

#----Add run_system script 
ADD run_system /artifacts/

#------------------------------------------------------------
