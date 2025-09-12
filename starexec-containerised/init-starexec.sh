#!/bin/bash

# Immediately exit on errors, treat unset vars as errors, and fail on pipe errors
set -euo pipefail

# Populate /home/starexec from the source directory if it's empty (first run with volume)
if [ ! -d "/home/starexec/StarExec-deploy" ] || [ ! -f "/home/starexec/StarExec-deploy/build.xml" ]; then
  echo "StarExec directory not found or incomplete in volume, initializing from source..."
  
  # Remove any existing incomplete directory
  rm -rf /home/starexec/StarExec-deploy
  
  # Copy the application source to the volume
  cp -a /app_source /home/starexec/StarExec-deploy
  echo "Initialization complete."
else 
  echo "StarExec directory found in volume, skipping initialization."
fi

# Change to the deployment directory now that we've ensured it exists
cd /home/starexec/StarExec-deploy

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

# Ensure /export/starexec exists and has correct permissions
mkdir -p /export/starexec && chown -R tomcat:star-web /export/starexec
chmod 755 /export/starexec

# Add sandbox user to star-web group for proper access to /export/starexec
usermod -a -G star-web sandbox

# Configure runtime permissions (only what changes at runtime)
chown -R tomcat:star-web /home/sandbox  # This may change due to mounted volumes
chmod 755 -R /home/starexec  # Ensure permissions after potential volume mounts

# Ensure runsolver is executable if it exists from a previous build
if [ -f "/home/starexec/StarExec-deploy/src/org/starexec/config/sge/runsolver" ]; then
    echo "Setting execute permission on runsolver for sandbox user..."
    chmod +x "/home/starexec/StarExec-deploy/src/org/starexec/config/sge/runsolver"
    chown sandbox:sandbox "/home/starexec/StarExec-deploy/src/org/starexec/config/sge/runsolver" 2>/dev/null || true
fi

# Ensure critical runtime directories exist within their respective volumes
echo "Ensuring runtime directories exist in volumes..."
RUNTIME_DIRS=(
    "/export/starexec"
    "/home/starexec/jobin"
    "/home/starexec/joboutput"
    "/home/starexec/Benchmarks"
    "/home/starexec/trash"
    "/home/starexec/Solvers"
    "/home/starexec/StarOffice"
    "/home/starexec/processor_scripts"
    "/home/starexec/PostProcessors"
)

for dir in "${RUNTIME_DIRS[@]}"; do
    mkdir -p "$dir"
    # Ownership should be tomcat:star-web for Tomcat to write, but
    # the root user in the container also needs access to manage files.
    # Group permissions are key.
    chown tomcat:star-web "$dir"
    chmod 775 "$dir"
done

# Start Apache in the background
echo "Starting Apache..."
/usr/sbin/apache2ctl -D FOREGROUND &

# Initialize and prepare MySQL environment
echo "Preparing MySQL environment..."

# Set MySQL user ID (can be overridden by environment)
MYSQL_UID="${MYSQL_UID:-999}"
MYSQL_GID="${MYSQL_GID:-999}"

# Check if we're running in a Kubernetes/managed storage environment
MANAGED_STORAGE=false
if [ -n "${KUBERNETES_SERVICE_HOST:-}" ] || [ -n "${STAREXEC_MANAGED_STORAGE:-}" ]; then
    MANAGED_STORAGE=true
    echo "Detected managed storage environment - adapting permission handling"
fi

# Ensure MySQL directories exist with proper ownership. /var/lib/mysql is on a persistent volume, so we skip chown on it.
MYSQL_DIRS=("/var/run/mysqld" "/var/log/mysql")
for dir in "${MYSQL_DIRS[@]}"; do
  if [ ! -d "$dir" ]; then
    echo "Creating MySQL directory: $dir"
    mkdir -p "$dir"
  fi
  chown -R mysql:mysql "$dir"
  chmod 755 "$dir"
done

# Create the mysql data directory if it doesn't exist and ensure proper permissions
if [ ! -d "/var/lib/mysql" ]; then
    echo "Creating MySQL directory: /var/lib/mysql"
    mkdir -p "/var/lib/mysql"
fi

# In Kubernetes environments, we need to ensure the mysql user owns the data directory
echo "Ensuring MySQL data directory has proper ownership and permissions..."
# In EKS/Kubernetes, chown operations may fail on persistent volumes
# Use || true to continue if chown fails (common in managed storage)
if chown -R mysql:mysql "/var/lib/mysql" 2>/dev/null; then
    echo "Successfully changed ownership of MySQL data directory"
else
    echo "Warning: Could not change ownership of /var/lib/mysql (expected in managed Kubernetes storage)"
    # Check if MySQL can still access the directory
    if [ -r "/var/lib/mysql" ] && [ -w "/var/lib/mysql" ]; then
        echo "MySQL data directory is accessible, continuing..."
    else
        echo "ERROR: MySQL data directory is not accessible"
        exit 1
    fi
