/*****************************************************
 * @file    SerialPortFeatureAdapter.h
 * @date    April 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect SerialPortFeatureInterface instances.
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

#ifndef OCEANDIRECT_SERIAL_PORT_FEATURE_ADAPTER_H
#define OCEANDIRECT_SERIAL_PORT_FEATURE_ADAPTER_H

#include <cstdint>
#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/serial_port/SerialPortFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class SerialPortFeatureAdapter : public FeatureAdapterTemplate<SerialPortFeatureInterface> {
        public:
            SerialPortFeatureAdapter(SerialPortFeatureInterface *intf,
                                     const FeatureFamily &f,
                                     Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~SerialPortFeatureAdapter();

            int getBaudRate(int *errorCode);
            void setBaudRate(int *errorCode, int baudRate);
            void saveSettingToFlash(int *errorCode);
            std::uint8_t getSerialCommThresholdMode(int* errorCode);
            void setSerialCommThresholdMode(int* errorCode, std::uint8_t thresholdMode);
        };

    }
}

#endif
