# Makefile for deploying StarExec Helm chart on MicroK8s

# --- Configuration ---
NAMESPACE       := starexec
RELEASE_NAME    := starexec-local
CHART_DIR       := .
HELM            := microk8s helm3
KUBECTL         := microk8s kubectl

# Paths to existing key/cert files relative to starexec-helm directory
TLS_CERT_PATH   := ../starexec-kubernetes/microk8s/starexec-tls.crt
TLS_KEY_PATH    := ../starexec-kubernetes/microk8s/starexec-tls.key
SSH_KEY_PATH    := ../starexec-kubernetes/microk8s/starexec-ssh-key

# Secrets names (should match values.yaml or be overridden)
TLS_SECRET_NAME := starexec-tls-secret
SSH_SECRET_NAME := starexec-ssh-key

# --- MicroK8s Setup ---

.PHONY: check-microk8s
check-microk8s:
	@echo "--> Checking MicroK8s status..."
	@microk8s status --wait-ready || (echo "MicroK8s is not running or not ready. Please start it." && exit 1)

.PHONY: enable-addons
enable-addons: check-microk8s
	@echo "--> Enabling MicroK8s addon: dns..."
	@microk8s enable dns
	@echo "--> Enabling MicroK8s addon: hostpath-storage..."
	@microk8s enable hostpath-storage
	@echo "--> Enabling MicroK8s addon: ingress..."
	@microk8s enable ingress
	@echo "--> Enabling MicroK8s addon: helm3..."
	@microk8s enable helm3

# --- Kubernetes Resources ---

.PHONY: create-namespace
create-namespace: check-microk8s
	@echo "--> Creating namespace '$(NAMESPACE)'..."
	@$(KUBECTL) get namespace $(NAMESPACE) > /dev/null 2>&1 || $(KUBECTL) create namespace $(NAMESPACE)

.PHONY: create-secrets
create-secrets: check-microk8s create-namespace
	@echo "--> Checking for required secret files..."
	@test -f $(TLS_CERT_PATH) || (echo "ERROR: TLS certificate file not found at $(TLS_CERT_PATH)" && exit 1)
	@test -f $(TLS_KEY_PATH) || (echo "ERROR: TLS key file not found at $(TLS_KEY_PATH)" && exit 1)
	@test -f $(SSH_KEY_PATH) || (echo "ERROR: SSH key file not found at $(SSH_KEY_PATH)" && exit 1)
	@echo "--> Creating TLS secret '$(TLS_SECRET_NAME)'..."
	@$(KUBECTL) get secret $(TLS_SECRET_NAME) -n $(NAMESPACE) > /dev/null 2>&1 || \
		$(KUBECTL) create secret tls $(TLS_SECRET_NAME) \
			--namespace=$(NAMESPACE) \
			--cert=$(TLS_CERT_PATH) \
			--key=$(TLS_KEY_PATH)
	@echo "--> Creating SSH secret '$(SSH_SECRET_NAME)'..."
	@$(KUBECTL) get secret $(SSH_SECRET_NAME) -n $(NAMESPACE) > /dev/null 2>&1 || \
		$(KUBECTL) create secret generic $(SSH_SECRET_NAME) \
			--namespace=$(NAMESPACE) \
			--from-file=starexec_podman_key=$(SSH_KEY_PATH) # Key name matches volumeMount subPath

# --- Helm Operations ---

.PHONY: lint
lint:
	@echo "--> Linting chart in $(CHART_DIR)..."
	@$(HELM) lint $(CHART_DIR)

