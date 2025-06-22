
pybind11_add_module(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME}
PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

# The duplication of logic should be removed.
# Ideally I'll only need evaluate if the mode is UNIT_TESTING or not a 
# Single time.

# Variable to hold the name of the targed shared library to be linked with.
set(SHARED_SDK "SeeCube")
set(SHARED_SDK_PATH "")


add_subdirectory(fake_SeeCube)



#Ensure that the correct libraries are included.
# These libraries are what is used in the example repo.
# Uncomment one of these below to target devices with those serial numbers.

set(SDK_SERIAL "E6D25080001_N1225140005_E3x25110003")
#set(SDK_SERIAL "E6D25230002")

message("\n\nWARNING! This build's shared libraries only support specific hardware!")
message("Please ensure your device's serial number is listed:")
message("Serial Numbers: ${SDK_SERIAL}\n\n")


# First thing to check is if we are in unit testing mode.
# If we are then we want to link the fake library for testing.
if(UNIT_TESTING)
    message("Linking with Fake libraries for unit testing.")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        fake_SeeCube    
    )

elseif(CMAKE_HOST_SYSTEM STREQUAL "Linux")
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(LIBUSB REQUIRED libusb-1.0)
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBUSB_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBUSB_LIBRARIES})

    find_package(OpenCV REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})


    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
        set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/linux_x86/${SDK_SERIAL}/libSeeCube.so")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${MY_SHARED_LIB})

    elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/linux_arm/${SDK_SERIAL}/libSeeCube.so")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${MY_SHARED_LIB})

    else()
        message("ERROR: Unknown platform!")
    endif()

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows" )
    set(MY_SHARED_LIB "${CMAKE_SOURCE_DIR}/src/windows/${SDK_SERIAL}/SeeCubed.lib")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${MY_SHARED_LIB})
endif()

