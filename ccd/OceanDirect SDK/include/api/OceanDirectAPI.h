/*******************************************************
 * @file    OceanDirectAPI.h
 * @date    September 2021
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to connect to devices over USB and other buses.
 * This is intended as a usable and extensible API. The method
 * calls below represent the complete C and Python interface for
 * accessing an Ocean Insight spectrometer.
 *
 * This provides a C and Python interface to help with linkage.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2020] Ocean Insight Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Ocean Insight Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Ocean Insight Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Ocean Insight Incorporated.
 *
 **************************************************************************/

#ifndef OCEAN_DIRECT_API_H
#define OCEAN_DIRECT_API_H

#include "api/DllDecl.h"
#include "api/FeatureIds.h"
#include "common/public/UsbEndpoint.h"

#ifdef __cplusplus
#include <vector>
#include <fstream>
#include <memory>
#include "common/devices/IDevice.h"
#include "api/advanced/Advance.h"
#include "common/public/SpectrumWithMetadata.h"

extern "C" {
    /** Redeclaration of the features enum with "friendlier" names for the public API.
     * Use this with isFeatureEnabled to determine if a spectrometer has a give feature.
     * Give it C linkage so it can be used by the C API.
     */
    enum FeatureId {
        FEATURE_ID_SERIAL_NUMBER = oceandirect::api::serNo,
        FEATURE_ID_SPECTROMETER = oceandirect::api::spectrm,
        FEATURE_ID_THERMOELECTRIC = oceandirect::api::tec,
        FEATURE_ID_IRRADCAL = oceandirect::api::iirad,
        FEATURE_ID_EEPROM = oceandirect::api::eeprom,
        FEATURE_ID_STROBE_LAMP = oceandirect::api::strobe,
        FEATURE_ID_WAVECAL = oceandirect::api::wavecal,
        FEATURE_ID_NONLINEARITYCAL = oceandirect::api::nonline,
        FEATURE_ID_STRAYLIGHTCAL = oceandirect::api::stray,
        FEATURE_ID_RAW_BUS_ACCESS = oceandirect::api::raw,
        FEATURE_ID_CONTINUOUS_STROBE = oceandirect::api::contsrtb,
        FEATURE_ID_LIGHT_SOURCE = oceandirect::api::light,
        FEATURE_ID_TEMPERATURE = oceandirect::api::temper,
        FEATURE_ID_OPTICAL_BENCH = oceandirect::api::optic,
        FEATURE_ID_REVISION = oceandirect::api::revise,
        FEATURE_ID_DATA_BUFFER = oceandirect::api::buffer,
        FEATURE_ID_PIXEL_BINNING = oceandirect::api::binn,
        FEATURE_ID_GPIO = oceandirect::api::gpio,
        FEATURE_ID_SINGLE_STROBE = oceandirect::api::singlestrb,
        FEATURE_ID_QUERY_STATUS = oceandirect::api::status,
        FEATURE_ID_BACK_TO_BACK = oceandirect::api::backToBack,
        FEATURE_ID_LED_ACTIVITY = oceandirect::api::activity,
        FEATURE_ID_TIME_META = oceandirect::api::time,
        FEATURE_ID_DHCP = oceandirect::api::dhcp,
        FEATURE_ID_PIXEL = oceandirect::api::pixel,
        FEATURE_ID_AUTO_NULLING = oceandirect::api::autonulling,
        FEATURE_ID_IPV4_ADDRESS = oceandirect::api::ipv4address,
        FEATURE_ID_IPV4_USER_STRING = oceandirect::api::userstring,
        FEATURE_ID_DEVICE_INFORMATION = oceandirect::api::deviceInformation,
        FEATURE_ID_DEVICE_ALIAS = oceandirect::api::deviceAlias,
        FEATURE_ID_SERIAL_PORT = oceandirect::api::serialPort,
        FEATURE_ID_SPECTRUM_ACQUISITION_CONTROL = oceandirect::api::spectrumAcquisitionControl,
        FEATURE_ID_NETWORK_CONFIGURATION = oceandirect::api::networkConfiguration,
        FEATURE_ID_ETHERNET = oceandirect::api::ethernet,
        FEATURE_ID_SHUTTER = oceandirect::api::shutter,
        FEATURE_ID_HIGH_GAIN_MODE = oceandirect::api::highGainMode
    };
    }
#else
#include <stdint.h>
#include <stdbool.h>
 /* Redeclaration of the features enum with "friendlier" names for the public API.
  * Use this with isFeatureEnabled to determine if a spectrometer has a give feature.
  * Give it C linkage so it can be used by the C API.
 */
enum FeatureId {
    FEATURE_ID_SERIAL_NUMBER = serNo,
    FEATURE_ID_SPECTROMETER = spectrm,
    FEATURE_ID_THERMOELECTRIC = tec,
    FEATURE_ID_IRRADCAL = iirad,
    FEATURE_ID_EEPROM = eeprom,
    FEATURE_ID_STROBE_LAMP = strobe,
    FEATURE_ID_WAVECAL = wavecal,
    FEATURE_ID_NONLINEARITYCAL = nonline,
    FEATURE_ID_STRAYLIGHTCAL = stray,
    FEATURE_ID_RAW_BUS_ACCESS = raw,
    FEATURE_ID_CONTINUOUS_STROBE = contsrtb,
    FEATURE_ID_LIGHT_SOURCE = light,
    FEATURE_ID_TEMPERATURE = temper,
    FEATURE_ID_OPTICAL_BENCH = optic,
    FEATURE_ID_REVISION = revise,
    FEATURE_ID_DATA_BUFFER = buffer,
    FEATURE_ID_PIXEL_BINNING = binn,
    FEATURE_ID_GPIO = gpio,
    FEATURE_ID_SINGLE_STROBE = singlestrb,
    FEATURE_ID_QUERY_STATUS = status,
    FEATURE_ID_BACK_TO_BACK = backToBack,
    FEATURE_ID_LED_ACTIVITY = activity,
    FEATURE_ID_TIME_META = time,
    FEATURE_ID_DHCP = dhcp,
    FEATURE_ID_PIXEL = pixel,
    FEATURE_ID_AUTO_NULLING = autonulling,
    FEATURE_ID_IPV4_ADDRESS = ipv4address,
    FEATURE_ID_IPV4_USER_STRING = userstring,
    FEATURE_ID_DEVICE_INFORMATION = deviceInformation,
    FEATURE_ID_DEVICE_ALIAS = deviceAlias,
    FEATURE_ID_SERIAL_PORT = serialPort
};
#endif


#ifdef __cplusplus
 /*!
     @brief  This is an interface to OceanDirect that allows
             the user to connect to devices over USB and
             other buses.  This is intended as a usable and
             extensible API.

     @note   Detailed method documentation is available in
             the analogous C functions in OceanDirectAPI.h
 */

namespace oceandirect {

    namespace api {

        class DeviceAdapter;

        class DLL_DECL OceanDirectAPI {
        public:
            /**
             * No public constructor.  To use this class in C++,
             * you must first call getInstance().  This provides
             * a singleton: it is the same on every call.
             *
             * @param licenseStatus returns 0 on success i.e. there is a valid
             *             software license, 1 otherwise in which case Ocean should
             *             be contacted.
             */
            static OceanDirectAPI* getInstance();

            /**
             * No public destructor.  Call this to force memory cleanup.
             */
            static void shutdown();

            /**
            * Return the major, minor and point release version numbers.
            *
            * @param major the major software version number.
            * @param minor the minor software version number.
            * @param point the point software version number.
            */
            virtual void getAPIVersionNumber(unsigned int* major, unsigned int* minor, unsigned int* point);
            virtual void getAPIRCNumber(unsigned int* candidate);

            /**
            * Set the number of times to send multicast message for dynamic probing. This must be 
            * called before probing network devices.
            * @see detectNetworkDevices()
            * @param retryCount The number of times to send messages.
            */
            void setMulticastMsgSendRetry(size_t retryCount);

            /**
            * Set the number of times to read multicast message response. This must be called
            * before probing network devices.
            * @see detectNetworkDevices()
            * @param retryCount The number of times to try reading multicast response messages.
            */
            void setMulticastMsgResponseReadRetry(size_t retryCount);

            /**
            * Set the delay between reading multicast response. This must be called before 
            * probing network devices.
            * @see detectNetworkDevices()
            * @param delayMs The delay in milliseconds before next read.
            */
            void setMulticastMsgResponseReadDelay(size_t delayMs);

            /**
             * Use the probeDevices() method to force the driver to look for any device that can
             * be found automatically. If this is not called then such devices will not be available
             * for use. This should be used when attempting to find USB devices. Note that this 
             * should only be done by one thread at a time. For multithreaded application this 
             * function must be synchronized.
             * @see detectNetworkDevices()
             * @return the number of detected USB devices.
             */
            virtual int probeDevices();

            /**
             * Use the addRS232DeviceLocation() method to specify that a device may be
             * found on a particular serial bus with a given baud rate.  Once specified,
             * the typical openDevice() function can be used to access it.
             *
             * @param deviceTypeName a valid Ocean spectrometer device type.
             * @param deviceBusPath a valid serial port path that the device is connected to.
             * @param baud the baud rate for the specified serial port.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_CODE_INVALID_ARGUMENT if the device cannot be created.
             */
            virtual void addRS232DeviceLocation(char *deviceTypeName, char *deviceBusPath, unsigned int baud, int* errorCode);

            /**
             * This provides a way to find all Ethernet discoverable devices on a network.
             * Afterwards, a call to probeDevices is neccessary to grab the interface for opening
             * and connecting to discovered device. Note that this should only be done by one
             * thread at a time. For multithreaded application this function must be synchronized.
             * @see probeDevices()
             * @return the number of detected network devices.
            */
            virtual int detectNetworkDevices();

            /**
             * This provides the number of devices that have either been probed or
             * manually specified.  Devices are not opened automatically, but this can
             * provide a bound for getDeviceIDs(). Note that this should only be done 
             * by one thread at a time.
             *
             * @return the total number of devices, both specified and probed.
             */
            virtual int getNumberOfDeviceIDs();

            /**
             * This provides a unique ID of each device that is detected or specified.
             * The IDs are copied into the user-provided buffer.  These IDs are weak
             * references: attempting to access a device that no longer exists will cause
             * an error value to be returned but should not cause any instability.
             * The IDs may be entirely random, but a given ID will always refer to the
             * same device for as long as the program is running. Note that this should only 
             * be done by one thread at a time. For multithreaded application this function must be synchronized.
             *
             * @param ids the buffer to receive the device IDs.
             * @param maxLength the actual size of the buffer ids.
             * @return the number of device IDs actually copied into the array or 0 on error.
             */
            virtual int getDeviceIDs(long *ids, unsigned long maxLength);

            /**
             * This provides a unique ID of each network attached device that is detected or manually
             * specified. The IDs are copied into the user-provided buffer.  These IDs are weak
             * references: attempting to access a device that no longer exists will cause an error value
             * to be returned but should not cause any instability. The IDs may be entirely random, 
             * but a given ID will always refer to the same device for as long as the program is running.
             * Note that this should only be done by one thread at a time. For multithreaded application
             * this function must be synchronized.
             *
             * @param ids the buffer to receive the device IDs.
             * @param maxLength the actual size of the buffer ids.
             * @return the number of device IDs actually copied into the array or 0 on error.
             */
            virtual int getNetworkDeviceIDs(long* ids, unsigned long maxLength);


            /**
             * This will attempt to open the bus connection to the device with the given ID. After the device 
             * is closed the id becomes invalid. You need to call either probeDevices()/addNetworkDevice()/detectNetworkDevices() 
             * and getDeviceIDs() in order to have a valid id before reopening the device again. For a network
             * connected device this function may return an error code if the device is not yet ready to accept
             * incoming connection or the device is unreachable. Note that this should only be done by one 
             * thread at a time. For multithreaded application this function must be synchronized.
             * @see closeDevice()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_NO_DEVICE if the device does not exist;
             */
            virtual void openDevice(long deviceID, int *errorCode);

            /**
             * Manually create an instance of the network attached device and then open it using the 
             * openDevice() function. It is the responsiblitiy of the user to ensure that the device
             * exists and is configured properly. Note that this should only be done by one thread 
             * at a time. For multithreaded application this function must be synchronized.
             *
             * @param ipAddressStr The ip address as string (ex: "10.20.30.100" ) of the device to be opened.
             * @param deviceTypeStr The device type could be OceanFX or OceanHDX. This is case sensitive.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_NO_DEVICE if the device does not exist;
             * @return The device id or -1 if an error occured.
             */
            virtual int addNetworkDevice(const char* ipAddressStr, const char* deviceTypeStr, int* errorCode);

            /**
             * This will attempt to close the bus connection to the device with the given ID. The id 
             * becomes invalid after closing the device. Note that this should only be done by one 
             * thread at a time. For multithreaded application this function must be synchronized.
             * @see openDevice()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_NO_DEVICE if the device does not exist.
             */
            virtual void closeDevice(long deviceID, int *errorCode);

            /**
             * Get a string that describes the type of device
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_BAD_USER_BUFFER if the pointer to the buffer is null or the supplied buffer length is 0;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param buffer a character buffer to receive the device type string.
             * @param length the length of the supplied buffer.
             * @return the actual length of the device type string on success.
             */
            virtual int getDeviceType(long deviceID, int *errorCode, char *buffer, unsigned int length);


            /**
             * Get the device model name by passing in a pre-allocated buffer
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the feature is not available;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param buffer a character buffer to receive the device model string.
             * @param bufferLength the length of the supplied buffer.
             * @return the actual length of the device model string on success.
             */
            virtual int getDeviceModelText(long deviceID, int *errorCode, char *buffer, unsigned int bufferLength);

            /**
             * Get the usb endpoint address for a specified type of endpoint
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_INPUT_OUT_OF_BOUNDS if an invalid endpoint value is supplied;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param endpointType the USB endpoint type (see UsbEndpoint.h)
             * @return the endpoint address for the requested endpoint.
            */
            virtual unsigned char getDeviceEndpoint(long deviceID, int *error_code, usbEndpointType endpointType);

            /**
             * Advanced extension of the API. Access to the advanced APIs is
             * throught the pointer returned by this function.
             *
             * @return a pointer to access the advanced APIs.
            */
            virtual Advance* AdvancedControl();

            /**
             * Check if a specified feature is enabled for a device, return true if yes, false if not
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param featureId the feature ID of interest (declared elsewhere in OceanDirectAPI.h).
             * @return true if the specified feature is enabled, false otherwise.
             */
            virtual bool isFeatureEnabled(long deviceId, int *errorCode, FeatureId featureId);

            /**
             * Get the serial number of the device.
             * @see getSerialNumberMaximumLength
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the serial number feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param buffer the buffer to receive the returned serial number.
             * @param bufferLength the size of the supplied buffer.
             * @return the actual number of characters in the returned serial number.
             */
            virtual int getSerialNumber(long deviceID, int *errorCode, char *buffer, int bufferLength);

            /**
             * Return maximum length of the device serial number.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the serial number feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the maximum length of the serial number.
             */
            virtual unsigned char getSerialNumberMaximumLength(long deviceID, int *errorCode);

            /**
             * @deprecated Set nonlinearity correction on or off on raw spectrum
             * 
             * @see setStoredDarkSpectrum
             * @see getStoredDarkSpectrum
             * @see getNonlinearityCorrectedSpectrum
             * @see nonLinearityCorrectionUsage()
             * @warning if nonlinearity correction is enabled using this function then
             * some of the newer nonlinearity correction functionality e.g. getNonlinearityCorrectedSpectrum
             * may not be used.
             * 
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param value true if nonlinearity correction is to be used, false otherwise.
             */
            virtual void applyNonLinearityCorrection(long deviceID, int *errorCode, bool value);

            /**
             * @deprecated Determine if nonlinearity correction is on or off on raw spectrum
             * 
             * @see applyNonLinearityCorrection()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return true if nonlinearity correction is turned on, false otherwise.
             */
            virtual bool nonLinearityCorrectionUsage(long deviceID, int *errorCode);

