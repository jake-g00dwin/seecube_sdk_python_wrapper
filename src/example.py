# Date: 2025-05-29
# FileName: example.py
# Description: Example/Demo of SeeCube SDK python bindings.

import re
import cv2 as cv
import numpy as np
from pathlib import Path


# Import the python bindings for the SeeCube SDK.
import py_seecube as sc

# Global Variables.

# These are set during the main function.
width = 0
height = 0

# Meant to hold a matrix for the image data.
mat_img = None

printDefectivePixels = False
printMetadata = False
printSensorTemperature = False
printTargetTemperature = False

clahe = cv.createCLAHE(5, (5, 5))


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


def controller(img, brightness=255, contrast=127):
    brightness = int((brightness - 0) * (255 - (-255)) / (510 - 0) + (-255))
    contrast = int((contrast - 0) * (127 - (-127)) / (254 - 0) + (-127))

    if brightness != 0:
        if brightness > 0:
            shadow = brightness
            max = 255
        else:
            shadow = 0
            max = 255 + brightness

        al_pha = (max - shadow) / 255
        ga_mma = shadow

        # The function addWeighted calculates
        # the weighted sum of two arrays
        cal = cv.addWeighted(img, al_pha, img, 0, ga_mma)

    else:
        cal = img
    if contrast != 0:
        Alpha = float(131 * (contrast + 127)) / (127 * (131 - contrast))
        Gamma = 127 * (1 - Alpha)

        # The function addWeighted calculates
        # the weighted sum of two arrays
        cal = cv.addWeighted(cal, Alpha, cal, 0, Gamma)

    return cal


def BrightnessContrast(img, brightness=0):
    # getTrackbarPos returns the current
    # position of the specified trackbar.
    brightness = cv.getTrackbarPos("Brightness", "Thermal frame")

    contrast = cv.getTrackbarPos("Contrast", "Thermal frame")

    effect = controller(img, brightness, contrast)

    return effect


def intro_print():
    print("SeeCube SDK pybindings Example:")
    print("OpenCV version:", cv.__version__)


def cli_menu():
    print("")


def main():
    intro_print()
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
    data_path = str(Path.cwd() / "data")
    device = sc.SeeCube(0, data_path)

    # If there is at least one device connected.

    # Try to connect to the first availble device.
    print("Attempting connection to device...")

    # Check if the device connection was sucessful.
    if(not sc_sdk.isConnected(0)):
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
    device.setMappingMode(sc.SeeCube.mapping.histEq)

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

    defective_pixels_correction = device.getDefectivePixelsCorrectionStatus()
    defective_pixels = None
    if(defective_pixels_correction):
        print("Defective pixel correction: Enabled")
        result, defective_pixels = device.getDefectivePixelsCorrection()
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

    # Allocate memory for images; uses the size data.
    sc.allocate_imagedata(width, height)

    # Create OpenCV window for viewing images.
    cv.namedWindow("Thermal frame", cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
    cv.resizeWindow("Thermal frame", width, height)

    # Create OpenCV window for viewing color images.
    cv.namedWindow("Color frame", cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
    cv.resizeWindow("Color frame", width, height)

    cv.createTrackbar(
        "Brightness", "Thermal frame", 255, 2 * 255, BrightnessContrast
    )

    # Contrast range -127 to 127
    cv.createTrackbar(
        "Contrast", "Thermal frame", 127, 2 * 127, BrightnessContrast
    )

    print("Press `q` to quit.")

    img_shape = (height, width)
    thermal_img = np.zeros(img_shape, np.uint16)

    # Setup OpenCV loop.
    while True:
        # Check conditions for exiting or breaking out of loop.
        key = cv.waitKey(16)
        if key == ord("q"):
            break

        # Get the current image data.
        # thermal_img = device.getRawFrame()
        np.copyto(thermal_img, device.getRawFrame())

        img8 = cv.normalize(
                thermal_img,
                None,
                0,
                255,
                cv.NORM_MINMAX).astype(np.uint8)

        img8 = np.uint8(img8)

        adj = BrightnessContrast(img8.copy())
        adj = cv.cvtColor(adj, cv.COLOR_GRAY2BGR)

        adj2 = clahe.apply(img8)
        adj2 = cv.cvtColor(adj2, cv.COLOR_GRAY2BGR)

        color_img = cv.applyColorMap(adj2, cv.COLORMAP_INFERNO)

        # Update the image for each window.
        cv.imshow("Thermal frame", adj)
        cv.imshow("Color frame", color_img)

    # Clean up all the CV stuff.
    cv.destroyAllWindows()

    # Free all memory that was allocated for the program.
    sc.delete_metadata()
    sc.delete_imagedata()

    exit(0)


# This is diabled by default when testing.
# Call The main function
main()
