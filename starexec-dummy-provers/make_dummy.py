import argparse
import os, shutil

def makeDummyProver(prover, archiveName, k8s):
    
    os.makedirs("parent/bin", exist_ok=True)

    # the starexec runscript checks for these files to know what to do 
    # (instead of running starexec_run_{archiveName}, 
    # like the local backend would normally do)
    if k8s:
        shutil.copy("../starexec-kubernetes/run_image_k8s.py", "parent/bin/run_image_k8s.py")
    else:
        shutil.copy("../provers-containerised/run_image.py", "parent/bin/run_image.py")

    with open(f"parent/bin/prover.txt", "w") as f:
        f.write(prover)

    shutil.copy("../starexec-kubernetes/job_template.yaml", "parent/bin/job_template.yaml")
    
    # Despite not being used, there needs to be a "configuration..."
    with open(f"parent/bin/starexec_run_{archiveName}", "w") as f:
        f.write("dummy\n")
    
    
    shutil.make_archive(archiveName, 'gztar', 'parent')
    shutil.rmtree("parent")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("prover", help="The name:tag of a podman image existing in the host where the dummy prover will be run.")
    parser.add_argument("archiveName", help="The name of the archive/dummy_prover to be created.")
    parser.add_argument("--k8s", action="store_true", help="If set, the dummy prover will use kubectl with a templated job.yaml file instead of using podman directly.")
    args = parser.parse_args()

    makeDummyProver(args.prover, args.archiveName, args.k8s)

