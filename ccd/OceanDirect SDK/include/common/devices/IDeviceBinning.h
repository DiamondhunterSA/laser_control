#ifndef I_DEVICE_BINNING_H
#define I_DEVICE_BINNING_H
/*****************************************************
 * @file    IDeviceBinning.h
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
    * IDeviceBinning defines the interface to the Device pixel binning functionality. This functionality is deprecated and
    * only appears here for API backward compatibility.
    */
    class IDeviceBinning {
    public:
        virtual void setPixelBinningFactor(int* errorCode, const unsigned char binningFactor) = 0;
        virtual unsigned char getPixelBinningFactor(int* errorCode) = 0;
        virtual void setDefaultPixelBinningFactor(int* errorCode, const unsigned char binningFactor) = 0;
        virtual void setDefaultPixelBinningFactor(int* errorCode) = 0;
        virtual unsigned char getDefaultPixelBinningFactor(int* errorCode) = 0;
        virtual unsigned char getMaxPixelBinningFactor(int* errorCode) = 0;

        virtual ~IDeviceBinning() {}
    };
}
#endif // !I_DEVICE_BINNING_H
