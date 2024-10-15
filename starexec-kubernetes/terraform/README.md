# Deploy StarExec in EKS using terraform

## Steps to follow
0. Prepare:
    - Install Terraform.
        - `brew install terraform` or in Ubuntu: `snap install terraform --classic` [`more info`](https://askubuntu.com/questions/983351/how-to-install-terraform-in-ubuntu)
    - Install the AWS CLI and login:
        - `brew install awscli` or in Ubuntu: `snap install aws-cli --classic`
        - check configuration with `aws sts get-caller-identity`
        - or, if needed, [configure AWS CLI](https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-configure.html)
    - Install kubectl:
        - `brew install kubectl` or in Ubuntu `snap install kubectl --classic`
        - check with `kubectl version`

1. Edit `configuration.sh` to set your domain name, number of nodes, etc.

2. Run ```make```, which does the following:
    - ```make init```: Initializes terraform by running ```terraform init -upgrade```.
        - If you change .tf files, you should run terraform init again to reinitialize the working directory, although take care because doing so can cause you to lose track of things that you've deployed.
    - ```make create-cluster```: Creates the EKS cluster using terraform.
    - ```make kubectl-setup```: Sets up kubectl to connect to the cluster.
    - ```make populate-cluster```: Populates the cluster with the StarExec k8s resources using kubectl.

3. Wait a bit for the head node to be up-and-running:
   - You can check using ```kubectl describe pod se-depl``` and other kubectl commands.
     (Initial lines saying "FailedScheduling" can be ignored - it's normal.)

4. Forward your domain name to the service:
    - If your domain name is registered with Route53 using the account signed into the AWS cli: 
      * Make sure you have created a hosted zone
      * Set the domain in ```configurations.sh``` and run ```make forward-domain-route53```
    - Otherwise: 
      * Run ```kubectl get svc``` to get the AWS domain name for the service
      * Separately forward your domain name to the service using a `CNAME` record.
    - Tell the cluster about the domain:
      * Run ```make reconfig-starexec``` to reconfigure the java ant build which uses the domain for some internal redirects like on the job-pairs page.
      * Run ```make get-certificate``` to use certbot to obtain a certificate for the domain **(The domain must be forwarding to the cluster for this to work!)**

5. You should now be able to login to your new StarExec instance from https://domainname/starexec
    - ```domainname``` is your domain if forwarded, otherwise the auto-generated AWS domain.
    - username and password are both `admin`

6. Normal StarExec tar.gz packages for provers do not work in this setup.
   Instead, upload <i>proxy</i> prover packages:
   - These can be created from the <a href="https://github.com/StarExecMiami/starexec-ARC/tree/master/starexec-proxy-provers/README.md">starexec-proxy-provers</a> subdirectory of this repository.
   - These proxy packages reference containerized provers hosted in online repositories like dockerhub.

7. To run a first example job, you can upload the PUZ001+1.p problem and eprover proxy package that are provided in the <a href="https://github.com/StarExecMiami/starexec-ARC/tree/master/starexec-proxy-provers">starexec-proxy-provers</a> subdirectory of this repository.
