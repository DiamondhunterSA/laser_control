#ifndef I_DEVICE_NETWORK_CONFIGURATION_H
#define I_DEVICE_NETWORK_CONFIGURATION_H
/*****************************************************
 * @file    IDeviceNetworkConfiguration.h
 * @date    August 2023
 * @author  Ocean Insight, Inc.
 *
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2023] Ocean Insight Incorporated
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
    * IDeviceNetworkConfiguration defines the interface to the Device network configuration functionality e.g. getting the number
    * of network interfaces.
    */
    class IDeviceNetworkConfiguration {
    public:
        //Legacy Commands
        virtual std::uint32_t getNetworkInterfaceCount(int* errorCode) = 0;
        virtual std::uint32_t getNetworkInterfaceType(int* errorCode, std::uint32_t interfaceIndex) = 0;
        virtual bool getNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex) = 0;
        virtual void setNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable) = 0;
        virtual bool getMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex) = 0;
        virtual void setMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex, bool enabled) = 0;
        virtual void saveNetworkInterfaceSetting(int* errorCode, std::uint32_t interfaceIndex) = 0;


        //OBP2 Commands
        virtual bool getIPAddressAssignedMode(int* errorCode) = 0;
        virtual void setIPAddressAssignedMode(int* errorCode, bool useStaticIP) = 0;
        virtual void getManualNetworkConfiguration(int* errorCode,
                                             std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                             std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                             std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                             std::uint8_t* outDNSServer, std::uint32_t dnsServerSize) = 0;
        virtual void setManualNetworkConfiguration(int* errorCode,
                                             const std::uint8_t* ipv4Address, std::uint32_t ipv4AddressSize,
                                             const std::uint8_t* subnetMask, std::uint32_t subnetMaskSize,
                                             const std::uint8_t* defaultGateway, std::uint32_t defaultGatewaySize,
                                             const std::uint8_t* dnsServer, std::uint32_t dnsServerSize) = 0;

        virtual void getNetworkConfiguration(int* errorCode, bool &outManualAssignment,
                                             std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                             std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                             std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                             std::uint8_t* outDNSServer, std::uint32_t dnsServerSize) = 0;
        virtual bool getEthernetAddOnAvailable(int* errorCode) = 0;
        virtual void getEthernetMACAddress(int* errorCode, std::uint8_t* outMACAddress, std::uint32_t outMACAddressSize) = 0;
        virtual void setEthernetMACAddress(int* errorCode, const std::uint8_t* macAddress, std::uint32_t macAddressSize) = 0;
        virtual bool getEthernetLoopBackTest(int* errorCode) = 0;

        virtual ~IDeviceNetworkConfiguration() {}
    };
}
#endif // !I_DEVICE_NETWORK_CONFIGURATION_H
