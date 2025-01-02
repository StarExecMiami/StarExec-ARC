# Using MicroK8s to deploy StarExec <br>(head node only with local backend)

Makefile Targets:
---

+ `make apply` - Enables microk8s ingress, deploys k8s resources (service, deployment, storage, etc.) from the YAMLFiles directory, and creates an SSH key that the head node can use for starting jobs in the outside using podman. 

+ `make connect` - Starts and presents a shell in the head node for debugging.

+ `make clean` - Deletes the k8s resources deployed by `make apply`

+ `make info` - Lists all k8s resources (including but not limited to those deployed by `make apply`)