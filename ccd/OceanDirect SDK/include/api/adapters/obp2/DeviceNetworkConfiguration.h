#ifndef DEVICE_NETWORK_CONFIGURATION_H
#define DEVICE_NETWORK_CONFIGURATION_H

/*******************************************************
 * @file    DeviceNetworkConfiguration.h
 * @date    November 2022
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to connect to devices over USB and other buses.
 * This is intended as a usable and extensible API. The method
 * calls below represent the complete C and Python interface for
 * accessing an Ocean Insight spectrometer.
 *
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
#include <functional>
#include <map>
#include "common/devices/IDeviceNetworkConfiguration.h"
#include "api/adapters/obp2/IFunctionDeactivator.h"
// so we can abbreviate the placeholders as _1, _2 etc.
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
using std::placeholders::_5;
using std::placeholders::_6;
using std::placeholders::_7;
using std::placeholders::_8;
using std::placeholders::_9;
using std::placeholders::_10;

//Mac placeholders is limited to 10 so lets use a lamdba function instead. 
//using std::placeholders::_11;

namespace oceandirect {

    class Device;

    namespace api {
        class DeviceNetworkConfiguration :
            public IDeviceNetworkConfiguration,
            public IFunctionDeactivator {

            /* Functions that will be invoked to provide the interface.If the commands are not supported by the device they will
            * be replaced by a lambda function that returns a command not supported error.
            */
            std::function<std::uint32_t(int*)> fnGetNetworkInterfaceCount = std::bind(&DeviceNetworkConfiguration::implGetNetworkInterfaceCount, this, _1);
            std::function<std::uint32_t(int*, std::uint32_t)> fnGetNetworkInterfaceType = std::bind(&DeviceNetworkConfiguration::implGetNetworkInterfaceType, this, _1, _2);
            std::function<bool(int*, std::uint32_t)> fnGetNetworkInterfaceStatus = std::bind(&DeviceNetworkConfiguration::implGetNetworkInterfaceStatus, this, _1, _2);
            std::function<void(int*, std::uint32_t, bool)> fnSetNetworkInterfaceStatus = std::bind(&DeviceNetworkConfiguration::implSetNetworkInterfaceStatus, this, _1, _2, _3);
            std::function<void(int*, std::uint32_t)> fnSaveNetworkInterfaceSetting = std::bind(&DeviceNetworkConfiguration::implSaveNetworkInterfaceSetting, this, _1, _2);

            std::function<bool(int*)> fnGetIPAddressAssignedMode  = std::bind(&DeviceNetworkConfiguration::implGetIPAddressAssignedMode, this, _1);
            std::function<void(int*, bool)> fnSetIPAddressAssignedMode  = std::bind(&DeviceNetworkConfiguration::implSetIPAddressAssignedMode, this, _1, _2);

            std::function<void(int*, bool*, 
                               std::uint8_t*, std::uint32_t,
                               std::uint8_t*, std::uint32_t,
                               std::uint8_t*, std::uint32_t,
                               std::uint8_t*, std::uint32_t)> fnGetNetworkConfiguration = [this](auto a,  auto b,  auto c,  auto d,  auto e, auto f, auto g,
                                                                                             auto h,  auto i,  auto j)->void {
                                                                                             DeviceNetworkConfiguration::implGetNetworkConfiguration(a,b,c,d,e,f,g,h,i,j);
                                                                                           };

            std::function<void(int* ,
                               const std::uint8_t*, std::uint32_t,
                               const std::uint8_t*, std::uint32_t,
                               const std::uint8_t*, std::uint32_t,
                               const std::uint8_t*, std::uint32_t)> fnSetManualNetworkConfiguration = std::bind(&DeviceNetworkConfiguration::implSetManualNetworkConfiguration, this, _1, _2, _3, _4, _5, _6, _7, _8, _9);
            std::function<void(int*,
                               std::uint8_t*, std::uint32_t,
                               std::uint8_t*, std::uint32_t,
                               std::uint8_t*, std::uint32_t,
                               std::uint8_t*, std::uint32_t)> fnGetManualNetworkConfiguration = std::bind(&DeviceNetworkConfiguration::implGetManualNetworkConfiguration, this, _1, _2, _3, _4, _5, _6, _7, _8, _9);
            std::function<bool(int*)> fnGetEthernetAddOnAvailable = std::bind(&DeviceNetworkConfiguration::implGetEthernetAddOnAvailable, this, _1);
            std::function<void(int*, std::uint8_t*, std::uint32_t)> fnGetEthernetMACAddress = std::bind(&DeviceNetworkConfiguration::implGetEthernetMACAddress, this, _1, _2, _3);
            std::function<void(int*, const std::uint8_t*, std::uint32_t)> fnSetEthernetMACAddress = std::bind(&DeviceNetworkConfiguration::implSetEthernetMACAddress, this, _1, _2, _3);
            std::function<bool(int*)> fnGetEthernetLoopBackTest = std::bind(&DeviceNetworkConfiguration::implGetEthernetLoopBackTest, this, _1);

            std::uint32_t implGetNetworkInterfaceCount(int* errorCode);
            std::uint32_t implGetNetworkInterfaceType(int* errorCode, std::uint32_t interfaceIndex);
            bool implGetNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex);
            void implSetNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable);
            void implSaveNetworkInterfaceSetting(int* errorCode, std::uint32_t interfaceIndex);

            bool implGetIPAddressAssignedMode(int* errorCode);
            void implSetIPAddressAssignedMode(int* errorCode, bool useDHCP);
            void implGetNetworkConfiguration(int* errorCode, bool* outManualAssignment,
                                             std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                             std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                             std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                             std::uint8_t* outDNSServer, std::uint32_t dnsServerSize);
            void implSetManualNetworkConfiguration(int* errorCode, 
                                             const std::uint8_t* ipv4Address, std::uint32_t ipv4AddressSize,
                                             const std::uint8_t* subnetMask, std::uint32_t subnetMaskSize,
                                             const std::uint8_t* defaultGateway, std::uint32_t defaultGatewaySize,
                                             const std::uint8_t* dnsServer, std::uint32_t dnsServerSize);
            void implGetManualNetworkConfiguration(int* errorCode,
                                             std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                             std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                             std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                             std::uint8_t* outDNSServer, std::uint32_t dnsServerSize);
            bool implGetEthernetAddOnAvailable(int* errorCode);
            void implGetEthernetMACAddress(int* errorCode, std::uint8_t* outMACAddress, std::uint32_t macAddressSize);
            void implSetEthernetMACAddress(int* errorCode, const std::uint8_t* macAddress, std::uint32_t macAddressSize);
            bool implGetEthernetLoopBackTest(int* errorCode);

            std::multimap<unsigned int, std::function<void()>> functionDeactivationMap;
            Device* device;

        public:
            DeviceNetworkConfiguration(Device* dev);

            //Legacy Commands
            std::uint32_t getNetworkInterfaceCount(int* errorCode) override;
            std::uint32_t getNetworkInterfaceType(int* errorCode, std::uint32_t interfaceIndex) override;
            bool getNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex) override;
            void setNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable) override;
            bool getMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex) override;
            void setMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex, bool enabled) override;
            void saveNetworkInterfaceSetting(int* errorCode, std::uint32_t interfaceIndex) override;

            //OBP2 Commands
            //Put all OBP2 commands in a single file to simplify development.
            bool getIPAddressAssignedMode(int* errorCode) override;
            void setIPAddressAssignedMode(int* errorCode, bool useStaticIP) override;
            void getManualNetworkConfiguration(int* errorCode,
                                               std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                               std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                               std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                               std::uint8_t* outDNSServer, std::uint32_t dnsServerSize) override;
            void setManualNetworkConfiguration(int* errorCode,
                                               const std::uint8_t* ipv4Address, std::uint32_t ipv4AddressSize,
                                               const std::uint8_t* subnetMask, std::uint32_t subnetMaskSize,
                                               const std::uint8_t* defaultGateway, std::uint32_t defaultGatewaySize,
                                               const std::uint8_t* dnsServer, std::uint32_t dnsServerSize) override;
            void getNetworkConfiguration(int* errorCode, bool& outManualAssignment, 
                                         std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                         std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                         std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                         std::uint8_t* outDNSServer, std::uint32_t dnsServerSize) override;
            bool getEthernetAddOnAvailable(int* errorCode) override;
            void getEthernetMACAddress(int* errorCode, std::uint8_t* outMACAddress, std::uint32_t macAddressSize) override;
            void setEthernetMACAddress(int* errorCode, const std::uint8_t* macAddress, std::uint32_t macAddressSize) override;
            bool getEthernetLoopBackTest(int* errorCode) override;

            const std::multimap<unsigned int, std::function<void()>>& FunctionDeactivations() override;
        };
    }
}
#endif // !DEVICE_NETWORK_CONFIGURATION_H
