/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of fixed-size integer types for various platforms
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */


#ifndef TECHNOSOFTWARE_TYPES_H
#define TECHNOSOFTWARE_TYPES_H


#include "Base/Base.h"


namespace Technosoftware
{
    namespace Base
    {


#if defined(_MSC_VER)
        //
        // Windows/Visual C++
        //
        typedef signed char            Int8;
        typedef unsigned char          UInt8;
        typedef signed short           Int16;
        typedef unsigned short         UInt16;
        typedef signed int             Int32;
        typedef unsigned int           UInt32;
        typedef signed __int64         Int64;
        typedef unsigned __int64       UInt64;
#if defined(_WIN64)
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
        typedef signed __int64     IntPtr;
        typedef unsigned __int64   UIntPtr;
#else
        typedef signed long        IntPtr;
        typedef unsigned long      UIntPtr;
#endif
#define TECHNOSOFTWARE_HAVE_INT64 1
#elif defined(__GNUC__) || defined(__clang__)
        //
        // Unix/GCC/Clang
        //
        typedef signed char            Int8;
        typedef unsigned char          UInt8;
        typedef signed short           Int16;
        typedef unsigned short         UInt16;
        typedef signed int             Int32;
        typedef unsigned int           UInt32;
#if defined(_WIN64)
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
        typedef signed long long   IntPtr;
        typedef unsigned long long UIntPtr;
        typedef signed long long   Int64;
        typedef unsigned long long UInt64;
#else
        typedef signed long        IntPtr;
        typedef unsigned long      UIntPtr;
#if defined(__LP64__)
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
#define TECHNOSOFTWARE_LONG_IS_64_BIT 1
        typedef signed long        Int64;
        typedef unsigned long      UInt64;
#else
        typedef signed long long   Int64;
        typedef unsigned long long UInt64;
#endif
#endif
#define TECHNOSOFTWARE_HAVE_INT64 1
#elif defined(__DECCXX)
        //
        // Compaq C++
        //
        typedef signed char            Int8;
        typedef unsigned char          UInt8;
        typedef signed short           Int16;
        typedef unsigned short         UInt16;
        typedef signed int             Int32;
        typedef unsigned int           UInt32;
        typedef signed __int64         Int64;
        typedef unsigned __int64       UInt64;
#if defined(__VMS)
#if defined(__32BITS)
        typedef signed long    IntPtr;
        typedef unsigned long  UIntPtr;
#else
        typedef Int64          IntPtr;
        typedef UInt64         UIntPtr;
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
#endif
#else
        typedef signed long        IntPtr;
        typedef unsigned long      UIntPtr;
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
#define TECHNOSOFTWARE_LONG_IS_64_BIT 1
#endif
#define TECHNOSOFTWARE_HAVE_INT64 1
#elif defined(__HP_aCC)
        //
        // HP Ansi C++
        //
        typedef signed char            Int8;
        typedef unsigned char          UInt8;
        typedef signed short           Int16;
        typedef unsigned short         UInt16;
        typedef signed int             Int32;
        typedef unsigned int           UInt32;
        typedef signed long            IntPtr;
        typedef unsigned long          UIntPtr;
#if defined(__LP64__)
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
#define TECHNOSOFTWARE_LONG_IS_64_BIT 1
        typedef signed long        Int64;
        typedef unsigned long      UInt64;
#else
        typedef signed long long   Int64;
        typedef unsigned long long UInt64;
#endif
#define TECHNOSOFTWARE_HAVE_INT64 1
#elif defined(__SUNPRO_CC)
        //
        // SUN Forte C++
        //
        typedef signed char            Int8;
        typedef unsigned char          UInt8;
        typedef signed short           Int16;
        typedef unsigned short         UInt16;
        typedef signed int             Int32;
        typedef unsigned int           UInt32;
        typedef signed long            IntPtr;
        typedef unsigned long          UIntPtr;
#if defined(__sparcv9)
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
#define TECHNOSOFTWARE_LONG_IS_64_BIT 1
        typedef signed long        Int64;
        typedef unsigned long      UInt64;
#else
        typedef signed long long   Int64;
        typedef unsigned long long UInt64;
#endif
#define TECHNOSOFTWARE_HAVE_INT64 1
#elif defined(__IBMCPP__) 
        //
        // IBM XL C++
        //
        typedef signed char            Int8;
        typedef unsigned char          UInt8;
        typedef signed short           Int16;
        typedef unsigned short         UInt16;
        typedef signed int             Int32;
        typedef unsigned int           UInt32;
        typedef signed long            IntPtr;
        typedef unsigned long          UIntPtr;
#if defined(__64BIT__)
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
#define TECHNOSOFTWARE_LONG_IS_64_BIT 1
        typedef signed long        Int64;
        typedef unsigned long      UInt64;
#else
        typedef signed long long   Int64;
        typedef unsigned long long UInt64;
#endif
#define TECHNOSOFTWARE_HAVE_INT64 1
#elif defined(__sgi) 
        //
        // MIPSpro C++
        //
        typedef signed char            Int8;
        typedef unsigned char          UInt8;
        typedef signed short           Int16;
        typedef unsigned short         UInt16;
        typedef signed int             Int32;
        typedef unsigned int           UInt32;
        typedef signed long            IntPtr;
        typedef unsigned long          UIntPtr;
#if _MIPS_SZLONG == 64
#define TECHNOSOFTWARE_PTR_IS_64_BIT 1
#define TECHNOSOFTWARE_LONG_IS_64_BIT 1
        typedef signed long        Int64;
        typedef unsigned long      UInt64;
#else
        typedef signed long long   Int64;
        typedef unsigned long long UInt64;
#endif
#define TECHNOSOFTWARE_HAVE_INT64 1
#elif defined(_DIAB_TOOL)
        typedef signed char        Int8;
        typedef unsigned char      UInt8;
        typedef signed short       Int16;
        typedef unsigned short     UInt16;
        typedef signed int         Int32;
        typedef unsigned int       UInt32;
        typedef signed long        IntPtr;
        typedef unsigned long      UIntPtr;
        typedef signed long long   Int64;
        typedef unsigned long long UInt64;
#define TECHNOSOFTWARE_HAVE_INT64 1
#endif

    }
}


#endif /* TECHNOSOFTWARE_TYPES_H */
