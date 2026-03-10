/*****************************************************
 * @file    ThermoElectricAPI.h
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

#ifndef THERMOELECTRICAPI_H
#define THERMOELECTRICAPI_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
	namespace api {

		class DLL_DECL ThermoElectricAPI {
		public:
			ThermoElectricAPI();
			virtual ~ThermoElectricAPI();
			static ThermoElectricAPI *getInstance();

			static void shutdown();
			/**
			* Read the current TEC temperature in degrees Celcius.
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the temperature in degrees Celcius.
			*/
			virtual float getTemperatureDegreesC(long deviceID, int *errorCode); // all

			/**
			* Set the current TEC temperature setpoint in degrees Celcius.
			* @see getTemperatureSetpointDegreesC()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param temperatureDegreesCelsius the desired setpoint in degress Celcius.
			*/
			virtual void setTemperatureSetpointDegreesC(long deviceID, int *errorCode, float temperatureDegreesCelsius); // all

			/**
			* Enable or disable the TEC.
			* @see getEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param tecEnable true to enable the TEC, false to disabel the TEC.
			*/
			virtual void setEnable(long deviceID, int *errorCode, unsigned char tecEnable); // all
            
			/**
			* Determine if the TEC is enabled or disabled.
			* @see setEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return true if the TEC is enabled, false otherwise.
			*/
			virtual bool getEnable(long deviceID, int *errorCode); //qe pro

			/**
			* Get the current TEC setpoint in degrees Celcius
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the TEC setpoint inf degrees Celcius.
			*/
			virtual float getTemperatureSetpointDegreesC(long deviceID, int *errorCode); // qe pro

			/**
			* Determine if the TEC has reached as stable temperature.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return true if the TEC temperature is stable, false otherwise.
			*/
			virtual bool getStable(long deviceID, int *errorCode); // qe pro

			/**
			* Determine if the TEC fan is enabled.
			*
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return true if the TEC fan is enabled, false otherwise.
			*/
			virtual bool getFanEnable(long deviceID, int *errorCode); // neither

		protected:

			static ThermoElectricAPI *instance;

		};
	}
}
#endif /* THERMOELECTRICAPI_H */
