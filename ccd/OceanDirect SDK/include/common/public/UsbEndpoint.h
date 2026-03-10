#ifndef OCEAN_USB_ENDPOINT_H
#define OCEAN_USB_ENDPOINT_H
/*******************************************************
 * @file    UsbEndpoint.h
 * @date    June 2021
 * @author  Ocean Insight, Inc.
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
// usb endpoints are associated with a particular device.
typedef enum usbEndpointType {
    kEndpointTypePrimaryOut, // slow speed
    kEndpointTypePrimaryIn,  // slow speed
    kEndpointTypeSecondaryOut, // could be high speed
    kEndpointTypeSecondaryIn,  // could be high speed
    kEndpointTypeSecondaryIn2  // generally high speed
} usbEndpointType;
#endif // !OCEAN_USB_ENDPOINT_H

