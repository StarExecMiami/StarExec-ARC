# make sure shell is bash, since I normally use fish:
SHELL = bash

domain := $(shell ./configuration.sh domain)

default:
	@echo "---- 1. Initializing Terraform"
	make init

	@echo "---- 2. Using Terraform to create EKS/EFS/etc in AWS"
	make create-cluster

	@echo "---- 3. Connecting kubectl to EKS cluster"
	make kubectl-setup

	@echo "---- 4. Deploying StarExec in the EKS cluster"
	make populate-cluster
	@echo "---- 4a. Waiting a bit for the head node to be up-and-running"
	sleep 120
	@echo "---- 4b. Testing (Initial lines saying "FailedScheduling" can be ignored)"
	kubectl describe pod se-depl

	@echo "---- 5. Forwarding domain "
	@if aws route53 list-hosted-zones | grep -q "$(domain)"; then \
		echo "---- 5a. Forwarding the domain to the head node URL provided by AWS"; \
		make forward-domain-route53; \
		echo "---- 5b. Installing the domain in StarExec"; \
		make reconfig-starexec; \
		echo "---- 5b. Waiting a bit for StarExec and the domain to be available"; \
		sleep 120; \
		echo "---- 5c. Getting TLS/SSL certificate"; \
		make get-certificate; \
	else \
		echo "Domain $(domain) not found in Route53."; \
		echo "Please manually forward $(domain) to the address found by 'kubectl get svc'"; \
		echo "Then run 'make reconfig-starexec' and 'make get-certificate'"; \
	fi

reconfig-starexec:
	@echo "Finding running pod for se-depl..."
	@POD_NAME=$$(kubectl get pods --selector=app=starexec -o jsonpath='{.items[0].metadata.name}'); \
	if [ -z "$$POD_NAME" ]; then \
		echo "No pod found for se-depl"; \
		exit 1; \
	fi; \
	echo "Pod found: $$POD_NAME"; \
	echo "External IP for starexec-service: $(domain)"; \
	echo "Executing reconfig script in the pod with domain $(domain)..."; \
	kubectl cp reconfig_starexec.sh $$POD_NAME:/tmp/reconfig_starexec.sh; \
	kubectl exec $$POD_NAME -- /bin/sh -c "chmod +x /tmp/reconfig_starexec.sh && /tmp/reconfig_starexec.sh $(domain)"

get-certificate:
	@echo "Finding running pod for se-depl..."
	@POD_NAME=$$(kubectl get pods --selector=app=starexec -o jsonpath='{.items[0].metadata.name}'); \
	if [ -z "$$POD_NAME" ]; then \
		echo "No pod found for se-depl"; \
		exit 1; \
	fi; \
	echo "Pod found: $$POD_NAME"; \
	echo "External IP for starexec-service: $(domain)"; \
	echo "Executing get-certificate script in the pod with domain $(domain)..."; \
	kubectl cp get_certificate.sh $$POD_NAME:/tmp/get_certificate.sh; \
	kubectl exec $$POD_NAME -- /bin/sh -c "chmod +x /tmp/get_certificate.sh && /tmp/get_certificate.sh $(domain)"

