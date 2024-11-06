# Copyright (c) HashiCorp, Inc.
# SPDX-License-Identifier: MPL-2.0

# Work in progress...
# data "external" "region" {
#   program = ["bash", "-c", "aws configure list | grep region | awk '{print $2}'"]
# }

# variable "region" {
#   description = "AWS region"
#   type        = string
#   default     = data.external.region.result.value
# }

# variable "region" {
#   description = "AWS region"
#   type        = string
#   default     = "us-east-2"
# }
