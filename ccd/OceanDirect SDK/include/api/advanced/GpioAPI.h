/*****************************************************
 * @file    GpioAPI.h
 * @date    July 2019
 * @author  Ocean Optics, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to connect to devices over USB and other buses.
 * This is intended as a usable and extensible API.
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

#ifndef GPIOAPI_H
#define GPIOAPI_H

#include "api/DllDecl.h"
#include <cstdint>

 /*!
     @brief  This is an interface to advanced features of
             OceanDirect that allow access to less common
             controls. This is intended as a usable and
             extensible API.
 */
namespace oceandirect {
    namespace api {

        class DLL_DECL GpioAPI {
        public:
            GpioAPI();
            virtual ~GpioAPI() = default;
            static GpioAPI *getInstance();

            static void shutdown();

            /* GPIO capabilities */
            /*!
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @return the number of GPIO pins provided by the device.
            */
            virtual int getNumberOfGPIO(long deviceID, int *errorCode);
            /*! Set the direction (input/output) of a specified GPIO pin.
             * @see getOutputEnable()
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @param bit the GPIO pin to set.
             * @param isOutput set to true to make the pin output, false to make the pin input.
            */
            virtual void setOutputEnable(long deviceID, int *errorCode, std::uint32_t bitPosition, bool isOutput);
            /*! Set the direction (input/output) of the GPIO pins.
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @param bitmask a bitmask specifying the pin directions i.e. the nth bit set to 1 sets the nth pin to output.
            */
            virtual void setOutputEnable(long deviceID, int *errorCode, std::uint32_t bitmask);

            /*!
             * Read bit direction on whether it's in or out.
             * @see setOutputEnable()
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @param bit the GPIO pin to query.
             * @return true if the pin is an output pin, false if the pin is an input pin.
            */
            virtual bool getOutputEnable(long deviceID, int *errorCode, int bit);
            /*!
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @return the bitmask specifying the direction of each GPIO pin.
            */
            virtual std::uint32_t getOutputEnable(long deviceID, int *errorCode);

            /*!
             * Set the logic value for a spcified pin.
             * @see getValue()
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @param bit the GPIO pin to set.
             * @param isHigh set true to set the logic level high, set false to set the logic level low.
            */
            virtual void setValue(long deviceID, int *errorCode, std::uint32_t bitPosition, bool isHigh);
            /*! Set the logic value for all GPIO pins.
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @param bitmask the bitmask specifying the logic level of each GPIO pin.
            */
            virtual void setValue(long deviceID, int *errorCode, std::uint32_t bitmask);

            /*!
             * Read the bit value whether it's high or low.
             * @see setValue()
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @param bit the GPIO pin to query.
             * @return true if the specified pin is set to logic level hig, false if the specified pin is set to logic level low.
            */
            virtual bool getValue(long deviceID, int *errorCode, int bit);
            /*!
             * @param deviceID the ID of the device returned by getDeviceIDs.
             * @param errorCode on exit this contains zero on success, nonzero otherwise.
             * @return the bitmask specifying the logic level of each GPIO pin.
            */
            virtual uint32_t getValue(long deviceID, int *errorCode);

            /**
            * Set the alternate functionality for the specified pin (bit) number. Not
            * all spectrometers support this functionality.
            *
            * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
            * @param deviceID The ID of the device returned by getDeviceIDs.
            * @param errorCode on exit this contains zero on success, nonzero otherwise.
            * @param bit Which GPIO bit or pin to set
            * @param isAlternate set true to enable the alternate functionality for the pin, false otherwise (pin is a GPIO pin).
            */
            virtual void setOutputAlternate(long deviceID, int* errorCode, int bit, bool isAlternate);

            /**
            * Set the alternate functionality for the specified pins (bits). Not
            * all spectrometers support this functionality.
            *
            * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
            * @param deviceID The ID of the device returned by getDeviceIDs.
            * @param errorCode on exit this contains zero on success, nonzero otherwise.
            * @param bitMask with bit set to 1 to set enable the alternate functionality, 0 otherwise (pin is a GPIO pin).
            */
            virtual void setOutputAlternate(long deviceID, int* errorCode, uint32_t bitMask);

            /**
            * Get the setting for alternate functionality on the specified bit (pin). Not
            * all spectrometers support this functionality.
            *
            * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
            * @param deviceID The ID of the device returned by getDeviceIDs.
            * @param errorCode on exit this contains zero on success, nonzero otherwise.
            * @param bit Which GPIO bit or pin to query.
            * @return true if the pin is set to alternate functionality, false otherwise (pin is a GPIO pin).
            */
            virtual bool getOutputAlternate(long deviceID, int* errorCode, int bit);

            /**
            * Get the settings for alternate functionality on the GPIO pins. Not
            * all spectrometers support this functionality.
            *
            * @deprecated This function is deprecated starting with release 2.1 and will be removed in the future release.
            * @param deviceID The ID of the device returned by getDeviceIDs.
            * @param errorCode on exit this contains zero on success, nonzero otherwise.
            * @return a bitmask with value 1 where the corresponding pin is set to alternate functionality, 0 otherwise (pin is a GPIO pin).
            */
            virtual uint32_t getOutputAlternate(long deviceID, int* errorCode);

        protected:
            static GpioAPI *instance;

        };
    }
}
#endif /* GPIOAPI_H */
