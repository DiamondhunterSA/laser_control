#ifndef I_DEVICE_DATA_BUFFER_H
#define I_DEVICE_DATA_BUFFER_H
/*****************************************************
 * @file    IDeviceDataBuffer.h
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
namespace oceandirect {
    /*
    * IDeviceDataBuffer defines the interface to the Device data buffer functionality e.g. setting buffer capacity.
    */
    class IDeviceDataBuffer {
    public:
        virtual void dataBufferClear(int* errorCode) = 0;
        virtual unsigned long getDataBufferNumberOfElements(int* errorCode) = 0;
        virtual unsigned long getDataBufferBufferCapacity(int* errorCode) = 0;
        virtual unsigned long getDataBufferBufferCapacityMaximum(int* errorCode) = 0;
        virtual unsigned long getDataBufferBufferCapacityMinimum(int* errorCode) = 0;
        virtual void setDataBufferBufferCapacity(int* errorCode, unsigned long capacity) = 0;
        virtual void setDataBufferBufferEnabled(int* errorCode, bool enabled) = 0;
        virtual bool getDataBufferBufferEnabled(int* errorCode) = 0;

        virtual ~IDeviceDataBuffer() {}
    };
}
#endif // !I_DEVICE_DATA_BUFFER_H
