/*****************************************************
 * @file    SpectrometerFeatureAdapter.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect OOISpectrometerFeature instances.
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

#ifndef OCEANDIRECT_SPECTROMETER_FEATURE_ADAPTER_H
#define OCEANDIRECT_SPECTROMETER_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "common/public/SpectrumWithMetadata.h"
#include "common/buses/Bus.h"
#include "common/protocols/Protocol.h"
#include "vendors/OceanOptics/features/pixel/PixelFeatureInterface.h"
#include "vendors/OceanOptics/features/spectrometer/OOISpectrometerFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class SpectrometerFeatureAdapter : public FeatureAdapterTemplate<OOISpectrometerFeatureInterface> {
        public:
            SpectrometerFeatureAdapter(
                OOISpectrometerFeatureInterface *spec,
                    const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~SpectrometerFeatureAdapter();

            /* Spectrometer commands */
            int getUnformattedSpectrum(int *errorCode, unsigned char *buffer, int bufferLength);
            int getFormattedSpectrum(int *errorCode, double* buffer, int bufferLength);
            int getFormattedSpectrumWithMetaData(int *error_code, SpectrumWithMetadata *buffer, int bufferLength);

            void setStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength);
            int getStoredDarkSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength);
            int getDarkCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
            int darkCorrectSpectrum(int* errorCode, double* illuminatedSpectrum, int illuminatedSpectrumLength,
                double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
            int getDarkCorrectedSpectrum(int* errorCode, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);
            int darkCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* darkCorrectedSpectrum, int darkCorrectedSpectrumLength);

            int getNonlinearityCorrectedSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength,
                double* nonlinearityCoeffs, int nonlinearityCoeffsLength,
                double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
            int nonlinearityCorrectSpectrum(int* errorCode, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCoeffs, int nonlinearityCoeffsLength,
                double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
            int getNonlinearityCorrectedSpectrum(int* errorCode, double* nonlinearityCoeffs, int nonlinearityCoeffsLength,
                double* nonlinearityCorrectedSpectrum, int nonlinearityCorrectedSpectrumLength);
            int nonlinearityCorrectSpectrum(int* errorCode, double* darkSpectrum, int darkSpectrumLength, double* illuminatedSpectrum,
                int illuminatedSpectrumLength, double* nonlinearityCoeffs, int nonlinearityCoeffsLength, double* nonlinearityCorrectedSpectrum,
                int nonlinearityCorrectedSpectrumLength);

            void boxcarCorrectSpectrum(int* errorCode, const double* illuminatedSpectrum, unsigned int illuminatedSpectrumLength,
                unsigned int boxcarWidth, double* boxcarCorrectedSpectrum, unsigned int boxcarCorrectedSpectrumLength);

            int getUnformattedSpectrumLength(int *errorCode);
            int getFormattedSpectrumLength(int *errorCode);
            void setTriggerMode(int *errorCode, int mode);
            int getTriggerMode(int *errorCode);
            unsigned long getAcquisitionDelayIncrementMicroseconds(int* errorCode);
            unsigned long getAcquisitionDelayMaximumMicroseconds(int* errorCode);
            unsigned long getAcquisitionDelayMinimumMicroseconds(int* errorCode);
            unsigned long getAcquisitionDelayMicroseconds(int* errorCode);
            void setAcquisitionDelayMicroseconds(int* errorCode, const unsigned long delay_usec);


            int getWavelengths(int *errorCode, double *wavelengths, int length);
            int getWavelengthCoefficients(int *errorCode, double *wavelengths, int length);
            void setWavelengthCoefficients(int *errorCode, double *wavelengths, int length);
            int getElectricDarkPixelCount(int *errorCode, PixelFeatureInterface *pixelFeatureInterface);
            int getElectricDarkPixelIndices(int *errorCode, PixelFeatureInterface *pixelFeatureInterface, int *indices, int length);
            void setIntegrationTimeMicros(int *errorCode, unsigned long integrationTimeMicros);
            unsigned long getIntegrationTimeMicros(int *errorCode);
            unsigned long getIntegrationTimeIncrementMicros(int* errorCode);
            long getMinimumIntegrationTimeMicros(int *errorCode);
            long getMinimumAveragingIntegrationTimeMicros(int* errorCode);
            long getMaximumIntegrationTimeMicros(int *errorCode);
            double getMaximumIntensity(int *errorCode);

            void setSpectraSummationCount(int* errorCode, std::uint32_t spectraCount);
            int getSpectraSummationCount(int* errorCode);

            void updateSaturationLevel(int* errorCode);
        };

    }
}

#endif
