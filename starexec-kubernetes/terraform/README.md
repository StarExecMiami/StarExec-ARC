# Deploy StarExec in EKS using terraform

## Steps to follow
0. Prepare:
    - Install Terraform.
        - `brew install terraform` or [`ubuntu installation`](https://askubuntu.com/questions/983351/how-to-install-terraform-in-ubuntu)
    - Install the AWS CLI and login:
        - `brew install awscli` or `apt install awscli`
        - check with `aws sts get-caller-identity`
    - Install kubectl:
        - `brew install kubectl` or `apt install kubectl`
        - check with `kubectl version`

1. Edit `configuration.sh` to set your domain name, number of nodes, etc.
2. Run ```make```, which does:
    - ```make create-cluster```: Creates the EKS cluster using terraform.
    - ```make kubectl-setup```: Sets up kubectl to connect to the cluster.
    - ```make populate-cluster```: Populates the cluster with the StarExec k8s resources using kubectl.

3. Wait a bit for the head node to be up-and-running:
    - You can check using ```kubectl describe se-depl``` and other kubectl commands.

4. Forward your domain name to the service:
    - If your domain name is registered with Route53 using the account signed into the AWS cli, you can run ```make forward-domain-route53```.
    - Otherwise, you can run ```kubectl get svc```
    to get a domain name for the service, and separately
    forward your domain name to the service using a `CNAME` record.
5. Tell the cluster about the domain:
    - Run ```make reconfig-starexec``` to reconfigure the java ant build which uses the domain for some internal redirects like on the job-pairs page.
    - Run ```make get-certificate``` to use certbot to obtain a certificate for the domain **(The domain must be forwarding to the cluster for this to work!)**