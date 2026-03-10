#ifndef I_DEVICE_NONLINEARITY_H
#define I_DEVICE_NONLINEARITY_H
/*****************************************************
 * @file    IDeviceNonlinearity.h
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
namespace oceandirect {
    /*
    * IDeviceNonlinearity defines the interface to the Device nonlinearity functionality e.g. getting and setting nonlinearity coefficients
    */
    class IDeviceNonlinearity {
    public:
        virtual int getNonlinearityCoeffsCount(int* errorCode) = 0;
        virtual double getNonlinearityCoeffs(int* errorCode, int index) = 0;
        virtual void setNonlinearityCoeffs(int* errorCode, int index, double coefficient) = 0;
        virtual int getNonlinearityCoeffs(int* errorCode, double* buffer, int bufferLength) = 0;
        virtual int setNonlinearityCoeffs(int* errorCode, double* buffer, int bufferLength) = 0;

        virtual ~IDeviceNonlinearity() {}
    };
}
#endif // !I_DEVICE_NONLINEARITY_H
