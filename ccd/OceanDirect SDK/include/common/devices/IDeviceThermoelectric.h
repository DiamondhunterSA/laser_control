#ifndef I_DEVICE_THERMOELECTRIC_H
#define I_DEVICE_THERMOELECTRIC_H
/*****************************************************
 * @file    IDeviceThermoelectric.h
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
    * IDeviceThermoelectric defines the interface to the Device TEC functionality e.g. getting and setting TEC setpoint.
    */
    class IDeviceThermoelectric {
    public:
        virtual double readTecTemperatureDegreesC(int* errorCode) = 0;
        virtual void setTecTemperatureSetpointDegreesC(int* errorCode, double temperatureDegreesCelsius) = 0;
        virtual void setTecEnable(int* errorCode, bool tecEnable) = 0;
        virtual bool getTecEnable(int* errorCode) = 0;
        virtual float getTecSetpoint(int* errorCode) = 0;
        virtual bool getTecStable(int* errorCode) = 0;
        virtual bool getTecFanEnable(int* errorCode) = 0;
        virtual void setTecFanEnable(int* errorCode, bool enable) = 0;

        virtual ~IDeviceThermoelectric() {}
    };
}
#endif // !I_DEVICE_THERMOELECTRIC_H
