#ifndef DEVICE_SPECTROMETER_H
#define DEVICE_SPECTROMETER_H

/*******************************************************
 * @file    DeviceSpectrometer.h
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
#include "common/devices/IDeviceSpectrometer.h"
#include "api/adapters/obp2/IFunctionDeactivator.h"
#include "api/adapters/obp2/ISpectrometerParameterObserver.h"
#include "api/adapters/obp2/INonlinearityCoefficientObserver.h"
#include <functional>
#include <map>
#include <vector>
#include <memory>
 // so we can abbreviate the placeholders as _1, _2 etc.
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
using std::placeholders::_5;
using std::placeholders::_6;
using std::placeholders::_7;

namespace oceandirect {

    class OBP2Device;
    namespace oceanBinaryProtocol {
        class OBP2Message;
    }
    using oceanBinaryProtocol::OBP2Message;

    namespace api {

        class DeviceSpectrometer :
            public IDeviceSpectrometer,
            public IFunctionDeactivator,
            public ISpectrometerParameterObserver,
            public INonlinearityCoefficientObserver {

            /* Functions that will be invoked to provide the interface.If the commands are not supported by the device they will
            * be replaced by a lambda function that returns a command not supported error.
            */
            std::function<void(int*, int)> fnSetTriggerMode = std::bind(&DeviceSpectrometer::implSetTriggerMode, this, _1, _2);
            std::function<int(int*)> fnGetTriggerMode = std::bind(&DeviceSpectrometer::implGetTriggerMode, this, _1);
            std::function<void(int*, unsigned long)> fnSetDelayMicroseconds = std::bind(&DeviceSpectrometer::implSetDelayMicroseconds, this, _1, _2);
            std::function<unsigned long(int*)> fnGetDelayMicroseconds = std::bind(&DeviceSpectrometer::implGetDelayMicroseconds, this, _1);
            std::function<unsigned long(int*)> fnGetDelayIncrementMicroseconds = std::bind(&DeviceSpectrometer::implGetDelayIncrementMicroseconds, this, _1);
            std::function<unsigned long(int*)> fnGetDelayMaximumMicroseconds = std::bind(&DeviceSpectrometer::implGetDelayMaximumMicroseconds, this, _1);
            std::function<unsigned long(int*)> fnGetDelayMinimumMicroseconds = std::bind(&DeviceSpectrometer::implGetDelayMinimumMicroseconds, this, _1);
            std::function<void(int*, unsigned long)> fnSetIntegrationTimeMicros = std::bind(&DeviceSpectrometer::implSetIntegrationTimeMicros, this, _1, _2);
            std::function<unsigned long(int*)> fnGetIntegrationTimeMicros = std::bind(&DeviceSpectrometer::implGetIntegrationTimeMicros, this, _1);
            std::function<unsigned long(int*)> fnGetIntegrationTimeIncrementMicros = std::bind(&DeviceSpectrometer::implGetIntegrationTimeIncrementMicros, this, _1);
            std::function<unsigned long(int*)> fnGetMinimumIntegrationTimeMicros = std::bind(&DeviceSpectrometer::implGetMinimumIntegrationTimeMicros, this, _1);
            std::function<unsigned long(int*)> fnGetMinimumAveragingIntegrationTimeMicros = std::bind(&DeviceSpectrometer::implGetMinimumAveragingIntegrationTimeMicros, this, _1);
            std::function<unsigned long(int*)> fnGetMaximumIntegrationTimeMicros = std::bind(&DeviceSpectrometer::implGetMaximumIntegrationTimeMicros, this, _1);
            std::function<double(int*)> fnGetMaximumIntensity = std::bind(&DeviceSpectrometer::implGetMaximumIntensity, this, _1);
            std::function<int(int*)> fnGetUnformattedSpectrumLength = std::bind(&DeviceSpectrometer::implGetUnformattedSpectrumLength, this, _1);
            std::function<int(int*, unsigned char*, int)> fnGetUnformattedSpectrum = std::bind(&DeviceSpectrometer::implGetUnformattedSpectrum, this, _1, _2, _3);
            std::function<int(int*)> fnGetFormattedSpectrumLength = std::bind(&DeviceSpectrometer::implGetFormattedSpectrumLength, this, _1);
            std::function<int(int*, double*, int)> fnGetFormattedSpectrum = std::bind(&DeviceSpectrometer::implGetFormattedSpectrum, this, _1, _2, _3);
            std::function<int(int*, SpectrumWithMetadata*, int)> fnGetFormattedSpectrumWithMetadata = std::bind(&DeviceSpectrometer::implGetFormattedSpectrumWithMetadata, this, _1, _2, _3);
            std::function<void(int*, double*, int)> fnSetStoredDarkSpectrum = std::bind(&DeviceSpectrometer::implSetStoredDarkSpectrum, this, _1, _2, _3);
            std::function<int(int*, double*, int)> fnGetStoredDarkSpectrum = std::bind(&DeviceSpectrometer::implGetStoredDarkSpectrum, this, _1, _2, _3);
            std::function<int(int*, double*, int, double*, int)> fnGetDarkCorrectedSpectrum5 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int, double*, int)>(&DeviceSpectrometer::implGetDarkCorrectedSpectrum), this, _1, _2, _3, _4, _5);
            std::function<int(int*, double*, int, double*, int)> fnDarkCorrectSpectrum5 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int, double*, int)>(&DeviceSpectrometer::implDarkCorrectSpectrum), this, _1, _2, _3, _4, _5);
            std::function<int(int*, double*, int)> fnGetDarkCorrectedSpectrum3 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int)>(&DeviceSpectrometer::implGetDarkCorrectedSpectrum), this, _1, _2, _3);
            std::function<int(int*, double*, int, double*, int, double*, int)> fnDarkCorrectSpectrum7 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int, double*, int, double*, int)>(&DeviceSpectrometer::implDarkCorrectSpectrum), this, _1, _2, _3, _4, _5, _6, _7);
            std::function<int(int*, double*, int, double*, int)> fnGetNonlinearityCorrectedSpectrum5 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int, double*, int)>(&DeviceSpectrometer::implGetNonlinearityCorrectedSpectrum), this, _1, _2, _3, _4, _5);
            std::function<int(int*, double*, int, double*, int)> fnNonlinearityCorrectSpectrum5 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int, double*, int)>(&DeviceSpectrometer::implNonlinearityCorrectSpectrum), this, _1, _2, _3, _4, _5);
            std::function<int(int*, double*, int)> fnGetNonlinearityCorrectedSpectrum3 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int)>(&DeviceSpectrometer::implGetNonlinearityCorrectedSpectrum), this, _1, _2, _3);
            std::function<int(int*, double*, int, double*, int, double*, int)> fnNonlinearityCorrectSpectrum7 = std::bind(static_cast<int(DeviceSpectrometer::*)(int*, double*, int, double*, int, double*, int)>(&DeviceSpectrometer::implNonlinearityCorrectSpectrum), this, _1, _2, _3, _4, _5, _6, _7);
            
            std::function<void(int*, double*, unsigned int, unsigned int)> fnBoxcarCorrectSpectrum = std::bind(&DeviceSpectrometer::implBoxcarCorrectSpectrum, this, _1, _2, _3, _4);
            
            std::function<int(int*, double*, int)> fnGetWavelengths = std::bind(&DeviceSpectrometer::implGetWavelengths, this, _1, _2, _3);
            std::function<int(int*, double*, int)> fnGetWavelengthCoefficients = std::bind(&DeviceSpectrometer::implGetWavelengthCoefficients, this, _1, _2, _3);
            std::function<void(int*, double*, int)> fnSetWavelengthCoefficients = std::bind(&DeviceSpectrometer::implSetWavelengthCoefficients, this, _1, _2, _3);
            std::function<unsigned int(int*)> fnGetScansToAverage = std::bind(&DeviceSpectrometer::implGetScansToAverage, this, _1);
            std::function<unsigned short int(int*)> fnGetBoxcarWidth = std::bind(&DeviceSpectrometer::implGetBoxcarWidth, this, _1);
            std::function<void(int*, unsigned short int)> fnSetBoxcarWidth = std::bind(&DeviceSpectrometer::implSetBoxcarWidth, this, _1, _2);
            std::function<void(int*, unsigned int)> fnSetScansToAverage = std::bind(&DeviceSpectrometer::implSetScansToAverage, this, _1, _2);

            void implSetTriggerMode(int* errorCode, int mode) ;
            int implGetTriggerMode(int* errorCode);
            void implSetDelayMicroseconds(int* errorCode, unsigned long delayMicroseconds);
            unsigned long implGetDelayMicroseconds(int* errorCode);
            unsigned long implGetDelayIncrementMicroseconds(int* errorCode);
            unsigned long implGetDelayMaximumMicroseconds(int* errorCode);
            unsigned long implGetDelayMinimumMicroseconds(int* errorCode);
            void implSetIntegrationTimeMicros(int* errorCode, unsigned long integrationTimeMicros);
            unsigned long implGetIntegrationTimeMicros(int* errorCode);
            unsigned long implGetIntegrationTimeIncrementMicros(int* errorCode);
            unsigned long implGetMinimumIntegrationTimeMicros(int* errorCode);
            unsigned long implGetMinimumAveragingIntegrationTimeMicros(int* errorCode);
            unsigned long implGetMaximumIntegrationTimeMicros(int* errorCode);
            double implGetMaximumIntensity(int* errorCode);
            int implGetUnformattedSpectrumLength(int* errorCode);
            int implGetUnformattedSpectrum(int* errorCode, unsigned char* buffer, int bufferLength);
            int implGetFormattedSpectrumLength(int* errorCode);
            int implGetFormattedSpectrum(int* errorCode, double* buffer, int bufferLength);
            int implGetFormattedSpectrumWithMetadata(int* errorCode, SpectrumWithMetadata* buffer, int bufferLength);
            void implSetStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength);
            int implGetStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength);
            int implGetDarkCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
            int implDarkCorrectSpectrum(int* errorCode, double* illuminatedSpectrum, int illuminatedSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
            int implGetDarkCorrectedSpectrum(int* errorCode, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
            int implDarkCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
            int implGetNonlinearityCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
            int implNonlinearityCorrectSpectrum(int* errorCode, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
            int implGetNonlinearityCorrectedSpectrum(int* errorCode, double* nonlinearityCorrectedSpectrum,
                int nonlinearityCorrectedSpectrumLength);
            int implNonlinearityCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
            void implBoxcarCorrectSpectrum(int* errorCode, double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength, unsigned int boxcarWidth);

            int implGetWavelengths(int* errorCode, double* wavelengths, int length);
            int implGetWavelengthCoefficients(int* errorCode, double* coeff, int length);
            void implSetWavelengthCoefficients(int* errorCode, double* coeff, int length);
            unsigned int implGetScansToAverage(int* errorCode);
            unsigned short int implGetBoxcarWidth(int* errorCode);
            void implSetBoxcarWidth(int* errorCode, unsigned short int newBoxcarWidth);
            void implSetScansToAverage(int* errorCode, unsigned int newScansToAverage);

            // These are here because of the legacy interface...they are implemented as part of the pixel info functionality
            // so we keep them private with no real functionality here to avoid any temptation to use them
            int getElectricDarkPixelCount(int* errorCode) override;
            int getElectricDarkPixelIndices(int* errorCode, int* indices, int length) override;

            int applyDeviceConfigElecDarkPixels(int* errorCode, double* sample, int sampleSize);
            int applyDeviceConfigNonlinearityCoeffs(int* errorCode, double* sample, int sampleSize);
            void applyDeviceConfigBoxcarWidth(int* errorCode, double* sample, int sampleSize);
            void applyDeviceConfigBadPixelsRemoval(double* sample, int sampleSize);

            // convenience method for retrieving an unformatted spectrum
            // the message is heavyweight so we return a (unique) pointer to it
            std::unique_ptr<OBP2Message> getUnformattedSpectrum();
            // convenience method for getting wavelength coefficients into a vector
            std::vector<double> getWavelengthCoefficients();
            // convenience method for getting an averaged spectrum depending on the
            // onboard averaging capability and scans to average values
            void getAveragedSpectrum(SpectrumWithMetadata& buffer, const int pixelCount, const bool onboardAveraging,
                const unsigned short scansToAverage);

            // cache the wavelengths and update the cache if the wavelength coefficients change.
            std::vector<double> CacheWavelengths(const int pixelCount);

            std::multimap<unsigned int, std::function<void()>> functionDeactivationMap;
            OBP2Device* device;

            // Parameters to be queried as "device capabilities"
            unsigned long delayIncrementMicroseconds;
            unsigned long delayMaximumMicroseconds;
            unsigned long delayMinimumMicroseconds;
            unsigned long integrationTimeMinMicroseconds;
            unsigned long integrationTimeAveragingMinMicroseconds;
            unsigned long integrationTimeMaxMicroseconds;
            double maxIntensity;
            // end of queried parameters

            // Parameters supplied by the pixel info "device", the number of pixels and
            // electric dark pixel indices (if any)
            int totalPixelCount;
            std::vector<int> electricDarkPixelIndices;
            std::vector<int> badPixelIndices;

            // Also cache the nonlinearity coefficients but since these can be changed the
            // spectrometer device is also a nonlinearity coefficient "observer"
            std::vector<double> nonlinearityCoefficients;

            // cached copy of the wavelengths, updated on successful set wavelength coefficients
            std::vector<double> cachedWavelengths;

            // flags for automatic electric dark and nonlinearity correction of spectra
            // if these are set true then an acquisition will apply these corrections before returning
            // NB: auto correction can conflict with the user-controlled corrections...the flags are
            // checked to return an error whenever this occurs.
            // NB: auto correction for both electric dark and nonlinearity is enabled by default
            bool automaticElectricDarkCorrect;
            bool automaticNonlinearityCorrect;

            std::vector<double> boxcarResult;
            std::vector<double> storedDarkSpectrum;
            unsigned short boxcarWidth;
            bool onboardAveraging;
            unsigned short scansToAverage;

        public:
            DeviceSpectrometer(OBP2Device* dev);

            void CachePixelInfoParameters(const int pixelCount, const std::vector<int>& elecDarkIndices, const std::vector<int>& badIndices);

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

            void boxcarCorrectSpectrum(int* errorCode, double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength, unsigned int boxcarWidth) override;

            int getWavelengths(int* errorCode, double* wavelengths, int length) override;
            int getWavelengthCoefficients(int* errorCode, double* coeff, int length) override;
            void setWavelengthCoefficients(int* errorCode, double* coeff, int length) override;

            void applyElectricDarkCorrection(int* errorCode, bool value) override;
            bool electricDarkCorrectionUsage(int* errorCode) override;
            void applyNonLinearityCorrection(int* errorCode, bool value) override;
            bool nonLinearityCorrectionUsage(int* errorCode) override;

            unsigned int getScansToAverage(int* errorCode) override;
            unsigned short int getBoxcarWidth(int* errorCode) override;
            void setBoxcarWidth(int* errorCode, unsigned short int newBoxcarWidth) override;
            void setScansToAverage(int* errorCode, unsigned int newScansToAverage) override;

            const std::multimap<unsigned int, std::function<void()>>& FunctionDeactivations() override;
            void OnRetrieveParameters(const SpectrometerParameters& params) override;
            void OnNonlinearityCoefficentsChanged(const std::vector<double>& coefficients) override;
            void OnNonlinearityCoefficentsChanged(const int index, const double coefficient) override;
        };
    }
}
#endif // !DEVICE_SPECTROMETER_H
