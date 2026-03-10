/*****************************************************
 * @file    AutoNullingFeatureAdapter.h
 * @date    March 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect AutoNullingFeatureInterface instances.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2021] Ocean Insight Incorporated
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

#ifndef OCEANDIRECT_AUTONULLING_FEATURE_ADAPTER_H
#define OCEANDIRECT_AUTONULLING_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/autonulling/AutoNullingFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class AutoNullingFeatureAdapter : public FeatureAdapterTemplate<AutoNullingFeatureInterface> {
        public:
            AutoNullingFeatureAdapter(AutoNullingFeatureInterface *intf,
                                      const FeatureFamily &f,
                                      Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~AutoNullingFeatureAdapter();

            int getMaximumADCCount(int *errorCode);

            int getSaturationLevel(int *errorCode);
            void setSaturationLevel(int *errorCode, int level);

            int getBaselineLevel(int *errorCode);
            void setBaselineLevel(int *errorCode, int level);

            int getFPGADigitalGain(int* errorCode);
            void setFPGADigitalGain(int* errorCode, int gain);
            int getFPGADigitalOffset(int* errorCode);
            void setFPGADigitalOffset(int* errorCode, int offset);

            void getBaselineLevelConstraints(int* errorCode, unsigned int* minDAC, unsigned int* maxDAC, float* minVolts, float* maxVolts);
            void getSaturationLevelConstraints(int* errorCode, unsigned int* minDAC, unsigned int* maxDAC, float* minVolts, float* maxVolts);
        };

    }
}

#endif
