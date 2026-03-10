#ifndef OCEAN_I_OBP2DEVICE_H
#define OCEAN_I_OBP2DEVICE_H

/*******************************************************
 * @file    IOBP2Device.h
 * @date    October 2023
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to connect to devices over USB and other buses.
 * This is intended as a usable and extensible API. The method
 * calls below represent the complete C and Python interface for
 * accessing an Ocean Insight spectrometer.
 *
 * This provides a C and Python interface to help with linkage.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2023] Ocean Insight Incorporated
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
#include "lighthouse/api/lhdefs.h"
#include "common/public/UsbEndpoint.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceInformation.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceTemperature.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceSpectrometer.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceThermoelectric.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceNonlinearity.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceContinuousStrobe.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceOpticalBench.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceGpio.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceSingleStrobe.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceLed.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceLamp.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDevicePixelInfo.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceAutonulling.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceUserString.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceSerialPort.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceAlias.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceNetworkConfiguration.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceShutter.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceHighGainMode.h"
#include "vendors/OceanOptics/device_functions/ILighthouseDeviceFlashScratchPad.h"

namespace oceandirect {

    class DeviceLocatorInterface;
    /*
    * IDevice is the interface to all Ocean spectrometers. Not all devices
    * may support all of the commands in this interface; when a command is
    * not supported the command will return an error code "command not supported".
    */
    class IOBP2Device :
        public ILighthouseDeviceInformation,
        public ILighthouseDeviceTemperature,
        public ILighthouseDeviceSpectrometer,
        public ILighthouseDeviceThermoelectric,
        public ILighthouseDeviceNonlinearity,
        public ILighthouseDeviceContinuousStrobe,
        public ILighthouseDeviceOpticalBench,
        public ILighthouseDeviceGpio,
        public ILighthouseDeviceSingleStrobe,
        public ILighthouseDeviceLed,
        public ILighthouseDeviceLamp,
        public ILighthouseDevicePixelInfo,
        public ILighthouseDeviceAutonulling,
        public ILighthouseDeviceUserString,
        public ILighthouseDeviceSerialPort,
        public ILighthouseDeviceNetworkConfiguration,
        public ILighthouseDeviceShutter,
        public ILighthouseDeviceHighGainMode,
        public ILighthouseDeviceFlashScratchPad {
    public:
        virtual ~IOBP2Device() = default;

        virtual int open(lh_error_code_t* errorCode) = 0;
        virtual void close() = 0;

        virtual DeviceLocatorInterface* getLocation() = 0;

        /* Get a string that describes the type of device */
        virtual size_t getDeviceType(lh_error_code_t* errorCode, char buffer[], size_t maxLength) = 0;
    };
}
#endif // !OCEAN_I_DEVICE_H

