/*****************************************************
 * @file    AcquisitionDelayFeatureAdapter.h
 * @date    November 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * DataBufferFeatureInterface instances.
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

#ifndef OCEANDIRECT_ACQUISITION_DELAY_FEATURE_ADAPTER_H
#define OCEANDIRECT_ACQUISITION_DELAY_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/acquisition_delay/AcquisitionDelayFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class AcquisitionDelayFeatureAdapter
                : public FeatureAdapterTemplate<AcquisitionDelayFeatureInterface> {
        public:
            AcquisitionDelayFeatureAdapter(AcquisitionDelayFeatureInterface *intf,
                const FeatureFamily &f, Protocol *p, Bus *b,
                unsigned short instanceIndex);

            virtual ~AcquisitionDelayFeatureAdapter() = default;

            /* Acquisition delay functions */
            unsigned long getAcquisitionDelayIncrementMicroseconds(int *errorCode);
            unsigned long getAcquisitionDelayMaximumMicroseconds(int *errorCode);
            unsigned long getAcquisitionDelayMinimumMicroseconds(int *errorCode);
            unsigned long getAcquisitionDelayMicroseconds(int *errorCode);
            void setAcquisitionDelayMicroseconds(int *errorCode, const unsigned long delay_usec);
        };

    } /* end namespace api */
} /* end namespace oceandirect */

#endif /* OCEANDIRECT_ACQUISITION_DELAY_FEATURE_ADAPTER_H */

