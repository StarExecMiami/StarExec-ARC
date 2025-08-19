variable "vpc_id" {
  description = "ID of the VPC where EFS will be created"
  type        = string
}

variable "vpc_cidr_block" {
  description = "CIDR block of the VPC"
  type        = string
}

variable "eks_cluster_security_group_id" {
  description = "Security group ID of the EKS cluster"
  type        = string
}

variable "eks_node_security_group_id" {
  description = "Security group ID of the EKS worker nodes"
  type        = string
}

variable "private_subnets" {
  description = "List of private subnet IDs"
  type        = list(string)
}