            /**
             * @deprecated Use electric dark correction on the acquired spectra.
             * 
             * @see setStoredDarkSpectrum
             * @see getStoredDarkSpectrum
             * @see getDarkCorrectedSpectrum
             * @see electricDarkCorrectionUsage()
             * @warning if electric dark correction is enabled using this function then
             * some of the newer dark correction functionality e.g. getDarkCorrectedSpectrum
             * may not be used.
             *
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
             *                                   electric dark correction;
             *                  ERROR_NO_DEVICE if the device does not exist.
            */
            virtual void applyElectricDarkCorrection(long deviceID, int *errorCode, bool value);

            /** 
             * @deprecated Determine if electric dark correction to the acquired spectra is on or off.
             * @see applyElectricDarkCorrection()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
             *                                   electric dark correction;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return true if electric dark correction is turned on, false if electric dark correction
             *          is either turned off or is not supported (see the returned error code).
            */
            virtual bool electricDarkCorrectionUsage(long deviceID, int *errorCode);

            /**
             * Return the system time of the device. The time is returned as an integer
             * representing the number of microseconds since January 1 1970 based on
             * the current device system clock.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             */
            virtual long long int getTime(long deviceID, int *errorCode);

            /**
             * Sets the system time of the device. The time must be sepcified as the integer
             * number of microseconds since 1 January 1970.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param timeInMicrosecond the time to set the device system clock as the
             *           number of microseconds since 1 January 1970.
             */
            virtual void setTime(long deviceID, int *errorCode, long long int timeInMicrosecond);

            /* Spectrometer capabilities */

            /**
             * Get the wavelengths for each pixel of the specified device.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the wavelengths feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param wavelengths an array to receive the wavelength values.
             * @param length the actual length of the supplied wavelengths array.
             * @return the actual number of wavelengths copied into the wavelengths array.
             */
            virtual int getWavelengths(long deviceID, int *errorCode, double *wavelengths, int length);

            /**
             * Get the coefficients of the polynomial used to calculate the wavelengths.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the wavelengths feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param coeff an array to receive the coefficient values.
             * @param length the actual length of the supplied coefficients array.
             * @return the actual number of coefficients copied into the coefficients array.
            */
            virtual int getWavelengthCoefficients(long deviceID, int *errorCode, double *coeff, int length);


            /**
             * Set integration time in microseconds.
             * 
             * @note some devices that make use of onboard functionality to perform averaging have
             * a different, larger, minimum integration time for acquisition when averaging is enabled.
             * Refer to the documentation for your spectrometer to see if this is the case.
             * The minimum integration time when averaging is enabled can be determined
             * using getMinimumAveragingIntegrationTimeMicros.
             * @see getIntegrationTimeMicros()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_INPUT_OUT_OF_BOUNDS if an invalid integration time is supplied;
             *                  ERROR_INTEGRATION_TIME_BELOW_AVERAGING_MIN if averaging is enabled and the specified
             *                                             integration time is below the minimum required for averaging
             *                                             (see getMinimumAveragingIntegrationTimeMicros);
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param integrationTimeMicros the desired integration time in microseconds.
             */
            virtual void setIntegrationTimeMicros(long deviceID, int *errorCode, unsigned long integrationTimeMicros);

            /**
             * Get integration time in microseconds
             * @see setIntegrationTimeMicros()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_INPUT_OUT_OF_BOUNDS if an invalid integration time is supplied;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the integration time in microseconds.
             */
            virtual unsigned long getIntegrationTimeMicros(long deviceID, int *errorCode);

            /**
             * Get integration time increment in microseconds
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_INPUT_OUT_OF_BOUNDS if an invalid integration time is supplied;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the integration time increment in microseconds.
             */
            virtual unsigned long getIntegrationTimeIncrementMicros(long deviceID, int* errorCode);

            /**
             * Get minimum integration time in microseconds.
             * 
             * @note some devices that make use of onboard functionality to perform averaging have
             * a different, larger, minimum integration time for acquisition when averaging is enabled.
             * Refer to the documentation for your spectrometer to see if this is the case.
             * The minimum integration time when averaging is enabled can be determined
             * using getMinimumAveragingIntegrationTimeMicros.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the minimum integration time in microseconds for acquisition with no averaging.
             */
            virtual unsigned long getMinimumIntegrationTimeMicros(long deviceID, int *errorCode);

            /**
             * Get minimum integration time in microseconds when averaging is enabled.
             * 
             * @note some devices that make use of onboard functionality to perform averaging have
             * a different, larger, minimum integration time for acquisition when averaging is enabled.
             * Refer to the documentation for your spectrometer to see if this is the case.
             * The minimum integration time when averaging is not enabled can be determined
             * using getMinimumIntegrationTimeMicros.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the minimum integration time in microseconds with averaging enabled.
             */
            virtual unsigned long getMinimumAveragingIntegrationTimeMicros(long deviceID, int* errorCode);

            /**
             * Get maximum integration time in microseconds
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the maximum integration time in microseconds.
             */
            virtual unsigned long getMaximumIntegrationTimeMicros(long deviceID, int *errorCode);

            /**
             * Get max intensity (in raw counts) that can be returned in any pixel.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the maximum pixel intensity.
             */
            virtual double getMaximumIntensity(long deviceID, int *errorCode);

            /**
             *Get formatted spectrum length i.e. the number of pixels in the spectrum.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the size of the formatted spectrum.
             */
            virtual int getFormattedSpectrumLength(long deviceID, int *errorCode);

            /**
             * Get a formatted spectrum
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NOT_ENOUGH_BUFFER_SPACE if the size of the buffer is smaller than the formatted spectrum length;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param buffer the buffer that will receive the formatted spectrum.
             * @param bufferLength the actual size of the buffer.
             * @return the actual number of pixels copied into buffer.
             */
            virtual int getFormattedSpectrum(long deviceID, int *errorCode, double *buffer, int bufferLength);

            /**
             * Get raw spectrum with meta-data. Only OBP enabled devices supported this command.
             * The number of returned spectra depends on the following condition:
             * 1) Device supports data buffering:
             *      A) If buffering is enabled then the number of spectra returned depends on how many 
                       spectra are in the buffer. It can be 0.
             *      B) If buffering is disabled then command will block until the requested number of spectra is received.
             * 2) Device don't support data buffering:
             *      A) Only 1 spectra will be returned per call.
             * 
             * @see SpectrumWithMetadata.h
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_CODE_INVALID_ARGUMENT if the size of the buffer is less than 1 or greater than 15;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param buffer the buffer that will receive the formatted spectrum.
             * @param bufferLength the actual size of the buffer.
             * @return the actual number of spectra copied into buffer.
             */
            virtual int getRawSpectrumWithMetadata(long deviceID, int *errorCode, SpectrumWithMetadata *buffer, int bufferLength);

            /**
            * Store a dark spectrum for use in subsequent corrections i.e. dark correction and nonlinearity correction.
            * @see getStoredDarkSpectrum.
            * 
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_NO_DEVICE if the device does not exist.
            * @param darkSpectrum the buffer that contains the dark spectrum to be stored.
            * @param darkSpectrumLength the actual size of the dark spectrum buffer.
            */
            virtual void setStoredDarkSpectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength);

            /**
            * Retrieve a previously stored dark spectrum for use in subsequent corrections i.e. dark correction and nonlinearity correction.
            * @see setStoredDarkSpectrum.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found;
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_NO_DEVICE if the device does not exist.
            * @param darkSpectrum the buffer that contains the dark spectrum to be retrieved.
            * @param darkSpectrumLength the actual size of the dark buffer.
            * @return the size of the stored dark spectrum on success, zero otherwise.
            */
            virtual int getStoredDarkSpectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength);

