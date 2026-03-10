/*****************************************************
 * @file    BackToBackFeatureAdapter.h
 * @date    December 2019
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

#ifndef OCEANDIRECT_BACKTOBACK_FEATURE_ADAPTER_H
#define OCEANDIRECT_BACKTOBACK_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/back_to_back/BackToBackFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class BackToBackFeatureAdapter
                : public FeatureAdapterTemplate<BackToBackFeatureInterface> {
        public:
            BackToBackFeatureAdapter(BackToBackFeatureInterface *intf,
                const FeatureFamily &f,
                Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~BackToBackFeatureAdapter();

			/* Back-To-Back scans functions */
			unsigned long getNumberOfBackToBackScans(int *errorCode);
			void setNumberOfBackToBackScans(int *errorCode, unsigned long numScans);
        };

    } /* end namespace api */
} /* end namespace oceandirect */

#endif /* OCEANDIRECT_BACKTOBACK_FEATURE_ADAPTER_H */

