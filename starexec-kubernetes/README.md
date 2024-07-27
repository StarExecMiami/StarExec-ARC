# Deploying StarExec in Kubernetes<br>(microk8s OR terraform->EKS)

1. The k8s configuration files are in `YAMLFiles`.
2. Deploying in microk8s can be done using the `Makefile`.
3. Terraform has a separate dir with its own `Makefile`.
    - This subdir has another `YAMLFiles` dir which has some symlinks
    and some modified copies from the outer `YAMLFiles` dir.