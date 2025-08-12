# Makefile for StarExec EKS Infrastructure Management
# Description: Manages EKS cluster provisioning and cloud resources

# Shell configuration
SHELL := /bin/bash
.SHELLFLAGS := -euo pipefail -c

# Make configuration
.DEFAULT_GOAL := help
.PHONY: help init plan apply destroy validate clean kubectl-setup info

# Color codes for output
RED    := \033[31m
GREEN  := \033[32m
YELLOW := \033[33m
BLUE   := \033[34m
RESET  := \033[0m

# Configuration variables
AWS_REGION ?= $(shell bash -c 'terraform output -raw region 2>/dev/null || aws configure get region 2>/dev/null || echo "us-east-1"')
DOMAIN ?= $(shell bash -c 'terraform output -raw domain_name 2>/dev/null || echo "starexec-arc.net"')

# Validation helpers
define check_aws_config
	@if [ -z "$(AWS_REGION)" ]; then \
		echo -e "$(RED)Error: AWS region not configured. Run 'aws configure'$(RESET)"; \
		exit 1; \
	fi
endef

define check_terraform_init
	@if [ ! -d ".terraform" ]; then \
		echo -e "$(YELLOW)Terraform not initialized. Running init...$(RESET)"; \
		$(MAKE) init; \
	fi
endef

# Help target
help: ## Show this help message
	@echo -e "$(BLUE)StarExec EKS Infrastructure Management$(RESET)"
	@echo ""
	@echo -e "$(GREEN)Usage:$(RESET) make [target]"
	@echo ""
	@echo -e "$(GREEN)Infrastructure Targets:$(RESET)"
	@awk 'BEGIN {FS = ":.*## "} /^[^[:space:]].*## / {printf "  $(YELLOW)%-20s$(RESET) %s\n", $$1, $$2}' $(MAKEFILE_LIST)

init: ## Initialize Terraform
	@echo -e "$(BLUE)Initializing Terraform...$(RESET)"
	@terraform init -upgrade

validate: ## Validate Terraform configuration
	@echo -e "$(BLUE)Validating Terraform configuration...$(RESET)"
	$(call check_terraform_init)
	@terraform validate
	@terraform fmt

plan: ## Show Terraform execution plan
	@echo -e "$(BLUE)Planning Terraform changes...$(RESET)"
	$(call check_terraform_init)
	$(call check_aws_config)
	@terraform plan -var="region=$(AWS_REGION)" -var="domain=$(DOMAIN)"

apply: ## Create EKS cluster and infrastructure
	@echo -e "$(BLUE)Creating EKS cluster and infrastructure...$(RESET)"
	$(call check_terraform_init)
	@terraform apply -var="region=$(AWS_REGION)" -var="domain=$(DOMAIN)" -auto-approve
	@echo "Saving cluster name to .cluster_name file..."
	@terraform output -raw cluster_name > .cluster_name
	@echo -e "$(GREEN)Infrastructure provisioning complete.$(RESET)"

destroy: ## Destroy EKS cluster and infrastructure
	@echo -e "$(YELLOW)Destroying EKS cluster...$(RESET)"
	$(call check_terraform_init)
	$(call check_aws_config)
	@echo -e "$(YELLOW)WARNING: This will destroy all infrastructure!$(RESET)"
	@read -p "Are you sure? (y/N): " confirm && [ "$$confirm" = "y" ]
	@terraform destroy -var="region=$(AWS_REGION)" -auto-approve
	@rm -f .cluster_name
	@echo -e "$(GREEN)Infrastructure destroyed.$(RESET)"

kubectl-setup: ## Configure kubectl for the EKS cluster
	@echo -e "$(BLUE)Configuring kubectl...$(RESET)"
	@if [ ! -f ".cluster_name" ]; then \
		echo -e "$(RED)Cluster name file not found. Run 'make apply' first.$(RESET)"; \
		exit 1; \
	fi
	@CLUSTER_NAME_FOR_KUBECTL=$$(grep -o 'starexec-eks-[a-zA-Z0-9-]*' .cluster_name | head -n 1); \
	echo "Cluster name is: '$$CLUSTER_NAME_FOR_KUBECTL'"; \
	aws eks update-kubeconfig --name "$$CLUSTER_NAME_FOR_KUBECTL" --region $(AWS_REGION)
	@echo -e "$(GREEN)kubectl configured successfully.$(RESET)"

info: ## Show infrastructure information
	@echo -e "$(BLUE)Infrastructure Information:$(RESET)"
	@terraform output

clean: ## Clean up local files
	@echo -e "$(YELLOW)Cleaning up local files...$(RESET)"
	@rm -f .cluster_name
	@rm -f datasync-s3-access-policy.json
	@rm -f YAMLFiles/storage.yaml
	@echo -e "$(GREEN)Local cleanup complete.$(RESET)"

