#ifndef I_DEVICE_FLASH_SCRATCH_PAD_H
#define I_DEVICE_FLASH_SCRATCH_PAD_H
/*****************************************************
 * @file    IDeviceFlashScratchPad.h
 * @date    August 2023
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
#include <cstdint>
namespace oceandirect {
    /*
    * IDeviceLed defines the interface to the Device functionalities such as:
    *     -Flash scratch pad (different non-volatile region similar to EEPROM slot)
    *     -I2C 
    *     -Ping Accessory Board
    */
    class IDeviceFlashScratchPad {
    public:
        virtual void setI2CData(int* errorCode, std::uint32_t i2cBusIndex, std::uint32_t i2cTargetAddress,
                                const std::uint8_t *data, std::uint32_t dataSize) = 0;
        virtual bool getAccessoryBoardAvailable(int* errorCode) = 0;
        virtual int  getFlashSlotData(int *errorCode, std::uint32_t slotNumber, std::uint8_t* outData, std::uint32_t outDataSize) = 0;
        virtual void setFlashSlotData(int* errorCode, std::uint32_t slotNumber, const std::uint8_t* data, std::uint32_t dataSize) = 0;

        virtual ~IDeviceFlashScratchPad() = default;
    };
}
#endif // !I_DEVICE_FLASH_SCRATCH_PAD_H
