/*****************************************************
 * @file    UserStringAPI.h
 * @date    January 2022
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to read and write user strin to device.
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

#ifndef USER_STRING_API_H
#define USER_STRING_API_H

#include "api/DllDecl.h"

 /*!
    @brief  This is an interface to advanced features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
            extensible API.
 */
namespace oceandirect {
	namespace api {

        class DLL_DECL UserStringAPI {
        public:
            UserStringAPI();
            virtual ~UserStringAPI();
            static UserStringAPI *getInstance();

            static void shutdown();

            /**
            * Read the user string from the device. If this field in the device is not yet 
            * populated then a non-zero(6) code will be returned.
            * @see setUserString()
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
            virtual int getUserString(long deviceID, int *errorCode, char *buffer, int bufferLength);

            /**
            * Write the user string to the device. The maximum string length is 16.
            * @see getUserString()
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
            virtual void setUserString(long deviceID, int *errorCode, char *buffer, int bufferLength);

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
            virtual int getUserStringCount(long deviceID, int *errorCode);

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
            virtual int getUserString(long deviceID, int *errorCode, int index, char *buffer, int bufferLength);

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
            virtual void setUserString(long deviceID, int *errorCode, int index, char *buffer, int bufferLength);

        protected:
            static UserStringAPI *instance;
        };
    }
}
#endif /* USER_STRING_API_H */
