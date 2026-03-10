#ifndef I_DEVICE_TIME_H
#define I_DEVICE_TIME_H
/*****************************************************
 * @file    IDeviceTime.h
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
    * IDeviceTime defines the interface to the Device time functionality e.g. getting and setting time.
    */
    class IDeviceTime {
    public:
        virtual long long int getTime(int* errorCode) = 0;
        virtual void setTime(int* errorCode, long long int timeInMicroseconds) = 0;

        virtual ~IDeviceTime() {}
    };
}
#endif // !I_DEVICE_TIME_H
