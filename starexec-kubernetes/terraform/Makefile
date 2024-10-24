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
	echo "Have you done a make clean?"
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

# Creates S3 bucket
create-s3-bucket:
	echo "Unimplemented"

# Copies data from EFS to S3
backup-to-s3:
	echo "Unimplemented"

# Restores data from S3 back to EFS
restore-from-s3:
	echo "Unimplemented"

# Downloads data from S3
download-from-s3:
	echo "Unimplemented"

# Uploads data to S3
upload-to-s3:
	echo "Unimplemented"

# Deletes S3 bucket
delete-s3-bucket:
	echo "Unimplemented"
