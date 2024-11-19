import requests
import shutil
import subprocess

def download_file(url, local_filename):
    """Download a file from the specified URL."""
    response = requests.get(url, stream=True)
    with open(local_filename, 'wb') as f:
        shutil.copyfileobj(response.raw, f)
    return local_filename

def execute_command(command):
    """Execute a shell command."""
    subprocess.run(command, shell=True)

if __name__ == "__main__":
    url = "https://github.com/PacktPublishing/Reverse-Engineering-Cookbook/raw/refs/heads/master/README.md"
    local_file = "README.md"
    print(f"Downloading {url}...")
    download_file(url, local_file)
    
    print("Executing a command...")
    execute_command("echo Hello World")
