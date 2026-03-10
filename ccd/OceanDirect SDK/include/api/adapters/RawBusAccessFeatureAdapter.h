/*****************************************************
 * @file    RawBusAccessFeatureAdapter.h
 * @date    February 2022
 * @author  Ocean Insight, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect RawBusAccessFeatureInterface instances.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2022] Ocean Insight Incorporatesd
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

#ifndef OCEANDIRECT_RAW_BUS_ACCESS_FEATURE_ADAPTER_H
#define OCEANDIRECT_RAW_BUS_ACCESS_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/raw_bus_access/RawBusAccessFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class RawBusAccessFeatureAdapter : public FeatureAdapterTemplate<RawBusAccessFeatureInterface> {
        public:
            RawBusAccessFeatureAdapter(RawBusAccessFeatureInterface *intf,
                                       const FeatureFamily &f,
                                       Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~RawBusAccessFeatureAdapter() = default;

            int readUSB(int *errorCode, unsigned char *buffer, unsigned int bufferLength, unsigned char usbEndpoint);
            int writeUSB(int *errorCode, unsigned char *buffer, unsigned int bufferLength, unsigned char usbEndpoint);
            int read(int *errorCode, unsigned char *buffer, unsigned int bufferLength);
            int write(int *errorCode, unsigned char *buffer, unsigned int bufferLength);
            std::string getStringDescriptor(int *errorCode, int index);
        };

    }
}

#endif /* OCEANDIRECT_RAW_BUS_ACCESS_FEATURE_ADAPTER_H */
