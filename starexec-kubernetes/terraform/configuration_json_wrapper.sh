#!/bin/bash

# This is for terraform to understand the configuration.sh file.
# (Terraform requires json basically)

value=$("./configuration.sh" "$1")
echo "{\"value\": \"$value\"}"
