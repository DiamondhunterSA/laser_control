/*****************************************************
 * @file    EthernetFeatureAdapter.h
 * @date    May 2022
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect UserStringFeatureInterface instances.
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

#ifndef OCEANDIRECT_ETHERNET_FEATURE_ADAPTER_H
#define OCEANDIRECT_ETHERNET_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/ethernet/EthernetFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class EthernetFeatureAdapter : public FeatureAdapterTemplate<EthernetFeatureInterface> {
        public:
            EthernetFeatureAdapter(EthernetFeatureInterface *intf,
                                   const FeatureFamily &f,
                                   Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~EthernetFeatureAdapter() = default;

            bool getGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex);
            void setGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable);

            void getMACAddress(int* errorCode, std::uint32_t interfaceIndex, std::uint8_t* macAddress, std::uint32_t macAddressLength);
            void setMACAddress(int* errorCode, std::uint32_t interfaceIndex, const std::uint8_t* macAddress, std::uint32_t macAddressLength);
        };
    }
}

#endif