            /**
            * Acquire a spectrum and use the supplied dark spectrum to perform a dark correction then return the dark corrected spectrum.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
            *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_TRANSFER_ERROR if a communication error occurred;
            *                  ERROR_NO_DEVICE if the device does not exist.
            * @param darkSpectrum the buffer that contains the dark spectrum to be used for the dark correction.
            * @param darkSpectrumLength the actual size of the dark spectrum buffer.
            * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
            * @param darkCorrectedSpectrumLength the actual size of the dark correction buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int getDarkCorrectedSpectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

            /**
            * Dark correct a previously acquired illuminated spectrum using a stored dark spectrum.
            * @see setStoredDarkSpectrum
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found.
            * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
            * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
            * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
            * @param darkCorrectedSpectrumLength the actual size of the dark corrected buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int darkCorrectSpectrum(long deviceID, int* errorCode, double* illuminatedSpectrum, int illuminatedSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

            /**
            * Acquire a spectrum and use the previously stored dark spectrum to perform a dark correction then return the dark corrected spectrum.
            * @see setStoredDarkSpectrum.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
            *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
            *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found.
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_TRANSFER_ERROR if a communication error occurred;
            *                  ERROR_NO_DEVICE if the device does not exist.
            * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
            * @param darkCorrectedSpectrumLength the actual size of the dark correction buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int getDarkCorrectedSpectrum(long deviceID, int* errorCode, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

            /**
            * Dark correct a previously acquired illuminated spectrum using a previously acquired dark spectrum.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            * @param darkSpectrum the buffer that contains the dark spectrum to be used for the dark correction.
            * @param darkSpectrumLength the actual size of the dark spectrum buffer.
            * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
            * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
            * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
            * @param darkCorrectedSpectrumLength the actual size of the dark corrected buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int darkCorrectSpectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

            /**
            * Acquire a spectrum and use the supplied dark spectrum to perform a dark correction
            * followed by the nonlinearity correction then return the nonlinearity corrected spectrum.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
            *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_TRANSFER_ERROR if a communication error occurred;
            *                  ERROR_NO_DEVICE if the device does not exist.
            * @param darkSpectrum the buffer that contains the dark spectrum to be used for the dark correction.
            * @param darkSpectrumLength the actual size of the dark spectrum buffer.
            * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
            * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity correction buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int getNonlinearityCorrectedSpectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);

            /**
            * Nonlinearity correct a previously acquired illuminated spectrum using a stored dark spectrum.
            * This function performs a dark correction using a previously stored dark spectrum prior to performing
            * the nonlinearity correction.
            * @see setStoredDarkSpectrum
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found.
            * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
            * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
            * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
            * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity corrected buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int nonlinearityCorrectSpectrum(long deviceID, int* errorCode, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);

            /**
            * Acquire a spectrum and use the previously stored dark spectrum to perform a dark correction
            * followed by a nonlinearity correction then return the nonlinearity corrected spectrum.
            * @see setStoredDarkSpectrum.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
            *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
            *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found;
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_TRANSFER_ERROR if a communication error occurred;
            *                  ERROR_NO_DEVICE if the device does not exist.
            * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
            * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity correction buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int getNonlinearityCorrectedSpectrum(long deviceID, int* errorCode, double* nonlinearityCorrectedSpectrum,
                int nonlinearityCorrectedSpectrumLength);

            /**
            * Nonlinearity correct a previously acquired illuminated spectrum after
            * dark correction using a previously acquired dark spectrum.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            * @param darkSpectrum the buffer that contains the dark spectrum to be used prior to the nonlinearity correction.
            * @param darkSpectrumLength the actual size of the dark spectrum buffer.
            * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
            * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
            * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
            * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity corrected buffer.
            * @return the size of the returned corrected spectrum on success, zero otherwise.
            */
            virtual int nonlinearityCorrectSpectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);

            /**
            * Apply a boxcar correction on the given illuminated spectrum.
            *
            * @param[in]  deviceID  The identifier of the device as returned by getDeviceIDs.
            * @param[out] errorCode Set to 0 if successful, an OceanDirect error code (nonzero) otherwise
            *                       ERROR_VALUE_NOT_FOUND no stored dark spectrum was found;
            *                       ERROR_NO_DEVICE if deviceID is not a valid and open deviceID
            *                       ERROR_TRANSFER_ERROR if a communication error occurred
            *                       ERROR_FEATURE_NOT_FOUND if device does not support this feature
            *                       ERROR_COMMAND_NOT_SUPPORTED if device does not support this command.
            * @param[in/out] illuminatedSpectrum The spectrum that will be boxcar corrected.
            * @param[in] boxcarWidth The boxcar width.
            */
            void boxcarCorrectSpectrum(long deviceID, int* errorCode, const double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength,
                                       unsigned int boxcarWidth, double* boxcarCorrectedSpectrum, unsigned int boxcarCorrectedSpectrumLength);

            /**
             * Get the number of spectra to be averaged per returned spectrum.
             * When this value has been set greater than 1 the specified number of spectra are averaged and the
             * resulting average is returned by getFormattedSpectrum (or getRawSpectrumWithMetadata).
             * @see setScansToAverage()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the number of spectra to be averaged per returned spectrum.
             */
            virtual unsigned int getScansToAverage(long deviceID, int* errorCode);

            /**
             * Set the number of spectra to be averaged per returned spectrum.
             * When this value is set greater than 1 the specified number of spectra are averaged and the
             * resulting average is returned by getFormattedSpectrum (or getRawSpectrumWithMetadata).
             * NOTE: Some devices have a minimum integration time for averaging that is different to
             * the minimum integration time for unaveraged acquisition (see your spectrometer documentation
             * to determine if this is a requirement).
             * @see getScansToAverage()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_INTEGRATION_TIME_BELOW_AVERAGING_MIN if the current integration time is
             *                                         below the minimum required for averaging
             *                                         it will not be possible to enable averaging
             *                                             (see getMinimumAveragingIntegrationTimeMicros);
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param scansToAverage the number of scans to be averaged
             */
            virtual void setScansToAverage(long deviceID, int* errorCode, unsigned int scansToAverage);

            /**
             * Get the width of the boxcar smoothing to be applied to the returned spectrum.
             * When this value has been set greater than 0, boxcar smoothing (a moving average) is
             * applied to the spectrum returned by getFormattedSpectrum (or getRawSpectrumWithMetadata).
             * The width specified is the number of pixels either side of the central pixel of the average
             * i.e. if the result of this function is n, the "full width" of the smoothing is 2*n+1.
             * @see setBoxcarWidth()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the width of the smoothing to be applied per returned spectrum.
             */
            virtual unsigned short int getBoxcarWidth(long deviceID, int* errorCode);

            /**
             * Set the width of the boxcar smoothing to be applied to the returned spectrum.
             * When this value is set greater than 0, boxcar smoothing (a moving average) is
             * applied to the spectrum returned by getFormattedSpectrum (or getRawSpectrumWithMetadata).
             * The width specified is the number of pixels either side of the central pixel of the average
             * i.e. if the result of this function is n, the "full width" of the smoothing is 2*n+1.
             * 
             * Setting this value to 0 turns off the boxcar smoothing.
             * @see getBoxcarWidth()
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
             *                  ERROR_TRANSFER_ERROR if a communication error occurred;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param boxcarWidth the width of the smoothing to be applied, or zero if smoothing is to be turned off.
             */
            virtual void setBoxcarWidth(long deviceID, int* errorCode, unsigned short int boxcarWidth);

            /**
            * Set the spectrometer trigger mode. Please see your spectrometer documentation for valid values
            * of the trigger mode.
            * @see getTriggerMode()
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
            *                  ERROR_TRANSFER_ERROR if a communication error occurred;
            *                  ERROR_CODE_INVALID_ARGUMENT if the mode supplied is not valid;
            *                  ERROR_NO_DEVICE if the device does not exist.
            * @param mode the trigger mode to apply.
            */
            virtual void setTriggerMode(long deviceID, int *errorCode, int mode);

            /**
            * Get the spectrometer trigger mode. Please see your spectrometer documentation for valid values
            * of the trigger mode.
            * @see setTriggerMode()
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
            *                  ERROR_TRANSFER_ERROR if a communication error occurred;
            *                  ERROR_CODE_INVALID_ARGUMENT if the mode supplied is not valid;
            *                  ERROR_NO_DEVICE if the device does not exist
            *                  ERROR_COMMAND_NOT_SUPPORTED device don't support this command.
            * @return the current trigger mode being used by the device.
            */
            virtual int getTriggerMode(long deviceID, int *errorCode);

            /**
            * Set the acquisition delay to the specified number of microseconds.
            * @see getAcquisitionDelayMicroseconds()
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                          ERROR_SUCCESS on success;
            *                          ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                          ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
            *                          ERROR_TRANSFER_ERROR if a communication error occurred;
            *                          ERROR_CODE_INVALID_ARGUMENT if the period supplied is not valid;
            *                          ERROR_NO_DEVICE if the device does not exist
            * @param delayMicroseconds the acquisition delay period in microseconds.
            */
            virtual void setAcquisitionDelayMicroseconds(long deviceID, int* errorCode, unsigned long delayMicroseconds);

            /**
            * Get the acquisition delay period in microseconds.
            * @see setAcquisitionDelayMicroseconds()
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                          ERROR_SUCCESS on success;
            *                          ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                          ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
            *                          ERROR_TRANSFER_ERROR if a communication error occurred;
            *                          ERROR_NO_DEVICE if the device does not exist.
            * @return the acquisition delay period in microseconds.
            */
            virtual unsigned long getAcquisitionDelayMicroseconds(long deviceID, int* errorCode);

            /**
            * Get the acquisition delay period increment in microseconds.
            * The increment is the minimum difference (in microseconds) between two adjacent, valid
            * acquisition delay periods.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                          ERROR_SUCCESS on success;
            *                          ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                          ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
            *                          ERROR_TRANSFER_ERROR if a communication error occurred;
            *                          ERROR_NO_DEVICE if the device does not exist.
            * @return the acquisition delay period increment in microseconds.
            */
            virtual unsigned long getAcquisitionDelayIncrementMicroseconds(long deviceID, int* errorCode);

            /**
            * Get the maximum valid acquisition delay period in microseconds.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                          ERROR_SUCCESS on success;
            *                          ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                          ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
            *                          ERROR_TRANSFER_ERROR if a communication error occurred;
            *                          ERROR_NO_DEVICE if the device does not exist.
            * @return the maximum acquisition delay period in microseconds.
            */
            virtual unsigned long getAcquisitionDelayMaximumMicroseconds(long deviceID, int* errorCode);

            /**
            * Get the minimum valid acquisition delay period in microseconds.
            *
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                          ERROR_SUCCESS on success;
            *                          ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
            *                          ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
            *                          ERROR_TRANSFER_ERROR if a communication error occurred;
            *                          ERROR_NO_DEVICE if the device does not exist.
            * @return the minimum acquisition delay period in microseconds.
            */
            virtual unsigned long getAcquisitionDelayMinimumMicroseconds(long deviceID, int* errorCode);

            /**
             * Get electric dark pixel count
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
             *                                   electric dark correction;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @return the number of electric dark pixels or zero if the electric dark correction is not supported (see the
             *           returned error code).
             */
            virtual int getElectricDarkPixelCount(long deviceID, int *errorCode);

            /**
             * Get electric dark pixel indices.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
             *                                   electric dark correction;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param indices the buffer that will receive the indices of the electric dark pixels.
             * @param length the actual size of the buffer.
             * @return the number of electric dark pixels copied into the buffer or zero if the electric
             *          dark correction is not supported (see the returned error code).
             */
            virtual int getElectricDarkPixelIndices(long deviceID, int *errorCode, int *indices, int length);

            /**
             * Get wavelength indices within a specified wavelength range
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_CODE_ARRAY_INDEX_OUT_OF_BOUNDS the lower or upper bound specified is not within the device's wavelength range;  
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param indices The output buffer that will receive the indices of the pixels in the specified range.
             * @param indicesLength The indices buffer size.
             * @param wavelength The output buffer that will receive the wavelengths associated with each pixel index.
             * @param wavelengthLength The wavelength buffer size.
             * @param lo the lower bound of the wavelength range.
             * @param hi the upper bound of the wavelength range.
             * @return the number of pixel indices copied into the buffer.
             */
            virtual int getIndicesAtWavelengthRange(long deviceID, int *errorCode, int *indices, int indicesLength, double *wavelengthLength, int wavelengthSize,
                                            double lo, double hi);

            /**
             * Get the indices and actual wavelengths of a specified set of wavelengths.
             * 
             * @note if any of the specified wavelengths are out of bounds then the wavelengths
             * array may be partially overwritten with the actual wavelengths found up to the point when
             * the error occurred.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_CODE_ARRAY_INDEX_OUT_OF_BOUNDS one or more of the specified wavelengths is not within the device's wavelength range;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param indices The buffer that will receive the indices of the pixels associated with the specified wavelengths.
             * @param indicesLength The indices buffer size.
             * @param wavelength The wavelengths to be searched for, overwritten with the actual wavelengths found.
             * @param wavelengthLength The wavelength buffer size.
             * @param length the actual length of the array of wavelengths to be searched for.
             * @return the number of pixel indices copied into the buffer.
             */
            virtual int getIndicesAtAnyWavelength(long deviceID, int *errorCode, int *indices, int indicesLength, double *wavelength, int wavelengthLength);

            /**
             * Get wavelength closest to the specified approximate wavelength.
             *
             * @param deviceID the identifier of the device as returned by getDeviceIDs.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_CODE_ARRAY_INDEX_OUT_OF_BOUNDS the specified wavelengths is not within the device's wavelength range;
             *                  ERROR_NO_DEVICE if the device does not exist.
             * @param wavelength the wavelength of the pixel nearest to the approximate wavelength within the device's wavelength range.
             * @param approxWavelength the approximate wavelength of the desired pixel to be found.
             * @return the index of the pixel closest to the approximate wavelength on success, -1 otherwise.
             */
            virtual int getIndexAtWavelength(long deviceID, int *errorCode, double &wavelength, double approxWavelength);

            virtual IDevice *getDeviceByID(long id);


            /**
             * Get error message associated with the given error code. If the error code is incorrect then
             * the return message will be "Error. Undefined error".
             *
             * @param errorCode The error code.
             * @param returnMessage The output buffer.
             * @param length Output buffer length
             * @return The number of characters copied into the output buffer.
             */
            virtual int getErrorMessage(int errorCode, char* returnMessage, int length);

            /**
             * Get error message length associated with the given error code. If the error code is incorrect then
             * the return message length will be 0.
             *
             * @param errorCode The error code.
             * @return The number of characters copied into the output buffer.
             */
            virtual int getErrorStringLength(int errorCode);

            virtual ~OceanDirectAPI();

            friend class OceanDirectAdminAPI;
            friend class NetOceanDirectAdmin;
        private:
            static constexpr int OBP1_TCP_IP_PORT = 57357;
            static constexpr int OBP2_TCP_IP_PORT = 57350;
            friend class InstrumentedOceanDirectAPI;
        protected:

            /**
             * Get the device Model name
             */
            virtual std::string getDeviceModel(long deviceID, int* errorCode, int index);

            /**
             * Use the addIPv4DeviceLocation() method to specify that a device may be
             * found on a TCP/IPv4 network on a given port.  Once specified,
             * the typical openDevice() function can be used to access it.
             *
             * @param deviceTypeName a valid Ocean spectrometer device type.
             * @param ipAddr a valid IP address.
             * @param port a valid TCP/UDP port.
             * @param errorCode a code indicating the result of the operation:
             *                  ERROR_SUCCESS on success;
             *                  ERROR_CODE_INVALID_ARGUMENT if the device cannot be created.
             */
            virtual long addTCPIPv4DeviceLocation(const char *deviceTypeName, std::string ipAddr, int port, int* errorCode);

            virtual long addTCPIPv4OBP2DeviceLocation(const char* deviceTypeName, std::string ipAddr,
                int port, int* errorCode);

            OceanDirectAPI();

            static OceanDirectAPI* instance;

            //std::vector<IDevice*> probedDevices;
            //std::vector<IDevice*> specifiedDevices;

        private:
            // private log file and methods for the instrumentation
            static std::shared_ptr<std::ofstream> logFile;
            static OceanDirectAPI* getInstance(const char* log);
            static void shutdownInstrumentation();
            int probeInstrumentedDevices();

            static constexpr int TCP_IP_PORT = 57357;
            static size_t multicastMsgSendRetry;
            static size_t multicastMsgResponseReadRetry;
            static size_t multicastMsgResponseReadDelay;
        };
    }
}

