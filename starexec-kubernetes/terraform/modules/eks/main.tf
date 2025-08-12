# EKS Module
# Responsible for creating the EKS cluster and node groups

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

      instance_types = [var.computenodes_instance_type]
      min_size      = 1
      max_size      = var.max_nodes
      desired_size  = var.desired_nodes
      disk_size     = 20
      capacity_type = "ON_DEMAND"
      update_config = {
      max_unavailable = 1
      }
    }

    headnode = {
      name = "headnode"

      instance_types = [var.headnode_instance_type]
      min_size      = 1
      max_size      = 1
      desired_size  = 1
      disk_size     = 20
      capacity_type = "ON_DEMAND"
      update_config = {
      max_unavailable = 1
      }
    }
  }
}