forward-domain-route53:
	@echo "Fetching external domain name from EKS service..."
	$(eval EXTERNAL_DOMAIN := $(shell kubectl get svc starexec-service -n default -o jsonpath='{.status.loadBalancer.ingress[0].hostname}'))
	@echo "External domain: $(EXTERNAL_DOMAIN)"

	@echo "Extracting ELB name from external domain..."
	$(eval ELB_NAME := $(shell echo "$(EXTERNAL_DOMAIN)" | cut -d'-' -f1))
	@echo "ELB name: $(ELB_NAME)"

	@echo "Fetching ELB Hosted Zone ID..."
	$(eval ELB_HOSTED_ZONE_ID := $(shell aws elb describe-load-balancers --load-balancer-names $(ELB_NAME) --query 'LoadBalancerDescriptions[0].CanonicalHostedZoneNameID' --output text))
	@echo "ELB Hosted Zone ID: $(ELB_HOSTED_ZONE_ID)"

	@echo "Fetching hosted zone ID from Route 53...(domain '$(domain)')"
	$(eval HOSTED_ZONE_ID := $(shell aws route53 list-hosted-zones-by-name --dns-name $(domain) --query "HostedZones[?Name=='$(domain).'].Id" --output text | cut -d'/' -f3))
	@echo "Hosted zone ID: $(HOSTED_ZONE_ID)"

	@echo "Updating Route 53 DNS record for apex domain..."
	aws route53 change-resource-record-sets --hosted-zone-id $(HOSTED_ZONE_ID) \
		--change-batch '{ "Changes": [ { "Action": "UPSERT", "ResourceRecordSet": { "Name": "$(domain).", "Type": "A", "AliasTarget": { "HostedZoneId": "$(ELB_HOSTED_ZONE_ID)", "DNSName": "$(EXTERNAL_DOMAIN).", "EvaluateTargetHealth": false } } } ] }'

	@echo "DNS update initiated."
	@echo "If this didn't work, ensure that the hosted zone and domain in Route53 have the same nameservers configured"

######################
#     Kubernetes     #
######################

cache-prover-image:
	@if [ -z "$(prover_image)" ]; then \
		echo "No prover_image specified. Please run as 'make cache-prover-image prover_image=\"docker.io/someProverImage\"'"; \
	else \
		echo "Caching prover image '$(prover_image)'..."; \
		kubectl create deployment test --image=$(prover_image); \
		while [ "$$(kubectl get pods -l app=test -o jsonpath='{.items[0].status.phase}')" != "Running" ]; do \
			echo "Waiting for image to be pulled and pod to be in Running state..."; \
			sleep 5; \
		done; \
		kubectl delete deployment test; \
	fi


enable-k8s-api-proxy:
	@echo "Restarting k8s api proxy..."
	@# List all kubectl proxy processes, filter out any that might affect the make process
	@pids=$$(ps aux | grep '[k]ubectl proxy' | grep -v grep | awk '{print $$2}'); \
	if [ -n "$$pids" ]; then \
		echo "Stopping existing kubectl proxy processes..."; \
		echo $$pids | xargs kill; \
		sleep 2; \
	fi
	@# Start kubectl proxy in the background
	@echo "Starting kubectl proxy..."
	@kubectl proxy > /dev/null 2>&1 &




label-nodes: enable-k8s-api-proxy
	@echo "Labeling compute nodes (compute node labels + k8s extended resource)..."
	# Label compute nodes
	for node in $$(kubectl get nodes -o jsonpath='{.items[*].metadata.name}'); do \
		if kubectl get node $$node -o jsonpath='{.metadata.labels.eks\.amazonaws\.com/nodegroup}' | grep -q "computenodes"; then \
			echo "Labeling compute node: $$node"; \
			kubectl label nodes $$node nodegroup=computenodes --overwrite; \
			curl --header "Content-Type: application/json-patch+json" \
				--request PATCH \
				--data '[{"op": "add", "path": "/status/capacity/example.com~1unicorn", "value": "1"}]' \
				http://localhost:8001/api/v1/nodes/$$node/status; \
		fi; \
	done

	# Label head node
	@echo "Labeling head node..."
	for node in $$(kubectl get nodes -o jsonpath='{.items[*].metadata.name}'); do \
		if kubectl get node $$node -o jsonpath='{.metadata.labels.eks\.amazonaws\.com/nodegroup}' | grep -q "headnode"; then \
			echo "Labeling head node: $$node"; \
			kubectl label nodes $$node nodegroup=headnode --overwrite; \
		fi; \
	done

	# Verify labeling
	@echo "Verifying labels:"
	@kubectl get nodes -L nodegroup

