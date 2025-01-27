#!/bin/bash

# Ask the user if they want to delete jobs from all namespaces or a specific one
echo "Do you want to delete Kubernetes jobs from all namespaces? (yes/no)"
read all_namespaces

if [[ $all_namespaces == "yes" ]]; then
    # Delete all jobs in all namespaces
    echo "Deleting all jobs in all namespaces..."
    kubectl delete jobs --all --all-namespaces
else
    # Ask for the specific namespace
    echo "Enter the namespace from which you want to delete jobs:"
    read namespace

    # Check if the namespace variable is empty
    if [[ -z $namespace ]]; then
        echo "Namespace is required. Exiting script."
        exit 1
    else
        # Delete all jobs in the specified namespace
        echo "Deleting all jobs in namespace $namespace..."
        kubectl delete jobs --all -n $namespace
    fi
fi

echo "Jobs deletion completed."

