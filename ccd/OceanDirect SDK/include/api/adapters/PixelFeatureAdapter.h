/*****************************************************
 * @file    PixelFeatureAdapter.h
 * @date    March 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows access to OceanDirect
 * PixelFeatureInterface instances.
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

#ifndef OCEANDIRECT_PIXEL_FEATUREADAPTER_H
#define OCEANDIRECT_PIXEL_FEATUREADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/pixel/PixelFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class PixelFeatureAdapter
                : public FeatureAdapterTemplate<PixelFeatureInterface> {
        public:
            PixelFeatureAdapter(PixelFeatureInterface *intf, const FeatureFamily &f,
                                Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~PixelFeatureAdapter();

            int getNumberOfPixel(int *errorCode);
            int getActivePixelCount(int* errorCode);
            int getActivePixelRange(int *errorCode, int *range, int rangeSize);
            int getNumberOfOpticalDarkPixel(int* errorCode);
            int getOpticalDarkPixelIndices(int* error_code, int* iIndices, int indicesSize) ;
            int getOpticalDarkPixelRange(int *errorCode, int *range, int rangeSize);
            int getTransitionPixelCount(int* errorCode);
            int getTransitionPixelRange(int *errorCode, int *range, int rangeSize);
            int getBadPixelIndices(int *errorCode, int *badPixelIndices, int badPixelSize);
            void setBadPixelIndices(int *errorCode, int *badPixelIndices, int badPixelSize);
        };
    }
}

#endif