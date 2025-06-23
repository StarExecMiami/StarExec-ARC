# Copyright (c) HashiCorp, Inc.
# SPDX-License-Identifier: MPL-2.0


variable "region" {
  description = "AWS region"
  type        = string
}

variable "timezone" {
  description = "Timezone for the cluster"
  type        = string
}

variable "efs_enable_lifecycle_policy" {
  description = "Enable lifecycle policy for EFS"
  type        = bool
}

variable "domain" {
  description = "Domain name for the cluster"
  type        = string
}

variable "prover_image" {
  description = "Docker image for the prover"
  type        = string
  default     = "tptpstarexec/eprover:latest"
}

variable "instance_type" {
  description = "EC2 instance type for the EKS node groups"
  type        = string
  default     = "t3.small"
}

variable "desired_nodes" {
  description = "Desired number of compute nodes"
  type        = number
  default     = 2
}

variable "max_nodes" {
  description = "Maximum number of compute nodes"
  type        = number
  default     = 3
}

# variable "region" {
#   description = "AWS region"
#   type        = string
#   default     = "us-east-1"
# }
