/*******************************************************
 * @file    OBP2DeviceFactory.h
 * @date    June 2022
 * @author  Ocean Optics, Inc.
 *
 * Notes:
 *
 * This class allows Device class instances to be created
 * using just the name of the class as a string.
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

#ifndef OCEANDIRECT_OBP2DEVICE_FACTORY_H
#define OCEANDIRECT_OBP2DEVICE_FACTORY_H

#include <string>
#include <map>
#include "vendors/OceanOptics/devices/OBP2Device.h"

namespace oceandirect {

    class OBP2DeviceFactory {

    public:
        static OBP2DeviceFactory* getInstance();
        static OBP2DeviceFactory* instance;
        static void shutdown();

        OBP2Device* create(const std::string& name);
        OBP2Device* create(int index);
        int getNumberOfDeviceTypes();

    private:
        typedef OBP2Device* (*creatorFunction)(void);
        OBP2DeviceFactory();
        std::map<std::string, creatorFunction> nameToCreator;
    };

}

#endif
