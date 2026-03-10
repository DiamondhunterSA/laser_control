/*****************************************************
 * @file    BackToBackAPI.h
 * @date    December 2019
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

#ifndef BACKTOBACKAPI_H
#define BACKTOBACKAPI_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
	namespace api {

		class DLL_DECL BackToBackAPI {
		public:
			BackToBackAPI();
			virtual ~BackToBackAPI();
			static BackToBackAPI *getInstance();

			static void shutdown();

			/**
			* Get the current number of back to back scans.
			* @see setNumberOfBackToBackScans()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @return the current number of back to back scans.
			*/
			virtual unsigned long getNumberOfBackToBackScans(long deviceID, int *errorCode);

			/**
			* Set the current number of back to back scans.
			* @see getNumberOfBackToBackScans()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param numScans the desired number of back to back scans.
			*/
			virtual void setNumberOfBackToBackScans(long deviceID, int *errorCode, unsigned long numScans);

		protected:
			static BackToBackAPI *instance;

		};
	}
}
#endif /* BACKTOBACKAPI_H */
