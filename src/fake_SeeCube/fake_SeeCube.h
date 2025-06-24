/**
 * @file fake_SeeCube.h
 * @brief A fake of the SeeCube SDK
 * @author: Jake Goodwin
 * @date: 2025-06-20
 */

/*
 * This header is for faking the actual compiled SeeCube SDK that is
 * distributed as a compiled library.
 *
 *
 */

#ifndef FAKE_SEECUBE
#define FAKE_SEECUBE

#include "SeeCube_SDK_user.h"

#define fake_max_fps 120
#define fake_min_fps 24

#define fake_width_default 1920
#define fake_height_default 1080

void set_FakeSeeCubeDeviceCount(int count);
void fakeSeeCube_setCameraConnectionState(bool set_connected);
void fakeSeeCube_setImageSizeReturnValue(bool value);
void fakeSeeCube_setRawImageReturnBool(bool value);
bool spy_is_pixelcorrection();

#endif // FAKE_SEECUBE
