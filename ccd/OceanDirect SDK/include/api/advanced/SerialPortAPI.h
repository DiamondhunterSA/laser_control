/*****************************************************
 * @file    SerialPortAPI.h
 * @date    April 2021
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to read and write serial port baud rate to device.
 * This is intended as a usable and extensible API.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2021] Ocean Insight Incorporated
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

#ifndef SERIAL_PORT_API_H
#define SERIAL_PORT_API_H

#include "api/DllDecl.h"
#include <cstdint>

 /*!
    @brief  This is an interface to advanced features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
            extensible API.
 */
namespace oceandirect {
	namespace api {

        class DLL_DECL SerialPortAPI {
        public:
            SerialPortAPI();
            virtual ~SerialPortAPI();
            static SerialPortAPI *getInstance();

            static void shutdown();

            /**
            * Get the baud rate of the serial port.
            * @see setBaudRate()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the baud rate of the serial port.
            */
            virtual int getBaudRate(long deviceID, int *errorCode);

            /**
            * Set the baud rate of the serial port.
            * @see getBaudRate()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param baudRate the desired baud rate of the serial port.
            */
            virtual void setBaudRate(long deviceID, int *errorCode, int baudRate);

            /**
            * Save settings to flash memory.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            */
            virtual void saveSettingsToFlash(long deviceID, int *errorCode);

            /**
            * Get the threshold mode of serial communication. The valid supported values are 0x10(RS-232) and 0x20(UART).
            * @see setSerialCommThresholdMode()
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                          ERROR_SUCCESS on success;
            *                          ERROR_NO_DEVICE the specified device ID could not be found;
            *                          ERROR_TRANSFER_ERROR if an error transferring the command to the device occurred;
            *                          ERROR_COMMAND_NOT_SUPPORTED if this operation is not supported by the device.
            * @return The threshold mode either 0x10 or 0x20.
            */
            virtual std::uint8_t getSerialCommThresholdMode(long deviceID, int* errorCode);

            /**
            * Set the threshold mode of serial communication. The valid supported values are 0x10(RS-232) and 0x20(UART).
            * @see getSerialCommThresholdMode()
            * @param deviceID the identifier of the device as returned by getDeviceIDs.
            * @param thresholdMode The threshold mode either 0x10 or 0x20.
            * @param errorCode a code indicating the result of the operation:
            *                          ERROR_SUCCESS on success;
            *                          ERROR_NO_DEVICE the specified device ID could not be found;
            *                          ERROR_TRANSFER_ERROR if an error transferring the command to the device occurred;
            *                          ERROR_COMMAND_NOT_SUPPORTED if this operation is not supported by the device.
            */
            virtual void setSerialCommThresholdMode(long deviceID, int* errorCode, std::uint8_t thresholdMode);
        protected:
            static SerialPortAPI *instance;
        };
    }
}
#endif /* SERIAL_PORT_API_H */
