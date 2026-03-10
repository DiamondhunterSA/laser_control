#ifndef DEVICE_CONFIGURATION_H
#define DEVICE_CONFIGURATION_H

/*******************************************************
 * @file    DeviceConfiguration.h
 * @date    October 2022
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to connect to devices over USB and other buses.
 * This is intended as a usable and extensible API. The method
 * calls below represent the complete C and Python interface for
 * accessing an Ocean Insight spectrometer.
 *
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2020] Ocean Insight Incorporated
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
#include <vector>
#include <string>
namespace oceandirect {
    namespace api {
        class DeviceConfiguration {
            //get number pixels
        public:
            std::string spectrometerSerialNumber;
            std::string spectrometerType;
            bool initialized = false;
            bool useNLC = true;
            bool useEDC = true;
            int numPixels = 0;
            int numActivePixels = 0;
            int firstActivePixel = 0;
            int lastActivePixel = 0;
            double maximumIntensity = 65535.0;
            unsigned long currentIntegrationTime = 0;
            unsigned long minIntegrationTime = 1000;
            unsigned long maxIntegrationTime = 60000;
            std::vector<int> elecDarkLoc;
            //get electric dark pixel indices
            std::vector<int> electricDarkPixelIndices;
            //get number active pixels
            std::vector<double> nonlinCoeffs;
            //get wavelength coefficients
            std::vector<double> wavelengths;
            std::vector<double> irradCalFile;
            double irradCalCollectionArea = 1.0;
            //smoothTypeEnum smoothType = smoothTypeEnum::None;
            int smoothFactor = 0;
            bool stabilityScanNeeded = false;
        };
    }
}
#endif // !DEVICE_CONFIGURATION_H
