/*****************************************************
 * @file    DeviceAliasAPI.h
 * @date    April 2021
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows the user to read 
 * and write device alias to the unit.
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

#ifndef DEVICE_ALIAS_API_H
#define DEVICE_ALIAS_API_H

#include "api/DllDecl.h"

 /*!
    @brief  This is an interface to advanced features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
            extensible API.
 */
namespace oceandirect {
	namespace api {

        class DLL_DECL DeviceAliasAPI {
        public:
            DeviceAliasAPI();
            virtual ~DeviceAliasAPI();
            static DeviceAliasAPI *getInstance();

            static void shutdown();

            /**
            * Get the device alias of the device.
            * @see setDeviceAlias()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param buffer the buffer to receive the device alias.
            * @param bufferLength the length of the buffer.
            * @return the number of bytes read.
            */
            virtual int getDeviceAlias(long deviceID, int* errorCode, char* buffer, int bufferLength);

            /**
            * Set the device alias of the device.
            * @see getDeviceAlias()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param buffer the buffer containing the desired device alias.
            * @param bufferLength the length of the buffer.
            */
            virtual void setDeviceAlias(long deviceID, int *errorCode, char *buffer, int bufferLength);

        protected:
            static DeviceAliasAPI *instance;
        };
    }
}
#endif /* DEVICE_ALIAS_API_H */
