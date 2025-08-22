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
  azs                  = slice(data.aws_availability_zones.available.names, 0, 2)
  private_subnets      = ["10.0.1.0/24", "10.0.2.0/24"]
  public_subnets       = ["10.0.4.0/24", "10.0.5.0/24"]
  enable_nat_gateway   = true
  single_nat_gateway   = true
  enable_dns_hostnames = true
}


#################### EKS ####################################################

module "eks" {
  source = "./modules/eks"

  cluster_name               = local.cluster_name
  cluster_version            = "1.32"
  vpc_id                     = module.vpc.vpc_id
  subnet_ids                 = module.vpc.private_subnets
  headnode_instance_type     = var.headnode_instance_type
  computenodes_instance_type = var.computenodes_instance_type
  desired_nodes              = var.desired_nodes
  max_nodes                  = var.max_nodes
  efs_csi_role_arn           = module.iam_efs_csi.iam_role_arn
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

  vpc_id                        = module.vpc.vpc_id
  vpc_cidr_block                = module.vpc.vpc_cidr_block
  eks_cluster_security_group_id = module.eks.cluster_security_group_id
  eks_node_security_group_id    = module.eks.node_security_group_id
  private_subnets               = module.vpc.private_subnets
}


#################### KUBERNETES PROVIDER & STORAGE CLASS #####################

provider "tls" {}

resource "kubernetes_namespace" "starexec" {
  metadata {
    name = "starexec"
  }
}

resource "tls_private_key" "starexec_key" {
  algorithm = "RSA"
  rsa_bits  = 2048
}

resource "tls_self_signed_cert" "starexec_cert" {
  private_key_pem = tls_private_key.starexec_key.private_key_pem

  subject {
    common_name  = "starexec.local"
    organization = "StarExec"
  }

  validity_period_hours = 8760 # 1 year

  allowed_uses = [
    "key_encipherment",
    "digital_signature",
    "server_auth",
  ]
}

resource "kubernetes_secret" "starexec_tls" {
  metadata {
    name      = "starexec-tls-secret"
    namespace = kubernetes_namespace.starexec.metadata[0].name
  }

  data = {
    "tls.crt" = tls_self_signed_cert.starexec_cert.cert_pem
    "tls.key" = tls_private_key.starexec_key.private_key_pem
  }

  type = "kubernetes.io/tls"

  depends_on = [
    kubernetes_namespace.starexec,
  ]
}

provider "kubernetes" {
  host                   = module.eks.cluster_endpoint
  cluster_ca_certificate = base64decode(module.eks.cluster_certificate_authority_data)

  exec {
    api_version = "client.authentication.k8s.io/v1beta1"
    command     = "aws"
    args = [
      "eks", "get-token",
      "--region", var.region,
      "--cluster-name", local.cluster_name
    ]
  }
}

resource "kubernetes_storage_class" "efs_sc" {
  metadata {
    name = "efs-sc"
  }

  storage_provisioner = "efs.csi.aws.com"
  reclaim_policy      = "Delete"

  parameters = {
    provisioningMode = "efs-ap"
    fileSystemId     = module.efs.efs_file_system_id
    accessPointId    = module.efs.shared_access_point_id
    directoryPerms   = "755"
  }

  depends_on = [module.eks]
}

resource "kubernetes_persistent_volume" "efs_pv" {
  metadata {
    name = "starexec-efs-pv"
  }

  spec {
    capacity = {
      storage = "100Gi"
    }

    volume_mode                      = "Filesystem"
    access_modes                     = ["ReadWriteMany"]
    persistent_volume_reclaim_policy = "Delete"
    storage_class_name               = "efs-sc"

    persistent_volume_source {
      csi {
        driver        = "efs.csi.aws.com"
        volume_handle = "${module.efs.efs_file_system_id}::${module.efs.shared_access_point_id}"
      }
    }
  }

  depends_on = [kubernetes_storage_class.efs_sc]

  # Pre-destroy hook to clean up PV claim reference
  provisioner "local-exec" {
    when       = destroy
    command    = <<-EOT
      kubectl patch pv starexec-efs-pv --type=merge -p '{"spec":{"claimRef":null}}' 2>/dev/null || true
      kubectl patch pv starexec-efs-pv --type=merge -p '{"metadata":{"finalizers":null}}' 2>/dev/null || true
    EOT
    on_failure = continue
  }
}

#################### HELM ####################################################

provider "helm" {
  kubernetes {
    host                   = module.eks.cluster_endpoint
    cluster_ca_certificate = base64decode(module.eks.cluster_certificate_authority_data)

    exec {
      api_version = "client.authentication.k8s.io/v1beta1"
      command     = "aws"
      args = [
        "eks", "get-token",
        "--region", var.region,
        "--cluster-name", local.cluster_name
      ]
    }
  }
}

resource "helm_release" "starexec" {
  name             = "starexec"
  chart            = "../../starexec-helm"
  namespace        = "starexec"
  create_namespace = true
  wait             = true
  timeout          = 300

  values = [
    file("../../starexec-helm/values.yaml"),
  ]

  depends_on = [
    module.eks,
    module.efs,
    kubernetes_storage_class.efs_sc,
    kubernetes_persistent_volume.efs_pv,
    kubernetes_secret.starexec_tls,
  ]
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
