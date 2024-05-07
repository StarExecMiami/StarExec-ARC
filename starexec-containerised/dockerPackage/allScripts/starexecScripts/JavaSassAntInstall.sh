#!/bin/bash
set -e
set -o pipefail

# Installs Java OpenJDK 8
echo "Installing Java OpenJDK"
sudo apt-get update
sudo apt-get install -y openjdk-8-jdk curl

# Installs Ant
echo "Installing Ant"
sudo apt-get install -y ant

# Installs Sass with Node.js package manager
echo "Downloading Node.js"
sudo apt-get install -y gcc g++ make

# Using NodeSource official setup script for Node.js 16.x
curl -sL https://deb.nodesource.com/setup_16.x | sudo -E bash -
sudo apt-get install -y nodejs

echo "Done, now installing Sass"
sudo npm install -g sass


