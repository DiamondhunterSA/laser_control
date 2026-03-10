#ifndef I_DEVICE_LAMP_STROBE_H
#define I_DEVICE_LAMP_STROBE_H
/*****************************************************
 * @file    IDeviceLampStrobe.h
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
    * IDeviceLampStrobe defines the interface to the Device lamp strobe functionality e.g. enable/disable lamp strobe.
    */
    class IDeviceLampStrobe {
    public:
        virtual void setLampStrobeEnable(int* errorCode, bool strobeEnable) = 0;
        virtual bool getLampStrobeEnable(int* errorCode) = 0;

        virtual ~IDeviceLampStrobe() {}
    };
}
#endif // !I_DEVICE_LAMP_STROBE_H
