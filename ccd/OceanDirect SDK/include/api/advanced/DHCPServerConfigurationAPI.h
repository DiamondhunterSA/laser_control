/*****************************************************
 * @file    DHCPServerConfigurationAPI.h
 * @date    August 2020
 * @author  Ocean Optics, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to connect to devices over USB and other buses.
 * This is intended as a usable and extensible API.
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

#ifndef  DHCPSERVERCONFIGURATIONAPI_H
#define DHCPSERVERCONFIGURATIONAPI_H

#include "api/DllDecl.h"

 /*!
	 @brief  This is an interface to advanced features of
			 OceanDirect that allow access to less common
			 controls. This is intended as a usable and
			 extensible API.
 */
namespace oceandirect {
    namespace api {

    class DLL_DECL DHCPServerConfigurationAPI {
        public:
             DHCPServerConfigurationAPI();
            virtual ~DHCPServerConfigurationAPI();
            static DHCPServerConfigurationAPI *getInstance();

            static void shutdown();

			/**
			* Determine if the DHCP server is enabled on a specified interface e.g. Ethernet, wifi. This function only applies to HDX/FX devices.
			* @see setDHCPServerEnable()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param ifNum the specified interface.
			* @return true if the DHCP server is enabled on the specified interface, false otherwise.
			*/
			bool isDHCPServerEnabled(long deviceID, int *errorCode, unsigned char ifNum);

			/**
			* Set the DHCP server to enabled or disabled on a specified interface e.g. Ethernet, wifi. This function only applies to HDX/FX devices.
			* @see isDHCPServerEnabled()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param ifNum the specified interface.
			* @param enabled true to enable DHCP, false to disable DHCP.
			*/
			void setDHCPServerEnable(long deviceID, int *errorCode, unsigned char ifNum, unsigned char enabled);

			/**
			* Get the address range for the DHCP server on a specified interface e.g. Ethernet, wifi. This function only applies to HDX/FX devices.
			* @see setDHCPServerAddressRange()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param ifNum the specified interface.
			* @param outBaseIpAddress
			* @param ipAddressArraySize the size of the buffer.
			* @param outNetMask the netmask for the DHCP server addresses.
			*/
			void readDHCPServerAddressRange(long deviceID, int *errorCode, unsigned char ifNum,
                                            unsigned int *outBaseIpAddress, unsigned int ipAddressArraySize, unsigned int *outNetMask);

			/**
			* Set the address range for the DHCP server on a specified interface e.g. Ethernet, wifi. This function only applies to HDX/FX devices.
			* @see readDHCPServerAddressRange()
			* @param deviceID the ID of the device returned by getDeviceIDs.
			* @param errorCode a code indicating the result of the operation:
			*                  ERROR_SUCCESS on success;
			*                  ERROR_NO_DEVICE if the device does not exist;
			*                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
			*                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
			* @param ifNum the specified interface.
			* @param baseIpAddress
			* @param ipAddressArraySize the size of the buffer.
			* @param netMask the netmask for the DHCP server addresses.
			*/
			void setDHCPServerAddressRange(long deviceID, int *errorCode, unsigned char ifNum,
                                           const unsigned int *baseIpAddress, unsigned int ipAddressArraySize, unsigned int netMask);

        private:
            static DHCPServerConfigurationAPI *instance;
        };
    }
}
#endif /* DHCPSERVERCONFIGURATIONAPI_H */
