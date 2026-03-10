/*****************************************************
 * @file    LightSourceFeatureAdapter.h
 * @date    May 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect LightSourceFeatureInterface instances.
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

#ifndef OCEANDIRECT_LIGHTSOURCEFEATUREADAPTER_H
#define OCEANDIRECT_LIGHTSOURCEFEATUREADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/light_source/LightSourceFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class LightSourceFeatureAdapter
                : public FeatureAdapterTemplate<LightSourceFeatureInterface> {
        public:
            LightSourceFeatureAdapter(LightSourceFeatureInterface *intf,
                    const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~LightSourceFeatureAdapter();

            int getLightSourceCount(int *errorCode);

            bool hasLightSourceEnable(int *errorCode, int lightSourceIndex);
            bool isLightSourceEnabled(int *errorCode, int lightSourceIndex);
            void setLightSourceEnable(int *errorCode, int lightSourceIndex,
                    bool enable);

            /* The intensity is normalized over the range [0, 1] where 0 is
             * the minimum programmable intensity and 1 is the maximum
             */
            bool hasVariableIntensity(int *errorCode, int lightSourceIndex);
            double getLightSourceIntensity(int *errorCode, int lightSourceIndex);
            void setLightSourceIntensity(int *errorCode, int lightSourceIndex,
                    double intensity);
        };

    }
}

#endif
