# IAM Module for EFS CSI Driver
# Responsible for creating the IAM role for the EFS CSI driver

variable "cluster_name" {
  description = "Name of the EKS cluster"
  type        = string
}

variable "oidc_provider" {
  description = "The OpenID Connect identity provider URL"
  type        = string
}

module "irsa_efs_csi" {
  source  = "terraform-aws-modules/iam/aws//modules/iam-assumable-role-with-oidc"
  version = "5.39.0"

  create_role                   = true
  role_name                     = "AmazonEFSTFEBSCSIRole-${var.cluster_name}"
  provider_url                  = var.oidc_provider
  role_policy_arns              = ["arn:aws:iam::aws:policy/service-role/AmazonEFSCSIDriverPolicy"]
  oidc_fully_qualified_subjects = ["system:serviceaccount:kube-system:efs-csi-controller-sa"]
}

output "iam_role_arn" {
  description = "ARN of the IAM role for EFS CSI driver"
  value       = module.irsa_efs_csi.iam_role_arn
}