#!/bin/bash
set -e
set -o pipefail

# Updates and upgrades packages
sudo apt update && sudo apt upgrade -y
sudo apt-get install -y sudo git wget unzip file apache2 tcsh libnuma-dev # libnuma for runsolver
a2enmod ssl


# Installs development tools
sudo apt-get install -y build-essential libssl-dev openssl

# Creates SSL certificate for localhost for HTTPS
bash ./allScripts/osScripts/SSLCreateLocalhost.sh

# Installs DNS utilities
sudo apt-get install -y dnsutils
