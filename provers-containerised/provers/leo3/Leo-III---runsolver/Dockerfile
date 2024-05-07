FROM leo3-build AS builder
FROM tptp-world-build

RUN apt-get update && \
    apt-get install -y --no-install-recommends openjdk-8-jre

ENV PATH=".:${PATH}"
WORKDIR /artifacts

# Leo-III-specific stuff from ostensibly external image
COPY --from=builder /artifacts/leo3* /artifacts/

# run_container script 
ADD run_system /artifacts/

# run_Leo-III script 
ADD run_Leo-III /artifacts/

ENTRYPOINT ["runsolver", "--timestamp"]
