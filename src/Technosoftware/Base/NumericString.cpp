/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Numeric string utility functions.
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

#include "Base/Bugcheck.h"

// +++ double conversion +++
#define UNREACHABLE technosoftware_bugcheck
#define UNIMPLEMENTED technosoftware_bugcheck
#include "diy-fp.cc"
#include "cached-powers.cc"
#include "bignum-dtoa.cc"
#include "bignum.cc"
#include "fast-dtoa.cc"
#include "fixed-dtoa.cc"
#include "strtod.cc"
#include "double-conversion.cc"
// --- double conversion ---

#include "Base/NumericString.h"
#include "Base/String.h"
#include <memory>
#include <cctype>

namespace {

    /**
     * @fn  void Pad(std::string& str, int precision, int width, char prefix = ' ', char decSep = '.')
     *
     * @brief   Pads the string with prefix space and postfix 0. Alternative prefix (e.g. zero
     *          instead of space) can be supplied by caller. Used only internally.
     *
     * @param [in,out]  str         The string.
     * @param           precision   The precision.
     * @param           width       The width.
     * @param           prefix      (Optional) the prefix.
     * @param           decSep      (Optional) the decrement separator.
     */

    void Pad(std::string& str, int precision, int width, char prefix = ' ', char decSep = '.')
    {
        // these cases should never happen, if they do, it's a library bug
        technosoftware_assert_dbg(precision > 0);
        technosoftware_assert_dbg(str.length());

        std::string::size_type decSepPos = str.find(decSep);
        if (decSepPos == std::string::npos)
        {
            str.append(1, '.');
            decSepPos = str.size() - 1;
        }

        std::string::size_type frac = str.length() - decSepPos - 1;

        std::string::size_type ePos = str.find_first_of("eE");
#if __cplusplus < 201103L
        std::auto_ptr<std::string> eStr;
#else
	std::unique_ptr<std::string> eStr;
#endif
        if (ePos != std::string::npos)
        {
            eStr.reset(new std::string(str.substr(ePos, std::string::npos)));
            frac -= eStr->length();
            str = str.substr(0, str.length() - eStr->length());
        }

        if (frac != precision)
        {
            if (frac < precision)
                str.append(precision - frac, '0');
            else if ((frac > precision) && (decSepPos != std::string::npos))
                str = str.substr(0, decSepPos + 1 + precision);
        }

        if (eStr.get()) str += *eStr;

        if (width && (str.length() < width)) str.insert(str.begin(), width - str.length(), prefix);
    }

    /**
     * @fn  void InsertThousandSep(std::string& str, char thSep, char decSep = '.')
     *
     * @brief   Inserts thousand separators. Used only internally.
     *
     * @param [in,out]  str     The string.
     * @param           thSep   The th separator.
     * @param           decSep  (Optional) the decrement separator.
     */

    void InsertThousandSep(std::string& str, char thSep, char decSep = '.')
    {
        technosoftware_assert(decSep != thSep);
        if (str.size() == 0) return;

        std::string::size_type exPos = str.find('e');
        if (exPos == std::string::npos) exPos = str.find('E');
        std::string::size_type decPos = str.find(decSep);
        // there's no rinsert, using forward iterator to go backwards
        std::string::iterator it = str.end();
        if (exPos != std::string::npos) it -= str.size() - exPos;

        if (decPos != std::string::npos)
        {
            while (it != str.begin())
            {
                --it;
                if (*it == decSep) break;
            }
        }
        int thCount = 0;
        if (it == str.end()) --it;
        for (; it != str.begin();)
        {
            std::string::iterator pos = it;
            std::string::value_type chr = *it;
            std::string::value_type prevChr = *--it;

            if (!std::isdigit(chr)) continue;

            if (++thCount == 3 && std::isdigit(prevChr))
                it = str.insert(pos, thSep);

            if (thCount == 3) thCount = 0;
        }
    }


} // namespace


namespace Technosoftware
{
    namespace Base
    {


        void FloatToStr(char* buffer, int bufferSize, float value, int lowDec, int highDec)
        {
            using namespace double_conversion;

            StringBuilder builder(buffer, bufferSize);
            int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
            DoubleToStringConverter dc(flags, TECHNOSOFTWARE_FLT_INF, TECHNOSOFTWARE_FLT_NAN, TECHNOSOFTWARE_FLT_EXP, lowDec, highDec, 0, 0);
            dc.ToShortestSingle(value, &builder);
            builder.Finalize();
        }


        void FloatToFixedStr(char* buffer, int bufferSize, float value, int precision)
        {
            using namespace double_conversion;

            StringBuilder builder(buffer, bufferSize);
            int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
            DoubleToStringConverter dc(flags, TECHNOSOFTWARE_FLT_INF, TECHNOSOFTWARE_FLT_NAN, TECHNOSOFTWARE_FLT_EXP, -std::numeric_limits<float>::digits10, std::numeric_limits<float>::digits10, 0, 0);
            dc.ToFixed(value, precision, &builder);
            builder.Finalize();
        }


