output "iam_role_arn" {
  description = "ARN of the IAM role for EFS CSI driver"
  value       = module.irsa_efs_csi.iam_role_arn
}