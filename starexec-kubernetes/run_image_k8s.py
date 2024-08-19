#!/usr/bin/env python3

import argparse
import subprocess
import os, sys
import shutil
import subprocess
from random import randint

# Template params: (see job_jinja.yaml)
#   - name: the name of the job
#   - image: the image to use
#   - cpu_limit: the cpu time limit in seconds
#   - wall_clock_limit: the wall clock time limit in seconds
#   - memory_limit: the memory limit in MiB
#   - intent: "THM" or "SAT"
#   - sandbox: "sandbox" or "sandbox2"

def makeJobYAML(args):
    """
    Generate job.yaml from job_jinja.yaml
    """

    with open(args.job_template_path) as f:
        template = f.read()

    legalProverName = ''.join([x for x in os.path.split(args.image_name)[1] if x.isalnum()]).lower()
    name = f"arc-job-{legalProverName}-{randint(0, 1_000_000_000)}"
    image = f"{args.image_name}"

    template = template.replace("{{ name }}", name)
    template = template.replace("{{ image }}", image)
    template = template.replace("{{ cpu_limit }}", str(args.cpu_limit))
    template = template.replace("{{ wall_clock_limit }}", str(args.wall_clock_limit))
    template = template.replace("{{ memory_limit }}", str(args.memory_limit))
    template = template.replace("{{ intent }}", args.intent)
    template = template.replace("{{ sandbox }}", args.sandbox)

    return name, template



#----------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    parser = argparse.ArgumentParser("Wrapper for a kubectl call to a run a prover image in kubernetes")
    parser.add_argument("image_name", 
help="Image name, e.g., eprover:3.0.03-RLR-arm64")
    parser.add_argument("-P", "--problem", 
help="Problem file if not stdin")
    parser.add_argument("-C", "--cpu-limit", default=0, type=int, 
help="CPU time limit in seconds, default=none")
    parser.add_argument("-W", "--wall-clock-limit", default=0, type=int, 
help="Wall clock time limit in seconds, default=none")
    parser.add_argument("-M", "--memory-limit", default=0, type=int, 
help="Memory limit in MiB, default=none")
    parser.add_argument("-I", "--intent", default="THM", choices=["THM", "SAT"], 
help="Intention (THM, SAT, etc), default=THM")
    parser.add_argument("--sandbox", default="sandbox", choices=["sandbox", "sandbox2"],
help="Where will starexec look for the results / store the necessary inputs? (sandbox or sandbox2)")
    parser.add_argument("--job-template-path", default="job_template.yaml", 
help="Path to the job template file")
    parser.add_argument("--dry-run", action="store_true", 
help="dry run")
    
    args = parser.parse_args()

    if args.wall_clock_limit == 0 and args.cpu_limit != 0:
        args.wall_clock_limit = args.cpu_limit
    
    job_name, job_yaml = makeJobYAML(args)

    command = "kubectl apply -f job.yaml"


#----Run command or print for dry run
    if args.dry_run:
        print(job_yaml)
        print("\n" + "#"*80 + "\n")
        print(command)

    else:
        with open("job.yaml", "w") as f:
            f.write(job_yaml)
        
        subprocess.run(command, shell=True)

        # need to wait for the job to finish
        # subprocess.run(f"kubectl wait --for=condition=complete job/{job_name} --timeout={args.wall_clock_limit}s", shell=True)

        # don't assume that the job is complete when the timeout is reached:
        # subprocess.run(f"kubectl wait --for=condition=complete job/{job_name}", shell=True)






#----------------------------------------------------------------------------------------------------

