
variable "cluster_name" {
  description = "Name of the EKS cluster"
  type        = string
}

variable "cluster_version" {
  description = "Kubernetes version for the EKS cluster"
  type        = string
  default     = "1.31"
}

variable "vpc_id" {
  description = "ID of the VPC where the EKS cluster will be created"
  type        = string
}

variable "subnet_ids" {
  description = "List of subnet IDs for the EKS cluster"
  type        = list(string)
}

variable "headnode_instance_type" {
  description = "EC2 instance type for the head node group"
  type        = string
}

variable "computenodes_instance_type" {
  description = "EC2 instance type for the compute nodes"
  type        = string
}

variable "desired_nodes" {
  description = "Desired number of compute nodes"
  type        = number
}

variable "max_nodes" {
  description = "Maximum number of compute nodes"
  type        = number
}

variable "efs_csi_role_arn" {
  description = "ARN of the IAM role for EFS CSI driver"
  type        = string
}