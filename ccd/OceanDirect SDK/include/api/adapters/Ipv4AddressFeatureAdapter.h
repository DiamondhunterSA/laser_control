/*****************************************************
 * @file    Ipv4AddressFeatureAdapter.h
 * @date    MArch 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect SerialNumberFeatureInterface instances.
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

#ifndef OCEANDIRECT_IPV4ADDRESSFEATUREADAPTER_H
#define OCEANDIRECT_IPV4ADDRESSFEATUREADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/ipv4_address/Ipv4AddressFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class Ipv4AddressFeatureAdapter : public FeatureAdapterTemplate<Ipv4AddressFeatureInterface> {
        public:
            Ipv4AddressFeatureAdapter(Ipv4AddressFeatureInterface *intf, const FeatureFamily &f,
                Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~Ipv4AddressFeatureAdapter();

            bool isDHCPEnabled(int *errorCode, unsigned char ifNum);
            void setDHCPEnable(int *errorCode, unsigned char ifNum, unsigned char enabled);
            int getNumberOfIpAddresses(int *errorCode, unsigned char ifNum);
            void readIpAddress(int *errorCode, unsigned char ifNum, unsigned char addressIndex,
                unsigned char *ipAddress, int ipAddressLength, unsigned int *netmask);
            void addStaticIpAddress(int* errorCode, unsigned char ifNum,
                unsigned char *ipAddress, int ipAddressLength, unsigned int netmask);
            void deleteStaticIpAddress(int* errorCode, unsigned char ifNum, unsigned char addressIndex);

            void getDefaultGatewayIpAddress(int* errorCode, unsigned char ifNum,
                                            std::vector<uint8_t>& ipv4AddressNetworkByteOrder);
            void setDefaultGatewayIpAddress(int* errorCode, unsigned char ifNum,
                                            const std::vector<uint8_t>& ipv4AddressNetworkByteOrder);
        };

    }
}

#endif
