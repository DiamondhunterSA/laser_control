/*****************************************************
 * @file    PixelBinningFeatureAdapter.h
 * @date    October 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * TECFeatureInterface instances.
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

#ifndef OCEANDIRECT_PIXEL_BINNING_FEATURE_ADAPTER_H
#define OCEANDIRECT_PIXEL_BINNING_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/pixel_binning/PixelBinningFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class PixelBinningFeatureAdapter
                : public FeatureAdapterTemplate<PixelBinningFeatureInterface> {
        public:
            PixelBinningFeatureAdapter(PixelBinningFeatureInterface *intf,
                    const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~PixelBinningFeatureAdapter();

            /* Thermoelectric cooler functions */
            unsigned char getPixelBinningFactor(int *errorCode);

            void setPixelBinningFactor(int *errorCode,
                    const unsigned char binningFactor);

            unsigned char getDefaultPixelBinningFactor(int *errorCode);

            void setDefaultPixelBinningFactor(int *errorCode,
                    const unsigned char binningFactor);

            void setDefaultPixelBinningFactor(int *errorCode);

            unsigned char getMaxPixelBinningFactor(int *errorCode);
        };
    }
}

#endif
