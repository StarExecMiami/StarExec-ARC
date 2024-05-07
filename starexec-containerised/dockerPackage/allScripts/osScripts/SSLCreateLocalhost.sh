#!/bin/bash
set -e
set -o pipefail

# Assuming openssl is installed in the default system path
openssl req -x509 -out localhost.crt -keyout localhost.key \
    -newkey rsa:2048 -nodes -sha256 \
    -subj '/CN=localhost' -extensions EXT -config <( \
       printf "[dn]\nCN=localhost\n[req]\ndistinguished_name = dn\n[EXT]\nsubjectAltName=DNS:localhost\nkeyUsage=digitalSignature\nextendedKeyUsage=serverAuth")

echo 'made key'

# Move the key and certificate to appropriate Ubuntu directories
sudo mkdir -p /etc/ssl/private
sudo mkdir -p /etc/ssl/certs

mv localhost.key /etc/ssl/private/
mv localhost.crt /etc/ssl/certs/
