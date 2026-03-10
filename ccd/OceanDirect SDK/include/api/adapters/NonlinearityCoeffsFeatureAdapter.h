/*****************************************************
 * @file    NonlinearityCoeffsFeatureAdapter.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a wrapper that allows
 * access to OceanDirect NonlinearityCoeffFeatureInterface instances.
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

#ifndef OCEANDIRECT_NONLINEARITYCOEFFSFEATUREADAPTER_H
#define OCEANDIRECT_NONLINEARITYCOEFFSFEATUREADAPTER_H

#include "api/adapters/FeatureAdapterTemplate.h"
#include "vendors/OceanOptics/features/nonlinearity/NonlinearityCoeffsFeatureInterface.h"

namespace oceandirect {
    namespace api {

        class NonlinearityCoeffsFeatureAdapter
                : public FeatureAdapterTemplate<NonlinearityCoeffsFeatureInterface> {
        public:
            NonlinearityCoeffsFeatureAdapter(NonlinearityCoeffsFeatureInterface *intf,
                    const FeatureFamily &f,
                    Protocol *p, Bus *b, unsigned short instanceIndex);
            virtual ~NonlinearityCoeffsFeatureAdapter();

            int readNonlinearityCoeffsCount(int *errorCode);

            double readNonlinearityCoeffs(int *errorCode, int index);

            void writeNonlinearityCoeffs(int *errorCode, int index, double coefficent);

            int readNonlinearityCoeffs(int *errorCode, double *buffer, int bufferLength);

            int writeNonlinearityCoeffs(int *errorCode, double *buffer, int bufferLength);
        };

    }
}

#endif
