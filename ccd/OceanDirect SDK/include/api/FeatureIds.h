/*******************************************************
 * @file    FeatureAdapterInterface.h
 * @date    March 2021
 * @author  Ocean Optics, Inc.
 *
 * This interface allows device features to be treated
 * consistently regardless of the actual capabilities.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2021] Ocean Insight Incorporated
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

#ifndef OCEANDIRECT_FEATUREADAPTERID_H
#define OCEANDIRECT_FEATUREADAPTERID_H
#ifdef __cplusplus
extern "C" {
    namespace oceandirect {
        namespace api {
#endif

            // changed enum class to just enum because it is only ever cast to a long
            enum featId {
                //NOTE: Do not change the order. Python wrapper enum type is dependent on this order.
                invalid,
                serNo,
                spectrm,
                tec,
                iirad,
                eeprom,
                strobe,
                wavecal,
                nonline,
                stray,
                raw,
                contsrtb,
                light,
                temper,
                optic,
                revise,
                process,
                buffer,
                delay,
                binn,
                gpio,
                highGainMode,
                singlestrb,
                status,
                backToBack,
                activity,
                time,
                dhcp,
                shutter,
                ipv4address,
                pixel,
                autonulling,
                userstring,
                deviceInformation,
                deviceAlias,
                serialPort,
                spectrumAcquisitionControl,
                networkConfiguration,
                ethernet,
                flashScratchPad
            };
#ifdef __cplusplus
        }
    }
}
#endif

#endif
