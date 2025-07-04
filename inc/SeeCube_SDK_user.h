﻿#pragma once

/*
DO NOT EDIT THIS FILE!
*/

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#define SEECUBESDK_API __declspec(dllimport)
#else
#define SEECUBESDK_API
#include <pthread.h>
#endif

/**
* Only one instance of this class should be created and used for controlling SeeCube devices,
* and be maintained throughout the program's lifecycle.
* It handles all processing threads, ressources, and logging.
*/
class SEECUBESDK_API SeeCubeSDK {
public:
    /**
    * @brief Verbosity levels used for logging.
    */
    enum class verbosityLevel : uint8_t {
        error = 0,      ///< Only errors are logged.
        warning = 1,    ///< Warnings and errors are logged.
        info = 2        ///< All information will be logged.
    };

private:
    /// \cond
    // SeeCubeSDK class private opaque data.
    // Do not access these members directly.
    static std::map<const int, void*> mPrivateData1;
    static bool mPrivateData2;
    /// \endcond

public:
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
    SeeCubeSDK(const verbosityLevel& pVerbosity = verbosityLevel::error,
               const int& pThreadPoolSize = 0);

    /**
    * @brief Destructor for the SeeCubeSDK class.
    *
    * Releases resources, stops processing threads, and destroys the SeeCubeSDK instance.
    */
    virtual ~SeeCubeSDK(void);

    /**
    * @brief Get the number of connected SeeCube devices.
    *
    * @return An integer representing the count of connected SeeCube devices.
    */
    int getDeviceCount(void);

    /**
    * @brief Get the name of a SeeCube device.
    *
    * @param[in] pHandle The handle of the device. Default is 0.
    * @return A string containing the name of the specified SeeCube device.
    */
    std::string getDeviceName(const int& pHandle = 0);

    /**
    * @brief Check the connection status of a SeeCube device.
    *
    * @param[in] pHandle The handle of the device to check. Default is 0.
    * @return A boolean value: true if the device is connected, false otherwise.
    */
    bool isConnected(const int& pHandle = 0);

    /**
    * @brief Parse and apply core parameters.
    *
    * This function parses the provided parameter string and applies the corresponding core settings.
    *
    * @param[in] pParameter A string containing the core parameter to be parsed and applied.
    */
    void parseCoreParameter(const std::string& pParameter);
};

/**
* Base object used for controlling SeeCube devices.
* One instance of this class should be created for each SeeCube device,
* and be maintained as long as the camera core is in use.
*/
class SEECUBESDK_API SeeCube {
public:
    /**
    * @brief Enum for image levels mapping.
    */
    enum class mapping : uint8_t {
        fullScale = 0,  ///< Full scale (no mapping)
        automatic = 1,  ///< Automatic min/max mapping
        manual = 2,     ///< Manual mapping
        histEq = 3,     ///< Histogram equalization mapping
        adaptive = 4    ///< Adaptive mapping
    };

    /**
    * @brief Enum for image metadata.
    */
    struct metadata {
        float sensorTemperature;    ///< Sensor temperature in Kelvins
        uint64_t frameCounter;      ///< Total frames aquired by the device
        uint64_t relativeTimestamp; ///< Relative timestamp in milliseconds since last transfered frame
        uint64_t epochTimestamp;    ///< Absolute timestamp in milliseconds
        uint32_t* histogram;        ///< Histogram data (if available)
    };

private:
    /// \cond
    // SeeCube class private opaque data.
    // Do not access these members directly.
    uint64_t mPrivateData1;
    const int mPrivateData2;
    uint64_t mPrivateData3;
    std::string mPrivateData4;
    /// \endcond

public:
    /**
     * @brief Constructor for the SeeCube class.
     *
     * Creates a SeeCube instance, connects to a SeeCube device, and initializes camera core settings.
     *
     * @param[in] pHandle The handle of the SeeCube device to connect to. Default is 0.
     * @param[in] mSensorDataPath The path to the sensor data files. Default is an empty string.
     */
    SeeCube(const int& pHandle = 0,
            const std::string& mSensorDataPath = "");

