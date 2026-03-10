#ifndef I_DEVICE_TEMPERATURE_H
#define I_DEVICE_TEMPERATURE_H
/*****************************************************
 * @file    IDeviceTemperature.h
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
    * IDeviceTemperature defines the interface to the Device temperature functionality e.g. getting temperatures.
    */
    class IDeviceTemperature {
    public:
        virtual int getTemperatureCount(int* errorCode) = 0;
        virtual double getTemperature(int* errorCode, int index) = 0;
        virtual double getTemperatureExtreme(int* errorCode) = 0;
        virtual int getAllTemperatures(int* errorCode, double* buffer, int max_length) = 0;

        virtual ~IDeviceTemperature() {}
    };
}
#endif // !I_DEVICE_TEMPERATURE_H
