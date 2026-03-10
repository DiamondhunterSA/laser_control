#ifndef I_DEVICE_LIGHT_SOURCE_H
#define I_DEVICE_LIGHT_SOURCE_H
/*****************************************************
 * @file    IDeviceLightSource.h
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
    * IDeviceLightSource defines the interface to the Device light source functionality e.g. enable/disable light source.
    */
    class IDeviceLightSource {
    public:
        virtual int getLightSourceCount(int* errorCode) = 0;
        virtual bool hasLightSourceEnable(int* errorCode, int lightSourceIndex) = 0;
        virtual bool isLightSourceEnabled(int* errorCode, int lightSourceIndex) = 0;
        virtual void setLightSourceEnable(int* errorCode, int lightSourceIndex, bool enable) = 0;
        virtual bool hasLightSourceVariableIntensity(int* errorCode, int lightSourceIndex) = 0;
        virtual double getLightSourceIntensity(int* errorCode, int lightSourceIndex) = 0;
        virtual void setLightSourceIntensity(int* errorCode, int lightSourceIndex, double intensity) = 0;

        virtual ~IDeviceLightSource() {}
    };
}
#endif // !I_DEVICE_LIGHT_SOURCE_H
