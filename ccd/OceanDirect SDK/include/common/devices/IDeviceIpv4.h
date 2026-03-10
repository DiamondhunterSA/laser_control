#ifndef I_DEVICE_IPV4_H
#define I_DEVICE_IPV4_H
/*****************************************************
 * @file    IDeviceIpv4.h
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
    * IDeviceIpv4 defines the interface to the Device IPV4 functionality e.g. adding a static IP address.
    */
    class IDeviceIpv4 {
    public:
        virtual bool getDHCPEnabled(int* errorCode, unsigned char ifNum) = 0;
        virtual void setDHCPEnable(int* errorCode, unsigned char ifNum, unsigned char enabled) = 0;
        virtual int getNumberOfIpAddresses(int* errorCode, unsigned char ifNum) = 0;
        virtual void getIpAddress(int* errorCode, unsigned char ifNum, unsigned char addressIndex,
            unsigned char* ipAddress, int ipAddressLength, unsigned int* netmask) = 0;
        virtual void addStaticIpAddress(int* errorCode, unsigned char ifNum,
            unsigned char* ipAddress, int ipAddressLength, unsigned int netmask) = 0;
        virtual void deleteStaticIpAddress(int* errorCode, unsigned char ifNum, unsigned char addressIndex) = 0;
        virtual void setDefaultGatewayIpAddress(int* errorCode, unsigned char ifNum, unsigned char* ipAddress, int ipAddressLength) = 0;
        virtual void getDefaultGatewayIpAddress(int* errorCode, unsigned char ifNum, unsigned char* outIpAddress, int ipAddressLength) = 0;

        virtual ~IDeviceIpv4() {}
    };
}
#endif // !I_DEVICE_IPV4_H
