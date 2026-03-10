/*****************************************************
 * @file    NonLinearityAPI.h
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

#ifndef NONLINEARITYAPI_H
#define NONLINEARITYAPI_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
	namespace api {

		class DLL_DECL NonLinearityAPI {
		public:
			NonLinearityAPI();
			virtual ~NonLinearityAPI();
			static NonLinearityAPI *getInstance();
			static void shutdown();

            /**
            * Get the number of nonlinearity correction coefficients.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @return the number of nonlinearity coefficients.
            */
            virtual int getCoeffsCount(long deviceID, int *errorCode);

            /**
            * Get the specified of nonlinearity correction coefficient.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param index the index of the desired coefficient.
            * @return the value of the specified nonlinearity coefficient.
            */
            virtual double getCoeffs(long deviceID, int *errorCode, int index);

            /**
            * Get the nonlinearity correction coefficients.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param buffer the buffer to receive the nonlinearity coefficients.
            * @param maxLength the size of the buffer.
            * @return the number nonlinearity coefficients received.
            */
            virtual int getCoeffs(long deviceID, int *errorCode, double *buffer, int maxLength);

		protected:

			static NonLinearityAPI *instance;

		};
	}
}
#endif /* NONLINEARITYAPI_H */
