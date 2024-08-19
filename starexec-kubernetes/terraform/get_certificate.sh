#!/bin/bash

###################################################################
# This cannot be used with the auto-generated domains from AWS.   #
# Instead, only run this script once you have configured a domain #
# to point to this server. (This is in the makefile)              #
###################################################################

# Check if an argument was provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 new_web_address"
    exit 1
fi


########################################################################################
# 1.) Setup SSL Certificate for $1: install certbot and create SSL certificate for $1  #
########################################################################################
sudo apt-get install -y certbot python3-certbot-apache
if [ $? -ne 0 ]; then
    echo "Failed to install certbot"
    exit 1
fi

# sudo certbot --apache -d $1
sudo certbot --apache -d $1 -n --agree-tos --register-unsafely-without-email
if [ $? -ne 0 ]; then
    echo "Failed to create SSL certificate for $1"
    exit 1
fi

########################################################################################
# 2.) edit auto generated starexec-le-ssl.conf file to point to redirect to tomcat     #
########################################################################################
sed -i '23i\
ProxyPass /starexec http://localhost:8080/starexec\n\
ProxyPassReverse /starexec http://localhost:8080/starexec' /etc/apache2/sites-enabled/starexec-le-ssl.conf

service apache2 restart