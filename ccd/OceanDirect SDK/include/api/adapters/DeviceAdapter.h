#ifndef DEVICE_ADAPTER_H
#define DEVICE_ADAPTER_H
/*****************************************************
 * @file    DeviceAdapter.h
 * @date    August 2023
 * @author  Ocean Insight, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect Device instances.
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
#include "common/devices/IDevice.h"
#include <memory>

using oceandirect::IDevice;

namespace oceandirect {

    class Device;
    
    namespace api {

        class RawBusAccessFeatureAdapter;
        class SerialNumberFeatureAdapter;
        class SpectrometerFeatureAdapter;
        class ThermoElectricCoolerFeatureAdapter;
        class IrradCalFeatureAdapter;
        class EEPROMFeatureAdapter;
        class LightSourceFeatureAdapter;
        class StrobeLampFeatureAdapter;
        class ContinuousStrobeFeatureAdapter;
        class SingleStrobeFeatureAdapter;
        class GpioFeatureAdapter;
        class NonlinearityCoeffsFeatureAdapter;
        class TemperatureFeatureAdapter;
        class RevisionFeatureAdapter;
        class OpticalBenchFeatureAdapter;
        class StrayLightCoeffsFeatureAdapter;
        class PixelBinningFeatureAdapter;
        class DataBufferFeatureAdapter;
        class BackToBackFeatureAdapter;
        class AcquisitionDelayFeatureAdapter;
        class QueryStatusFeatureAdapter;
        class LedActivityFeatureAdapter;
        class TimeFeatureAdapter;
        class DHCPServerConfigurationFeatureAdapter;
        class PixelFeatureAdapter;
        class AutoNullingFeatureAdapter;
        class UserStringFeatureAdapter;
        class DeviceInformationFeatureAdapter;
        class DeviceAliasFeatureAdapter;
        class SerialPortFeatureAdapter;
        class Ipv4AddressFeatureAdapter;
        class SpectrumAcquisitionControlFeatureAdapter;
        class NetworkConfigurationFeatureAdapter;
        class EthernetFeatureAdapter;
        class ShutterFeatureAdapter;
        class HighGainModeFeatureAdapter;
        class FlashScratchPadFeatureAdapter;

        class DeviceAdapter :
            public IDevice {

        public:
            DeviceAdapter(std::unique_ptr<Device> dev, unsigned long id);
            ~DeviceAdapter();

            int open(int *errorCode) override;
            void close() override;

            DeviceLocatorInterface *getLocation() override;

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
                //bad pixel indices
                std::vector<int> badPixelIndices;
                //get wavelength coefficients
                std::vector<double> wavelengths;
                std::vector<double> irradCalFile;
                double irradCalCollectionArea = 1.0;
                //smoothTypeEnum smoothType = smoothTypeEnum::None;
                int smoothFactor = 0;
                bool stabilityScanNeeded = false;

            } deviceConfig;

            /* An for weak association to this object */
            unsigned long getID() override;
            Device* getDevice();

	        /* Get a string that describes the type of device */
	        int getDeviceType(int *errorCode, char *buffer, unsigned int maxLength) override;

	        /* Get a usb endpoint for the device according to the enumerator */
 	        /*  endpointType. A 0 is returned if the endpoint requested is not in use. */
	        unsigned char getDeviceEndpoint(int *errorCode, usbEndpointType anEndpointType) override;

	        /* check an array for saturation and set a warning code if saturated*/
	        int checkArrayForSaturation(std::vector<double> arrayToCheck, int *errorCode) override;

	        /* Get initial immutable properties of the spectrometer to save for future requests*/
	        int getDeviceConfiguration(int *errorCode) override;
	        int getDeviceConfigNumPixels();
	        const std::vector<int>& getDeviceConfigElecDarkPixels();
	        int applyDeviceConfigElecDarkPixels(int *errorCode, double *sample, int sampleSize);
	        const std::vector<double>& getDeviceConfigNonlinearityCoeffs();
	        int applyDeviceConfigNonlinearityCoeffs(int *errorCode, double *sample, int sampleSize);
            void applyDeviceConfigBoxcarWidth(int* errorCode, double* sample, int sampleSize);
            void applyDeviceConfigBadPixelsRemoval(int* errorCode, double* sample, int sampleSize) const;
	        std::vector<double> getDeviceConfigWavelengths() override;
	        std::vector<double> getDeviceConfigIrradCalFile() override;
	        double getDeviceConfigIrradCollectionArea() override;

            void applyElectricDarkCorrection(int* errorCode, bool value) override;
            bool electricDarkCorrectionUsage(int* errorCode) override;
            void applyNonLinearityCorrection(int* errorCode, bool value) override;
            bool nonLinearityCorrectionUsage(int* errorCode) override;

            int GetDeviceConfigSmoothFactor();
            unsigned long GetDeviceConfigMinIntegrationTime();
            unsigned long GetDeviceConfigMaxIntegrationTime();

            std::string getStringDescriptor(int* errorCode, int index) override;
            int rawBusAccessRead(int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint) override;
            int rawBusAccessWrite(int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint) override;
            int rawBusAccessRead(int* errorCode, unsigned char* buffer, unsigned int bufferLength) override;
            int rawBusAccessWrite(int* errorCode, unsigned char* buffer, unsigned int bufferLength) override;

            int getSerialNumber(int* errorCode, char* buffer, int bufferLength) override;
            void setSerialNumber(int* errorCode, char* buffer, int bufferLength) override;
            unsigned char getSerialNumberMaximumLength(int* errorCode) override;

            /* Get and set time features */
            long long int getTime(int *errorCode) override;
            void setTime(int *errorCode, long long int timeInMicroseconds) override;

            void setTriggerMode(int* errorCode, int mode) override;
            int getTriggerMode(int* errorCode) override;
            void setDelayMicroseconds(int* errorCode, unsigned long delayMicroseconds) override;
            unsigned long getDelayMicroseconds(int* errorCode) override;
            unsigned long getDelayIncrementMicroseconds(int* errorCode) override;
            unsigned long getDelayMaximumMicroseconds(int* errorCode) override;
            unsigned long getDelayMinimumMicroseconds(int* errorCode) override;

            void setIntegrationTimeMicros(int* errorCode, unsigned long integrationTimeMicros) override;
            unsigned long getIntegrationTimeMicros(int* errorCode) override;
            unsigned long getIntegrationTimeIncrementMicros(int* errorCode) override;

            unsigned long getMinimumIntegrationTimeMicros(int* errorCode) override;
            unsigned long getMinimumAveragingIntegrationTimeMicros(int* errorCode) override;
            unsigned long getMaximumIntegrationTimeMicros(int* errorCode) override;
            double getMaximumIntensity(int* errorCode) override;
            int getUnformattedSpectrumLength(int* errorCode) override;
            int getUnformattedSpectrum(int* errorCode, unsigned char* buffer, int bufferLength) override;
            int getFormattedSpectrumLength(int* errorCode) override;
            int getFormattedSpectrum(int* errorCode, double* buffer, int bufferLength) override;
            int getFormattedSpectrumWithMetadata(int* errorCode, SpectrumWithMetadata* buffer, int bufferLength) override;

            void setStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength) override;
            int getStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength) override;
            int getDarkCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) override;
            int darkCorrectSpectrum(int* errorCode, double* illuminatedSpectrum, int illuminatedSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) override;
            int getDarkCorrectedSpectrum(int* errorCode, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) override;
            int darkCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) override;

            int getNonlinearityCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength) override;
            int nonlinearityCorrectSpectrum(int* errorCode, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength) override;
            int getNonlinearityCorrectedSpectrum(int* errorCode, double* nonlinearityCorrectedSpectrum,
                int nonlinearityCorrectedSpectrumLength) override;
            int nonlinearityCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength) override;

            void boxcarCorrectSpectrum(int* errorCode, const double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength, unsigned int boxcarWidth,
                                       double* boxcarCorrectedSpectrum, unsigned int boxcarCorrectedSpectrumLength) override;

            int getWavelengths(int* errorCode, double* wavelengths, int length) override;
            int getWavelengthCoefficients(int* errorCode, double* coeff, int length) override;
            void setWavelengthCoefficients(int* errorCode, double* coeff, int length) override;
            int getElectricDarkPixelCount(int* errorCode) override;
            int getElectricDarkPixelIndices(int* errorCode, int* indices, int length) override;
            unsigned int getScansToAverage(int* errorCode) override;
            unsigned short int getBoxcarWidth(int* errorCode) override;
            void setBoxcarWidth(int* errorCode, unsigned short int newBoxcarWidth) override;
            void setScansToAverage(int* errorCode, unsigned int newScansToAverage) override;

            /* Query status features */
            int getNumberOfStatusFeatures();
            int getStatusFeatures(long *buffer, int maxFeatures);
            int statusReadStatus(long statusFeatureId, int *errorCode, unsigned char *buffer, int bufferLength);
            unsigned long statusGetIntegrationTime(long statusFeatureID, int *errorCode);

            void setPixelBinningFactor(int* errorCode, const unsigned char binningFactor) override;
            unsigned char getPixelBinningFactor(int* errorCode) override;
            void setDefaultPixelBinningFactor(int* errorCode, const unsigned char binningFactor) override;
            void setDefaultPixelBinningFactor(int* errorCode) override;
            unsigned char getDefaultPixelBinningFactor(int* errorCode) override;
            unsigned char getMaxPixelBinningFactor(int* errorCode) override;

            double readTecTemperatureDegreesC(int* errorCode) override;
            void setTecTemperatureSetpointDegreesC(int* errorCode, double temperatureDegreesCelsius) override;
            void setTecEnable(int* errorCode, bool tecEnable) override;
            bool getTecEnable(int* errorCode) override;
            float getTecSetpoint(int* errorCode) override;
            bool getTecStable(int* errorCode) override;
            bool getTecFanEnable(int* errorCode) override;
            void setTecFanEnable(int* errorCode, bool enable) override;

            int readIrradCalibration(int* errorCode, double* buffer, int bufferLength) override;
            int readIrradCalibrationSize(int* errorCode) override;
            int writeIrradCalibration(int* errorCode, double* buffer, int bufferLength) override;
            bool hasIrradCalibrationCollectionArea(int* errorCode) override;
            float readIrradCalibrationCollectionArea(int* errorCode) override;
            void writeIrradCalibrationCollectionArea(int* errorCode, float area) override;

            int readEepromSlot(int* errorCode, int slotNumber,
                unsigned char* buffer, int length) override;

            int getLightSourceCount(int* errorCode) override;
            bool hasLightSourceEnable(int* errorCode, int lightSourceIndex) override;
            bool isLightSourceEnabled(int* errorCode, int lightSourceIndex) override;
            void setLightSourceEnable(int* errorCode, int lightSourceIndex, bool enable) override;
            bool hasLightSourceVariableIntensity(int* errorCode, int lightSourceIndex) override;
            double getLightSourceIntensity(int* errorCode, int lightSourceIndex) override;
            void setLightSourceIntensity(int* errorCode, int lightSourceIndex, double intensity) override;
            void setLampStrobeEnable(int* errorCode, bool strobeEnable) override;
            bool getLampStrobeEnable(int* errorCode) override;

            unsigned long getContinuousStrobePeriodMicroseconds(int* errorCode) override;
            bool getContinuousStrobeEnable(int* errorCode) override;
            unsigned long getContinuousStrobePeriodMinimumMicroseconds(int* errorCode) override;
            unsigned long getContinuousStrobePeriodMaximumMicroseconds(int* errorCode) override;
            unsigned long getContinuousStrobePeriodIncrementMicroseconds(int* errorCode) override;
            unsigned long getContinuousStrobeWidthMicroseconds(int* errorCode) override;
            void setContinuousStrobePeriodMicroseconds(int* errorCode, unsigned long period_usec) override;
            void setContinuousStrobeEnable(int* errorCode, bool enable) override;
            void setContinuousStrobeWidthMicroseconds(int* errorCode, unsigned long strobeWidthMicroseconds) override;

            int getGpioCount(int* errorCode) override;
            void setGpioOutputEnable(int* errorCode, std::uint32_t bitPosition, bool isOutput) override;
            void setGpioOutputEnable(int* errorCode, std::uint32_t bits, std::uint32_t bitmask) override;
            bool getGpioOutputEnable(int* errorCode, int bit) override;
            uint32_t getGpioOutputEnable(int* errorCode) override;
            void setGpioValue(int* errorCode, std::uint32_t bitPosition, bool value) override;
            void setGpioValue(int* errorCode, uint32_t bitmask) override;
            void setGpioValue(int* errorCode, uint32_t bits, uint32_t bitmask) override;
            bool getGpioValue(int* errorCode, int bit) override;
            uint32_t getGpioValue(int* errorCode) override;
            void setGpioOutputAlternate(int* errorCode, int bit, bool isAlternate) override;
            void setGpioOutputAlternate(int* errorCode, uint32_t bitMask) override;
            bool getGpioOutputAlternate(int* errorCode, int bit) override;
            uint32_t getGpioOutputAlternate(int* errorCode) override;

            int getNonlinearityCoeffsCount(int* errorCode) override;
            double getNonlinearityCoeffs(int* errorCode, int index) override;
            void setNonlinearityCoeffs(int* errorCode, int index, double coefficient) override;
            int getNonlinearityCoeffs(int* errorCode, double* buffer, int bufferLength) override;
            int setNonlinearityCoeffs(int* errorCode, double* buffer, int bufferLength) override;

            int getTemperatureCount(int* errorCode) override;
            double getTemperature(int* errorCode, int index) override;
            double getTemperatureExtreme(int* errorCode) override;
            int getAllTemperatures(int* errorCode, double* buffer, int max_length) override;

            int getRevisionHardware(int* errorCode, char* buffer, int bufferLength) override;
            int getRevisionFirmware(int* errorCode, char* buffer, int bufferLength) override;
            int getRevisionFPGA(int* errorCode, char* buffer, int bufferLength) override;
            int getRevisionSystem(int* errorCode, char* buffer, int bufferLength) override;

            int getOpticalBenchArrayWavelength(int* errorCode, char* buffer, int bufferLength) override;
            unsigned short int getOpticalBenchSlitWidthMicrons(int* errorCode) override;
            void setOpticalBenchSlitWidthMicrons(int* errorCode, unsigned short int widthMicrons) override;
            int getOpticalBenchSerialNumber(int* errorCode, char* buffer, int bufferLength) override;
            void setOpticalBenchSerialNumber(int* errorCode, char* buffer, int bufferLength) override;
            int getOpticalBenchId(int* errorCode, char* buffer, int bufferLength) override;
            void setOpticalBenchId(int* errorCode, char* buffer, int bufferLength) override;
            unsigned short int getOpticalBenchFiberDiameter(int* errorCode) override;
            void setOpticalBenchFiberDiameter(int* errorCode, unsigned short int diameterMicrons) override;
            int getOpticalBenchCoating(int* errorCode, char* buffer, int bufferLength) override;
            void setOpticalBenchCoating(int* errorCode, char* buffer, int bufferLength) override;
            int getOpticalBenchFilter(int* errorCode, char* buffer, int bufferLength) override;
            void setOpticalBenchFilter(int* errorCode, char* buffer, int bufferLength) override;
            int getOpticalBenchGrating(int* errorCode, char* buffer, int bufferLength) override;
            void setOpticalBenchGrating(int* errorCode, char* buffer, int bufferLength) override;
            int getOpticalBenchLensInstalled(int* errorCode, char* buffer, int bufferLength) override;

            int getStrayLightCoeffs(int* errorCode, double* buffer, int bufferLength) override;

            void dataBufferClear(int* errorCode) override;
            unsigned long getDataBufferNumberOfElements(int* errorCode) override;
            unsigned long getDataBufferBufferCapacity(int* errorCode) override;
            unsigned long getDataBufferBufferCapacityMaximum(int* errorCode) override;
            unsigned long getDataBufferBufferCapacityMinimum(int* errorCode) override;
            void setDataBufferBufferCapacity(int* errorCode, unsigned long capacity) override;
            void setDataBufferBufferEnabled(int* errorCode, bool enabled) override;
            bool getDataBufferBufferEnabled(int* errorCode) override;

            void abortAcquisition(int* errorCode) override;
            void acquireSpectraToBuffer(int* errorCode) override;
            bool getDeviceIdleState(int* errorCode) override;

            unsigned long getBackToBackNumScans(int* errorCode) override;
            void setBackToBackNumScans(int* errorCode, unsigned long numScans) override;

            void setSingleStrobeDelayMicroseconds(int* errorCode, unsigned long period_usec) override;
            void setSingleStrobeWidthMicroseconds(int* errorCode, unsigned long period_usec) override;
            void setSingleStrobeEnable(int* errorCode, bool enable) override;
            unsigned long getSingleStrobeDelayMicroseconds(int* errorCode) override;
            unsigned long getSingleStrobeWidthMicroseconds(int* errorCode) override;
            bool getSingleStrobeEnable(int* errorCode) override;
            unsigned long  getSingleStrobeDelayMinimumMicroseconds(int* errorCode) override;
            unsigned long  getSingleStrobeDelayMaximumMicroseconds(int* errorCode) override;
            unsigned long  getSingleStrobeWidthMinimumMicroseconds(int* errorCode) override;
            unsigned long  getSingleStrobeWidthMaximumMicroseconds(int* errorCode) override;
            unsigned long  getSingleStrobeCycleMaximumMicroseconds(int* errorCode) override;
            unsigned long  getSingleStrobeDelayIncrementMicroseconds(int* errorCode) override;
            unsigned long  getSingleStrobeWidthIncrementMicroseconds(int* errorCode) override;


            bool getLedActivityEnable(int* errorCode) override;
            void setLedActivityEnable(int* errorCode, bool enable) override;


            bool isDHCPServerEnabled(int* errorCode, unsigned char ifNum) override;
            void setDHCPServerEnable(int* errorCode, unsigned char ifNum, bool enable) override;
            void getDHCPServerAddressRange(int* errorCode, unsigned char ifNum,
                unsigned int* outBaseIpAddress, unsigned int ipAddressArraySize, unsigned int* outNetmask) override;
            void setDHCPServerAddressRange(int* errorCode, unsigned char ifNum,
                const unsigned int* baseIpAddress, unsigned int ipAddressArraySize, unsigned int netmask) override;

            bool getDHCPEnabled(int* errorCode, unsigned char ifNum) override;
            void setDHCPEnable(int* errorCode, unsigned char ifNum, unsigned char enabled) override;
            int getNumberOfIpAddresses(int* errorCode, unsigned char ifNum) override;
            void getIpAddress(int* errorCode, unsigned char ifNum, unsigned char addressIndex,
                unsigned char* ipAddress, int ipAddressLength, unsigned int* netmask) override;
            void addStaticIpAddress(int* errorCode, unsigned char ifNum,
                unsigned char* ipAddress, int ipAddressLength, unsigned int netmask) override;
            void deleteStaticIpAddress(int* errorCode, unsigned char ifNum, unsigned char addressIndex) override;
            void setDefaultGatewayIpAddress(int* errorCode, unsigned char ifNum, unsigned char* ipAddress, int ipAddressLength) override;
            void getDefaultGatewayIpAddress(int* errorCode, unsigned char ifNum, unsigned char* outIpAddress, int ipAddressLength) override;

            int getPixelCount(int* error_code) override;
            int getActivePixelRange(int* error_code, int* range, int rangeSize) override;
            int getActivePixelCount(int* error_code) override;
            int getOpticalDarkPixelCount(int* error_code) override;
            int getOpticalDarkPixelIndices(int* error_code, int* indices, int indicesSize) override;
            int getOpticalDarkPixelRange(int* error_code, int* range, int rangeSize) override;
            int getTransitionPixelCount(int* error_code) override;
            int getTransitionPixelRange(int* error_code, int* range, int rangeSize) override;
            int getBadPixelIndices(int* error_code, int* baxPixelIndices, int baxPixelSize) override;
            void setBadPixelIndices(int* error_code, int* baxPixelIndices, int baxPixelSize) override;

            int getMaximumADCCount(int* error_code) override;
            int getSaturationLevel(int* error_code) override;
            void setSaturationLevel(int* error_code, int level) override;
            int getBaselineLevel(int* error_code) override;
            void setBaselineLevel(int* error_code, int level) override;
            int getFPGADigitalGain(int* error_code) override;
            void setFPGADigitalGain(int* error_code, int gain) override;
            int getFPGADigitalOffset(int* error_code) override;
            void setFPGADigitalOffset(int* error_code, int offset) override;
            void getBaselineLevelConstraints(int* error_code, std::uint32_t& minDAC, std::uint32_t& maxDAC, float& minVolts, float& maxVolts) override;
            void getSaturationLevelConstraints(int* error_code, std::uint32_t& minDAC, std::uint32_t& maxDAC, float& minVolts, float& maxVolts) override;

            int getUserString(int* errorCode, char* buffer, int bufferLength) override;
            void setUserString(int* errorCode, char* buffer, int bufferLength) override;
            int getUserStringCount(int* errorCode) override;
            int getUserString(int* errorCode, int index, char* buffer, int bufferLength) override;
            void setUserString(int* errorCode, int index, char* buffer, int bufferLength) override;

            int getDeviceAlias(int* errorCode, char* buffer, int bufferLength) override;
            void setDeviceAlias(int* errorCode, char* buffer, int bufferLength) override;

            void resetDevice(int* errorCode) override;
            std::uint16_t getOriginalVID(int* errorCode) override;
            std::uint16_t getOriginalPID(int* errorCode) override;
            std::uint16_t getVID(int* errorCode) override;
            void setVID(int* errorCode, std::uint16_t vid) override;
            std::uint16_t getPID(int* errorCode) override;
            void setPID(int* errorCode, std::uint16_t pid) override;
            int getOriginalManufacturerString(int* errorCode, char* buffer, int bufferLength) override;
            int getOriginalModelString(int* errorCode, char* buffer, int bufferLength) override;
            int getManufacturerString(int* errorCode, char* buffer, int bufferLength) override;
            void setManufacturerString(int* errorCode, char* buffer, int bufferLength) override;
            int getModelString(int* errorCode, char* buffer, int bufferLength) override;
            void setModelString(int* errorCode, char* buffer, int bufferLength) override;
            std::uint32_t getIntegrationTimeStepSize(int* errorCode) /*override*/;

            int getBaudRate(int* errorCode) override;
            void setBaudRate(int* errorCode, int baudRate) override;
            void saveSettingsToFlash(int* errorCode) override;
            std::uint8_t getSerialCommThresholdMode(int* errorCode) override;
            void setSerialCommThresholdMode(int* errorCode, std::uint8_t thresholdMode) override;

            /* Network configuration (interface) features */
            std::uint32_t getNetworkInterfaceCount(int* errorCode) override;
            std::uint32_t getNetworkInterfaceType(int* errorCode, std::uint32_t interfaceIndex) override;
            bool getNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex) override;
            void setNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable) override;
            bool getMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex) override;
            void setMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex, bool enable) override;
            void saveNetworkInterfaceSetting(int* errorCode, std::uint32_t interfaceIndex) override;

            bool getIPAddressAssignedMode(int* errorCode) override;
            void setIPAddressAssignedMode(int* errorCode, bool useDHCP) override;
            void getNetworkConfiguration(int* errorCode, bool& outIPAddressAssignment,
                                         std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                         std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                         std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                         std::uint8_t* outDNSServer, std::uint32_t dnsServerSize) override;
            void setManualNetworkConfiguration(int* errorCode,
                                               const std::uint8_t* ipv4Address, std::uint32_t ipv4AddressSize,
                                               const std::uint8_t* subnetMask, std::uint32_t subnetMaskSize,
                                               const std::uint8_t* defaultGateway, std::uint32_t defaultGatewaySize,
                                               const std::uint8_t* dnsServer, std::uint32_t dnsServerSize) override;
            void getManualNetworkConfiguration(int* errorCode,
                                               std::uint8_t* outIpv4Address, std::uint32_t ipv4AddressSize,
                                               std::uint8_t* outSubnetMask, std::uint32_t subnetMaskSize,
                                               std::uint8_t* outDefaultGateway, std::uint32_t defaultGatewaySize,
                                               std::uint8_t* outDNSServer, std::uint32_t dnsServerSize) override;
            bool getEthernetAddOnAvailable(int* errorCode) override;
            void getEthernetMACAddress(int* errorCode, std::uint8_t* outMACAddress, std::uint32_t outMACAddressSize) override;
            void setEthernetMACAddress(int* errorCode, const std::uint8_t* macAddress, std::uint32_t macAddressSize) override;
            bool getEthernetLoopBackTest(int* errorCode) override;

            /* Ethernet features */
            bool getGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex) override;
            void setGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable) override;
            void getMACAddress(int* errorCode, std::uint32_t interfaceIndex, std::uint8_t* macAddress, std::uint32_t macAddressLength) override;
            void setMACAddress(int* errorCode, std::uint32_t interfaceIndex, const std::uint8_t* macAddress, std::uint32_t macAddressLength) override;

            /* Shutter features */
            void setShutterOpen(int* errorCode, bool opened) override;
            bool getShutterState(int* errorCode) override;

            /* High Gain Mode features */
            void setHighGainMode(int* errorCode, bool enableHighGain) override;
            bool getHighGainMode(int* errorCode) override;
            void setSensorGainMode(int* errorCode, bool enableHighGain, bool enableStandardGain) override;
            void getSensorGainMode(int* errorCode, bool& outHighGain, bool& outStandardGain) override;
            bool getSensorGainHWState(int* errorCode) override;

            /* Flash and I2C commands - OBP2 only*/
            void setI2CData(int* errorCode, std::uint32_t i2cBusIndex, std::uint32_t i2cTargetAddress,
                            const std::uint8_t* data, std::uint32_t dataSize) override;
            bool getAccessoryBoardAvailable(int* errorCode) override;
            int  getFlashSlotData(int* errorCode, std::uint32_t slotNumber, std::uint8_t* outData, std::uint32_t outDataSize) override;
            void setFlashSlotData(int* errorCode, std::uint32_t slotNumber, const std::uint8_t* data, std::uint32_t dataSize) override;

    private:
        // get command list and get device parameters are part of the interface but are not supported by legacy devices so these commands are private here
        int getCommandList(int* errorCode, unsigned int* commands, int length) override;
        std::string getDeviceParameters(int* errorCode) override;

        /* Get one or more raw bus access features */
        int getNumberOfRawBusAccessFeatures();
        int getRawBusAccessFeatures(long* buffer, int maxFeatures);
        std::string getStringDescriptor(long featureID, int* errorCode, int index);
        int rawBusAccessRead(long featureID, int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint);
        int rawBusAccessWrite(long featureID, int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint);
        int rawBusAccessRead(long featureID, int* errorCode, unsigned char* buffer, unsigned int bufferLength);
        int rawBusAccessWrite(long featureID, int* errorCode, unsigned char* buffer, unsigned int bufferLength);

        /* Get one or more serial number features */
        int getNumberOfSerialNumberFeatures();
        int getSerialNumberFeatures(long* buffer, int maxFeatures);
        int getSerialNumber(long featureID, int* errorCode, char* buffer, int bufferLength);
        void setSerialNumber(long featureID, int* errorCode, char* buffer, int bufferLength);
        unsigned char getSerialNumberMaximumLength(long featureID, int* errorCode);

        /* Get and set time features */
        long long int getTime(long featureID, int* errorCode);
        void setTime(long featureID, int* errorCode, long long int timeInMicroseconds);

        /* Get one or more spectrometer acquisition features */
        int getNumberOfSpectrometerFeatures();
        int getSpectrometerFeatures(long* buffer, int maxFeatures);
        void spectrometerSetTriggerMode(long featureID, int* errorCode, int mode);
        int spectrometerGetTriggerMode(long featureID, int* errorCode);
        void spectrometerSetDelayMicroseconds(long featureID, int* errorCode, unsigned long delayMicroseconds);
        unsigned long spectrometerGetDelayMicroseconds(long featureID, int* errorCode);
        unsigned long spectrometerGetDelayIncrementMicroseconds(long featureID, int* errorCode);
        unsigned long spectrometerGetDelayMaximumMicroseconds(long featureID, int* errorCode);
        unsigned long spectrometerGetDelayMinimumMicroseconds(long featureID, int* errorCode);

        void spectrometerSetIntegrationTimeMicros(long spectrometerFeatureID, int* errorCode, unsigned long integrationTimeMicros);
        unsigned long spectrometerGetIntegrationTimeMicros(long spectrometerFeatureID, int* errorCode);
        unsigned long spectrometerGetIntegrationTimeIncrementMicros(long spectrometerFeatureID, int* errorCode);

        unsigned long spectrometerGetMinimumIntegrationTimeMicros(long spectrometerFeatureID, int* errorCode);
        unsigned long spectrometerGetMinimumAveragingIntegrationTimeMicros(long spectrometerFeatureID, int* errorCode);
        unsigned long spectrometerGetMaximumIntegrationTimeMicros(long spectrometerFeatureID, int* errorCode);
        double spectrometerGetMaximumIntensity(long spectrometerFeatureID, int* errorCode);
        int spectrometerGetUnformattedSpectrumLength(long spectrometerFeatureID, int* errorCode);
        int spectrometerGetUnformattedSpectrum(long spectrometerFeatureID, int* errorCode, unsigned char* buffer, int bufferLength);
        int spectrometerGetFormattedSpectrumLength(long spectrometerFeatureID, int* errorCode);
        int spectrometerGetFormattedSpectrum(long spectrometerFeatureID, int* errorCode, double* buffer, int bufferLength);
        int spectrometerGetFormattedSpectrumWithMetadata(long spectrometerFeatureID, int* errorCode, SpectrumWithMetadata* buffer, int bufferLength);

        void spectrometerSetStoredDarkSpectrum(long spectrometerFeatureID, int* errorCode, double* darkSpectrum, int darkSpectrumLength);
        int spectrometerGetStoredDarkSpectrum(long spectrometerFeatureID, int* errorCode, double* darkSpectrum, int darkSpectrumLength);
        int spectrometerGetDarkCorrectedSpectrum(long spectrometerFeatureID, int* errorCode, double* darkSpectrum, int darkSpectrumLength,
            double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
        int spectrometerDarkCorrectSpectrum(long spectrometerFeatureID, int* errorCode, double* illuminatedSpectrum, int illuminatedSpectrumLength,
            double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
        int spectrometerGetDarkCorrectedSpectrum(long spectrometerFeatureID, int* errorCode, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
        int spectrometerDarkCorrectSpectrum(long spectrometerFeatureID, int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
            int illuminatedSpectrumLength, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

        int spectrometerGetNonlinearityCorrectedSpectrum(long spectrometerFeatureID, int* errorCode, double* darkSpectrum, int darkSpectrumLength,
            double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
        int spectrometerNonlinearityCorrectSpectrum(long spectrometerFeatureID, int* errorCode, double* illuminatedSpectrum,
            int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
        int spectrometerGetNonlinearityCorrectedSpectrum(long spectrometerFeatureID, int* errorCode, double* nonlinearityCorrectedSpectrum,
            int nonlinearityCorrectedSpectrumLength);
        int spectrometerNonlinearityCorrectSpectrum(long spectrometerFeatureID, int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
            int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
        void spectrometerBoxcarCorrectSpectrum(long spectrometerFeatureID, int* errorCode, const double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength,
            unsigned int boxcarWidth, double* boxcarCorrectedSpectrum, unsigned int boxcarCorrectedSpectrumLength);

        int spectrometerGetWavelengths(long spectrometerFeatureID, int* errorCode, double* wavelengths, int length);
        int spectrometerGetWavelengthCoefficients(long spectrometerFeatureID, int* errorCode, double* coeff, int length);
        void spectrometerSetWavelengthCoefficients(long spectrometerFeatureID, int* errorCode, double* coeff, int length);
        int spectrometerGetElectricDarkPixelCount(long spectrometerFeatureID, int* errorCode);
        int spectrometerGetElectricDarkPixelIndices(long spectrometerFeatureID, int* errorCode, int* indices, int length);
        unsigned int spectrometerGetScansToAverage(long spectrometerFeatureID, int* errorCode);
        unsigned short int spectrometerGetBoxcarWidth(long spectrometerFeatureID, int* errorCode);
        void spectrometerSetBoxcarWidth(long spectrometerFeatureID, int* errorCode, unsigned short int newBoxcarWidth);
        void spectrometerSetScansToAverage(long spectrometerFeatureID, int* errorCode, unsigned int newScansToAverage);

        /* Get one or more pixel binning features */
        int getNumberOfPixelBinningFeatures();
        int getPixelBinningFeatures(long* buffer, int maxFeatures);
        void binningSetPixelBinningFactor(long spectrometerFeatureID, int* errorCode, const unsigned char binningFactor);
        unsigned char binningGetPixelBinningFactor(long spectrometerFeatureID, int* errorCode);
        void binningSetDefaultPixelBinningFactor(long spectrometerFeatureID, int* errorCode, const unsigned char binningFactor);
        void binningSetDefaultPixelBinningFactor(long spectrometerFeatureID, int* errorCode);
        unsigned char binningGetDefaultPixelBinningFactor(long spectrometerFeatureID, int* errorCode);
        unsigned char binningGetMaxPixelBinningFactor(long spectrometerFeatureID, int* errorCode);

        /* Get one or more TEC features */
        int getNumberOfThermoElectricFeatures();
        int getThermoElectricFeatures(long* buffer, int maxFeatures);
        double tecReadTemperatureDegreesC(long featureID, int* errorCode);
        void tecSetTemperatureSetpointDegreesC(long featureID, int* errorCode, double temperatureDegreesCelsius);
        void tecSetEnable(long featureID, int* errorCode, bool tecEnable);
        bool tecGetEnable(long featureID, int* errorCode);
        float tecGetSetpoint(long featureID, int* errorCode);
        bool tecGetStable(long featureID, int* errorCode);
        bool tecGetFanEnable(long featureID, int* errorCode);
        void tecSetFanEnable(long featureID, int* errorCode, bool enable);

        /* Get one or more irradiance calibration features */
        int getNumberOfIrradCalFeatures();
        int getIrradCalFeatures(long* buffer, int maxFeatures);
        int irradCalibrationRead(long featureID, int* errorCode, double* buffer, int bufferLength);
        int irradCalibrationSizeRead(long featureID, int* errorCode);
        int irradCalibrationWrite(long featureID, int* errorCode, double* buffer, int bufferLength);
        bool irradCalibrationHasCollectionArea(long featureID, int* errorCode);
        float irradCalibrationReadCollectionArea(long featureID, int* errorCode);
        void irradCalibrationWriteCollectionArea(long featureID, int* errorCode, float area);

        /* Get one or more EEPROM features */
        int getNumberOfEEPROMFeatures();
        int getEEPROMFeatures(long* buffer, int maxFeatures);
        int eepromReadSlot(long featureID, int* errorCode, int slotNumber,
            unsigned char* buffer, int length);

        /* Get one or more light source features */
        int getNumberOfLightSourceFeatures();
        int getLightSourceFeatures(long* buffer, int maxFeatures);
        int lightSourceGetCount(long featureID, int* errorCode);
        bool lightSourceHasEnable(long featureID, int* errorCode, int lightSourceIndex);
        bool lightSourceIsEnabled(long featureID, int* errorCode, int lightSourceIndex);
        void lightSourceSetEnable(long featureID, int* errorCode, int lightSourceIndex, bool enable);
        bool lightSourceHasVariableIntensity(long featureID, int* errorCode, int lightSourceIndex);
        double lightSourceGetIntensity(long featureID, int* errorCode, int lightSourceIndex);
        void lightSourceSetIntensity(long featureID, int* errorCode, int lightSourceIndex, double intensity);

        /* Get one or more strobe lamp enable features */
        int getNumberOfStrobeLampFeatures();
        int getStrobeLampFeatures(long* buffer, int maxFeatures);
        void lampSetStrobeEnable(long featureID, int* errorCode, bool strobeEnable);
        bool lampGetStrobeEnable(long featureID, int* errorCode);

        /* Get one or more continuous strobe features */
        int getNumberOfContinuousStrobeFeatures();
        int getContinuousStrobeFeatures(long* buffer, int maxFeatures);
        unsigned long continuousStrobeGetPeriodMicroseconds(long featureID, int* errorCode);
        bool continuousStrobeGetEnable(long featureID, int* errorCode);
        unsigned long continuousStrobeGetPeriodMinimumMicroseconds(long featureID, int* errorCode);
        unsigned long continuousStrobeGetPeriodMaximumMicroseconds(long featureID, int* errorCode);
        unsigned long continuousStrobeGetPeriodIncrementMicroseconds(long featureID, int* errorCode);
        unsigned long continuousStrobeGetWidthMicroseconds(long featureID, int* errorCode);
        void continuousStrobeSetPeriodMicroseconds(long featureID, int* errorCode, unsigned long period_usec);
        void continuousStrobeSetEnable(long featureID, int* errorCode, bool enable);
        void continuousStrobeSetWidthMicroseconds(long featureID, int* errorCode, unsigned long strobeWidthMicroseconds);

        /* Get one or more gpio features */
        int getNumberOfGpioFeatures();
        int getGpioFeatures(long* buffer, int maxFeatures);
        int getGpioCount(long featureID, int* errorCode);
        void gpioSetOutputEnable(long featureID, int* errorCode, std::uint32_t bitPosition, bool isOutput);
        void gpioSetOutputEnable(long featureID, int* errorCode, std::uint32_t bits, std::uint32_t bitmask);
        bool gpioGetOutputEnable(long featureID, int* errorCode, int bit);
        uint32_t gpioGetOutputEnable(long featureID, int* errorCode);
        void gpioSetValue(long featureID, int* errorCode, std::uint32_t bitPosition, bool value);
        void gpioSetValue(long featureID, int* errorCode, uint32_t bitmask);
        void gpioSetValue(long featureID, int* errorCode, uint32_t bits, uint32_t bitmask);
        bool gpioGetValue(long featureID, int* errorCode, int bit);
        uint32_t gpioGetValue(long featureID, int* errorCode);
        void gpioSetOutputAlternate(long featureID, int* errorCode, int bit, bool isAlternate);
        void gpioSetOutputAlternate(long featureID, int* errorCode, uint32_t bitMask);
        bool gpioGetOutputAlternate(long featureID, int* errorCode, int bit);
        uint32_t gpioGetOutputAlternate(long featureID, int* errorCode);

        /* Get one or more nonlinearity coefficients features */
        int getNumberOfNonlinearityCoeffsFeatures();
        int getNonlinearityCoeffsFeatures(long* buffer, int maxFeatures);

        int getNonlinearityCoeffsCount(long featureID, int* errorCode);
        double getNonlinearityCoeffs(long featureID, int* errorCode, int index);
        void setNonlinearityCoeffs(long featureID, int* errorCode, int index, double coefficient);
        int nonlinearityCoeffsGet(long featureID, int* errorCode, double* buffer, int bufferLength);
        int nonlinearityCoeffsSet(long featureID, int* errorCode, double* buffer, int bufferLength);

        /* Get one or more temperature features */
        int getNumberOfTemperatureFeatures();
        int getTemperatureFeatures(long* buffer, int maxFeatures);
        int temperatureCountGet(long temperatureFeatureID, int* errorCode);
        double temperatureGet(long temperatureFeatureID, int* errorCode, int index);
        double getTemperatureExtreme(long temperatureFeatureID, int* errorCode);
        int getAllTemperatures(long temperatureFeatureID, int* errorCode, double* buffer, int max_length);

        /* Get one or more revision features */
        int getNumberOfRevisionFeatures();
        int getRevisionFeatures(long* buffer, int maxFeatures);
        int revisionHardwareGet(long featureID, int* errorCode, char* buffer, int bufferLength);
        int revisionFirmwareGet(long featureID, int* errorCode, char* buffer, int bufferLength);
        int revisionFPGAGet(long featureID, int* errorCode, char* buffer, int bufferLength);
        int revisionSystemGet(long featureID, int* errorCode, char* buffer, int bufferLength);

        /* Get one or more optical bench features */
        int getNumberOfOpticalBenchFeatures();
        int getOpticalBenchFeatures(long* buffer, int maxFeatures);
        int opticalBenchGetArrayWavelength(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        unsigned short int opticalBenchGetSlitWidthMicrons(long opticalBenchFeatureID, int* errorCode);
        void opticalBenchSetSlitWidthMicrons(long opticalBenchFeatureID, int* errorCode, unsigned short int widthMicrons);
        int opticalBenchGetSerialNumber(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        void opticalBenchSetSerialNumber(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        int opticalBenchGetId(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        void opticalBenchSetId(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        unsigned short int opticalBenchGetFiberDiameter(long opticalBenchFeatureID, int* errorCode);
        void opticalBenchSetFiberDiameter(long opticalBenchFeatureID, int* errorCode, unsigned short int diameterMicrons);
        int opticalBenchGetCoating(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        void opticalBenchSetCoating(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        int opticalBenchGetFilter(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        void opticalBenchSetFilter(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        int opticalBenchGetGrating(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        void opticalBenchSetGrating(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);
        int opticalBenchLensInstalled(long opticalBenchFeatureID, int* errorCode, char* buffer, int bufferLength);

        /* Get one or more stray light coefficients features */
        int getNumberOfStrayLightCoeffsFeatures();
        int getStrayLightCoeffsFeatures(long* buffer, int maxFeatures);
        int strayLightCoeffsGet(long featureID, int* errorCode, double* buffer, int bufferLength);

        /* Get one or more data buffer features */
        int getNumberOfDataBufferFeatures();
        int getDataBufferFeatures(long* buffer, int maxFeatures);
        void dataBufferClear(long featureID, int* errorCode);
        unsigned long dataBufferGetNumberOfElements(long featureID, int* errorCode);
        unsigned long dataBufferGetBufferCapacity(long featureID, int* errorCode);
        unsigned long dataBufferGetBufferCapacityMaximum(long featureID, int* errorCode);
        unsigned long dataBufferGetBufferCapacityMinimum(long featureID, int* errorCode);
        void dataBufferSetBufferCapacity(long featureID, int* errorCode, unsigned long capacity);
        void dataBufferSetBufferEnabled(long featureID, int* errorCode, bool enabled);
        bool dataBufferGetBufferEnabled(long featureID, int* errorCode);

        /* Spectra control acquisition feature */
        void abortAcquisition(long featureID, int* errorCode);
        void acquireSpectraToBuffer(long featureID, int* errorCode);
        bool getDeviceIdleState(long featureID, int* errorCode);

        /* Get one or more back-to-back-scans features */
        int getNumberOfBackToBackFeatures();
        int getBackToBackFeatures(long* buffer, int maxFeatures);
        unsigned long backToBackGetNumScans(long featureID, int* errorCode);
        void backToBackSetNumScans(long featureID, int* errorCode, unsigned long numScans);

        /* Get one or more acquisition delay features */
        int getNumberOfAcquisitionDelayFeatures();
        int getAcquisitionDelayFeatures(long* buffer, int maxFeatures);
        void acquisitionDelaySetDelayMicroseconds(long featureID, int* errorCode, unsigned long delay_usec);
        unsigned long acquisitionDelayGetDelayMicroseconds(long featureID, int* errorCode);
        unsigned long acquisitionDelayGetDelayIncrementMicroseconds(long featureID, int* errorCode);
        unsigned long acquisitionDelayGetDelayMaximumMicroseconds(long featureID, int* errorCode);
        unsigned long acquisitionDelayGetDelayMinimumMicroseconds(long featureID, int* errorCode);

        /* Get one or more single strobe features */
        int getSingleStrobeFeatures(long* buffer, int maxFeatures);
        void singleStrobeSetDelayMicroseconds(long featureID, int* errorCode, unsigned long period_usec);
        void singleStrobeSetWidthMicroseconds(long featureID, int* errorCode, unsigned long period_usec);
        void singleStrobeSetEnable(long featureID, int* errorCode, bool enable);
        unsigned long singleStrobeGetDelayMicroseconds(long featureID, int* errorCode);
        unsigned long singleStrobeGetWidthMicroseconds(long featureID, int* errorCode);
        bool singleStrobeGetEnable(long featureID, int* errorCode);
        unsigned long  getSingleStrobeDelayMinimumMicroseconds(long featureID, int* errorCode);
        unsigned long  getSingleStrobeDelayMaximumMicroseconds(long featureID, int* errorCode);
        unsigned long  getSingleStrobeWidthMinimumMicroseconds(long featureID, int* errorCode);
        unsigned long  getSingleStrobeWidthMaximumMicroseconds(long featureID, int* errorCode);
        unsigned long  getSingleStrobeCycleMaximumMicroseconds(long featureID, int* errorCode);
        unsigned long  getSingleStrobeDelayIncrementMicroseconds(long featureID, int* errorCode);
        unsigned long  getSingleStrobeWidthIncrementMicroseconds(long featureID, int* errorCode);

        /* Get one or more activity features */
        int getNumberOfActivityFeatures();
        int getActivityFeatures(long* buffer, int maxFeatures);
        bool ledActivityGetEnable(long featureID, int* errorCode);
        void ledActivitySetEnable(long featureID, int* errorCode, bool enable);

        /* DHCP server configuration */
        int getDHCPServerFeatures(long* buffer, int maxFeatures);
        bool isDHCPServerEnabled(long featureID, int* errorCode, unsigned char ifNum);
        void setDHCPServerEnable(long featureID, int* errorCode, unsigned char ifNum, bool enable);
        void getDHCPServerAddressRange(long featureID, int* errorCode, unsigned char ifNum,
            unsigned int* outBaseIpAddress, unsigned int ipAddressArraySize, unsigned int* outNetmask);
        void setDHCPServerAddressRange(long featureID, int* errorCode, unsigned char ifNum,
            const unsigned int* baseIpAddress, unsigned int ipAddressArraySize, unsigned int netmask);

        /* IPv4 Address feature */
        int getNumberOfIpv4Features();
        int getIpv4AddressFeatures(long* buffer, int maxFeatures);
        bool isDHCPEnabled(long featureID, int* errorCode, unsigned char ifNum);
        void setDHCPEnable(long featureID, int* errorCode, unsigned char ifNum, unsigned char enabled);
        int getNumberOfIpAddresses(long featureID, int* errorCode, unsigned char ifNum);
        void readIpAddress(long featureID, int* errorCode, unsigned char ifNum, unsigned char addressIndex,
            unsigned char* ipAddress, int ipAddressLength, unsigned int* netmask);
        void addStaticIpAddress(long featureID, int* errorCode, unsigned char ifNum,
            unsigned char* ipAddress, int ipAddressLength, unsigned int netmask);
        void deleteStaticIpAddress(long featureID, int* errorCode, unsigned char ifNum, unsigned char addressIndex);

        /* Get pixel info commands. */
        int getPixelCount(long featureID, int* error_code);
        int getActivePixelRange(long featureID, int* error_code, int* range, int rangeSize);
        int getOpticalDarkPixelCount(long featureID, int* error_code);
        int getOpticalDarkPixelIndices(long featureID, int* error_code, int* indices, int indicesSize);
        int getOpticalDarkPixelRange(long featureID, int* error_code, int* range, int rangeSize);
        int getTransitionPixelRange(long featureID, int* error_code, int* range, int rangeSize);
        int getBadPixelIndices(long featureID, int* error_code, int* baxPixelIndices, int baxPixelSize);
        void setBadPixelIndices(long featureID, int* error_code, int* baxPixelIndices, int baxPixelSize);

        /* Auto nulling commands */
        int getMaximumADCCount(long featureID, int* error_code);
        int getSaturationLevel(long featureID, int* error_code);
        void setSaturationLevel(long featureID, int* error_code, int level);
        int getBaselineLevel(long featureID, int* error_code);
        void setBaselineLevel(long featureID, int* error_code, int level);

        /* User string features */
        int getUserString(long featureID, int* errorCode, char* buffer, int bufferLength);
        void setUserString(long featureID, int* errorCode, char* buffer, int bufferLength);
        int getUserStringCount(long featureID, int* errorCode);
        int getUserString(long featureID, int* errorCode, int index, char* buffer, int bufferLength);
        void setUserString(long featureID, int* errorCode, int index, char* buffer, int bufferLength);

        /* Device alias features */
        int getDeviceAlias(long featureID, int* errorCode, char* buffer, int bufferLength);
        void setDeviceAlias(long featureID, int* errorCode, char* buffer, int bufferLength);

        /* Device information features */
        void resetDevice(long featureID, int* errorCode);
        std::uint16_t getOriginalVID(long featureID, int* errorCode);
        std::uint16_t getOriginalPID(long featureID, int* errorCode);
        std::uint16_t getVID(long featureID, int* errorCode);
        void setVID(long featureID, int* errorCode, std::uint16_t vid);
        std::uint16_t getPID(long featureID, int* errorCode);
        void setPID(long featureID, int* errorCode, std::uint16_t pid);
        int getOriginalManufacturerString(long featureID, int* errorCode, char* buffer, int bufferLength);
        int getOriginalModelString(long featureID, int* errorCode, char* buffer, int bufferLength);
        int getManufacturerString(long featureID, int* errorCode, char* buffer, int bufferLength);
        void setManufacturerString(long featureID, int* errorCode, char* buffer, int bufferLength);
        int getModelString(long featureID, int* errorCode, char* buffer, int bufferLength);
        void setModelString(long featureID, int* errorCode, char* buffer, int bufferLength);

        /* Get OBP commands supported by the device. This command only applies to the newer devices with latest version of OBP */
        int getCommandList(long featureID, int* errorCode, unsigned int* commands, int length);
        std::uint32_t getIntegrationTimeStepSize(long featureID, int* errorCode);

        /* Serial port configuration features */
        int getBaudRate(long featureID, int* errorCode);
        void setBaudRate(long featureID, int* errorCode, int baudRate);
        void saveSettingsToFlash(long featureID, int* errorCode);



        std::vector<int> emptyDummyIntVar;
        std::vector<double> emptyDummyDoubleVar;
        std::vector<double> correctedSpectra;

        protected:
            unsigned long instanceID;
            std::unique_ptr<oceandirect::Device> device;
            int scanToAverage; //0/1(single scan), more than 1 (averaging)
            int boxcarWidth;   //software side only.

            std::vector<RawBusAccessFeatureAdapter *> rawBusAccessFeatures;
            std::vector<SerialNumberFeatureAdapter *> serialNumberFeatures;
            std::vector<SpectrometerFeatureAdapter *> spectrometerFeatures;
            std::vector<ThermoElectricCoolerFeatureAdapter *> tecFeatures;
            std::vector<IrradCalFeatureAdapter *> irradCalFeatures;
            std::vector<EEPROMFeatureAdapter *> eepromFeatures;
            std::vector<LightSourceFeatureAdapter *> lightSourceFeatures;
            std::vector<StrobeLampFeatureAdapter *> strobeLampFeatures;
            std::vector<ContinuousStrobeFeatureAdapter *> continuousStrobeFeatures;
            std::vector<SingleStrobeFeatureAdapter *> singleStrobeFeatures;
            std::vector<GpioFeatureAdapter *> gpioFeatures;
            std::vector<NonlinearityCoeffsFeatureAdapter *> nonlinearityFeatures;
            std::vector<TemperatureFeatureAdapter *> temperatureFeatures;
            std::vector<RevisionFeatureAdapter *> revisionFeatures;
            std::vector<OpticalBenchFeatureAdapter *> opticalBenchFeatures;
            std::vector<StrayLightCoeffsFeatureAdapter *> strayLightFeatures;
            std::vector<PixelBinningFeatureAdapter *> pixelBinningFeatures;
            std::vector<DataBufferFeatureAdapter *> dataBufferFeatures;
            std::vector<BackToBackFeatureAdapter *> backToBackFeatures;
            std::vector<AcquisitionDelayFeatureAdapter *> acquisitionDelayFeatures;
            std::vector<QueryStatusFeatureAdapter*> queryStatusFeatures;
            std::vector<LedActivityFeatureAdapter *> ledActivityFeatures;
            std::vector<TimeFeatureAdapter *> timeFeatures;
            std::vector<DHCPServerConfigurationFeatureAdapter *> dhcpFeatures;
            std::vector<PixelFeatureAdapter *> pixelFeatures;
            std::vector<AutoNullingFeatureAdapter *> autoNullingFeatures;
            std::vector<UserStringFeatureAdapter *> userStringFeatures;
            std::vector<DeviceInformationFeatureAdapter *> deviceInformationFeatures;
            std::vector<DeviceAliasFeatureAdapter *> deviceAliasFeatures;
            std::vector<SerialPortFeatureAdapter *> serialPortFeatures;
            std::vector<Ipv4AddressFeatureAdapter *> ipv4AddressFeatures;
            std::vector<SpectrumAcquisitionControlFeatureAdapter *> spectrumAcquisitionControlFeatures;
            std::vector<NetworkConfigurationFeatureAdapter*> networkConfigurationFeatures;
            std::vector<EthernetFeatureAdapter*> ethernetFeatures;
            std::vector<ShutterFeatureAdapter*> shutterFeatures;
            std::vector<HighGainModeFeatureAdapter*> highGainModeFeatures;
            std::vector<FlashScratchPadFeatureAdapter*> flashScratchPadFeatures;

            RawBusAccessFeatureAdapter *getRawBusAccessFeatureByID(long featureID);
            SerialNumberFeatureAdapter *getSerialNumberFeatureByID(long featureID);
            SpectrometerFeatureAdapter *getSpectrometerFeatureByID(long featureID);
            ThermoElectricCoolerFeatureAdapter *getTECFeatureByID(long featureID);
            IrradCalFeatureAdapter *getIrradCalFeatureByID(long featureID);
            EEPROMFeatureAdapter *getEEPROMFeatureByID(long featureID);
            LightSourceFeatureAdapter *getLightSourceFeatureByID(long featureID);
            StrobeLampFeatureAdapter *getStrobeLampFeatureByID(long featureID);
            ContinuousStrobeFeatureAdapter *getContinuousStrobeFeatureByID(long featureID);
            SingleStrobeFeatureAdapter *getSingleStrobeFeatureByID(long featureID);
            GpioFeatureAdapter *getGpioFeatureByID(long featureID);
            NonlinearityCoeffsFeatureAdapter *getNonlinearityCoeffsFeatureByID(long featureID);
            TemperatureFeatureAdapter *getTemperatureFeatureByID(long featureID);
            RevisionFeatureAdapter *getRevisionFeatureByID(long featureID);
            OpticalBenchFeatureAdapter *getOpticalBenchFeatureByID(long featureID);
            StrayLightCoeffsFeatureAdapter *getStrayLightCoeffsFeatureByID(long featureID);
            PixelBinningFeatureAdapter *getPixelBinningFeatureByID(long featureID);
            DataBufferFeatureAdapter *getDataBufferFeatureByID(long featureID);
            BackToBackFeatureAdapter *getBackToBackFeatureByID(long featureID);
            AcquisitionDelayFeatureAdapter *getAcquisitionDelayFeatureByID(long featureID);
            QueryStatusFeatureAdapter *getQueryStatusFeatureByID(long featureID);
            LedActivityFeatureAdapter *getActivityFeatureByID(long featureID);
            TimeFeatureAdapter *getTimeFeatureByID(long featureID);

            DHCPServerConfigurationFeatureAdapter *getDHCPFeatureByID(long featureID);
            Ipv4AddressFeatureAdapter *getIpv4AddressFeatureByID(long featureID);
            PixelFeatureAdapter *getPixelFeatureByID(long featureID);
            AutoNullingFeatureAdapter *getAutoNullingFeatureByID(long featureID);
            UserStringFeatureAdapter *getUserStringFeatureByID(long featureID);
            DeviceInformationFeatureAdapter *getDeviceInformationFeatureByID(long featureID);
            DeviceAliasFeatureAdapter *getDeviceAliasFeatureByID(long featureID);
            SerialPortFeatureAdapter *getSerialPortFeatureByID(long featureID);
            SpectrumAcquisitionControlFeatureAdapter *getSpectrumAcquisitionControlFeatureByID(long featureID);
            NetworkConfigurationFeatureAdapter *getNetworkConfigurationFeatureByID(long featureID);
            EthernetFeatureAdapter* getEthernetFeatureByID(long featureID);
            ShutterFeatureAdapter* getShutterFeatureByID(long featureID);

            // Assignments for feature lookups
            enum class featureId {
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
                singstrb,
                status,
                backToBack,
                activity,
                time,
                volt_in,
                volt_out,
                dhcp,
                ipv4_address,
                pixel,
                autonulling,
                userstring,
                deviceInfo,
                deviceAlias,
                serialPort,
                spectrumAcquisitionControl,
                networkConfiguration,
                ethernet,
                shutter,
                highGainMode,
                flashScratchPad
            };
        };
    }
}

#endif

