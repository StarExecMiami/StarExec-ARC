#------------------------------------------------------------
#----To build, e.g., for E---3.0.03:
#----    podman build -t eprover:3.0.03-RLR --build-arg PROVER_IMAGE=eprover:3.0.03 .

ARG PROVER_IMAGE

FROM ${PROVER_IMAGE} AS builder
FROM tptp-world

ENV PATH=".:${PATH}"
WORKDIR /artifacts

# System specific stuff 
COPY --from=builder /artifacts/* /artifacts/

#ENTRYPOINT ["ResourceLimitedRun"]
ENTRYPOINT ["runsolver"]
#------------------------------------------------------------