.PHONY: template
template: create-secrets # Secrets might be referenced in templates even if not created by Helm
	@echo "--> Templating chart '$(RELEASE_NAME)'..."
	@$(HELM) template $(RELEASE_NAME) $(CHART_DIR) \
        --namespace $(NAMESPACE) \
        --set persistence.storageClassName=microk8s-hostpath \
        --set persistence.voldb.accessModes={ReadWriteOnce} \
        --set persistence.volstar.accessModes={ReadWriteOnce} \
        --set persistence.volpro.accessModes={ReadWriteOnce} \
        --set persistence.volexport.accessModes={ReadWriteOnce} \
        --set ingress.enabled=true \
        --set ingress.hosts[0].host=localhost \
        --set ingress.tls[0].secretName=$(TLS_SECRET_NAME) \
        --set ingress.tls[0].hosts[0]=localhost \
        --set ingress.createTlsSecret=false \
        --set sshSecret.create=false \
        --set sshSecret.existingSecretName=$(SSH_SECRET_NAME) \
        > $(RELEASE_NAME)-templated.yaml
	@echo "--> Template output saved to $(RELEASE_NAME)-templated.yaml"

.PHONY: debug-probes
debug-probes: check-microk8s create-namespace create-secrets
	@echo "--> Debugging probes by installing chart with direct probe definitions..."
	@$(HELM) upgrade --install $(RELEASE_NAME) $(CHART_DIR) \
		--namespace $(NAMESPACE) \
		--set persistence.storageClassName=microk8s-hostpath \
		--set persistence.voldb.accessModes={ReadWriteOnce} \
		--set persistence.volstar.accessModes={ReadWriteOnce} \
		--set persistence.volpro.accessModes={ReadWriteOnce} \
		--set persistence.volexport.accessModes={ReadWriteOnce} \
		--set ingress.enabled=true \
		--set ingress.hosts[0].host=localhost \
		--set "ingress.hosts[0].paths[0].path=/" \
		--set "ingress.hosts[0].paths[0].pathType=Prefix" \
		--set "ingress.tls[0].hosts[0]=localhost" \
		--set "ingress.tls[0].secretName=$(TLS_SECRET_NAME)" \
		--set sshSecret.create=false \
		--set "sshSecret.existingSecretName=$(SSH_SECRET_NAME)" \
		--set "probes.readiness.enabled=false" \
		--set "probes.liveness.enabled=false" \
		--set "probes.startup.enabled=false"
	@echo "--> Deployed with all health probes disabled"
	@echo "--> You can now manually check if the application is working by accessing it at https://localhost/starexec"

.PHONY: install
install: enable-addons create-namespace create-secrets lint
	@echo "--> Installing chart '$(RELEASE_NAME)' into namespace '$(NAMESPACE)'..."
	@$(HELM) install $(RELEASE_NAME) $(CHART_DIR) \
		--namespace $(NAMESPACE) \
		--set persistence.storageClassName=microk8s-hostpath \
		--set persistence.voldb.accessModes={ReadWriteOnce} \
		--set persistence.volstar.accessModes={ReadWriteOnce} \
		--set persistence.volpro.accessModes={ReadWriteOnce} \
		--set persistence.volexport.accessModes={ReadWriteOnce} \
		--set ingress.enabled=true \
		--set ingress.hosts[0].host=localhost \
		--set "ingress.hosts[0].paths[0].path=/" \
		--set "ingress.hosts[0].paths[0].pathType=Prefix" \
		--set "ingress.tls[0].hosts[0]=localhost" \
		--set "ingress.tls[0].secretName=$(TLS_SECRET_NAME)" \
		--set sshSecret.create=false \
		--set "sshSecret.existingSecretName=$(SSH_SECRET_NAME)" \
		--set "probes.readiness.enabled=false"
	@echo "--> Installation started. Check pod status with: microk8s kubectl get pods -n $(NAMESPACE)"
	@echo "--> Access the application at: https://localhost/starexec once it's running"

