/*******************************************************
 * @file    DeviceFactory.h
 * @date    February 2018
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

#ifndef OCEANDIRECT_DEVICE_FACTORY_H
#define OCEANDIRECT_DEVICE_FACTORY_H

#include <string>
#include <map>
#include "common/devices/Device.h"

namespace oceandirect {

    class DeviceFactory {

    public:
        static DeviceFactory* getInstance();
        static DeviceFactory* instance;
        static void shutdown();

        Device *create(const std::string& name);
        Device *create(int index);
        int getNumberOfDeviceTypes();

    private:
        typedef Device *(*creatorFunction)(void);
        DeviceFactory();
        std::map<std::string, creatorFunction> nameToCreator;
    };

}

#endif
