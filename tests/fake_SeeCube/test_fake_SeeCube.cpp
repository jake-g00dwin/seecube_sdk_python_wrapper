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
    void setup()
    {

    }
    void teardown()
    {

    }
};


TEST(test_fakeSeeCube, InstanceOfSeeCubeSDKWorks)
{
    //Declareing an instance of the SeeCubeSDK class as sc_sdk
    SeeCubeSDK sc_sdk(SeeCubeSDK::verbosityLevel::info, 4);
}
