/*****************************************************
 * @file    SingleStrobeAPI.h
 * @date    October 2019
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

#ifndef SINGLE_STROBE_API_H
#define SINGLE_STROBE_API_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
	namespace api {

		class DLL_DECL SingleStrobeAPI {
		public:
			SingleStrobeAPI();
			virtual ~SingleStrobeAPI();
			static SingleStrobeAPI *getInstance();

			static void shutdown();

			/**
			* Enable or disable strobe.
			* @see getStrobeEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param strobeEnable true to enable strobe, false to disable strobe.
			*/
			virtual void setStrobeEnable(long deviceID, int *errorCode, bool strobeEnable);

			/**
			* Set the strobe delay in microseconds.
			* @see getStrobeDelayMicroseconds()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param microseconds the strobe delay in microseconds.
			*/
			virtual void setStrobeDelayMicroseconds(long deviceID, int *errorCode, unsigned long microseconds);

			/**
			* Set the strobe width in microseconds.
			* @see getStrobeWidthMicroseconds()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param microseconds the strobe width in microseconds.
			*/
			virtual void setStrobeWidthMicroseconds(long deviceID, int *errorCode, unsigned long microseconds);

			/**
			* Determine if strobe is enabled.
			* @see setStrobeEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return true if strobe is enabled, false otherwise.
			*/
			virtual bool getStrobeEnable(long deviceID, int *errorCode);

			/**
			* Get the strobe delay in microseconds.
			* @see setStrobeDelayMicroseconds()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the strobe delay in microseconds.
			*/
			virtual unsigned long getStrobeDelayMicroseconds(long deviceID, int *errorCode);

			/**
			* Get the strobe width in microseconds.
			* @see setStrobeWidthMicroseconds()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the strobe width in microseconds.
			*/
			virtual unsigned long getStrobeWidthMicroseconds(long deviceID, int *errorCode);

			/**
			* Get the minimum strobe delay in microseconds.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the minimum strobe delay in microseconds.
			*/
			virtual unsigned long getStrobeDelayMinimumMicroseconds(long featureID, int *errorCode);

			/**
			* Get the maximum strobe delay in microseconds.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the maximum strobe delay in microseconds.
			*/
			virtual unsigned long getStrobeDelayMaximumMicroseconds(long featureID, int *errorCode);

			/**
			* Get the minimum strobe width in microseconds.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the minimum strobe width in microseconds.
			*/
			virtual unsigned long getStrobeWidthMinimumMicroseconds(long featureID, int *errorCode);

			/**
			* Get the maximum strobe width in microseconds.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the maximum strobe width in microseconds.
			*/
			virtual unsigned long getStrobeWidthMaximumMicroseconds(long featureID, int *errorCode);

			/**
			* Get the maximum strobe cycle in microseconds.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the maximum strobe cycle in microseconds.
			*/
			virtual unsigned long getStrobeCycleMaximumMicroseconds(long featureID, int *errorCode);

			/**
			* Get the strobe delay increment i.e. the minimum time between adjacent, valid strobe delays in microseconds.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the strobe delay ncrement in microseconds.
			*/
			virtual unsigned long getStrobeDelayIncrementMicroseconds(long featureID, int *errorCode);

			/**
			* Get the strobe width increment i.e. the minimum time between adjacent, valid strobe width in microseconds.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the strobe width increment in microseconds.
			*/
			virtual unsigned long getStrobeWidthIncrementMicroseconds(long featureID, int *errorCode);

		protected:

			static SingleStrobeAPI *instance;

		};
	}
}
#endif /* SINGLE_STROBE_API_H */
