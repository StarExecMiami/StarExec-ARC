variable "cluster_name" {
  description = "Name of the EKS cluster"
  type        = string
}

variable "oidc_provider" {
  description = "The OpenID Connect identity provider URL"
  type        = string
}