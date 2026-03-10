/*****************************************************
 * @file    PixelAPI.h
 * @date    March 2021
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

#ifndef PIXEL_API_H
#define PIXEL_API_H

#include "api/DllDecl.h"

 /*!
    @brief  This is an interface to advanced features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
            extensible API.
 */
namespace oceandirect {
    namespace api {

        class DLL_DECL PixelAPI {
        public:
            PixelAPI();
            virtual ~PixelAPI();
            static PixelAPI *getInstance();

            static void shutdown();

            /**
            * Get the total number of pixels.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the total number of pixels.
            */
            virtual int getPixelCount(long deviceID, int *error_code);

            virtual int getActivePixelCount(long deviceID, int* error_code);

            /**
            * Get the optically active pixel indices.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param range the buffer to receive the optically active pixel indices.
            * @param rangeSize the size of the buffer.
            * @return the number of optically active pixels.
            */
            virtual int getActivePixelRange(long deviceID, int *error_code, int *range, int rangeSize);

            virtual int getOpticalDarkPixelCount(long deviceID, int* error_code);

            /**
            * Get the optically dark pixel indices.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param range the buffer to receive the optically dark pixel indices.
            * @param rangeSize the size of the buffer.
            * @return the number of optically dark pixels.
            */
            virtual int getOpticalDarkPixelRange(long deviceID, int *error_code, int *range, int rangeSize);

            virtual int getTransitionPixelCount(long deviceID, int* error_code);

            /**
            * Get the transition pixel indices.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param range the buffer to receive the transition pixel indices.
            * @param rangeSize the size of the buffer.
            * @return the number of transition pixels.
            */
            virtual int getTransitionPixelRange(long deviceID, int *error_code, int *range, int rangeSize);

            /**
            * Get the pixel indices of the pixels marked as "bad" e.g. hot pixels.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param badPixelIndices the buffer to receive the bad pixel indices.
            * @param badPixelSize the size of the buffer.
            * @return the number of bad pixels.
            */
            virtual int getBadPixelIndices(long deviceID, int *error_code, int *badPixelIndices, int badPixelSize);

            /**
            * Set the pixel indices of the pixels marked as "bad" e.g. hot pixels.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param badPixelIndices the bad pixel indices.
            * @param badPixelSize the size of the buffer.
            */
            virtual void setBadPixelIndices(long deviceID, int* error_code, int* badPixelIndices, int badPixelSize);

        protected:
            static PixelAPI *instance;

        };
    }
}
#endif /* PIXEL_API_H */
