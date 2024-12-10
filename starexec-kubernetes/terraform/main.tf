
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
  source  = "terraform-aws-modules/vpc/aws"
  version = "5.8.1"

  name = "starexec-vpc"

  cidr = "10.0.0.0/16"
  azs  = slice(data.aws_availability_zones.available.names, 0, 3)

  private_subnets = ["10.0.1.0/24", "10.0.2.0/24", "10.0.3.0/24"]
  public_subnets  = ["10.0.4.0/24", "10.0.5.0/24", "10.0.6.0/24"]

  enable_nat_gateway   = true
  single_nat_gateway   = true
  enable_dns_hostnames = true

  public_subnet_tags = {
    "kubernetes.io/role/elb" = 1
  }

  private_subnet_tags = {
    "kubernetes.io/role/internal-elb" = 1
  }
}


data "external" "max_nodes" {
  program = ["bash", "./configuration_json_wrapper.sh", "maxNodes"]
}

data "external" "desired_nodes" {
  program = ["bash", "./configuration_json_wrapper.sh", "desiredNodes"]
}

data "external" "instance_type" {
  program = ["bash", "./configuration_json_wrapper.sh", "instanceType"]
}












#################### EKS ####################################################

# data "aws_eks_cluster_versions" "available" {}

# locals {
#   latest_k8s_version = versionmax(data.aws_eks_cluster_versions.available.versions)
# }


module "eks" {
  source  = "terraform-aws-modules/eks/aws"
  version = "20.8.5"

  cluster_name    = local.cluster_name
  cluster_version = "1.32"
  # cluster_version = local.latest_k8s_version

  cluster_endpoint_public_access           = true
  enable_cluster_creator_admin_permissions = true

  cluster_addons = {
    aws-efs-csi-driver = {
      service_account_role_arn = module.irsa-efs-csi.iam_role_arn
    }
  }

  vpc_id     = module.vpc.vpc_id
  subnet_ids = module.vpc.private_subnets

  eks_managed_node_group_defaults = {
    ami_type = "AL2_x86_64"
  }

  eks_managed_node_groups = {
    computenodes = {
      name = "computenodes"

      instance_types = [data.external.instance_type.result.value]
      min_size     = 1
      max_size     = tonumber(data.external.max_nodes.result.value)
      desired_size = tonumber(data.external.desired_nodes.result.value)
    }
    
    headnode = {
      name = "headnode"

      instance_types = [data.external.instance_type.result.value]
      min_size     = 1
      max_size     = 1
      desired_size = 1
    }
  }
}










#################### EFS ####################################################

data "aws_iam_policy" "efs_csi_policy" {
  arn = "arn:aws:iam::aws:policy/service-role/AmazonEFSCSIDriverPolicy"
}

module "irsa-efs-csi" {
  source  = "terraform-aws-modules/iam/aws//modules/iam-assumable-role-with-oidc"
  version = "5.39.0"

  create_role                   = true
  role_name                     = "AmazonEFSTFEBSCSIRole-${module.eks.cluster_name}"
  provider_url                  = module.eks.oidc_provider
  role_policy_arns              = [data.aws_iam_policy.efs_csi_policy.arn]
  oidc_fully_qualified_subjects = ["system:serviceaccount:kube-system:efs-csi-controller-sa"]
}

resource "aws_efs_file_system" "example" {
  creation_token = "efs-example"

  tags = {
    Name = "StarExec-EFS"
  }
}

resource "aws_efs_mount_target" "example" {
  for_each           = toset(module.vpc.private_subnets)
  file_system_id     = aws_efs_file_system.example.id
  subnet_id          = each.value
  security_groups    = [aws_security_group.efs_sg.id]
}

resource "aws_security_group" "efs_sg" {
  vpc_id = module.vpc.vpc_id

  ingress {
    from_port   = 2049
    to_port     = 2049
    protocol    = "tcp"
    cidr_blocks = [module.vpc.vpc_cidr_block]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "EFS Security Group"
  }
}










#################### EFS Access Points ######################################
resource "aws_efs_access_point" "voldb" {
  file_system_id = aws_efs_file_system.example.id
  
  posix_user {
    gid = 0
    uid = 0
  }
  
  root_directory {
    path = "/voldb"
    creation_info {
      owner_gid = 0
      owner_uid = 0
      permissions = 0777
    }
  }
}

resource "aws_efs_access_point" "volstar" {
  file_system_id = aws_efs_file_system.example.id
  
  posix_user {
    gid = 0
    uid = 0
  }
  
  root_directory {
    path = "/volstar"
    creation_info {
      owner_gid = 0
      owner_uid = 0
      permissions = 0777
    }
  }
}

resource "aws_efs_access_point" "volpro" {
  file_system_id = aws_efs_file_system.example.id
  
  posix_user {
    gid = 0
    uid = 0
  }
  
  root_directory {
    path = "/volpro"
    creation_info {
      owner_gid = 0
      owner_uid = 0
      permissions = 0777
    }
  }
}

# resource "aws_efs_access_point" "volexport" {
#   file_system_id = aws_efs_file_system.example.id
  
#   posix_user {
#     gid = 0
#     uid = 0
#   }
  
#   root_directory {
#     path = "/volexport"
#     creation_info {
#       owner_gid = 0
#       owner_uid = 0
#       permissions = 0777
#     }
#   }
# }










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
