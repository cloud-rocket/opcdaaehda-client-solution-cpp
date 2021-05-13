/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the NumberFormatter class.
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


#include "Base/NumberFormatter.h"
#include "Base/MemoryStream.h"
#include <iomanip>
#if !defined(TECHNOSOFTWARE_NO_LOCALE)
#include <locale>
#endif
#include <cstdio>


#if defined(_MSC_VER) || defined(__MINGW32__)
#define I64_FMT "I64"
#elif defined(__APPLE__) 
#define I64_FMT "q"
#else
#define I64_FMT "ll"
#endif


namespace Technosoftware
{
    namespace Base
    {


        std::string NumberFormatter::Format(bool value, BoolFormat format)
        {
            switch (format)
            {
            default:
            case FMT_TRUE_FALSE:
                if (value == true)
                    return "true";
                return "false";
            case FMT_YES_NO:
                if (value == true)
                    return "yes";
                return "no";
            case FMT_ON_OFF:
                if (value == true)
                    return "on";
                return "off";
            }
        }


        void NumberFormatter::Append(std::string& str, int value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, int value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz, false, width);
            str.append(result, sz);
        }


        void NumberFormatter::Append0(std::string& str, int value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, int value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(static_cast<unsigned int>(value), 0x10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, int value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(static_cast<unsigned int>(value), 0x10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, unsigned value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, unsigned value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz, false, width);
            str.append(result, sz);
        }


        void NumberFormatter::Append0(std::string& str, unsigned int value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, unsigned value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 0x10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, unsigned value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 0x10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, long value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, long value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz, false, width);
            str.append(result, sz);
        }


        void NumberFormatter::Append0(std::string& str, long value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, long value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(static_cast<unsigned long>(value), 0x10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, long value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(static_cast<unsigned long>(value), 0x10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, unsigned long value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, unsigned long value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::Append0(std::string& str, unsigned long value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, unsigned long value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 0x10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, unsigned long value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 0x10, result, sz, false, width, '0');
            str.append(result, sz);
        }


#if defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)


        void NumberFormatter::Append(std::string& str, Int64 value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, Int64 value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::Append0(std::string& str, Int64 value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            IntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, Int64 value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(static_cast<UInt64>(value), 0x10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, Int64 value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(static_cast<UInt64>(value), 0x10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, UInt64 value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::Append(std::string& str, UInt64 value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::Append0(std::string& str, UInt64 value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 10, result, sz, false, width, '0');
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, UInt64 value)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 0x10, result, sz);
            str.append(result, sz);
        }


        void NumberFormatter::AppendHex(std::string& str, UInt64 value, int width)
        {
            char result[NF_MAX_INT_STRING_LEN];
            std::size_t sz = NF_MAX_INT_STRING_LEN;
            UIntToStr(value, 0x10, result, sz, false, width, '0');
            str.append(result, sz);
        }


#endif // defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)


        void NumberFormatter::Append(std::string& str, float value)
        {
            char buffer[NF_MAX_FLT_STRING_LEN];
            FloatToStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value);
            str.append(buffer);
        }


        void NumberFormatter::Append(std::string& str, float value, int precision)
        {
            char buffer[NF_MAX_FLT_STRING_LEN];
            FloatToFixedStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value, precision);
            str.append(buffer);
        }


        void NumberFormatter::Append(std::string& str, float value, int width, int precision)
        {
            std::string result;
            str.append(FloatToFixedStr(result, value, precision, width));
        }


        void NumberFormatter::Append(std::string& str, double value)
        {
            char buffer[NF_MAX_FLT_STRING_LEN];
            DoubleToStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value);
            str.append(buffer);
        }


        void NumberFormatter::Append(std::string& str, double value, int precision)
        {
            char buffer[NF_MAX_FLT_STRING_LEN];
            DoubleToFixedStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value, precision);
            str.append(buffer);
        }


        void NumberFormatter::Append(std::string& str, double value, int width, int precision)
        {
            std::string result;
            str.append(DoubleToFixedStr(result, value, precision, width));
        }


        void NumberFormatter::Append(std::string& str, const void* ptr)
        {
            char buffer[24];
#if defined(TECHNOSOFTWARE_PTR_IS_64_BIT)
#if defined(TECHNOSOFTWARE_LONG_IS_64_BIT)
            std::sprintf(buffer, "%016lX", (UIntPtr)ptr);
#else
            std::sprintf(buffer, "%016" I64_FMT "X", (UIntPtr)ptr);
#endif
#else
            std::sprintf(buffer, "%08lX", (UIntPtr)ptr);
#endif
            str.append(buffer);
        }


    }
}
