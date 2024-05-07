FROM scala-build

ARG LEO3_VERSION=v1.7.0

RUN git clone --depth 1 --branch $LEO3_VERSION https://github.com/leoprover/Leo-III.git

# Set working directory to cloned sources directory
WORKDIR Leo-III

RUN make all
RUN cp bin/leo3* /artifacts/

# Smoke tests
RUN echo "############ Smoke tests ############" && \
    /artifacts/leo3 $PWD/demo/ho/sur_cantor.p | grep "SZS status Theorem" && \
    /artifacts/leo3 $PWD/demo/poly/sur_cantor_th1.p | grep "SZS status Theorem"

RUN echo "### Working directory [$PWD] content:" && echo "$(ls $PWD)" && \
    echo "### Artifacts directory content:" && echo "$(ls /artifacts/)"


