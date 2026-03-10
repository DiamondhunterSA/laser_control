#ifndef I_DEVICE_ETHERNET_H
#define I_DEVICE_ETHERNET_H
/*****************************************************
 * @file    IDeviceEthernet.h
 * @date    November 2022
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
    * IDeviceEthernet defines the interface to the Device network configuration functionality e.g. getting the number
    * of network interfaces.
    */
    class IDeviceEthernet {
    public:
        virtual bool getGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex) = 0;
        virtual void setGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable) = 0;
        virtual void getMACAddress(int* errorCode, std::uint32_t interfaceIndex, std::uint8_t* macAddress, std::uint32_t macAddressLength) = 0;
        virtual void setMACAddress(int* errorCode, std::uint32_t interfaceIndex, const std::uint8_t* macAddress, std::uint32_t macAddressLength) = 0;

        virtual ~IDeviceEthernet() {}
    };
}
#endif // !I_DEVICE_ETHERNET_H
