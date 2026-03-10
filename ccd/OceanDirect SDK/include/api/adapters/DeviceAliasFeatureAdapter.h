/*****************************************************
 * @file    DeviceAliasFeatureAdapter.h
 * @date    April 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * DeviceAliasFeatureInterface instances.
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

#ifndef OCEANDIRECT_DEVICE_ALIAS_FEATURE_ADAPTER_H
#define OCEANDIRECT_DEVICE_ALIAS_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/device_alias/DeviceAliasFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class DeviceAliasFeatureAdapter : public FeatureAdapterTemplate<DeviceAliasFeatureInterface> {
        public:
            DeviceAliasFeatureAdapter(DeviceAliasFeatureInterface *intf,
                                     const FeatureFamily &f,
                                     Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~DeviceAliasFeatureAdapter();

            int getDeviceAlias(int *errorCode, char *buffer, int buffer_length);
            void setDeviceAlias(int *errorCode, char *buffer, int buffer_length);
        };
    }
}

#endif

