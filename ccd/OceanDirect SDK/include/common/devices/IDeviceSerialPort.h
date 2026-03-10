#ifndef I_DEVICE_SERIAL_PORT_H
#define I_DEVICE_SERIAL_PORT_H
/*****************************************************
 * @file    IDeviceSerialPort.h
 * @date    October 2022
 * @author  Ocean Insight, Inc.
 *
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2022] Ocean Insight Incorporated
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
#include <cstdint>
namespace oceandirect {
    /*
    * IDeviceSerialPort defines the interface to the Device serial port functionality e.g. getting and setting baud rate.
    */
    class IDeviceSerialPort {
    public:
        virtual int getBaudRate(int* errorCode) = 0;
        virtual void setBaudRate(int* errorCode, int baudRate) = 0;
        virtual void saveSettingsToFlash(int* errorCode) = 0;
        virtual std::uint8_t getSerialCommThresholdMode(int* errorCode) = 0;
        virtual void setSerialCommThresholdMode(int* errorCode, std::uint8_t thresholdMode) = 0;

        virtual ~IDeviceSerialPort() {}
    };
}
#endif // !I_DEVICE_SERIAL_PORT_H
