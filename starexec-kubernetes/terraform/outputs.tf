# Copyright (c) HashiCorp, Inc.
# SPDX-License-Identifier: MPL-2.0

output "cluster_endpoint" {
  description = "Endpoint for EKS control plane"
  value       = module.eks.cluster_endpoint
}

output "cluster_security_group_id" {
  description = "Security group ids attached to the cluster control plane"
  value       = module.eks.cluster_security_group_id
}

output "region" {
  description = "AWS region"
  value       = var.region
}

output "cluster_name" {
  description = "Kubernetes Cluster Name"
  value       = module.eks.cluster_name
}

output "efs_file_system_id" {
  value = aws_efs_file_system.example.id
}


output "efs_voldb_access_point_id" {
  value = aws_efs_access_point.voldb.id
}

output "efs_volstar_access_point_id" {
  value = aws_efs_access_point.volstar.id
}

output "efs_volpro_access_point_id" {
  value = aws_efs_access_point.volpro.id
}

output "efs_volexport_access_point_id" {
  value = aws_efs_access_point.volexport.id
}