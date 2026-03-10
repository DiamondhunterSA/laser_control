/*******************************************************
 * @file    DllDecl.h
 * @date    September 2018
 * @author  Ocean Optics, Inc.
 *
 * This class provides the DLL import/export decorations
 * required for Windows DLLs.  It is encapsulated to
 * reduce copy-paste and to allow a single point of
 * maintenance.
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

#ifndef OCEANDIRECT_DLL_DECL_H
#define OCEANDIRECT_DLL_DECL_H

#ifdef _WIN32
    #ifdef BUILD_DLL
        #define DLL_DECL __declspec(dllexport)
    #else
        #define DLL_DECL __declspec(dllimport)
    #endif

    // "STL member 'oceandirect::api::Foo::foo' needs to have dll-interface
    // to be used by clients of class 'oceandirect::api::Foo'"
    #pragma warning (disable: 4251)

    // "non dll-interface class 'oceandirect::Foo' used as base for dll-interface
    // class 'oceandirect::api::Bar'"
    #pragma warning (disable: 4275)
#else
    #define DLL_DECL
#endif

#endif
