/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the UTF32Encoding class.
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

#include "Base/UTF32Encoding.h"
#include "Base/ByteOrder.h"
#include "Base/String.h"

namespace Technosoftware
{
    namespace Base
    {
        const char* UTF32Encoding::names_[] =
        {
            "UTF-32",
            "UTF32",
            NULL
        };


        const TextEncoding::CharacterMap UTF32Encoding::charMap_ =
        {
            /* 00 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 10 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 20 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 30 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 40 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 50 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 60 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 70 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 80 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* 90 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* a0 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* b0 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* c0 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* d0 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* e0 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            /* f0 */    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
        };


        UTF32Encoding::UTF32Encoding(ByteOrderType byteOrder)
        {
            SetByteOrder(byteOrder);
        }


        UTF32Encoding::UTF32Encoding(int byteOrderMark)
        {
            SetByteOrder(byteOrderMark);
        }


        UTF32Encoding::~UTF32Encoding()
        {
        }


        UTF32Encoding::ByteOrderType UTF32Encoding::GetByteOrder() const
        {
#if defined(TECHNOSOFTWARE_ARCH_BIG_ENDIAN)
            return flipBytes_ ? LITTLE_ENDIAN_BYTE_ORDER : BIG_ENDIAN_BYTE_ORDER;
#else
            return flipBytes_ ? BIG_ENDIAN_BYTE_ORDER : LITTLE_ENDIAN_BYTE_ORDER;
#endif
        }


        void UTF32Encoding::SetByteOrder(ByteOrderType byteOrder)
        {
#if defined(TECHNOSOFTWARE_ARCH_BIG_ENDIAN)
            flipBytes_ = byteOrder == LITTLE_ENDIAN_BYTE_ORDER;
#else
            flipBytes_ = byteOrder == BIG_ENDIAN_BYTE_ORDER;;
#endif
        }


        void UTF32Encoding::SetByteOrder(int byteOrderMark)
        {
            flipBytes_ = byteOrderMark != 0xFEFF;
        }


        const char* UTF32Encoding::GetCanonicalName() const
        {
            return names_[0];
        }


        bool UTF32Encoding::IsA(const std::string& encodingName) const
        {
            for (const char** name = names_; *name; ++name)
            {
                if (Base::CaseInsensitiveCompare(encodingName, *name) == 0)
                    return true;
            }
            return false;
        }


        const TextEncoding::CharacterMap& UTF32Encoding::GetCharacterMap() const
        {
            return charMap_;
        }


        int UTF32Encoding::Convert(const unsigned char* bytes) const
        {
            UInt32 uc;
            unsigned char* p = (unsigned char*)&uc;
            *p++ = *bytes++;
            *p++ = *bytes++;
            *p++ = *bytes++;
            *p++ = *bytes++;

            if (flipBytes_)
            {
                ByteOrder::FlipBytes(uc);
            }

            return uc;
        }


        int UTF32Encoding::Convert(int ch, unsigned char* bytes, int length) const
        {
            if (bytes && length >= 4)
            {
                UInt32 ch1 = flipBytes_ ? ByteOrder::FlipBytes((UInt32)ch) : (UInt32)ch;
                unsigned char* p = (unsigned char*)&ch1;
                *bytes++ = *p++;
                *bytes++ = *p++;
                *bytes++ = *p++;
                *bytes++ = *p++;
            }
            return 4;
        }


        int UTF32Encoding::QueryConvert(const unsigned char* bytes, int length) const
        {
            int ret = -4;

            if (length >= 4)
            {
                UInt32 uc;
                unsigned char* p = (unsigned char*)&uc;
                *p++ = *bytes++;
                *p++ = *bytes++;
                *p++ = *bytes++;
                *p++ = *bytes++;
                if (flipBytes_)
                    ByteOrder::FlipBytes(uc);
                return uc;
            }

            return ret;
        }


        int UTF32Encoding::GetSequenceLength(const unsigned char* bytes, int length) const
        {
            return 4;
        }

    }
}
