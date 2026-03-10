/*****************************************************
 * @file    SingleStrobeFeatureAdapter.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * ContinuousStrobeFeatureInterface instances.
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

#ifndef OCEANDIRECT_SINGLE_STROBE_FEATURE_ADAPTER_H
#define OCEANDIRECT_SINGLE_STROBE_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/single_strobe/SingleStrobeFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class SingleStrobeFeatureAdapter
                : public FeatureAdapterTemplate<SingleStrobeFeatureInterface> {
        public:
            SingleStrobeFeatureAdapter(SingleStrobeFeatureInterface *intf,
                                       const FeatureFamily &f,
                                       Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~SingleStrobeFeatureAdapter() = default;

            void setSingleStrobeDelayMicroseconds(int *errorCode, int microseconds);

            void setSingleStrobeWidthMicroseconds(int *errorCode, int microseconds);

            void setSingleStrobeEnable(int *errorCode, bool enable);

            bool getSingleStrobeEnable(int *errorCode);

            unsigned long getSingleStrobeDelayMicroseconds(int *errorCode);

            unsigned long getSingleStrobeWidthMicroseconds(int *errorCode);

            unsigned long getSingleStrobeDelayMinimumMicroseconds(int *errorCode);

            unsigned long getSingleStrobeDelayMaximumMicroseconds(int *errorCode);

            unsigned long getSingleStrobeWidthMinimumMicroseconds(int *errorCode);

            unsigned long getSingleStrobeWidthMaximumMicroseconds(int *errorCode);

            unsigned long getSingleStrobeCycleMaximumMicroseconds(int *errorCode);

            unsigned long getSingleStrobeDelayIncrementMicroseconds(int *errorCode);

            unsigned long getSingleStrobeWidthIncrementMicroseconds(int *errorCode);

        };
    }
}

#endif
