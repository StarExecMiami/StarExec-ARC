#!/bin/bash

# For configuration of the cluster (domain name, etc)
domain=starexec.mckeown.in
desiredNodes=3
maxNodes=5


# Look at this site to see the instance types available:
# https://aws.amazon.com/ec2/instance-types/
# StarExec Cloud proposal suggested x2iedn.xlarge
# One-CPU instances are preferred because scheduling is simpler / more reliable in k8s.
instanceType="t3.small"




if ! [ -z ${1+x} ]; then echo ${!1}; fi
