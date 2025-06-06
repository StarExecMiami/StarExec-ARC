import argparse
import os
import shutil
from helpers import verifyImageExists

# -----------------------------------------------------------------------------
def makeProxyProver(prover, archiveName, local):

    os.makedirs("parent/bin", exist_ok=True)

    # ---- The starexec runscript checks for these files to know what to do
    # ---- (instead of running starexec_run_{archiveName}, like the local
    # ---- backend would normally do)
    if local:
        shutil.copy(
            "../provers-containerised/run_image.py",
            "parent/bin/run_image.py"
        )
    else:
        shutil.copy(
            "../starexec-kubernetes/run_image_k8s.py",
            "parent/bin/run_image_k8s.py"
        )

    # Check if prover image exists
    # (in docker.io / whatever registry, or locally if no registry)
    verifyImageExists(prover)
    with open("parent/bin/prover.txt", "w") as f:
        f.write(prover)

    shutil.copy("job_template.yaml", "parent/bin/job_template.yaml")

    # ----Despite not being used, there needs to be a "configuration..."
    with open(f"parent/bin/starexec_run_{archiveName}", "w") as f:
        f.write("proxy\n")

    # ----Make the prover's .tgz file with container-safe options
    import subprocess
    
    # Create archive using tar command with container-safe flags
    tar_cmd = [
        "tar",
        "--create",
        "--gzip",
        "--file", f"{archiveName}.tgz",
        "--no-same-permissions",
        "--no-same-owner", 
        "--directory", "parent",
        "."
    ]
    
    try:
        subprocess.run(tar_cmd, check=True)
        print(f"Successfully created {archiveName}.tgz with container-safe options")
    except subprocess.CalledProcessError as e:
        print(f"Error creating archive: {e}")
        # Fallback to original method if tar command fails
        shutil.make_archive(archiveName, "gztar", "parent")
        shutil.move(f"{archiveName}.tar.gz", f"{archiveName}.tgz")
    
    shutil.rmtree("parent")

# -----------------------------------------------------------------------------
if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "prover",
        help=(
            "The name:tag of a podman image existing in the host where the "
            "proxy prover will be run."
        ),
    )
    parser.add_argument(
        "archiveName",
        help="The name of the archive/proxy prover to be created."
    )
    parser.add_argument(
        "--local",
        action="store_true",
        help=(
            "If set, the proxy prover will NOT use kubectl with a templated "
            "job.yaml file, instead it'll invoke podman directly."
        ),
    )
    args = parser.parse_args()

    makeProxyProver(args.prover, args.archiveName, args.local)
# -----------------------------------------------------------------------------
