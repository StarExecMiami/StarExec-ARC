import argparse
import os, shutil

def makeDummyProver(prover, archiveName):
    
    os.makedirs("parent/bin", exist_ok=True)
    shutil.copy("../provers-containerised/run_image.py", "parent/bin/run_image.py")

    # make bin/starexec-run-{archiveName} script
    with open(f"parent/bin/prover.txt", "w") as f:
        f.write(prover)
    
    # Despite not being used, there needs to be a "configuration..."
    with open(f"parent/bin/starexec_run_{archiveName}", "w") as f:
        f.write("dummy\n")
    
    
    shutil.make_archive(archiveName, 'gztar', 'parent')
    shutil.rmtree("parent")



if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("prover", help="The name:tag of a podman image existing in the host where the dummy prover will be run.")
    parser.add_argument("archiveName", help="The name of the archive/dummy_prover to be created.")
    args = parser.parse_args()

    makeDummyProver(args.prover, args.archiveName)

