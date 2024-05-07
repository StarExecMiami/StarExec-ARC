#!/bin/bash
set -e
set -o pipefail

#create star-web group
sudo su -c "groupadd -g 160 star-web"

#create tomcat group

sudo su -c "groupadd -g 153 tomcat"

#Create tomcat user
sudo su -c "useradd -r -m -d /home/tomcat -s /bin/bash -c \"Tomcat User\" -u 153 -g 160 tomcat"

# create starexec user
sudo su -c "useradd -r -m -d /home/starexec -s /bin/bash -c \"Starexec User\" -u 152 -g 160 starexec"

# Add sandbox users
sudo su -c "useradd -r -m -d /home/sandbox -s /bin/bash -c \"Cluster UserOne\" -u 111 sandbox"

sudo su -c "useradd -r -m -d /home/sandbox2 -s /bin/bash -c \"Cluster UserTwo\" -u 112 sandbox2"

# And sandbox user to star-web group
usermod -aG star-web sandbox
usermod -aG star-web sandbox2

#configure Backend.WorkingDir
sudo mkdir /export
sudo mkdir /export/starexec
sudo mkdir /export/starexec/sandbox
sudo mkdir /export/starexec/sandbox2
sudo chown -R tomcat:star-web /export/starexec
#sudo chgrp -R star-web /export/starexec

#next 4 lines to configure sandbox directory
mkdir -p /local/sandbox

sudo chown sandbox:sandbox /local/sandbox/

sudo chmod 770 /local/sandbox/

sudo chmod g+s /local/sandbox/

#creates sandbox2

mkdir -p /local/sandbox2

sudo chown sandbox2:sandbox2 /local/sandbox2/

sudo chmod 770 /local/sandbox2/

sudo chmod g+s /local/sandbox2/


usermod -aG star-web tomcat

usermod -aG star-web starexec

usermod -aG sandbox tomcat

usermod -aG sandbox2 tomcat

su
