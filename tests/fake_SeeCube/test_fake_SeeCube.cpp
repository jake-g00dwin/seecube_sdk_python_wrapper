/*
 * Author: username
 * Date: todays_date 
 * filename: test_fake_SeeCube.c
 * description: module_purpose
 */


//The include for <map> causes issues, likely due to the memory leak detection
//that is part of the cpputest framework.
#include "fake_SeeCube.h"


#include "CppUTest/CommandLineTestRunner.h"

extern "C" 
{
    //#include "fake_SeeCube.h"
}

TEST_GROUP(test_fakeSeeCube)
{
    SeeCubeSDK sc_sdk;
    void setup()
    {
        //Declareing an instance of the SeeCubeSDK class as sc_sdk
        SeeCubeSDK sc_sdk(SeeCubeSDK::verbosityLevel::info, 1);
    }
    void teardown()
    {

    }
};


TEST(test_fakeSeeCube, SCSDK_GetsInstanceValue)
{
    set_FakeSeeCubeDeviceCount(0);
    CHECK_EQUAL(0, sc_sdk.getDeviceCount());

    set_FakeSeeCubeDeviceCount(1);
    CHECK_EQUAL(1, sc_sdk.getDeviceCount());
}

