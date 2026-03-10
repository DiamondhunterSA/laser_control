/*****************************************************
 * @file    Advance.h
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

#ifndef ADVANCED_H
#define ADVANCED_H

#include "api/DllDecl.h"
#include "DeviceRevisionAPI.h"
#include "ContinuousStrobeAPI.h"
#include "ThermoElectricAPI.h"
#include "LightSourceAPI.h"
#include "DataBufferAPI.h"
#include "BackToBackAPI.h"
#include "NonLinearityAPI.h"
#include "SingleStrobeAPI.h"
#include "GpioAPI.h"
#include "LedActivityAPI.h"
#include "Ipv4AddressAPI.h"
//#include "DHCPServerConfigurationAPI.h"
#include "PixelAPI.h"
#include "AutoNullingAPI.h"
#include "UserStringAPI.h"
#include "DeviceInformationAPI.h"
#include "DeviceAliasAPI.h"
#include "SerialPortAPI.h"
#include "BinningAPI.h"
#include "SpectrumAcquisitionControlAPI.h"
#include "NetworkConfigurationAPI.h"
#include "EthernetAPI.h"
#include "ShutterAPI.h"

 /*!
    @brief  This is an interface to Advance features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
    extensible API.
 */
namespace oceandirect {
    namespace api {

        class DLL_DECL Advance {
        public:
            Advance();
            virtual ~Advance();
            static Advance *getInstance();
            static void shutdown();

            virtual DeviceRevisionAPI* DeviceRevisionControl();
            virtual ContinuousStrobeAPI* ContinuousStrobeControl();
            virtual ThermoElectricAPI* ThermoElectricControl();
            virtual LightSourceAPI* LightSourceControl();
            virtual DataBufferAPI* DataBufferControl();
            virtual BackToBackAPI* BackToBackControl();
            virtual NonLinearityAPI* NonLinearityControl();
            virtual SingleStrobeAPI* SingleStrobeControl();
            virtual GpioAPI* GpioControl();
            virtual LedActivityAPI* ActivityControl();
            virtual PixelAPI* PixelControl();
            virtual AutoNullingAPI* AutoNullingControl();
            virtual UserStringAPI* UserStringControl();
            virtual DeviceInformationAPI* DeviceInformationControl();
            virtual DeviceAliasAPI* DeviceAliasControl();
            virtual SerialPortAPI* SerialPortControl();
            virtual Ipv4AddressAPI* Ipv4AddressControl();
            virtual SpectrumAcquisitionControlAPI* SpectrumAcquisitionControl();
            virtual NetworkConfigurationAPI* NetworkConfigurationControl();
            virtual EthernetAPI* EthernetControl();
            virtual ShutterAPI* ShutterControl();

        protected:
            static Advance *instance;
        };
    }
}
#endif /* ADVANCED_H */
