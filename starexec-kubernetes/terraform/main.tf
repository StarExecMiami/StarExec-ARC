
#################### SETUP ####################################################
provider "aws" {
  region = var.region
}

# Filter out local zones, which are not currently supported 
# with managed node groups
data "aws_availability_zones" "available" {
  filter {
    name   = "opt-in-status"
    values = ["opt-in-not-required"]
  }
}

locals {
  cluster_name = "starexec-eks-${random_string.suffix.result}"
}

resource "random_string" "suffix" {
  length  = 8
  special = false
}

#################### VPC ####################################################

module "vpc" {
  source = "./modules/vpc"

  vpc_name             = "starexec-vpc"
  vpc_cidr             = "10.0.0.0/16"
  azs                  = slice(data.aws_availability_zones.available.names, 0, 3)
  private_subnets      = ["10.0.1.0/24", "10.0.2.0/24", "10.0.3.0/24"]
  public_subnets       = ["10.0.4.0/24", "10.0.5.0/24", "10.0.6.0/24"]
  enable_nat_gateway   = true
  single_nat_gateway   = true
  enable_dns_hostnames = true
}


#################### EKS ####################################################

module "eks" {
  source = "./modules/eks"

  cluster_name     = local.cluster_name
  cluster_version  = "1.31"
  vpc_id           = module.vpc.vpc_id
  subnet_ids       = module.vpc.private_subnets
  instance_type    = var.instance_type
  desired_nodes    = var.desired_nodes
  max_nodes        = var.max_nodes
  efs_csi_role_arn = module.iam_efs_csi.iam_role_arn
}

#################### IAM for EFS CSI ####################################################

data "aws_iam_policy" "efs_csi_policy" {
  arn = "arn:aws:iam::aws:policy/service-role/AmazonEFSCSIDriverPolicy"
}

module "iam_efs_csi" {
  source  = "terraform-aws-modules/iam/aws//modules/iam-assumable-role-with-oidc"
  version = "5.39.0"

  create_role                   = true
  role_name                     = "AmazonEFSTFEBSCSIRole-${module.eks.cluster_name}"
  provider_url                  = module.eks.oidc_provider
  role_policy_arns              = [data.aws_iam_policy.efs_csi_policy.arn]
  oidc_fully_qualified_subjects = ["system:serviceaccount:kube-system:efs-csi-controller-sa"]
}

#################### EFS ####################################################

module "efs" {
  source = "./modules/efs"

  vpc_id          = module.vpc.vpc_id
  vpc_cidr_block  = module.vpc.vpc_cidr_block
  private_subnets = module.vpc.private_subnets
}










#################### CLEANUP ##############################################
resource "null_resource" "pre_destroy_cleanup" {
  triggers = {
    always_run = "${timestamp()}"
  }

  provisioner "local-exec" {
    command = "echo 'Ensure all dependent resources are cleared'"
  }

  depends_on = [
    module.eks,
    module.vpc
  ]

  lifecycle {
    create_before_destroy = true
  }
}
