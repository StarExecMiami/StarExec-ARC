#!/bin/bash
set -e
set -o pipefail

# Create groups
groupadd -g 160 star-web
groupadd -g 153 tomcat

# Create users
useradd -r -m -d /home/tomcat -s /bin/bash -c "Tomcat User" -u 153 -g 160 tomcat
useradd -r -m -d /home/starexec -s /bin/bash -c "Starexec User" -u 152 -g 160 starexec
useradd -r -m -d /home/sandbox -s /bin/bash -c "Cluster UserOne" -u 111 sandbox
useradd -r -m -d /home/sandbox2 -s /bin/bash -c "Cluster UserTwo" -u 112 sandbox2

# Add users to groups
usermod -aG star-web sandbox
usermod -aG star-web sandbox2
usermod -aG star-web tomcat
usermod -aG star-web starexec
usermod -aG sandbox tomcat
usermod -aG sandbox2 tomcat

# Create and configure directories
mkdir -p /export/starexec/{sandbox,sandbox2}
chown -R tomcat:star-web /export/starexec

# Configure sandbox directories
mkdir -p /local/sandbox
mkdir -p /local/sandbox2
chown sandbox:sandbox /local/sandbox
chown sandbox2:sandbox2 /local/sandbox2
chmod 770 /local/sandbox /local/sandbox2
chmod g+s /local/sandbox /local/sandbox2
