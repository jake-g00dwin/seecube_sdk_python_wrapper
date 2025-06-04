
pybind11_add_module(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME}
PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

# Variable to hold the name of the targed shared library to be linked with.
set(SHARED_SDK "SeeCube")

#Ensure that the correct libraries are included.
# These libraries are what is used in the example repo.


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
        message("Setting linux_x86 lib")
        set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/linux_x86/libSeeCube.so")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        message("Setting linux_arm lib")
        set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/linux_arm/libSeeCube.so")
    endif()
# For windows based systems, there is only one sdk.
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    message("Setting windows lib")
    set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/windows/SeeCube.lib")
endif()

message("Shared library path: ${MY_SHARED_LIB}")

#link_directories(${MY_SHARED_LIB})

# Link with the correct shared library from the SDK.
target_link_libraries(${PROJECT_NAME} PRIVATE ${MY_SHARED_LIB})



