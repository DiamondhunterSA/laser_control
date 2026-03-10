/*****************************************************
 * @file    NetworkConfigurationAPI.h
 * @date    May 2022
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to read and write user strin to device.
 * This is intended as a usable and extensible API.
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

#ifndef NETWORK_CONFIGURATION_API_H
#define NETWORK_CONFIGURATION_API_H

#include "api/DllDecl.h"
#include <cstdint>
 /*!
    @brief  This is an interface to advanced features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
            extensible API.
 */
namespace oceandirect {
	namespace api {

        class DLL_DECL NetworkConfigurationAPI {
        public:
            NetworkConfigurationAPI() = default;
            virtual ~NetworkConfigurationAPI() = default;
            static NetworkConfigurationAPI*getInstance();

            static void shutdown();

            //Legacy Commands
            /**
            * Read the number of supported communication interface. This function only applies to HDX/FX devices.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @return The number of interface.
            */
            virtual std::uint32_t getNetworkInterfaceCount(long deviceID, int* errorCode);

            /**
            * Return the interface type of the given interface index. This function only applies to HDX/FX devices.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param interfaceIndex The interface to look at.
            * @return The interface type which could be one 0(Loopback), 1(wired ethernet), 2 (WIFI), and 3 (USB - CDC Ethernet).
            */
            virtual std::uint32_t getNetworkInterfaceType(long deviceID, int* errorCode, std::uint32_t interfaceIndex);

            /**
            * Return true if the interface is enabled otherwise it's false. This function only applies to HDX/FX devices.
            * @see setNetworkInterfaceStatus()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param interfaceIndex The interface to look at.
            * @return True if the interface if enabled otherwise it's False.
            */
            virtual bool getNetworkInterfaceStatus(long deviceID, int* errorCode, std::uint32_t interfaceIndex);

            /**
            * Enable or disable the interface. This function only applies to HDX/FX devices.
            * @see getNetworkInterfaceStatus()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param interfaceIndex The interface to look at.
            * @param enable True will enable the interface. False will disable it.
            */
            virtual void setNetworkInterfaceStatus(long deviceID, int* errorCode, std::uint32_t interfaceIndex, bool enable);

            /**
            * Return true if the multicast group message is enabled otherwise it's false. This function only applies to HDX/FX devices.
            * @see setMulticastGroupEnabled()
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param interfaceIndex[in] The interface to look at.
            * @return True if it's enabled otherwise it's False.
            */
            bool getMulticastGroupEnabled(long deviceID, int* errorCode, std::uint32_t interfaceIndex);

            /**
            * Enable or disable the multicast message group. This function only applies to HDX/FX devices.
            * @see getMulticastGroupEnabled()
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param interfaceIndex[in] The interface to look at.
            * @param enable[in] True will enable the multicast group message. False will disable it.
            */
            void setMulticastGroupEnabled(long deviceID, int* errorCode, std::uint32_t interfaceIndex, bool enabled);


            /**
            * Save the network interface settings to the device. This function only applies to HDX/FX devices.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param interfaceIndex The interface to save to.
            */
            virtual void saveNetworkInterfaceSetting(long deviceID, int* errorCode, std::uint32_t interfaceIndex);


            //OBP2 Commands
            /**
            * Read the ip address assignment mode from an OBP2 enabled device.
            * @see setIPAddressAssignedMode()
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @return True if it's DHCP IP address otherwise it's False (static IP).
            */
            virtual bool getIPAddressAssignedMode(long deviceID, int* errorCode);

            /**
            * Set the ip address assignment mode to the OBP2 enabled device.
            * @see getIPAddressAssignedMode()
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param useDHCP True if it's DHCP IP address otherwise it's False (static IP).
            */
            virtual void setIPAddressAssignedMode(long deviceID, int* errorCode, bool useDHCP);


