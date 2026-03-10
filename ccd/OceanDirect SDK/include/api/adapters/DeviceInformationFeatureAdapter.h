/*****************************************************
 * @file    DeviceInformationFeatureAdapter.h
 * @date    April 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect DeviceInformationFeatureInterface instances.
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

#ifndef OCEANDIRECT_DEVICE_INFORMATION_FEATURE_ADAPTER_H
#define OCEANDIRECT_DEVICE_INFORMATION_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/device_info/DeviceInformationFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class DeviceInformationFeatureAdapter : public FeatureAdapterTemplate<DeviceInformationFeatureInterface> {
        public:
            DeviceInformationFeatureAdapter(DeviceInformationFeatureInterface *intf,
                                            const FeatureFamily &f,
                                            Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~DeviceInformationFeatureAdapter();

            void resetDevice(int *errorCode);
            std::uint16_t getOriginalVID(int *errorCode);
            std::uint16_t getOriginalPID(int *errorCode);
            std::uint16_t getVID(int *errorCode);
            void setVID(int *errorCode, std::uint16_t vid);
            std::uint16_t getPID(int *errorCode);
            void setPID(int *errorCode, std::uint16_t pid);

            int getOriginalManufacturerString(int *errorCode, char *buffer, int bufferLength);
            int getOriginalModelString(int *errorCode, char *buffer, int bufferLength);
            int getManufacturerString(int *errorCode, char *buffer, int bufferLength);
            void setManufacturerString(int *errorCode, char *buffer, int bufferLength);
            int getModelString(int *errorCode, char *buffer, int bufferLength);
            void setModelString(int *errorCode, char *buffer, int bufferLength);

            int getCommandList(int *errorCode, std::uint32_t *buffer, int bufferLength);
            std::uint32_t getIntegrationTimeStepSize(int *errorCode);
        };
    }
}

#endif

