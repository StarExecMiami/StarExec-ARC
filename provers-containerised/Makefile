.PHONY: base provers eprover iprover leo3 vampire

# Current versions of each prover as variables:
EPROVER_VERSION = 3.0.03
VAMPIRE_VERSION = 4.8
LEO3_VERSION = 1.7.0

# High level targets ########################################################
all: base provers

base: ubuntu-arc tptp-world

provers: eprover 
# leo3 vampire

# Prerequisite targets ######################################################
ubuntu-arc:
	podman build -t ubuntu-arc .//ubuntu-arc

#scala-build:
#	podman build -t scala-build ./base-build/scala-build

tptp-world: ubuntu-arc
	podman build -t tptp-world ./tptp-world

#############################################################################
# Targets for each prover ###################################################
#############################################################################

# Eprover targets: #########################################################
eprover: ubuntu-arc eprover-RAW eprover-RLR

eprover-RAW: tptp-world
	podman build -t eprover:$(EPROVER_VERSION) ./provers/E---$(EPROVER_VERSION)

eprover-RLR: eprover-RAW
	podman build -t eprover:$(EPROVER_VERSION)-RLR --build-arg PROVER_IMAGE=eprover:$(EPROVER_VERSION) ./provers


# Vampire targets: ###########################################################
vampire: ubuntu-arc vampire-build vampire-runsolver

vampire-build: 
	podman build -t vampire-build ./provers/vampire/Vampire---$(VAMPIRE_VERSION)/build

vampire-runsolver: 
	podman build -t vampire:$(VAMPIRE_VERSION)-runsolver ./provers/vampire/Vampire---runsolver


# Leo3 targets: #############################################################
leo3: leo3-build leo3-runsolver

leo3-build: 
	podman build -t leo3-build ./provers/leo3/Leo-III---$(LEO3_VERSION)/build

leo3-runsolver: 
	podman build -t leo3:$(LEO3_VERSION)-runsolver ./provers/leo3/Leo-III---runsolver