    /**
     * @brief Destructor for the SeeCube class.
     *
     * This virtual destructor is responsible for cleaning up resources,
     * disconnecting from the SeeCube device, and destroying the SeeCube instance.
     * It ensures proper release of any allocated memory and handles device disconnection.
     */
    virtual ~SeeCube(void);

    /**
     * @brief Retrieves the part number of the SeeCube device.
     *
     * This function returns the part number of the connected SeeCube device,
     * which can be used for identification and compatibility checking.
     *
     * @return A string containing the part number of the SeeCube device.
     */
    std::string getPartNumber(void);

    /**
     * @brief Retrieves the serial number of the SeeCube device.
     *
     * This function returns the unique serial number of the connected SeeCube device,
     * which can be used for device identification and tracking.
     *
     * @return A string containing the serial number of the SeeCube device.
     */
    std::string getSerialNumber(void);

     /**
     * @brief Retrieves the current sensor settings from the SeeCube device.
     *
     * This function fetches the current values of various sensor settings, including
     * integration time, transistors gates voltages, external trigger mode, gain and window invert-revert-rotation.
     *
     * @param[out] pTINT Reference to a uint16_t variable where the integration time value will be stored.
     * @param[out] pGFID Reference to a uint16_t variable where the transistors gate voltage for the active microbolometers value will be stored.
     * @param[out] pGSK Reference to a uint16_t variable where the transistors gate voltage for the compensation microbolometers value will be stored.
     * @param[out] pGAIN Reference to a uint16_t variable where the external trigger mode / gain / window invert-revert-rotation values will be stored.
     *
     * @return This function does not return a value.
     */
    void getSensorSettings(uint16_t& pTINT,
                           uint16_t& pGFID,
                           uint16_t& pGSK,
                           uint16_t& pGAIN);

    /**
     * @brief Retrieves the current frame rate of the SeeCube device.
     *
     * This function returns the current frame rate at which the connected SeeCube device
     * can capture images. The frame rate is expressed in frames per second (FPS).
     *
     * @return A float value representing the current frame rate of the device in FPS.
     */
    float getDeviceFrameRate(void);

    /**
     * @brief Sets the frame rate of the SeeCube device.
     *
     * This function attempts to set the frame rate of the connected SeeCube device
     * to the specified value. The actual frame rate achieved may depend on the
     * device's capabilities and current settings.
     *
     * @param[in] pFrameRate The desired frame rate in frames per second (FPS).
     *
     * @return A boolean value indicating the success of the operation:
     *         - true if the frame rate was successfully set
     *         - false if the operation failed or is not supported by the device
     */
    bool setDeviceFrameRate(const float& pFrameRate);

    /**
     * @brief Retrieves the size of the image captured by the SeeCube device.
     *
     * This function gets the current width and height of the images produced by the device.
     *
     * @param[out] pWidth Reference to a size_t variable where the image width will be stored.
     * @param[out] pHeight Reference to a size_t variable where the image height will be stored.
     *
     * @return A boolean value indicating the success of the operation:
     *         - true if the image size was successfully retrieved
     *         - false if the operation failed or the information is not available
     */
    bool getImageSize(size_t& pWidth,
                      size_t& pHeight);

    /**
     * @brief Retrieves a raw/thermal frame from the SeeCube device.
     *
     * This function captures a raw frame from the device, which should be used for all temperature measurements.
     * It can optionally provide metadata about the captured frame.
     *
     * @param[out] pData Pointer to an unsigned char buffer where the raw frame data will be stored.
     *                   The buffer must be pre-allocated with sufficient size to hold the frame data.
     * @param[out] pMetadata Pointer to a metadata struct where frame metadata will be stored.
     *                       Can be nullptr if metadata is not required. Default is nullptr.
     * @param[in] pTimeout Timeout value in milliseconds for frame acquisition.
     *                     If 0, returns immediately if no frame is available.
     *                     If -1, waits indefinitely for a new frame.
     *                     Default is 0.
     *
     * @return Returns true if a frame was successfully acquired, false otherwise.
     *
     * @note If the device is not in free run mode and pTimeout is set to -1, a software trigger
     *       must be sent from another thread, as this call will block until a new frame is available.
     */
    bool getRawFrame(unsigned char* pData,
                     metadata* pMetadata = nullptr,
                     const int32_t& pTimeout = 0);

