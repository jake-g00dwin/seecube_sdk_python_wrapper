
pybind11_add_module(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME}
PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

# Variable to hold the name of the targed shared library to be linked with.
set(SHARED_SDK "SeeCube")
set(SHARED_SDK_PATH "")

#Ensure that the correct libraries are included.
# These libraries are what is used in the example repo.
# Uncomment one of these below to target devices with those serial numbers.

set(SDK_SERIAL "E6D25080001_N1225140005_E3x25110003")
#set(SDK_SERIAL "E6D2523002")


message("\n\nWARNING! This build's shared libraries only support specific hardware!")
message("Please ensure your device's serial number is listed:")
message("Serial Numbers: ${SDK_SERIAL}\n\n")

# Determine the correct shared library to link
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    # If the system is a linux based system then it coulb be x86 or arm

    find_package(PkgConfig REQUIRED)

    pkg_check_modules(LIBUSB REQUIRED libusb-1.0)
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBUSB_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBUSB_LIBRARIES})

    find_package(OpenCV REQUIRED)
#pkg_check_modules(OPENCV REQUIRED OpenCV)
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
        message("\n\n##############################")
        message("Setting linux_x86 lib")
        message("##############################\n\n")

        set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/linux_x86/${SDK_SERIAL}/libSeeCube.so")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        message("\n\n##############################")
        message("Setting linux_arm lib")
        message("##############################\n\n")

        set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/linux_arm/${SDK_SERIAL}/libSeeCube.so")
    endif()
# For windows based systems, there is only one sdk.
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    message("\n\n##############################")
    message("Setting windows lib")
    message("##############################\n\n")
    # There is both the debug and release libraries availble.
    set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/windows/${SDK_SERIAL}/SeeCubed.lib")
    #set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/windows/${SDK_SERIAL}/SeeCube.lib")
endif()

message("Shared library path: ${MY_SHARED_LIB}")

#link_directories(${MY_SHARED_LIB})

# Link with the correct shared library from the SDK.
target_link_libraries(${PROJECT_NAME} PRIVATE ${MY_SHARED_LIB})




