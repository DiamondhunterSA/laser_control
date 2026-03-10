/*****************************************************
 * @file    DHCPServerConfigurationFeatureAdapter.h
 * @date    August 2020
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

#ifndef OCEANDIRECT_DHCPSERVERCONFIGURATIONFEATUREADAPTER_H
#define OCEANDIRECT_DHCPSERVERCONFIGURATIONFEATUREADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/dhcp/DHCPServerConfigurationFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class DHCPServerConfigurationFeatureAdapter : public FeatureAdapterTemplate<DHCPServerConfigurationFeatureInterface> {
        public:
            DHCPServerConfigurationFeatureAdapter(DHCPServerConfigurationFeatureInterface *intf, const FeatureFamily &f,
                                                  Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~DHCPServerConfigurationFeatureAdapter();

            void setDHCPServerEnable(int *errorCode, unsigned char ifNum, unsigned char enabled);
            bool isDHCPServerEnabled(int *errorCode, unsigned char ifNum);
            void getDHCPServerAddressRange(int *errorCode, unsigned char ifNum,
                                           std::vector<unsigned char> &outBaseIpAddress, unsigned char &outNetMask);
            void setDHCPServerAddressRange(int *errorCode, unsigned char ifNum,
                                           const std::vector<unsigned char> &baseIpAddress, unsigned char netMask);
        };

    }
}

#endif