    /**
     * @brief Retrieves a color frame from the SeeCube device.
     *
     * This function captures a color frame from the device, which should be used for visualizing thermal data after equalization.
     * It can optionally provide metadata about the captured frame.
     *
     * @param[out] pData Pointer to an unsigned char buffer where the color frame data will be stored.
     *                   The buffer must be pre-allocated with sufficient size to hold the frame data.
     * @param[out] pMetadata Pointer to a metadata struct where frame metadata will be stored.
     *                       Can be nullptr if metadata is not required. Default is nullptr.
     * @param[in] pTimeout Timeout value in milliseconds for frame acquisition.
     *                     If 0, returns immediately if no frame is available.
     *                     If -1, waits indefinitely for a new frame.
     *                     Default is 0.
     *
     * @return Returns true if a frame was successfully acquired, false otherwise.
     *
     * @note If the device is not in free run mode and pTimeout is set to -1, a software trigger
     *       must be sent from another thread, as this call will block until a new frame is available.
     */
    bool getColorFrame(unsigned char* pData,
                       metadata* pMetadata = nullptr,
                       const int32_t& pTimeout = 0);

    /**
     * @brief Retrieves the current processing frame rate.
     *
     * This function returns the frame rate at which image processing is being performed.
     * The processing frame rate may differ from the device's capture frame rate.
     *
     * @return A float value representing the current processing frame rate in frames per second (FPS).
     */
    float getProcessingFrameRate(void);

    /**
     * @brief Sets the processing frame rate for image processing.
     *
     * This function sets the frame rate at which image processing operations are performed.
     * The processing frame rate may be different from the device's capture frame rate.
     *
     * @param[in] pFrameRate The desired processing frame rate in frames per second (FPS).
     *
     * @return This function does not return a value.
     */
    void setProcessingFrameRate(const float& pFrameRate);

    /**
     * @brief Sets the free run mode for the SeeCube device.
     *
     * This function toggles the free run mode of the device. When in free run mode,
     * the device continuously captures frames without requiring external/software triggers.
     *
     * @param[in] pFreeRun A boolean reference indicating the desired free run state:
     *                     - true: Enable free run mode
     *                     - false: Disable free run mode (requires triggering)
     *
     * @return This function does not return a value.
     */
    void setFreeRun(const bool& pFreeRun);

    /**
     * @brief Retrieves the current free run mode status of the SeeCube device.
     *
     * This function checks whether the device is currently operating in free run mode,
     * where it continuously captures frames without requiring external or software triggers.
     *
     * @return A boolean value indicating the free run mode status:
     *         - true if the device is in free run mode
     *         - false if the device is not in free run mode (requires triggering)
     */
    bool getFreeRun(void);

    /**
     * @brief Runs a Flat Field Correction (FFC) on the SeeCube device.
     *
     * This function initiates a Flat Field Correction process, which helps to improve
     * image quality by compensating for non-uniformities or parasitic reflections.
     *
     * @param[in] pUseShutter A boolean reference indicating whether to use the shutter during FFC.
     *                        If true, the device will use the shutter for the correction process.
     *                        - Not applicable to Eileen 3, which is not equipped with a mechanical shutter
     *                        Default value is true.
     * @param[in] pFrameCount An integer reference specifying the number of frames to use for FFC.
     *                        This determines how many frames will be averaged for the correction.
     *                        Default value is 8.
     *
     * @return This function does not return a value.
     */
    void runFFC(const bool& pUseShutter = true,
                const int& pFrameCount = 8);

