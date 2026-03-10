#ifndef I_DEVICE_RAW_BUS_H
#define I_DEVICE_RAW_BUS_H
/*****************************************************
 * @file    IDeviceRawBus.h
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
#include <string>
namespace oceandirect {
    /*
    * IDeviceRawBus defines the interface to the Device raw bus functionality e.g. read/write direct to USB.
    */
    class IDeviceRawBus {
    public:
        virtual std::string getStringDescriptor(int* errorCode, int index) = 0;
        virtual int rawBusAccessRead(int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint) = 0;
        virtual int rawBusAccessWrite(int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint) = 0;
        virtual int rawBusAccessRead(int* errorCode, unsigned char* buffer, unsigned int bufferLength) = 0;
        virtual int rawBusAccessWrite(int* errorCode, unsigned char* buffer, unsigned int bufferLength) = 0;

        virtual ~IDeviceRawBus() {}
    };
}
#endif // !I_DEVICE_RAW_BUS_H
