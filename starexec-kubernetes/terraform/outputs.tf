# Copyright (c) HashiCorp, Inc.
# SPDX-License-Identifier: MPL-2.0

data "kubernetes_service" "starexec_service" {
  metadata {
    name      = "starexec-service"
    namespace = "default"
  }
}

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
  description = "ID of the EFS file system"
  value       = module.efs.efs_file_system_id
}

output "efs_voldb_access_point_id" {
  description = "ID of the voldb access point"
  value       = module.efs.voldb_access_point_id
}

output "efs_volstar_access_point_id" {
  description = "ID of the volstar access point"
  value       = module.efs.volstar_access_point_id
}

output "efs_volpro_access_point_id" {
  description = "ID of the volpro access point"
  value       = module.efs.volpro_access_point_id
}

output "domain_name" {
  description = "The domain name configured for the StarExec cluster."
  value       = var.domain
}

output "prover_image" {
  description = "The prover image used in the StarExec cluster."
  value       = var.prover_image

}

# Output the external IP of the starexec-service LoadBalancer
output "starexec_service_loadbalancer_ip" {
  description = "The external IP of the starexec-service LoadBalancer"
  value = try(
    data.kubernetes_service.starexec_service.status[0].load_balancer[0].ingress[0].ip,
    "not-available"
  )
}
