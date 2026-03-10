#ifndef I_DEVICE_DHCP_SERVER_H
#define I_DEVICE_DHCP_SERVER_H
/*****************************************************
 * @file    IDeviceDhcpServer.h
 * @date    October 2022
 * @author  Ocean Insight, Inc.
 *
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
#include <cstdint>
namespace oceandirect {
    /*
    * IDeviceDhcpServer defines the interface to the Device DHCP server functionality e.g. enabling/disabling DHCP server.
    */
    class IDeviceDhcpServer {
    public:
        virtual bool isDHCPServerEnabled(int* errorCode, unsigned char ifNum) = 0;
        virtual void setDHCPServerEnable(int* errorCode, unsigned char ifNum, bool enable) = 0;
        virtual void getDHCPServerAddressRange(int* errorCode, unsigned char ifNum,
            unsigned int* outBaseIpAddress, unsigned int ipAddressArraySize, unsigned int* outNetmask) = 0;
        virtual void setDHCPServerAddressRange(int* errorCode, unsigned char ifNum,
            const unsigned int* baseIpAddress, unsigned int ipAddressArraySize, unsigned int netmask) = 0;

        virtual ~IDeviceDhcpServer() {}
    };
}
#endif // !I_DEVICE_DHCP_SERVER_H
