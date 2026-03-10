#ifndef I_DEVICE_REVISION_H
#define I_DEVICE_REVISION_H
/*****************************************************
 * @file    IDeviceRevision.h
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
    * IDeviceRevision defines the interface to the Device revision functionality e.g. getting and firmware version.
    */
    class IDeviceRevision {
    public:
        virtual int getRevisionHardware(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getRevisionFirmware(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getRevisionFPGA(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getRevisionSystem(int* errorCode, char* buffer, int bufferLength) = 0;

        virtual ~IDeviceRevision() {}
    };
}
#endif // !I_DEVICE_REVISION_H
