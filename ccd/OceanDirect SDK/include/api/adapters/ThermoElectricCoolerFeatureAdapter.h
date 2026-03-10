/*****************************************************
 * @file    ThermoElectricCoolerFeatureAdapter.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * TECFeatureInterface instances.
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

#ifndef OCEANDIRECT_THERMO_ELECTRIC_COOLER_FEATURE_ADAPTER_H
#define OCEANDIRECT_THERMO_ELECTRIC_COOLER_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/thermoelectric/ThermoElectricFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class ThermoElectricCoolerFeatureAdapter
                : public FeatureAdapterTemplate<ThermoElectricFeatureInterface> {
        public:
            ThermoElectricCoolerFeatureAdapter(ThermoElectricFeatureInterface *intf, const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~ThermoElectricCoolerFeatureAdapter();

            /* Thermoelectric cooler functions */
            double readTECTemperature(int *errorCode);
            void setTECTemperature(int *errorCode, double temperature_degrees_celsius);
            void setTECEnable(int *errorCode, bool tecEnable);
            bool getTECEnable(int *errorCode);
            float getTECSetpoint(int *errorCode);
            bool getTECStable(int *errorCode);
            bool getTECFanEnable(int *errorCode);
            void setTECFanEnable(int *errorCode, bool enable);
        };

    }
}

#endif
