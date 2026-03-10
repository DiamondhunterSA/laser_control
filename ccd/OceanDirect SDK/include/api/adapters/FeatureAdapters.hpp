#ifndef FEATURE_ADAPTER_HPP
#define FEATURE_ADAPTER_HPP
/*****************************************************
 * @file    FeatureAdapter.hpp
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
#include "common/devices/Device.h"
#include "common/features/Feature.h"
#include "common/features/FeatureFamily.h"
#include "common/protocols/ProtocolFamily.h"
#include "common/buses/Bus.h"
#include "common/protocols/Protocol.h"
#include <vector>
#include <memory>
using oceandirect::Device;
using oceandirect::Feature;
using oceandirect::FeatureFamily;
using oceandirect::ProtocolFamily;
using oceandirect::Bus;
using oceandirect::Protocol;

template <class T>
std::vector<T*>* __sbapi_getFeatures(Device* dev) {
    /* This is a templated function to get all of the features of a particular
    * type based on the feature interface.  These can be used directly to
    * create feature adapters, but the logic to do that is too much for a
    * simple templated function to deal with.
    */
    std::vector<Feature*> features = dev->getFeatures();
    std::vector<T*>* retval = new std::vector<T*>();
    for (Feature* feature : features) {
        T* intf = dynamic_cast<T*>(feature);
        if (intf) {
            retval->push_back(intf);
        }
    }

    return retval;
}

template <class T> void __delete_feature_adapters(std::vector<T*>& features) {
    for (T* feature : features) {
        delete feature;
    }
}

template <class T, class U> void __create_feature_adapters(Device* device, std::vector<U*>& adapters,
    Bus* bus, const FeatureFamily& family) {

    /* Purge anything already in the adapters the create the feature list */
    adapters.clear();
    unsigned short i = 0;
    std::unique_ptr<std::vector<T*>> features(__sbapi_getFeatures<T>(device));
    for (T* feature : *features) {
        // All FeatureInterface instances should also be Features, but do a proper cast to be sure.
        Feature* f = dynamic_cast<Feature*>(feature);
        if (f) {
            ProtocolFamily protocolFamily = device->getSupportedProtocol(f->getFeatureFamily(),
                bus->getBusFamily());
            std::vector<Protocol*> protocols = device->getProtocolsByFamily(protocolFamily);
            if (protocols.size()) {
                adapters.push_back(new U(feature, family, protocols[0], bus, i++));
            }
        }
    }
}

template <class T> T* __getFeatureByID(std::vector<T*> features, long id) {
    unsigned int i;

    for (i = 0; i < features.size(); i++) {
        if (features[i]->getID() == id) {
            return features[i];
        }
    }

    return nullptr;
}
#endif // !FEATURE_ADAPTER_HPP

