#ifndef I_DEVICE_HIGH_GAIN_MODE_H
#define I_DEVICE_HIGH_GAIN_MODE_H
/*****************************************************
 * @file    IDeviceHighGainMode.h
 * @date    May 2023
 * @author  Ocean Insight, Inc.
 *
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
namespace oceandirect {
    /*
    * IDeviceHighGainMode defines the interface to the high gain mode functionality of selected devices
    * such as NirQuest.
    */
    class IDeviceHighGainMode {
    public:
        virtual void setHighGainMode(int* errorCode, bool enableHighGain) = 0;
        virtual bool getHighGainMode(int* errorCode) = 0;

        virtual void setSensorGainMode(int* errorCode, bool enableHighGain, bool enableStandardGain) = 0;
        virtual void getSensorGainMode(int* errorCode, bool& outHighGain, bool& outStandardGain) = 0;
        virtual bool getSensorGainHWState(int* errorCode) = 0;

        virtual ~IDeviceHighGainMode() {}
    };
}
#endif // !I_DEVICE_HIGH_GAIN_MODE_H
