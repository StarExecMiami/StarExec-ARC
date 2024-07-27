# make sure shell is bash, since I normally use fish:
SHELL = bash

apply:
	microk8s enable ingress
	cd YAMLFiles && microk8s kubectl apply -f .
	if [ ! -f ../starexec-containerised/starexec_podman_key ]; then \
		ssh-keygen -t rsa -N "" -f ../starexec-containerised/starexec_podman_key; \
	fi

	microk8s kubectl create secret generic starexec-ssh-key --from-file=starexec_ssh_key=../starexec-containerised/starexec_podman_key -n default; \


connect:
	microk8s kubectl exec -it $$(microk8s kubectl get pods --selector=app=starexec -o jsonpath='{.items[0].metadata.name}') -- /bin/bash


clean:
	microk8s kubectl delete -f YAMLFiles

info:
	microk8s kubectl get all --all-namespaces


# https://github.com/canonical/microk8s/issues/3241
dumb-fix:
	sudo snap set microk8s dummy="$(date)"
	sudo microk8s refresh-certs --cert server.crt
	sudo microk8s refresh-certs --cert front-proxy-client.crt

	openssl x509 -in /var/snap/microk8s/current/certs/server.crt -text -noout | grep -A 1 "Subject Alternative Name"




