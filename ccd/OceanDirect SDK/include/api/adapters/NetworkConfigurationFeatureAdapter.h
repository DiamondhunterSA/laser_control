/*****************************************************
 * @file    NetworkConfigurationAdapter.h
 * @date    May 2022
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect NetworkConfigurationFeatureInterface instances.
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

#ifndef OCEANDIRECT_NETWORK_CONFIGURATION_FEATURE_ADAPTER_H
#define OCEANDIRECT_NETWORK_CONFIGURATION_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/network_configuration/NetworkConfigurationFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class NetworkConfigurationFeatureAdapter : public FeatureAdapterTemplate<NetworkConfigurationFeatureInterface> {
        public:
            NetworkConfigurationFeatureAdapter(NetworkConfigurationFeatureInterface *intf,
                                               const FeatureFamily &f,
                                               Protocol *p, Bus *b, unsigned short instanceIndex);
            ~NetworkConfigurationFeatureAdapter() = default;

            //Legacy Commands
            std::uint32_t getNetworkInterfaceCount(int* errorCode);
            std::uint32_t getNetworkInterfaceType(int* errorCode, std::uint32_t interfaceIndex);
            bool getNetworkInterfaceEnableStatus(int* errorCode, std::uint32_t interfaceIndex);
            void setNetworkInterfaceEnableStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable);
            bool getMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex);
            void setMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex, bool enable);
            void saveNetworkInterfaceSettings(int* errorCode, std::uint32_t interfaceIndex);

            //OBP2 Commands
            bool getIPAddressAssignedMode(int* errorCode);
            void setIPAddressAssignedMode(int* errorCode, bool useDHCP);
            void getNetworkConfiguration(int* errorCode, bool& outIPAddressAssignment,
                                         std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                         std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                         std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                         std::uint8_t* outDNSServer, std::uint32_t dnsServerSize);
            void setManualNetworkConfiguration(int* errorCode,
                                               const std::uint8_t* ipv4Address, std::uint32_t ipv4AddressSize,
                                               const std::uint8_t* subnetMask, std::uint32_t subnetMaskSize,
                                               const std::uint8_t* defaultGateway, std::uint32_t defaultGatewaySize,
                                               const std::uint8_t* dnsServer, std::uint32_t dnsServerSize);
            void getManualNetworkConfiguration(int* errorCode,
                                               std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                               std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                               std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                               std::uint8_t* outDNSServer, std::uint32_t dnsServerSize);

            bool getEthernetAvailable(int* errorCode);
            void getMACAddress(int* errorCode, std::uint8_t* outMACAddress, std::uint32_t macAddressSize);
            void setMACAddress(int* errorCode, const std::uint8_t* macAddress, std::uint32_t macAddressSize);
            bool getEthernetLoopBackTest(int* errorCode);
        };
    }
}

#endif

