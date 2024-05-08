#------------------------------------------------------------
.PHONY: base provers eprover iprover leo3 vampire

#----Current versions of each prover as variables:
EPROVER_VERSION = 3.0.03
VAMPIRE_VERSION = 4.8
LEO3_VERSION = 1.7.0

#------------------------------------------------------------
#----High level targets 
all: base provers
	echo "Now try 'run_image.py eprover:3.0.03-RLR -P PUZ001+1.p -C 60'"

base: ubuntu-arc tptp-world

provers: eprover leo3 vampire

#------------------------------------------------------------
#----Prerequisite targets 
ubuntu-arc:
	podman build -t ubuntu-arc ./ubuntu-arc

tptp-world: ubuntu-arc
	podman build -t tptp-world ./tptp-world

scala-build:
	podman build -t scala-build ./base-build/scala-build

#------------------------------------------------------------
#----Targets for each prover 

#---Eprover targets 
eprover: eprover-RLR

eprover-RLR: eprover-RAW tptp-world
	podman build -t eprover:$(EPROVER_VERSION)-RLR --build-arg PROVER_IMAGE=eprover:$(EPROVER_VERSION) ./provers

eprover-RAW: ubuntu-arc
	podman build -t eprover:$(EPROVER_VERSION) ./provers/E---$(EPROVER_VERSION)


#----Vampire targets
vampire: vampire-RLR

vampire-RLR: vampire-RAW tptp-world
	podman build -t vampire:$(VAMPIRE_VERSION)-RLR --build-arg PROVER_IMAGE=vampire:$(VAMPIRE_VERSION) ./provers

vampire-RAW: ubuntu-arc
	podman build -t vampire:$(VAMPIRE_VERSION) ./provers/Vampire---$(VAMPIRE_VERSION)


#----Leo3 targets
leo3: leo3-RLR

leo3-RLR: leo3-RAW tptp-world
	podman build -t leo3:$(LEO3_VERSION)-RLR --build-arg PROVER_IMAGE=leo3:$(LEO3_VERSION) ./provers

leo3-RAW: 
	podman build -t leo3:$(LEO3_VERSION) ./provers/Leo-III---$(LEO3_VERSION)

#------------------------------------------------------------
