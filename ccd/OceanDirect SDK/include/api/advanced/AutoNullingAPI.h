/*****************************************************
 * @file    AutoNullingAPI.h
 * @date    April 2021
 * @author  Ocean Optics, Inc.
 *
 * This is an interface to OceanDirect that allows  the user to read and write autonulling 
 * information (basleine, saturation level, maximum ADC count) from/to the device.
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

#ifndef AUTONULLING_API_H
#define AUTONULLING_API_H

#include "api/DllDecl.h"

 /*!
    @brief  This is an interface to advanced features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
            extensible API.
 */
namespace oceandirect {
    namespace api {

        class DLL_DECL AutoNullingAPI {
        public:
            AutoNullingAPI();
            virtual ~AutoNullingAPI();
            static AutoNullingAPI *getInstance();

            static void shutdown();

            /**
            * Get the maximum ADC value.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the maximum ADC value.
            */
            virtual int getMaximumADCCount(long deviceID, int * errorCode);

            /**
            * Get the current saturation level.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the saturation level.
            */
            virtual int getSaturationLevel(long deviceID, int * errorCode);

            /**
            * Get the current baseline level.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the baseline level.
            */
            virtual int getBaselineLevel(long deviceID, int * errorCode);

            /**
            * Get the current FPGA digital gain.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the gain value.
            */
            virtual int getFPGADigitalGain(long deviceID, int* errorCode);

            /**
            * Get the current FPGA digital offset.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the offset value.
            */
            virtual int getFPGADigitalOffset(long deviceID, int* errorCode);

            /**
            * Get autonulling constraints value for baseline settings. This command only applies to Ocean FX/HDX units.
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
            virtual void getBaselineLevelConstraints(long deviceID, int* errorCode, unsigned int* minDAC, unsigned int* maxDAC, float* minVolts, float* maxVolts);

            /**
            * Get autonulling constraints value for saturation settings. This command only applies to Ocean FX/HDX units.
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
            virtual void getSaturationLevelConstraints(long deviceID, int* errorCode, unsigned int* minDAC, unsigned int* maxDAC, float* minVolts, float* maxVolts);

        protected:
            static AutoNullingAPI *instance;

        };
    }
}
#endif /* AUTONULLING_API_H */
