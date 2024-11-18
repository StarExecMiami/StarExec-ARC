import subprocess
import requests


def parse_image_name(imageName):
    # First, split by '@' to separate digest (if any)
    if '@' in imageName:
        imageName, digest = imageName.rsplit('@', 1)
    else:
        digest = None

    # Now split by ':' to separate tag (if any)
    if ':' in imageName:
        name, tag = imageName.rsplit(':', 1)
    else:
        name = imageName
        tag = None

    # Now split name into parts
    parts = name.split('/')

    if len(parts) >= 2 and ('.' in parts[0] or ':' in parts[0]):
        # The first part is the registryURL
        registryURL = parts[0]
        repository = '/'.join(parts[1:])
    else:
        # No registryURL
        registryURL = None
        repository = '/'.join(parts)

    return registryURL, repository, tag, digest

def findImageOnline(imageName):
    """Check if the image exists in an online registry such as docker.io. returns true or false"""
    registryURL, repository, tag, digest = parse_image_name(imageName)

    if registryURL is None:
        # Image name does not have a URL
        return False

    if tag is None and digest is None:
        # No tag or digest specified, default to 'latest'
        tag = 'latest'

    if registryURL in ['docker.io', 'registry.hub.docker.com', 'index.docker.io']:
        # Use Docker Hub API
        # Split repository into namespace and repo_name
        repository_parts = repository.split('/')
        if len(repository_parts) == 2:
            namespace = repository_parts[0]
            repo_name = repository_parts[1]
        elif len(repository_parts) == 1:
            namespace = 'library'  # Default namespace
            repo_name = repository_parts[0]
        else:
            # Repositories with more than 2 parts are not handled
            return False

        if digest:
            # Query by digest is more complex, and requires Docker Registry API
            # For simplicity, we'll not handle digest in this example
            return False

        url = f'https://registry.hub.docker.com/v2/repositories/{namespace}/{repo_name}/tags/{tag}/'

        try:
            response = requests.get(url)
            if response.status_code == 200:
                return True
            elif response.status_code == 404:
                return False
            else:
                # Other error
                return False
        except Exception as e:
            return False

    else:
        return False

def findImageLocal(imageName):
    """Check if the image exists locally."""
    try:
        # Run docker command to list images and search for imageName
        result = subprocess.run(['podman', 'images', '--format', '{{.Repository}}:{{.Tag}}'], capture_output=True, text=True)
        if imageName in result.stdout:
            return True
    except Exception as e:
        print(f"Error checking image locally: {e}")
    return False

def verifyImageExists(imageName):
    """Verifies that the imageName provided is either:
    a valid image path such as docker.io/tptpstarexec/eprover:3.0.03-RLR-arm64
                                 or 
    + a valid image name such as tptpstarexec/eprover:3.0.03-RLR-arm64"""

    if findImageOnline(imageName):
        print(f"Found '{imageName}' online. This is the preferred way to do things.")
    elif findImageLocal(imageName):
        print(f"Found '{imageName}' locally. However, in the cloud setting, be aware that EKS must be able to find it and that having it locally on your development machine is not enough.")
    else:
        print(f"""
#####################################################
# Failed to find image locally or online.           #
# (THE RESULTING PROXY PROVER WILL LIKELY NOT WORK) #
#                                                   #
# The image name '{imageName}' needs to be able to  #
# be found by starexec's kubernetes cluster         #
#####################################################
""")