populate-cluster: label-nodes
	export EFS_ID=$$(terraform output -raw efs_file_system_id) && \
	export VOLDB_LABEL=$$(terraform output -raw efs_voldb_access_point_id) && \
	export VOLSTAR_LABEL=$$(terraform output -raw efs_volstar_access_point_id) && \
	export VOLPRO_LABEL=$$(terraform output -raw efs_volpro_access_point_id) && \
	envsubst < YAMLFiles/storage.yaml.template > YAMLFiles/storage.yaml 
	
	cd YAMLFiles && kubectl apply -f .
	if [ ! -f ../../starexec-containerised/starexec_podman_key ]; then \
		ssh-keygen -t rsa -N "" -f ../../starexec-containerised/starexec_podman_key; \
	fi

	@if ! kubectl get secret starexec-ssh-key -n default > /dev/null 2>&1; then \
		echo "Creating Kubernetes secret for SSH key..."; \
		kubectl create secret generic starexec-ssh-key --from-file=starexec_ssh_key=../../starexec-containerised/starexec_podman_key -n default; \
	else \
		echo "Kubernetes secret 'starexec-ssh-key' already exists. No need to recreate."; \
	fi


depopulate-cluster:
	@echo "Deleting Ingress..."
	@kubectl delete -f YAMLFiles/ingress.yaml --wait=true --timeout=1m || echo "Failed to delete ingress."
	
	@echo "Deleting Service..."
	@kubectl delete -f YAMLFiles/service.yaml --wait=true --timeout=1m || echo "Failed to delete service."
	
	@echo "Deleting Deployment..."
	@kubectl delete -f YAMLFiles/deployment.yaml --wait=true --timeout=1m || echo "Failed to delete deployment."
	
	@echo "Deleting Headnode Role Binding..."
	@kubectl delete -f YAMLFiles/headnode-role-binding.yaml --wait=true --timeout=1m || echo "Failed to delete headnode role binding."
	
	@echo "Deleting Headnode Role..."
	@kubectl delete -f YAMLFiles/headnode-role.yaml --wait=true --timeout=1m || echo "Failed to delete headnode role."
	
	@echo "Deleting Headnode Service Account..."
	@kubectl delete -f YAMLFiles/headnode-service-account.yaml --wait=true --timeout=1m || echo "Failed to delete headnode service account."
	
	@echo "Deleting PVCs..."
	@kubectl delete -f YAMLFiles/pvcs.yaml --wait=true --timeout=1m || echo "Failed to delete PVCs."
	
	@echo "Deleting Storage..."
	@kubectl delete -f YAMLFiles/storage.yaml --wait=true --timeout=1m || echo "Failed to delete storage."





# For changing the number of nodes in the EKS cluster (applying a change made in configuration.sh)
update-node-count:
	@echo "##############################################################################";
	@echo "Be aware that this Makefile target only updates the number of nodes";
	@echo "in the cluster according to what's in the configuration.sh file";
	@echo "";
	@echo "It does this by doing a full \"terraform apply\" command, however."
	@echo "##############################################################################";
	@sleep 10;
	@AWS_REGION=$$(aws configure list | grep region | awk '{print $$2}' | tr -d "'"); \
	if [ -z "$$AWS_REGION" ]; then \
		echo "Please first configure your aws region (you can verify it using 'aws configure list')"; \
		exit 1; \
	fi; \
	terraform apply -var="region=$$AWS_REGION" -auto-approve;

info:
	kubectl get all --all-namespaces

connect:
	kubectl exec -it $$(kubectl get pods --selector=app=starexec -o jsonpath='{.items[0].metadata.name}') -- /bin/bash

######################
# Terraform/EKS/AWS  #
######################

# Creates EKS infrastructure
create-cluster:
	@AWS_REGION=$$(aws configure list | grep region | awk '{print $$2}' | tr -d "'"); \
	if [ -z "$$AWS_REGION" ]; then \
		echo "Please first configure your aws region (you can verify it using 'aws configure list')"; \
		exit 1; \
	fi; \
	terraform apply -var="region=$$AWS_REGION" -target=module.vpc -auto-approve; \
	terraform apply -var="region=$$AWS_REGION" -auto-approve;

