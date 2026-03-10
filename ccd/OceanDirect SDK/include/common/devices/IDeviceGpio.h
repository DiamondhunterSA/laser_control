#ifndef I_DEVICE_GPIO_H
#define I_DEVICE_GPIO_H
/*****************************************************
 * @file    IDeviceGpio.h
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
    * IDeviceGpio defines the interface to the Device GPIO functionality e.g. getting and setting GPIO bits.
    */
    class IDeviceGpio {
    public:
        virtual int getGpioCount(int* errorCode) = 0;
        virtual void setGpioOutputEnable(int* errorCode, std::uint32_t bitPosition, bool isOutput) = 0;
        virtual void setGpioOutputEnable(int* errorCode, std::uint32_t bits, std::uint32_t bitmask) = 0;
        virtual bool getGpioOutputEnable(int* errorCode, int bit) = 0;
        virtual uint32_t getGpioOutputEnable(int* errorCode) = 0;
        virtual void setGpioValue(int* errorCode, std::uint32_t bitPosition, bool value) = 0;
        virtual void setGpioValue(int* errorCode, uint32_t bitmask) = 0;
        virtual void setGpioValue(int* errorCode, uint32_t bits, uint32_t bitmask) = 0;
        virtual bool getGpioValue(int* errorCode, int bit) = 0;
        virtual uint32_t getGpioValue(int* errorCode) = 0;
        virtual void setGpioOutputAlternate(int* errorCode, int bit, bool isAlternate) = 0;
        virtual void setGpioOutputAlternate(int* errorCode, uint32_t bitMask) = 0;
        virtual bool getGpioOutputAlternate(int* errorCode, int bit) = 0;
        virtual uint32_t getGpioOutputAlternate(int* errorCode) = 0;

        virtual ~IDeviceGpio() {}
    };
}
#endif // !I_DEVICE_GPIO_H
