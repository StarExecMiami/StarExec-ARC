#!/bin/bash

# Immediately exit on errors, treat unset vars as errors, and fail on pipe errors
set -euo pipefail

function error() {
  echo "[ERROR] $1"
  exit 1
}

function healthcheck() {
  # Check if MySQL is running
  if ! mysqladmin ping -u root --silent --connect-timeout=3; then
    echo "[HEALTHCHECK] MySQL is not running"
    exit 1
  fi
  
  # Check if Apache is running
  if ! service apache2 status | grep -q "running"; then
    echo "[HEALTHCHECK] Apache is not running"
    exit 1
  fi
  
  # Check if Tomcat is running
  if ! ps -ef | grep -v grep | grep -q "org.apache.catalina.startup.Bootstrap"; then
    echo "[HEALTHCHECK] Tomcat is not running"
    exit 1
  fi
  
  # Check if the application is responding
  if ! curl -s -k --max-time 5 -I https://localhost/starexec/ | grep -q "200 OK"; then
    echo "[HEALTHCHECK] StarExec application is not responding"
    exit 1
  fi
  
  echo "[HEALTHCHECK] All services are healthy"
  exit 0
}

function cleanup() {
  echo "Container stopped, performing cleanup..."
  
  # Attempt a graceful shutdown of Tomcat
  /project/apache-tomcat-7/bin/shutdown.sh || true
  
  # Wait briefly for Tomcat to finish cleaning up
  sleep 1
  
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

# If first argument is "healthcheck", run the healthcheck function
if [ "${1:-}" = "healthcheck" ]; then
  healthcheck
fi

# Generate SSL certificates if they don't exist
if [ ! -f "/etc/ssl/certs/localhost.crt" ] || [ ! -f "/etc/ssl/private/localhost.key" ]; then
  echo "Generating SSL certificates..."
  printf "[dn]\nCN=localhost\n[req]\ndistinguished_name = dn\n[EXT]\nsubjectAltName=DNS:localhost\nkeyUsage=digitalSignature\nextendedKeyUsage=serverAuth" > /tmp/openssl.cnf
  openssl req -x509 -out /etc/ssl/certs/localhost.crt -keyout /etc/ssl/private/localhost.key \
    -newkey rsa:2048 -nodes -sha256 \
    -subj '/CN=localhost' -extensions EXT -config /tmp/openssl.cnf
  rm /tmp/openssl.cnf
  chmod 644 /etc/ssl/certs/localhost.crt
  chmod 600 /etc/ssl/private/localhost.key
fi

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

# Configure runtime permissions (only what changes at runtime)
chown -R tomcat:star-web /home/sandbox  # This may change due to mounted volumes
chmod 755 -R /home/starexec  # Ensure permissions after potential volume mounts

# Start Apache in the background
echo "Starting Apache..."
/usr/sbin/apache2ctl -D FOREGROUND &

# Initialize MySQL data directory if not already initialized
if [ ! -d "/var/lib/mysql/mysql" ]; then
  echo "Initializing MySQL data directory..."
  chown -R mysql:mysql /var/lib/mysql
  mysql_install_db --user=mysql --ldata=/var/lib/mysql
fi

# Ensure MySQL runtime directory exists
echo "Setting up MySQL runtime directory..."
rm -rf /var/run/mysqld
mkdir -p /var/run/mysqld
chown mysql:mysql /var/run/mysqld
chmod 755 /var/run/mysqld

# Start MySQL in the background
echo "Starting MySQL..."
/usr/bin/mysqld_safe --basedir=/usr --user=mysql &

# Wait for MySQL to start
MYSQL_START_TIMEOUT=60
MYSQL_START_INTERVAL=1
MYSQL_START_ELAPSED=0

until mysqladmin ping &>/dev/null; do
  if [ "$MYSQL_START_ELAPSED" -ge "$MYSQL_START_TIMEOUT" ]; then
    error "MySQL failed to start within $MYSQL_START_TIMEOUT seconds."
  fi
  echo "Waiting for MySQL to start... ($MYSQL_START_ELAPSED/$MYSQL_START_TIMEOUT)"
  sleep "$MYSQL_START_INTERVAL"
  MYSQL_START_ELAPSED=$((MYSQL_START_ELAPSED + MYSQL_START_INTERVAL))
done

# Configure the database
echo "Configuring database..."
if ! mysql -u root -e "USE $DB_NAME" 2>/dev/null; then
  echo "Database $DB_NAME does not exist, creating..."
  mysql -u root -e "
    CREATE DATABASE $DB_NAME;
    GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'localhost' IDENTIFIED BY '$DB_PASS';
    FLUSH PRIVILEGES;
  "

  # Initialize the database with NewInstall.sql only if it's a fresh install
  echo "Initializing database with NewInstall.sql..."
  cd "$DEPLOY_DIR/sql" || error "Cannot change directory to $DEPLOY_DIR/sql"
  mysql -u root "$DB_NAME" < "$SQL_FILE"
  cd "$DEPLOY_DIR" || error "Cannot change directory back to $DEPLOY_DIR"

else
  echo "Database $DB_NAME already exists, skipping initialization..."
  # Just ensure privileges are set correctly
  mysql -u root -e "
    GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'localhost' IDENTIFIED BY '$DB_PASS';
    FLUSH PRIVILEGES;
  "
fi

# Configure SSH for non-interactive access to the Podman host
echo "Configuring SSH for non-interactive Podman host access (${HOST_MACHINE})..."
# SSH directory already created in Dockerfile
cat << EOF > /root/.ssh/config
Host ${HOST_MACHINE}
    UserKnownHostsFile /dev/null
    StrictHostKeyChecking no
    LogLevel ERROR
EOF
chmod 600 /root/.ssh/config
chown root:root /root/.ssh/config

# Configure Podman connection to the host for root user
echo "Configuring Podman system connection 'host-machine-podman-connection' for root user..."
# Remove existing connection if it exists, to ensure idempotency
podman system connection remove host-machine-podman-connection >/dev/null 2>&1 || true
if podman system connection add host-machine-podman-connection \
  --identity /root/.ssh/starexec_podman_key \
  --default \
  "ssh://${SSH_USERNAME}@${HOST_MACHINE}:${SSH_PORT}${SSH_SOCKET_PATH}"; then
  echo "Podman connection 'host-machine-podman-connection' configured successfully and set as default for root."
else
  echo "WARNING: Podman connection 'host-machine-podman-connection' configuration failed for root."
  # Optionally, list connections for debugging if the add command fails
  podman system connection list || true
fi

# Configure SSH and Podman connection for sandbox user as well
echo "Configuring SSH and Podman connection for sandbox user..."
# SSH directories already created in Dockerfile
cat << EOF > /home/sandbox/.ssh/config
Host ${HOST_MACHINE}
    UserKnownHostsFile /dev/null
    StrictHostKeyChecking no
    LogLevel ERROR
EOF
# Copy the SSH key to sandbox user's directory
cp /root/.ssh/starexec_podman_key /home/sandbox/.ssh/
# Set proper permissions (directories already created with correct ownership)
chmod 600 /home/sandbox/.ssh/config
chmod 600 /home/sandbox/.ssh/starexec_podman_key

# Configure Podman connection for sandbox user
echo "Configuring Podman system connection for sandbox user..."
su - sandbox -c "
  podman system connection remove host-machine-podman-connection >/dev/null 2>&1 || true
  if podman system connection add host-machine-podman-connection \
    --identity /home/sandbox/.ssh/starexec_podman_key \
    --default \
    'ssh://${SSH_USERNAME}@${HOST_MACHINE}:${SSH_PORT}${SSH_SOCKET_PATH}'; then
    echo 'Podman connection configured successfully for sandbox user.'
  else
    echo 'WARNING: Podman connection configuration failed for sandbox user.'
    podman system connection list || true
  fi
"

# Start Tomcat
echo "Starting Tomcat..."
# Setting both properties to handle different Tomcat versions
export CATALINA_OPTS="-Dorg.apache.catalina.loader.WebappClassLoader.ENABLE_CLEAR_REFERENCES=false -Dorg.apache.catalina.loader.WebappClassLoaderBase.ENABLE_CLEAR_REFERENCES=false ${CATALINA_OPTS:-}"
/project/apache-tomcat-7/bin/catalina.sh run &

# Wait for Tomcat to start
until curl -s http://localhost:8080 >/dev/null; do
  echo "Waiting for Tomcat to start..."
  sleep 1
done

# Soft deploy StarExec
cd "$DEPLOY_DIR" || error "Cannot change directory to $DEPLOY_DIR"
echo "Running ant build -buildfile $BUILD_FILE reload-sql update-sql..."

# Only run reload-sql and update-sql without reinitializing the database
if ! ant build -buildfile "$BUILD_FILE" reload-sql; then
  error "ERROR: reload-sql failed. Please check the build file and try again."
fi

if ! ant -buildfile "$BUILD_FILE" update-sql; then
  error "ERROR: update-sql failed. Please check the build file and try again."
fi

script/soft-deploy.sh && printf "SUCCESS! VISIT IN YOUR BROWSER: https://localhost:7827\n\nuser: admin\npassword: admin\n\n"

# Start monitoring all critical services in the background
echo "Starting service monitoring..."

# Monitor Apache
monitor_service "Apache2" "pgrep apache2 > /dev/null" "/usr/sbin/apache2ctl start" &> /dev/null &

# Keep the container running; wait on background jobs
wait
