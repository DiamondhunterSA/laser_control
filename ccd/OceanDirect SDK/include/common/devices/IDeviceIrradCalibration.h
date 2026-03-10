#ifndef I_DEVICE_IRRAD_CALIBRATION_H
#define I_DEVICE_IRRAD_CALIBRATION_H
/*****************************************************
 * @file    IDeviceIrradCalibration.h
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
    * IDeviceIrradCalibration defines the interface to the Device irradiance calibration functionality e.g. getting and setting calibration coefficients.
    */
    class IDeviceIrradCalibration {
    public:
        virtual int readIrradCalibration(int* errorCode, double* buffer, int bufferLength) = 0;
        virtual int readIrradCalibrationSize(int* errorCode) = 0;
        virtual int writeIrradCalibration(int* errorCode, double* buffer, int bufferLength) = 0;
        virtual bool hasIrradCalibrationCollectionArea(int* errorCode) = 0;
        virtual float readIrradCalibrationCollectionArea(int* errorCode) = 0;
        virtual void writeIrradCalibrationCollectionArea(int* errorCode, float area) = 0;

        virtual ~IDeviceIrradCalibration() {}
    };
}
#endif // !I_DEVICE_IRRAD_CALIBRATION_H
