#------------------------------------------------------------
# Variables
PROVERS           = eprover vampire leo3
EPROVER_VERSION   = 3.0.03
VAMPIRE_VERSION   = 4.8
LEO3_VERSION       = 1.7.0

# Raw sub‐dirs under ./provers
E_RAW_DIR         = E---$(EPROVER_VERSION)
V_RAW_DIR         = Vampire---$(VAMPIRE_VERSION)
L_RAW_DIR         = Leo-III---$(LEO3_VERSION)

#------------------------------------------------------------
# Functions to pick version or raw‑dir by prover name
define version_of
	$(if $(filter $1,eprover),$(EPROVER_VERSION),  \
	$(if $(filter $1,vampire),$(VAMPIRE_VERSION),  \
	$(if $(filter $1,leo3),$(LEO3_VERSION))))
endef

define raw_dir
	$(if $(filter $1,eprover),$(E_RAW_DIR),         \
	$(if $(filter $1,vampire),$(V_RAW_DIR),         \
	$(if $(filter $1,leo3),$(L_RAW_DIR))))
endef

#------------------------------------------------------------
# Phony targets
.PHONY: all base ubuntu-arc tptp-world provers           \
				$(PROVERS)                                       \
				$(addsuffix -RAW,$(PROVERS))                     \
				$(addsuffix -RLR,$(PROVERS))

# Default
all: base provers
	@echo "Now try 'run_image.py eprover:$(EPROVER_VERSION)-RLR -P PUZ001+1.p'"

# Build base images
base: ubuntu-arc tptp-world

ubuntu-arc:
	podman build -t ubuntu-arc ./ubuntu-arc

tptp-world: ubuntu-arc
	podman build -t tptp-world ./tptp-world

#------------------------------------------------------------
# Generate each prover’s RAW, RLR and shortcut targets
provers: $(PROVERS)

$(PROVERS): %: %-RLR

%-RAW: ubuntu-arc
	podman build \
		-t $@:$(call version_of,$@) \
		./provers/$(call raw_dir,$@)

%-RLR: %-RAW tptp-world
	podman build \
		-t $@:$(call version_of,$*)-RLR \
		--build-arg PROVER_IMAGE=$*:$(call version_of,$*) \
		./provers

