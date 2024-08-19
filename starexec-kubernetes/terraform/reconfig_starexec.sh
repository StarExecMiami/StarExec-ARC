#!/bin/bash

# Check if an argument was provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 new_web_address"
    exit 1
fi




#######################################################################################
# 1.) Replace 'Web.Address: localhost' with 'Web.Address: $1' in the properties file  #
#######################################################################################
file_path="/home/starexec/StarExec-deploy/build/overrides.properties"
sed -i "s/Web.Address: localhost/Web.Address: $1/" $file_path
if [ $? -ne 0 ]; then
    echo "Failed to update the Web.Address in $file_path"
    exit 1
fi

# Change directory to the StarExec-deploy
cd /home/starexec/StarExec-deploy
if [ $? -ne 0 ]; then
    echo "Failed to change directory to /home/starexec/StarExec-deploy"
    exit 1
fi

# Build using Ant
ant build -buildfile build.xml
if [ $? -ne 0 ]; then
    echo "Ant build failed"
    exit 1
fi

# Run the soft-deploy script
./script/soft-deploy.sh
if [ $? -ne 0 ]; then
    echo "Soft-deploy script failed"
    exit 1
fi

echo "Deployment completed successfully"










