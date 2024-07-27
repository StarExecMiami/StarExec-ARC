# make sure shell is bash, since I normally use fish:
SHELL = bash

default:
	echo "1. create-cluster, 2. kubectl-setup, 3. populate-cluster, 4. info, 5. connect, 6. clean"

######################
#     Kubernetes     #
######################

populate-cluster:

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
	terraform apply -target=module.vpc
	terraform apply

# Destroys EKS infrastructure
destroy:
	terraform destroy

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