    /**
     * @brief Sets the Flat Field Correction (FFC) status for the SeeCube device.
     *
     * This function enables or disables the Flat Field Correction feature, which
     * helps to improve image quality by compensating for non-uniformities or parasitic reflections.
     *
     * @param[in] pStatus A boolean reference indicating the desired FFC state:
     *                    - true: Enable FFC
     *                    - false: Disable FFC
     *
     * @return This function does not return a value.
     */
    void setFFC(const bool& pStatus);

    /**
     * @brief Retrieves the current Flat Field Correction (FFC) status of the SeeCube device.
     *
     * This function checks whether the Flat Field Correction feature is currently enabled or disabled.
     * FFC helps improve image quality by compensating for non-uniformities or parasitic reflections.
     *
     * @return A boolean value indicating the FFC status:
     *         - true if FFC is currently enabled
     *         - false if FFC is currently disabled
     */
    bool getFFC(void);

    /**
     * @brief Closes the shutter of the SeeCube device.
     *
     * This function sends a command to close the mechanical shutter of the SeeCube device.
     * It is used to protect the sensor or to perform certain calibration operations.
     *
     * @note This function is not applicable to Eileen 3 cores, which are not equipped with a mechanical shutter.
     *
     * @return This function does not return a value.
     */
    void closeShutter(void);

    /**
     * @brief Opens the shutter of the SeeCube device.
     *
     * This function sends a command to open the mechanical shutter of the SeeCube device.
     * It is used to expose the sensor for imaging or to prepare for certain operations.
     *
     * @note This function is not applicable to Eileen 3 cores, which are not equipped with a mechanical shutter.
     *
     * @return This function does not return a value.
     */
    void openShutter(void);

    /**
     * @brief Sets the color preset for image visualization.
     *
     * This function changes the color mapping used for visualizing thermal images.
     * Different presets can enhance the visibility of specific temperature ranges or features.
     *
     * @param[in,out] pPreset Reference to an integer specifying the desired color preset.
     *                        The value may be modified to reflect the actually applied preset
     *                        if the requested preset is not available.
     *
     * @note The available presets and their corresponding integer values may vary
     *       depending on the specific SeeCube device model and firmware version.
     *
     * @return This function does not return a value.
     */
    void setColorPreset(int& pPreset);

    /**
     * @brief Retrieves the current color preset used for image visualization.
     *
     * This function returns an integer representing the currently active color preset
     * used for visualizing thermal images. Different presets can enhance the visibility
     * of specific temperature ranges or features in the thermal image.
     *
     * @return An integer value representing the current color preset.
     *         The meaning of this value depends on the specific SeeCube device model
     *         and firmware version, where each integer corresponds to a particular
     *         color mapping scheme.
     */
    int getColorPreset(void);

    /**
     * @brief Sets the status of defective pixels correction.
     *
     * This function enables or disables the correction of defective pixels in the thermal image.
     * When enabled, the device will attempt to interpolate or correct pixels that have been
     * identified as defective, improving overall image quality.
     *
     * @param[in] pStatus A boolean reference indicating the desired correction state:
     *                    - true: Enable defective pixels correction
     *                    - false: Disable defective pixels correction
     *
     * @return This function does not return a value.
     */
    void setDefectivePixelsCorrection(const bool& pStatus);

    /**
     * @brief Retrieves the current status of defective pixels correction.
     *
     * This function checks whether the defective pixels correction feature is currently
     * enabled or disabled on the SeeCube device. Defective pixels correction helps
     * improve image quality by interpolating or correcting pixels identified as defective.
     *
     * @return A boolean value indicating the defective pixels correction status:
     *         - true if defective pixels correction is currently enabled
     *         - false if defective pixels correction is currently disabled
     */
    bool getDefectivePixelsCorrection(void);

    /**
     * @brief Retrieves the current status of defective pixels correction and the list of defective pixels.
     *
     * This function checks whether the defective pixels correction feature is currently enabled
     * and provides a list of identified defective pixels on the sensor.
     *
     * @param[out] pDefectivePixelsList A reference to a vector of integer pairs, where each pair
     *                                  represents the (x, y) coordinates of a defective pixel.
     *                                  This vector will be populated with the list of defective pixels.
     *
     * @return A boolean value indicating the defective pixels correction status:
     *         - true if defective pixels correction is currently enabled
     *         - false if defective pixels correction is currently disabled
     */
    bool getDefectivePixelsCorrection(std::vector<std::pair<int, int>>& pDefectivePixelsList);