fi
chmod 755 "/var/lib/mysql" 2>/dev/null || echo "Warning: Could not change permissions of /var/lib/mysql"

# Clean up any stale MySQL runtime files
echo "Cleaning up stale MySQL runtime files..."
rm -f /var/run/mysqld/mysqld.sock /var/run/mysqld/mysqld.pid /var/lib/mysql/mysql.sock

# Initialize MySQL data directory if not already initialized
if [ ! -d "/var/lib/mysql/mysql" ]; then
  echo "MySQL data directory not found, initializing..."
  
  # Ensure clean state before initialization
  rm -rf /var/lib/mysql/*
  
  # Ensure proper ownership before initialization
  # In Kubernetes environments, this may fail due to volume constraints
  if chown -R mysql:mysql /var/lib/mysql 2>/dev/null; then
    echo "Successfully set ownership for MySQL initialization"
  else
    echo "Warning: Could not change ownership for initialization (expected in managed storage)"
  fi
  
  # Initialize the database with comprehensive error handling
  if ! mysql_install_db --user=mysql --datadir=/var/lib/mysql --force --skip-name-resolve; then
    error "Failed to initialize MySQL data directory"
  fi
  
  # Verify initialization was successful
  if [ ! -d "/var/lib/mysql/mysql" ] || [ ! -f "/var/lib/mysql/mysql/user.frm" ]; then
    error "MySQL initialization appears incomplete - required system tables not found"
  fi
  
  echo "MySQL data directory initialized successfully"
else
  echo "MySQL data directory already exists, skipping initialization"
  
  # Ensure proper ownership of existing data (may fail in Kubernetes)
  if chown -R mysql:mysql /var/lib/mysql 2>/dev/null; then
    echo "Successfully ensured ownership of existing MySQL data"
  else
    echo "Warning: Could not change ownership of existing data (expected in managed storage)"
  fi
  
  # Verify existing installation integrity
  if [ ! -f "/var/lib/mysql/mysql/user.frm" ]; then
    echo "WARNING: Existing MySQL installation may be corrupted - missing system tables"
  fi
fi

# Verify and validate MySQL configuration
echo "Validating MySQL configuration..."

# Create MySQL configuration for managed storage if needed
if [ "$MANAGED_STORAGE" = true ]; then
    echo "Creating MySQL configuration for managed storage environment..."
    mkdir -p /etc/mysql/conf.d
    cat > /etc/mysql/conf.d/managed-storage.cnf << 'EOF'

EOF
    echo "Created managed storage MySQL configuration"
fi

MYSQL_CONFIG=""
if [ -f "/etc/mysql/my.cnf" ]; then
  MYSQL_CONFIG="/etc/mysql/my.cnf"
elif [ -f "/etc/my.cnf" ]; then
  MYSQL_CONFIG="/etc/my.cnf"
else
  echo "WARNING: No MySQL configuration file found, using defaults"
fi

# Test configuration syntax if config file exists
if [ -n "$MYSQL_CONFIG" ]; then
  if ! mysqld --help --verbose >/dev/null 2>&1; then
    echo "WARNING: MySQL configuration validation failed, proceeding with caution"
  else
    echo "MySQL configuration validated successfully"
  fi
fi

# Final ownership and permission verification
echo "Finalizing MySQL environment setup..."
# These operations may fail in managed Kubernetes storage - that's expected
chown -R mysql:mysql /var/run/mysqld 2>/dev/null || echo "Note: Could not change ownership of /var/run/mysqld"
find /var/lib/mysql -type d -exec chmod 755 {} \; 2>/dev/null || echo "Note: Could not change directory permissions"
find /var/lib/mysql -type f -exec chmod 644 {} \; 2>/dev/null || echo "Note: Could not change file permissions"

echo "MySQL environment preparation completed"

# Start MySQL in the background
echo "Starting MySQL..."

# In managed storage environments, MySQL may need to run as root or with different user
if [ "$MANAGED_STORAGE" = true ] && [ ! -w "/var/lib/mysql" ]; then
    echo "Starting MySQL as root due to managed storage constraints..."
    /usr/sbin/mysqld --user=root &
elif id mysql >/dev/null 2>&1; then
    echo "Starting MySQL as mysql user..."
    /usr/sbin/mysqld --user=mysql &
else
    echo "MySQL user not found, starting as root..."
    /usr/sbin/mysqld --user=root &
fi

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
# Ensure the .config directory and its subdirectories are owned by sandbox
mkdir -p /home/sandbox/.config/containers
chown -R sandbox:sandbox /home/sandbox/.config

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

# Use JDK 8 compatible options (no module system options)
export CATALINA_OPTS="-Dorg.apache.catalina.loader.WebappClassLoader.ENABLE_CLEAR_REFERENCES=false \
-Dorg.apache.catalina.loader.WebappClassLoaderBase.ENABLE_CLEAR_REFERENCES=false \
-Djava.security.egd=file:/dev/./urandom \
-Xms512m -Xmx1024m \
${CATALINA_OPTS:-}"
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
