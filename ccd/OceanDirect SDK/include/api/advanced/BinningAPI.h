/*****************************************************
 * @file    BinningAPI.h
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

#ifndef BINNINGAPI_H
#define BINNINGAPI_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
	namespace api {

		class DLL_DECL BinningAPI {
		public:
			BinningAPI();
			virtual ~BinningAPI();
			static BinningAPI *getInstance();

			static void shutdown();

			/* Pixel binning capabilities */
			void setFactor(long deviceID, int *errorCode, const unsigned char binningFactor);
			unsigned char getFactor(long deviceID, int *errorCode);
			void setDefaultFactor(long deviceID, int *errorCode);
			void setDefaultFactor2(long deviceID, int *errorCode, const unsigned char binningFactor);
			unsigned char getDefaultFactor(long deviceID, int *errorCode);
			unsigned char getMaxFactor(long deviceID, int *errorCode);

		private:

			static BinningAPI *instance;

		};
	}
}
#endif /* BINNINGAPI_H */
