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
    security_groups = [var.eks_cluster_security_group_id, var.eks_node_security_group_id]
    description = "Allow NFS traffic from EKS cluster and worker nodes"
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

# EFS Access Point - Single shared access point for all StarExec data
resource "aws_efs_access_point" "starexec_shared" {
  file_system_id = aws_efs_file_system.starexec.id
  
  posix_user {
    uid = 0
    gid = 0
  }
  
  root_directory {
    path = "/starexec"
    creation_info {
      owner_gid = 0
      owner_uid = 0
      permissions = 0755
    }
  }

  tags = {
    Name = "StarExec-Shared-AP"
    Purpose = "Shared Application Data"
  }

  depends_on = [aws_efs_mount_target.starexec]
}

data "aws_iam_policy_document" "efs_policy" {
  statement {
    sid    = "AllowAllMounts"
    effect = "Allow"
    principals {
      type        = "AWS"
      identifiers = ["*"]
    }
    actions = [
      "elasticfilesystem:ClientMount",
      "elasticfilesystem:ClientWrite",
      "elasticfilesystem:ClientRootAccess"
    ]
    resources = [aws_efs_file_system.starexec.arn]
  }
}

resource "aws_efs_file_system_policy" "starexec" {
  file_system_id = aws_efs_file_system.starexec.id
  policy         = data.aws_iam_policy_document.efs_policy.json
  depends_on     = [aws_efs_access_point.starexec_shared]
}