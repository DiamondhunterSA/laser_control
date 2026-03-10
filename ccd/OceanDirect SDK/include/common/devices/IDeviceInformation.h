#ifndef I_DEVICE_INFORMATION_H
#define I_DEVICE_INFORMATION_H
/*****************************************************
 * @file    IDeviceInformation.h
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
#include <string>
namespace oceandirect {
    /*
    * IDeviceInformation defines the interface to the Device Information functionality e.g. getting and setting USB VID/PID.
    */
    class IDeviceInformation {
    public:
        virtual void resetDevice(int* errorCode) = 0;
        virtual std::uint16_t getOriginalVID(int* errorCode) = 0;
        virtual std::uint16_t getOriginalPID(int* errorCode) = 0;
        virtual std::uint16_t getVID(int* errorCode) = 0;
        virtual void setVID(int* errorCode, std::uint16_t vid) = 0;
        virtual std::uint16_t getPID(int* errorCode) = 0;
        virtual void setPID(int* errorCode, std::uint16_t pid) = 0;
        virtual int getOriginalManufacturerString(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getOriginalModelString(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getManufacturerString(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setManufacturerString(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getModelString(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setModelString(int* errorCode, char* buffer, int bufferLength) = 0;

        virtual int getCommandList(int* errorCode, unsigned int* commands, int length) = 0;
        virtual std::string getDeviceParameters(int* errorCode) = 0;

        virtual ~IDeviceInformation() {}
    };
}
#endif // !I_DEVICE_INFORMATION_H
