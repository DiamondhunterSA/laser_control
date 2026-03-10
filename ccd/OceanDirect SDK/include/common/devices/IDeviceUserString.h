#ifndef I_DEVICE_USER_STRING_H
#define I_DEVICE_USER_STRING_H
/*****************************************************
 * @file    IDeviceUserString.h
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
namespace oceandirect {
    /*
    * IDeviceUserString defines the interface to the Device Information functionality e.g. getting and setting user defined strings.
    */
    class IDeviceUserString {
    public:
        virtual int getUserString(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setUserString(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getUserStringCount(int* errorCode) = 0;
        virtual int getUserString(int* errorCode, int index, char* buffer, int bufferLength) = 0;
        virtual void setUserString(int* errorCode, int index, char* buffer, int bufferLength) = 0;

        virtual ~IDeviceUserString() {}
    };
}
#endif // !I_DEVICE_USER_STRING_H