.PHONY: upgrade
upgrade: enable-addons create-namespace create-secrets lint
	@echo "--> Upgrading chart '$(RELEASE_NAME)' in namespace '$(NAMESPACE)'..."
	@$(HELM) upgrade --install $(RELEASE_NAME) $(CHART_DIR) \
		--namespace $(NAMESPACE) \
		--set persistence.storageClassName=microk8s-hostpath \
		--set persistence.voldb.accessModes={ReadWriteOnce} \
		--set persistence.volstar.accessModes={ReadWriteOnce} \
		--set persistence.volpro.accessModes={ReadWriteOnce} \
		--set persistence.volexport.accessModes={ReadWriteOnce} \
		--set ingress.enabled=true \
		--set ingress.hosts[0].host=localhost \
		--set "ingress.hosts[0].paths[0].path=/" \
		--set "ingress.hosts[0].paths[0].pathType=Prefix" \
		--set "ingress.tls[0].hosts[0]=localhost" \
		--set "ingress.tls[0].secretName=$(TLS_SECRET_NAME)" \
		--set sshSecret.create=false \
		--set sshSecret.existingSecretName=$(SSH_SECRET_NAME) \
		--set "probes.readiness.enabled=false"
	@echo "--> Upgrade started. Check pod status with: microk8s kubectl get pods -n $(NAMESPACE)"
	@echo "--> Access the application at: https://localhost/starexec once it's running"

.PHONY: uninstall
uninstall: check-microk8s
	@echo "--> Uninstalling chart '$(RELEASE_NAME)' from namespace '$(NAMESPACE)'..."
	@$(HELM) uninstall $(RELEASE_NAME) --namespace $(NAMESPACE)

.PHONY: status
status: check-microk8s
	@echo "--> Getting status for release '$(RELEASE_NAME)'..."
	@$(HELM) status $(RELEASE_NAME) --namespace $(NAMESPACE)
	@echo "--> Checking pods..."
	@$(KUBECTL) get pods -n $(NAMESPACE) -l app.kubernetes.io/instance=$(RELEASE_NAME)
	@echo "--> Checking ingress..."
	@$(KUBECTL) get ingress -n $(NAMESPACE) $(RELEASE_NAME)

.PHONY: get-url
get-url:
	@echo "--> Access StarExec (once ready) at: https://localhost/starexec"
	@echo "--> (You might need to accept self-signed certificate warnings in your browser)"

# --- Cleanup ---

.PHONY: clean-secrets
clean-secrets: check-microk8s
	@echo "--> Deleting secrets '$(TLS_SECRET_NAME)' and '$(SSH_SECRET_NAME)' from namespace '$(NAMESPACE)'..."
	@$(KUBECTL) delete secret $(TLS_SECRET_NAME) -n $(NAMESPACE) --ignore-not-found
	@$(KUBECTL) delete secret $(SSH_SECRET_NAME) -n $(NAMESPACE) --ignore-not-found

.PHONY: clean-namespace
clean-namespace: check-microk8s
	@echo "--> Deleting namespace '$(NAMESPACE)'..."
	@$(KUBECTL) delete namespace $(NAMESPACE) --ignore-not-found

.PHONY: clean
clean: uninstall clean-secrets clean-namespace
	@echo "--> Cleanup complete."

.PHONY: help
help:
	@echo "Makefile for StarExec Helm Chart on MicroK8s"
	@echo ""
	@echo "Usage:"
	@echo "  make check-microk8s    Check if MicroK8s is running"
	@echo "  make enable-addons     Enable required MicroK8s addons (dns, storage, ingress, helm3)"
	@echo "  make create-namespace  Create the Kubernetes namespace ($(NAMESPACE))"
	@echo "  make create-secrets    Create TLS and SSH secrets from local files"
	@echo "  make lint              Lint the Helm chart"
	@echo "  make template          Generate Kubernetes YAML from the Helm chart"
	@echo "  make debug-probes      Install with health probes disabled for troubleshooting"
	@echo "  make install           Install the Helm chart (depends on addons, namespace, secrets)"
	@echo "  make upgrade           Upgrade or install the Helm chart"
	@echo "  make uninstall         Uninstall the Helm chart"
	@echo "  make status            Show the status of the Helm release and related pods/ingress"
	@echo "  make get-url           Display the likely access URL"
	@echo "  make clean-secrets     Delete the created secrets"
	@echo "  make clean-namespace   Delete the Kubernetes namespace"
	@echo "  make clean             Uninstall chart and delete secrets and namespace"
	@echo "  make help              Show this help message"
	@echo ""
	@echo "Note: Uses MicroK8s default 'microk8s-hostpath' storage (RWO)."

# Default target
.DEFAULT_GOAL := help
