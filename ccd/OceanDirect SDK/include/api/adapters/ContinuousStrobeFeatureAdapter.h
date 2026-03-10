/*****************************************************
 * @file    ContinuousStrobeFeatureAdapter.h
 * @date    October 2018
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

#ifndef OCEANDIRECT_CONTINUOUS_STROBE_FEATURE_ADAPTER_H
#define OCEANDIRECT_CONTINUOUS_STROBE_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/continuous_strobe/ContinuousStrobeFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class ContinuousStrobeFeatureAdapter
                : public FeatureAdapterTemplate<ContinuousStrobeFeatureInterface> {
        public:
            ContinuousStrobeFeatureAdapter(ContinuousStrobeFeatureInterface *intf,
                    const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~ContinuousStrobeFeatureAdapter();

            unsigned long getContinuousStrobePeriodMicroseconds(int *errorCode);
            bool getContinuousStrobeEnable(int *errorCode);
            unsigned long getContinuousStrobePeriodMinimumMicroseconds(int *errorCode);
            unsigned long getContinuousStrobePeriodMaximumMicroseconds(int *errorCode);
            unsigned long getContinuousStrobePeriodIncrementMicroseconds(int *errorCode);
            unsigned long getContinuousStrobeWidthMicroseconds(int *errorCode);

            void setContinuousStrobePeriodMicroseconds(int *errorCode, unsigned long period_usec);
            void setContinuousStrobeEnable(int *errorCode, bool enable);
            void setContinuousStrobeWidthMicroseconds(int *errorCode, unsigned long strobeWidthMicroseconds);
        };
    }
}

#endif
