/*
 * Author: Jake G 
 * Date: 2025 
 * filename: fake_SeeCube.c
 * description: For testing. 
 */

#include "fake_SeeCube.h"
#include <iostream>
#include <cstring>

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
bool fake_rawimage_return = false;

bool is_pixelcorrection = false;

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


void fakeSeeCube_setRawImageReturnBool(bool value)
{
    fake_rawimage_return = value;
}


bool spy_is_pixelcorrection()
{
    return is_pixelcorrection;
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


bool SeeCube::getRawFrame(unsigned char* pData,
        metadata* pMetadata, 
        const int32_t& pTimeout)
{
    //We want zero out the memory before we send it back.
    std::memset(pData, 0, sizeof(uint16_t) * (fake_height_default * fake_width_default));    

    return fake_rawimage_return;
}


bool SeeCube::getColorFrame(unsigned char* pData, 
        metadata* pMetadata,
        const int32_t& pTimeout)
{
    return false;
}


float SeeCube::getProcessingFrameRate(void)
{
    return 0.0;
}


void SeeCube::setProcessingFrameRate(const float& pFrameRate)
{

}


void SeeCube::setFreeRun(const bool& pFreeRun)
{

}


bool SeeCube::getFreeRun(void)
{
    return false;
}


void SeeCube::runFFC(const bool& pUseShutter,
            const int& pFrameCount)
{

}


void SeeCube::setFFC(const bool& pStatus)
{

}


bool SeeCube::getFFC(void)
{
    return false;
}


void SeeCube::closeShutter(void)
{

}

void SeeCube::openShutter(void)
{

}


void SeeCube::setColorPreset(int& pPreset)
{

}

int SeeCube::getColorPreset(void)
{
    return 0;
}



void SeeCube::setDefectivePixelsCorrection(const bool& pStatus)
{
    is_pixelcorrection = pStatus;
}

bool SeeCube::getDefectivePixelsCorrection(void)
{
    return is_pixelcorrection;
}


bool SeeCube::getDefectivePixelsCorrection(
        std::vector<std::pair<int, int>>& pDefectivePixelsList)
{
    pDefectivePixelsList.push_back({255, 255});
    return is_pixelcorrection;
}



void SeeCube::setShutterlessCorrection(const bool& pStatus)
{

}


bool SeeCube::getShutterlessCorrection(void)
{
    return false;
}


void SeeCube::setRadiometricCorrection(const bool& pStatus)
{

}


bool SeeCube::getRadiometricCorrection(void)
{
    return false;
}


float SeeCube::getSensorTemperature(void)
{
    return 0.0;
}


float SeeCube::getPixelTemperature(const int& pX,
                          const int& pY,
                          const float& pEmissivity)
{
    return 0.0;
}


void SeeCube::setMappingMode(const mapping& pMode,
                    const float& pFirstParam,
                    const float& pSecondParam)
{

}



SeeCube::mapping SeeCube::getMappingMode(void)
{
    mapping fake_mapping;
    return fake_mapping;
}


void SeeCube::setColumnDestriping(const bool& pStatus)
{

}



bool SeeCube::getColumnDestriping(void)
{
    return false;
}

void SeeCube::setTemporalFiltering(const float& pRatio)
{

}


float SeeCube::getTemporalFiltering(void)
{
    return 0.0;
}


void SeeCube::softwareTriggerRequest(void)
{

}

















