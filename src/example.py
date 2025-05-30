# Date: 2025-05-29
# FileName: example.py
# Description: Example/Demo of SeeCube SDK python bindings. 

import re
import pytest
import py_seecube


def exract_project_versione(file_path):
    version_pattern = re.compile(
            r'project\s*\([^\)]+VERSION\s+([\d\.]+)',
            re.IGNORECASE)

    try:
        with open(file_path, 'r', encoding='utf-8') as cmake_file:
            for line in cmake_file:
                match = version_pattern.search(line)
                if match:
                    return match.group(1)
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"Error reading file: {e}")


def cli_menu():
    print("SeeCube SDK pybindings Example:")
    print("")


def main():
    cli_menu()
