#ifndef I_DEVICE_SERIAL_NUMBER_H
#define I_DEVICE_SERIAL_NUMBER_H
/*****************************************************
 * @file    IDeviceSerialNumber.h
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
    * IDeviceSerialNumber defines the interface to the Device serial number functionality
    */
    class IDeviceSerialNumber {
    public:

        virtual int getSerialNumber(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setSerialNumber(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual unsigned char getSerialNumberMaximumLength(int* errorCode) = 0;

        virtual ~IDeviceSerialNumber() {}
    };
}
#endif // !I_DEVICE_SERIAL_NUMBER_H
