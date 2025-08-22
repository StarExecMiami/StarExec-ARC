# Copyright (c) HashiCorp, Inc.
# SPDX-License-Identifier: MPL-2.0

terraform {

  backend "s3" {
    bucket         = "starexec-kubernetes-terraform-state-kxiu6ah2"
    key            = "terraform.tfstate"
    region         = "us-east-1"
    dynamodb_table = "starexec-kubernetes-terraform-locks"
    encrypt        = true
  }

  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.47.0"
    }

    random = {
      source  = "hashicorp/random"
      version = "~> 3.6.1"
    }

    tls = {
      source  = "hashicorp/tls"
      version = "~> 4.0.5"
    }

    cloudinit = {
      source  = "hashicorp/cloudinit"
      version = "~> 2.3.4"
    }

    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = ">= 2.18"
    }

    helm = {
      source  = "hashicorp/helm"
      version = "~> 2.16.0"
    }
  }

  required_version = "~> 1.3"
}

