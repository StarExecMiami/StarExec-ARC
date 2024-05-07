#!/bin/bash
set -e
set -o pipefail

# Installs MariaDB
echo "Installing MariaDB"
apt-get update
apt-get install -y mariadb-client mariadb-server

# Checks MariaDB version
mysql -u root --version

# Ensures the MariaDB database directory is clean (only if absolutely necessary; dangerous otherwise)
echo "Checking MariaDB database directory at /var/lib/mysql"
ls -al /var/lib/mysql

echo "Done installing MariaDB"

