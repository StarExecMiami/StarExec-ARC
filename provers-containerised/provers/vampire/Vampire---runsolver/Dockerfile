FROM vampire-build AS builder
FROM tptp-world-build

ENV PATH=".:${PATH}"
WORKDIR /artifacts

# Vampire-specific stuff from ostensibly external image
COPY --from=builder /artifacts/vampire /artifacts/

# Add run_container script 
ADD run_system /artifacts/

# Add run_vampire script 
ADD run_vampire /artifacts/

# static binaries as an alternative
# ADD vampire_rel_static_ahmed-new-hol_6848 /artifacts/
# ADD vampire_z3_rel_static_master_6827 /artifacts/

ENTRYPOINT ["runsolver", "--timestamp"]
