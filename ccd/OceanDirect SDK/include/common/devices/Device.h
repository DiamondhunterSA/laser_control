/*******************************************************
 * @file    Device.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a base class for all sorts of devices.  A
 * device is really just an aggregation of features
 * with the protocols and buses required to access them.
 * A Device is intended to represent a single discrete
 * piece of equipment that may have several capabilities
 * (features) inside.  The device may communicate to the
 * outside world via seqences of bytes (a protocol) that
 * are transferred across a physical medium (the bus).
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

#ifndef DEVICE_H
#define DEVICE_H

#include <vector>
#include <string>
#include "common/public/UsbEndpoint.h"
#include "common/buses/Bus.h"
#include "common/buses/BusFamily.h"
#include "common/buses/DeviceLocatorInterface.h"
#include "common/features/Feature.h"
#include "common/features/FeatureFamily.h"
#include "common/protocols/Protocol.h"

namespace oceandirect {

    class Device {
    public:
        Device();
        virtual ~Device();
        std::vector<Bus *> &getBuses();
        std::vector<Feature *> &getFeatures();
        std::vector<Protocol *> &getProtocols();
        std::string &getName();
        
        // get the usb endpoints, according to the endpointType enumerator, 
        //  if the endpoint type is not used, a 0 is returned
        // TODO: this should be delegated down into a Bus instance
        // (e.g. found by getBusesByFamily()) for USB.  It is inappropriate here.
        unsigned char getEndpoint(int *errorCode, usbEndpointType endpointType);

        /* This will allow the driver to probe the device and initialize itself
         * based on what it finds there.  This should be called shortly after
         * open().  The Device instance should use the indicated Bus instance to
         * communicate with the hardware and get everything set up.  It can
         * use any appropriate protocol or protocols that are valid for the Bus.
         */
        virtual bool initialize(const Bus &bus);

        /* Each instance of a device is assumed to be associated with a unique
         * location on a bus.  If the device is connected via multiple buses, then
         * a special DeviceLocator and TransferHelper will have to hide those
         * details.  Otherwise, each connection to the device will be considered
         * independent of all others.
         */
        virtual DeviceLocatorInterface *getLocation();
        virtual void setLocation(const DeviceLocatorInterface &loc);

        virtual int open();

        virtual void close();

        virtual std::vector<Bus *> getBusesByFamily(BusFamily &family);

        virtual oceandirect::ProtocolFamily getSupportedProtocol(
                oceandirect::FeatureFamily family, BusFamily bus) = 0;

        virtual std::vector<Protocol *> getProtocolsByFamily(
                oceandirect::ProtocolFamily &family);

        virtual Bus *getOpenedBus();

    protected:
        void applyUnifiedTriggerModes(int fpgaMajorVersion, int minFPGAMajorVersion);
        int getFPGAMajorVersion(const Bus& bus);

    protected:
        std::vector<Bus *> buses;
        std::vector<Feature *> features;
        std::vector<Protocol *> protocols;

        std::string name;
        unsigned char usbEndpoint_primary_out;
    	unsigned char usbEndpoint_primary_in;
    	unsigned char usbEndpoint_secondary_out;
    	unsigned char usbEndpoint_secondary_in;
    	unsigned char usbEndpoint_secondary_in2; 
    	

        DeviceLocatorInterface *location;
        Bus *openedBus;
    };

}

#endif /* DEVICE_H */
