/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Basic definitions for the Technosoftware Base library.
 * This file must be the first file included by every other Base
 * header file.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The source code in this file is covered under a dual-license scenario:
 *   - Owner of a purchased license: SCLA 1.0
 *   - GPL V3: everybody else
 *
 * SCLA license terms accompanied with this source code.
 * See SCLA 1.0: https://technosoftware.com/license/Source_Code_License_Agreement.pdf
 *
 * GNU General Public License as published by the Free Software Foundation;
 * version 3 of the License are accompanied with this source code.
 * See https://technosoftware.com/license/GPLv3License.txt
 *
 * This source code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef TECHNOSOFTWARE_BASE_H
#define TECHNOSOFTWARE_BASE_H

//
// Include library configuration
//
#include "Base/Config.h"

/**
 *
 * @namespace Technosoftware::Base
 * @brief Technosoftware::Base contains the API used by all other Technosoftware APIs.
 */

/**
 *
 * @defgroup Base Technosoftware Base API
 * @brief The Base group bundles all code usable by the Technosoftware Core, Client and Server APIs as well as the plugins.
 *
 * @defgroup BaseCore Core Functionality
 * @ingroup Base
 * @brief The Core group bundles the core functionality of the Technosoftware Base API.
 *
 * @defgroup BaseDateTime DateTime Functionality
 * @ingroup Base
 * @brief The DateTime group bundles the functionality related to Date and Time operations of the Technosoftware Base API.
 *
 * @defgroup BaseStreams Streams Functionality
 * @ingroup Base
 * @brief The Streams group bundles the functionality related to Date and Time operations of the Technosoftware Base API.
 *
 * @defgroup BaseText Text Functionality
 * @ingroup Base
 * @brief The Text group bundles the functionality related to Date and Time operations of the Technosoftware Base API.
 *
 * @defgroup BaseThreading Threading Functionality
 * @ingroup Base
 * @brief The Threading group bundles the functionality related to Date and Time operations of the Technosoftware Base API.
 *
 * @defgroup BaseOPC OPC Functionality
 * @ingroup Base
 * @brief The OPC group bundles the functionality related to Date and Time operations of the Technosoftware Base API.
 *
 */

//
// Ensure that TECHNOSOFTWARE_DLL is default unless TECHNOSOFTWARE_STATIC is defined
//
#if defined(_WIN32) && defined(_DLL)
    #if !defined(TECHNOSOFTWARE_DLL) && !defined(TECHNOSOFTWARE_STATIC)
        #define TECHNOSOFTWARE_DLL
    #endif
#endif


//
// The following block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the Foundation_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TECHNOSOFTWARE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if (defined(_WIN32) || defined(_WIN32_WCE)) && defined(TECHNOSOFTWARE_DLL)
    #if defined(TECHNOSOFTWARE_EXPORTS)
        #define TECHNOSOFTWARE_API __declspec(dllexport)
    #else
        #define TECHNOSOFTWARE_API __declspec(dllimport)    
    #endif
#endif


#if !defined(TECHNOSOFTWARE_API)
    #if !defined(TECHNOSOFTWARE_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
        #define TECHNOSOFTWARE_API __attribute__ ((visibility ("default")))
    #else
        #define TECHNOSOFTWARE_API
    #endif
#endif


//
// Automatically link Base library.
//
#if defined(_MSC_VER)
    #if defined(TECHNOSOFTWARE_DLL)
        #if defined(_DEBUG)
            #define TECHNOSOFTWARE_LIB_SUFFIX ".lib"
        #else
            #define TECHNOSOFTWARE_LIB_SUFFIX ".lib"
        #endif
    #elif defined(_DLL)
        #if defined(_DEBUG)
            #define TECHNOSOFTWARE_LIB_SUFFIX "mdd.lib"
        #else
            #define TECHNOSOFTWARE_LIB_SUFFIX "md.lib"
        #endif
    #else
        #if defined(_DEBUG)
            #define TECHNOSOFTWARE_LIB_SUFFIX "mtd.lib"
        #else
            #define TECHNOSOFTWARE_LIB_SUFFIX "mt.lib"
        #endif
    #endif

    #if !defined(TECHNOSOFTWARE_NO_AUTOMATIC_LIBS) && !defined(Foundation_EXPORTS)
        //#pragma comment(lib, "Technosoftware" TECHNOSOFTWARE_LIB_SUFFIX)
    #endif
#endif


//
// Include platform-specific definitions
//
#include "Base/Platform.h"
#if defined(_WIN32)
    #include "Base/Platform_WIN32.h"
#elif defined(__VMS)
    #include "Base/Platform_VMS.h"
#elif defined(TECHNOSOFTWARE_VXWORKS)
    #include "Base/Platform_VX.h"
#elif defined(TECHNOSOFTWARE_OS_FAMILY_UNIX)
    #include "Base/Platform_POSIX.h"
#endif


//
// Include alignment settings early
//
#include "Base/Alignment.h"

//
// Cleanup inconsistencies
//
#ifdef TECHNOSOFTWARE_OS_FAMILY_WINDOWS
    #if defined(TECHNOSOFTWARE_WIN32_UTF8) && defined(TECHNOSOFTWARE_NO_WSTRING)
        #error TECHNOSOFTWARE_WIN32_UTF8 and TECHNOSOFTWARE_NO_WSTRING are mutually exclusive.
    #endif
#else
    #ifdef TECHNOSOFTWARE_WIN32_UTF8
        #undef TECHNOSOFTWARE_WIN32_UTF8
    #endif
#endif


//
// TECHNOSOFTWARE_JOIN
//
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in TECHNOSOFTWARE_DO_JOIN2 but does in TECHNOSOFTWARE_DO_JOIN.
//
#define TECHNOSOFTWARE_JOIN(X, Y) TECHNOSOFTWARE_DO_JOIN(X, Y)
#define TECHNOSOFTWARE_DO_JOIN(X, Y) TECHNOSOFTWARE_DO_JOIN2(X, Y)
#define TECHNOSOFTWARE_DO_JOIN2(X, Y) X##Y


//
// Pull in basic definitions
//
#include "Base/Bugcheck.h"
#include "Base/Types.h"
#include <string>
#include <stdint.h>

/**
 *
 * @namespace Technosoftware
 * @brief Technosoftware is the main namespace of all Technosoftware APIs.
 *
 */

namespace Technosoftware
{
    namespace Base
    {
        /**
        * @typedef    uint32_t OpcStatusCode
        *
        * @brief    Define the OPC UA StatusCode type (a 32-bit unsigned integer, see Specs Part 4).
        */

        typedef uint32_t OpcStatusCode;
    }
}

#endif /* TECHNOSOFTWARE_BASE_H */
