/*****************************************************
 * @file    LightSourceAPI.h
 * @date    October 2018
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

#ifndef LIGHTSOURCEAPI_H
#define LIGHTSOURCEAPI_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
	namespace api {

		class DLL_DECL LightSourceAPI {
		public:
			LightSourceAPI();
			virtual ~LightSourceAPI();
			static LightSourceAPI *getInstance();

			static void shutdown();

			/**
			* Gets the number of light sources that are connected to the given device.
			* Such light sources could be individual LEDs, light bulbs, lasers, etc.
			* Each of these light sources may have different capabilities, such as programmable
			* intensities and enables, which should be queried before they are used.
			*
			* @param deviceID the device ID for the device to be queried (from OceanDirect::findDevices())
			* @param errorCode set to 0 if successful, an OceanDirect error code (nonzero) otherwise
			*
			* @return number of light sources connected to the given device
			*/
			virtual int getCount(long deviceID, int* errorCode);

			/**
			* Determine if the specified light source has enable/disable functionality.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param lightSourceIndex the index of the specified light source.
			* @return true if the light source has enable/disable capability, false otherwise.
			*/
			virtual bool hasEnable(long deviceID, int *errorCode, int lightSourceIndex);

			/**
			* Determine if the specified light source is enabled or disabled.
			* @see setEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param lightSourceIndex the index of the specified light source.
			* @return true if the light source is enabled, false if the light source is disabled.
			*/
			virtual bool isEnabled(long deviceID, int *errorCode, int lightSourceIndex);

			/**
			* Set the specified light source to enabled or disabled.
			* @see isEnabled()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param lightSourceIndex the index of the specified light source.
			* @param enable true to enable the light source, false to disable the light source.
			*/
			virtual void setEnable(long deviceID, int *errorCode, int lightSourceIndex, bool enable);

			/**
			* Set strobe enable.
			* @see getLampStrobeEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param strobeEnable true to set strobe enable, false to disable.
			*/
			virtual void setLampStrobeEnable(long deviceID, int *errorCode, bool strobeEnable);

			/**
			* Get strobe enable.
			* @see setLampStrobeEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return true if strobe is enabled, false otherwise.
			*/
			virtual bool getLampStrobeEnable(long deviceID, int *errorCode);

		protected:

			static LightSourceAPI *instance;

		};
	}
}
#endif /* LIGHTSOURCEAPI_H */
