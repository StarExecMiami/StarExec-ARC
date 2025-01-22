#!/bin/bash

function cleanup() {
  echo 'Container stopped, performing cleanup...'
  /project/apache-tomcat-7/bin/shutdown.sh
  /usr/bin/mysqladmin -u root shutdown
  /usr/sbin/apache2ctl -k graceful-stop
  exit 0
}

trap cleanup SIGINT SIGTERM

set -e
set -o pipefail

# Configure permissions
chown -R tomcat:star-web /project
chown -R tomcat:star-web /home/starexec
chown -R tomcat:star-web /home/sandbox
chown -R mysql:mysql /var/lib/mysql
chmod 755 -R /home/starexec

# Start Apache2
/usr/sbin/apache2ctl -D FOREGROUND &

# Start MySQL
/usr/bin/mysqld_safe --basedir=/usr --user=mysql &

# Wait for MySQL to start
until mysqladmin ping &>/dev/null; do
  echo "Waiting for MySQL to start..."
  sleep 1
done

# Configure database
mysql -u root -e "
  DROP DATABASE IF EXISTS $DB_NAME;
  CREATE DATABASE $DB_NAME;
  GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'localhost' IDENTIFIED BY '$DB_PASS';
  FLUSH PRIVILEGES;
"

# Configure Podman connection
echo "Configuring Podman connection"
podman system connection add host-machine-podman-connection \
  ssh://${SSH_USERNAME}@${HOST_MACHINE}:${SSH_PORT}${SOCKET_PATH} \
  --identity=/root/.ssh/starexec_podman_key || echo "Podman connection configuration failed"

# Start Tomcat
/project/apache-tomcat-7/bin/catalina.sh run &

# Wait for Tomcat to start
until curl -s http://localhost:8080 >/dev/null; do
  echo "Waiting for Tomcat to start..."
  sleep 1
done

# Soft deploy StarExec
cd $DEPLOY_DIR
echo "Running ant build -buildfile $BUILD_FILE reload-sql update-sql"
if ! ant build -buildfile $BUILD_FILE reload-sql update-sql; then
  echo "Running NewInstall.sql"
  cd $DEPLOY_DIR/sql && mysql -u root $DB_NAME < $SQL_FILE
  cd $DEPLOY_DIR

  if ! ant build -buildfile $BUILD_FILE reload-sql update-sql; then
    echo "ERROR! Please rebuild the Docker image..."
    exit 1
  fi
fi

script/soft-deploy.sh && printf "SUCCESS! VISIT IN YOUR BROWSER: http://localhost \n\nuser: admin \npassword: admin\n\n"

# Keep the container running
tail -f /dev/null
