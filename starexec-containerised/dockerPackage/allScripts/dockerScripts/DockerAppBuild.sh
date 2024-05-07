#!/bin/bash
set -e
set -o pipefail

#THIS SCRIPT RUNS AT DOCKER BUILD TIME AND JUST MAKES THE APP ALONG WITH VOLUMEDATA (DIRECTORY FOR PERSISTANT DATA)


#starts mysql server
/usr/bin/mysqld_safe --basedir=/usr --user=mysql & # --log-error=/var/log/mysql/error.log &

#starts tomcat server
su -c "/project/apache-tomcat-7/bin/catalina.sh run &" tomcat

# Wait for MySQL to start
until mysqladmin ping &>/dev/null; do
    echo "Waiting for MySQL to start..."
    # cat /var/log/mysql/error.log || true
    sleep 1
done

bash allScripts/starexecScripts/AntBuildDeploy.sh
