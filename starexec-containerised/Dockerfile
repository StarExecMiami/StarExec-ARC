FROM ubuntu:latest

ENV LANG=en_US.UTF-8

# Copy 
ADD --chmod=0777 ./dockerPackage/configFiles ./configFiles
ADD --chmod=0755 ./dockerPackage/solverAdditions ./solverAdditions


# Install sudo 
RUN apt-get update && \
    apt-get install -y sudo && \
    rm -rf /var/lib/apt/lists/*


# Weird Unicode stuff...
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y locales
RUN sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
    dpkg-reconfigure --frontend=noninteractive locales && \
    update-locale LANG=en_US.UTF-8
ENV LANG en_US.UTF-8 

# Run OS scripts
ADD --chmod=0755 ./dockerPackage/allScripts/osScripts ./allScripts/osScripts
RUN allScripts/osScripts/installOsDeps.sh
RUN allScripts/osScripts/SetupUsers.sh

# Run Starexec scripts
ADD --chmod=0755 ./dockerPackage/allScripts/starexecScripts ./allScripts/starexecScripts
RUN ls -la allScripts/starexecScripts/

RUN allScripts/starexecScripts/JavaSassAntInstall.sh
RUN allScripts/starexecScripts/CloneStarexecRepo.sh
RUN allScripts/starexecScripts/AddMachineSpecs.sh
RUN allScripts/starexecScripts/ConfigTomcat7.sh
RUN allScripts/starexecScripts/MariaDbconfig.sh
RUN allScripts/starexecScripts/HttpdConfigAndRun.sh
RUN allScripts/starexecScripts/SetupStarexecOverrideProps.sh
RUN allScripts/starexecScripts/UpdateSudoRules.sh
RUN allScripts/starexecScripts/AddRunsolverAndComputerInfo.sh


# Run container build scripts
ADD --chmod=0755 ./dockerPackage/allScripts/dockerScripts ./allScripts/dockerScripts
RUN allScripts/dockerScripts/DockerAppBuild.sh

EXPOSE 80
EXPOSE 443

CMD allScripts/dockerScripts/DockerRun.sh
