
import argparse
import os
from pathlib import Path
import subprocess
import re

build_directory = 'proj_build'
parent_directory = os.path.abspath(os.path.join(os.path.dirname(__file__)))
cmake_proj_name_str = 'CUI_PROJECT_NAME'

def check_if_build_directory_exists():
    ret = False
    target_directory = os.path.join(parent_directory, build_directory)
    if os.path.exists(target_directory) and os.path.isdir(target_directory):
        ret = True
    else:
        ret = False
    return ret
    

def build():
    print('Building...')
    if not check_if_build_directory_exists():
        Path(build_directory).mkdir(parents=True, exist_ok=True)
    os.chdir(build_directory)
    subprocess.run(["cmake", ".."])
    subprocess.run(["cmake", "--build", ".", "-j", "4"])

def read_cmake_variable():
    with open('CMakeLists.txt', "r") as cmake_file:
        content = cmake_file.read()
        # Construct regular expression to match the variable assignment
        pattern = re.compile(r"set\s*\(\s*" + re.escape(cmake_proj_name_str) + r"\s+(.*?)\s*\)", re.MULTILINE | re.DOTALL)
        match = pattern.search(content)
        if match:
            return match.group(1).strip("'\"")
        else:
            return None

def run():
    print('Running...')
    if not check_if_build_directory_exists():
        print(f'No {build_directory} found; please build the project first(python run.py build).')
        return
    project_name = read_cmake_variable()
    subprocess.run([f'{build_directory}/{project_name}'])

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="A script to perform build or run actions.")

    parser.add_argument("action", choices=["build", "run"], help="Action to perform: 'build' or 'run'")

    args = parser.parse_args()

    if args.action == 'build':
        build()
    elif args.action == "run":
        run()
