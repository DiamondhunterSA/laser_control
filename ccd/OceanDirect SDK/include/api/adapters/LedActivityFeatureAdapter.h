/*****************************************************
 * @file    LedActivityFeatureAdapter.h
 * @date    July 2020
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

#ifndef OCEANDIRECT_ACTIVITY_FEATURE_ADAPTER_H
#define OCEANDIRECT_ACTIVITY_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/activity/LEDActivityFeatureInterface.h"

namespace oceandirect {
	namespace api {

		class LedActivityFeatureAdapter
			: public FeatureAdapterTemplate<LEDActivityFeatureInterface> {
		public:
			LedActivityFeatureAdapter(LEDActivityFeatureInterface *intf,
				const FeatureFamily &f,
				Protocol *p, Bus *b, unsigned short instanceIndex);
			virtual ~LedActivityFeatureAdapter();

			/* LED Activity functions */
			bool getLEDActivityEnable(int *errorCode);
			void setLEDActivityEnable(int *errorCode, const bool enable);
		};

	} /* end namespace api */
} /* end namespace oceandirect */

#endif /* OCEANDIRECT_ACTIVITY_FEATURE_ADAPTER_H */

