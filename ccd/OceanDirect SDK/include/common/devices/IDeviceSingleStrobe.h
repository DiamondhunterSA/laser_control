#ifndef I_DEVICE_SINGLE_STROBE_H
#define I_DEVICE_SINGLE_STROBE_H
/*****************************************************
 * @file    IDeviceSingleStrobe.h
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
    * IDeviceSingleStrobe defines the interface to the Device single strobe functionality e.g. getting and setting single strobe delay.
    */
    class IDeviceSingleStrobe {
    public:
        virtual void setSingleStrobeDelayMicroseconds(int* errorCode, unsigned long period_usec) = 0;
        virtual void setSingleStrobeWidthMicroseconds(int* errorCode, unsigned long period_usec) = 0;
        virtual void setSingleStrobeEnable(int* errorCode, bool enable) = 0;
        virtual unsigned long getSingleStrobeDelayMicroseconds(int* errorCode) = 0;
        virtual unsigned long getSingleStrobeWidthMicroseconds(int* errorCode) = 0;
        virtual bool getSingleStrobeEnable(int* errorCode) = 0;
        virtual unsigned long  getSingleStrobeDelayMinimumMicroseconds(int* errorCode) = 0;
        virtual unsigned long  getSingleStrobeDelayMaximumMicroseconds(int* errorCode) = 0;
        virtual unsigned long  getSingleStrobeWidthMinimumMicroseconds(int* errorCode) = 0;
        virtual unsigned long  getSingleStrobeWidthMaximumMicroseconds(int* errorCode) = 0;
        virtual unsigned long  getSingleStrobeCycleMaximumMicroseconds(int* errorCode) = 0;
        virtual unsigned long  getSingleStrobeDelayIncrementMicroseconds(int* errorCode) = 0;
        virtual unsigned long  getSingleStrobeWidthIncrementMicroseconds(int* errorCode) = 0;

        virtual ~IDeviceSingleStrobe() {}
    };
}
#endif // !I_DEVICE_SINGLE_STROBE_H
