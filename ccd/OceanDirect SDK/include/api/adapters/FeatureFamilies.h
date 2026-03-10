/*****************************************************
 * @file    FeatureFamilies.h
 * @date    March 2021
 * @author  Ocean Optics, Inc.
 *
 * This provides a way to get references to different kinds
 * of features (e.g. spectrometer, TEC) generically.
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

#ifndef OCEANDIRECT_FEATUREFAMILIES_H
#define OCEANDIRECT_FEATUREFAMILIES_H

#include "common/features/FeatureFamily.h"
#include <vector>

namespace oceandirect {
    namespace api {

        class UndefinedFeatureFamily : public FeatureFamily {
        public:
            UndefinedFeatureFamily();
            virtual ~UndefinedFeatureFamily();
        };

        class SerialNumberFeatureFamily : public FeatureFamily {
        public:
            SerialNumberFeatureFamily();
            virtual ~SerialNumberFeatureFamily();
        };

        class SpectrometerFeatureFamily : public FeatureFamily {
        public:
            SpectrometerFeatureFamily();
            virtual ~SpectrometerFeatureFamily();
        };

        class ThermoElectricFeatureFamily : public FeatureFamily {
        public:
            ThermoElectricFeatureFamily();
            virtual ~ThermoElectricFeatureFamily();
        };

        class IrradCalFeatureFamily : public FeatureFamily {
        public:
            IrradCalFeatureFamily();
            virtual ~IrradCalFeatureFamily();
        };

        class EEPROMFeatureFamily : public FeatureFamily {
        public:
            EEPROMFeatureFamily();
            virtual ~EEPROMFeatureFamily();
        };

        class LightSourceFeatureFamily : public FeatureFamily {
        public:
            LightSourceFeatureFamily();
            virtual ~LightSourceFeatureFamily();
        };

        class StrobeLampFeatureFamily : public FeatureFamily {
        public:
            StrobeLampFeatureFamily();
            virtual ~StrobeLampFeatureFamily();
        };

        class ContinuousStrobeFeatureFamily : public FeatureFamily {
        public:
            ContinuousStrobeFeatureFamily();
            virtual ~ContinuousStrobeFeatureFamily();
        };

        class WaveCalFeatureFamily : public FeatureFamily {
        public:
            WaveCalFeatureFamily();
            virtual ~WaveCalFeatureFamily();
        };

        class NonlinearityCoeffsFeatureFamily : public FeatureFamily {
        public:
            NonlinearityCoeffsFeatureFamily();
            virtual ~NonlinearityCoeffsFeatureFamily();
        };

        class TemperatureFeatureFamily : public FeatureFamily {
        public:
            TemperatureFeatureFamily();
            virtual ~TemperatureFeatureFamily();
        };

        class RevisionFeatureFamily : public FeatureFamily {
        public:
            RevisionFeatureFamily();
            virtual ~RevisionFeatureFamily();
        };

        class OpticalBenchFeatureFamily : public FeatureFamily {
        public:
            OpticalBenchFeatureFamily();
            virtual ~OpticalBenchFeatureFamily();
        };

        class StrayLightCoeffsFeatureFamily : public FeatureFamily {
        public:
            StrayLightCoeffsFeatureFamily();
            virtual ~StrayLightCoeffsFeatureFamily();
        };

        class RawBusAccessFeatureFamily : public FeatureFamily {
        public:
            RawBusAccessFeatureFamily();
            virtual ~RawBusAccessFeatureFamily();
        };

        class DataBufferFeatureFamily : public FeatureFamily {
        public:
            DataBufferFeatureFamily();
            virtual ~DataBufferFeatureFamily();
        };

        class BackToBackFeatureFamily : public FeatureFamily {
        public:
            BackToBackFeatureFamily();
            virtual ~BackToBackFeatureFamily();
        };

        class AcquisitionDelayFeatureFamily : public FeatureFamily {
        public:
            AcquisitionDelayFeatureFamily();
            virtual ~AcquisitionDelayFeatureFamily();
        };

        class PixelBinningFeatureFamily : public FeatureFamily {
        public:
            PixelBinningFeatureFamily();
            virtual ~PixelBinningFeatureFamily();
        };

        class GpioFeatureFamily : public FeatureFamily {
        public:
            GpioFeatureFamily();
            virtual ~GpioFeatureFamily();
        };

        class HighGainModeFeatureFamily : public FeatureFamily {
        public:
            HighGainModeFeatureFamily();
            virtual ~HighGainModeFeatureFamily();
        };

        class SingleStrobeFeatureFamily : public FeatureFamily {
        public:
            SingleStrobeFeatureFamily();
            virtual ~SingleStrobeFeatureFamily();
        };

        class QueryStatusFeatureFamily : public FeatureFamily {
        public:
            QueryStatusFeatureFamily();
            virtual ~QueryStatusFeatureFamily();
        };

        class LEDActivityFeatureFamily : public FeatureFamily {
        public:
            LEDActivityFeatureFamily();
            virtual ~LEDActivityFeatureFamily();
        };

        class TimeFeatureFamily : public FeatureFamily {
        public:
            TimeFeatureFamily();
            virtual ~TimeFeatureFamily();
        };

        class DHCPServerConfigurationFeatureFamily : public FeatureFamily {
        public:
            DHCPServerConfigurationFeatureFamily();
            virtual ~DHCPServerConfigurationFeatureFamily();
         };

        class ShutterFeatureFamily : public FeatureFamily {
        public:
            ShutterFeatureFamily();
            virtual ~ShutterFeatureFamily();
         };

        class PixelFeatureFamily : public FeatureFamily {
        public:
            PixelFeatureFamily();
            virtual ~PixelFeatureFamily();
        };

        class AutoNullingFeatureFamily : public FeatureFamily {
        public:
            AutoNullingFeatureFamily();
            virtual ~AutoNullingFeatureFamily();
        };

        class UserStringFeatureFamily : public FeatureFamily {
        public:
            UserStringFeatureFamily();
            virtual ~UserStringFeatureFamily();
        };

        class DeviceInformationFeatureFamily : public FeatureFamily {
        public:
            DeviceInformationFeatureFamily();
            virtual ~DeviceInformationFeatureFamily();
        };

        class DeviceAliasFeatureFamily : public FeatureFamily {
        public:
            DeviceAliasFeatureFamily();
            virtual ~DeviceAliasFeatureFamily();
        };

        class SerialPortFeatureFamily : public FeatureFamily {
        public:
            SerialPortFeatureFamily();
            virtual ~SerialPortFeatureFamily();
        };

    class Ipv4AddressFeatureFamily : public FeatureFamily {
    public:
        Ipv4AddressFeatureFamily();
        virtual ~Ipv4AddressFeatureFamily();
    };

    class SpectrumAcquisitionControlFeatureFamily : public FeatureFamily {
    public:
        SpectrumAcquisitionControlFeatureFamily();
        virtual ~SpectrumAcquisitionControlFeatureFamily();
    };

    class NetworkConfigurationFeatureFamily : public FeatureFamily {
    public:
        NetworkConfigurationFeatureFamily();
        virtual ~NetworkConfigurationFeatureFamily();
    };

    class EthernetFeatureFamily : public FeatureFamily {
    public:
        EthernetFeatureFamily();
        virtual ~EthernetFeatureFamily();
    };

    class FlashScratchPadFeatureFamily : public FeatureFamily {
    public:
        FlashScratchPadFeatureFamily();
        virtual ~FlashScratchPadFeatureFamily();
    };

    class FeatureFamilies {
        public:
            const UndefinedFeatureFamily UNDEFINED;
            const SerialNumberFeatureFamily SERIAL_NUMBER;
            const SpectrometerFeatureFamily SPECTROMETER;
            const ThermoElectricFeatureFamily THERMOELECTRIC;
            const IrradCalFeatureFamily IRRAD_CAL;
            const EEPROMFeatureFamily EEPROM;
            const LightSourceFeatureFamily LIGHT_SOURCE;
            const StrobeLampFeatureFamily STROBE_LAMP_ENABLE;
            const ContinuousStrobeFeatureFamily CONTINUOUS_STROBE;
            const WaveCalFeatureFamily WAVELENGTH_CAL;
            const NonlinearityCoeffsFeatureFamily NONLINEARITY_COEFFS;
            const TemperatureFeatureFamily TEMPERATURE;
            const RevisionFeatureFamily REVISION;
            const OpticalBenchFeatureFamily OPTICAL_BENCH;
            const StrayLightCoeffsFeatureFamily STRAY_LIGHT_COEFFS;
            const RawBusAccessFeatureFamily RAW_BUS_ACCESS;
            const DataBufferFeatureFamily DATA_BUFFER;
            const BackToBackFeatureFamily BACK_TO_BACK;
            const AcquisitionDelayFeatureFamily ACQUISITION_DELAY;
            const PixelBinningFeatureFamily PIXEL_BINNING;
            const GpioFeatureFamily GPIO;
            const HighGainModeFeatureFamily HIGH_GAIN_MODE;
            const SingleStrobeFeatureFamily SINGLE_STROBE;
            const QueryStatusFeatureFamily QUERY_STATUS;
            const LEDActivityFeatureFamily LED_ACTIVITY;
            const TimeFeatureFamily TIME;
            const DHCPServerConfigurationFeatureFamily DHCP;
            const ShutterFeatureFamily SHUTTER;
            const PixelFeatureFamily PIXEL;
            const AutoNullingFeatureFamily AUTONULLING;
            const UserStringFeatureFamily USER_STRING;
            const DeviceInformationFeatureFamily DEVICE_INFORMATION;
            const DeviceAliasFeatureFamily DEVICE_ALIAS;
            const SerialPortFeatureFamily SERIAL_PORT;
            const Ipv4AddressFeatureFamily IPV4_ADDRESS;
            const SpectrumAcquisitionControlFeatureFamily SPECTRUM_ACQUISITION_CONTROL;
            const NetworkConfigurationFeatureFamily NETWORK_CONFIGURATION;
            const EthernetFeatureFamily ETHERNET;
            const FlashScratchPadFeatureFamily FLASH_SCRATCH_PAD;

            static const int FEATURE_FAMILY_ID_UNDEFINED;
            static const int FEATURE_FAMILY_ID_SERIAL_NUMBER;
            static const int FEATURE_FAMILY_ID_SPECTROMETER;
            static const int FEATURE_FAMILY_ID_THERMOELECTRIC;
            static const int FEATURE_FAMILY_ID_IRRADCAL;
            static const int FEATURE_FAMILY_ID_EEPROM;
            static const int FEATURE_FAMILY_ID_STROBE_LAMP;
            static const int FEATURE_FAMILY_ID_WAVECAL;
            static const int FEATURE_FAMILY_ID_NONLINEARITYCAL;
            static const int FEATURE_FAMILY_ID_STRAYLIGHTCAL;
            static const int FEATURE_FAMILY_ID_RAW_BUS_ACCESS;
            static const int FEATURE_FAMILY_ID_CONTINUOUS_STROBE;
            static const int FEATURE_FAMILY_ID_LIGHT_SOURCE;
            static const int FEATURE_FAMILY_ID_TEMPERATURE;
            static const int FEATURE_FAMILY_ID_OPTICAL_BENCH;
            static const int FEATURE_FAMILY_ID_REVISION;
            static const int FEATURE_FAMILY_ID_DATA_BUFFER;
            static const int FEATURE_FAMILY_ID_ACQUISITION_DELAY;
            static const int FEATURE_FAMILY_ID_PIXEL_BINNING;
            static const int FEATURE_FAMILY_ID_GPIO;
            static const int FEATURE_FAMILY_ID_HIGH_GAIN_MODE;
            static const int FEATURE_FAMILY_ID_SINGLE_STROBE;
            static const int FEATURE_FAMILY_ID_QUERY_STATUS;
            static const int FEATURE_FAMILY_ID_BACK_TO_BACK;
            static const int FEATURE_FAMILY_ID_LED_ACTIVITY;
            static const int FEATURE_FAMILY_ID_TIME;
            static const int FEATURE_FAMILY_ID_DHCP;
            static const int FEATURE_FAMILY_ID_SHUTTER;
            static const int FEATURE_FAMILY_ID_PIXEL;
            static const int FEATURE_FAMILY_ID_AUTONULLING;
            static const int FEATURE_FAMILY_ID_USER_STRING;
            static const int FEATURE_FAMILY_ID_DEVICE_INFORMATION;
            static const int FEATURE_FAMILY_ID_DEVICE_ALIAS;
            static const int FEATURE_FAMILY_ID_SERIAL_PORT;
            static const int FEATURE_FAMILY_ID_IPV4_ADDRESS;
            static const int FEATURE_FAMILY_ID_SPECTRUM_ACQUISITION_CONTROL;
            static const int FEATURE_FAMILY_ID_NETWORK_CONFIGURATION;
            static const int FEATURE_FAMILY_ID_ETHERNET;
            static const int FEATURE_FAMILY_ID_FLASH_SCRATCH_PAD;

            FeatureFamilies();
            ~FeatureFamilies();
            std::vector<FeatureFamily *> getAllFeatureFamilies();
        };
    }
}

#endif
