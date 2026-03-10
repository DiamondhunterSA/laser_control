#ifndef I_DEVICE_PIXEL_INFO_H
#define I_DEVICE_PIXEL_INFO_H
/*****************************************************
 * @file    IDevicePixelInfo.h
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
    * IDevicePixelInfo defines the interface to the Device pixel information functionality e.g. getting optically dark pixel indices.
    */
    class IDevicePixelInfo {
    public:
        virtual int getPixelCount(int* error_code) = 0;
        virtual int getActivePixelCount(int* error_code) = 0;
        virtual int getActivePixelRange(int* error_code, int* range, int rangeSize) = 0;
        virtual int getOpticalDarkPixelCount(int* error_code) = 0;
        virtual int getOpticalDarkPixelIndices(int* error_code, int* indices, int indicesSize) = 0;
        virtual int getOpticalDarkPixelRange(int* error_code, int* range, int rangeSize) = 0;
        virtual int getTransitionPixelCount(int* error_code) = 0;
        virtual int getTransitionPixelRange(int* error_code, int* range, int rangeSize) = 0;
        virtual int getBadPixelIndices(int* error_code, int* baxPixelIndices, int baxPixelSize) = 0;
        virtual void setBadPixelIndices(int* error_code, int* baxPixelIndices, int baxPixelSize) = 0;

        virtual ~IDevicePixelInfo() {}
    };
}
#endif // !I_DEVICE_PIXEL_INFO_H
