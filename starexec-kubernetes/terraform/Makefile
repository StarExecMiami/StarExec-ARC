# make sure shell is bash, since I normally use fish:
SHELL = bash

domain := $(shell ./configuration.sh domain)

default:
	echo "0. init 1. create-cluster, 2. kubectl-setup, 3. populate-cluster"
	make init create-cluster kubectl-setup populate-cluster

	# echo "Getting certificate and reconfiguring starexec (java ant build config)"
	# make reconfig-starexec get-certificate

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
label-nodes:
	# Label compute nodes
	for node in $$(kubectl get nodes -o jsonpath='{.items[*].metadata.name}'); do \
		if kubectl get node $$node -o jsonpath='{.metadata.labels.eks\.amazonaws\.com/nodegroup}' | grep -q "computenodes"; then \
			echo "Labeling compute node: $$node"; \
			kubectl label nodes $$node nodegroup=computenodes --overwrite; \
		fi; \
	done

	# Label head node
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
	export VOLEXPORT_LABEL=$$(terraform output -raw efs_volexport_access_point_id) && \
	envsubst < YAMLFiles/storage.yaml.template > YAMLFiles/storage.yaml 
	
	cd YAMLFiles && kubectl apply -f .
	if [ ! -f ../../starexec-containerised/starexec_podman_key ]; then \
		ssh-keygen -t rsa -N "" -f ../../starexec-containerised/starexec_podman_key; \
	fi
	kubectl create secret generic starexec-ssh-key --from-file=starexec_ssh_key=../../starexec-containerised/starexec_podman_key -n default;

connect:
	kubectl exec -it $$(kubectl get pods --selector=app=starexec -o jsonpath='{.items[0].metadata.name}') -- /bin/bash

clean:
	kubectl delete -f YAMLFiles

info:
	kubectl get all --all-namespaces

######################
# Terraform/EKS/AWS  #
######################

# Creates EKS infrastructure
create-cluster:
	terraform apply -target=module.vpc -auto-approve
	terraform apply -auto-approve

# Destroys EKS infrastructure
destroy:
	# run make clean if k8s stuff hasn't been shut down.
	@if kubectl cluster-info > /dev/null 2>&1; then \
		echo "Cluster is up. Running make clean..."; \
		make clean; \
	else \
		echo "Cluster is not up. Skipping make clean."; \
	fi
	terraform destroy -target=module.eks -auto-approve
	terraform destroy -target=module.vpc -auto-approve
	terraform destroy -auto-approve




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
		--options '{ "OverwriteMode": "ALWAYS", "VerifyMode": "POINT_IN_TIME_CONSISTENT" }' \
		--query 'TaskArn' --output text); \
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
		if [ "$$BYTES_TRANSFERRED" != "None" ] && [ "$$BYTES_WRITTEN" != "None" ] && [ "$$BYTES_TRANSFERRED" -ne 0 ]; then \
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







