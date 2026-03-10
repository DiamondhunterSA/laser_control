#ifndef I_DEVICE_CONT_STROBE_H
#define I_DEVICE_CONT_STROBE_H
/*****************************************************
 * @file    IDeviceContinuousStrobe.h
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
    * IDeviceContinuousStrobe defines the interface to the Device continuous strobe functionality e.g. getting and setting strobe width.
    */
    class IDeviceContinuousStrobe {
    public:
        virtual unsigned long getContinuousStrobePeriodMicroseconds(int* errorCode) = 0;
        virtual bool getContinuousStrobeEnable(int* errorCode) = 0;
        virtual unsigned long getContinuousStrobePeriodMinimumMicroseconds(int* errorCode) = 0;
        virtual unsigned long getContinuousStrobePeriodMaximumMicroseconds(int* errorCode) = 0;
        virtual unsigned long getContinuousStrobePeriodIncrementMicroseconds(int* errorCode) = 0;
        virtual unsigned long getContinuousStrobeWidthMicroseconds(int* errorCode) = 0;
        virtual void setContinuousStrobePeriodMicroseconds(int* errorCode, unsigned long period_usec) = 0;
        virtual void setContinuousStrobeEnable(int* errorCode, bool enable) = 0;
        virtual void setContinuousStrobeWidthMicroseconds(int* errorCode, unsigned long strobeWidthMicroseconds) = 0;

        virtual ~IDeviceContinuousStrobe() {}
    };
}
#endif // !I_DEVICE_CONT_STROBE_H