    /**
     * @brief Sets the status of shutterless correction for the SeeCube device.
     *
     * This function enables or disables the shutterless correction feature. When enabled,
     * the device applies correction algorithms to improve image quality without using
     * a mechanical shutter, which is particularly useful for continuous operation or
     * in devices without a physical shutter.
     *
     * @param[in] pStatus A boolean reference indicating the desired shutterless correction state:
     *                    - true: Enable shutterless correction
     *                    - false: Disable shutterless correction
     *
     * @return This function does not return a value.
     */
    void setShutterlessCorrection(const bool& pStatus);

    /**
     * @brief Retrieves the current status of shutterless correction for the SeeCube device.
     *
     * This function checks whether the shutterless correction feature is currently enabled or disabled.
     * Shutterless correction improves image quality without using a mechanical shutter, which is
     * particularly useful for continuous operation or in devices without a physical shutter.
     *
     * @return A boolean value indicating the shutterless correction status:
     *         - true if shutterless correction is currently enabled
     *         - false if shutterless correction is currently disabled
     */
    bool getShutterlessCorrection(void);

    /**
     * @brief Sets the status of radiometric correction for the SeeCube device.
     *
     * This function enables or disables the radiometric correction feature. When enabled,
     * the device applies correction algorithms to improve the accuracy of temperature
     * measurements in the thermal image.
     *
     * @param[in] pStatus A boolean reference indicating the desired radiometric correction state:
     *                    - true: Enable radiometric correction
     *                    - false: Disable radiometric correction
     *
     * @return This function does not return a value.
     */
    void setRadiometricCorrection(const bool& pStatus);

    /**
     * @brief Retrieves the current status of radiometric correction for the SeeCube device.
     *
     * This function checks whether the radiometric correction feature is currently enabled or disabled.
     * Radiometric correction improves the accuracy of temperature measurements in the thermal image.
     *
     * @return A boolean value indicating the radiometric correction status:
     *         - true if radiometric correction is currently enabled
     *         - false if radiometric correction is currently disabled
     */
    bool getRadiometricCorrection(void);

    /**
     * @brief Retrieves the current temperature of the sensor's Focal Plane Array (FPA).
     *
     * This function returns the current temperature of the sensor's FPA in degrees Celsius.
     * Monitoring the sensor temperature is important for maintaining calibration accuracy
     * and ensuring optimal performance of the thermal imaging system.
     *
     * @return A float value representing the current sensor FPA temperature in degrees Celsius.
     */
    float getSensorTemperature(void);

    /**
     * @brief Retrieves the temperature of a specific pixel in the thermal image.
     *
     * This function calculates and returns the temperature of a pixel at the specified
     * coordinates in the thermal image. The temperature is returned in degrees Celsius.
     *
     * @param[in] pX The x-coordinate of the pixel in the thermal image.
     * @param[in] pY The y-coordinate of the pixel in the thermal image.
     * @param[in] pEmissivity The emissivity value of the target surface, ranging from 0 to 100.
     *                        Default value is 100.0 (100% emissivity).
     *
     * @return The temperature of the specified pixel in degrees Celsius.
     *         Returns -273.15 (zero kelvin) if the pixel coordinates are out of range.
     */
    float getPixelTemperature(const int& pX,
                              const int& pY,
                              const float& pEmissivity = 100.0f);