           /**
            * Read the network configuration parameters from an OBP2 enabled device.
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param outManualAssignment[out]  An output argument that contains the IP Address mode. True if it's DHCP IP address otherwise it's False (static IP).
            * @param outIpv4Address[out]       Output buffer for the static IP address.
            * @param ipv4AddressSize[in]       The static IP address buffer size.
            * @param outSubnetMask[out]        Output buffer for the subnet mask.
            * @param subnetMaskSize[in]        The subnet mask buffer size.
            * @param outDefaultGateway[out]    Output buffer for the default gateway IP address.
            * @param defaultGatewaySize[in]    The default gateway buffer size.
            * @param outDNSServer[out]         Output buffer for the DNS server IP address.
            * @param dnsServerSize[in]         The DNS server buffer size.
            */
            virtual void getNetworkConfiguration(long deviceID, int* errorCode, bool& outManualAssignment,
                                         std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                         std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                         std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                         std::uint8_t* outDNSServer, std::uint32_t dnsServerSize);

            /**
            * Write the network configuration parameters (static ip address) on OBP2 enabled device.
            * @see getManualNetworkConfiguration()
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param ipv4Address[in]        The static IP address.
            * @param ipv4AddressSize[in]    The static IP address buffer length.
            * @param subnetMask[in]         The subnet mask.
            * @param subnetMaskSize[in]     The subnet mask buffer length.
            * @param defaultGateway[in]     The default gateway IP address.
            * @param defaultGatewaySize[in] The default gateway buffer length.
            * @param dnsServer[in]          The DNS server IP address.
            * @param dnsServerSize[in]      The DNS server buffer length.
            */
            virtual void setManualNetworkConfiguration(long deviceID, int* errorCode,
                                               const std::uint8_t* ipv4Address, std::uint32_t ipv4AddressSize,
                                               const std::uint8_t* subnetMask, std::uint32_t subnetMaskSize,
                                               const std::uint8_t* defaultGateway, std::uint32_t defaultGatewaySize,
                                               const std::uint8_t* dnsServer, std::uint32_t dnsServerSize);

            /**
            * Read the network configuration parameters (static ip address) from an OBP2 enabled device.
            * @see setManualNetworkConfiguration()
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param outIpv4Address[out]    Output buffer for the static IP address.
            * @param ipv4AddressSize[in]    The static IP address buffer length.
            * @param outSubnetMask[out]     Output buffer for the subnet mask.
            * @param subnetMaskSize[in]     The subnet mask buffer length.
            * @param outDefaultGateway[out] Output buffer for the default gateway IP address.
            * @param defaultGatewaySize[in] The default gateway buffer length.
            * @param outDNSServer[out]      Output buffer for the DNS server IP address.
            * @param dnsServerSize[in]      The DNS server buffer length.
            */
            virtual void getManualNetworkConfiguration(long deviceID, int* errorCode,
                                               std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                               std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                               std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                               std::uint8_t* outDNSServer, std::uint32_t dnsServerSize);


            /**
            * Return True or False on whether an ethernet add-on package is available in the
            * OBP2 enabled device.
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @return True if the add-on is available otherwise False.
            */
            virtual bool getEthernetAddOnAvailable(long deviceID, int* errorCode);

            /**
            * Read the ethernet 6-byte mac address from an OBP2 enabled device.
            * @see setEthernetMACAddress
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param outMACAddress[in]     The output buffer for mac address.
            * @param outMACAddressSize[in] The output buffer size which must be at least 6 bytes long.
            */
            virtual void getEthernetMACAddress(long deviceID, int* errorCode, std::uint8_t* outMACAddress, std::uint32_t outMACAddressSize);

            /**
            * Writes a new ethernet 6-byte mac address into an OBP2 enabled device.
            * @see getEthernetMACAddress
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param macAddress[in] The new mac address.
            * @param macAddress[in] The new mac address buffer size which is 6-byte long.
            * @return The mac address.
            */
            virtual void setEthernetMACAddress(long deviceID, int* errorCode, const std::uint8_t* macAddress, std::uint32_t macAddressSize);

            /**
            * Run a loop back and return true if it's successful.
            * @param deviceID[in] the ID of the device returned by getDeviceIDs.
            * @param errorCode[out] a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @return True for successful loop back testing otherwise its False.
            */
            virtual bool getEthernetLoopBackTest(long deviceID, int* errorCode);

        protected:
            static NetworkConfigurationAPI *instance;
        };
    }
}
#endif /* NETWORK_CONFIGURATION_API_H */
