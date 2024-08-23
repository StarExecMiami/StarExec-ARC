# make sure shell is bash, since I normally use fish:
SHELL = bash

domain := $(shell ./configuration.sh domain)


default:
	echo "1. create-cluster, 2. kubectl-setup, 3. populate-cluster"
	make create-cluster kubectl-setup populate-cluster

	# echo "Getting certificate and reconfiguring starexec (java ant build config)"
	# make reconfig-starexec get-certificate




reconfig-starexec:
	@echo "Finding running pod for starexec-deployment..."
	@POD_NAME=$$(kubectl get pods --selector=app=starexec -o jsonpath='{.items[0].metadata.name}'); \
	if [ -z "$$POD_NAME" ]; then \
		echo "No pod found for starexec-deployment"; \
		exit 1; \
	fi; \
	echo "Pod found: $$POD_NAME"; \
	echo "External IP for starexec-service: $(domain)"; \
	echo "Executing reconfig script in the pod with domain $(domain)..."; \
	kubectl cp reconfig_starexec.sh $$POD_NAME:/tmp/reconfig_starexec.sh; \
	kubectl exec $$POD_NAME -- /bin/sh -c "chmod +x /tmp/reconfig_starexec.sh && /tmp/reconfig_starexec.sh $(domain)"


get-certificate:
	@echo "Finding running pod for starexec-deployment..."
	@POD_NAME=$$(kubectl get pods --selector=app=starexec -o jsonpath='{.items[0].metadata.name}'); \
	if [ -z "$$POD_NAME" ]; then \
		echo "No pod found for starexec-deployment"; \
		exit 1; \
	fi; \
	echo "Pod found: $$POD_NAME"; \
	echo "External IP for starexec-service: $(domain)"; \
	echo "Executing get-certificate script in the pod with domain $(domain)..."; \
	kubectl cp get_certificate.sh $$POD_NAME:/tmp/get_certificate.sh; \
	kubectl exec $$POD_NAME -- /bin/sh -c "chmod +x /tmp/get_certificate.sh && /tmp/get_certificate.sh $(domain)"


# Untested...
forward-domain-route53:
	@echo "Fetching external domain name from EKS service..."
	# Using default namespace and the service name starexec-service
	EXTERNAL_DOMAIN=$(shell kubectl get svc starexec-service -n default -o jsonpath='{.status.loadBalancer.ingress[0].hostname}')
	@echo "External domain: $$EXTERNAL_DOMAIN"
	
	@echo "Fetching hosted zone ID from Route 53..."
	# Assuming ./configuration.sh domain returns a domain name registered with Route 53, e.g., example.com
	HOSTED_ZONE_ID=$(shell aws route53 list-hosted-zones-by-name --dns-name $$domain --query "HostedZones[?Name=='$$domain.'].Id" --output text | cut -d'/' -f3)
	@echo "Hosted zone ID: $$HOSTED_ZONE_ID"
	
	@echo "Updating Route 53 DNS record..."
	aws route53 change-resource-record-sets --hosted-zone-id $$HOSTED_ZONE_ID --change-batch '{
	  "Changes": [{
	    "Action": "UPSERT",
	    "ResourceRecordSet": {
	      "Name": "$$domain",  # Use the domain obtained from the configuration script
	      "Type": "CNAME",
	      "TTL": 300,
	      "ResourceRecords": [{
	        "Value": "'"$$EXTERNAL_DOMAIN"'"
	      }]
	    }
	  }]
	}'
	@echo "DNS update initiated."






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
	terraform destroy -auto-approve

# Show what *will* be created with "terraform apply" (or make create-cluster)
plan:
	terraform plan

# Initialize terraform (Probably only need to do once?)
init:
	terraform init -upgrade

# Terraform uses stored aws creds to setup kubectl to connect to cluster
kubectl-setup:
	aws eks --region $$(terraform output -raw region) update-kubeconfig \
		--name $$(terraform output -raw cluster_name)
