/*****************************************************
 * @file    OceanDirectAPIConstants.h
 * @date    January 2018
 * @author  Ocean Optics, Inc.
 *
 * This file defines constants for use with OceanDirect API
 * implementations.
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

#ifndef OCEANDIRECTAPICONSTANTS_H
#define OCEANDIRECTAPICONSTANTS_H

#include "api/DllDecl.h"

/* Macros and constants */
#define SET_ERROR_CODE(code) do { if(NULL != errorCode) { *errorCode = code; }  } while(0)

#ifdef ERROR_SUCCESS
#undef ERROR_SUCCESS
#endif

#define UNUSED(x) (void)(x)
#ifdef __cplusplus
extern "C" {
#endif
    /**
     * Error code(0) representing no error, or success.
     */
    DLL_DECL extern const int ERROR_SUCCESS;
    /**
     * Error code(1) representing an undefined error.
     */
    DLL_DECL extern const int ERROR_INVALID_ERROR;
    /**
     * Error code(2) representing No device found.
     */
    extern DLL_DECL const int ERROR_NO_DEVICE;
    /**
     * Error code(3) representing could not close device.
     */
    DLL_DECL extern const int ERROR_FAILED_TO_CLOSE;
    /**
     * Error code(4) representing feature not implemented.
     */
    DLL_DECL extern const int ERROR_NOT_IMPLEMENTED;
    /**
     * Error code(5) representing no such feature on device.
     */
    DLL_DECL extern const int ERROR_FEATURE_NOT_FOUND;
    /**
     * Error code(6) representing a data transfer error.
     */
    DLL_DECL extern const int ERROR_TRANSFER_ERROR;
    /**
     * Error code(7) representing an invalid user buffer provided.
     */
    DLL_DECL extern const int ERROR_BAD_USER_BUFFER;
    /**
     * Error code(8) representing an Input was out of bounds.
     */
    DLL_DECL extern const int ERROR_INPUT_OUT_OF_BOUNDS;
    /**
     * Error code(9) representing a spectrometer was saturated.
     */
    DLL_DECL extern const int ERROR_SPECTROMETER_SATURATED;
    /**
     * Error code(10) representing a value not found.
     */
    DLL_DECL extern const int ERROR_VALUE_NOT_FOUND;
    /**
     * Error code(11) representing a  Divide-By-Zero error.
     */
    DLL_DECL extern const int ERROR_CODE_DIVIDE_BY_ZERO;
    /**
     * Error code(12) representing a Non-Invertible Matrix error.
     */
    DLL_DECL extern const int ERROR_CODE_NONINVERTIBLE_MATRIX;
    /**
     * Error code(13) representing an Array Length error.
     */
    DLL_DECL extern const int ERROR_CODE_ARRAY_LENGTH;
    /**
     * Error code(14) representing an Array-Index-Out-Of-Bounds error.
     */
    DLL_DECL extern const int ERROR_CODE_ARRAY_INDEX_OUT_OF_BOUNDS;
    /**
     * Error code(15) representing an invalid argument error.
     */
    DLL_DECL extern const int ERROR_CODE_INVALID_ARGUMENT;
    /**
     * Error code(16) representing an empty vector error.
     */
    DLL_DECL extern const int ERROR_CODE_EMPTY_VECTOR;
    /**
     * Error code(17) representing a Color Conversion error.
     */
    DLL_DECL extern const int ERROR_CODE_COLOR_CONVERSION_ERROR;
    /**
     * Error code(18) representing a No-Peak-Found error.
     */
    DLL_DECL extern const int ERROR_CODE_NO_PEAK_FOUND_ERROR;
    /**
     * Error code(19) resulting in an Illegal State error.
     */
    DLL_DECL extern const int ERROR_CODE_ILLEGAL_STATE_ERROR;
    /**
     * Error code(20) resulting in inability to find best
     *     integration time because we have reached the minimum.
     */
    DLL_DECL extern const int ERROR_CODE_MIN_INT_TIME_REACHED;
    /**
     * Error code(21) resulting in inability to find best
     *     integration time because we have reached the maxnimum.
     */
    DLL_DECL extern const int ERROR_CODE_MAX_INT_TIME_REACHED;
    /**
     * Error code(22) resulting in inability to find best
     *     integration time because lamp is likely off
     */
    DLL_DECL extern const int ERROR_ENSURE_LAMP_IS_ON;
    /**
     * Error code(23) representing when the given output 
     *     buffer is less than the expected output. 
     */
    DLL_DECL extern const int ERROR_NOT_ENOUGH_BUFFER_SPACE;
    /**
     * Error code(24) representing when the command
     *     invoked is not supprted by device.
     */
    DLL_DECL extern const int ERROR_COMMAND_NOT_SUPPORTED;

    /**
     * Error code(25) for those devices that have a different
     * minimum integration time for averaging returned when
     * averaging is enabled and an attempt to set the integration time
     * below this value or when the integration time is already below this value
     * and an attempt to enable averaging averaging is made.
     */
    DLL_DECL extern const int ERROR_INTEGRATION_TIME_BELOW_AVERAGING_MIN;

    /**
    * Error code(26) returned when the legacy electric dark or nonlinearity
    * correction is enabled but the user attempts to use one of the
    * newer correction functions that use getSpectrum. This would lead
    * to "double-correction".
    */
    DLL_DECL extern const int ERROR_DARK_NONLINEARITY_CORRECTION_CONFLICT;
#ifdef __cplusplus
}
#endif

/* When a new error code is added here, make sure to
also add a corresponding string to OceanDirectApi.cpp
static const char *error_msgs[]
*/
#endif /* OCEANDIRECTAPICONSTANTS_H */
