/*****************************************************
 * @file    HighGainModeFeatureAdapter.h
 * @date    May 2023
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect HighGainModeFeatureInterface instances.
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

#ifndef OCEANDIRECT_HIGH_GAIN_MODE_FEATUREADAPTER_H
#define OCEANDIRECT_HIGH_GAIN_MODE_FEATUREADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/high_gain_mode/HighGainModeFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class HighGainModeFeatureAdapter
                : public FeatureAdapterTemplate<HighGainModeFeatureInterface> {
        public:
            HighGainModeFeatureAdapter(HighGainModeFeatureInterface*intf,
                                       const FeatureFamily &f,
                                       Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~HighGainModeFeatureAdapter();

            void setHighGainMode(int *errorCode, bool enableHighGain);
            bool getHighGainMode(int* errorCode);

            void setSensorGainMode(int* errorCode, bool enableHighGain, bool enableStandardGain);
            void getSensorGainMode(int* errorCode, bool& outHighGain, bool& outStandardGain);
            bool getSensorGainHWState(int* errorCode);
        };

    }
}

#endif
