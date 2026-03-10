/*****************************************************
 * @file    GpioFeatureAdapter.h
 * @date    December 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * GpioFeatureInterface instances.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2020] Ocean Insight Incorporated
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

#ifndef OCEANDIRECT_GPIO_FEATURE_ADAPTER_H
#define OCEANDIRECT_GPIO_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/gpio/GpioFeatureInterface.h"

namespace oceandirect {
	namespace api {

        class GpioFeatureAdapter : public FeatureAdapterTemplate<GpioFeatureInterface> {
        public:
            GpioFeatureAdapter(GpioFeatureInterface *intf,
	                           const FeatureFamily &f,
	                           Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~GpioFeatureAdapter();

            /* GpioFeatureAdapter functions */
            int getNumberOfGPIO(int *errorCode);
            void setOutputEnable(int *errorCode, std::uint32_t bitPosition, bool isOutput);
            void setOutputEnable(int *errorCode, std::uint32_t bits, std::uint32_t bitmask);
            bool getOutputEnable(int *errorCode, int bit);
            std::uint32_t getOutputEnable(int *errorCode);
            void setValue(int *errorCode, std::uint32_t bitPosition, bool value);
            void setValue(int *errorCode, std::uint32_t bitmask);
            void setValue(int *errorCode, std::uint32_t bits, std::uint32_t bitmask);
            bool getValue(int *errorCode, int bit);
            std::uint32_t getValue(int *errorCode);
            void gpioSetOutputAlternate(int *errorCode, int bit, bool isAlternate);
            void gpioSetOutputAlternate(int *errorCode, uint32_t bitMask);
            bool gpioGetOutputAlternate(int *errorCode, int bit);
            uint32_t gpioGetOutputAlternate(int *errorCode);
        };

	}
}

#endif
