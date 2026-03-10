/*****************************************************
 * @file    OpticalBenchFeatureAdapter.h
 * @date    February 2022
 * @author  Ocean Insight, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect TemperatureFeatureInterface instances.
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

#ifndef OCEANDIRECT_OPTICAL_BENCH_FEATURE_ADAPTER_H
#define OCEANDIRECT_OPTICAL_BENCH_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/optical_bench/OpticalBenchFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class OpticalBenchFeatureAdapter : public FeatureAdapterTemplate<OpticalBenchFeatureInterface> {
        public:
            OpticalBenchFeatureAdapter(OpticalBenchFeatureInterface *intf,
                                       const FeatureFamily &f,
                                       Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~OpticalBenchFeatureAdapter() = default;

            int readOpticalBenchWavelength(int *errorCode, char *buffer, int buffer_length);
            unsigned short int readOpticalBenchSlitWidthMicrons(int *errorCode);
            void writeOpticalBenchSlitWidthMicrons(int *errorCode, unsigned short int widthMicrons);
            int readOpticalBenchSerialNumber(int *errorCode, char *buffer, int buffer_length);
            void writeOpticalBenchSerialNumber(int *errorCode, char *buffer, int buffer_length);
            int readOpticalBenchId(int *errorCode, char *buffer, int buffer_length);
            void writeOpticalBenchId(int *errorCode, char *buffer, int buffer_length);
            unsigned short int readOpticalBenchFiberDiameter(int *errorCode);
            void writeOpticalBenchFiberDiameter(int *errorCode, unsigned short int diameterMicrons);

            int readOpticalBenchCoating(int *errorCode, char *buffer, int buffer_length);
            void writeOpticalBenchCoating(int *errorCode, char *buffer, int buffer_length);
            int readOpticalBenchFilter(int *errorCode, char *buffer, int buffer_length);
            void writeOpticalBenchFilter(int *errorCode, char *buffer, int buffer_length);
            int readOpticalBenchGrating(int *errorCode, char *buffer, int buffer_length);
            void writeOpticalBenchGrating(int *errorCode, char *buffer, int buffer_length);
            int readOpticalBenchLens(int *errorCode, char *buffer, int buffer_length);
        };
    }
}

#endif /* OCEANDIRECT_OPTICAL_BENCH_FEATURE_ADAPTER_H */