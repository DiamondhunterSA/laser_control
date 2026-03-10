#ifndef I_DEVICE_BACK_TO_BACK_H
#define I_DEVICE_BACK_TO_BACK_H
/*****************************************************
 * @file    IDeviceBackToBack.h
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
    * IDeviceBackToBack defines the interface to the Device back to back functionality e.g. setting the number of back to back scans.
    */
    class IDeviceBackToBack {
    public:
        virtual unsigned long getBackToBackNumScans(int* errorCode) = 0;
        virtual void setBackToBackNumScans(int* errorCode, unsigned long numScans) = 0;

        virtual ~IDeviceBackToBack() {}
    };
}
#endif // !I_DEVICE_BACK_TO_BACK_H
