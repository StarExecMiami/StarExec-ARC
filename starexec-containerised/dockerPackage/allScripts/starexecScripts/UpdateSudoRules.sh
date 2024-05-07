#!/bin/bash
set -e
set -o pipefail

#echo "updating sudo rules"

sudo cat allScripts/starexecScripts/sudoRules.txt >> /etc/sudoers
echo "Done"
