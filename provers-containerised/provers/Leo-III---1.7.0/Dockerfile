#------------------------------------------------------------
#----To build: podman build -t leo3:1.7.0 .
FROM ubuntu-arc

#----Install SBT and Scala
ARG SCALA_VERSION=2.13.0
ARG SBT_VERSION=1.6.2

RUN apt-get update && apt-get install -y wget curl git make && \
    wget --no-check-certificate https://downloads.lightbend.com/scala/$SCALA_VERSION/scala-$SCALA_VERSION.deb && \
    dpkg -i scala-$SCALA_VERSION.deb && \
    curl -L -o sbt-$SBT_VERSION.deb https://repo.scala-sbt.org/scalasbt/debian/sbt-$SBT_VERSION.deb && \
    dpkg --configure -a && \
    dpkg --ignore-depends=bash -i sbt-$SBT_VERSION.deb && \
    rm scala-$SCALA_VERSION.deb sbt-$SBT_VERSION.deb

#----Prevent this error: java.lang.IllegalStateException: cannot run sbt from 
#----root directory without -Dsbt.rootdir=true; see sbt/sbt#1458
WORKDIR /app

#----Init SBT
RUN sbt sbtVersion

#----Clone repository and build
ARG LEO3_VERSION=v1.7.0
RUN git clone --depth 1 --branch $LEO3_VERSION -c advice.detachedHead=false https://github.com/leoprover/Leo-III.git && \
    cd Leo-III && \
    make all && \
    cp bin/leo3* /artifacts/

#----Add run_system script
ADD run_system /artifacts/

#------------------------------------------------------------
