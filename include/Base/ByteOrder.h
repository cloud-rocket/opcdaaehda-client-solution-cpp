/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of converters between big-endian and little-endian
 * integers of various sizes.
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

#ifndef TECHNOSOFTWARE_BYTEORDER_H
#define TECHNOSOFTWARE_BYTEORDER_H

#include "Base/Base.h"
#include "Base/Types.h"
#if defined(_MSC_VER)
#include <stdlib.h> // builtins
#endif

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   ByteOrder
         *
         * @brief   This class contains a number of static methods to convert between big-endian and
         *          little-endian integers of various sizes.
         *
         * @ingroup BaseCore
         */

        class TECHNOSOFTWARE_API ByteOrder
        {
        public:
            static Int16 FlipBytes(Int16 value);
            static UInt16 FlipBytes(UInt16 value);
            static Int32 FlipBytes(Int32 value);
            static UInt32 FlipBytes(UInt32 value);
#if defined(TECHNOSOFTWARE_HAVE_INT64)
            static Int64 FlipBytes(Int64 value);
            static UInt64 FlipBytes(UInt64 value);
#endif

            static Int16 ToBigEndian(Int16 value);
            static UInt16 ToBigEndian(UInt16 value);
            static Int32 ToBigEndian(Int32 value);
            static UInt32 ToBigEndian(UInt32 value);
#if defined(TECHNOSOFTWARE_HAVE_INT64)
            static Int64 ToBigEndian(Int64 value);
            static UInt64 ToBigEndian(UInt64 value);
#endif

            static Int16 FromBigEndian(Int16 value);
            static UInt16 FromBigEndian(UInt16 value);
            static Int32 FromBigEndian(Int32 value);
            static UInt32 FromBigEndian(UInt32 value);
#if defined(TECHNOSOFTWARE_HAVE_INT64)
            static Int64 FromBigEndian(Int64 value);
            static UInt64 FromBigEndian(UInt64 value);
#endif

            static Int16 ToLittleEndian(Int16 value);
            static UInt16 ToLittleEndian(UInt16 value);
            static Int32 ToLittleEndian(Int32 value);
            static UInt32 ToLittleEndian(UInt32 value);
#if defined(TECHNOSOFTWARE_HAVE_INT64)
            static Int64 ToLittleEndian(Int64 value);
            static UInt64 ToLittleEndian(UInt64 value);
#endif

            static Int16 FromLittleEndian(Int16 value);
            static UInt16 FromLittleEndian(UInt16 value);
            static Int32 FromLittleEndian(Int32 value);
            static UInt32 FromLittleEndian(UInt32 value);
#if defined(TECHNOSOFTWARE_HAVE_INT64)
            static Int64 FromLittleEndian(Int64 value);
            static UInt64 FromLittleEndian(UInt64 value);
#endif

            static Int16 ToNetwork(Int16 value);
            static UInt16 ToNetwork(UInt16 value);
            static Int32 ToNetwork(Int32 value);
            static UInt32 ToNetwork(UInt32 value);
#if defined(TECHNOSOFTWARE_HAVE_INT64)
            static Int64 ToNetwork(Int64 value);
            static UInt64 ToNetwork(UInt64 value);
#endif

            static Int16 FromNetwork(Int16 value);
            static UInt16 FromNetwork(UInt16 value);
            static Int32 FromNetwork(Int32 value);
            static UInt32 FromNetwork(UInt32 value);
#if defined(TECHNOSOFTWARE_HAVE_INT64)
            static Int64 FromNetwork(Int64 value);
            static UInt64 FromNetwork(UInt64 value);
#endif
        };


#if !defined(TECHNOSOFTWARE_NO_BYTESWAP_BUILTINS)
#if defined(_MSC_VER)
#if (TECHNOSOFTWARE_MSVC_VERSION > 71)
#define TECHNOSOFTWARE_HAVE_MSC_BYTESWAP 1
#endif
#elif defined(__clang__) 
#if __has_builtin(__builtin_bswap32)
#define TECHNOSOFTWARE_HAVE_GCC_BYTESWAP 1
#endif
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#define TECHNOSOFTWARE_HAVE_GCC_BYTESWAP 1
#endif
#endif


        //
        // inlines
        //
        inline UInt16 ByteOrder::FlipBytes(UInt16 value)
        {
#if defined(TECHNOSOFTWARE_HAVE_MSC_BYTESWAP)
            return _byteswap_ushort(value);
#else
            return ((value >> 8) & 0x00FF) | ((value << 8) & 0xFF00);
#endif
        }


        inline Int16 ByteOrder::FlipBytes(Int16 value)
        {
            return Int16(FlipBytes(UInt16(value)));
        }


        inline UInt32 ByteOrder::FlipBytes(UInt32 value)
        {
#if defined(TECHNOSOFTWARE_HAVE_MSC_BYTESWAP)
            return _byteswap_ulong(value);
#elif defined(TECHNOSOFTWARE_HAVE_GCC_BYTESWAP)
            return __builtin_bswap32(value);
#else
            return ((value >> 24) & 0x000000FF) | ((value >> 8) & 0x0000FF00)
                | ((value << 8) & 0x00FF0000) | ((value << 24) & 0xFF000000);
#endif
        }


        inline Int32 ByteOrder::FlipBytes(Int32 value)
        {
            return Int32(FlipBytes(UInt32(value)));
        }


#if defined(TECHNOSOFTWARE_HAVE_INT64)
        inline UInt64 ByteOrder::FlipBytes(UInt64 value)
        {
#if defined(TECHNOSOFTWARE_HAVE_MSC_BYTESWAP)
            return _byteswap_uint64(value);
#elif defined(TECHNOSOFTWARE_HAVE_GCC_BYTESWAP)
            return __builtin_bswap64(value);
#else
            UInt32 hi = UInt32(value >> 32);
            UInt32 lo = UInt32(value & 0xFFFFFFFF);
            return UInt64(FlipBytes(hi)) | (UInt64(FlipBytes(lo)) << 32);
#endif
        }


        inline Int64 ByteOrder::FlipBytes(Int64 value)
        {
            return Int64(FlipBytes(UInt64(value)));
        }
#endif // TECHNOSOFTWARE_HAVE_INT64


        //
        // some macro trickery to automate the method implementation
        //
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, type) \
    inline type ByteOrder::op(type value)        \
    {                                            \
        return value;                            \
    }
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, type) \
    inline type ByteOrder::op(type value)        \
    {                                            \
        return FlipBytes(value);                \
    }


#if defined(TECHNOSOFTWARE_HAVE_INT64)
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP(op) \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, Int16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, UInt16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, Int32)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, UInt32)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, Int64)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, UInt64)
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP(op) \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, Int16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, UInt16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, Int32)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, UInt32)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, Int64)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, UInt64)
#else
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP(op) \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, Int16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, UInt16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, Int32)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP_(op, UInt32)
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP(op) \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, Int16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, UInt16)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, Int32)    \
        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP_(op, UInt32)
#endif


#if defined(TECHNOSOFTWARE_ARCH_BIG_ENDIAN)
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_BIG TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_LIT TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP
#else
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_BIG TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_FLIP
#define TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_LIT TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_NOOP
#endif


        TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_BIG(ToBigEndian)
            TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_BIG(FromBigEndian)
            TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_BIG(ToNetwork)
            TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_BIG(FromNetwork)
            TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_LIT(ToLittleEndian)
            TECHNOSOFTWARE_IMPLEMENT_BYTEORDER_LIT(FromLittleEndian)

    }
}


#endif /* TECHNOSOFTWARE_BYTEORDER_H */
