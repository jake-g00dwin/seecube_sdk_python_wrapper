/*
 * Author: Jake G 
 * Date: 2025 
 * filename: fake_SeeCube.c
 * description: For testing. 
 */

#include "fake_SeeCube.h"
#include <iostream>

/*
 *################################
 * SECTION
 *################################
 */


int FakeSeeCube_DeviceCount;
std::string device_name = "";
bool is_connected = false;

float device_framerate = 60.0;

bool fake_imagesize_return = false;


void set_FakeSeeCubeDeviceCount(int count)
{
    FakeSeeCube_DeviceCount = count;
}


void fakeSeeCube_setCameraConnectionState( bool set_connected)
{
    is_connected = set_connected;
}


void fakeSeeCube_setImageSizeReturnValue(bool value)
{
    fake_imagesize_return = value;
}


/*
 *################################
 * SeeCubeSDK 
 *################################
 */

/**
* @brief Constructor for the SeeCubeSDK class.
*
* Creates a SeeCubeSDK instance and enumerates connected devices, setting up the SDK environment
* with specified verbosity level and thread pool size.
*
* @param[in] pVerbosity The verbosity level for logging. Determines the amount of information logged.
*                       Default value is verbosityLevel::error.
* @param[in] pThreadPoolSize The size of the thread pool to be used by the SDK.
*                            A value of 0 lets the SDK determine the optimal size.
*                            Default is 0.
*/
SeeCubeSDK::SeeCubeSDK(const verbosityLevel& pVerbosity,
           const int& pThreadPoolSize)
{
    //std::cout << "Constructor Called!" << std::endl;
}


SeeCubeSDK::~SeeCubeSDK(void)
{
    //std::cout << "Destructor Called!" << std::endl;
}

int SeeCubeSDK::getDeviceCount()
{
    return FakeSeeCube_DeviceCount;
}


std::string SeeCubeSDK::getDeviceName(const int& pHandle)
{
    if(FakeSeeCube_DeviceCount == 0){
        device_name = "undefined"; 
    }
    else{
        device_name = "device_name";
    }
    return device_name;
}


bool SeeCubeSDK::isConnected(const int& pHandle)
{
    return is_connected;
}


void SeeCubeSDK::parseCoreParameter(const std::string& pParameter)
{
    //Do nothing for now.
}



/*
 *################################
 * SeeCube Class Definitions 
 *################################
 */


SeeCube::SeeCube(const int& pHandle,const std::string& mSensorDataPath)
    : mPrivateData2(pHandle)
{
    mPrivateData1 = 0;
    mPrivateData3 = 0;
    mPrivateData4 = mSensorDataPath;
}


SeeCube::~SeeCube(void)
{
    //std::cout << "Destructor Called!" << std::endl;
}


std::string SeeCube::getPartNumber(void)
{
    std::string part_number{"FAKEPART"};
    return part_number;
}


std::string SeeCube::getSerialNumber(void)
{
    std::string part_number{"FAKESERIAL"};
    return part_number;
}


void SeeCube::getSensorSettings(uint16_t& pTINT,
                           uint16_t& pGFID,
                           uint16_t& pGSK,
                           uint16_t& pGAIN)
{
    //Just leaving them, stubbing the function.
}


float SeeCube::getDeviceFrameRate(void)
{
    return device_framerate;
}


bool SeeCube::setDeviceFrameRate(const float& pFrameRate)
{
    if(pFrameRate > fake_max_fps || pFrameRate < fake_min_fps){
        return false;
    }
    
    device_framerate = pFrameRate;
    return true;
}


bool SeeCube::getImageSize(size_t& pWidth, size_t& pHeight)
{
    pWidth = fake_width_default;
    pHeight = fake_height_default;
    return fake_imagesize_return;
}

