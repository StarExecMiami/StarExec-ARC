# Base image
FROM ubuntu:22.04

# Maintainer
LABEL maintainer="Starexec Team"

# Arguments
ARG DB_USER
ARG DB_PASS

# Environment variables
ENV DEBIAN_FRONTEND=noninteractive \
    TOMCAT_VERSION=7.0.90 \
    MYSQL_CON_VERSION=8.0.30 \
    DB_NAME=starexec \
    DB_USER=${DB_USER} \
    DB_PASS=${DB_PASS} \
    DEPLOY_DIR=/home/starexec/StarExec-deploy
ENV SQL_FILE=${DEPLOY_DIR}/sql/NewInstall.sql \
    BUILD_FILE=build.xml \
    SSH_USERNAME=starexec \
    HOST_MACHINE=localhost \
    SSH_PORT=22 \
    SOCKET_PATH=/run/user/1000/podman/podman.sock

# Update system and install dependencies
RUN apt-get update --fix-missing && apt-get upgrade -y && \
    apt-get install -y --no-install-recommends --no-install-suggests \
    apt-utils sudo git unzip file apache2 tcsh libnuma-dev \
    build-essential libssl-dev openssl dnsutils ca-certificates \
    openjdk-11-jdk curl ant ant-optional gcc g++ make mariadb-client \
    mariadb-server podman locales && \
    a2enmod ssl && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Install and configure locales
RUN sed -i 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/g' /etc/locale.gen && \
    locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8 \
    JAVA_TOOL_OPTIONS="-Dfile.encoding=UTF-8"

# Generate local SSL key and certificate
RUN printf "[dn]\nCN=localhost\n[req]\ndistinguished_name = dn\n[EXT]\nsubjectAltName=DNS:localhost\nkeyUsage=digitalSignature\nextendedKeyUsage=serverAuth" > /tmp/openssl.cnf && \
    openssl req -x509 -out /etc/ssl/certs/localhost.crt -keyout /etc/ssl/private/localhost.key \
    -newkey rsa:2048 -nodes -sha256 \
    -subj '/CN=localhost' -extensions EXT -config /tmp/openssl.cnf && \
    rm /tmp/openssl.cnf && \
    echo 'Key and certificate created and moved to appropriate directories'

# Install Node.js and Sass
RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && \
    apt-get install -y nodejs --no-install-recommends --no-install-suggests && \
    npm install -g sass

# Configure Apache2
COPY dockerPackage/configFiles/ssl.conf /etc/apache2/sites-available/
COPY dockerPackage/configFiles/starexec.conf /etc/apache2/sites-available/
RUN a2dissite 000-default.conf default-ssl.conf && \
    a2ensite ssl starexec && \
    a2enmod proxy headers proxy_http rewrite && \
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
    useradd -r -m -d /home/tomcat -s /bin/bash -c "Tomcat User" -u 153 -g 160 tomcat && \
    useradd -r -m -d /home/starexec -s /bin/bash -c "Starexec User" -u 152 -g 160 starexec && \
    useradd -r -m -d /home/sandbox -s /bin/bash -c "Cluster UserOne" -u 111 sandbox && \
    useradd -r -m -d /home/sandbox2 -s /bin/bash -c "Cluster UserTwo" -u 112 sandbox2 && \
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

# Clone StarExec repository
RUN su - starexec -c "git clone -b UMprod --single-branch https://github.com/StarexecMiami/StarExec.git ${DEPLOY_DIR}" && \
    git config --global --add safe.directory ${DEPLOY_DIR} && \
    cd ${DEPLOY_DIR}/WebContent/css/details && ln -s ../shared && \
    chown -R tomcat:star-web /home/starexec

COPY dockerPackage/allScripts/starexecScripts/overridesproperties.txt /tmp/
# Configure StarExec
RUN mkdir -p ${DEPLOY_DIR}/build && \
    touch ${DEPLOY_DIR}/build/Cluster.MachineSpecs.txt && \
    chown starexec:star-web ${DEPLOY_DIR}/build/Cluster.MachineSpecs.txt && \
    touch ${DEPLOY_DIR}/build/overrides.properties && \
    cat /tmp/overridesproperties.txt >> ${DEPLOY_DIR}/build/overrides.properties && \
    chown starexec:star-web ${DEPLOY_DIR}/build/overrides.properties && \
    rm /tmp/overridesproperties.txt

# Configure sudo
COPY dockerPackage/allScripts/starexecScripts/sudoRules.txt /etc/sudoers.d/starexec
RUN chmod 0440 /etc/sudoers.d/starexec && \
    visudo -c -f /etc/sudoers.d/starexec

# Configure GetComputerInfo and runsolver
RUN mkdir -p /home/starexec/bin && \
    chown tomcat:star-web /home/starexec/bin && \
    chmod 755 /home/starexec/bin
COPY dockerPackage/solverAdditions/GetComputerInfo /home/starexec/bin/
RUN chown tomcat:star-web /home/starexec/bin/GetComputerInfo && \
    chmod 755 /home/starexec/bin/GetComputerInfo
WORKDIR ${DEPLOY_DIR}/src/org/starexec/config/sge/RunSolverSource
RUN make clean && make && \
    cp runsolver ${DEPLOY_DIR}/src/org/starexec/config/sge/

# Install kubectl
RUN if [ "$(uname -m)" = "x86_64" ]; then \
        curl -fsSLO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"; \
    else \
        curl -fsSLO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/arm64/kubectl"; \
    fi && \
    chmod +x ./kubectl && \
    install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl && \
    rm kubectl

# Copy initialization script
COPY init-starexec.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/init-starexec.sh

# Copy SSH key for Podman
COPY starexec_podman_key /root/.ssh/starexec_podman_key
RUN chmod 600 /root/.ssh/starexec_podman_key

# Expose necessary ports
EXPOSE 443 8080 3306

WORKDIR ${DEPLOY_DIR}

# Command to start services
CMD ["/usr/local/bin/init-starexec.sh"]
