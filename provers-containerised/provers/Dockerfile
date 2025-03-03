#------------------------------------------------------------
#----To build, e.g., for E---3.0.03:
#----    podman build -t eprover:3.0.03-RLR --build-arg PROVER_IMAGE=eprover:3.0.03 .

ARG PROVER_IMAGE

FROM ${PROVER_IMAGE} AS builder
FROM tptp-world

ENV PATH=".:${PATH}"
WORKDIR /artifacts

# Copy artifacts from the builder stage
COPY --from=builder /artifacts/ /artifacts/

# Add GetComputerInfo for headers
ADD start_RLR /artifacts/

# Set the entrypoint to start_RLR
ENTRYPOINT ["start_RLR"]
#------------------------------------------------------------
