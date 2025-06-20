# Date: 2025-05-29
# FileName: example.py
# Description: Example/Demo of SeeCube SDK python bindings.

import re
import cv2 as cv

# Import the python bindings for the SeeCube SDK.
import py_seecube as sc

# Global Variables.

printDefectivePixels = False
printMetadata = False
printSensorTemperature = False
printTargetTemperature = False


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


def self_test():
    print("cheking test function: add")
    if(sc.add(1, 1) == 2):
        print("Sucess!")
    else:
        print("Failure: 1 + 1 != 2")


def main():
    intro_print()
    self_test()
    cli_menu()

    # Initalize the SeeCubeSDK.
    sc_sdk = sc.SeeCubeSDK(
            sc.SeeCubeSDK.verbosityLevel.info, 1)

    # Enable Histogram overlay.
    sc_sdk.parseCoreParameter("displayHistogram")

    # Get the number of conected devices.
    count = sc_sdk.getDeviceCount()
    if(count <= 0):
        print("No device found\n")
        print("Exiting...")
        exit(1)

    print("Displaying devices:\n")
    for i in range(count):
        print("Device: {}: {}\n".format(i, sc_sdk.getDeviceName(i)))

    # Try to connect to the first device.
    # Default is handle 0 and filepath ""
    device = sc.SeeCube(0, "")

    # If there is at least one device connected.

    # Try to connect to the first availble device.
    print("Attempting connection to device...")

    # Check if the device connection was sucessful.
    if(not sc_sdk.isConnected()):
        print("Error: Failed to connect to device!\n")
        print("Exiting...")
        exit(1)

    print("Success: Device now connected.")

    # Get and print out device parameters.
    print("Device Properties:\n")
    print("Part number: " + str(device.getPartNumber()))
    print("Serial: " + str(device.getSerialNumber()))

    # Print out sensor settings.
    tint, gfid, gsk, gain = device.getSensorSettings()
    print("Sensor settings TINT={} GFID={} GSK={} GAIN={}\n".format(
        tint, gfid, gsk, gain))

    # Get the frame rate setting.
    frame_rate = device.getDeviceFrameRate()
    print("Device frame rate: {}\n".format(frame_rate))

    # Get the image size.
    width, height = device.getImageSize()
    print("Image size: {}x{}\n".format(width, height))

    # Allocate memory for metadata.
    sc.allocate_metadata()

    # Set the mapping mode to histogram.
    print("Setting mapping mode: histogram")
    mapping = device.getMappingMode()
    mapping = sc.mapping.histEq
    device.setMappingMode(mapping)

    # Set the color preset value to 10.
    print("Setting color preset value: 10")
    device.setColorPreset(10)

    # Set the processing frame rate to 60FPS.
    print("Setting frame rate: 60")
    device.setProcessingFrameRate(frame_rate)
    free_run = device.getFreeRun()

    # Retrive current image processing status.
    print("Getting image processing status...")
    flat_field_correction = device.getFFC()
    column_destriping = device.getColumnDestriping()

    # TODO: get vector bindings setup.
    defective_pixels_correction = device.getDefectivePixelsCorrectionStatus()
    defective_pixels = None
    if(defective_pixels_correction):
        print("Defective pixel correction: Enabled")
        defective_pixels = device.getDefectivePixelsCorrection()
    else:
        print("Defective pixel correction: Disabled")

    """
    if(printDefectivePixels):
        for pixel in defective_pixels:
            print("Defective pixel at ({}, {})\n".format(pixel.x pixel.y))
    """

    # Gather data on correction and filtering settings.
    shutterlessCorrection = device.getShutterlessCorrection()
    radiometricCorrection = device.getRadiometricCorrection()
    temporalFiltering = device.getTemporalFiltering()


    # Allocate memory for images.

    # Create OpenCV window for viewing images.

    # Create OpenCV window for viewing color images.

    # Setup OpenCV loop.

    # Configure video saving and JPEG compression.

    # PUT WHILE LOOP HERE!

    # Free all memory that was allocated for the program.
    sc.delete_metadata()

    exit(0)


# This is diabled by default when testing.
# Call The main function
main()
