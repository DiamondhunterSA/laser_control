/*****************************************************
 * @file    FlashScratchPadFeatureAdapter.h
 * @date    August 2023
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * BackToBackFeatureInterface instances.
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

#ifndef OCEANDIRECT_FLASH_SCRATCH_PAD_FEATURE_ADAPTER_H
#define OCEANDIRECT_FLASH_SCRATCH_PAD_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/flash_scratch_pad/FlashScratchPadFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class FlashScratchPadFeatureAdapter : public FeatureAdapterTemplate<FlashScratchPadFeatureInterface> {
        public:
            FlashScratchPadFeatureAdapter(FlashScratchPadFeatureInterface*intf,
                                          const FeatureFamily &f,
                                          Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~FlashScratchPadFeatureAdapter() = default;

            void setI2CData(int* errorCode, std::uint32_t i2cBusIndex, std::uint32_t i2cTargetAddress,
                            const std::uint8_t* data, std::uint32_t dataSize);
            bool getAccessoryBoardAvailable(int* errorCode);
            int  getFlashSlotData(int* errorCode, std::uint32_t slotNumber, std::uint8_t* outData, std::uint32_t outDataSize);
            void setFlashSlotData(int* errorCode, std::uint32_t slotNumber, const std::uint8_t* data, std::uint32_t dataSize);
        };

    } /* end namespace api */
} /* end namespace oceandirect */

#endif /* OCEANDIRECT_FLASH_SCRATCH_PAD_FEATURE_ADAPTER_H */

