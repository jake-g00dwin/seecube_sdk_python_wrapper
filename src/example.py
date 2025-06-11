# Date: 2025-05-29
# FileName: example.py
# Description: Example/Demo of SeeCube SDK python bindings.

import re
# import pytest
# import py_seecube
import cv2 as cv


def exract_project_version(file_path):
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


def intro_print():
    print("SeeCube SDK pybindings Example:")
    print("OpenCV version:", cv.__version__)


def cli_menu():
    print("")


def main():
    intro_print()
    cli_menu()

    # Initalize the SeeCubeSDK.
    # py_seecube.

    # Enable Histogram overlay.

    # Get the number of conected devices.

    # If there is at least one device connected.
    if(True):
        # Try to connect to the first availble device.
        print("Attempting connection to device...")

        # Check if the device connection was sucessful.

        # Get and print out device parameters.

        # Allocate memory in C/Cpp style for metadata.

        # Set the mapping mode to histogram.

        # Set the color preset value to 10.

        # Set the processing frame rate to 60FPS.

        # Retrive current image processing status.
        print("Gettign image processing status...")

        # Allocate memory for images.

        # Create OpenCV window for viewing images.

        # Create OpenCV window for viewing color images.

        # Setup OpenCV loop.

        # Configure video saving and JPEG compression.

        # PUT WHILE LOOP HERE!

    exit(0)


# Call The main function
main()
