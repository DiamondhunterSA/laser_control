#ifndef I_DEVICE_SPECTROMETER_H
#define I_DEVICE_SPECTROMETER_H
/*****************************************************
 * @file    IDeviceSpectrometer.h
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
    class SpectrumWithMetadata;
    /*
    * IDeviceSpectrometer defines the interface to the Device spectrometer functionality e.g. getting spectra and setting integration time
    */
    class IDeviceSpectrometer {
    public:

        virtual void setTriggerMode(int* errorCode, int mode) = 0;
        virtual int getTriggerMode(int* errorCode) = 0;
        virtual void setDelayMicroseconds(int* errorCode, unsigned long delayMicroseconds) = 0;
        virtual unsigned long getDelayMicroseconds(int* errorCode) = 0;
        virtual unsigned long getDelayIncrementMicroseconds(int* errorCode) = 0;
        virtual unsigned long getDelayMaximumMicroseconds(int* errorCode) = 0;
        virtual unsigned long getDelayMinimumMicroseconds(int* errorCode) = 0;

        virtual void setIntegrationTimeMicros(int* errorCode, unsigned long integrationTimeMicros) = 0;
        virtual unsigned long getIntegrationTimeMicros(int* errorCode) = 0;
        virtual unsigned long getIntegrationTimeIncrementMicros(int* errorCode) = 0;

        virtual unsigned long getMinimumIntegrationTimeMicros(int* errorCode) = 0;
        virtual unsigned long getMinimumAveragingIntegrationTimeMicros(int* errorCode) = 0;
        virtual unsigned long getMaximumIntegrationTimeMicros(int* errorCode) = 0;
        virtual double getMaximumIntensity(int* errorCode) = 0;
        virtual int getUnformattedSpectrumLength(int* errorCode) = 0;
        virtual int getUnformattedSpectrum(int* errorCode, unsigned char* buffer, int bufferLength) = 0;
        virtual int getFormattedSpectrumLength(int* errorCode) = 0;
        virtual int getFormattedSpectrum(int* errorCode, double* buffer, int bufferLength) = 0;
        virtual int getFormattedSpectrumWithMetadata(int* errorCode, SpectrumWithMetadata* buffer, int bufferLength) = 0;

        virtual void setStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength) = 0;
        virtual int getStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength) = 0;
        virtual int getDarkCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
            double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) = 0;
        virtual int darkCorrectSpectrum(int* errorCode, double* illuminatedSpectrum, int illuminatedSpectrumLength,
            double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) = 0;
        virtual int getDarkCorrectedSpectrum(int* errorCode, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) = 0;
        virtual int darkCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
            int illuminatedSpectrumLength, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength) = 0;

        virtual int getNonlinearityCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
            double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength) = 0;
        virtual int nonlinearityCorrectSpectrum(int* errorCode, double* illuminatedSpectrum,
            int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength) = 0;
        virtual int getNonlinearityCorrectedSpectrum(int* errorCode, double* nonlinearityCorrectedSpectrum,
            int nonlinearityCorrectedSpectrumLength) = 0;
        virtual int nonlinearityCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
            int illuminatedSpectrumLength, double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength) = 0;

        virtual void boxcarCorrectSpectrum(int* errorCode, const double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength, unsigned int boxcarWidth,
                                           double* boxcarCorrectedSpectrum, unsigned int boxcarCorrectedSpectrumLength) = 0;

        virtual int getWavelengths(int* errorCode, double* wavelengths, int length) = 0;
        virtual int getWavelengthCoefficients(int* errorCode, double* coeff, int length) = 0;
        virtual void setWavelengthCoefficients(int* errorCode, double* coeff, int length) = 0;
        virtual int getElectricDarkPixelCount(int* errorCode) = 0;
        virtual int getElectricDarkPixelIndices(int* errorCode, int* indices, int length) = 0;

        virtual void applyElectricDarkCorrection(int* errorCode, bool value) = 0;
        virtual bool electricDarkCorrectionUsage(int* errorCode) = 0;
        virtual void applyNonLinearityCorrection(int* errorCode, bool value) = 0;
        virtual bool nonLinearityCorrectionUsage(int* errorCode) = 0;

        virtual unsigned int getScansToAverage(int* errorCode) = 0;
        virtual unsigned short int getBoxcarWidth(int* errorCode) = 0;
        virtual void setBoxcarWidth(int* errorCode, unsigned short int newBoxcarWidth) = 0;
        virtual void setScansToAverage(int* errorCode, unsigned int newScansToAverage) = 0;
        virtual ~IDeviceSpectrometer() {}
    };
}
#endif // !I_DEVICE_SPECTROMETER_H
