/*****************************************************
 * @file    QueryStatusFeatureAdapter.h
 * @date    February 2022
 * @author  Ocean Insight, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * QueryFeature instances.
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

#ifndef OCEANDIRECT_QUERY_STATUS_FEATURE_ADAPTER_H
#define OCEANDIRECT_QUERY_STATUS_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/status/QueryStatusFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class QueryStatusFeatureAdapter : public FeatureAdapterTemplate<QueryStatusFeatureInterface> {
        public:
            QueryStatusFeatureAdapter(QueryStatusFeatureInterface *intf,
                                      const FeatureFamily &f, Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~QueryStatusFeatureAdapter() = default;

            /* Query status functions */
            int readStatus(int *errorCode, unsigned char *status, int length);
            unsigned long getIntegrationTimeMicroseconds(int *errorCode);
        };
    }
}

#endif
