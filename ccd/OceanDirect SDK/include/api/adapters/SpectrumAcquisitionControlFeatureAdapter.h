/*****************************************************
 * @file    SpectrumAcquisitionControlFeatureAdapter.h
 * @date    December 2021
 * @author  Ocean Insight, Inc. 
 *
 * This is a wrapper that allows
 * access to OceanDirect SpectrumAcquisitionControlFeatureInterface instances.
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

#ifndef OCEANDIRECT_SPECTRUM_ACQUISITION_CONTROL_FEATURE_ADAPTER_H
#define OCEANDIRECT_SPECTRUM_ACQUISITION_CONTROL_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/spectrometer_acq_control/SpectrumAcquisitionControlFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class SpectrumAcquisitionControlFeatureAdapter : public FeatureAdapterTemplate<SpectrumAcquisitionControlFeatureInterface> {
        public:
            SpectrumAcquisitionControlFeatureAdapter(SpectrumAcquisitionControlFeatureInterface *intf,
                                                     const FeatureFamily &f,
                                                     Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~SpectrumAcquisitionControlFeatureAdapter();

            bool readDeviceIdleState(int *errorCode);
            void writeAbortAcquisition(int *errorCode);
            void writeAcquireSpectraToBuffer(int *errorCode);
        };

    }
}

#endif /* OCEANDIRECT_SPECTRUM_ACQUISITION_CONTROL_FEATURE_ADAPTER_H */