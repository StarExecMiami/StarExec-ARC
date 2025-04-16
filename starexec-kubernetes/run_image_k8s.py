#!/usr/bin/env python3

import argparse
import subprocess
import json
import time
import os
from random import randint


def wait_for_job_completion(job_name, namespace="default", timeout=None):
    start_time = time.time()

    while True:
        # Get job status
        result = subprocess.run(
            f"kubectl get job {job_name} -n {namespace} -o json",
            shell=True,
            capture_output=True,
            text=True,
        )

        # Parse the JSON output
        job_status = json.loads(result.stdout)

        # Check for completion or failure
        conditions = job_status.get("status", {}).get("conditions", [])
        for condition in conditions:
            if condition["type"] == "Complete" and condition["status"] == "True":
                print("Job completed successfully.")
                return True
            elif condition["type"] == "Failed" and condition["status"] == "True":
                print("Job failed.")
                return False

        # Check for timeout
        if timeout is not None and (time.time() - start_time) > timeout:
            print("Timeout reached while waiting for job completion.")
            return False

        # Sleep for a while before checking again
        time.sleep(1)


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

    legalProverName = "".join(
        [x for x in os.path.split(args.image_name)[1] if x.isalnum()]
    ).lower()
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


# -----------------------------------------------------------------------------
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        "Wrapper for a kubectl call to a run a prover image in kubernetes"
    )
    parser.add_argument("image_name", help="Image name, e.g., eprover:3.0.03-RLR-arm64")
    parser.add_argument("-P", "--problem", help="Problem file if not stdin")
    parser.add_argument(
        "-C",
        "--cpu-limit",
        default=0,
        type=int,
        help="CPU time limit in seconds, default=none",
    )
    parser.add_argument(
        "-W",
        "--wall-clock-limit",
        default=0,
        type=int,
        help="Wall clock time limit in seconds, default=none",
    )
    parser.add_argument(
        "-M",
        "--memory-limit",
        default=0,
        type=int,
        help="Memory limit in MiB, default=none",
    )
    parser.add_argument(
        "-I",
        "--intent",
        default="THM",
        choices=["THM", "SAT"],
        help="Intention (THM, SAT, etc), default=THM",
    )
    parser.add_argument(
        "--sandbox",
        default="sandbox",
        help=(
            "Where will starexec look for the results / store the necessary "
            "inputs? (full path)"
        ),
    )
    parser.add_argument(
        "--job-template-path",
        default="job_template.yaml",
        help="Path to the job template file",
    )
    parser.add_argument("--dry-run", action="store_true", help="dry run")

    args = parser.parse_args()

    if args.wall_clock_limit == 0 and args.cpu_limit != 0:
        args.wall_clock_limit = args.cpu_limit

    job_name, job_yaml = makeJobYAML(args)

    command = "kubectl apply -f job.yaml"

    # ----Run command or print for dry run
    if args.dry_run:
        print(job_yaml)
        print("\n" + "#" * 80 + "\n")
        print(command)

    else:
        with open("job.yaml", "w") as f:
            f.write(job_yaml)

        subprocess.run(command, shell=True)

        # Should never be reached, but just in case...
        # The job could be "waiting for an available node" because of the
        # nodeAffinity stuff.
        OneHour = 3600
        wait_for_job_completion(job_name, timeout=12 * OneHour)


# ------------------------------------------------------------------------
