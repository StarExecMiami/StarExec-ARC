#!/bin/bash

# Directory to modify
DIR="$1"

# Ensure directory is specified
if [[ -z "$DIR" ]]; then
    echo "Please specify a directory."
    exit 1
fi

# Loop over all .sh files in the directory
find "$DIR" -name "*.sh" -type f | while read -r file; do
    # Output the modified script to a temporary file
    {
        echo "#!/bin/bash"
        echo "set -e"
        echo "set -o pipefail"
        cat "$file" | tail -n +2
    } >"$file.tmp"

    # Replace the original script with the modified one
    mv "$file.tmp" "$file"

    # Make the script executable
    chmod +x "$file"
done

# Find and remove all .tmp files in the directory
find "$DIR" -name "*.tmp" -type f -delete
