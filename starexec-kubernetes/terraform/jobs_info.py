#!/usr/bin/env python3

import subprocess
import json
from datetime import datetime

def run_command(command):
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
    if result.returncode != 0:
        print(f"Error running command: {command}")
        print(result.stderr)
        exit(1)
    return result.stdout.strip()

def parse_iso8601(date_string):
    if not date_string:
        return None
    return datetime.fromisoformat(date_string.replace('Z', '+00:00'))

def check_job_overlap(jobs):
    overlaps = []
    sorted_jobs = sorted(jobs, key=lambda x: x['start_time'] or datetime.max)
    
    for i in range(len(sorted_jobs)):
        for j in range(i + 1, len(sorted_jobs)):
            job1, job2 = sorted_jobs[i], sorted_jobs[j]
            if job1['end_time'] and job2['start_time'] and job1['end_time'] > job2['start_time']:
                overlaps.append((job1['name'], job2['name']))
    
    return overlaps

def main():
    # Get all jobs
    jobs_json = run_command("kubectl get jobs -o json")
    jobs_data = json.loads(jobs_json)

    node_jobs = {}

    for job in jobs_data['items']:
        job_name = job['metadata']['name']
        start_time = parse_iso8601(job['status'].get('startTime'))
        completion_time = parse_iso8601(job['status'].get('completionTime'))

        print(f"Job: {job_name}")
        print(f"  Start Time: {start_time}")
        print(f"  Completion Time: {completion_time}")

        # Get the pod for this job
        pod_json = run_command(f"kubectl get pods --selector=job-name={job_name} -o json")
        pod_data = json.loads(pod_json)

        for pod in pod_data['items']:
            node_name = pod['spec']['nodeName']
            print(f"  Pod: {pod['metadata']['name']}")
            print(f"    Node: {node_name}")

            # Get node labels
            node_json = run_command(f"kubectl get node {node_name} -o json")
            node_data = json.loads(node_json)
            nodegroup = node_data['metadata']['labels'].get('nodegroup', 'Unknown')

            if nodegroup == 'computenodes':
                print("    Node Type: Compute Node")
            elif nodegroup == 'headnode':
                print("    Node Type: Head Node")
            else:
                print("    Node Type: Unknown")

            if node_name not in node_jobs:
                node_jobs[node_name] = []
            node_jobs[node_name].append({
                'name': job_name,
                'start_time': start_time,
                'end_time': completion_time
            })

        print()

    # Check for overlaps
    has_overlap = False
    for node, jobs in node_jobs.items():
        overlaps = check_job_overlap(jobs)
        if overlaps:
            has_overlap = True
            print(f"ASSERTION FAILED: Overlapping jobs found on node {node}:")
            for job1, job2 in overlaps:
                print(f"  - {job1} and {job2} overlapped")

    if not has_overlap:
        print("ASSERTION PASSED: No two jobs were running at the same time on the same node.")
    else:
        exit(1)

if __name__ == "__main__":
    main()
