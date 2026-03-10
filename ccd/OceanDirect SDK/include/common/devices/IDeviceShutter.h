#ifndef I_DEVICE_SHUTTER_H
#define I_DEVICE_SHUTTER_H
/*****************************************************
 * @file    IDeviceShutter.h
 * @date    March 2023
 * @author  Ocean Insight, Inc.
 *
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2023] Ocean Insight Incorporated
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
    * IDeviceShutter defines the interface to the Shutter functionality e.g. getting and setting shutter state.
    */
    class IDeviceShutter {
    public:
        virtual void setShutterOpen(int* errorCode, bool opened) = 0;
        virtual bool getShutterState(int* errorCode) = 0;

        virtual ~IDeviceShutter() {}
    };
}
#endif // !I_DEVICE_SHUTTER_H