# Destroys EKS infrastructure
destroy-cluster:
	# run make depopulate-cluster if k8s stuff hasn't been shut down.
	@AWS_REGION=$$(aws configure list | grep region | awk '{print $$2}' | tr -d "'"); \
	# run make clean if k8s stuff hasn't been shut down.
	@if kubectl cluster-info > /dev/null 2>&1; then \
		echo "Cluster is up. Running make depopulate-cluster..."; \
		make depopulate-cluster; \
	else \
		echo "Cluster is not up. Skipping make depopulate-cluster."; \
	fi
	terraform destroy -var="region=$$AWS_REGION" -target=module.eks -auto-approve
	terraform destroy -var="region=$$AWS_REGION" -target=module.vpc -auto-approve
	terraform destroy -var="region=$$AWS_REGION" -auto-approve

# Show what *will* be created with "terraform apply" (or make create-cluster)
plan:
	terraform plan

# Initialize terraform state
init:
	terraform init -upgrade

# Terraform uses stored aws creds to setup kubectl to connect to cluster
kubectl-setup:
	aws eks --region $$(terraform output -raw region) update-kubeconfig \
		--name $$(terraform output -raw cluster_name)

######################
# S3 Backups         #
######################

BUCKET_NAME := $(shell terraform output -raw cluster_name | tr '[:upper:]' '[:lower:]')-bucket
REGION := $(shell terraform output -raw region)
EFS_FILE_SYSTEM_ID := $(shell terraform output -raw efs_file_system_id)
DATASYNC_S3_ACCESS_ROLE_NAME := DataSyncS3AccessRole

# Creates S3 bucket (does nothing if already exists)
create-s3-bucket:
	@echo "Creating S3 bucket: $(BUCKET_NAME)"
	@aws s3api head-bucket --bucket $(BUCKET_NAME) >/dev/null 2>&1 || \
	aws s3api create-bucket --bucket $(BUCKET_NAME) --create-bucket-configuration LocationConstraint=$(REGION)

# Creates IAM role for DataSync to access S3
create-datasync-iam-role:
	@echo "Creating IAM role for DataSync to access S3"
	@aws iam get-role --role-name $(DATASYNC_S3_ACCESS_ROLE_NAME) >/dev/null 2>&1 || \
	aws iam create-role --role-name $(DATASYNC_S3_ACCESS_ROLE_NAME) --assume-role-policy-document file://datasync-trust-policy.json
	@sed 's/BUCKET_NAME/$(BUCKET_NAME)/g' datasync-s3-access-policy.json.tpl > datasync-s3-access-policy.json
	@aws iam put-role-policy --role-name $(DATASYNC_S3_ACCESS_ROLE_NAME) --policy-name DataSyncS3AccessPolicy --policy-document file://datasync-s3-access-policy.json
	@rm datasync-s3-access-policy.json

