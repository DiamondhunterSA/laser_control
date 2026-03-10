/*****************************************************
 * @file    RevisionFeatureAdapter.h
 * @date    April 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect RevisionFeatureInterface instances.
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

#ifndef OCEANDIRECT_REVISION_FEATURE_ADAPTER_H
#define OCEANDIRECT_REVISION_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/revision/RevisionFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class RevisionFeatureAdapter
                : public FeatureAdapterTemplate<RevisionFeatureInterface> {
        public:
            RevisionFeatureAdapter(RevisionFeatureInterface *intf,
                    const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~RevisionFeatureAdapter();

            int readHardwareRevision(int *errorCode, char *buffer, int buffer_length);
            int readFirmwareRevision(int *errorCode, char *buffer, int buffer_length);
            int readFPGARevision(int *errorCode, char *buffer, int buffer_length);
            int readSystemRevision(int* errorCode, char* buffer, int buffer_length);
            
        };

    }
}

#endif