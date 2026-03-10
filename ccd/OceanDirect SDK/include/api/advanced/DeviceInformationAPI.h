/*****************************************************
 * @file    DeviceInformationAPI.h
 * @date    April 2021
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows  the user to read and write 
 * device information such as VID, PID, model,  manufacturer info, etc.
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

#ifndef DEVICE_INFORMATION_API_H
#define DEVICE_INFORMATION_API_H

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

        class DLL_DECL DeviceInformationAPI {
        public:
            DeviceInformationAPI();
            virtual ~DeviceInformationAPI();
            static DeviceInformationAPI *getInstance();

            static void shutdown();

            virtual void resetDevice(long deviceID, int *errorCode);

            virtual std::uint16_t getOriginalUsbVID(long deviceID, int *errorCode);
            virtual std::uint16_t getOriginalUsbPID(long deviceID, int *errorCode);
            virtual std::uint16_t getUsbVID(long deviceID, int *errorCode);
            virtual void setUsbVID(long deviceID, int *errorCode, std::uint16_t vid);
            virtual std::uint16_t getUsbPID(long deviceID, int *errorCode);
            virtual void setUsbPID(long deviceID, int *errorCode, std::uint16_t pid);

            virtual int getOriginalManufacturerString(long deviceID, int *errorCode, char *buffer, int bufferLength);
            virtual int getOriginalModelString(long deviceID, int *errorCode, char *buffer, int bufferLength);
            virtual int getManufacturerString(long deviceID, int *errorCode, char *buffer, int bufferLength);
            virtual void setManufacturerString(long deviceID, int *errorCode, char *buffer, int bufferLength);
            virtual int getModelString(long deviceID, int *errorCode, char *buffer, int bufferLength);
            virtual void setModelString(long deviceID, int *errorCode, char *buffer, int bufferLength);

        protected:
            static DeviceInformationAPI *instance;
        };
    }
}
#endif /* DEVICE_INFORMATION_API_H */
