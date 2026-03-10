/*****************************************************
 * @file    EthernetAPI.h
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

#ifndef ETHERNET_API_H
#define ETHERNET_API_H

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

        class DLL_DECL EthernetAPI {
        public:
            EthernetAPI() = default;
            virtual ~EthernetAPI() = default;
            static EthernetAPI *getInstance();

            static void shutdown();


            /**
            * Read the gigabit ethernet status on a specified interface e.g. Ethernet. This function only applies to HDX/FX devices.
            * @see setGigabitEthernetEnableStatus()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param interfaceIndex the specified interface.
            * @return true if the gigabit ethernet is enabled on the specified interface, false otherwise.
            */
            virtual bool getGigabitEthernetEnableStatus(long deviceID, int* errorCode, std::uint32_t interfaceIndex);

            /**
            * Enable or disable the gigabit ethernet status on a specified interface e.g. Ethernet. This function only applies to HDX/FX devices.
            * @see getGigabitEthernetEnableStatus()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param interfaceIndex the specified interface.
            * @param enable true will enable the gigabit ethernet, false will disable otherwise.
            */
            virtual void setGigabitEthernetEnableStatus(long deviceID, int* errorCode, std::uint32_t interfaceIndex, bool enable);

            /**
            * Read the mac address on a specified interface e.g. Ethernet. This function only applies to HDX/FX devices.
            * @see setMACAddress()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param interfaceIndex the specified interface.
            * @param macAddress output buffer for mac address.
            * @param macAddressLength output buffer size.
            */
            virtual void getMACAddress(long deviceID, int* errorCode, std::uint32_t interfaceIndex, std::uint8_t *macAddress, std::uint32_t macAddressLength);

            /**
            * Write the mac address on a specified interface e.g. Ethernet. This function only applies to HDX/FX devices.
            * @see setMACAddress()
            * @param deviceID the ID of the device returned by getDeviceIDs.
            * @param errorCode a code indicating the result of the operation:
            *                  ERROR_SUCCESS on success;
            *                  ERROR_NO_DEVICE if the device does not exist;
            *                  ERROR_FEATURE_NOT_FOUND the feature is not enabled on the specified device;
            *                  ERROR_TRANSFER_ERROR the device protocol for the feature could not be found.
            * @param interfaceIndex the specified interface.
            * @param macAddress the new mac address.
            * @param macAddressLength the mac address buffer size.
            */
            virtual void setMACAddress(long deviceID, int* errorCode, std::uint32_t interfaceIndex, std::uint8_t* macAddress, std::uint32_t macAddressLength);

        protected:
            static EthernetAPI *instance;
        };
    }
}
#endif /* ETHERNET_API_H */
