/*****************************************************
 * @file    ProtocolFamilies.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This provides a way to describe different kinds
 * protocols (e.g. OOI, OBP) generically.
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

#ifndef OCEANDIRECT_PROTOCOLFAMILIES_H
#define OCEANDIRECT_PROTOCOLFAMILIES_H

#include "common/protocols/ProtocolFamily.h"
#include <vector>

namespace oceandirect {
    namespace api {

        class UndefinedProtocolFamily : public ProtocolFamily {
        public:
            UndefinedProtocolFamily();
            virtual ~UndefinedProtocolFamily();
        };

        class OOIProtocolFamily : public ProtocolFamily {
        public:
            OOIProtocolFamily();
            virtual ~OOIProtocolFamily();
        };

        class OceanBinaryProtocolFamily : public ProtocolFamily {
        public:
            OceanBinaryProtocolFamily();
            virtual ~OceanBinaryProtocolFamily();
        };

        class JazMessagingProtocolFamily : public ProtocolFamily {
        public:
            JazMessagingProtocolFamily();
            virtual ~JazMessagingProtocolFamily();
        };

        class VirtualProtocolFamily : public ProtocolFamily {
        public:
            VirtualProtocolFamily();
            virtual ~VirtualProtocolFamily();
        };

        class ProtocolFamilies {
        public:
            const UndefinedProtocolFamily UNDEFINED_PROTOCOL;
            const OOIProtocolFamily OOI_PROTOCOL;
            const OceanBinaryProtocolFamily OCEAN_BINARY_PROTOCOL;
            const JazMessagingProtocolFamily JAZ_MESSAGING_PROTOCOL;
            const VirtualProtocolFamily VIRTUAL_PROTOCOL;

            ProtocolFamilies();
            ~ProtocolFamilies();
            std::vector<ProtocolFamily *> getAllProtocolFamilies();
        };
    }
}

#endif
