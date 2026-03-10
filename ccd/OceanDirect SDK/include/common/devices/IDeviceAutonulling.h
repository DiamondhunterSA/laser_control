#ifndef I_DEVICE_AUTONULLING_H
#define I_DEVICE_AUTONULLING_H
/*****************************************************
 * @file    IDeviceAutonulling.h
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
    * IDeviceAutonulling defines the interface to the Device Information functionality e.g. getting and setting saturation level.
    */
    class IDeviceAutonulling {
    public:
        virtual int getMaximumADCCount(int* error_code) = 0;
        virtual int getSaturationLevel(int* error_code) = 0;
        virtual void setSaturationLevel(int* error_code, int level) = 0;
        virtual int getBaselineLevel(int* error_code) = 0;
        virtual void setBaselineLevel(int* error_code, int level) = 0;

        virtual int getFPGADigitalGain(int* error_code) = 0;
        virtual void setFPGADigitalGain(int* error_code, int gain) = 0;
        virtual int getFPGADigitalOffset(int* error_code) = 0;
        virtual void setFPGADigitalOffset(int* error_code, int offset) = 0;

        virtual void getBaselineLevelConstraints(int* error_code, std::uint32_t& minDAC, std::uint32_t& maxDAC, float& minVolts, float& maxVolts) = 0;
        virtual void getSaturationLevelConstraints(int* error_code, std::uint32_t& minDAC, std::uint32_t& maxDAC, float& minVolts, float& maxVolts) = 0;

        virtual ~IDeviceAutonulling() {}
    };
}
#endif // !I_DEVICE_AUTONULLING_H
