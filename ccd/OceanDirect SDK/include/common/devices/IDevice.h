#ifndef OCEAN_I_DEVICE_H
#define OCEAN_I_DEVICE_H

/*******************************************************
 * @file    IDevice.h
 * @date    June 2022
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
#include "common/public/UsbEndpoint.h"
#include "common/devices/IDeviceInformation.h"
#include "common/devices/IDeviceTemperature.h"
#include "common/devices/IDeviceSerialNumber.h"
#include "common/devices/IDeviceSpectrometer.h"
#include "common/devices/IDeviceThermoelectric.h"
#include "common/devices/IDeviceIrradCalibration.h"
#include "common/devices/IDeviceEeprom.h"
#include "common/devices/IDeviceLampStrobe.h"
#include "common/devices/IDeviceNonlinearity.h"
#include "common/devices/IDeviceStrayLight.h"
#include "common/devices/IDeviceRawBus.h"
#include "common/devices/IDeviceContinuousStrobe.h"
#include "common/devices/IDeviceLightSource.h"
#include "common/devices/IDeviceOpticalBench.h"
#include "common/devices/IDeviceRevision.h"
#include "common/devices/IDeviceDataBuffer.h"
#include "common/devices/IDeviceGpio.h"
#include "common/devices/IDeviceSingleStrobe.h"
#include "common/devices/IDeviceBackToBack.h"
#include "common/devices/IDeviceLed.h"
#include "common/devices/IDeviceTime.h"
#include "common/devices/IDeviceDhcpServer.h"
#include "common/devices/IDeviceIpv4.h"
#include "common/devices/IDevicePixelInfo.h"
#include "common/devices/IDeviceAutonulling.h"
#include "common/devices/IDeviceUserString.h"
#include "common/devices/IDeviceAlias.h"
#include "common/devices/IDeviceSerialPort.h"
#include "common/devices/IDeviceSpectrumControl.h"
#include "common/devices/IDeviceBinning.h"
#include "common/devices/IDeviceNetworkConfiguration.h"
#include "common/devices/IDeviceEthernet.h"
#include "common/devices/IDeviceShutter.h"
#include "common/devices/IDeviceHighGainMode.h"
#include "common/devices/IDeviceFlashScratchPad.h"
#include <vector>

namespace oceandirect {

    class DeviceLocatorInterface;
    /*
    * IDevice is the interface to all Ocean spectrometers. Not all devices
    * may support all of the commands in this interface; when a command is
    * not supported the command will return an error code "command not supported".
    */
    class IDevice :
        public IDeviceInformation,
        public IDeviceTemperature,
        public IDeviceSerialNumber,
        public IDeviceSpectrometer,
        public IDeviceThermoelectric,
        public IDeviceIrradCalibration,
        public IDeviceEeprom,
        public IDeviceLampStrobe,
        public IDeviceNonlinearity,
        public IDeviceStrayLight,
        public IDeviceRawBus,
        public IDeviceContinuousStrobe,
        public IDeviceLightSource,
        public IDeviceOpticalBench,
        public IDeviceRevision,
        public IDeviceDataBuffer,
        public IDeviceGpio,
        public IDeviceSingleStrobe,
        public IDeviceBackToBack,
        public IDeviceLed,
        public IDeviceTime,
        public IDeviceDhcpServer,
        public IDeviceIpv4,
        public IDevicePixelInfo,
        public IDeviceAutonulling,
        public IDeviceUserString,
        public IDeviceAlias,
        public IDeviceSerialPort,
        public IDeviceSpectrumControl,
        public IDeviceBinning,
        public IDeviceNetworkConfiguration,
        public IDeviceEthernet,
        public IDeviceShutter,
        public IDeviceHighGainMode,
        public IDeviceFlashScratchPad {
    public:
        virtual ~IDevice() {}

        virtual int open(int* errorCode) = 0;
        virtual void close() = 0;

        virtual DeviceLocatorInterface* getLocation() = 0;

        /* An for weak association to this object */
        virtual unsigned long getID() = 0;

        /* Get a string that describes the type of device */
        virtual int getDeviceType(int* errorCode, char* buffer, unsigned int maxLength) = 0;

        /* Get a usb endpoint for the device according to the enumerator */
        /*  endpointType. A 0 is returned if the endpoint requested is not in use. */
        virtual unsigned char getDeviceEndpoint(int* errorCode, usbEndpointType anEndpointType) = 0;

        /* check an array for saturation and set a warning code if saturated*/
        virtual int checkArrayForSaturation(std::vector<double> arrayToCheck, int* errorCode) = 0;

        /* Needed for legacy device support but get rid of this as soon as possible */
        virtual std::vector<double> getDeviceConfigWavelengths() = 0;

        /* Get initial immutable properties of the spectrometer to save for future requests*/
        virtual int getDeviceConfiguration(int* errorCode) = 0;
        virtual std::vector<double> getDeviceConfigIrradCalFile() = 0;
        virtual double getDeviceConfigIrradCollectionArea() = 0;
    };
}
#endif // !OCEAN_I_DEVICE_H