        std::string& FloatToStr(std::string& str, float value, int precision, int width, char thSep, char decSep)
        {
            if (!decSep) decSep = '.';
            if (precision == 0) value = std::floor(value);

            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            FloatToStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value);
            str = buffer;

            if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
                ReplaceInPlace(str, '.', decSep);

            if (thSep) InsertThousandSep(str, thSep, decSep);
            if (precision > 0 || width) Pad(str, precision, width, ' ', decSep ? decSep : '.');
            return str;
        }


        std::string& FloatToFixedStr(std::string& str, float value, int precision, int width, char thSep, char decSep)
        {
            if (!decSep) decSep = '.';
            if (precision == 0) value = std::floor(value);

            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            FloatToFixedStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value, precision);
            str = buffer;

            if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
                ReplaceInPlace(str, '.', decSep);

            if (thSep) InsertThousandSep(str, thSep, decSep);
            if (precision > 0 || width) Pad(str, precision, width, ' ', decSep ? decSep : '.');
            return str;
        }


        void DoubleToStr(char* buffer, int bufferSize, double value, int lowDec, int highDec)
        {
            using namespace double_conversion;

            StringBuilder builder(buffer, bufferSize);
            int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
            DoubleToStringConverter dc(flags, TECHNOSOFTWARE_FLT_INF, TECHNOSOFTWARE_FLT_NAN, TECHNOSOFTWARE_FLT_EXP, lowDec, highDec, 0, 0);
            dc.ToShortest(value, &builder);
            builder.Finalize();
        }


        void DoubleToFixedStr(char* buffer, int bufferSize, double value, int precision)
        {
            using namespace double_conversion;

            StringBuilder builder(buffer, bufferSize);
            int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
            DoubleToStringConverter dc(flags, TECHNOSOFTWARE_FLT_INF, TECHNOSOFTWARE_FLT_NAN, TECHNOSOFTWARE_FLT_EXP, -std::numeric_limits<double>::digits10, std::numeric_limits<double>::digits10, 0, 0);
            dc.ToFixed(value, precision, &builder);
            builder.Finalize();
        }


        std::string& DoubleToStr(std::string& str, double value, int precision, int width, char thSep, char decSep)
        {
            if (!decSep) decSep = '.';
            if (precision == 0) value = std::floor(value);

            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            DoubleToStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value);

            str = buffer;

            if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
                ReplaceInPlace(str, '.', decSep);

            if (thSep) InsertThousandSep(str, thSep, decSep);
            if (precision > 0 || width) Pad(str, precision, width, ' ', decSep ? decSep : '.');
            return str;
        }


        std::string& DoubleToFixedStr(std::string& str, double value, int precision, int width, char thSep, char decSep)
        {
            if (!decSep) decSep = '.';
            if (precision == 0) value = std::floor(value);

            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            DoubleToFixedStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value, precision);

            str = buffer;

            if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
                ReplaceInPlace(str, '.', decSep);

            if (thSep) InsertThousandSep(str, thSep, decSep);
            if (precision > 0 || width) Pad(str, precision, width, ' ', decSep ? decSep : '.');
            return str;
        }


        float StrToFloat(const char* str)
        {
            using namespace double_conversion;

            int processed;
            int flags = StringToDoubleConverter::ALLOW_LEADING_SPACES |
                StringToDoubleConverter::ALLOW_TRAILING_SPACES;
            StringToDoubleConverter converter(flags, 0.0, Single::NaN(), TECHNOSOFTWARE_FLT_INF, TECHNOSOFTWARE_FLT_NAN);
            float result = converter.StringToFloat(str, static_cast<int>(strlen(str)), &processed);
            return result;
        }


        double StrToDouble(const char* str)
        {
            using namespace double_conversion;
            int processed;
            int flags = StringToDoubleConverter::ALLOW_LEADING_SPACES |
                StringToDoubleConverter::ALLOW_TRAILING_SPACES;
            StringToDoubleConverter converter(flags, 0.0, Double::NaN(), TECHNOSOFTWARE_FLT_INF, TECHNOSOFTWARE_FLT_NAN);
            double result = converter.StringToDouble(str, static_cast<int>(strlen(str)), &processed);
            return result;
        }


        bool StrToFloat(const std::string& str, float& result, char decSep, char thSep)
        {
            using namespace double_conversion;

            std::string tmp(str);
            TrimInPlace(tmp);
            RemoveInPlace(tmp, thSep);
            RemoveInPlace(tmp, 'f');
            ReplaceInPlace(tmp, decSep, '.');
            result = StrToFloat(tmp.c_str());
            return !FPEnvironment::IsInfinite(result) &&
                !FPEnvironment::IsNaN(result);
        }


        bool StrToDouble(const std::string& str, double& result, char decSep, char thSep)
        {
            if (str.empty()) return false;

            using namespace double_conversion;

            std::string tmp(str);
            TrimInPlace(tmp);
            RemoveInPlace(tmp, thSep);
            ReplaceInPlace(tmp, decSep, '.');
            RemoveInPlace(tmp, 'f');
            result = StrToDouble(tmp.c_str());
            return !FPEnvironment::IsInfinite(result) &&
                !FPEnvironment::IsNaN(result);
        }

    }
}
