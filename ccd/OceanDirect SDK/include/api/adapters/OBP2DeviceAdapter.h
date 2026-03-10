#ifndef OBP2_DEVICE_ADAPTER_H
#define OBP2_DEVICE_ADAPTER_H
/*****************************************************
 * @file    OBP2DeviceAdapter.h
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
#include "api/adapters/DeviceConfiguration.h"

using oceandirect::IDevice;

namespace oceandirect {

    class IOBP2Device;
    class Device;

    namespace api {

        class OBP2DeviceAdapter :
            public IDevice {

        public:
            OBP2DeviceAdapter(IOBP2Device& dev, unsigned long id);
            OBP2DeviceAdapter(const OBP2DeviceAdapter& other);
            OBP2DeviceAdapter() = delete;
            ~OBP2DeviceAdapter();

            int open(int* errorCode) override;
            void close() override;

            DeviceLocatorInterface* getLocation() override;

            //DeviceConfiguration deviceConfig;

            /* An for weak association to this object */
            unsigned long getID() override;
            //Device* getDevice();

            /* Get a string that describes the type of device */
            int getDeviceType(int* errorCode, char* buffer, unsigned int maxLength) override;

            /* Get a usb endpoint for the device according to the enumerator */
            /*  endpointType. A 0 is returned if the endpoint requested is not in use. */
            unsigned char getDeviceEndpoint(int* errorCode, usbEndpointType anEndpointType) override;

            /* check an array for saturation and set a warning code if saturated*/
            int checkArrayForSaturation(std::vector<double> arrayToCheck, int* errorCode) override;

            /* Needed for legacy device support but unused here, get rid of this as soon as possible */
            std::vector<double> getDeviceConfigWavelengths() override {return {};};

            /* Get initial immutable properties of the spectrometer to save for future requests*/
            int getDeviceConfiguration(int* errorCode) override;
            std::vector<double> getDeviceConfigIrradCalFile() override;
            double getDeviceConfigIrradCollectionArea() override;

            void applyElectricDarkCorrection(int* errorCode, bool value) override;
            bool electricDarkCorrectionUsage(int* errorCode) override;
            void applyNonLinearityCorrection(int* errorCode, bool value) override;
            bool nonLinearityCorrectionUsage(int* errorCode) override;

            //int GetDeviceConfigSmoothFactor();

            std::string getStringDescriptor(int* errorCode, int index) override;
            int rawBusAccessRead(int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint) override;
            int rawBusAccessWrite(int* errorCode, unsigned char* buffer, unsigned int bufferLength, unsigned char endpoint) override;
            int rawBusAccessRead(int* errorCode, unsigned char* buffer, unsigned int bufferLength) override;
            int rawBusAccessWrite(int* errorCode, unsigned char* buffer, unsigned int bufferLength) override;

            int getSerialNumber(int* errorCode, char* buffer, int bufferLength) override;
            void setSerialNumber(int* errorCode, char* buffer, int bufferLength) override;
            unsigned char getSerialNumberMaximumLength(int* errorCode) override;

            /* Get and set time features */
            long long int getTime(int* errorCode) override;
            void setTime(int* errorCode, long long int timeInMicroseconds) override;

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

            void boxcarCorrectSpectrum(int* errorCode, const double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength,
                 unsigned int boxcarWidth, double *boxcarCorrectedSpectrum, unsigned int boxcarCorrectedSpectrumLength) override;

            int getWavelengths(int* errorCode, double* wavelengths, int length) override;
            int getWavelengthCoefficients(int* errorCode, double* coeff, int length) override;
            void setWavelengthCoefficients(int* errorCode, double* coeff, int length) override;
            int getElectricDarkPixelCount(int* errorCode) override;
            int getElectricDarkPixelIndices(int* errorCode, int* indices, int length) override;
            unsigned int getScansToAverage(int* errorCode) override;
            unsigned short int getBoxcarWidth(int* errorCode) override;
            void setBoxcarWidth(int* errorCode, unsigned short int newBoxcarWidth) override;
            void setScansToAverage(int* errorCode, unsigned int newScansToAverage) override;

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
            int getActivePixelCount(int* error_code) override;
            int getActivePixelRange(int* error_code, int* range, int rangeSize) override;
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
            int getCommandList(int* errorCode, unsigned int* commands, int length) override;

            int getBaudRate(int* errorCode) override;
            void setBaudRate(int* errorCode, int baudRate) override;
            void saveSettingsToFlash(int* errorCode) override;
            std::uint8_t getSerialCommThresholdMode(int* errorCode) override;
            void setSerialCommThresholdMode(int* errorCode, std::uint8_t thresholdMode) override;

            std::uint32_t getNetworkInterfaceCount(int* errorCode) override;
            std::uint32_t getNetworkInterfaceType(int* errorCode, std::uint32_t interfaceIndex) override;
            bool getNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex) override;
            void setNetworkInterfaceStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable) override;
            bool getMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex) override;
            void setMulticastGroupEnabled(int* errorCode, std::uint32_t interfaceIndex, bool enabled) override;
            void saveNetworkInterfaceSetting(int* errorCode, std::uint32_t interfaceIndex) override;
            bool getGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex) override;

            bool getIPAddressAssignedMode(int* errorCode) override;
            void setIPAddressAssignedMode(int* errorCode, bool useDHCP) override;
            void getNetworkConfiguration(int* errorCode, bool& outManualAssignment,
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

            void setGigabitEthernetEnableStatus(int* errorCode, std::uint32_t interfaceIndex, bool enable) override;
            void getMACAddress(int* errorCode, std::uint32_t interfaceIndex, std::uint8_t* macAddress, std::uint32_t macAddressLength) override;
            void setMACAddress(int* errorCode, std::uint32_t interfaceIndex, const std::uint8_t* macAddress, std::uint32_t macAddressLength) override;

            void setShutterOpen(int* errorCode, bool opened) override;
            bool getShutterState(int* errorCode) override;

            void setHighGainMode(int* errorCode, bool enableHighGain) override;
            bool getHighGainMode(int* errorCode) override;

            void setSensorGainMode(int* errorCode, bool enableHighGain, bool enableStandardGain) override;
            void getSensorGainMode(int* errorCode, bool& outHighGain, bool& outStandardGain) override;
            bool getSensorGainHWState(int* errorCode) override;

            void setI2CData(int* errorCode, std::uint32_t i2cBusIndex, std::uint32_t i2cTargetAddress,
                            const std::uint8_t* data, std::uint32_t dataSize) override;
            bool getAccessoryBoardAvailable(int* errorCode) override;
            int  getFlashSlotData(int* errorCode, std::uint32_t slotNumber, std::uint8_t* outData, std::uint32_t outDataSize) override;
            void setFlashSlotData(int* errorCode, std::uint32_t slotNumber, const std::uint8_t* data, std::uint32_t dataSize) override;

        protected:
            // This function queries the spectrometer for the commands it supports.
            // The std::function for each supported command will be assigned to the "implementation" that invokes the
            // associated OBP2 protocol. Any functions not assigned an implementation will retain their default behaviour
            // i.e the will throw a command not supported exception.
            std::vector<unsigned int> GetSupportedCommands(int* errorCode);
            // This function takes the supported commands returned by GetSupportedCommands and assigns the implementation
            // to the std::function.
            void DeactivateUnsupportedCommands(const std::vector<unsigned int>& supportedCommands);
            std::string getDeviceParameters(int* errorCode) override;

            unsigned long instanceID;
            IOBP2Device& device;
        private:
            size_t findPixelRange(const uint16_t indices[], size_t indicesSize, int* range, size_t rangeSize);
        };
    }
}

#endif