# Copies data from EFS to S3
backup-to-s3-from-efs: create-s3-bucket create-datasync-iam-role
	@echo "Backing-up data from EFS to S3 bucket: $(BUCKET_NAME)"
	@AWS_ACCOUNT_ID=$$(aws sts get-caller-identity --query 'Account' --output text); \
	REGION=$(REGION); \
	EFS_FILE_SYSTEM_ID=$(EFS_FILE_SYSTEM_ID); \
	EFS_SUBNET_ID=$$(aws efs describe-mount-targets --file-system-id $(EFS_FILE_SYSTEM_ID) --query 'MountTargets[0].SubnetId' --output text); \
	MOUNT_TARGET_ID=$$(aws efs describe-mount-targets --file-system-id $(EFS_FILE_SYSTEM_ID) --query 'MountTargets[0].MountTargetId' --output text); \
	EFS_SECURITY_GROUP_IDS=$$(aws efs describe-mount-target-security-groups --mount-target-id $$MOUNT_TARGET_ID --query 'SecurityGroups' --output text); \
	EFS_SECURITY_GROUP_ARNS="[$$(for sg_id in $$EFS_SECURITY_GROUP_IDS; do printf '"arn:aws:ec2:%s:%s:security-group/%s",' $$REGION $$AWS_ACCOUNT_ID $$sg_id; done | sed 's/,$$//')]"; \
	EFS_SUBNET_ARN="arn:aws:ec2:$$REGION:$$AWS_ACCOUNT_ID:subnet/$$EFS_SUBNET_ID"; \
	EFS_FILESYSTEM_ARN="arn:aws:elasticfilesystem:$$REGION:$$AWS_ACCOUNT_ID:file-system/$$EFS_FILE_SYSTEM_ID"; \
	echo "Creating EFS Location"; \
	EFS_LOCATION_ARN=$$(aws datasync create-location-efs --efs-filesystem-arn $$EFS_FILESYSTEM_ARN --ec2-config "SubnetArn=$$EFS_SUBNET_ARN,SecurityGroupArns=$$EFS_SECURITY_GROUP_ARNS" --query 'LocationArn' --output text); \
	DATASYNC_S3_ACCESS_ROLE_ARN=$$(aws iam get-role --role-name $(DATASYNC_S3_ACCESS_ROLE_NAME) --query 'Role.Arn' --output text); \
	S3_LOCATION_ARN=$$(aws datasync create-location-s3 --s3-bucket-arn arn:aws:s3:::$(BUCKET_NAME) --s3-config '{ "BucketAccessRoleArn": "'"$$DATASYNC_S3_ACCESS_ROLE_ARN"'" }' --query 'LocationArn' --output text); \
	TASK_ARN=$$(aws datasync create-task --source-location-arn $$EFS_LOCATION_ARN --destination-location-arn $$S3_LOCATION_ARN --name EFS-to-S3-Backup --query 'TaskArn' --output text); \
	echo "Starting DataSync task $$TASK_ARN"; \
	EXECUTION_ARN=$$(aws datasync start-task-execution --task-arn $$TASK_ARN --query 'TaskExecutionArn' --output text); \
	echo "Waiting for DataSync task to complete (Execution arn $$EXECUTION_ARN)"; \
	while true; do \
		STATUS=$$(aws datasync describe-task-execution --task-execution-arn $$EXECUTION_ARN --query 'Status' --output text); \
		BYTES_TRANSFERRED=$$(aws datasync describe-task-execution --task-execution-arn $$EXECUTION_ARN --query 'BytesTransferred' --output text); \
		BYTES_WRITTEN=$$(aws datasync describe-task-execution --task-execution-arn $$EXECUTION_ARN --query 'BytesWritten' --output text); \
		echo "Task status: $$STATUS, Bytes transferred: $$BYTES_TRANSFERRED, Bytes written: $$BYTES_WRITTEN"; \
		if [ "$$BYTES_TRANSFERRED" != "None" ] && [ "$$BYTES_WRITTEN" != "None" ] && [ $$BYTES_TRANSFERRED -ne 0 ]; then \
			PERCENT=$$(echo "scale=2; $$BYTES_WRITTEN * 100 / $$BYTES_TRANSFERRED" | bc); \
			echo "Task status: $$STATUS, Progress: $$PERCENT%"; \
		else \
			echo "Task status: $$STATUS, Progress: Calculating..."; \
		fi; \
		if [ "$$STATUS" = "SUCCESS" ]; then \
			echo "DataSync task completed successfully"; \
			break; \
		elif [ "$$STATUS" = "ERROR" ]; then \
			ERROR_CODE=$$(aws datasync describe-task-execution --task-execution-arn $$EXECUTION_ARN --query 'Result.ErrorCode' --output text); \
			ERROR_DETAIL=$$(aws datasync describe-task-execution --task-execution-arn $$EXECUTION_ARN --query 'Result.ErrorDetail' --output text); \
			echo "DataSync task failed with error code: $$ERROR_CODE"; \
			echo "Error details: $$ERROR_DETAIL"; \
			exit 1; \
		else \
			sleep 10; \
		fi; \
	done
	echo "Cleaning up DataSync task and locations"; \
	aws datasync delete-task --task-arn $$TASK_ARN; \
	aws datasync delete-location --location-arn $$EFS_LOCATION_ARN; \
	aws datasync delete-location --location-arn $$S3_LOCATION_ARN

