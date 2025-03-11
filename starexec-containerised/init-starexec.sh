#!/bin/bash

# Immediately exit on errors, treat unset vars as errors, and fail on pipe errors
set -euo pipefail

function error() {
  echo "[ERROR] $1"
  exit 1
}

function cleanup() {
  echo "Container stopped, performing cleanup..."
  
  # Attempt a graceful shutdown of Tomcat
  /project/apache-tomcat-7/bin/shutdown.sh || true
  
  # Wait briefly for Tomcat to finish cleaning up
  sleep 5
  
  # Forcibly kill any remaining Tomcat processes (matching the Bootstrap class)
  pkill -f 'org.apache.catalina.startup.Bootstrap' || true
  
  /usr/bin/mysqladmin -u root shutdown || true
  /usr/sbin/apache2ctl -k graceful-stop || true
  exit 0
}

# Function to check and restart services
function monitor_service() {
  local name=$1
  local check_cmd=$2
  local restart_cmd=$3
  
  while true; do
    if ! eval "$check_cmd"; then
      echo "$name is not running, restarting..."
      eval "$restart_cmd"
    fi
    sleep 30
  done
}

# Generate SQL install file using Ant build target
echo "Generating SQL install file..."
ant -buildfile "${BUILD_FILE}" compile-sql
SQL_FILE="${DEPLOY_DIR}/sql/NewInstall.sql"

# Trap signals for cleanup
trap cleanup SIGINT SIGTERM

# Verify essential environment variables are set
: "${DB_NAME:?DB_NAME is not set}"
: "${DB_USER:?DB_USER is not set}"
: "${DB_PASS:?DB_PASS is not set}"
: "${DEPLOY_DIR:?DEPLOY_DIR is not set}"
: "${BUILD_FILE:?BUILD_FILE is not set}"
: "${SQL_FILE:?SQL_FILE is not set}"

# Configure permissions
chown -R tomcat:star-web /project
chown -R tomcat:star-web /home/starexec
chown -R tomcat:star-web /home/sandbox
chown -R mysql:mysql /var/lib/mysql
chmod 755 -R /home/starexec

# Start Apache in the background
echo "Starting Apache..."
/usr/sbin/apache2ctl -D FOREGROUND &

# Start MySQL in the background
echo "Starting MySQL..."
/usr/bin/mysqld_safe --basedir=/usr --user=mysql &

# Wait for MySQL to start
until mysqladmin ping &>/dev/null; do
  echo "Waiting for MySQL to start..."
  sleep 1
done

# Configure the database
echo "Configuring database..."
mysql -u root -e "
  DROP DATABASE IF EXISTS $DB_NAME;
  CREATE DATABASE $DB_NAME;
  GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'localhost' IDENTIFIED BY '$DB_PASS';
  FLUSH PRIVILEGES;
"

# Configure Podman connection
echo "Configuring Podman connection..."
podman system connection add host-machine-podman-connection \
  ssh://${SSH_USERNAME}@${HOST_MACHINE}:${SSH_PORT}${SOCKET_PATH} \
  --identity=/root/.ssh/starexec_podman_key || echo "Podman connection configuration failed"

# Start Tomcat
echo "Starting Tomcat..."
CATALINA_OPTS="${CATALINA_OPTS:-} -Dcatalina.loader.webappClassLoader.ENABLE_CLEAR_REFERENCES=false"
/project/apache-tomcat-7/bin/catalina.sh run &

# Wait for Tomcat to start
until curl -s http://localhost:8080 >/dev/null; do
  echo "Waiting for Tomcat to start..."
  sleep 1
done

# Soft deploy StarExec
cd "$DEPLOY_DIR" || error "Cannot change directory to $DEPLOY_DIR"
echo "Running ant build -buildfile $BUILD_FILE reload-sql update-sql..."

# First initialize the database with NewInstall.sql
echo "Initializing database with NewInstall.sql..."
cd "$DEPLOY_DIR/sql" || error "Cannot change directory to $DEPLOY_DIR/sql"
mysql -u root "$DB_NAME" < "$SQL_FILE"
cd "$DEPLOY_DIR" || error "Cannot change directory back to $DEPLOY_DIR"

# Then run reload-sql to load procedures
if ! ant build -buildfile "$BUILD_FILE" reload-sql; then
  error "ERROR: reload-sql failed after initializing database. Please check the build file and try again."
fi

# Finally run update-sql to apply schema changes
if ! ant -buildfile "$BUILD_FILE" update-sql; then
  error "ERROR: update-sql failed. Please check the build file and try again."
fi

script/soft-deploy.sh && printf "SUCCESS! VISIT IN YOUR BROWSER: https://localhost:8443\n\nuser: admin\npassword: admin\n\n"

# Start monitoring all critical services in the background
echo "Starting service monitoring..."

# Monitor Apache
monitor_service "Apache2" "service apache2 status" "service apache2 restart" &> /dev/null &

# Keep the container running; wait on background jobs
wait
