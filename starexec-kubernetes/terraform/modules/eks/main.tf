# EKS Module
# Responsible for creating the EKS cluster and node groups

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

variable "instance_type" {
  description = "EC2 instance type for the EKS node groups"
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

module "eks" {
  source  = "terraform-aws-modules/eks/aws"
  version = "20.8.5"

  cluster_name    = var.cluster_name
  cluster_version = var.cluster_version

  cluster_endpoint_public_access           = true
  enable_cluster_creator_admin_permissions = true

  cluster_addons = {
    aws-efs-csi-driver = {
      service_account_role_arn = var.efs_csi_role_arn
    }
  }

  vpc_id     = var.vpc_id
  subnet_ids = var.subnet_ids

  eks_managed_node_group_defaults = {
    ami_type = "AL2_x86_64"
  }

  eks_managed_node_groups = {
    computenodes = {
      name = "computenodes"

      instance_types = [var.instance_type]
      min_size     = 1
      max_size     = var.max_nodes
      desired_size = var.desired_nodes
    }
    
    headnode = {
      name = "headnode"

      instance_types = [var.instance_type]
      min_size     = 1
      max_size     = 1
      desired_size = 1
    }
  }
}

output "cluster_name" {
  description = "The name of the EKS cluster"
  value       = module.eks.cluster_name
}

output "cluster_endpoint" {
  description = "Endpoint for EKS control plane"
  value       = module.eks.cluster_endpoint
}

output "cluster_security_group_id" {
  description = "Security group IDs attached to the cluster control plane"
  value       = module.eks.cluster_security_group_id
}

output "oidc_provider" {
  description = "The OpenID Connect identity provider (issuer URL without leading https://)"
  value       = module.eks.oidc_provider
}