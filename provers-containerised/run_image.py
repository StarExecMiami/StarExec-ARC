#!/usr/bin/env python3

import argparse
import subprocess
import os, sys
import shutil

#--------------------------------------------------------------------------------------------------
def getRLRArgs(args):
    sandbox = "sandbox" if args.starexec == 1 else "sandbox2"

    paths_part = f"--watcher-data /dev/null"
    if args.starexec:
        paths_part = f" --add-eof --watcher-data /export/starexec/{sandbox}/output/watcher.out" + \
                     f" -o /export/starexec/{sandbox}/output/stdout.txt" + \
                     f" -v /export/starexec/{sandbox}/output/var.out"

    cpu_part = f"-C {args.cpu_limit} -W {args.wall_clock_limit}"
    mem_part = f"-M {args.memory_limit}" if args.memory_limit > 0 else ""
    return f"--timestamp {paths_part} {cpu_part} {mem_part}"
#--------------------------------------------------------------------------------------------------
def getEnvVars(args):

    sandbox = "sandbox" if args.starexec == 1 else "sandbox2"
    if args.starexec:
        input_file = f"/export/starexec/{sandbox}/benchmark/theBenchmark.p"
    else:
        input_file = "/artifacts/CWD/problemfile"

    envVars = [
        ("RLR_INPUT_FILE", input_file),
        ("RLR_CPU_LIMIT", args.cpu_limit),
        ("RLR_WC_LIMIT", args.wall_clock_limit),
        ("RLR_MEM_LIMIT", args.memory_limit),
        ("RLR_INTENT", args.intent),
    ]

    if "TPTP" in os.environ:
        envVars.append(("TPTP", "/artifacts/TPTP"))

    return " ".join([f"-e {k}='{v}'" for k, v in envVars])
#--------------------------------------------------------------------------------------------------
def TPTPMount():

    if "TPTP" in os.environ:
        return f" -v {os.environ['TPTP']}:/artifacts/TPTP"
    return ""
#--------------------------------------------------------------------------------------------------
# This is not used when using --starexec
def makeBenchmark(problem):

    if problem:
        shutil.copy(problem, "./problemfile")
    else:
        with open('./problemfile', 'w') as problemfile:
            problemfile.write(sys.stdin.read())
#--------------------------------------------------------------------------------------------------
if __name__ == "__main__":

    parser = argparse.ArgumentParser("Wrapper for a podman call to a prover image")
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
    parser.add_argument("--dry-run", action="store_true", 
help="dry run")

    parser.add_argument("-s", "--starexec", type=int, default=0, 
help="""This is for using run_image.py from inside a containerized starexec instance. 
This is done using the --remote and --connection flags in podman. (see starexec-proxy-provers)
the arg here will be the sandbox number.

The problem must be made available to the prover container as well.
This can't be done simply using the -v flag as normal, because the problem file isn't on the 
host, where podman expects the volumes when using "--remote"

Instead, we can assume that that run_image.py is running in a container that uses a volume. 
That volume is then mounted inside the prover container as well.

By convention, we can use the volExport from starexec.

This involves the following work:
    1. replacing "-v .:/artifacts/CWD" with "-v volExport:/export"
    2. replacing "/artifacts/CWD/problemfile" in getEnvVars() with "/export/starexec/sandbox{i}/benchmark/theBenchmark.p"
    3. adding "--remote --connection host-machine-podman-connection"
    4. telling runsolver / RLR to output to /export/starexec/sandbox{i}/output/stdout.txt

""")
    
    args = parser.parse_args()

    if args.wall_clock_limit == 0 and args.cpu_limit != 0:
        args.wall_clock_limit = args.cpu_limit
    
    if args.starexec:
        volumes = f"-v volExport:/export"
        remote = "--remote --connection host-machine-podman-connection"
    else:
        volumes = "-v .:/artifacts/CWD"
        remote = ""

    command = f"podman {remote} run {getEnvVars(args)} {TPTPMount()} {volumes} " + \
f"-t {args.image_name} {getRLRArgs(args)} run_system"

#----Run command or print for dry run
    if args.dry_run:
        print(command)
    else:
        makeBenchmark(args.problem)
        subprocess.run(command, shell=True)
        os.remove("./problemfile")
#--------------------------------------------------------------------------------------------------

