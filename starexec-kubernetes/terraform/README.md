# Making and Deploying StarExec in an EKS cluster, using `terraform`

0. Prepare:
   - Install terraform:
     * On a Mac: `brew install terraform` 
     * In Ubuntu: `snap install terraform --classic` [`more info`](https://askubuntu.com/questions/983351/how-to-install-terraform-in-ubuntu)
   - Install the AWS CLI and login:
     * On a Mac: `brew install awscli` 
     * In Ubuntu: `snap install aws-cli --classic`
     * Check configuration with `aws sts get-caller-identity` or, if needed, 
       [configure AWS CLI](https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-configure.html)

1. Edit `configuration.sh` to set your domain name, number of nodes, etc.
   - It's nice to have your own domain, and even better if you use Route53 as the registrar.
     Set the `domain` in `configuration.sh`.
   - The `desiredNodes` and `maxNodes` determine how many StarExec compute node will be in
     your EKS cluster.
   - The `instanceType` is the type of compute node. 
     Note that regardless of what you choose, one and only one StarExec job pair will run at
     a time on each node, i.e., using more powerful nodes give more power to the job pair,
     but does not make the queue of job pairs get run faster.
     The `t3.small` type is cheap, with two CPUs.

2. Run `make`, which does the following:
   - `make init`: Initializes terraform by running `terraform init -upgrade`.
      * If you change .tf files, you should run terraform init again to reinitialize the 
        working directory, although take care because doing so can cause you to lose track 
        of things that you've deployed.
   - `make create-cluster`: Creates the EKS cluster using terraform.
   - `make kubectl-setup`: Sets up kubectl to connect to the cluster.
   - `make populate-cluster`: Populates the cluster with the StarExec resources, using kubectl.

3. Wait a bit for the head node to be up-and-running:
   - You can check using `kubectl describe pod se-depl` and other kubectl commands.
     (Initial lines saying "FailedScheduling" can be ignored - it's normal.)

4. Forward your domain name to the service:
   - If your domain name is registered with Route53 using the account signed into the AWS cli: 
     * Make sure you have created a hosted zone
     * Set the domain in `configurations.sh` and run `make forward-domain-route53`
   - Otherwise: 
     * Run `kubectl get svc` to get the AWS domain name for the service
     * Separately forward your domain name to the service using a `CNAME` record.
   - Tell the cluster about the domain:
     * Run `make reconfig-starexec` to reconfigure the StarExec ant build, which uses the 
       domain for some internal redirects, e.g., on the job-pairs page.
     * Test if your domain works in a browser - it will complain that it's insecure, but then
       you do the next step. But **you must wait until the domain is working** (insecurely) before 
       you do the next step.
     * Run `make get-certificate` to use certbot to obtain a certificate for the domain 
       **(The domain must be forwarding to the cluster for this to work!)**

5. You should now be able to login to your new StarExec instance from `https://domainname/starexec`
   - `domainname` is your domain if forwarded, otherwise the auto-generated AWS domain.
   - The default user name and password are both `admin`

6. Normal StarExec `tgz` packages for provers do not work in this setup.
   Instead, upload proxy prover packages:
   - These are created in the [`starexec-proxy-provers`](../../starexec-proxy-provers) directory.
   - Proxy provers reference containerized provers hosted online, e.g., in dockerhub.

7. To run a first example job, you can upload the PUZ001+1.p problem and the eprover proxy package 
   that are provided in the [`starexec-proxy-provers`](../../starexec-proxy-provers) directory.

---

# Managing the EKS cluster

- Changing the number of compute nodes
  * Edit `configuration.sh`
  * `make update-node-count`
- Taking StarExec off the cluster
  * `make depopulate-cluster`
- Putting StarExec on the cluster
  * `make populate-cluster`
  * Wait a bit for the head node to be up-and-running
  * If you have a Route53 domain to forward to:
    + Edit `configuration.sh` to put in the domain
    + `make forward-domain-route53`
    + `make reconfig-starexec` 
    + Wait a few minutes
    + `make get-certificate`
  * If you have a non-Route53 domain to forward to:
    + Edit `configuration.sh` to put in the domain
    + Use a CNAME entry to forward the domain
    + `make reconfig-starexec` 
    + Wait a few minutes
    + `make get-certificate`
- Saving and Restoring StarExec data (solvers, benchmarks, jobs, etc.) via S3
  * Saving StarExec data to S3
    + Stop StarExec with `make depopulate-cluster`
    + `make create-s3-bucket`
    + `make backup-to-s3-from-efs`
    + Restart StarExec with `make populate-cluster`
  * Restoring StarExec data from S3
    + Stop StarExec with `make depopulate-cluster`
    + `make restore-to-efs-from-s3
    + Restart StarExec with `make populate-cluster`
  * Downloading StarExec data from S3
    + `make download-from-s3` (this also does `make create-s3-bucket` DOES IT DO backup-to-s3-from-efs?
      The data is saved in `./s3-backup`
  * Uploading StarExec data to S3
    + `make upload-to-s3`
      The data is uploaded from `./s3-backup`
