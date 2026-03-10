/*****************************************************
 * @file    ContinuousStrobeAPI.h
 * @date    January 2020
 * @author  Ocean Insight, Inc.
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

#ifndef CONTINSTROBEAPI_H
#define CONTINSTROBEAPI_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
	namespace api {

		class DLL_DECL ContinuousStrobeAPI {
		public:
			ContinuousStrobeAPI();
			virtual ~ContinuousStrobeAPI();
			static ContinuousStrobeAPI *getInstance();

			static void shutdown();

            /**
            * Get the continuous strobe period in microseconds.
            * @see setStrobePeriodMicroseconds()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the continuous strobe period in microseconds.
            */
            virtual unsigned long getContinuousStrobePeriodMicroseconds(long deviceID, int *errorCode);

            /**
            * Determine if continuous strobe is enabled or disabled.
            * @see setStrobeEnable()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return true if continuous strobe is enabled, false otherwise.
            */
            virtual bool getContinuousStrobeEnable(long deviceID, int *errorCode);

            /**
            * Get the minimum continuous strobe period in microseconds.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the minimum continuous strobe period in microseconds.
            */
            virtual unsigned long getContinuousStrobePeriodMinimumMicroseconds(long deviceID, int *errorCode);

            /**
            * Get the maximum continuous strobe period in microseconds.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the maximum continuous strobe period in microseconds.
            */
            virtual unsigned long getContinuousStrobePeriodMaximumMicroseconds(long deviceID, int *errorCode);

            /**
            * Get the continuous strobe period increment in microseconds i.e. the minimum time between
            * adjacent valid continuous strobe period.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the continuous strobe period increment in microseconds.
            */
            virtual unsigned long getContinuousStrobePeriodIncrementMicroseconds(long deviceID, int *errorCode);

            /**
            * Get the maximum continuous strobe period in microseconds.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the maximum continuous strobe period in microseconds.
            */

            /**
            * Get the continuous strobe width in microseconds.
            * @see setContinuousStrobeWidthMicroseconds()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the continuous strobe width in microseconds.
            */
            virtual unsigned long getContinuousStrobeWidthMicroseconds(long deviceID, int *errorCode);

            /**
            * Enable or disable continuous strobe.
            * @see getContinuousStrobeEnable()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param strobeEnable true to enable continuous strobe, false to disable continuous strobe.
            */
            virtual void setStrobeEnable(long deviceID, int *errorCode, bool strobeEnable);

            /**
            * Set the continuous strobe period in microseconds.
            * @see getContinuousStrobePeriodMicroseconds()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param strobePeriodMicroseconds the continuous strobe period in microseconds.
            */
            virtual void setStrobePeriodMicroseconds(long deviceID, int *errorCode, unsigned long strobePeriodMicroseconds);

            /**
            * Set the continuous strobe width in microseconds.
            * @see getContinuousStrobeWidthMicroseconds()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param strobeWidthMicroseconds the continuous strobe width in microseconds.
            */
            virtual void setContinuousStrobeWidthMicroseconds(long deviceID, int *errorCode, unsigned long strobeWidthMicroseconds);

		protected:
			static ContinuousStrobeAPI *instance;
		};
	}
}
#endif /* CONTINSTROBEAPI_H */
