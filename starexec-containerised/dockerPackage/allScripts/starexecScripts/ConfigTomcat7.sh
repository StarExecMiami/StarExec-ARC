#!/bin/bash
set -e
set -o pipefail

echo "making directory for project"
sudo mkdir /project
cd /project

# makes project folder and installs tomcat on it
echo "unzipping tomcat7 from starexec repo clone (to extract libs)"
sudo unzip ~starexec/StarExec-deploy/distribution/apache-tomcat-7.0.64.zip
# sudo ln -s /project/apache-tomcat-7.0.64 /project/apache-tomcat-7
echo "Done unzipping"

# download and sets up newer tomcat version (and then copying lib from repo)
echo "getting and downloading latest version of tomcat7"

TOMCAT_VERSION=7.0.94
wget https://archive.apache.org/dist/tomcat/tomcat-7/v${TOMCAT_VERSION}/bin/apache-tomcat-${TOMCAT_VERSION}.tar.gz
sudo tar --no-same-permissions --no-same-owner -xzvf apache-tomcat-${TOMCAT_VERSION}.tar.gz
sudo cp /project/apache-tomcat-7.0.64/lib/drmaa.jar /project/apache-tomcat-${TOMCAT_VERSION}/lib/
# sudo cp /project/apache-tomcat-7.0.64/lib/mysql-connector-java-5.1.22-bin.jar /project/apache-tomcat-${TOMCAT_VERSION}/lib/

# Get mysql connector from here: https://search.maven.org/remotecontent?filepath=mysql/mysql-connector-java/8.0.19/mysql-connector-java-8.0.19.jar
MYSQL_CON_VERSION=5.1.9
MYSQL_CON_URL=https://search.maven.org/remotecontent?filepath=mysql/mysql-connector-java/${MYSQL_CON_VERSION}/mysql-connector-java-${MYSQL_CON_VERSION}.jar
wget -O mysql-connector-java-${MYSQL_CON_VERSION}.jar ${MYSQL_CON_URL}
sudo cp mysql-connector-java-${MYSQL_CON_VERSION}.jar /project/apache-tomcat-${TOMCAT_VERSION}/lib

ln -s /project/apache-tomcat-${TOMCAT_VERSION} /project/apache-tomcat-7
sudo chown -R tomcat:tomcat /project/apache-tomcat-${TOMCAT_VERSION}
chmod 744 /project/apache-tomcat-7/bin/*.sh
echo "Done downloading and setting up Tomcat ${TOMCAT_VERSION}"


#make tomcat7 statup script
echo "Making tomcat7 startup script"
touch /etc/systemd/system/tomcat7.service
sudo chmod 744 /etc/systemd/system/tomcat7.service

cat > /etc/systemd/system/tomcat7.service  <<EOF

[Unit]
Description=StarExec Apache Tomcat 7 Servlet Container
After=syslog.target network.target
[Service]
User=tomcat
Group=tomcat
Type=forking
Environment=CATALINA_PID=/var/run/tomcat-7.pid
Environment=CATALINA_HOME=/project/apache-tomcat-7
Environment=CATALINA_BASE=/project/apache-tomcat-7
ExecStart=/project/apache-tomcat-7/bin/startup.sh
ExecStop=/project/apache-tomcat-7/bin/shutdown.sh
Restart=on-failure
[Install]
WantedBy=multi-user.target

EOF


# makes tomcat setenv.sh
echo "creating tomcat7 setenv.sh"
sudo touch /project/apache-tomcat-7/bin/setenv.sh
cd ../
cat /allScripts/starexecScripts/setenv.txt > /project/apache-tomcat-7/bin/setenv.sh
sudo chown tomcat:tomcat /project/apache-tomcat-7/bin/setenv.sh
echo "Done making setenv.sh"
echo "Done configuring tomcat7"
