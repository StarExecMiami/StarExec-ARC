FROM ubuntu-build

RUN apt-get update && \
    apt-get install -y --no-install-recommends openjdk-8-jdk

######### Install SBT ############
RUN wget --no-check-certificate https://downloads.lightbend.com/scala/2.13.0/scala-2.13.0.deb
RUN dpkg -i scala-2.13.0.deb
ARG SBT_VERSION=1.6.2
# prevent this error: java.lang.IllegalStateException: cannot run sbt from root directory without -Dsbt.rootdir=true; see sbt/sbt#1458
WORKDIR /app
# Download and install SBT debian package
RUN curl -L -o sbt-$SBT_VERSION.deb https://repo.scala-sbt.org/scalasbt/debian/sbt-$SBT_VERSION.deb
RUN dpkg --configure -a && \
    dpkg --ignore-depends=bash -i sbt-$SBT_VERSION.deb
# Cleanup
RUN  rm sbt-$SBT_VERSION.deb
# Init SBT
RUN sbt sbtVersion

# Clones repository
ARG LEO3_VERSION=v1.7.0
RUN git clone --depth 1 --branch $LEO3_VERSION -c advice.detachedHead=false https://github.com/leoprover/Leo-III.git

# Set working directory to cloned sources directory
WORKDIR Leo-III

RUN make all
RUN cp bin/leo3* /artifacts/

RUN echo "### Working directory [$PWD] content:" && echo "$(ls $PWD)" && \
    echo "### Artifacts directory content:" && echo "$(ls /artifacts/)"

