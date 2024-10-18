#!/bin/bash

# For configuration of the cluster (domain name, etc)
domain=starexec.net
domain=a5ce3301edf034d919a18c57affb2c13-1189330949.us-east-2.elb.amazonaws.com
desiredNodes=5
maxNodes=5

# Look at this site to see the instance types available:
# https://aws.amazon.com/ec2/instance-types/
# StarExec Cloud proposal suggested x2iedn.xlarge
# One-CPU instances are preferred because scheduling is simpler / more reliable in k8s.
instanceType="t3.small"

if ! [ -z ${1+x} ]; then echo ${!1}; fi
