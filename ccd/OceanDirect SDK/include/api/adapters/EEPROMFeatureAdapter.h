/*****************************************************
 * @file    EEPROMFeatureAdapter.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect EEPROMFeatureInterface instances.
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

#ifndef OCEANDIRECT_EEPROMFEATUREADAPTER_H
#define OCEANDIRECT_EEPROMFEATUREADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/eeprom_slots/EEPROMSlotFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class EEPROMFeatureAdapter
                : public FeatureAdapterTemplate<EEPROMSlotFeatureInterface> {
        public:
            EEPROMFeatureAdapter(EEPROMSlotFeatureInterface *intf,
                    const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~EEPROMFeatureAdapter();

            /* EEPROM functions */
            int readEEPROMSlot(int *errorCode, int slotNumber,
                    unsigned char *buffer, int bufferLength);
        };
    }
}

#endif
