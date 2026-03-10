/*****************************************************
 * @file    DataBufferAPI.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to connect to devices over USB and other buses.
 * This is intended as a usable and extensible API.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2022] Ocean Insight Incorporated
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

#ifndef DATA_BUFFER_API_H
#define DATA_BUFFER_API_H

#include "api/DllDecl.h"

/*!
@brief  This is an interface to advanced features of
    OceanDirect that allow access to less common
    controls. This is intended as a usable and
    extensible API.
*/
namespace oceandirect {
    namespace api {

        class DLL_DECL DataBufferAPI {
        public:
            DataBufferAPI();
            virtual ~DataBufferAPI() = default;
            static DataBufferAPI *getInstance();

            static void shutdown();

            /**
            * Clear the device buffer.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            */
            virtual void clearBuffer(long deviceID, int *errorCode);

            /**
            * 
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            */
            virtual unsigned long getNumberOfElements(long deviceID, int *errorCode);

            /**
            * Get the current buffer capacity.
            * @see setBufferCapacity()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the current buffer capacity.
            */
            virtual unsigned long getBufferCapacity(long deviceID, int *errorCode);

            /**
            * Get the maximum current buffer capacity.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the maximum buffer capacity.
            */
            virtual unsigned long getBufferCapacityMaximum(long deviceID, int *errorCode);

            /**
            * Get the minimum current buffer capacity.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the minimum buffer capacity.
            */
            virtual unsigned long getBufferCapacityMinimum(long deviceID, int *errorCode);

            /**
            * Set the current buffer capacity.
            * @see getBufferCapacity()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param capacity the desired buffer capacity.
            */
            virtual void setBufferCapacity(long deviceID, int *errorCode, unsigned long capacity);

            /**
            * Enable or disable buffering.
            * @see getBufferEnabled()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param enabled true to enable buffering, false to disable buffering.
            */
            virtual void setBufferEnabled(long deviceID, int *errorCode, bool enabled);

            /**
            * Determine if buffering is enabled or disabled.
            * @see setBufferEnabled()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return true if buffering is enabled, false otherwise.
            */
            virtual bool getBufferEnabled(long deviceID, int *errorCode);

        protected:
            static DataBufferAPI *instance;
        };
    }
}
#endif /* DATA_BUFFER_API_H */
