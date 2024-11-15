#!/bin/bash
set -e
set -o pipefail

su - starexec  -c  "git clone -b UMprod --single-branch https://github.com/StarexecMiami/StarExec.git StarExec-deploy"
git config --global --add safe.directory /home/starexec/StarExec-deploy

chown -R tomcat:star-web /home/starexec

cd ~starexec/StarExec-deploy/WebContent/css/details && sudo ln -s ../shared

