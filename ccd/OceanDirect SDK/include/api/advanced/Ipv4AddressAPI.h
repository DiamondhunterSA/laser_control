#ifndef IPV4ADDRESSAPI_H
#define IPV4ADDRESSAPI_H
/*****************************************************
 * @file    Ipv4AddressAPI.h
 * @date    March 2021
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to query and set IPv4 address parameters
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


#include "api/DllDecl.h"

 /*!
     @brief  This is an interface to OceanDirect that allows
             the user to query and set IPv4 address parameters
 */
namespace oceandirect {
    namespace api {

        class DLL_DECL Ipv4AddressAPI {
        public:
            virtual ~Ipv4AddressAPI();
            static Ipv4AddressAPI *getInstance();

            static void shutdown();

            /**
            * Check to see if DHCP (client) is enabled on the specified interface. If DHCP is
            * enabled then the device will be able to receive and IP address from a DHCP server
            * in the network it is connected to. This function only applies to HDX/FX devices.
            * @see setDHCPEnable()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @return true if DHCP is enabled on the specified interface, false otherwise.
            */
            virtual bool isDHCPEnabled(long deviceID, int *errorCode, unsigned char ifNum);

            /**
            * Turn the DHCP client on or off for the device on the specified interface. This function only applies to HDX/FX devices.
            * @see isDHCPEnabled()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @param enabled a value of 0 turns the DHCP client off, a value greater than 0 turns the DHCP client on.
            */
            virtual void setDHCPEnable(long deviceID, int *errorCode, unsigned char ifNum, unsigned char enabled);

            /**
            * Get the number of IP addresses available on the specified interface. If DHCP is enabled on the
            * specified interface then index 0 represents the DHCP address and the following addresses
            * will be any static IP addresses. This function only applies to HDX/FX devices.
            *
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @return the number of IP addresses on the specified interface.
            */
            virtual int getNumberOfIpAddresses(long deviceID, int *errorCode, unsigned char ifNum);

            /**
            * Retrieve the IP address and netmask on the specified interface. If DHCP is enabled on the specified
            * interface then index 0 represents the DHCP address and the following addresses will be any static IP addresses.
            * The IP address is returned as 4 bytes into a user supplied array. The leading part of
            * the IP address will be in the first element of the array, followed by the remaining parts in order
            * to the last part of the IP address in the fourth element of the array. This function only applies to HDX/FX devices.
            * @see getNumberOfIpAddresses()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
            *                                             array size is less than 4.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @param addressIndex the index of the address to be retrieved.
            * @param ipAddress a pointer to the array that will receive the IP address.
            * @param ipAddressLength the size of the array ipAddress.
            * @param netmask a pointer to the netmask specifying the subnet of the network the device is on.
            */
            virtual void readIpAddress(long deviceID, int *errorCode, unsigned char ifNum, unsigned char addressIndex,
                unsigned char *ipAddress, int ipAddressLength, unsigned int *netmask);

            /**
            * Add a static IP address to the specified interface. The IP address is specified as 4 bytes in an array. The leading part of
            * the IP address must contain the first element of the array, followed by the remaining parts in order
            * to the last part of the IP address in the fourth element of the array. This function only applies to HDX/FX devices.
            * @see deleteStaticIpAddress()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
            *                                             array size is less than 4.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @param ipAddress the static IP address to be added.
            * @param netmask the netmask specifying the subnet of the network the device is on.
            */
            virtual void addStaticIpAddress(long deviceID, int* errorCode, unsigned char ifNum,
                unsigned char *ipAddress, int ipAddressLength, unsigned int netmask);

            /**
            * Delete a static IP address on the specified interface. This function only applies to HDX/FX devices.
            * @see addStaticIpAddress()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @param addressIndex the index of the address to be deleted.
            */
            virtual void deleteStaticIpAddress(long deviceID, int* errorCode, unsigned char ifNum, unsigned char addressIndex);


            /*
            TODO: Add the following functions
            -get/set ipv4 default gateway
            */
            /**
            * Set the gateway ip address for the device on the specified interface. This function only applies to HDX/FX devices.
            * @see getDefaultGatewayIpAddress()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
            *                                             array size is less than 4.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @param ipAddress the gateway IP address.
            * @param ipAddressLength the gateway IP address length.
            */
            virtual void setDefaultGatewayIpAddress(long deviceID, int* errorCode, unsigned char ifNum, unsigned char* ipAddress, int ipAddressLength);

            /**
            * Get the gateway ip address for the device on the specified interface. This function only applies to HDX/FX devices.
            * @see setDefaultGatewayIpAddress()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found;
            *                  ERROR_CODE_INVALID_ARGUMENT the interface number is not 0 or 1 or the ipAddress
            *                                             array size is less than 4.
            * @param ifNum the interface number: 0 for Ethernet, 1 for wi-fi.
            * @param outIpAddress the output buffer for gateway IP address.
            * @param ipAddressLength the output buffer length.
            */
            virtual void getDefaultGatewayIpAddress(long deviceID, int* errorCode, unsigned char ifNum, unsigned char* outIpAddress, int ipAddressLength);

        protected:
            Ipv4AddressAPI();
            static Ipv4AddressAPI *instance;
        };
    }
}
#endif /* IPV4ADDRESSAPI_H */
