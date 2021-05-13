/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the UTF16Encoding class.
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

#include "Base/UTF16Encoding.h"
#include "Base/ByteOrder.h"
#include "Base/String.h"

namespace Technosoftware
{
    namespace Base
    {
        const char* UTF16Encoding::names_[] =
        {
            "UTF-16",
            "UTF16",
            NULL
        };


        const TextEncoding::CharacterMap UTF16Encoding::charMap_ =
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


        UTF16Encoding::UTF16Encoding(ByteOrderType byteOrder)
        {
            SetByteOrder(byteOrder);
        }


        UTF16Encoding::UTF16Encoding(int byteOrderMark)
        {
            SetByteOrder(byteOrderMark);
        }


        UTF16Encoding::~UTF16Encoding()
        {
        }


        UTF16Encoding::ByteOrderType UTF16Encoding::GetByteOrder() const
        {
#if defined(TECHNOSOFTWARE_ARCH_BIG_ENDIAN)
            return flipBytes_ ? LITTLE_ENDIAN_BYTE_ORDER : BIG_ENDIAN_BYTE_ORDER;
#else
            return flipBytes_ ? BIG_ENDIAN_BYTE_ORDER : LITTLE_ENDIAN_BYTE_ORDER;
#endif
        }


        void UTF16Encoding::SetByteOrder(ByteOrderType byteOrder)
        {
#if defined(TECHNOSOFTWARE_ARCH_BIG_ENDIAN)
            flipBytes_ = byteOrder == LITTLE_ENDIAN_BYTE_ORDER;
#else
            flipBytes_ = byteOrder == BIG_ENDIAN_BYTE_ORDER;;
#endif
        }


        void UTF16Encoding::SetByteOrder(int byteOrderMark)
        {
            flipBytes_ = byteOrderMark != 0xFEFF;
        }


        const char* UTF16Encoding::GetCanonicalName() const
        {
            return names_[0];
        }


        bool UTF16Encoding::IsA(const std::string& encodingName) const
        {
            for (const char** name = names_; *name; ++name)
            {
                if (Base::CaseInsensitiveCompare(encodingName, *name) == 0)
                    return true;
            }
            return false;
        }


        const TextEncoding::CharacterMap& UTF16Encoding::GetCharacterMap() const
        {
            return charMap_;
        }


        int UTF16Encoding::Convert(const unsigned char* bytes) const
        {
            UInt16 uc;
            unsigned char* p = (unsigned char*)&uc;
            *p++ = *bytes++;
            *p++ = *bytes++;

            if (flipBytes_)
            {
                ByteOrder::FlipBytes(uc);
            }

            if (uc >= 0xd800 && uc < 0xdc00)
            {
                UInt16 uc2;
                p = (unsigned char*)&uc2;
                *p++ = *bytes++;
                *p++ = *bytes++;

                if (flipBytes_)
                {
                    ByteOrder::FlipBytes(uc2);
                }
                if (uc2 >= 0xdc00 && uc2 < 0xe000)
                {
                    return ((uc & 0x3ff) << 10) + (uc2 & 0x3ff) + 0x10000;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return uc;
            }
        }


        int UTF16Encoding::Convert(int ch, unsigned char* bytes, int length) const
        {
            if (ch <= 0xFFFF)
            {
                if (bytes && length >= 2)
                {
                    UInt16 ch1 = flipBytes_ ? ByteOrder::FlipBytes((UInt16)ch) : (UInt16)ch;
                    unsigned char* p = (unsigned char*)&ch1;
                    *bytes++ = *p++;
                    *bytes++ = *p++;
                }
                return 2;
            }
            else
            {
                if (bytes && length >= 4)
                {
                    int ch1 = ch - 0x10000;
                    UInt16 w1 = 0xD800 + ((ch1 >> 10) & 0x3FF);
                    UInt16 w2 = 0xDC00 + (ch1 & 0x3FF);
                    if (flipBytes_)
                    {
                        w1 = ByteOrder::FlipBytes(w1);
                        w2 = ByteOrder::FlipBytes(w2);
                    }
                    unsigned char* p = (unsigned char*)&w1;
                    *bytes++ = *p++;
                    *bytes++ = *p++;
                    p = (unsigned char*)&w2;
                    *bytes++ = *p++;
                    *bytes++ = *p++;
                }
                return 4;
            }
        }


        int UTF16Encoding::QueryConvert(const unsigned char* bytes, int length) const
        {
            int ret = -2;

            if (length >= 2)
            {
                UInt16 uc;
                unsigned char* p = (unsigned char*)&uc;
                *p++ = *bytes++;
                *p++ = *bytes++;
                if (flipBytes_)
                    ByteOrder::FlipBytes(uc);
                if (uc >= 0xd800 && uc < 0xdc00)
                {
                    if (length >= 4)
                    {
                        UInt16 uc2;
                        p = (unsigned char*)&uc2;
                        *p++ = *bytes++;
                        *p++ = *bytes++;
                        if (flipBytes_)
                            ByteOrder::FlipBytes(uc2);
                        if (uc2 >= 0xdc00 && uc < 0xe000)
                        {
                            ret = ((uc & 0x3ff) << 10) + (uc2 & 0x3ff) + 0x10000;
                        }
                        else
                        {
                            ret = -1;    // Malformed sequence
                        }
                    }
                    else
                    {
                        ret = -4;    // surrogate pair, four bytes needed
                    }
                }
                else
                {
                    ret = uc;
                }
            }

            return ret;
        }


        int UTF16Encoding::GetSequenceLength(const unsigned char* bytes, int length) const
        {
            int ret = -2;

            if (flipBytes_)
            {
                if (length >= 1)
                {
                    unsigned char c = *bytes;
                    if (c >= 0xd8 && c < 0xdc)
                        ret = 4;
                    else
                        ret = 2;
                }
            }
            else
            {
                if (length >= 2)
                {
                    UInt16 uc;
                    unsigned char* p = (unsigned char*)&uc;
                    *p++ = *bytes++;
                    *p++ = *bytes++;
                    if (uc >= 0xd800 && uc < 0xdc00)
                        ret = 4;
                    else
                        ret = 2;
                }
            }
            return ret;
        }

    }
}
