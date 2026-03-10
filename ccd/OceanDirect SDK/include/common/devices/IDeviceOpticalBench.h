#ifndef I_DEVICE_OPTICAL_BENCH_H
#define I_DEVICE_OPTICAL_BENCH_H
/*****************************************************
 * @file    IDeviceOpticalBench.h
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
    * IDeviceOpticalBench defines the interface to the Device optical bench functionality e.g. getting and setting slit width.
    */
    class IDeviceOpticalBench {
    public:
        virtual int getOpticalBenchArrayWavelength(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual unsigned short int getOpticalBenchSlitWidthMicrons(int* errorCode) = 0;
        virtual void setOpticalBenchSlitWidthMicrons(int* errorCode, unsigned short int widthMicrons) = 0;
        virtual int getOpticalBenchSerialNumber(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setOpticalBenchSerialNumber(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getOpticalBenchId(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setOpticalBenchId(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual unsigned short int getOpticalBenchFiberDiameter(int* errorCode) = 0;
        virtual void setOpticalBenchFiberDiameter(int* errorCode, unsigned short int diameterMicrons) = 0;
        virtual int getOpticalBenchCoating(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setOpticalBenchCoating(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getOpticalBenchFilter(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setOpticalBenchFilter(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getOpticalBenchGrating(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual void setOpticalBenchGrating(int* errorCode, char* buffer, int bufferLength) = 0;
        virtual int getOpticalBenchLensInstalled(int* errorCode, char* buffer, int bufferLength) = 0;

        virtual ~IDeviceOpticalBench() {}
    };
}
#endif // !I_DEVICE_OPTICAL_BENCH_H