# Restores data from S3 back to EFS
restore-to-efs-from-s3: create-datasync-iam-role
	@echo "Restoring data from S3 bucket: $(BUCKET_NAME) to EFS file system: $(EFS_FILE_SYSTEM_ID)"
	@AWS_ACCOUNT_ID=$$(aws sts get-caller-identity --query 'Account' --output text); \
	REGION=$(REGION); \
	EFS_FILE_SYSTEM_ID=$(EFS_FILE_SYSTEM_ID); \
	EFS_SUBNET_ID=$$(aws efs describe-mount-targets --file-system-id $$EFS_FILE_SYSTEM_ID --query 'MountTargets[0].SubnetId' --output text); \
	MOUNT_TARGET_ID=$$(aws efs describe-mount-targets --file-system-id $$EFS_FILE_SYSTEM_ID --query 'MountTargets[0].MountTargetId' --output text); \
	EFS_SECURITY_GROUP_IDS=$$(aws efs describe-mount-target-security-groups --mount-target-id $$MOUNT_TARGET_ID --query 'SecurityGroups' --output text); \
	EFS_SECURITY_GROUP_ARNS="[$$(for sg_id in $$EFS_SECURITY_GROUP_IDS; do printf '"arn:aws:ec2:%s:%s:security-group/%s",' $$REGION $$AWS_ACCOUNT_ID $$sg_id; done | sed 's/,$$//')]"; \
	EFS_SUBNET_ARN="arn:aws:ec2:$$REGION:$$AWS_ACCOUNT_ID:subnet/$$EFS_SUBNET_ID"; \
	EFS_FILESYSTEM_ARN="arn:aws:elasticfilesystem:$$REGION:$$AWS_ACCOUNT_ID:file-system/$$EFS_FILE_SYSTEM_ID"; \
	echo "Creating EFS Location"; \
	EFS_LOCATION_ARN=$$(aws datasync create-location-efs \
		--efs-filesystem-arn $$EFS_FILESYSTEM_ARN \
		--ec2-config "SubnetArn=$$EFS_SUBNET_ARN,SecurityGroupArns=$$EFS_SECURITY_GROUP_ARNS" \
		--query 'LocationArn' --output text); \
	DATASYNC_S3_ACCESS_ROLE_ARN=$$(aws iam get-role --role-name $(DATASYNC_S3_ACCESS_ROLE_NAME) --query 'Role.Arn' --output text); \
	S3_LOCATION_ARN=$$(aws datasync create-location-s3 \
		--s3-bucket-arn arn:aws:s3:::$(BUCKET_NAME) \
		--s3-config '{ "BucketAccessRoleArn": "'"$$DATASYNC_S3_ACCESS_ROLE_ARN"'" }' \
		--query 'LocationArn' --output text); \
	echo "Creating DataSync task to restore data from S3 to EFS"; \
	TASK_ARN=$$(aws datasync create-task \
		--source-location-arn $$S3_LOCATION_ARN \
		--destination-location-arn $$EFS_LOCATION_ARN \
		--name S3-to-EFS-Restore \
		--query 'TaskArn' --output text); \
	# echo "Creating CloudWatch log group for DataSync task"; \
	# aws logs create-log-group --log-group-name /aws/datasync/S3-to-EFS-Restore; \
	# echo "Update DataSync task with CloudWatch logging"; \
	# aws datasync update-task \
	# 	--task-arn $$TASK_ARN \
	# 	--cloud-watch-log-group-arn arn:aws:logs:$$REGION:$$AWS_ACCOUNT_ID:log-group:/aws/datasync/S3-to-EFS-Restore; \
	echo "Starting DataSync task $$TASK_ARN"; \
	EXECUTION_ARN=$$(aws datasync start-task-execution \
		--task-arn $$TASK_ARN \
		--query 'TaskExecutionArn' --output text); \
	echo "Waiting for DataSync task to complete (Execution ARN: $$EXECUTION_ARN)"; \
	while true; do \
		STATUS=$$(aws datasync describe-task-execution \
			--task-execution-arn $$EXECUTION_ARN \
			--query 'Status' --output text); \
		BYTES_TRANSFERRED=$$(aws datasync describe-task-execution \
			--task-execution-arn $$EXECUTION_ARN \
			--query 'BytesTransferred' --output text); \
		BYTES_WRITTEN=$$(aws datasync describe-task-execution \
			--task-execution-arn $$EXECUTION_ARN \
			--query 'BytesWritten' --output text); \
		echo "Task status: $$STATUS, Bytes transferred: $$BYTES_TRANSFERRED, Bytes written: $$BYTES_WRITTEN"; \
		if [ "$$BYTES_TRANSFERRED" != "None" ] && [ "$$BYTES_WRITTEN" != "None" ] && [ $$BYTES_TRANSFERRED -ne 0 ]; then \
			PERCENT=$$(echo "scale=2; $$BYTES_WRITTEN * 100 / $$BYTES_TRANSFERRED" | bc); \
			echo "Task status: $$STATUS, Progress: $$PERCENT%"; \
		else \
			echo "Task status: $$STATUS, Progress: Calculating..."; \
		fi; \
		if [ "$$STATUS" = "SUCCESS" ]; then \
			echo "DataSync task completed successfully"; \
			break; \
		elif [ "$$STATUS" = "ERROR" ]; then \
			ERROR_CODE=$$(aws datasync describe-task-execution \
				--task-execution-arn $$EXECUTION_ARN \
				--query 'Result.ErrorCode' --output text); \
			ERROR_DETAIL=$$(aws datasync describe-task-execution \
				--task-execution-arn $$EXECUTION_ARN \
				--query 'Result.ErrorDetail' --output text); \
			echo "DataSync task failed with error code: $$ERROR_CODE"; \
			echo "Error details: $$ERROR_DETAIL"; \
			exit 1; \
		else \
			sleep 10; \
		fi; \
	done; \
	echo "Cleaning up DataSync task and locations"; \
	aws datasync delete-task --task-arn $$TASK_ARN; \
	aws datasync delete-location --location-arn $$EFS_LOCATION_ARN; \
	aws datasync delete-location --location-arn $$S3_LOCATION_ARN

