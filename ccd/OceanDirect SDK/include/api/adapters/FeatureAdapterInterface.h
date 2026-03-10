/*****************************************************
 * @file    FeatureAdapterInterface.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This interface allows device features to be treated
 * consistently regardless of the actual capabilities.
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

#ifndef OCEANDIRECT_FEATUREADAPTERINTERFACE_H
#define OCEANDIRECT_FEATUREADAPTERINTERFACE_H

#include "common/features/FeatureFamily.h"

namespace oceandirect {
    namespace api {

        class FeatureAdapterInterface {
        public:
            virtual ~FeatureAdapterInterface() = 0;

            /* This gets a semi-unique integer ID for this feature instance */
            virtual long getID() = 0;

            /* Gets the general category of the feature, if any */
            virtual FeatureFamily &getFeatureFamily() = 0;
        };

        /* Default empty destructor for otherwise abstract class */
        inline FeatureAdapterInterface::~FeatureAdapterInterface() { }
    }
}

#endif