    /**
     * @brief Sets the image mapping mode for thermal image visualization as color image.
     *
     * This function configures how thermal image data is mapped to color image.
     * Different mapping modes can enhance visibility of specific temperature ranges or features.
     *
     * @param[in] pMode The mapping mode to set. Use values from the SeeCube::mapping enum.
     * @param[in] pFirstParam Optional parameter used in specific mapping modes:
     *                        - For manual mode: Minimum level for tone mapping (range: 0 to 65535)
     *                        - For histogram equalization or adaptive modes: Normalization factor (range: 0 to 100)
     *                        - For other modes: Not used
     * @param[in] pSecondParam Optional parameter used in specific mapping modes:
     *                         - For manual mode: Maximum level for tone mapping (range: 0 to 65535)
     *                         - For other modes: Not used
     *
     * @return This function does not return a value.
     */
    void setMappingMode(const mapping& pMode,
                        const float& pFirstParam = -1.0f,
                        const float& pSecondParam = -1.0f);

    /**
     * @brief Retrieves the current image mapping mode for thermal image visualization.
     *
     * This function returns the current mapping mode used for converting thermal image data
     * to color image data. The mapping mode determines how temperature values are translated
     * into visual representations, which can affect the visibility of specific temperature
     * ranges or features in the thermal image.
     *
     * @return A SeeCube::mapping enum value representing the current mapping mode:
     *         - fullScale: Full scale (no mapping)
     *         - automatic: Automatic min/max mapping
     *         - manual: Manual mapping
     *         - histEq: Histogram equalization mapping
     *         - adaptive: Adaptive mapping
     */
    mapping getMappingMode(void);

    /**
     * @brief Sets the status of image column destriping.
     *
     * This function enables or disables the column destriping feature for thermal images.
     * Column destriping helps to remove vertical artifacts that can occur in thermal imaging
     * due to sensor non-uniformities or other factors, potentially improving image quality.
     *
     * @param[in] pStatus A boolean reference indicating the desired destriping state:
     *                    - true: Enable column destriping
     *                    - false: Disable column destriping
     *
     * @note Additional parameters for fine-tuning the destriping process may be exposed in future releases.
     *
     * @return This function does not return a value.
     */
    void setColumnDestriping(const bool& pStatus);

    /**
     * @brief Retrieves the current status of image column destriping.
     *
     * This function checks whether the column destriping feature is currently enabled or disabled.
     * Column destriping helps to remove vertical artifacts in thermal images that can occur due to
     * sensor non-uniformities or other factors, potentially improving image quality.
     *
     * @return A boolean value indicating the column destriping status:
     *         - true if column destriping is currently enabled
     *         - false if column destriping is currently disabled
     */
    bool getColumnDestriping(void);

    /**
     * @brief Sets the temporal filtering ratio for image processing.
     *
     * This function configures the temporal filtering applied to the thermal images.
     * Temporal filtering helps reduce noise and smooth out rapid temperature fluctuations
     * between consecutive frames.
     *
     * @param[in] pRatio The filtering ratio, ranging from 0.0 to 1.0.
     *                   - 0.0: No filtering (each frame is independent)
     *                   - 1.0: Maximum filtering (high temporal smoothing)
     *                   Values between 0 and 1 provide varying degrees of temporal smoothing.
     *
     * @note Additional parameters for fine-tuning the temporal filtering may be exposed in future releases.
     *
     * @return This function does not return a value.
     */
    void setTemporalFiltering(const float& pRatio);

    /**
     * @brief Retrieves the current temporal filtering ratio.
     *
     * This function returns the current temporal filtering ratio applied to the thermal images.
     * The temporal filtering helps reduce noise and smooth out rapid temperature fluctuations
     * between consecutive frames.
     *
     * @return A float value representing the current temporal filtering ratio:
     *         - 0.0 indicates no filtering (each frame is independent)
     *         - 1.0 indicates maximum filtering (high temporal smoothing)
     *         - Values between 0.0 and 1.0 represent varying degrees of temporal smoothing
     */
    float getTemporalFiltering(void);

    /**
     * @brief Sends a software trigger request to the SeeCube device.
     *
     * This function initiates a software trigger for frame acquisition when the device
     * is not in free run mode. It's used to manually request a new frame from the device.
     *
     * @note This function should be called only when the device is not in free run mode.
     *
     * @return This function does not return a value.
     */
    void softwareTriggerRequest(void);
};
