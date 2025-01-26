#!/bin/bash
set -e
set -o pipefail


#add config files for ssh
# cp ./configFiles/ssl.conf /etc/httpd/conf.d/ # <-- CentOS
cp ./configFiles/ssl.conf /etc/apache2/sites-available/

#add starexec configFile for https
# cp ./configFiles/starexec.conf /etc/httpd/conf.d/ # <-- CentOS
cp ./configFiles/starexec.conf /etc/apache2/sites-available/

# disable default sites...
sudo a2dissite 000-default.conf
sudo a2dissite default-ssl.conf

# enable ssl and starexec.conf:
sudo a2ensite ssl
sudo a2ensite starexec

# needed for something in one of the conf files...
sudo a2enmod proxy
sudo a2enmod headers
sudo a2enmod proxy_http
sudo a2enmod rewrite

sudo mkdir -p /etc/apache2/logs/


# reload apache
sudo sh -c 'echo "ServerName localhost" >> /etc/apache2/apache2.conf'
sudo service apache2 restart



# Try to run httpd
# usr/sbin/httpd || true # <-- CentOS
sudo /usr/sbin/apache2ctl -D FOREGROUND

