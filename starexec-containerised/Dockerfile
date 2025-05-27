# ---------------------------
# Stage 1: Build runsolver
# ---------------------------
FROM debian:sid-slim AS builder

LABEL maintainer="Starexec Team"
ENV DEPLOY_DIR=/home/starexec/StarExec-deploy

# Install build dependencies efficiently
RUN apt update && \
    apt install -y --no-install-recommends --no-install-suggests \
      build-essential \
      make \
      gcc \
      g++ \
      libnuma-dev \
      iputils-ping \
      git && \
    # Clean up
    apt clean && \
    rm -rf /var/lib/apt/lists/*

# Clone StarExec repository specifically for runsolver
RUN git -c http.sslVerify=false clone -b containerised --single-branch https://github.com/StarexecMiami/StarExec.git ${DEPLOY_DIR}

# Build runsolver
WORKDIR ${DEPLOY_DIR}/src/org/starexec/config/sge/RunSolverSource
# Ensure clean build environment
RUN make clean && make

# ---------------------------
# Stage 2: Final runtime
# ---------------------------
FROM ubuntu:22.04

LABEL maintainer="Starexec Team"

ENV DEBIAN_FRONTEND=noninteractive \
    TOMCAT_VERSION=7.0.109 \
    MYSQL_CON_VERSION=8.0.30 \
    DB_NAME=starexec \
    DB_USER=se_admin \
    DB_PASS=dfsdf34RFerfg3TFGRfrF3edFVg12few2 \
    DEPLOY_DIR=/home/starexec/StarExec-deploy \
    SQL_FILE=/home/starexec/StarExec-deploy/sql/NewInstall.sql \
    BUILD_FILE=build.xml \
    SSH_USERNAME=starexec \
    HOST_MACHINE=localhost \
    SSH_PORT=22 \
    SOCKET_PATH=/run/user/1000/podman/podman.sock \
    LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8 \
    JAVA_TOOL_OPTIONS="-Dfile.encoding=UTF-8" \
    TZ=UTC

# ---------------------------
# Install system packages and dependencies
# ---------------------------

# Combine package installation, configuration, and cleanup
RUN apt update && \
    apt install -y --no-install-recommends --no-install-suggests \
    # Runtime dependencies
    ca-certificates tzdata sudo git unzip file apache2 tcsh libnuma-dev \
    openssl dnsutils curl ant ant-optional mariadb-client mariadb-server podman locales vim acl \
    # SSH client for Podman communication
    openssh-client \
    # Tools needed for setup/runtime scripts
    procps \
    # Install specific JDK version (Temurin 16)
    && mkdir -p /usr/lib/jvm && \
    curl -fsSL -o /tmp/jdk16.tar.gz https://github.com/adoptium/temurin16-binaries/releases/download/jdk-16.0.2%2B7/OpenJDK16U-jdk_x64_linux_hotspot_16.0.2_7.tar.gz && \
    tar xzf /tmp/jdk16.tar.gz -C /usr/lib/jvm && \
    rm /tmp/jdk16.tar.gz && \
    # Set Java alternatives
    update-alternatives --install /usr/bin/java java /usr/lib/jvm/jdk-16.0.2+7/bin/java 1 && \
    update-alternatives --install /usr/bin/javac javac /usr/lib/jvm/jdk-16.0.2+7/bin/javac 1 && \
    # Configure timezone and locales
    ln -fs /usr/share/zoneinfo/UTC /etc/localtime && \
    echo "UTC" > /etc/timezone && \
    dpkg-reconfigure -f noninteractive tzdata && \
    sed -i 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/g' /etc/locale.gen && \
    locale-gen en_US.UTF-8 && \
    # Install Node.js and Sass
    curl -fsSL https://deb.nodesource.com/setup_20.x | bash - && \
    apt install -y --no-install-recommends nodejs && \
    npm install -g npm@latest && \
    npm install -g sass && \
    # Clean up apt cache and lists
    apt clean && \
    rm -rf /var/lib/apt/lists/*

# ---------------------------
# Configure application directories and users
# ---------------------------

# Configure Apache2
COPY dockerPackage/configFiles/ssl.conf /etc/apache2/sites-available/
COPY dockerPackage/configFiles/starexec.conf /etc/apache2/sites-available/
RUN a2dissite 000-default.conf default-ssl.conf && \
    a2ensite ssl starexec && \
    a2enmod ssl proxy headers proxy_http rewrite && \
    mkdir -p /etc/apache2/logs/ && \
    echo "ServerName localhost" >> /etc/apache2/apache2.conf

# Configure Tomcat
RUN mkdir -p /project && cd /project && \
    curl -fsSL https://archive.apache.org/dist/tomcat/tomcat-7/v${TOMCAT_VERSION}/bin/apache-tomcat-${TOMCAT_VERSION}.tar.gz | tar -xz && \
    mv apache-tomcat-${TOMCAT_VERSION} apache-tomcat-7 && \
    curl -fsSL -o /project/apache-tomcat-7/lib/mysql-connector-java-${MYSQL_CON_VERSION}.jar \
    https://search.maven.org/remotecontent?filepath=mysql/mysql-connector-java/${MYSQL_CON_VERSION}/mysql-connector-java-${MYSQL_CON_VERSION}.jar

# Create groups and users
RUN groupadd -g 160 star-web && \
    groupadd -g 153 tomcat && \
    groupadd -g 111 sandbox && \
    groupadd -g 112 sandbox2 && \
    useradd -r -m -d /home/tomcat -s /bin/bash -c "Tomcat User" -u 153 -g 160 tomcat && \
    useradd -r -m -d /home/starexec -s /bin/bash -c "Starexec User" -u 152 -g 160 starexec && \
    useradd -r -m -d /home/sandbox -s /bin/bash -c "Cluster UserOne" -u 111 -g 111 sandbox && \
    useradd -r -m -d /home/sandbox2 -s /bin/bash -c "Cluster UserTwo" -u 112 -g 112 sandbox2 && \
    usermod -aG star-web sandbox && \
    usermod -aG star-web sandbox2 && \
    usermod -aG star-web tomcat && \
    usermod -aG star-web starexec

# Configure directories and permissions
RUN mkdir -p /export/starexec/sandbox /export/starexec/sandbox2 && \
    chown -R tomcat:star-web /export/starexec && \
    mkdir -p /local/sandbox /local/sandbox2 && \
    chown sandbox:sandbox /local/sandbox && \
    chown sandbox2:sandbox2 /local/sandbox2 && \
    chmod 770 /local/sandbox /local/sandbox2 && \
    chmod g+s /local/sandbox /local/sandbox2 && \
    usermod -aG sandbox tomcat && \
    usermod -aG sandbox2 tomcat

# Apply container-friendly permissions from script logic
RUN echo "Setting up container-friendly permissions..." && \
    echo "Configuring ACLs for sandbox directories (errors ignored)..." && \
    setfacl -d -m g::rwx /local/sandbox/ 2>/dev/null || true && \
    setfacl -d -m g::rwx /local/sandbox2/ 2>/dev/null || true && \
    setfacl -d -m u::rwx /local/sandbox/ 2>/dev/null || true && \
    setfacl -d -m u::rwx /local/sandbox2/ 2>/dev/null || true

RUN echo "Configure umask for sandbox users (errors ignored)..." && \
    (echo "umask 002" >> /home/sandbox/.bashrc 2>/dev/null || true) && \
    (echo "umask 002" >> /home/sandbox2/.bashrc 2>/dev/null || true)

RUN echo "Create temporary directory with relaxed permissions for archive extraction..." && \
    mkdir -p /tmp/starexec-temp && \
    chmod 777 /tmp/starexec-temp && \
    chown tomcat:star-web /tmp/starexec-temp && \
    echo "Container permissions configured successfully"

COPY dockerPackage/allScripts/starexecScripts/overrides.properties /tmp/
COPY dockerPackage/allScripts/starexecScripts/sudoRules.txt /etc/sudoers.d/starexec
COPY dockerPackage/solverAdditions/GetComputerInfo /home/starexec/bin/
RUN git -c http.sslVerify=false clone -b containerised --single-branch https://github.com/StarexecMiami/StarExec.git ${DEPLOY_DIR} && \
    git config --global --add safe.directory ${DEPLOY_DIR} && \
    cd ${DEPLOY_DIR}/WebContent/css/details && ln -s ../shared && \
    chown -R tomcat:star-web /home/starexec && \
    # Configure overrides and machine specs
    mkdir -p ${DEPLOY_DIR}/build && \
    touch ${DEPLOY_DIR}/build/Cluster.MachineSpecs.txt && \
    chown starexec:star-web ${DEPLOY_DIR}/build/Cluster.MachineSpecs.txt && \
    touch ${DEPLOY_DIR}/build/overrides.properties && \
    cat /tmp/overrides.properties >> ${DEPLOY_DIR}/build/overrides.properties && \
    chown starexec:star-web ${DEPLOY_DIR}/build/overrides.properties && \
    rm /tmp/overrides.properties && \
    # Configure sudo
    chmod 0440 /etc/sudoers.d/starexec && \
    # visudo check removed for non-interactive build, ensure syntax is correct
    # Configure GetComputerInfo
    mkdir -p /home/starexec/bin && \
    chown tomcat:star-web /home/starexec/bin && \
    chmod 755 /home/starexec/bin && \
    chown tomcat:star-web /home/starexec/bin/GetComputerInfo && \
    chmod 755 /home/starexec/bin/GetComputerInfo

# Copy the compiled runsolver from the builder stage
COPY --from=builder ${DEPLOY_DIR}/src/org/starexec/config/sge/RunSolverSource/runsolver ${DEPLOY_DIR}/src/org/starexec/config/sge/

# Install kubectl and clean up in one layer
RUN ARCH=$(dpkg --print-architecture) && \
    curl -fsSLO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/${ARCH}/kubectl" && \
    chmod +x ./kubectl && \
    install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl && \
    rm kubectl

# ---------------------------
# Setup runtime directories and permissions
# ---------------------------

# Setup SSL certificate directories and permissions
RUN mkdir -p /etc/ssl/certs /etc/ssl/private && \
    chmod 755 /etc/ssl/certs && \
    chmod 700 /etc/ssl/private

# Initialize MySQL data directory with proper permissions
RUN mkdir -p /var/lib/mysql && \
    chown -R mysql:mysql /var/lib/mysql && \
    chmod 755 /var/lib/mysql

# SSH key setup for Podman (key mounted at runtime)
RUN mkdir -p /root/.ssh && chmod 700 /root/.ssh && \
    # Create SSH directories for sandbox users
    mkdir -p /home/sandbox/.ssh /home/sandbox/.config /home/sandbox/.local && \
    mkdir -p /home/sandbox2/.ssh /home/sandbox2/.config /home/sandbox2/.local && \
    chmod 700 /home/sandbox/.ssh /home/sandbox2/.ssh && \
    chown -R sandbox:sandbox /home/sandbox/.ssh /home/sandbox/.config /home/sandbox/.local && \
    chown -R sandbox2:sandbox2 /home/sandbox2/.ssh /home/sandbox2/.config /home/sandbox2/.local

# Set up base permissions for runtime directories
RUN chown -R tomcat:star-web /project && \
    chown -R tomcat:star-web /home/starexec && \
    chmod 755 -R /home/starexec

# ---------------------------
# Final setup and entrypoint
# ---------------------------

# Copy initialization script
COPY init-starexec.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/init-starexec.sh

# Expose necessary ports
EXPOSE 80 443 3306 8080

WORKDIR ${DEPLOY_DIR}

CMD ["/usr/local/bin/init-starexec.sh"]
