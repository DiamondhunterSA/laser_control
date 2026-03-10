/*****************************************************
 * @file    SpectrumWithMetadata.h
 * @date    August 2021
 * @author  Ocean Optics, Inc.
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

#ifndef OCEANDIRECT_SPECTRUM_WITH_METADATA_H
#define OCEANDIRECT_SPECTRUM_WITH_METADATA_H

#include "api/DllDecl.h"

namespace oceandirect {

    class DLL_DECL SpectrumWithMetadata {
    public:
        SpectrumWithMetadata();

        //This is a wrapper class. User of this class is responsible for deleting the "double*".
        SpectrumWithMetadata(double *thatSpectrum, int thatSpectrumSize, long long int thatTickCount);
        virtual ~SpectrumWithMetadata();

        SpectrumWithMetadata(const SpectrumWithMetadata &copy);
        SpectrumWithMetadata& operator=(const SpectrumWithMetadata &copy);

        /* Dimensionality of data.  0 for scalar, 1 for vector,
         * 2 for a pair of related vectors (e.g. [X, Y] or matrix),
         * 3 for 3D, etc.
         */
        virtual int getNumberOfDimensions();

        /* Get the data associated with this instance */
        double* getSpectrum();
        int getSpectrumLength() const;
        long long int getTickCount() const;
        void setTickCount(long long int thatTickCount);
        void setSpectrumSize(int spectrumSize);
        void setSpectrum(double *thatSpectrum);

    private:
        double* spectrum;
        int     spectrumLength;
        long long int tickCount;
    };
}

#endif /* OCEANDIRECT_SPECTRUM_WITH_METADATA_H */