extern "C" {
#endif /* __cplusplus */
#if 1
    /* All of these C functions start with odapi_ to prevent namespace
     * collisions.
     */

     /**
      * This should be called prior to any other odapi_call.  The API may
      * recover gracefully if this is not called, but future releases may assume
      * this is called first.  This should be called synchronously -- a single
      * thread should call this.
      */

    DLL_DECL void odapi_initialize();

    /**
     * This may be called to free up any allocated memory being held by the
     * driver interface.  After this is called by any thread, odapi_initialize
     * should be called again before any other odapi_ functions are used.
     */
    DLL_DECL void odapi_shutdown();

    /**
     * @deprecated Returns the OceanDirect SDK version number
     * 
     * @see odapi_get_api_version_numbers
     *
     * @return double version number
    */
    DLL_DECL double odapi_get_api_version();

    /**
     * Returns the OceanDirect SDK version numbers (major.minor.point)
     *
     * @param major the major software version number.
     * @param minor the minor software version number.
     * @param point the point software version number.
     *
    */
    DLL_DECL void odapi_get_api_version_numbers(unsigned int* major, unsigned int* minor, unsigned int* point);
    DLL_DECL void odapi_get_rc_version_number(unsigned int* candidate);

    /**
    * Set the number of times to send multicast message for dynamic probing. This must be called 
    * before probing network devices.
    * @see odapi_detect_network_devices()
    * @param retryCount The number of times to send messages.
    */
    DLL_DECL void odapi_set_multicast_msg_send_retry(unsigned int retryCount);

    /**
    * Set the number of times to read multicast message response. This must be called before 
    * probing network devices.
    * before probing network devices.
    * @see odapi_detect_network_devices()
    * @param retryCount The number of times to try reading multicast response messages.
    */
    DLL_DECL void odapi_set_multicast_msg_response_read_retry(unsigned int retryCount);

    /**
    * Set the delay between reading multicast response. This must be called before
    * probing network devices.
    * @see odapi_detect_network_devices()
    * @param delayMs The delay in milliseconds before next read.
    */
    DLL_DECL void odapi_set_multicast_msg_response_read_delay(unsigned int delayMs);


    /**
     * This specifies to the driver that a device of the given type might be
     * found on a particular RS232 bus (e.g. a COM port).  The driver will add
     * the device type and location to the set of those that can be opened.
     *
     * @param deviceTypeName The name of a type of device.  This can be
     *      one of the following: QE-PRO, STS.
     *
     * @param deviceBusPath The location of the device on the RS232 bus.
     *      This will be a platform-specific location.  Under Windows, this may
     *      be COM1, COM2, etc.  Under Linux, this might be /dev/ttyS0, /dev/ttyS1,
     *      etc.
     *
     * @param baud Baud rate at which to open the device.  This should
     *      be specified as the rate itself, e.g. 9600, 57600, or 115200.
     * @param errorCode a code indicating the result of the operation:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_CODE_INVALID_ARGUMENT if the device cannot be created.
     */
    DLL_DECL void
        odapi_add_RS232_device_location(char *deviceTypeName, char *deviceBusPath,
            unsigned int baud, int* errorCode);

    /**
     * This causes a search for known devices on all buses that support
     * autodetection.  This does NOT automatically open any device -- that must
     * still be done with the odapi_open_device() function.  Note that this
     * should only be done by one thread at a time, and it is recommended that
     * other threads avoid calling odapi_get_number_of_device_ids() or
     * odapi_get_device_ids() while this is executing.  Ideally, a single thread
     * should be designated for all device discovery/get actions, and
     * separate worker threads can be used for each device discovered.
     *
     * @return the total number of devices that have been found
     *      automatically.  If called repeatedly, this will always return the
     *      number of devices most recently found, even if they have been
     *      found or opened previously.
     */
    DLL_DECL int
        odapi_probe_devices();

    /**
     * This returns the total number of devices that are known either because
     * they have been specified with odapi_add_RS232_device_location or
     * because they were probed on some bus. This can be used to bound the
     * number of device references that can be gotten with
     * odapi_get_device_ids(). Note that this should only be done by one thread at a time.
     *
     * @return the total number of devices references that are available
     *      through odapi_get_device_ids().
     */
    DLL_DECL int
        odapi_get_number_of_device_ids();

    /**
     * This will populate the provided buffer with up to max_ids of device
     * references. These references must be used as the first parameter to
     * most of the other odapi_ calls.  Each uniquely identifies a single
     * device instance. Note that this should only be done by one thread at a time.
     * For multithreaded application this function must be synchronized.
     *
     * @param ids an array of long integers that will be overwritten
     *           with the unique IDs of each known device.  Note that these
     *           devices will not be open by default.
     * @param max_ids the maximum number of IDs that may be written
     *           to the array
     *
     * @return The total number of device IDs that were written to the array.
     *      This may be zero on error.
     */
    DLL_DECL int
        odapi_get_device_ids(long *ids, unsigned int max_ids);

    /**
     * This will populate the provided buffer with up to max_ids of network device
     * references.  These references must be used as the first parameter to
     * most of the other odapi_ calls.  Each uniquely identifies a single
     * device instance. Note that this should only be done by one thread at a time.
     * For multithreaded application this function must be synchronized.
     *
     * @param ids an array of long integers that will be overwritten
     *           with the unique IDs of each known device.  Note that these
     *           devices will not be open by default.
     * @param max_ids the maximum number of IDs that may be written
     *           to the array
     *
     * @return The total number of device IDs that were written to the array.
     *      This may be zero on error.
     */
    DLL_DECL int
        odapi_get_network_device_ids(long* ids, unsigned int max_ids);

    /**
     * Get the number of network connected devices. Note that this should only be done by one 
     * thread at a time. For multithreaded application this function must be synchronized.
     * 
     * @return the number of network detected devices connected.
     */
    DLL_DECL int odapi_detect_network_devices();

    /**
     * This function opens a device attached to the system.  The device must
     * be provided as a location ID from the odapi_get_device_ids()
     * function. Such locations can either be specified or probed using the
     * other methods in this interface. After the device is closed the id becomes invalid. You need to 
     * call either odapi_probe_devices()/odapi_add_network_devices()/odapi_detect_network_devices() and
     * odapi_get_device_ids() in order to have a valid id before reopening the device again. For a network
     * connected device this function may return an error code if the device is not yet ready to accept
     * incoming connection or the device is unreachable. Note that this should only be done by one
     * thread at a time. For multithreaded application this function must be synchronized.
     *
     * @param id The location ID of a device to try to open.  Only IDs
     *      that have been returned by a previous call to oceandirect_get_device_ids()
     *      are valid.
     * @param error_code A pointer to an integer that can be used for
     *      storing error codes:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     */
    DLL_DECL void
        odapi_open_device(long id, int *error_code);

    /**
     * Manually create an instance of the network attached device and then open it 
     * using the openDevice() function. It is the responsibility of the user to ensure
     * that the device exist and configured properly. Note that this should only be 
     * done by one thread at a time. For multithreaded application this function 
     * must be synchronized.
     *
     * @param ipAddressStr The ip address as string (ex: "10.20.30.100" ) of the device to be opened.
     * @param deviceTypeStr The device type could be OceanFX or OceanHDX. This is case sensitive.
     * @param errorCode a code indicating the result of the operation:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist;
     * @return The device id or -1 if an error occured.
     */
    DLL_DECL long
        odapi_add_network_devices(const char* ipAddressStr, const char* deviceTypeStr, int* error_code);

    /**
     * This function closes the spectrometer attached to the system. The id becomes 
     * invalid after closing the device. Note that this should only be done by one 
     * thread at a time. For multithreaded application this function must be synchronized.
     *
     * @param id (Input) The location ID of a device previously opened with odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     */
    DLL_DECL void
        odapi_close_device(long id, int *error_code);

    /**
     * This function returns a description of the error denoted by
     * error_code.
     *
     * @param error_code (Input) The integer error code to look up.  Error codes
     *      may not be zero, but can be any non-zero integer (positive or
     *      negative).
     *
     * @return char *: A description in the form of a string that describes
     *      what the error was or "Undefined error" if the error code is not known.
     */
    DLL_DECL int
        odapi_get_error_string(int error_code, char* error_string, int length);
    /**
    * Get the length of the error string associated with the specified error code.
    * 
    * @param error_code the error code used to determine the length of the error string.
    * @return the length of the error string associated with the specified error code if
    *         the error code is a known error code, otherwise the length of the "unknown"
    *         error code string.
    */
    DLL_DECL int
        odapi_get_error_string_length(int error_code);

    /**
     * This function copies a string denoting the type of the device into the
     * provided buffer.
     *
     * @param id (Input) The location ID of a device previously opened with
     *      odapi_get_device_locations().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes.  This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_BAD_USER_BUFFER if the pointer to the buffer is null or the supplied buffer length is 0;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @param buffer (Output) Pointer to a user buffer that the name will be
     *      stored into.
     *
     * @param length (Input) Maximum number of bytes that may be written to the
     *      buffer
     *
     * @return integral number of bytes actually written to the user buffer
     */
    DLL_DECL int
        odapi_get_device_type(long id, int *error_code,
            char *buffer, unsigned int length);

    /**
     * This function determines the correct spectrometer model name assigned.
     * It is not based on VID or PID of device.
     *
     * @param id (Input) The location ID of a device previously opened with
     *      odapi_get_device_locations().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes.  This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     * @param buffer (Output) Pointer to a user buffer that the name will be
     *      stored into.
     * @param length (Input) Maximum number of bytes that may be written to the
     *      buffer
     *
     * @return integral number of bytes actually written to the user buffer
     */
    DLL_DECL int
        odapi_get_device_name(long id, int *error_code,
            char *buffer, unsigned int length);

    /**
     * This function returns the usb endpoint for the primary output.
     * If the type is not supported by the device, a zero is returned.
     * 0 is normally the control endpoint. That value is not valid in this context.
     *
     * @param deviceID (Input)  The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return the usb endpoint address of the primary output endpoint.
     */
    DLL_DECL unsigned char
        odapi_get_device_usb_endpoint_primary_out(long id, int *error_code);

    /**
     * This function returns the usb endpoint for the primary input.
     * If the type is not supported by the device, a zero is returned.
     * 0 is normally the control endpoint. That value is not valid in this context.
     *
     * @param deviceID (Input)  The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return the usb endpoint address of the primary input endpoint.
     */
    DLL_DECL unsigned char
        odapi_get_device_usb_endpoint_primary_in(long id, int *error_code);

    /**
     * This function returns the usb endpoint for the secondary output.
     * If the type is not supported by the device, a zero is returned.
     * 0 is normally the control endpoint. That value is not valid in this context.
     *
     * @param deviceID (Input)  The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return the usb endpoint address of the secondary output endpoint.
     */
    DLL_DECL unsigned char
        odapi_get_device_usb_endpoint_secondary_out(long id, int *error_code);

    /**
     * This function returns the usb endpoint for the type secondary input.
     * If the type is not supported by the device, a zero is returned.
     * 0 is normally the control endpoint. That value is not valid in this context.
     *
     * @param deviceID (Input)  The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return the usb endpoint address of the secondary input endpoint.
     */
    DLL_DECL unsigned char
        odapi_get_device_usb_endpoint_secondary_in(long id, int *error_code);

    /**
     * This function returns the usb endpoint for the secondary input.
     * If the type is not supported by the device, a zero is returned.
     * 0 is normally the control endpoint. That value is not valid in this context.
     *
     * @param deviceID (Input)  The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return the usb endpoint address of ths secondary input.
     */
    DLL_DECL unsigned char
        odapi_get_device_usb_endpoint_secondary_in2(long id, int *error_code);

    /**
     * This function checks if a feature is enabled for a specified device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param featureID (Input) One of the feature enum constants.
     *
     * @return true if the feature is enabled for the specified device, false otherwise.
     */
    DLL_DECL bool
        odapi_is_feature_enabled(long deviceID, int *errorCode, enum FeatureId featureID);

    /**
    * This reads the device's serial number and fills the
    * provided array (up to the given length) with it.
    *
    * @param deviceID (Input) The index of a device previously opened with
    *      odapi_open_device().
    * @param error_code (Output) pointer to an integer that can be used for
    *      storing error codes. This may be NULL in which case no error code is returned.
    *      The error codes returned by this function are:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
    *                  ERROR_TRANSFER_ERROR if a communication error occurred;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param buffer (Output)  A pre-allocated array of characters that the
    *      serial number will be copied into
    * @param buffer_length (Input) The number of values to copy into the buffer
    *      (this should be no larger than the number of chars allocated in
    *      the buffer)
    *
    * @return the number of bytes written into the buffer
    */
    DLL_DECL int
        odapi_get_serial_number(long deviceID, int *error_code, char *buffer, int buffer_length);

    /**
     * This reads the possible maximum length of the device's serial number
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the length of the serial number in an unsigned character byte
     */
    DLL_DECL unsigned char
        odapi_get_serial_number_maximum_length(long deviceID, int *error_code);

    /**
     * This reads the current system time from the device. Currently only FX device supports this.
     * The time is returned as an integer
     * representing the number of microseconds since January 1 1970 based on
     * the current device system clock.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the time since 1 January 1970 in microseconds.
     */
    DLL_DECL long long int
        odapi_get_time(long deviceID, int *error_code);

    /**
     * This sets a new time to the device. Currently only FX device supports this.
     *  The time must be sepcified as the integer number of microseconds since 1 January 1970.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param time_in_microsecond (input) a time since 1 January 1970 in microseconds.
     */
    DLL_DECL void
        odapi_set_time(long deviceID, int *error_code, long long int time_in_microsecond);

    /**
     * @deprecated This function sets the nonlinearity correction mode for the specified device.
     * Note that requesting an unsupported mode will result in an error.
     * @see odapi_set_stored_dark_spectrum
     * @see odapi_get_stored_dark_spectrum
     * @see odapi_get_nonlinearity_corrected_spectrum1
     * @see odapi_get_nonlinearity_corrected_spectrum2
     * 
     *
     * @warning if nonlinearity correction is enabled using this function then
     * some of the newer nonlinearity correction functionality e.g. odapi_get_nonlinearity_corrected_spectrum1
     * may not be used.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param mode (Input) a bool value of true to use or false to not use.
     */
    DLL_DECL void odapi_apply_nonlinearity_correct_usage(long deviceID, int *error_code, bool use);

    /**
     * @deprecated This function returns the usage state of nonlinearity correction.
     * @see odapi_set_stored_dark_spectrum
     * @see odapi_get_stored_dark_spectrum
     * @see odapi_get_nonlinearity_corrected_spectrum1
     * @see odapi_get_nonlinearity_corrected_spectrum2
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used
     *      for storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return Returns usage state true/false.
     */
    DLL_DECL bool odapi_get_nonlinearity_correct_usage(long deviceID, int *error_code);

    /**
     * @deprecated this function has now been replaced by odapi_set_trigger_mode.
     *
     * This function sets the trigger mode for the specified device.
     * Note that requesting an unsupported mode will result in an error.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param mode (Input) a trigger mode (0 = normal, 1 = software,
     *      2 = synchronization, 3 = external hardware, etc - check your
     *      particular spectrometer's Data Sheet)
     */
    DLL_DECL void
        odapi_adv_set_trigger_mode(long deviceID, int *error_code, int mode);

    /**
     * @deprecated this function has now been replaced by odapi_get_trigger_mode.
     * This function gets the trigger mode for the specified device.
     * Note that requesting an unsupported mode will result in an error.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param mode (Input) a trigger mode (0 = normal, 1 = software,
     *      2 = synchronization, 3 = external hardware, etc - check your
     *      particular spectrometer's Data Sheet)
     */
    DLL_DECL int
        odapi_adv_get_trigger_mode(long deviceID, int *error_code);

    /**
     * This function sets the trigger mode for the specified device.
     * Note that requesting an unsupported mode will result in an error.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param mode (Input) a trigger mode (0 = normal, 1 = software,
     *      2 = synchronization, 3 = external hardware, etc - check your
     *      particular spectrometer's Data Sheet)
     */
    DLL_DECL void
        odapi_set_trigger_mode(long deviceID, int *error_code, int mode);

    /**
     * This function gets the trigger mode for the specified device.
     * Note that requesting an unsupported mode will result in an error.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *                  ERROR_NO_DEVICE if the device does not exist.
     *                  ERROR_COMMAND_NOT_SUPPORTED device don't support this command.
     * @return the trigger mode (0 = normal, 1 = software,
     *      2 = synchronization, 3 = external hardware, etc - check your
     *      particular spectrometer's Data Sheet)
     */
    DLL_DECL int
        odapi_get_trigger_mode(long deviceID, int *error_code);

    /**
     * Set the acquisition delay in microseconds.  This may also be referred to as the
     * trigger delay.  In any event, it is the time between some event (such as a request
     * for data, or an external trigger pulse) and when data acquisition begins.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param delay_usec (Input) The new delay to use in microseconds
     */
    DLL_DECL void odapi_set_acquisition_delay_microseconds(long deviceID, int* errorCode, unsigned long delay_usec);

    /**
     * Get the acquisition delay in microseconds.  This may also be referred to as the
     * trigger delay.  In any event, it is the time between some event (such as a request
     * for data, or an external trigger pulse) and when data acquisition begins.
     *
     * Note that not all devices support reading this value back.  In these cases, the
     * returned value will be the last value sent to odapi_adv_set_acquisition_delay_microseconds().
     * If no value has been set and the value cannot be read back, this function will
     * indicate an error.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_COMMAND_NOT_SUPPORTED if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The acquisition delay in microseconds
     */
    DLL_DECL unsigned long odapi_get_acquisition_delay_microseconds(long deviceID, int* errorCode);

    /**
     * Get the allowed step size for the acquisition delay in microseconds.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The acquisition delay step size in microseconds
     */
    DLL_DECL unsigned long odapi_get_acquisition_delay_increment_microseconds(long deviceID, int* errorCode);

    /**
     * Get the maximum allowed acquisition delay in microseconds.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The maximum acquisition delay in microseconds
     */
    DLL_DECL unsigned long odapi_get_acquisition_delay_maximum_microseconds(long deviceID, int* errorCode);

    /**
     * Get the minimum allowed acquisition delay in microseconds.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The minimum acquisition delay in microseconds
     */
    DLL_DECL unsigned long odapi_get_acquisition_delay_minimum_microseconds(long deviceID, int* errorCode);

    /**
     * This function sets the integration time for the specified device.
     * This function should not be responsible for performing stability
     * scans.
     * NOTE: some devices that make use of onboard functionality to perform averaging have
     * a different, larger, minimum integration time for acquisition when averaging is enabled.
     * Refer to the documentation for your spectrometer to see if this is the case.
     * The minimum integration time when averaging is enabled can be determined
     * using getMinimumAveragingIntegrationTimeMicros.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_INPUT_OUT_OF_BOUNDS if an invalid integration time is supplied;
     *                  ERROR_INTEGRATION_TIME_BELOW_AVERAGING_MIN if averaging is enabled and the specified
     *                                             integration time is below the minimum required for averaging
     *                                             (see odapi_get_minimum_averaging_integration_time_micros);
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param integration_time_micros (Input) The new integration time in
     *      units of microseconds
     */
    DLL_DECL void
        odapi_set_integration_time_micros(long deviceID,
            int *error_code, unsigned long integration_time_micros);

    /**
     * This function gets the integration time from the specified device.
     * This function should not be responsible for performing stability
     * scans.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_INPUT_OUT_OF_BOUNDS if an invalid integration time is supplied;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param integration_time_micros (Input) The new integration time in
     *      units of microseconds
     */
    DLL_DECL unsigned long
        odapi_get_integration_time_micros(long deviceID, int *error_code);

    /**
     * This function returns the smallest integration time setting,
     * in microseconds, that is valid for the spectrometer.
     * 
     * @note some devices that make use of onboard functionality to perform averaging have
     * a different, larger, minimum integration time for acquisition when averaging is enabled.
     * Refer to the documentation for your spectrometer to see if this is the case.
     * The minimum integration time when averaging is enabled can be determined
     * using odapi_get_minimum_averaging_integration_time_micros.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used
     *      for storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return Returns minimum legal integration time in microseconds if > 0.
     *      On error, returns 0 and error_code will be set accordingly.
     */
    DLL_DECL unsigned long
        odapi_get_minimum_integration_time_micros(long deviceID, int *error_code);

    /**
     * This function returns the integration time increment setting,
     * in microseconds, that is valid for the spectrometer. Most spectrometer returns 1.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used
     *      for storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return Returns the integration time increment in microseconds.
     */
    DLL_DECL unsigned long
        odapi_get_integration_time_increment_micros(long deviceID, int* error_code);

    /**
     * Get minimum integration time in microseconds when averaging is enabled.
     * 
     * @note some devices that make use of onboard functionality to perform averaging have
     * a different, larger, minimum integration time for acquisition when averaging is enabled.
     * Refer to the documentation for your spectrometer to see if this is the case.
     * The minimum integration time when averaging is not enabled can be determined
     * using odapi_get_minimum_integration_time_micros.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used
     *      for storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return Returns minimum legal integration time in microseconds if > 0.
     *      On error, returns 0 and error_code will be set accordingly.
     */
    DLL_DECL unsigned long
        odapi_get_minimum_averaging_integration_time_micros(long deviceID, int* error_code);

    /**
    * This function returns the largest integration time setting,
    * in microseconds, that is valid for the spectrometer.
    *
    * @param deviceID (Input) The index of a device previously opened with
    *      odapi_open_device().
    * @param error_code (Output) A pointer to an integer that can be used
    *      for storing error codes. This may be NULL in which case no error code is returned.
    *      The error codes returned by this function are:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
    *                  ERROR_TRANSFER_ERROR if a communication error occurred;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @return Returns minimum legal integration time in microseconds if > 0.
    *      On error, returns 0 and error_code will be set accordingly.
    */
    DLL_DECL unsigned long
        odapi_get_maximum_integration_time_micros(long deviceID, int *error_code);

    /**
     * This function returns the maximum pixel intensity for the
     * spectrometer.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used
     *      for storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return Returns maximum pixel intensity if > 0.
     *      On error, returns -1 and error_code will be set accordingly.
     */
    DLL_DECL double
        odapi_get_maximum_intensity(long deviceID, int *error_code);

    /**
     * Read a maximum of 15 spectra from the data buffer. This function requires that both back to back scans
     * and data buffer be enabled. See "odapi_adv_set_data_buffer_enable()" and "odapi_adv_set_number_of_backtoback_scans()".
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing error codes.
     *      This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_CODE_INVALID_ARGUMENT if either buffer or tick_count are a null pointer;
     *                  ERROR_NOT_ENOUGH_BUFFER_SPACE if the buffer space size or the tick count size are not = 15;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param buffer (Output) An array of pointer for storing spectra.
     * @param buffer_row_size  (Input) The buffer array size must be 15. This is the maximum value that can be return by this function.
     * @param buffer_column_size  (Input) The data size of each element of the "buffer".
     * @param tick_count (Output) The timestamp of each spectra.
     * @param tick_count_size  (Input) The "tick_count" array size must be 15. This is the maximum value that can be return by this function.
     * @return Returns the number of spectra read. It can be zero.
     */
    DLL_DECL int
        odapi_get_raw_spectrum_with_metadata(long deviceID, int *error_code, double *buffer[], int buffer_row_size, int buffer_column_size,
                                             long long int *tick_count, int tick_count_size);

    /**
     * This returns an integer denoting the number of pixels in a
     * formatted spectrum (as returned by get_formatted_spectrum(...)).
     *
     * @param deviceID (Input)  The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the length of a formatted spectrum.
     */
    DLL_DECL int
        odapi_get_formatted_spectrum_length(long deviceID, int *error_code);

    /**
     * This acquires a spectrum and returns the answer in formatted
     *     floats.  In this mode, auto-nulling should be automatically
     *     performed for devices that support it.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_NOT_ENOUGH_BUFFER_SPACE if the size of the buffer is smaller than the formatted spectrum length;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param buffer (Output) A buffer (with memory already allocated) to
     *      hold the spectral data
     * @param buffer_length (Input) The length of the buffer
     *
     * @return the number of floats read into the buffer
     */
    DLL_DECL int
        odapi_get_formatted_spectrum(long deviceID, int *error_code,
            double* buffer, int buffer_length);

    /**
    * Store a dark spectrum for use in subsequent corrections i.e. dark correction and nonlinearity correction.
    * @see getStoredDarkSpectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param darkSpectrum the buffer that contains the dark spectrum to be stored.
    * @param darkSpectrumLength the actual size of the dark spectrum buffer.
    */
    DLL_DECL void odapi_set_stored_dark_spectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength);

    /**
    * Retrieve a previously stored dark spectrum for use in subsequent corrections i.e. dark correction and nonlinearity correction.
    * @see setStoredDarkSpectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found;
    *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param darkSpectrum the buffer that contains the dark spectrum to be retrieved.
    * @param darkSpectrumLength the actual size of the dark buffer.
    * @return the size of the stored dark spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_get_stored_dark_spectrum(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength);

    /**
    * Acquire a spectrum and use the supplied dark spectrum to perform a dark correction then return the dark corrected spectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
    *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
    *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
    *                  ERROR_TRANSFER_ERROR if a communication error occurred;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param darkSpectrum the buffer that contains the dark spectrum to be used for the dark correction.
    * @param darkSpectrumLength the actual size of the dark spectrum buffer.
    * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
    * @param darkCorrectedSpectrumLength the actual size of the dark correction buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_get_dark_corrected_spectrum1(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength,
        double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

    /**
    * Dark correct a previously acquired illuminated spectrum and a stored dark spectrum.
    * @see setStoredDarkSpectrum
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found.
    * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
    * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
    * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
    * @param darkCorrectedSpectrumLength the actual size of the dark corrected buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_dark_correct_spectrum1(long deviceID, int* errorCode, double* illuminatedSpectrum, int illuminatedSpectrumLength,
        double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

    /**
    * Acquire a spectrum and use the previously stored dark spectrum to perform a dark correction then return the dark corrected spectrum.
    * @see setStoredDarkSpectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
    *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
    *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found.
    *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
    *                  ERROR_TRANSFER_ERROR if a communication error occurred;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
    * @param darkCorrectedSpectrumLength the actual size of the dark correction buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_get_dark_corrected_spectrum2(long deviceID, int* errorCode, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

    /**
    * Dark correct a previously acquired illuminated spectrum using a previously acquired dark spectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    * @param darkSpectrum the buffer that contains the dark spectrum to be used for the dark correction.
    * @param darkSpectrumLength the actual size of the dark spectrum buffer.
    * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
    * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
    * @param darkCorrectedSpectrum the buffer that will receive the dark corrected spectrum.
    * @param darkCorrectedSpectrumLength the actual size of the dark corrected buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_dark_correct_spectrum2(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
        int illuminatedSpectrumLength, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

    /**
    * Acquire a spectrum and use the supplied dark spectrum to perform a dark correction
    * followed by the nonlinearity correction then return the nonlinearity corrected spectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
    *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
    *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
    *                  ERROR_TRANSFER_ERROR if a communication error occurred;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param darkSpectrum the buffer that contains the dark spectrum to be used for the dark correction.
    * @param darkSpectrumLength the actual size of the dark spectrum buffer.
    * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
    * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity correction buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_get_nonlinearity_corrected_spectrum1(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength,
        double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);

    /**
    * Nonlinearity correct a previously acquired illuminated spectrum using a stored dark spectrum.
    * This function performs a dark correction using a previously stored dark spectrum prior to performing
    * the nonlinearity correction.
    * @see setStoredDarkSpectrum
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found.
    * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
    * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
    * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
    * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity corrected buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_nonlinearity_correct_spectrum1(long deviceID, int* errorCode, double* illuminatedSpectrum,
        int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);

    /**
    * Acquire a spectrum and use the previously stored dark spectrum to perform a dark correction
    * followed by a nonlinearity correction then return the nonlinearity corrected spectrum.
    * @see setStoredDarkSpectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT legacy correction functionality has been enabled using
    *                                    either applyElectricDarkCorrection or applyNonLinearityCorrection or both;
    *                  ERROR_VALUE_NOT_FOUND no stored dark spectrum was found;
    *                  ERROR_FEATURE_NOT_FOUND if the spectrometer feature is not available;
    *                  ERROR_TRANSFER_ERROR if a communication error occurred;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
    * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity correction buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_get_nonlinearity_corrected_spectrum2(long deviceID, int* errorCode, double* nonlinearityCorrectedSpectrum,
        int nonlinearityCorrectedSpectrumLength);

    /**
    * Nonlinearity correct a previously acquired illuminated spectrum after
    * dark correction using a previously acquired dark spectrum.
    *
    * @param deviceID the identifier of the device as returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    * @param darkSpectrum the buffer that contains the dark spectrum to be used prior to the nonlinearity correction.
    * @param darkSpectrumLength the actual size of the dark spectrum buffer.
    * @param illuminatedSpectrum the buffer that contains the illuminated spectrum to be corrected.
    * @param illuminatedSpectrumLength the actual size of the illuminated spectrum buffer.
    * @param nonlinearityCorrectedSpectrum the buffer that will receive the nonlinearity corrected spectrum.
    * @param nonlinearityCorrectedSpectrumLength the actual size of the nonlinearity corrected buffer.
    * @return the size of the returned corrected spectrum on success, zero otherwise.
    */
    DLL_DECL int odapi_nonlinearity_correct_spectrum2(long deviceID, int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
        int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);

    /**
    * Apply a boxcar correction on the given illuminated spectrum.
    *
    * @param[in]  deviceID  The identifier of the device as returned by getDeviceIDs.
    * @param[out] errorCode Set to 0 if successful, an OceanDirect error code (nonzero) otherwise
    *                       ERROR_VALUE_NOT_FOUND no stored dark spectrum was found;
    *                       ERROR_NO_DEVICE if deviceID is not a valid and open deviceID
    *                       ERROR_TRANSFER_ERROR if a communication error occurred
    *                       ERROR_FEATURE_NOT_FOUND if device does not support this feature
    *                       ERROR_COMMAND_NOT_SUPPORTED if device does not support this command.
    * @param[in/out] illuminatedSpectrum The spectrum that will be boxcar corrected.
    * @param[in] boxcarWidth The boxcar width.
    */
    DLL_DECL void odapi_boxcar_correct_spectrum(long deviceID, int* errorCode, double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength,
                                                unsigned int boxcarWidth, double* boxcarCorrectedSpectrum, unsigned int boxcarCorrectedSpectrumLength);

    /**
     * Get the number of spectra to be averaged per returned spectrum.
     * When this value has been set greater than 1 the specified number of spectra are averaged and the
     * resulting average is returned by odapi_get_formatted_spectrum (or odapi_get_raw_spectrum_with_metadata).
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the number of scans to average as an unsigned short integer
     */
    DLL_DECL unsigned int odapi_get_scans_to_average(long deviceID, int* error_code);

    /**
     * Set the number of spectra to be averaged per returned spectrum.
     * When this value is set greater than 1 the specified number of spectra are averaged and the
     * resulting average is returned by odapi_get_formatted_spectrum (or odapi_get_raw_spectrum_with_metadata).
     * 
     * @note Some devices have a minimum integration time for averaging that is different to
     * the minimum integration time for unaveraged acquisition (see your spectrometer documentation
     * to determine if this is a requirement).
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_INTEGRATION_TIME_BELOW_AVERAGING_MIN if the current integration time is
     *                                         below the minimum required for averaging
     *                                         it will not be possible to enable averaging
     *                                             (see odapi_get_minimum_averaging_integration_time_micros);
     *                  ERROR_INPUT_OUT_OF_BOUNDS an invalid value for scans to average has been supplied;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param scansToAverage (Input) The number of spectrum scans used to generate a less
     *		noisy spectrum due to averaging
     *
     * @return void
     */
    DLL_DECL void odapi_set_scans_to_average(long deviceID, int* error_code, unsigned int scansToAverage);


    /**
     * Get the width of the boxcar smoothing to be applied to the returned spectrum.
     * When this value has been set greater than 0, boxcar smoothing (a moving average) is
     * applied to the spectrum returned by odapi_get_formatted_spectrum (or odapi_get_raw_spectrum_with_metadata).
     * The width specified is the number of pixels either side of the central pixel of the average
     * i.e. if the result of this function is n, the "full width" of the smoothing is 2*n+1.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the width of the boxcar filter an unsigned char (values typically 0-15)
     */
    DLL_DECL unsigned short int odapi_get_boxcar_width(long deviceID, int* error_code);

    /**
     * Set the width of the boxcar smoothing to be applied to the returned spectrum.
     * When this value is set greater than 0, boxcar smoothing (a moving average) is
     * applied to the spectrum returned by odapi_get_formatted_spectrum (or odapi_get_raw_spectrum_with_metadata).
     * The width specified is the number of pixels either side of the central pixel of the average
     * i.e. if the result of this function is n, the "full width" of the smoothing is 2*n+1.
     *
     * Setting this value to 0 turns off the boxcar smoothing.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_INPUT_OUT_OF_BOUNDS an invalid value for boxcar width has been supplied;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param boxcarWidth (Input) The width of the boxcar smoothing function to be used.
     *			Values are typically 1 to 15.
     */
    DLL_DECL void odapi_set_boxcar_width(long deviceID, int* error_code, unsigned short int boxcarWidth);

    /**
     * This computes the wavelengths for the spectrometer and fills in the
     * provided array (up to the given length) with those values.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      open_spectrometer().
     * @param error_code (Ouput) pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param wavelengths (Output) A pre-allocated array of doubles that the wavelengths
     *      will be copied into
     * @param length (Input) The number of values to copy into the wavelength array
     *      (this should be no larger than the number of doubles allocated in the wavelengths
     *      array)
     *
     * @return the number of wavelengths written into the wavelength buffer
     */
    DLL_DECL int
        odapi_get_wavelengths(long deviceID, int *error_code, double *wavelengths, int length);

    /**
     * Return wavelengths coefficients stored in the device.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      open_spectrometer().
     * @param error_code (Ouput) pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param coeff (Output) A pre-allocated array of doubles that the coefficients will be copied into
     * @param length (Input) The number of values to copy into the coefficients array
     *      (this should be no larger than the number of doubles allocated in the coefficients
     *      array)
     *
     * @return the number of coefficients copied to the output buffer.
     */
    DLL_DECL int odapi_get_wavelength_coeffs(long deviceID, int *error_code, double *coeff, int length);

    /**
     * This finds a single x-axis index corresponding to an approximate single wavelength.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      open_spectrometer().
     * @param error_code (Ouput) pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_CODE_ARRAY_INDEX_OUT_OF_BOUNDS the specified wavelengths is not within the device's wavelength range;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param wavelength (Output) A doubles that contains the actual wavelength.
     * @param approxWavelength (Input) A double value containing a best guess or
     *      approximate (this should be within bounds of the entire wavelength array
     *      or an error is generated)
     *
     * @return the index used for the entire wavelength array from (odapi_get_wavelengths()) method.
     */
    DLL_DECL int
        odapi_get_index_at_wavelength(long deviceID, int *error_code, double *wavelength, double approxWavelength);

    /**
     * This finds one or multiple x-axis indices corresponding to one or multilpe estimated wavelengths.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      open_spectrometer().
     * @param error_code (Ouput) pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_CODE_ARRAY_INDEX_OUT_OF_BOUNDS one or more of the specified wavelengths is not within the device's wavelength range;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param indices (Output) A double array that contains indices of actual wavelengths.
     * @param indicesLength (Input) The indices buffer size.
     * @param wavelength (Output) A double array that contains the actual wavelengths.
     * @param wavelengthLength (Input) The wavelength buffer size.
     *
     * @return the length of both the wavelength and indices array.
     */
    DLL_DECL int
    odapi_get_indices_at_wavelengths(long deviceID, int *error_code, int *indices, int indicesLength, double *wavelength, int wavelengthLength);

    /**
     * This finds a continuous range of x-axis indices corresponding to a low and high
     * wavelength parameter given.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      open_spectrometer().
     * @param error_code (Ouput) pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_CODE_ARRAY_INDEX_OUT_OF_BOUNDS the lower or upper bound specified is not within the device's wavelength range;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param indices (Output) A double array that contains indices of actual wavelengths.
     * @param indicesLength (input) The indices buffer size.
     * @param wavelength (Output) A double array that contains the actual wavelengths.
     * @param wavelengthLength (Input) The wavelength buffer size.
     * @param lo (Input) low estimated wavelength for start of range.
     * @param hi (Input) high estimated wavelength for end of range.
     *
     * @return the length of both the wavelength and indices array.
     */
    DLL_DECL int
        odapi_get_indices_at_wavelength_range(long deviceID, int *error_code, int *indices, int indicesLength,
                                              double *wavelength, int wavelengthLength, double lo, double hi);

    /**
     * This returns the number of pixels that are electrically active but
     * optically masked (a.k.a. electric dark pixels).  Note that not all
     * detectors have optically masked pixels; in that case, this function
     * will return zero.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
     *                                   electric dark correction;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the number of pixels that can be retrieved by the
     *      odapi_spectrometer_get_electric_dark_pixel_indices() function.
     */
    DLL_DECL int odapi_get_electric_dark_pixel_count(long deviceID, int *error_code);

    /**
    * Return the pixel count. The pixel count refers to all the pixels from the spectra we received from the device.
    *
    * @param[in] deviceID the device ID for the device to be configured (from OceanDirect::findDevices())
    * @param[out] errorCode set to 0 if successful, an OceanDirect error code (nonzero) otherwise
    *             ERROR_NO_DEVICE if deviceID is not a valid and open deviceID
    *             ERROR_FEATURE_NOT_FOUND if device does not support this feature
    *             ERROR_TRANSFER_ERROR if data transfer to/from device fails
    * @return The pixel count.
    */
    DLL_DECL int odapi_get_pixel_count(long deviceID, int *error_code);

    /**
    * Read the active pixel range from the sensor pixel array.
    *
    * @param[in] deviceID the device ID for the device to be configured (from OceanDirect::findDevices())
    * @param[out] errorCode set to 0 if successful, an OceanDirect error code (nonzero) otherwise
    *             ERROR_NO_DEVICE if deviceID is not a valid and open deviceID
    *             ERROR_FEATURE_NOT_FOUND if device does not support this feature
    *             ERROR_TRANSFER_ERROR if data transfer to/from device fails
    * @param[out] range The output buffer for active pixel range indices.
    * @param[in] rangeSize The output buffer size.
    * @return Number of elements copied into the output buffer.
    */
    DLL_DECL int odapi_get_active_pixel_range(long deviceID, int *error_code, int *range, int rangeSize);

    /**
    * Read the optical dark pixel range from the sensor pixel array.
    *
    * @param[in] deviceID the device ID for the device to be configured (from OceanDirect::findDevices())
    * @param[out] errorCode set to 0 if successful, an OceanDirect error code (nonzero) otherwise
    *             ERROR_NO_DEVICE if deviceID is not a valid and open deviceID
    *             ERROR_FEATURE_NOT_FOUND if device does not support this feature
    *             ERROR_TRANSFER_ERROR if data transfer to/from device fails
    * @param[out] range The output buffer for optical dark pixel range indices.
    * @param[in] rangeSize The output buffer size.
    * @return Number of elements copied into the output buffer.
    */
    DLL_DECL int odapi_get_optical_dark_pixel_range(long deviceID, int *error_code, int *range, int rangeSize);

    /**
    * Read the transition pixel range from the sensor pixel array.
    *
    * @param[in] deviceID the device ID for the device to be configured (from OceanDirect::findDevices())
    * @param[out] errorCode set to 0 if successful, an OceanDirect error code (nonzero) otherwise
    *             ERROR_NO_DEVICE if deviceID is not a valid and open deviceID
    *             ERROR_FEATURE_NOT_FOUND if device does not support this feature
    *             ERROR_TRANSFER_ERROR if data transfer to/from device fails
    * @param[out] range The output buffer for transition pixel range indices.
    * @param[in] rangeSize The output buffer size.
    * @return Number of elements copied into the output buffer.
    */
    DLL_DECL int odapi_get_transition_pixel_range(long deviceID, int *error_code, int *range, int rangeSize);

    /**
    * Read bad pixel indices from the sensor pixel array.
    *
    * @param[in] deviceID the device ID for the device to be configured (from OceanDirect::findDevices())
    * @param[out] errorCode set to 0 if successful, an OceanDirect error code (nonzero) otherwise
    *             ERROR_NO_DEVICE if deviceID is not a valid and open deviceID
    *             ERROR_FEATURE_NOT_FOUND if device does not support this feature
    *             ERROR_TRANSFER_ERROR if data transfer to/from device fails
    * @param[out] badPixelIndices The output buffer for bad pixel indices.
    * @param[in] badPixelIndices The output buffer size.
    * @return Number of elements copied into the output buffer.
    */
    DLL_DECL int odapi_get_bad_pixel_indices(long deviceID, int *error_code, int *badPixelsIndices, int badPixelSize);


    DLL_DECL void odapi_set_bad_pixel_indices(long deviceID, int* error_code, int* badPixelsIndices, int badPixelSize);

    /**
    * This fills in the provided array (up to the given length) with the indices
    * of the pixels that are electrically active but optically masked
    * (a.k.a. electric dark pixels).  Note that not all detectors have optically
    * masked pixels; in that case, this function will return zero.
    *
    * @param deviceID (Input) The index of a device previously opened with
    *      odapi_open_device().
    * @param error_code (Output) pointer to an integer that can be used for
    *      storing error codes. This may be NULL in which case no error code is returned.
    *      The error codes returned by this function are:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
    *                                   electric dark correction;
    *                  ERROR_NO_DEVICE if the device does not exist.
    * @param indices (Output) A pre-allocated array of ints that the pixel indices
    *      will be copied into
    * @param length (Input) The number of values to copy into the indices array
    *      (this should be no larger than the number of ints allocated in the indices
    *      array)
    *
    * @return the number of indices written into the indices buffer
    */
    DLL_DECL int odapi_get_electric_dark_pixel_indices(long deviceID, int *error_code, int *indices, int length);

    /**
     * This function gets the number of light sources that are represented by
     * the given featureID.  Such light sources could be individual LEDs,
     * light bulbs, lasers, etc.  Each of these light sources may have different
     * capabilities, such as programmable intensities and enables, which should
     * be queried before they are used.
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the number of light sources (e.g. bulbs) in the indicated feature
     */
    DLL_DECL int
        odapi_adv_get_light_source_count(long deviceID, int* error_code);

    /**
     * Queries whether the indicated light source within the given feature
     * instance has a usable enable/disable control.  If this returns 0
     * (meaning no enable available) then calling odapi_light_source_set_enable()
     * or odapi_light_source_is_enabled() is likely to result in an error.
     *

     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Ouput)  A pointer to an integer that can be used for
     *      storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param light_source_index (Input) Which of potentially many light sources
     *      (LEDs, lasers, light bulbs) within the indicated feature instance to query
     *
     * @return 0 to indicate specified light source cannot be enabled/disabled,
     *         1 to indicate specified light source can be enabled/disabled with
     *                       odapi_adv_light_source_set_enable()
     */
    DLL_DECL unsigned char
        odapi_adv_light_source_has_enable(long deviceID, int *error_code,
            int light_source_index);

    /**
     * Queries whether the indicated light source within the given feature
     * instance is enabled (energized).
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param light_source_index (Input) Which of potentially many light sources (LEDs, lasers,
     *      light bulbs) within the indicated feature instance to query
     *
     * @return 0 to indicate specified light source is disabled (should emit no light),
     *         1 to indicate specified light source is enabled (should emit light depending
     *                       on configured intensity setting)
     */
    DLL_DECL unsigned char
        odapi_adv_light_source_is_enabled(long deviceID, int *error_code,
            int light_source_index);

    /**
     * Attempts to enable or disable the indicated light source within the given
     * feature instance.  Not all light sources have an enable/disable control,
     * and this capability can be queried with odapi_adv_light_source_has_enable().
     * Note that an enabled light source should emit light according to its last
     * (or default) intensity setting which might be the minimum; in this case,
     * the light source might appear to remain off.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param light_source_index (Input) Which of potentially many light sources (LEDs, lasers,
     *      light bulbs) within the indicated feature instance to query
     * @param enable (Input) Whether to enable the light source.  A value of zero will attempt
     *      to disable the light source, and any other value will enable it.
     */
    DLL_DECL void
        odapi_adv_light_source_set_enable(long deviceID, int *error_code,
            int light_source_index, unsigned char enable);

    /**
     * This function sets the strobe enable on the spectrometer.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param lamp_enable (Input) A character used for denoting the desired value
     *      (high/low) of the strobe-enable pin.   If the value of
     *      strobe_enable is zero, then the pin should be set low. If
     *      the value of strobe_enable is non-zero, then the pin should be
     *      set high.
     */
    DLL_DECL void
        odapi_adv_set_lamp_enable(long deviceID, int *error_code, unsigned char lamp_enable);

    /**
     * This function returns the strobe enable state of the spectrometer.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return true if the lamp is enabled otherwise return false.
     */
    DLL_DECL bool
        odapi_adv_get_lamp_enable(long deviceID, int *error_code);

    /**
     * This function will open or close the shutter on the spectrometer.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param shutter_state (Input) True(1) will open the shutter. False(0) will close the shutter.
     */
    DLL_DECL void
        odapi_adv_set_shutter_open(long deviceID, int* error_code, unsigned char shutter_state);

    /**
     * This function returns the shutter state of the spectrometer.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return true if the shutter is opened otherwise return false.
     */
        DLL_DECL bool
            odapi_adv_get_shutter_state(long deviceID, int* error_code);

    /**
     * Set the enable status of the single strobe signal.  Note that on some
     * devices the enable control is shared with other signals (e.g. lamp
     * enable and continuous strobe) so this may have some side-effects and
     * changing those features may affect the single strobe as well.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param enable Whether to enable the single strobe function
     */
    DLL_DECL void
        odapi_adv_set_single_strobe_enable(long deviceID, int *error_code,
            unsigned char enable);

    /**
     * Set the amount of time, in microseconds, that should elapse after
     * a starting event before the single strobe should have
     * a rising edge.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param microseconds The delay, in microseconds, that the single strobe
     * should wait before the pulse begins.
     */
    DLL_DECL void
        odapi_adv_set_single_strobe_delay(long deviceID, int *error_code,
            unsigned long delay_micros);

    /**
     * Set the amount of time, in microseconds, that the single strobe pulse
     * should remain high after it begins.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param microseconds The duration, in microseconds, of the single
     * strobe pulse after the rising edge occurs. Once this duration elapses,
     * a falling edge will be generated.
     */
    DLL_DECL void
        odapi_adv_set_single_strobe_width(long deviceID, int *error_code,
            unsigned long width_micros);

    /**
     * Get the enable status of the single strobe signal.  Note that on some
     * devices the enable control is shared with other signals (e.g. lamp
     * enable and continuous strobe) so this may have some side-effects and
     * changing those features may affect the single strobe as well.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return false if not enabled, true if available.
     */
    DLL_DECL bool
        odapi_adv_get_single_strobe_enable(long deviceID, int *error_code);

    /**
     * Get the amount of time, in microseconds, that should elapse after
     * a starting event before the single strobe should have
     * a rising edge.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The delay, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_delay(long deviceID, int *error_code);

    /**
     * Get the amount of time, in microseconds, that the single strobe pulse
     * should remain high after it begins.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The width, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_width(long deviceID, int *error_code);

    /**
     * This function gets the continuous strobe period of the device in microseconds.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The period in microseconds.
     */
    DLL_DECL unsigned long odapi_adv_get_continuous_strobe_period_micros(long deviceID, int *error_code);

    /**
     * This function gets the continuous strobe state (enabled or disabled) of the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return true if continuous strobe is enabled, false otherwise.
     */
    DLL_DECL bool odapi_adv_get_continuous_strobe_enable(long deviceID, int *error_code);

    /**
     * This function gets the minimum continuous strobe period of the device in microseconds.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The minimum strobe period, in microseconds.
     */
    DLL_DECL unsigned long odapi_adv_get_continuous_strobe_period_minimum_micros(long deviceID, int *error_code);

    /**
     * This function gets the maximum continuous strobe period of the device in microseconds.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The maximum strobe period in microseconds.
     */
    DLL_DECL unsigned long odapi_adv_get_continuous_strobe_period_maximum_micros(long deviceID, int *error_code);

    /**
     * This function gets the current size of the strobe period increment of the device in microseconds.
     * The increment is dependent on the strobe period. Small strobe periods i.e. less than about 1ms
     * will have a small increment, typically 1 microsecond. Larger strobe periods will have larger
     * increments, typically 1ms.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The current strobe period increment in microseconds.
     */
    DLL_DECL unsigned long odapi_adv_get_continuous_strobe_period_increment_micros(long deviceID, int *error_code);

    /**
     * This function gets the strobe width of the device in microseconds.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The current strobe width in microseconds.
     */
    DLL_DECL unsigned long odapi_adv_get_continuous_strobe_width_micros(long deviceID, int *error_code);

    /**
     * Get the minimum amount of time, in microseconds, that should elapse after
     * a starting event before the single strobe should have
     * a rising edge.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The delay, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_delay_minimum(long deviceID, int *error_code);

    /**
     * Get the maximum amount of time, in microseconds, that should elapse after
     * a starting event before the single strobe should have
     * a rising edge.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The delay, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_delay_maximum(long deviceID, int *error_code);

    /**
     * This function gets the single strobe delay increment.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The delay increment, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_delay_increment(long deviceID, int *error_code);

    /**
     * Get the minimum amount of time, in microseconds, that the single strobe pulse
     * should remain high after it begins.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The minimum width, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_width_minimum(long deviceID, int *error_code);

    /**
     * Get the maximum amount of time, in microseconds, that the single strobe pulse
     * should remain high after it begins.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The maximum width, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_width_maximum(long deviceID, int *error_code);

    /**
     * Return the single strobe width increment.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The width increment, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_width_increment(long deviceID, int *error_code);

    /**
     * Return the single strobe cycle maximum.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The strobe maximum cycle, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_single_strobe_cycle_maximum(long deviceID, int *error_code);

    /**
     * This function gets the continuous strobe period on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The period, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_continuous_strobe_period_micros(long deviceID, int *error_code);

    /**
     * This function gets the continuous strobe state on the device whether its enabled or not.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return true if the continuous strobed is enable. Otherwise its false.
     */
    DLL_DECL bool
        odapi_adv_get_continuous_strobe_enable(long deviceID, int *error_code);

    /**
     * This function gets the minimum continuous strobe period on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The minimum strobe period.
     */
    DLL_DECL unsigned long
        odapi_adv_get_continuous_strobe_period_minimum_micros(long deviceID, int *error_code);

    /**
     * This function gets the maximum continuous strobe period on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The maximum strobe period.
     */
    DLL_DECL unsigned long
        odapi_adv_get_continuous_strobe_period_maximum_micros(long deviceID, int *error_code);

    /**
     * This function gets the continuous strobe increment on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The strobe increment.
     */
    DLL_DECL unsigned long
        odapi_adv_get_continuous_strobe_period_increment_micros(long deviceID, int *error_code);

    /**
     * This function gets the continuous strobe width on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The width, in microseconds.
     */
    DLL_DECL unsigned long
        odapi_adv_get_continuous_strobe_width_micros(long deviceID, int *error_code);

    /**
     * This function sets the continuous strobe enable state on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param enable (Input) A boolean used for denoting the desired state
     *        (on/off) of the continuous strobe generator.   If the value of
     *        enable is nonzero, then the continuous strobe will operate.  If
     *        the value of enable is zero, then the continuous strobe will stop.
     *        Note that on some devices the continuous strobe enable is tied to other
     *        enables (such as lamp enable or single strobe enable) which may cause
     *        side effects.
     */
    DLL_DECL void odapi_adv_set_continuous_strobe_enable(long deviceID, int *error_code, unsigned char enable);

    /**
     * This function sets the continuous strobe period on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param period_micros (Input) The new period of the continous strobe measured in microseconds
     */
    DLL_DECL void odapi_adv_set_continuous_strobe_period_micros(long deviceID, int *error_code, unsigned long period_micros);

    /**
     * This function sets the continuous strobe width on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param period_micros (Input) The new width of the continous strobe measured in microseconds
     */
    DLL_DECL void
        odapi_adv_set_continuous_strobe_width_micros(long deviceID, int *error_code, unsigned long width_micros);

    /**
    * This function sets the exterior blinking LED on the spectrometer.
    *
    * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
    * @param error_code (Output) A pointer to an integer that can be used for storing
    *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
    * @param led_enable (Input) A character used for denoting the desired value
    *      (high/low) of the LED enable pin.   If the value of
    *      led_enable is false, then the pin should be set off. If
    *      the value of led_enable is true, then the pin should be
    *      blinking.
    */
    DLL_DECL void
        odapi_adv_set_led_enable(long deviceID, int *error_code, bool led_enable);

    /**
     * This function gets the exterior LED state on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return true if the LED is enabled, false otherwise.
     */
    DLL_DECL bool
        odapi_adv_get_led_enable(long deviceID, int *error_code);

    /**
     * This function reads the actual temperature of the TEC and returns the value in
     * degrees celsius.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return The TEC temperature in degrees celsius.
     */
    DLL_DECL double
        odapi_adv_tec_get_temperature_degrees_C(long deviceID, int *error_code);

    /**
     * This function sets the target (setpoint) TEC temperature.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param temperature_degrees_celsius (Input) desired temperature,
     *      in degrees celsius.
     */
    DLL_DECL void
        odapi_adv_tec_set_temperature_setpoint_degrees_C(long deviceID, int *error_code,
            double temperature_degrees_celsius);

    /**
     * This function enables the TEC feature on the device.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param tec_enable (Input) A character that denotes the desired TEC enable
     *      state.  If the value of tec_enable is zero, the TEC should
     *      be disabled.  If the value of tec_enable is non-zero, the TEC
     *      should be enabled.
     */
    DLL_DECL void
        odapi_adv_tec_set_enable(long deviceID, int *error_code, unsigned char tec_enable);

    /**
     * This function returns true if the attached thermo electric cooler is enabled.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return bool True if the TEC is enabled otherwise it's false.
     */
    DLL_DECL bool
        odapi_adv_tec_get_enable(long deviceID, int *error_code);

    /**
     * This function returns the thermo electric cooler setpoint temperature.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return float Returns temperature value in celcius.
     */
    DLL_DECL float
        odapi_adv_tec_get_temperature_setpoint_degrees_C(long deviceID, int *error_code);

    /**
     * This function returns true if the thermo electric cooler temperature has reaches a stable setpoint temperature.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return bool True if the TEC temperature is stable otherwise it's false.
     */
    DLL_DECL bool
        odapi_adv_tec_get_stable(long deviceID, int *error_code);

    /**
     * This function returns the thermo electric cooler fan state whether it's enabled or not.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return bool True if the TEC fan is enabled.
     */
    DLL_DECL bool
        odapi_adv_tec_get_fan_enable(long deviceID, int *error_code);

    /**
     * This function reads out nonlinearity coefficients from the device's
     * internal memory if that feature is supported.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_VALUE_NOT_FOUND  no values are stored on the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param buffer (Output) preallocated buffer to store NLC coefficients
     * @param max_length (Input) size of preallocated buffer
     *
     * @return the number of doubles read from the device into the buffer
     */
    DLL_DECL int odapi_adv_get_nonlinearity_coeffs(long deviceID, int *error_code, double *buffer, int max_length);

    /**
     * This function read out the number of nonlinearity coefficients from the device's
     * internal memory if that feature is supported.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_VALUE_NOT_FOUND  no values are stored on the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param return The nonlinearity coefficient counts.
     */
    DLL_DECL int odapi_adv_get_nonlinearity_coeffs_count1(long deviceID, int *error_code);

    /**
     * This function read the nonlinearity coefficient of the given index.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_VALUE_NOT_FOUND  no values are stored on the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param index The nonlinearity coefficient index.
     * @param return The nonlinearity coefficient.
     */
    DLL_DECL double odapi_adv_get_nonlinearity_coeffs1(long deviceID, int *error_code, int index);

    /**
     * This function reads out the firmware revision from the device's
     * internal memory if that feature is supported.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the firmware revision as two unsigned short int bytes (Note that both Ocean View and SpectraSuite display the hex value.)
     */
    DLL_DECL unsigned short int odapi_adv_get_revision_firmware(long deviceID, int *error_code, char *buffer, int length);

    /**
     * This function reads out the FPGA revision from the device's
     * internal memory if that feature is supported.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the FPGA revision as two unsigned short int bytes (Note that both Ocean View and SpectraSuite display the hex value.)
     */
    DLL_DECL unsigned short int odapi_adv_get_revision_fpga(long deviceID, int *error_code, char *buffer, int length);

    /**
     * This function reads out the System revision from the device's
     * internal memory if that feature is supported.
     *
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *      error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED  this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     *
     * @return the FPGA revision as two unsigned short int bytes (Note that both Ocean View and SpectraSuite display the hex value.)
     */
    DLL_DECL unsigned short int odapi_adv_get_revision_system(long deviceID, int* error_code, char* buffer, int length);


    /**
     * @brief Clear the data buffer
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     */
    DLL_DECL void odapi_adv_clear_data_buffer(long deviceID, int *error_code);

    /**
     * @brief Get the number of data elements currently in the buffer
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return A count of how many items are available for retrieval from the buffer
     */
    DLL_DECL unsigned long odapi_adv_get_data_buffer_number_of_elements(long deviceID, int *error_code);

    /**
     * @brief Get the present limit of how many data elements will be retained by the buffer.
     *        This value can be changed with odapi_adv_set_buffer_capacity().
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return A count of how many items the buffer will store before data may be lost
     */
    DLL_DECL unsigned long odapi_adv_get_data_buffer_capacity(long deviceID, int *error_code);

    /**
     * @brief Get the maximum possible configurable size for the data buffer
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The largest value that may be set with odapi_adv_set_buffer_capacity().
     */
    DLL_DECL unsigned long odapi_adv_get_data_buffer_capacity_maximum(long deviceID, int *error_code);

    /**
     * @brief Get the minimum possible configurable size for the data buffer
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The smallest value that may be set with odapi_adv_set_buffer_capacity().
     */
    DLL_DECL unsigned long odapi_adv_get_data_buffer_capacity_minimum(long deviceID, int *error_code);

    /**
     * Set the number of data elements that the buffer should retain. This function must be
     * used with "odapi_adv_set_number_of_backtoback_scans()".
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param capacity (Input) Limit on the number of data elements to store.  This is
     *        bounded by what is returned by odapi_adv_get_buffer_capacity_minimum() and
     *        odapi_adv_get_buffer_capacity_maximum().
     */
    DLL_DECL void odapi_adv_set_data_buffer_capacity(long deviceID, int *error_code, unsigned long capacity);

    /**
     * Enable or disable data buffering.
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing error codes.
     * This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param flag True enable the buffer. False disable the buffer
     */
    DLL_DECL void odapi_adv_set_data_buffer_enable(long deviceID, int *error_code, unsigned char flag);

    /**
     * Return true if data buffering is enabled.
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing error codes.
     * This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_COMMAND_NOT_SUPPORTED this command is not supported by the device;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return True for enable data buffering otherwise it's false.
     */
    DLL_DECL bool odapi_adv_get_data_buffer_enable(long deviceID, int *error_code);

    /**
     * @brief Abort spectra acquisition.
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     */
    DLL_DECL void odapi_adv_abort_acquisition(long deviceID, int *error_code);

    /**
     * @brief Starts acquiring spectra and put them into device memory.
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     */
    DLL_DECL void odapi_adv_acquire_spectra_to_buffer(long deviceID, int *error_code);

    /**
     * @brief Get the device idle state. It returns 1(true) if device is idle otherwise it's 0(false).
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing
     *        error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return true if the device is idle, false otherwise.
     */
    DLL_DECL bool odapi_adv_get_device_idle_state(long deviceID, int *error_code);


    /**
     * Return the number of spectra that the device will capture per trigger event.
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing error codes.
     * This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @return The back-to-back scan value.
     */
    DLL_DECL unsigned long odapi_adv_get_number_of_backtoback_scans(long deviceID, int *error_code);

    /**
     * Set the number of spectra that the device will capture per trigger event. This function requires
     * data buffer to be enabled. See "odapi_adv_set_data_buffer_enable()".
     * @param deviceID (Input) The index of a device previously opened with odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used for storing error codes.
     * This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_FEATURE_NOT_FOUND if the feature does not exist;
     *                  ERROR_TRANSFER_ERROR if a communication error occurred;
     *                  ERROR_NO_DEVICE if the device does not exist.
     * @param numScans (Input) The back-to-back scan value.
     */
    DLL_DECL void odapi_adv_set_number_of_backtoback_scans(long deviceID, int *error_code, unsigned long numScans);

    /**
    * Read the maximum ADC counts.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The maximum ADC counts.
    */
    DLL_DECL int odapi_adv_get_autonull_maximum_adc_count(long deviceID, int *error_code);

    /**
    * Read the saturation level. Most devices returns 65535.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The saturation level.
    */
    DLL_DECL int odapi_adv_get_autonull_saturation_level(long deviceID, int *error_code);

    /**
    * Read the baseline level.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The baseline level.
    */
    DLL_DECL int odapi_adv_get_autonull_baseline_level(long deviceID, int *error_code);

    /**
    * Read the FPGA digital gain.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The gain value.
    */
    DLL_DECL int odapi_adv_get_autonull_fpga_digital_gain(long deviceID, int* error_code);

    /**
    * Read the FPGA digital offset.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The offset value.
    */
    DLL_DECL int odapi_adv_get_autonull_fpga_digital_offset(long deviceID, int* error_code);



    /**
    * Read autonulling constraints value for baseline settings. This command only applies to Ocean FX/HDX units.
    * @param deviceId the device ID for the device to be configured.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    * @param minDAC minimum offset DAC value.
    * @param maxDAC maximum offset DAC value.
    * @param minVolts minimum offset volt value.
    * @param maxVolts maximum offset volt value.
    */
    DLL_DECL void odapi_adv_get_autonull_baseline_level_constraints(long deviceID, int* error_code, unsigned int* minDAC, unsigned int* maxDAC, float* minVolts, float* maxVolts);

    /**
    * Read autonulling constraints value for saturation settings. This command only applies to Ocean FX/HDX units.
    * @param deviceId the device ID for the device to be configured.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    * @param minDAC minimum saturation DAC value.
    * @param maxDAC maximum saturation DAC value.
    * @param minVolts minimum saturation volt value.
    * @param maxVolts maximum saturation volt value.
    */
    DLL_DECL void odapi_adv_get_autonull_saturation_level_constraints(long deviceID, int* error_code, unsigned int* minDAC, unsigned int* maxDAC, float* minVolts, float* maxVolts);




    /**
    * Read the user string from the device. If this field in the device is not yet populated then a non-zero(6) code will be returned.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The output buffer containing user string.
    * @param buffer_length The buffer size should be at least 16.
    * @return The user string lengnth.
    */
    DLL_DECL int odapi_get_user_string(long deviceID, int *error_code, char *buffer, int buffer_length);

    /**
    * Write the user string to the device. The maximum string length is 16.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The buffer containing a user string.
    * @param buffer_length The maximum buffer size is 16.
    */
    DLL_DECL void odapi_set_user_string(long deviceID, int *error_code, char *buffer, int buffer_length);

    /**
    * Read the total user string count from the device. If the device don't support this command 
    * then a non-zero error code will be returned.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The total user string count.
    */
    DLL_DECL int odapi_get_user_string_count1(long deviceID, int *error_code);

    /**
    * Read the user string from the device. The maximum string length is 16. If this field in the
    * device is not yet populated then a non-zero(6) code will be returned. If the device don't support this command
    * then a non-zero error code will be returned.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param index  The user string index.
    * @param buffer The output buffer for user string.
    * @param buffer_length The maximum buffer size is 16.
    */
    DLL_DECL int odapi_get_user_string1(long deviceID, int *error_code, int index, char *buffer, int buffer_length);

    /**
    * Write the user string to the device. The maximum string length is 16. If the device don't support this command
    * then a non-zero error code will be returned.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param index  The user string index.
    * @param buffer The new user string.
    * @param buffer_length The maximum buffer size is 16.
    */
    DLL_DECL void odapi_set_user_string1(long deviceID, int *error_code, int index, char *buffer, int buffer_length);



    /**
    * Read the original vendor id (VID) from the device. This is an Ocean Insight VID.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The original VID.
    */
    DLL_DECL int odapi_adv_get_device_original_vid(long deviceID, int *error_code);

    /**
    * Read the original product id (PID) from the device. This is an Ocean Insight product specific PID.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The original PID.
    */
    DLL_DECL int odapi_adv_get_device_original_pid(long deviceID, int *error_code);

    /**
    * Read the vendor id (VID) from the device. This could be identical to the original VID or a customer assigned VID.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The device VID.
    */
    DLL_DECL int odapi_adv_get_device_vid(long deviceID, int *error_code);

    /**
    * Write a new vendor id (VID) to the device. After writing new value, you need to unplug the device before 
    * reading again the new value.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param int The new VID for the device.
    */
    DLL_DECL void odapi_adv_set_device_vid(long deviceID, int *error_code, int vid);

    /**
    * Set a new product id (PID) to the device. After writing new value, you need to unplug the device before 
    * reading again the new value.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param int The new PID for the device.
    */
    DLL_DECL void odapi_adv_set_device_pid(long deviceID, int *error_code, int pid);

    /**
    * Read the PID from the device. This could be identical to the original PID or a customer assigned PID.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The device PID.
    */
    DLL_DECL int odapi_adv_get_device_pid(long deviceID, int *error_code);

    /**
    * Read the original manufacturer string from the device.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The output buffer containing a manufacturer string.
    * @param buffer_length The minimum buffer size is 24.
    * @return The original manufacturer string length.
    */
    DLL_DECL int odapi_adv_get_device_original_manufacturer_string(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Read the original model string from the device.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The output buffer for the model string.
    * @param buffer_length The minimum buffer size is 24.
    * @return The original model string length.
    */
    DLL_DECL int odapi_adv_get_device_original_model_string(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Read the manufacturer string from the device.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The output buffer for the manufacturer string.
    * @param buffer_length The minimum buffer size is 24.
    * @return The manufacturer string length.
    */
    DLL_DECL int odapi_adv_get_device_manufacturer_string(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Set a new manufacturer string to the device. After writing new value, you need to unplug the device before 
    * reading again the new value.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The new manufacturer string.
    * @param buffer_length The maximum buffer size is 24.
    */
    DLL_DECL void odapi_adv_set_device_manufacturer_string(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Read the current model string from the device.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The output buffer for the model string.
    * @param buffer_length The minimum buffer size is 24.
    * @return The model string length.
    */
    DLL_DECL int odapi_adv_get_device_model_string(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Set a new model string to the device. After writing new value, you need to unplug the device before 
    * reading again the new value.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The new model string.
    * @param buffer_length The maximum buffer size is 24.
    */
    DLL_DECL void odapi_adv_set_device_model_string(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Read the device alias from the device. If this field in the device is not yet populated then a non-zero(6) code will be returned.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The output buffer for the device alias.
    * @param buffer_length The minimum buffer size is 16.
    * @return The device alias string length.
    */
    DLL_DECL int odapi_adv_get_device_alias(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Set a new device alias to the device.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param buffer The new model string.
    * @param buffer_length The maximum buffer size is 16.
    */
    DLL_DECL void odapi_adv_set_device_alias(long deviceID, int *error_code, char *buffer, int bufferLength);

    /**
    * Read the device RS-232 baud rate.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @return The port baud rate.
    */
    DLL_DECL int odapi_adv_get_baud_rate(long deviceID, int *error_code);

    /**
    * Set a new baud rate for the RS-232 port.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param baudRate The new port baud rate.
    */
    DLL_DECL void odapi_adv_set_baud_rate(long deviceID, int *error_code, int baudRate);

    /**
    * Save settings to flash.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    */
    DLL_DECL void odapi_adv_save_settings_to_flash(long deviceID, int *error_code);

    /**
    * Restarts the device.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    */
    DLL_DECL void odapi_adv_reset_device(long deviceID, int *error_code);


    /**
    * Check to see if DHCP (client) is enabled on the specified interface. If DHCP is
    * enabled then the device will be able to receive and IP address from a DHCP server
    * oin the network it is connected to.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @return true if DHCP is enabled on the specified interface, false otherwise.
    */
    DLL_DECL bool odapi_adv_ipv4_is_dhcp_enabled(long deviceID, int *errorCode, unsigned char ifNum);

    /**
    * Turn the DHCP client on or off for the device on the specified interface.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @param enabled a value of 0 turns the DHCP client off, a value greater than 0 turns the DHCP client on.
    */
    DLL_DECL void odapi_adv_ipv4_set_dhcp_enable(long deviceID, int *errorCode, unsigned char ifNum, unsigned char enabled);

    /**
    * Get the number of IP addresses available on the specified interface. If DHCP is enabled on the
    * specified interface then index 0 represents the DHCP address and the following addresses
    * will be any static IP addresses.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @return the number of IP addresses on the specified interface.
    */
    DLL_DECL int odapi_adv_ipv4_get_number_of_ip_addresses(long deviceID, int *errorCode, unsigned char ifNum);

    /**
    * Retrieve the IP address and netmask on the specified interface.
    * If DHCP is enabled on the specified interface then index 0 represents the DHCP address
    * and the following addresses will be any static IP addresses.
    * The IP address is returned as 4 bytes into a user supplied array. The leading part of
    * the IP address will be in the first element of the array, followed by the remaining parts in order
    * to the last part of the IP address in the fourth element of the array.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
    *                                             array size is less than 4.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @param addressIndex the index of the address to be retrieved.
    * @param ipAddress a pointer to the array that will receive the IP address.
    * @param ipAddressLength the size of the array ipAddress.
    * @param netmask a pointer to the netmask specifying the subnet of the network the device is on.
    */
    DLL_DECL void odapi_adv_ipv4_read_ip_address(long deviceID, int *errorCode, unsigned char ifNum, unsigned char addressIndex,
        unsigned char *ipAddress, int ipAddressLength, unsigned int *netmask);

    /**
    * Add a static IP address to the specified interface.
    * The IP address is specified as 4 bytes in an array. The leading part of
    * the IP address must contain the first element of the array, followed by the remaining parts in order
    * to the last part of the IP address in the fourth element of the array.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
    *                                             array size is less than 4.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @param ipAddress the static IP address to be added.
    * @param netmask the netmask specifying the subnet of the network the device is on.
    */
    DLL_DECL void odapi_adv_ipv4_add_static_ip_address(long deviceID, int* errorCode, unsigned char ifNum,
        unsigned char *ipAddress, int ipAddressLength, unsigned int netmask);

    /**
    * Delete a static IP address on the specified interface.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @param addressIndex the index of the address to be deleted.
    */
    DLL_DECL void odapi_adv_ipv4_delete_static_ip_address(long deviceID, int* errorCode, unsigned char ifNum, unsigned char addressIndex);


    /**
    * Set the default gateway IP address to the specified interface.
    * The IP address is specified as 4 bytes in an array. The leading part of
    * the IP address must contain the first element of the array, followed by the remaining parts in order
    * to the last part of the IP address in the fourth element of the array.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
    *                                             array size is less than 4.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @param ipAddress the default gateway IP address to be added.
    * @param ipAddressLength the ip address length.
    */
    DLL_DECL void odapi_adv_ipv4_set_default_gateway_ip_address(long deviceID, int* errorCode, unsigned char ifNum,
                                                                unsigned char* ipAddress, int ipAddressLength);

    /**
    * Get the default gateway IP address to the specified interface.
    * The IP address is specified as 4 bytes in an array. The leading part of
    * the IP address must contain the first element of the array, followed by the remaining parts in order
    * to the last part of the IP address in the fourth element of the array.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
    *                                             array size is less than 4.
    * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
    * @param outIpAddress contains the default gateway IP address.
    * @param ipAddressLength the ip address buffer length.
    */
    DLL_DECL void odapi_adv_ipv4_get_default_gateway_ip_address(long deviceID, int* errorCode, unsigned char ifNum,
                                                                unsigned char* outIpAddress, int ipAddressLength);


    /**
    * @deprecated Enable or disable electric dark correction.
    * @see odapi_set_stored_dark_spectrum
    * @see odapi_get_stored_dark_spectrum
    * @see odapi_get_dark_corrected_spectrum1
    * @see odapi_get_dark_corrected_spectrum2
    *
    * @warning if electric dark correction is enabled using this function then
    * some of the newer dark correction functionality e.g. odapi_get_dark_corrected_spectrum1
    * may not be used.

    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode A code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
    *                                   electric dark correction;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param enable True(1) enable electric dark correction otherwise it's false(0).
    */
    DLL_DECL void odapi_apply_electric_dark_correction_usage(long deviceID, int *error_code, unsigned char enable);

    /**
     * @deprecated This function returns the usage state of electric dark correction.
     * @see odapi_set_stored_dark_spectrum
     * @see odapi_get_stored_dark_spectrum
     * @see odapi_get_dark_corrected_spectrum1
     * @see odapi_get_dark_corrected_spectrum2
     *
     * @param deviceID (Input) The index of a device previously opened with
     *      odapi_open_device().
     * @param error_code (Output) A pointer to an integer that can be used
     *      for storing error codes. This may be NULL in which case no error code is returned.
     *      The error codes returned by this function are:
     *                  ERROR_SUCCESS on success;
     *                  ERROR_COMMAND_NOT_SUPPORTED if the device does not support
     *                                   electric dark correction;
|    *                  ERROR_NO_DEVICE if the device does not exist.
     * @return Returns usage state true/false.
     */
    DLL_DECL bool odapi_get_electric_dark_correction_usage(long deviceID, int *error_code);

    /**
    * Return the number of GPIO pins.
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @return the number of GPIO pins provided by the device.
    */
    DLL_DECL int odapi_adv_get_gpio_pin_count(long deviceID, int* errorCode);

    /**
     * Set the direction (input/output) of a specified GPIO pin.
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @param bit the GPIO pin to set.
     * @param isOutput set to true to make the pin output, false to make the pin input.
    */
    DLL_DECL void odapi_adv_gpio_set_output_enable1(long deviceID, int *errorCode, int bit, bool isOutput);

    /** Set the direction (input/output) of the GPIO pins.
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @param bitmask a bitmask specifying the pin directions i.e. the nth bit set to 1 sets the nth pin to output.
    */
    DLL_DECL void odapi_adv_gpio_set_output_enable2(long deviceID, int *errorCode, uint32_t bitmask);

    /**
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @param bit the GPIO pin to query.
     * @return true if the pin is an output pin, false if the pin is an input pin.
    */
    DLL_DECL bool odapi_adv_gpio_get_output_enable1(long deviceID, int *errorCode, int bit);

    /**
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @return the bitmask specifying the direction of each GPIO pin.
    */
    DLL_DECL uint32_t odapi_adv_gpio_get_output_enable2(long deviceID, int *errorCode);

    /*! Set the logic value for a spcified pin.
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @param bit the GPIO pin to set.
     * @param isHigh set true to set the logic level high, set false to set the logic level low.
    */
    DLL_DECL void odapi_adv_gpio_set_value1(long deviceID, int *errorCode, int bit, bool isHigh);

    /** Set the logic value for all GPIO pins.
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @param bitmask the bitmask specifying the logic level of each GPIO pin.
    */
    DLL_DECL void odapi_adv_gpio_set_value2(long deviceID, int *errorCode, uint32_t bitmask);

    /**
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @param bit the GPIO pin to query.
     * @return true if the specified pin is set to logic level hig, false if the specified pin is set to logic level low.
    */
    DLL_DECL bool odapi_adv_gpio_get_value1(long deviceID, int *errorCode, int bit);

    /**
     * @param deviceID the ID of the device returned by getDeviceIDs.
     * @param errorCode on exit this contains zero on success, nonzero otherwise.
     * @return the bitmask specifying the logic level of each GPIO pin.
    */
    DLL_DECL uint32_t odapi_adv_gpio_get_value2(long deviceID, int *errorCode);

    /**
    * Set the alternate functionality for the specified pin (bit) number. Not
    * all spectrometers support this functionality.
    * 
    * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
    * @param deviceID The ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param bit Which GPIO bit or pin to set
    * @param isAlternate set true to enable the alternate functionality for the pin, false otherwise (pin is a GPIO pin).
    */
    DLL_DECL void odapi_adv_gpio_set_output_alternate1(long deviceID, int* errorCode, int bit, bool isAlternate);

    /**
    * Set the alternate functionality for the specified pins (bits). Not
    * all spectrometers support this functionality.
    *
    * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
    * @param deviceID The ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param bitMask with bit set to 1 to set enable the alternate functionality, 0 otherwise (pin is a GPIO pin).
    */
    DLL_DECL void odapi_adv_gpio_set_output_alternate2(long deviceID, int* errorCode, uint32_t bitMask);

    /**
    * Get the setting for alternate functionality on the specified bit (pin). Not
    * all spectrometers support this functionality.
    *
    * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
    * @param deviceID The ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param bit Which GPIO bit or pin to query.
    * @return true if the pin is set to alternate functionality, false otherwise (pin is a GPIO pin).
    */
    DLL_DECL bool odapi_adv_gpio_get_output_alternate1(long deviceID, int* errorCode, int bit);

    /**
    * Get the settings for alternate functionality on the GPIO pins. Not
    * all spectrometers support this functionality.
    *
    * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
    * @param deviceID The ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @return a bitmask with value 1 where the corresponding pin is set to alternate functionality, 0 otherwise (pin is a GPIO pin).
    */
    DLL_DECL uint32_t odapi_adv_gpio_get_output_alternate2(long deviceID, int* errorCode);




    /**
    * Read the number of supported communication interface. This function only applies to HDX/FX devices.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @return The number of interface.
    */
    DLL_DECL uint32_t odapi_adv_network_conf_get_interface_count(long deviceID, int* errorCode);

    /**
    * Return the interface type of the given interface index. This function only applies to HDX/FX devices.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The interface to look at.
    * @return The interface type which could be one 0(Loopback), 1(wired ethernet), 2 (WIFI), and 3 (USB - CDC Ethernet).
    */
    DLL_DECL uint32_t odapi_adv_network_conf_get_interface_type(long deviceID, int* errorCode, unsigned int interfaceIndex);

    /**
    * Return true if the interface is enabled otherwise it's false. This function only applies to HDX/FX devices.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The interface to look at.
    * @return True if the interface if enabled otherwise it's False.
    */
    DLL_DECL bool odapi_adv_network_conf_get_interface_status(long deviceID, int* errorCode, unsigned int interfaceIndex);

    /**
    * Enable or disable the interface. This function only applies to HDX/FX devices.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The interface to look at.
    * @param enable True will enable the interface. False will disable it.
    */
    DLL_DECL void odapi_adv_network_conf_set_interface_status(long deviceID, int* errorCode, unsigned int interfaceIndex, bool enable);

    /**
    * Return true if the multicast group message is enabled otherwise it's false. This function only applies to HDX/FX devices.
    *
    * @param deviceID[in] the ID of the device returned by getDeviceIDs.
    * @param errorCode[out] a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param interfaceIndex[in] The interface to look at.
    * @return True if it's enabled otherwise it's False.
    */
    DLL_DECL bool odapi_adv_network_conf_get_multicast_group_enabled(long deviceID, int* errorCode, unsigned int interfaceIndex);
    
    /**
    * Enable or disable the multicast message group. This function only applies to HDX/FX devices.
    *
    * @param deviceID[in] the ID of the device returned by getDeviceIDs.
    * @param errorCode[out] a code indicating the result of the operation:
    *                  ERROR_SUCCESS on success;
    *                  ERROR_NO_DEVICE if the device does not exist;
    *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
    *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
    *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
    * @param interfaceIndex[in] The interface to look at.
    * @param enable[in] True will enable the multicast group message. False will disable it.
    */
    DLL_DECL void odapi_adv_network_conf_set_multicast_group_enabled(long deviceID, int* errorCode, unsigned int interfaceIndex, bool enable);



    /**
    * Save the network interface settings to the device. This function only applies to HDX/FX devices.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The interface to save to.
    */
    DLL_DECL void odapi_adv_network_conf_save_interface_setting(long deviceID, int* errorCode, unsigned int interfaceIndex);

    /**
    * Return the status on whether the gigabit ethernet is enabled or not. This function only applies to HDX/FX devices.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The ethernet interface to look at.
    * @return The interface status.
    */
    DLL_DECL bool odapi_adv_ethernet_get_gigabit_enable_status(long deviceID, int* errorCode, unsigned int interfaceIndex);

    /**
    * Enable or disable the gigabit ethernet the status. This function only applies to HDX/FX devices.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The ethernet interface to look at.
    * @param enable True will enable gigabit ethernet.
    */
    DLL_DECL void odapi_adv_ethernet_set_gigabit_enable_status(long deviceID, int* errorCode, unsigned int interfaceIndex, bool enable);

    /**
    * Read the ethernet 6-byte mac address from the spectrometer. This function only applies to HDX/FX devices.
    *
    * @attention  For devices with a single interface, the interfaceIndex parameter is ignored.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The ethernet interface to look at.
    * @param macAddress The output buffer for mac address.
    * @param macAddressLength The buffer length must be at least 6-bytes long.
    */
    DLL_DECL void odapi_adv_ethernet_get_mac_address(long deviceID, int* errorCode, unsigned int interfaceIndex, unsigned char* macAddress, int macAddressLength);

    /**
    * Writes a new ethernet 6-byte mac address into the spectrometer. This function only applies to HDX/FX devices.
    *
    * @attention  For devices with a single interface, the interfaceIndex parameter is ignored.
    *
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param interfaceIndex The ethernet interface to look at.
    * @param macAddress The new mac address.
    * @param macAddressLength The mac address length must be 6-bytes long.
    */
    DLL_DECL void odapi_adv_ethernet_set_mac_address(long deviceID, int* errorCode, uint32_t interfaceIndex, unsigned char* macAddress, int macAddressLength);

    //OBP2 Commands
    /**
    * Read the IP address mode from the OBP2 device.
    * @see odapi_adv_set_ip_address_assigned_mode()
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @return True if the ip address was generated via DHCP. False if the ip address was statically assigned.
    */
    DLL_DECL unsigned char odapi_adv_get_ip_address_assigned_mode(long deviceID, int* errorCode);

    /**
    * Set the IP address mode to the OBP2 device.
    * @see odapi_adv_set_ip_address_assigned_mode()
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param useDHCP[in] True will use DHCP server for ip assignment. False will use statically assigned IP address.
    */
    DLL_DECL void odapi_adv_set_ip_address_assigned_mode(long deviceID, int* errorCode, unsigned char useDHCP);

    /**
    * Read the network configuration parameters from an OBP2 enabled device.
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param outIpAddressAssignment[out] True if the IPv4 address is DHCP generated otherwise it's False.
    * @param outIpv4Address[out] Output buffer for the IPv4 address.
    * @param ipv4AddressSize[in] The ipv4 address buffer size.
    * @param outSubnetMask[out] Output buffer for the subnet mask.
    * @param subnetMaskSize[in] The subnet mask buffer size.
    * @param outDefaultGateway[out] Output buffer for the default gateway
    * @param defaultGatewaySize[in] The default gateway buffer size.
    * @param outDNSServer[out]  Output buffer for the DNS server.
    * @param dnsServerSize[in]  The dns server buffer size.
    */
    DLL_DECL void odapi_adv_get_network_configuration(long deviceID, int* errorCode, unsigned char* outIpAddressAssignment,
                                             unsigned char* outIpv4Address, unsigned int ipv4AddressSize,
                                             unsigned char* outSubnetMask, unsigned int subnetMaskSize,
                                             unsigned char* outDefaultGateway, unsigned int defaultGatewaySize,
                                             unsigned char* outDNSServer, unsigned int dnsServerSize);
    
    /**
    * Write the network configuration parameters (static ip address) on OBP2 enabled device.
    * @see odapi_adv_get_manual_network_configuration()
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param ipv4Address[in] The IPv4 address.
    * @param ipv4AddressSize[in] The ipv4 address buffer size.
    * @param subnetMask[in] The subnet mask.
    * @param subnetMaskSize[in] The subnet mask buffer size.
    * @param defaultGateway[in] The default gateway
    * @param defaultGatewaySize[in] The default gateway buffer size.
    * @param dnsServer[in]  The DNS server.
    * @param dnsServerSize[in]  The dns server buffer size.
    */
    DLL_DECL void odapi_adv_set_manual_network_configuration(long deviceID, int* errorCode,
                                              unsigned char* ipv4Address, unsigned int ipv4AddressSize,
                                              unsigned char* subnetMask, unsigned int subnetMaskSize,
                                              unsigned char* defaultGateway, unsigned int defaultGatewaySize,
                                              unsigned char* dnsServer, unsigned int dnsServerSize);

    /**
    * Read the network configuration parameters (static ip address) from an OBP2 enabled device.
    * @see odapi_adv_set_manual_network_configuration()
    * @param deviceID the ID of the device returned by getDeviceIDs.
    * @param errorCode on exit this contains zero on success, nonzero otherwise.
    * @param outIpv4Address[out] Output buffer for the IPv4 address.
    * @param ipv4AddressSize[in] The ipv4 address buffer size.
    * @param outSubnetMask[out] Output buffer for the subnet mask.
    * @param subnetMaskSize[in] The subnet mask buffer size.
    * @param outDefaultGateway[out] Output buffer for the default gateway
    * @param defaultGatewaySize[in] The default gateway buffer size.
    * @param outDNSServer[out]  Output buffer for the DNS server.
    * @param dnsServerSize[in]  The dns server buffer size.
    */
    DLL_DECL void odapi_adv_get_manual_network_configuration(long deviceID, int* errorCode,
                                            unsigned char* outIpv4Address, unsigned int ipv4AddressSize,
                                            unsigned char* outSubnetMask, unsigned int subnetMaskSize,
                                            unsigned char* outDefaultGateway, unsigned int defaultGatewaySize,
                                            unsigned char* outDNSServer, unsigned int dnsServerSize);
#endif /* excluding C interface */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* OCEAN_DIRECT_API_H */
