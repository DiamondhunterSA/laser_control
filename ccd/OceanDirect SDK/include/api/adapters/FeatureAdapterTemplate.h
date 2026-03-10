/*****************************************************
 * @file    FeatureAdapterTemplate.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a templated wrapper around OceanDirect Feature
 * instances.  This should make it easier to obtain a
 * particular Feature to call methods against.
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

#ifndef FEATUREADAPTERTEMPLATE_H
#define FEATUREADAPTERTEMPLATE_H

#include "api/adapters/FeatureAdapterInterface.h"
#include "common/buses/Bus.h"
#include "common/exceptions/IllegalArgumentException.h"
#include "common/features/FeatureFamily.h"
#include "common/protocols/Protocol.h"
#include <string>

namespace oceandirect {
    namespace api {

        template <class T> class FeatureAdapterTemplate
                    : public FeatureAdapterInterface {
        public:
            FeatureAdapterTemplate(T *featureInterface, const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex) {
                this->feature = featureInterface;
                this->family = f;
                this->protocol = p;
                this->bus = b;
                this->index = instanceIndex;

                /* Create a unique ID based on the feature type and index.  This
                 * might be expanded in the future to use one of the bytes for
                 * the feature type or index as a module number.
                 */
				//this->ID = (family.getType() << 16) | (instanceIndex & 0x00FFFF);
				this->ID = (long)family.getType();

                if(0 == this->feature || 0 == this->protocol || 0 == this->bus) {
                    std::string error("Null feature interface, protocol, or bus is not allowed.");
                    throw IllegalArgumentException(error);
                }
            }
            virtual ~FeatureAdapterTemplate() { /* Do nothing -- others delete feature */ }
            T *getFeature() { return this->feature; }

            virtual FeatureFamily &getFeatureFamily() { return this->family; }

            virtual long getID() { return this->ID; }

        protected:
            T *feature;
            FeatureFamily family;
            Protocol *protocol;
            Bus *bus;
            unsigned short index;
            unsigned long ID;
        };
    }
}

#endif
