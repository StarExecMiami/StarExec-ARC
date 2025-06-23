# Makefile for StarExec Kubernetes Infrastructure Management
# Author: DevOps Team
# Description: Manages EKS cluster, EFS storage, and StarExec deployment

# Shell configuration
SHELL := /bin/bash
.SHELLFLAGS := -euo pipefail -c

# Make configuration
.DEFAULT_GOAL := help
.PHONY: help init plan create-cluster destroy-cluster kubectl-setup
.PHONY: populate-cluster depopulate-cluster label-nodes cache-prover-image
.PHONY: get-certificate forward-domain-route53 update-node-count
.PHONY: backup-to-s3 restore-from-s3 download-from-s3 upload-to-s3
.PHONY: info connect clean validate

# Color codes for output
RED    := \033[31m
GREEN  := \033[32m
YELLOW := \033[33m
BLUE   := \033[34m
RESET  := \033[0m

# Configuration variables
# These are evaluated when used (due to =) to ensure terraform init may have run.
DOMAIN ?= $(if $(origin DOMAIN),$(DOMAIN),$(shell ./configuration.sh domain 2>/dev/null || echo "starexec-arc.net"))
# Use AWS_REGION from environment, or fallback to aws configure get region
AWS_REGION ?= $(if $(origin AWS_REGION),$(AWS_REGION),$(shell aws configure get region 2>/dev/null || echo "us-east-1"))
# Use fallback cluster name if terraform is not installed or not initialized
CLUSTER_NAME = $(shell command -v terraform >/dev/null 2>&1 && terraform output -raw cluster_name 2>/dev/null || echo "starexec-cluster")
BUCKET_NAME = $(shell echo "$(CLUSTER_NAME)" | tr '[:upper:]' '[:lower:]')-backup
EFS_ID = $(shell terraform output -raw efs_file_system_id 2>/dev/null || echo "")

# Validation helpers
define check_aws_config
	@if [ -z "$(AWS_REGION)" ]; then \
		echo -e "$(RED)Error: AWS region not configured. Run 'aws configure'$(RESET)"; \
		exit 1; \
	fi
endef

define check_domain
	@if [ -z "$(DOMAIN)" ]; then \
		echo -e "$(RED)Error: Domain not configured in configuration.sh$(RESET)"; \
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
	@echo -e "$(BLUE)StarExec Kubernetes Infrastructure Management$(RESET)"
	@echo ""
	@echo -e "$(GREEN)Usage:$(RESET) make [target]"
	@echo ""
	@echo -e "$(GREEN)Main Targets:$(RESET)"
	@awk 'BEGIN {FS = ":.*## "} /^[^[:space:]].*## / {printf "  $(YELLOW)%-20s$(RESET) %s\n", $$1, $$2}' $(MAKEFILE_LIST)

# Default deployment pipeline
default: ## Run complete deployment pipeline
	@echo -e "$(BLUE)====== StarExec Deployment Pipeline ======$(RESET)"
	@echo -e "$(GREEN)1. Initializing Terraform$(RESET)"
	$(MAKE) init
	@echo -e "$(GREEN)2. Creating EKS cluster and infrastructure$(RESET)"
	$(MAKE) create-cluster
	@echo -e "$(GREEN)3. Configuring kubectl$(RESET)"
	$(MAKE) kubectl-setup
	@echo -e "$(GREEN)4. Deploying StarExec$(RESET)"
	$(MAKE) populate-cluster
	@echo -e "$(GREEN)4a. Waiting for pods to stabilize$(RESET)"
	@sleep 120
	@echo -e "$(GREEN)4b. Checking deployment status$(RESET)"
	@kubectl describe pod -l app=starexec | head -20
	@echo -e "$(GREEN)5. Configuring domain and SSL$(RESET)"
	$(MAKE) setup-domain

####################
# Infrastructure   #
####################

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
	@terraform plan -var="region=$(AWS_REGION)"

create-cluster: ## Create EKS cluster and infrastructure
	@echo -e "$(BLUE)Creating EKS cluster...$(RESET)"
	$(call check_terraform_init)
	$(call check_aws_config)
	@terraform apply -var="region=$(AWS_REGION)" -target=module.vpc -auto-approve
	@terraform apply -var="region=$(AWS_REGION)" -auto-approve

destroy-cluster: ## Destroy EKS cluster and infrastructure
	@echo -e "$(YELLOW)Destroying EKS cluster...$(RESET)"
	$(call check_aws_config)
	@if kubectl cluster-info >/dev/null 2>&1; then \
		echo -e "$(YELLOW)Cleaning up Kubernetes resources...$(RESET)"; \
		$(MAKE) depopulate-cluster; \
	fi
	@terraform destroy -var="region=$(AWS_REGION)" -auto-approve

kubectl-setup: ## Configure kubectl for EKS cluster
	@echo -e "$(BLUE)Configuring kubectl...$(RESET)"
	$(call check_aws_config)
	@aws eks --region $(AWS_REGION) update-kubeconfig \
		--name $(CLUSTER_NAME)

update-node-count: ## Update EKS node group size
	@echo -e "$(YELLOW)Updating node count...$(RESET)"
	@echo -e "$(YELLOW)This will apply all Terraform changes$(RESET)"
	@sleep 5
	$(call check_aws_config)
	@terraform apply -var="region=$(AWS_REGION)" -auto-approve

####################
# Kubernetes       #
####################

populate-cluster: label-nodes ## Deploy StarExec to cluster
	@echo -e "$(BLUE)Deploying StarExec...$(RESET)"
	@export EFS_ID=$(EFS_ID) && \
	export VOLDB_LABEL=$$(terraform output -raw efs_voldb_access_point_id) && \
	export VOLSTAR_LABEL=$$(terraform output -raw efs_volstar_access_point_id) && \
	export VOLPRO_LABEL=$$(terraform output -raw efs_volpro_access_point_id) && \
	envsubst < YAMLFiles/storage.yaml.template > YAMLFiles/storage.yaml
	@cd YAMLFiles && kubectl apply -f .
	@$(MAKE) setup-ssh-keys

depopulate-cluster: ## Remove StarExec from cluster
	@echo -e "$(YELLOW)Removing StarExec deployment...$(RESET)"
	@for file in ingress service deployment headnode-role-binding headnode-role headnode-service-account pvcs storage; do \
		echo "Deleting $$file..."; \
		kubectl delete -f YAMLFiles/$$file.yaml --wait=true --timeout=300s || true; \
	done

label-nodes: enable-k8s-proxy ## Label cluster nodes appropriately
	@echo -e "$(BLUE)Labeling cluster nodes...$(RESET)"
	@for node in $$(kubectl get nodes -o jsonpath='{.items[*].metadata.name}'); do \
		nodegroup=$$(kubectl get node $$node -o jsonpath='{.metadata.labels.eks\.amazonaws\.com/nodegroup}'); \
		if echo "$$nodegroup" | grep -q "computenodes"; then \
			echo "Labeling compute node: $$node"; \
			kubectl label nodes $$node nodegroup=computenodes --overwrite; \
			$(MAKE) add-extended-resource NODE=$$node; \
		elif echo "$$nodegroup" | grep -q "headnode"; then \
			echo "Labeling head node: $$node"; \
			kubectl label nodes $$node nodegroup=headnode --overwrite; \
		fi; \
	done
	@kubectl get nodes -L nodegroup

add-extended-resource: ## Add extended resource to node (internal)
	@curl -s --header "Content-Type: application/json-patch+json" \
		--request PATCH \
		--data '[{"op": "add", "path": "/status/capacity/example.com~1unicorn", "value": "1"}]' \
		"http://localhost:8001/api/v1/nodes/$(NODE)/status" >/dev/null || true

enable-k8s-proxy: ## Enable Kubernetes API proxy
	@echo -e "$(BLUE)Starting Kubernetes API proxy...$(RESET)"
	@pkill -f "kubectl proxy" || true
	@sleep 2
	@kubectl proxy >/dev/null 2>&1 &

cache-prover-image: ## Cache prover image on cluster nodes
	@if [ -z "$(prover_image)" ]; then \
		echo -e "$(RED)Usage: make cache-prover-image prover_image=docker.io/image:tag$(RESET)"; \
		exit 1; \
	fi
	@echo -e "$(BLUE)Caching prover image: $(prover_image)$(RESET)"
	@kubectl create deployment cache-test --image=$(prover_image)
	@echo "Waiting for image pull..."
	@while [ "$$(kubectl get pods -l app=cache-test -o jsonpath='{.items[0].status.phase}' 2>/dev/null)" != "Running" ]; do \
		echo "Waiting for pod..."; \
		sleep 5; \
	done
	@kubectl delete deployment cache-test

setup-ssh-keys: ## Setup SSH keys for StarExec (internal)
	@if [ ! -f ../../starexec-containerised/starexec_podman_key ]; then \
		echo -e "$(BLUE)Generating SSH keys...$(RESET)"; \
		ssh-keygen -t rsa -N "" -f ../../starexec-containerised/starexec_podman_key; \
	fi
	@if ! kubectl get secret starexec-ssh-key >/dev/null 2>&1; then \
		echo -e "$(BLUE)Creating SSH key secret...$(RESET)"; \
		kubectl create secret generic starexec-ssh-key \
			--from-file=starexec_ssh_key=../../starexec-containerised/starexec_podman_key; \
	fi

####################
# Domain & SSL     #
####################

setup-domain: ## Setup domain forwarding and SSL
	$(call check_domain)
	@if aws route53 list-hosted-zones | grep -q "$(DOMAIN)"; then \
		echo -e "$(GREEN)Setting up domain forwarding...$(RESET)"; \
		$(MAKE) forward-domain-route53; \
		echo -e "$(GREEN)Waiting for DNS propagation...$(RESET)"; \
		sleep 120; \
		echo -e "$(GREEN)Obtaining SSL certificate...$(RESET)"; \
		$(MAKE) get-certificate; \
	else \
		echo -e "$(YELLOW)Domain $(DOMAIN) not found in Route53$(RESET)"; \
		echo -e "$(YELLOW)Please manually configure DNS or run 'make get-certificate'$(RESET)"; \
	fi

get-certificate: ## Obtain SSL certificate for domain
	@echo -e "$(BLUE)Obtaining SSL certificate...$(RESET)"
	$(call check_domain)
	@POD_NAME=$$(kubectl get pods -l app=starexec -o jsonpath='{.items[0].metadata.name}' 2>/dev/null); \
	if [ -z "$$POD_NAME" ]; then \
		echo -e "$(RED)No StarExec pod found$(RESET)"; \
		exit 1; \
	fi; \
	echo "Using pod: $$POD_NAME"; \
	kubectl cp get_certificate.sh $$POD_NAME:/tmp/get_certificate.sh; \
	kubectl exec $$POD_NAME -- chmod +x /tmp/get_certificate.sh; \
	kubectl exec $$POD_NAME -- /tmp/get_certificate.sh $(DOMAIN)

forward-domain-route53: ## Configure Route53 DNS forwarding
	@echo -e "$(BLUE)Configuring Route53 DNS...$(RESET)"
	$(call check_domain)
	@EXTERNAL_DOMAIN=$$(kubectl get svc starexec-service -o jsonpath='{.status.loadBalancer.ingress[0].hostname}' 2>/dev/null); \
	if [ -z "$$EXTERNAL_DOMAIN" ]; then \
		echo -e "$(RED)Load balancer not ready$(RESET)"; \
		exit 1; \
	fi; \
	ELB_NAME=$$(echo "$$EXTERNAL_DOMAIN" | cut -d'-' -f1); \
	ELB_ZONE_ID=$$(aws elb describe-load-balancers --load-balancer-names $$ELB_NAME \
		--query 'LoadBalancerDescriptions[0].CanonicalHostedZoneNameID' --output text); \
	HOSTED_ZONE_ID=$$(aws route53 list-hosted-zones-by-name --dns-name $(DOMAIN) \
		--query "HostedZones[?Name=='$(DOMAIN).'].Id" --output text | cut -d'/' -f3); \
	aws route53 change-resource-record-sets --hosted-zone-id $$HOSTED_ZONE_ID \
		--change-batch '{"Changes":[{"Action":"UPSERT","ResourceRecordSet":{"Name":"$(DOMAIN).","Type":"A","AliasTarget":{"HostedZoneId":"'$$ELB_ZONE_ID'","DNSName":"'$$EXTERNAL_DOMAIN'.","EvaluateTargetHealth":false}}}]}'; \
	echo -e "$(GREEN)DNS update completed$(RESET)"
####################
# Backup & Restore #
####################

backup-to-s3: init ## Backup EFS data to S3
	@echo -e "$(BLUE)Starting EFS to S3 backup...$(RESET)"
	@$(MAKE) create-s3-bucket
	@$(MAKE) create-datasync-role
	@$(MAKE) run-backup-task

restore-from-s3: init ## Restore EFS data from S3
	@echo -e "$(BLUE)Starting S3 to EFS restore...$(RESET)"
	@$(MAKE) create-datasync-role
	@$(MAKE) run-restore-task

download-from-s3: ## Download S3 backup to local directory
	@echo -e "$(BLUE)Downloading from S3...$(RESET)"
	@aws s3 sync s3://$(BUCKET_NAME)/ ./s3-backup/ --delete

upload-to-s3: ## Upload local directory to S3
	@echo -e "$(BLUE)Uploading to S3...$(RESET)"
	@aws s3 sync ./s3-backup/ s3://$(BUCKET_NAME)/ --delete

create-s3-bucket: ## Create S3 backup bucket (internal)
	@aws s3api head-bucket --bucket $(BUCKET_NAME) >/dev/null 2>&1 || \
	aws s3api create-bucket --bucket $(BUCKET_NAME) \
		--create-bucket-configuration LocationConstraint=$(AWS_REGION) --region $(AWS_REGION)

delete-s3-bucket: ## Delete S3 backup bucket
	@echo -e "$(YELLOW)Deleting S3 bucket: $(BUCKET_NAME)$(RESET)"
	@aws s3 rb s3://$(BUCKET_NAME) --force

####################
# Utilities        #
####################

info: ## Show cluster information
	@echo -e "$(BLUE)Cluster Information:$(RESET)"
	@kubectl get all --all-namespaces

connect: ## Connect to StarExec pod
	@POD_NAME=$$(kubectl get pods -l app=starexec -o jsonpath='{.items[0].metadata.name}' 2>/dev/null); \
	if [ -z "$$POD_NAME" ]; then \
		echo -e "$(RED)No StarExec pod found$(RESET)"; \
		exit 1; \
	fi; \
	kubectl exec -it $$POD_NAME -- /bin/bash

clean: ## Clean up local files and stop processes
	@echo -e "$(YELLOW)Cleaning up...$(RESET)"
	@pkill -f "kubectl proxy" || true
	@rm -f YAMLFiles/storage.yaml
	@rm -f datasync-s3-access-policy.json

# Internal targets for backup operations
create-datasync-role: ## Create DataSync IAM role and policies (internal)
	@echo -e "$(BLUE)Creating DataSync IAM role...$(RESET)"
	@ROLE_EXISTS=$$(aws iam get-role --role-name DataSyncServiceRole 2>/dev/null || echo "NOT_FOUND"); \
	if echo "$$ROLE_EXISTS" | grep -q "NOT_FOUND"; then \
		echo "Creating DataSync service role..."; \
		aws iam create-role --role-name DataSyncServiceRole \
			--assume-role-policy-document '{ \
				"Version": "2012-10-17", \
				"Statement": [{ \
					"Effect": "Allow", \
					"Principal": {"Service": "datasync.amazonaws.com"}, \
					"Action": "sts:AssumeRole" \
				}] \
			}'; \
		aws iam attach-role-policy --role-name DataSyncServiceRole \
			--policy-arn arn:aws:iam::aws:policy/service-role/AWSDataSyncServiceRolePolicy; \
	else \
		echo "DataSync service role already exists"; \
	fi
	@cat > datasync-s3-access-policy.json << 'EOF'
	{
		"Version": "2012-10-17",
		"Statement": [
			{
				"Effect": "Allow",
				"Action": [
					"s3:GetBucketLocation",
					"s3:ListBucket",
					"s3:ListBucketMultipartUploads"
				],
				"Resource": "arn:aws:s3:::$(BUCKET_NAME)"
			},
			{
				"Effect": "Allow",
				"Action": [
					"s3:AbortMultipartUpload",
					"s3:DeleteObject",
					"s3:GetObject",
					"s3:GetObjectTagging",
					"s3:ListMultipartUploadParts",
					"s3:PutObject",
					"s3:PutObjectTagging"
				],
				"Resource": "arn:aws:s3:::$(BUCKET_NAME)/*"
			}
		]
	}
	EOF
	@POLICY_EXISTS=$$(aws iam get-role-policy --role-name DataSyncServiceRole --policy-name DataSyncS3AccessPolicy 2>/dev/null || echo "NOT_FOUND"); \
	if echo "$$POLICY_EXISTS" | grep -q "NOT_FOUND"; then \
		echo "Creating S3 access policy..."; \
		aws iam put-role-policy --role-name DataSyncServiceRole \
			--policy-name DataSyncS3AccessPolicy \
			--policy-document file://datasync-s3-access-policy.json; \
	else \
		echo "S3 access policy already exists"; \
	fi

run-backup-task: ## Execute EFS to S3 backup using DataSync (internal)
	@echo -e "$(BLUE)Setting up and running backup task...$(RESET)"
	$(call check_aws_config)
	@if [ -z "$(EFS_ID)" ]; then \
		exit 1; \
	fi
	@ACCOUNT_ID=$$(aws sts get-caller-identity --query Account --output text); \
	 VPC_ID=$$(terraform output -raw vpc_id); \
	 SUBNET_ID=$$(terraform output -raw private_subnets | jq -r '.[0]'); \
	 SECURITY_GROUP_ID=$$(terraform output -raw worker_security_group_id); \
	 echo -e "$(BLUE)Creating DataSync locations...$(RESET)"
	@EFS_LOCATION_ARN=$$(aws datasync create-location-efs \
		--efs-filesystem-arn "arn:aws:elasticfilesystem:$(AWS_REGION):$$ACCOUNT_ID:file-system/$(EFS_ID)" \
		--ec2-config SubnetArn="arn:aws:ec2:$(AWS_REGION):$$ACCOUNT_ID:subnet/$$SUBNET_ID",SecurityGroupArns="arn:aws:ec2:$(AWS_REGION):$$ACCOUNT_ID:security-group/$$SECURITY_GROUP_ID" \
		--query LocationArn --output text 2>/dev/null || \
		aws datasync list-locations --query 'Locations[?contains(LocationUri, `$(EFS_ID)`)].LocationArn' --output text | head -1)
	@S3_LOCATION_ARN=$$(aws datasync create-location-s3 \
		--s3-bucket-arn "arn:aws:s3:::$(BUCKET_NAME)" \
		--s3-config BucketAccessRoleArn="arn:aws:iam::$$ACCOUNT_ID:role/DataSyncServiceRole" \
		--query LocationArn --output text 2>/dev/null || \
		aws datasync list-locations --query 'Locations[?contains(LocationUri, `$(BUCKET_NAME)`)].LocationArn' --output text | head -1)
	@echo -e "$(BLUE)Creating backup task...$(RESET)"
	@TASK_ARN=$$(aws datasync create-task \
		--source-location-arn "$$EFS_LOCATION_ARN" \
		--destination-location-arn "$$S3_LOCATION_ARN" \
		--name "starexec-efs-backup-$$(date +%Y%m%d-%H%M%S)" \
		--options VerifyMode=POINT_IN_TIME_CONSISTENT,OverwriteMode=ALWAYS,Atime=BEST_EFFORT,Mtime=PRESERVE,Uid=INT_VALUE,Gid=INT_VALUE,PreserveDeletedFiles=PRESERVE,PreserveDevices=NONE,PosixPermissions=PRESERVE,BytesPerSecond=-1,TaskQueueing=ENABLED,LogLevel=TRANSFER \
		--query TaskArn --output text)
	@echo -e "$(GREEN)Starting backup task: $$TASK_ARN$(RESET)"
	@EXECUTION_ARN=$$(aws datasync start-task-execution --task-arn "$$TASK_ARN" --query TaskExecutionArn --output text)
	@echo -e "$(BLUE)Monitoring backup progress (Execution: $$EXECUTION_ARN)$(RESET)"
	@while true; do \
		STATUS=$$(aws datasync describe-task-execution --task-execution-arn "$$EXECUTION_ARN" --query Status --output text); \
		case "$$STATUS" in \
			"QUEUED"|"LAUNCHING"|"PREPARING"|"TRANSFERRING"|"VERIFYING") \
				echo -e "$(YELLOW)Backup status: $$STATUS$(RESET)"; \
				sleep 30; \
				;; \
			"SUCCESS") \
				echo -e "$(GREEN)Backup completed successfully$(RESET)"; \
				aws datasync describe-task-execution --task-execution-arn "$$EXECUTION_ARN" \
					--query '{FilesTransferred:FilesTransferred,BytesTransferred:BytesTransferred,Status:Status}' \
					--output table; \
				break; \
				;; \
			"ERROR") \
				echo -e "$(RED)Backup failed$(RESET)"; \
				aws datasync describe-task-execution --task-execution-arn "$$EXECUTION_ARN" \
					--query '{Status:Status,ErrorCode:ErrorCode,ErrorDetail:ErrorDetail}' \
					--output table; \
				exit 1; \
				;; \
			*) \
				echo -e "$(RED)Unknown status: $$STATUS$(RESET)"; \
				exit 1; \
				;; \
		esac; \
	done

run-restore-task: ## Execute S3 to EFS restore using DataSync (internal)
	@echo -e "$(BLUE)Setting up and running restore task...$(RESET)"
	$(call check_aws_config)
	@if [ -z "$(EFS_ID)" ]; then \
		echo -e "$(RED)Error: EFS ID not found$(RESET)"; \
		exit 1; \
	fi
	@if ! aws s3api head-bucket --bucket $(BUCKET_NAME) >/dev/null 2>&1; then \
		echo -e "$(RED)Error: S3 bucket $(BUCKET_NAME) does not exist$(RESET)"; \
		exit 1; \
	fi
	@echo -e "$(YELLOW)WARNING: This will overwrite existing data in EFS$(RESET)"
	@sleep 10
	@ACCOUNT_ID=$$(aws sts get-caller-identity --query Account --output text); \
	 VPC_ID=$$(terraform output -raw vpc_id); \
	 SUBNET_ID=$$(terraform output -raw private_subnets | jq -r '.[0]'); \
	 SECURITY_GROUP_ID=$$(terraform output -raw worker_security_group_id); \
	 echo -e "$(BLUE)Creating DataSync locations...$(RESET)"
	@S3_LOCATION_ARN=$$(aws datasync create-location-s3 \
		--s3-bucket-arn "arn:aws:s3:::$(BUCKET_NAME)" \
		--s3-config BucketAccessRoleArn="arn:aws:iam::$$ACCOUNT_ID:role/DataSyncServiceRole" \
		--query LocationArn --output text 2>/dev/null || \
		aws datasync list-locations --query 'Locations[?contains(LocationUri, `$(BUCKET_NAME)`)].LocationArn' --output text | head -1)
	@EFS_LOCATION_ARN=$$(aws datasync create-location-efs \
		--efs-filesystem-arn "arn:aws:elasticfilesystem:$(AWS_REGION):$$ACCOUNT_ID:file-system/$(EFS_ID)" \
		--ec2-config SubnetArn="arn:aws:ec2:$(AWS_REGION):$$ACCOUNT_ID:subnet/$$SUBNET_ID",SecurityGroupArns="arn:aws:ec2:$(AWS_REGION):$$ACCOUNT_ID:security-group/$$SECURITY_GROUP_ID" \
		--query LocationArn --output text 2>/dev/null || \
		aws datasync list-locations --query 'Locations[?contains(LocationUri, `$(EFS_ID)`)].LocationArn' --output text | head -1)
	@echo -e "$(BLUE)Creating restore task...$(RESET)"
	@TASK_ARN=$$(aws datasync create-task \
		--source-location-arn "$$S3_LOCATION_ARN" \
		--destination-location-arn "$$EFS_LOCATION_ARN" \
		--name "starexec-efs-restore-$$(date +%Y%m%d-%H%M%S)" \
		--options VerifyMode=POINT_IN_TIME_CONSISTENT,OverwriteMode=ALWAYS,Atime=BEST_EFFORT,Mtime=PRESERVE,Uid=INT_VALUE,Gid=INT_VALUE,PreserveDeletedFiles=REMOVE,PreserveDevices=NONE,PosixPermissions=PRESERVE,BytesPerSecond=-1,TaskQueueing=ENABLED,LogLevel=TRANSFER \
		--query TaskArn --output text)
	@echo -e "$(GREEN)Starting restore task: $$TASK_ARN$(RESET)"
	@EXECUTION_ARN=$$(aws datasync start-task-execution --task-arn "$$TASK_ARN" --query TaskExecutionArn --output text)
	@echo -e "$(BLUE)Monitoring restore progress (Execution: $$EXECUTION_ARN)$(RESET)"
	@while true; do \
		STATUS=$$(aws datasync describe-task-execution --task-execution-arn "$$EXECUTION_ARN" --query Status --output text); \
		case "$$STATUS" in \
			"QUEUED"|"LAUNCHING"|"PREPARING"|"TRANSFERRING"|"VERIFYING") \
				echo -e "$(YELLOW)Restore status: $$STATUS$(RESET)"; \
				sleep 30; \
				;; \
			"SUCCESS") \
				echo -e "$(GREEN)Restore completed successfully$(RESET)"; \
				aws datasync describe-task-execution --task-execution-arn "$$EXECUTION_ARN" \
					--query '{FilesTransferred:FilesTransferred,BytesTransferred:BytesTransferred,Status:Status}' \
					--output table; \
				break; \
				;; \
			"ERROR") \
				echo -e "$(RED)Restore failed$(RESET)"; \
				aws datasync describe-task-execution --task-execution-arn "$$EXECUTION_ARN" \
					--query '{Status:Status,ErrorCode:ErrorCode,ErrorDetail:ErrorDetail}' \
					--output table; \
				exit 1; \
				;; \
			*) \
				echo -e "$(RED)Unknown status: $$STATUS$(RESET)"; \
				exit 1; \
				;; \
		esac; \
	done
	@echo -e "$(GREEN)Restore operation completed. You may need to restart pods to pick up restored data.$(RESET)"

