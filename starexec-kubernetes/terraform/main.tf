# Copyright (c) HashiCorp, Inc.
# SPDX-License-Identifier: MPL-2.0

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
  cluster_name = "education-eks-${random_string.suffix.result}"
}

resource "random_string" "suffix" {
  length  = 8
  special = false
}

module "vpc" {
  source  = "terraform-aws-modules/vpc/aws"
  version = "5.8.1"

  name = "education-vpc"

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

module "eks" {
  source  = "terraform-aws-modules/eks/aws"
  version = "20.8.5"

  cluster_name    = local.cluster_name
  cluster_version = "1.29"

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
    one = {
      name = "everything"

      instance_types = [data.external.instance_type.result.value]
      min_size     = 1
      max_size     = tonumber(data.external.max_nodes.result.value)
      desired_size = tonumber(data.external.desired_nodes.result.value)
    }
  }
}

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
    Name = "MyEFS"
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

# Access points for voldb, volstar, volpro, and volexport:

# voldb:
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

# volstar:
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

# volpro:
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

# volexport:
resource "aws_efs_access_point" "volexport" {
  file_system_id = aws_efs_file_system.example.id
  
  posix_user {
    gid = 0
    uid = 0
  }
  
  root_directory {
    path = "/volexport"
    creation_info {
      owner_gid = 0
      owner_uid = 0
      permissions = 0777
    }
  }
}





# # Generate the SSH key pair
# resource "tls_private_key" "ssh_key" {
#   algorithm = "RSA"
#   rsa_bits  = 2048
# }

# # Save the public key
# resource "local_file" "public_key_file" {
#   content  = tls_private_key.ssh_key.public_key_openssh
#   filename = "${path.module}/ssh-keys/id_rsa.pub"
# }

# # Use the generated public key
# resource "aws_key_pair" "deployer" {
#   key_name   = "efs-deployer-key"
#   public_key = tls_private_key.ssh_key.public_key_openssh
# }

# resource "aws_instance" "init_dirs" {
#   ami           = data.aws_ami.latest_linux_ami.id
#   instance_type = "t3.micro"

#   key_name = aws_key_pair.deployer.key_name

#   # Selecting the first private subnet for the instance
#   subnet_id = element(module.vpc.private_subnets, 0)
#   security_groups = [aws_security_group.efs_sg.id]

#   user_data = <<-EOF
#               #!/bin/bash
#               sudo mount -t efs ${aws_efs_file_system.example.id}:/ /mnt/efs
#               sudo mkdir -p /mnt/efs/voldb /mnt/efs/volpro /mnt/efs/volexport /mnt/efs/volstar
#               EOF

#   tags = {
#     Name = "EFS Directory Initializer"
#   }

#   lifecycle {
#     create_before_destroy = true
#   }
# }


# # Cleanup EC2 instance after setup
# resource "null_resource" "cleanup" {
#   triggers = {
#     instance_id = aws_instance.init_dirs.id
#   }

#   provisioner "local-exec" {
#     command = "aws ec2 terminate-instances --instance-ids ${self.triggers.instance_id}"
#   }

#   depends_on = [aws_instance.init_dirs]
# }

# # Fetch the latest AMI for Ubuntu
# data "aws_ami" "latest_linux_ami" {
#   most_recent = true

#   filter {
#     name   = "name"
#     values = ["ubuntu/images/hvm-ssd/ubuntu-*-20.04-amd64-server-*"]
#   }

#   filter {
#     name   = "virtualization-type"
#     values = ["hvm"]
#   }

#   owners = ["099720109477"] # Canonical
# }
