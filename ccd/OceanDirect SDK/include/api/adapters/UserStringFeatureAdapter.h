/*****************************************************
 * @file    UserStringFeatureAdapter.h
 * @date    April 2021
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect UserStringFeatureInterface instances.
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

#ifndef OCEANDIRECT_USER_STRING_FEATURE_ADAPTER_H
#define OCEANDIRECT_USER_STRING_FEATURE_ADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/user_string/UserStringFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class UserStringFeatureAdapter
                : public FeatureAdapterTemplate<UserStringFeatureInterface> {
        public:
            UserStringFeatureAdapter(UserStringFeatureInterface *intf,
                                     const FeatureFamily &f,
                                     Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~UserStringFeatureAdapter();

            int getUserString(int *errorCode, char *buffer, int buffer_length);
            void setUserString(int *errorCode, char *buffer, int buffer_length);

            int getUserStringCount(int *errorCode);
            int getUserString(int *errorCode, int index, char *buffer, int buffer_length);
            void setUserString(int *errorCode, int index, char *buffer, int buffer_length);
        };
    }
}

#endif

