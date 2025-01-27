import argparse
import subprocess
from time import sleep
from random import randint
import os

def makeJobYAML(template, args):
	"""
	Generate job.yaml from job_jinja.yaml
	"""

	with open(template) as f:
		template = f.read()

	template = template.replace("{{ cpusToStress }}", str(args.cpusToStress))
	template = template.replace("{{ jobNum }}", str(randint(1,100_000_000_000)))
	template = template.replace("{{ timeout }}", str(args.timeout))
	template = template.replace("{{ cpuResourceReq }}", args.cpuResourceReq)

	return template


def runJobs(args):
	for i in range(args.numJobs):
		yaml = makeJobYAML("exampleJobTemplate.yaml", args)

		with open(".job.yaml", "w") as f:
			f.write(yaml)

		subprocess.run("kubectl apply -f .job.yaml", shell=True)
		sleep(0.5)


if __name__=="__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument("numJobs", type=int, default=16)
	parser.add_argument("--cpusToStress", type=int, default=1)
	parser.add_argument("--timeout", type=int, default=60)
	parser.add_argument("--cpuResourceReq", type=str, default="1930m")
	args = parser.parse_args()

	runJobs(args)