# Downloads data from S3
download-from-s3: create-s3-bucket
	@echo "Initiating download of S3 bucket ($(BUCKET_NAME)) to ./s3-backup"
	@aws s3 sync s3://$(BUCKET_NAME)/ ./s3-backup/

# Uploads data to S3
upload-to-s3:
	@echo "Initiating upload of ./s3-backup to S3 bucket ($(BUCKET_NAME))"
	@aws s3 sync ./s3-backup/ s3://$(BUCKET_NAME)/

# Deletes S3 bucket
delete-s3-bucket:
	@echo "Deleting S3 bucket: $(BUCKET_NAME)"
	@aws s3 rb s3://$(BUCKET_NAME) --force

######################
# S3 Backups         #
######################

# BUCKET_NAME := $(shell terraform output -raw cluster_name)-bucket

# # Creates S3 bucket (does nothing if already exists)
# create-s3-bucket:
# 	@echo "Creating S3 bucket: $(BUCKET_NAME)"


# # Copies data from EFS to S3
# backup-to-s3-from-s3: create-s3-bucket
# 	@echo "Backing-up data from EFS to S3 bucket: $(BUCKET_NAME)"

# # Restores data from S3 back to EFS
# restore-to-efs-from-s3:
# 	@echo "Restoring data from S3 bucket ($(BUCKET_NAME)) to EFS"

# # Downloads data from S3
# download-from-s3: create-s3-bucket
# 	@echo "Initiating download of S3 bucket ($(BUCKET_NAME)) to ./s3-backup"

# # Uploads data to S3
# upload-to-s3:
# 	@echo "Initiating upload of ./s3-backup to S3 bucket ($(BUCKET_NAME))"

# # Deletes S3 bucket
# delete-s3-bucket:
# 	@echo "Deleting S3 bucket: $(BUCKET_NAME)"







