# EFS Module
# Responsible for creating EFS file system, mount targets, access points, and security groups

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

  depends_on = [
    aws_efs_file_system.starexec,
    aws_security_group.efs_sg
  ]
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

  depends_on = [aws_efs_mount_target.starexec]
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

  depends_on = [aws_efs_mount_target.starexec]
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

  depends_on = [aws_efs_mount_target.starexec]
}
