SHELL := /usr/bin/env bash
SOURCE_DIR := $(CURDIR)
KUBECTL := microk8s kubectl
NAMESPACE := default
APP_NAME := starexec
SSH_KEY := starexec-ssh-key
TLS_CERT_KEY := starexec-tls.key
TLS_CERT_CRT := starexec-tls.crt
TLS_SECRET_NAME := starexec-tls-secret

# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
NC := \033[0m

# Declare all phony targets
.PHONY: apply connect clean info list-pods list-services list-deployments list-nodes cert-refresh mkcert-setup mkcert-clean

apply: ## Deploy application and configure ingress
	@echo -e "${YELLOW}Ensuring TLS secret exists. Run 'make mkcert-setup' if this fails or certs need update.${NC}"
	@$(KUBECTL) get secret $(TLS_SECRET_NAME) > /dev/null || (echo -e "${RED}TLS secret '$(TLS_SECRET_NAME)' not found. Please run 'make mkcert-setup' first.${NC}" && exit 1)
	microk8s enable ingress
	cd YAMLFiles && $(KUBECTL) apply -f .
	if [ ! -f "$(SOURCE_DIR)/$(SSH_KEY)" ]; then \
		ssh-keygen -t rsa -N "" -f $(SSH_KEY); \
	fi
	$(KUBECTL) delete secret $(SSH_KEY) --ignore-not-found
	$(KUBECTL) delete secret $(SSH_KEY)-pub --ignore-not-found
	$(KUBECTL) create secret generic $(SSH_KEY) --from-file=$(SSH_KEY)=$(SSH_KEY)
	$(KUBECTL) create secret generic $(SSH_KEY)-pub --from-file=$(SSH_KEY)_pub=$(SSH_KEY).pub -n $(NAMESPACE)
	@echo -e "${GREEN}=== Access Instructions ===${NC}"
	@echo -e "${YELLOW}Option 1: Using cluster IP:${NC}"
	@echo -e "  $(KUBECTL) get svc $(APP_NAME)-service -o jsonpath='{.spec.clusterIP}'"
	@echo -e "${YELLOW}Option 2: Port forward to localhost:${NC}"
	@echo -e "  $(KUBECTL) port-forward svc/$(APP_NAME)-service 8443:443"
	@echo -e "  Then visit https://localhost:8443"

connect: ## Connect to the application pod
	$(KUBECTL) exec -it $$($(KUBECTL) get pods --selector=app=$(APP_NAME) -o jsonpath='{.items[0].metadata.name}') -- /bin/bash

clean: mkcert-clean ## Remove all deployed resources
	-$(KUBECTL) delete -f YAMLFiles --ignore-not-found || true
	-$(KUBECTL) delete secret $(SSH_KEY) --ignore-not-found
	-$(KUBECTL) delete secret $(SSH_KEY)-pub --ignore-not-found
	-rm -f $(SSH_KEY) $(SSH_KEY).pub

info: ## Display all resources across namespaces
	$(KUBECTL) get all --all-namespaces

list-pods: ## List all pods
	$(KUBECTL) get pods --all-namespaces

list-services: ## List all services
	$(KUBECTL) get services --all-namespaces

list-deployments: ## List all deployments
	$(KUBECTL) get deployments --all-namespaces

list-nodes: ## List all nodes
	$(KUBECTL) get nodes

cert-refresh: ## Refresh the application's TLS certificate and Kubernetes secret using mkcert
	@echo "Refreshing application TLS certificate and secret using mkcert..."
	@echo "Checking for mkcert..."
	@if ! command -v mkcert > /dev/null 2>&1; then \
		echo >&2 "${RED}mkcert is not installed. Cannot refresh certificates. Run 'make mkcert-setup' first or install mkcert.${NC}"; \
		exit 1; \
	fi
	@echo "Generating new TLS certificate and key ($(TLS_CERT_CRT), $(TLS_CERT_KEY))..."
	@mkcert -cert-file $(TLS_CERT_CRT) -key-file $(TLS_CERT_KEY) localhost 127.0.0.1 ::1
	@echo "Updating Kubernetes TLS secret '$(TLS_SECRET_NAME)'..."
	-$(KUBECTL) delete secret tls $(TLS_SECRET_NAME) --ignore-not-found
	@$(KUBECTL) create secret tls $(TLS_SECRET_NAME) --cert=$(TLS_CERT_CRT) --key=$(TLS_CERT_KEY)
	@echo -e "${GREEN}Application TLS certificate and secret '$(TLS_SECRET_NAME)' refreshed successfully.${NC}"
	@echo "Removing temporary certificate files..."
	#-rm -f $(TLS_CERT_CRT) $(TLS_CERT_KEY) # Keep files for potential reuse or debugging

mkcert-setup: ## Setup mkcert and generate TLS certificates for the application
	@echo "Setting up mkcert and localhost certificates..."
	@echo "Checking for mkcert..."
	@if ! command -v mkcert > /dev/null 2>&1; then \
		echo >&2 "mkcert is not installed. Please install it first."; \
		echo >&2 "  Linux: sudo apt update && sudo apt install -y mkcert libnss3-tools"; \
		echo >&2 "  macOS: brew install mkcert"; \
		exit 1; \
	fi
	@mkcert -install
	@echo "Generating TLS certificate and key ($(TLS_CERT_CRT), $(TLS_CERT_KEY))..."
	@mkcert -cert-file $(TLS_CERT_CRT) -key-file $(TLS_CERT_KEY) localhost 127.0.0.1 ::1
	@echo "Creating/Updating Kubernetes TLS secret '$(TLS_SECRET_NAME)'..."
	-$(KUBECTL) delete secret tls $(TLS_SECRET_NAME) --ignore-not-found
	@$(KUBECTL) create secret tls $(TLS_SECRET_NAME) --cert=$(TLS_CERT_CRT) --key=$(TLS_CERT_KEY)
	@echo -e "${GREEN}mkcert setup complete. TLS secret '$(TLS_SECRET_NAME)' created/updated.${NC}"

mkcert-clean: ## Remove generated TLS certificates and secret
	@echo "Removing generated TLS certificate files..."
	-rm -f $(TLS_CERT_CRT) $(TLS_CERT_KEY)
	@echo "Removing Kubernetes TLS secret '$(TLS_SECRET_NAME)'..."
	-$(KUBECTL) delete secret tls $(TLS_SECRET_NAME) --ignore-not-found

