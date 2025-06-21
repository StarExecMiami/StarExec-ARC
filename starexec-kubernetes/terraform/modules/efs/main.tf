# EFS Module
# Responsible for creating EFS file system, mount targets, access points, and security groups

variable "vpc_id" {
  description = "ID of the VPC where EFS will be created"
  type        = string
}

variable "vpc_cidr_block" {
  description = "CIDR block of the VPC"
  type        = string
}

variable "private_subnets" {
  description = "List of private subnet IDs"
  type        = list(string)
}

resource "aws_efs_file_system" "starexec" {
  creation_token = "efs-starexec"

  tags = {
    Name = "StarExec-EFS"
  }
}

resource "aws_security_group" "efs_sg" {
  vpc_id = var.vpc_id

  ingress {
    from_port   = 2049
    to_port     = 2049
    protocol    = "tcp"
    cidr_blocks = [var.vpc_cidr_block]
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

resource "aws_efs_mount_target" "starexec" {
  for_each        = { for idx, subnet in var.private_subnets : idx => subnet }
  file_system_id  = aws_efs_file_system.starexec.id
  subnet_id       = each.value
  security_groups = [aws_security_group.efs_sg.id]
}

# EFS Access Points
resource "aws_efs_access_point" "voldb" {
  file_system_id = aws_efs_file_system.starexec.id
  
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
  file_system_id = aws_efs_file_system.starexec.id
  
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
  file_system_id = aws_efs_file_system.starexec.id
  
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

output "efs_file_system_id" {
  description = "ID of the EFS file system"
  value       = aws_efs_file_system.starexec.id
}

output "voldb_access_point_id" {
  description = "ID of the voldb access point"
  value       = aws_efs_access_point.voldb.id
}

output "volstar_access_point_id" {
  description = "ID of the volstar access point"
  value       = aws_efs_access_point.volstar.id
}

output "volpro_access_point_id" {
  description = "ID of the volpro access point"
  value       = aws_efs_access_point.volpro.id
}