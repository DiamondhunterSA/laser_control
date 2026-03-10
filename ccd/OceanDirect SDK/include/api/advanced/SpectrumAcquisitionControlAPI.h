/*****************************************************
 * @file    SpectrumAcquisitionControlAPI.h
 * @date    December 2021
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

#ifndef SPECTRUM_ACQUISITION_CONTROL_API_H
#define SPECTRUM_ACQUISITION_CONTROL_API_H

#include "api/DllDecl.h"

 /*!
    @brief  This is an interface to advanced features of OceanDirect that allow access to less common
            controls. This is intended as a usable and extensible API.
 */
namespace oceandirect {
    namespace api {

        class DLL_DECL SpectrumAcquisitionControlAPI {
        public:
            SpectrumAcquisitionControlAPI();
            virtual ~SpectrumAcquisitionControlAPI();
            static SpectrumAcquisitionControlAPI *getInstance();

            static void shutdown();

            /**
            * Get the idle state of the spectrometer.
            * @see setAbortAcquisition()
            * @see setAcquireSpectraToBuffer()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return true if the device is idle, false otherwise.
            */
            virtual bool getDeviceIdleState(long deviceID, int *errorCode);

            /**
            * Abort any current acquisition.
            * @see getDeviceIdleState()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            */
            virtual void setAbortAcquisition(long deviceID, int *errorCode);

            /**
            * Start acquisition into the buffer.
            * @see getDeviceIdleState()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            */
            virtual void setAcquireSpectraToBuffer(long deviceID, int *errorCode);

        protected:
            static SpectrumAcquisitionControlAPI *instance;
        };
    }
}
#endif /* SPECTRUM_ACQUISITION_CONTROL_API_H */
