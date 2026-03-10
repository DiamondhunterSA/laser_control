/*****************************************************
 * @file    DataBufferFeatureAdapter.h
 * @date    October 2018
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

#ifndef OCEANDIRECT_DATA_BUFFER_FEATURE_ADAPTER_H
#define OCEANDIRECT_DATA_BUFFER_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/data_buffer/DataBufferFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class DataBufferFeatureAdapter : public FeatureAdapterTemplate<DataBufferFeatureInterface> {
        public:
            DataBufferFeatureAdapter(DataBufferFeatureInterface *intf,
                const FeatureFamily &f,
                Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~DataBufferFeatureAdapter();

            /* Data buffer functions */
            void clearBuffer(int *errorCode);
            unsigned long getNumberOfElements(int *errorCode);
            unsigned long getBufferCapacity(int *errorCode);
            unsigned long getBufferCapacityMaximum(int *errorCode);
            unsigned long getBufferCapacityMinimum(int *errorCode);
            void setBufferCapacity(int *errorCode, unsigned long capacity);
            void setBufferEnabled(int *errorCode, bool enabled);
            bool getBufferEnabled(int *errorCode);
        };

    } /* end namespace api */
} /* end namespace oceandirect */

#endif /* OCEANDIRECT_DATA_BUFFER_FEATURE_ADAPTER_H */

