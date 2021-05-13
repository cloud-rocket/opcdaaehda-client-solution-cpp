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

#ifndef TECHNOSOFTWARE_NUMERICSTRING_H
#define TECHNOSOFTWARE_NUMERICSTRING_H

#include "Base/Base.h"
#include "Base/Buffer.h"
#include "Base/FPEnvironment.h"
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#include <limits>
#include <cmath>
#if !defined(TECHNOSOFTWARE_NO_LOCALE)
#include <locale>
#endif

/**
 * @def    TECHNOSOFTWARE_MAX_INT_STRING_LEN
 *
 * @brief    binary numbers are supported, thus 64 (bits) + 1 (string terminating zero)
 *
 * @ingroup BaseCore
 */

#define TECHNOSOFTWARE_MAX_INT_STRING_LEN 65

/**
 * @def    TECHNOSOFTWARE_MAX_FLT_STRING_LEN
 *
 * @brief    value from strtod.cc (double_conversion::kMaxSignificantDecimalDigits)
 *
 * @ingroup BaseCore
 */

#define TECHNOSOFTWARE_MAX_FLT_STRING_LEN 780

#define TECHNOSOFTWARE_FLT_INF "inf"
#define TECHNOSOFTWARE_FLT_NAN "nan"
#define TECHNOSOFTWARE_FLT_EXP 'e'


namespace Technosoftware
{
    namespace Base
    {
        /**
         * @fn    inline char GetDecimalSeparator()
         *
         * @brief    Returns decimal separator from global locale or default '.' for platforms where
         *             locale is unavailable.
         *
         * @return    The decimal separator.
         *
         * @ingroup BaseCore
         */

        inline char GetDecimalSeparator()
        {
#if !defined(TECHNOSOFTWARE_NO_LOCALE)
            return std::use_facet<std::numpunct<char> >(std::locale()).decimal_point();
#else
            return '.';
#endif
        }

        /**
         * @fn    inline char GetThousandSeparator()
         *
         * @brief    Returns thousand separator from global locale or default ',' for platforms where
         *             locale is unavailable.
         *
         * @return    The thousand separator.
         *
         * @ingroup BaseCore
         */

        inline char GetThousandSeparator()
        {
#if !defined(TECHNOSOFTWARE_NO_LOCALE)
            return std::use_facet<std::numpunct<char> >(std::locale()).thousands_sep();
#else
            return ',';
#endif
        }

        /**
         * @fn    bool StrToInt(const char* pStr, I& result, short base, char thSep = ',')
         *
         * @brief    Converts zero-terminated character array to integer number;
         *             Thousand separators are recognized for base10 and current locale;
         *             it is silently skipped but not verified for correct positioning. Function returns
         *             true if succesful. If parsing was unsuccesful, the return value is false with the
         *             result value undetermined.
         *
         * @param    pStr              The string.
         * @param [in,out]    result    The result.
         * @param    base              The base.
         * @param    thSep              (Optional) the th separator.
         *
         * @return    The given data converted to a bool.
         *
         * @ingroup BaseCore
         */

        template <typename I>
        bool StrToInt(const char* pStr, I& result, short base, char thSep = ',')
        {
            if (!pStr) return false;
            while (isspace(*pStr)) ++pStr;
            if (*pStr == '\0') return false;
            short sign = 1;
            if ((base == 10) && (*pStr == '-'))
            {
                // Unsigned types can't be negative so abort parsing
                if (std::numeric_limits<I>::min() >= 0) return false;
                sign = -1;
                ++pStr;
            }
            else if (*pStr == '+') ++pStr;

            // parser states:
            const char STATE_SIGNIFICANT_DIGITS = 1;
            char state = 0;

            result = 0;
            I limitCheck = std::numeric_limits<I>::max() / base;
            for (; *pStr != '\0'; ++pStr)
            {
                switch (*pStr)
                {
                case '0':
                    if (state < STATE_SIGNIFICANT_DIGITS) break;

                case '1': case '2': case '3': case '4':
                case '5': case '6': case '7':
                    if (state < STATE_SIGNIFICANT_DIGITS) state = STATE_SIGNIFICANT_DIGITS;
                    if (result > limitCheck) return false;
                    result = result * base + (*pStr - '0');

                    break;

                case '8': case '9':
                    if ((base == 10) || (base == 0x10))
                    {
                        if (state < STATE_SIGNIFICANT_DIGITS) state = STATE_SIGNIFICANT_DIGITS;
                        if (result > limitCheck) return false;
                        result = result * base + (*pStr - '0');
                    }
                    else return false;

                    break;

                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                    if (base != 0x10) return false;
                    if (state < STATE_SIGNIFICANT_DIGITS) state = STATE_SIGNIFICANT_DIGITS;
                    if (result > limitCheck) return false;
                    result = result * base + (10 + *pStr - 'a');

                    break;

                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                    if (base != 0x10) return false;
                    if (state < STATE_SIGNIFICANT_DIGITS) state = STATE_SIGNIFICANT_DIGITS;
                    if (result > limitCheck) return false;
                    result = result * base + (10 + *pStr - 'A');

                    break;

                case '.':
                    if ((base == 10) && (thSep == '.')) break;
                    else return false;

                case ',':
                    if ((base == 10) && (thSep == ',')) break;
                    else return false;

                case ' ':
                    if ((base == 10) && (thSep == ' ')) break;
                    // fallthrough

                default:
                    return false;
                }
            }

            if ((sign < 0) && (base == 10)) result *= sign;

            return true;
        }


        /**
         * @fn    bool StrToInt(const std::string& str, I& result, short base, char thSep = ',')
         *
         * @brief    Converts string to integer number;
         *             This is a wrapper function, for details see see the bool strToInt(const char*, I&amp;,
         *             short, char) implementation.
         *
         * @param    str                  The string.
         * @param [in,out]    result    The result.
         * @param    base              The base.
         * @param    thSep              (Optional) the th separator.
         *
         * @return    The given data converted to a bool.
         *
         * @ingroup BaseCore
         */

        template <typename I>
        bool StrToInt(const std::string& str, I& result, short base, char thSep = ',')
        {
            return strToInt(str.c_str(), result, base, thSep);
        }


        //
        // Number to String Conversions
        //

        namespace Impl {

            class Ptr
                /// Utility char pointer wrapper class.
                /// Class ensures increment/decrement remain within boundaries.
            {
            public:
                Ptr(char* ptr, std::size_t offset) : _beg(ptr), _cur(ptr), end_(ptr + offset)
                {
                }

                char*& operator ++ () // prefix
                {
			checkBounds(_cur + 1);
                    return ++_cur;
                }

                char* operator ++ (int) // postfix
                {
			checkBounds(_cur + 1);
                    char* tmp = _cur++;
                    return tmp;
                }

                char*& operator -- () // prefix
                {
			checkBounds(_cur - 1);
                    return --_cur;
                }

                char* operator -- (int) // postfix
                {
			checkBounds(_cur - 1);
                    char* tmp = _cur--;
                    return tmp;
                }

                char*& operator += (int incr)
                {
			checkBounds(_cur + incr);
                    return _cur += incr;
                }

                char*& operator -= (int decr)
                {
			checkBounds(_cur - decr);
                    return _cur -= decr;
                }

                operator char* () const
                {
                    return _cur;
                }

                std::size_t span() const
                {
                    return end_ - _beg;
                }

            private:
		void checkBounds(char* ptr)
                {
                    if (ptr > end_) throw RangeException();
                }

                const char* _beg;
                char*       _cur;
                const char* end_;
            };

        } // namespace Impl

        /**
         * @fn  bool IntToStr(T value, unsigned short base, char* result, std::size_t& size, bool prefix = false, int width = -1, char fill = ' ', char thSep = 0)
         *
         * @brief   Converts integer to string. Numeric bases from binary to hexadecimal are supported.
         *          If width is non-zero, it pads the return value with fill character to the specified
         *          width. When padding is zero character ('0'), it is prepended to the number itself;
         *          all other paddings are prepended to the formatted result with minus sign or base
         *          prefix included If prefix is true and base is octal or hexadecimal, respective prefix
         *          ('0' for octal, "0x" for hexadecimal) is prepended. For all other bases, prefix
         *          argument is ignored. Formatted string has at least [width] total length.
         *
         * @param   value           The value.
         * @param   base            The base.
         * @param [out] result      If non-null, the result.
         * @param [in,out]  size    The size.
         * @param   prefix          (Optional) true to prefix.
         * @param   width           (Optional) the width.
         * @param   fill            (Optional) the fill.
         * @param   thSep           (Optional) the th separator.
         *
         * @return  true if it succeeds, false if it fails.
         *
         * @ingroup BaseCore
         */

        template <typename T>
        bool IntToStr(T value,
            unsigned short base,
            char* result,
            std::size_t& size,
            bool prefix = false,
            int width = -1,
            char fill = ' ',
            char thSep = 0)
        {
            if (base < 2 || base > 0x10)
            {
                *result = '\0';
                return false;
            }

            Impl::Ptr ptr(result, size);
            int thCount = 0;
            T tmpVal;
            do
            {
                tmpVal = value;
                value /= base;
                *ptr++ = "FEDCBA9876543210123456789ABCDEF"[15 + (tmpVal - value * base)];
                if (thSep && (base == 10) && (++thCount == 3))
                {
                    *ptr++ = thSep;
                    thCount = 0;
                }
            } while (value);

            if ('0' == fill)
            {
                if (tmpVal < 0) --width;
                if (prefix && base == 010) --width;
                if (prefix && base == 0x10) width -= 2;
                while ((ptr - result) < width) *ptr++ = fill;
            }

            if (prefix && base == 010) *ptr++ = '0';
            else if (prefix && base == 0x10)
            {
                *ptr++ = 'x';
                *ptr++ = '0';
            }

            if (tmpVal < 0) *ptr++ = '-';

            if ('0' != fill)
            {
                while ((ptr - result) < width) *ptr++ = fill;
            }

            size = ptr - result;
            technosoftware_assert_dbg(size <= ptr.span());
            technosoftware_assert_dbg((-1 == width) || (size >= size_t(width)));
            *ptr-- = '\0';

            char* ptrr = result;
            char tmp;
            while (ptrr < ptr)
            {
                tmp = *ptr;
                *ptr-- = *ptrr;
                *ptrr++ = tmp;
            }

            return true;
        }

        /**
         * @fn  bool UIntToStr(T value, unsigned short base, char* result, std::size_t& size, bool prefix = false, int width = -1, char fill = ' ', char thSep = 0)
         *
         * @brief   Converts unsigned integer to string. Numeric bases from binary to hexadecimal are
         *          supported. If width is non-zero, it pads the return value with fill character to the
         *          specified width. When padding is zero character ('0'), it is prepended to the number
         *          itself; all other paddings are prepended to the formatted result with minus sign or
         *          base prefix included If prefix is true and base is octal or hexadecimal, respective
         *          prefix ('0' for octal, "0x" for hexadecimal) is prepended. For all other bases,
         *          prefix argument is ignored. Formatted string has at least [width] total length.
         *
         * @param   value           The value.
         * @param   base            The base.
         * @param [out] result      If non-null, the result.
         * @param [in,out]  size    The size.
         * @param   prefix          (Optional) true to prefix.
         * @param   width           (Optional) the width.
         * @param   fill            (Optional) the fill.
         * @param   thSep           (Optional) the th separator.
         *
         * @return  true if it succeeds, false if it fails.
         *
         * @ingroup BaseCore
         */

        template <typename T>
        bool UIntToStr(T value,
            unsigned short base,
            char* result,
            std::size_t& size,
            bool prefix = false,
            int width = -1,
            char fill = ' ',
            char thSep = 0)
        {
            if (base < 2 || base > 0x10)
            {
                *result = '\0';
                return false;
            }

            Impl::Ptr ptr(result, size);
            int thCount = 0;
            T tmpVal;
            do
            {
                tmpVal = value;
                value /= base;
                *ptr++ = "FEDCBA9876543210123456789ABCDEF"[15 + (tmpVal - value * base)];
                if (thSep && (base == 10) && (++thCount == 3))
                {
                    *ptr++ = thSep;
                    thCount = 0;
                }
            } while (value);

            if ('0' == fill)
            {
                if (prefix && base == 010) --width;
                if (prefix && base == 0x10) width -= 2;
                while ((ptr - result) < width) *ptr++ = fill;
            }

            if (prefix && base == 010) *ptr++ = '0';
            else if (prefix && base == 0x10)
            {
                *ptr++ = 'x';
                *ptr++ = '0';
            }

            if ('0' != fill)
            {
                while ((ptr - result) < width) *ptr++ = fill;
            }

            size = ptr - result;
            technosoftware_assert_dbg(size <= ptr.span());
            technosoftware_assert_dbg((-1 == width) || (size >= size_t(width)));
            *ptr-- = '\0';

            char* ptrr = result;
            char tmp;
            while (ptrr < ptr)
            {
                tmp = *ptr;
                *ptr-- = *ptrr;
                *ptrr++ = tmp;
            }

            return true;
        }

        /**
         * @fn  bool IntToStr(T number, unsigned short base, std::string& result, bool prefix = false, int width = -1, char fill = ' ', char thSep = 0)
         *
         * @brief   Converts integer to string; This is a wrapper function, for details see see the bool
         *          intToStr(T, unsigned short, char*, int, int, char, char) implementation.
         *
         * @param   number          Number of.
         * @param   base            The base.
         * @param [in,out]  result  The result.
         * @param   prefix          (Optional) true to prefix.
         * @param   width           (Optional) the width.
         * @param   fill            (Optional) the fill.
         * @param   thSep           (Optional) the th separator.
         *
         * @return  true if it succeeds, false if it fails.
         *
         * @ingroup BaseCore
         */

        template <typename T>
        bool IntToStr(T number, unsigned short base, std::string& result, bool prefix = false, int width = -1, char fill = ' ', char thSep = 0)
        {
            char res[TECHNOSOFTWARE_MAX_INT_STRING_LEN] = { 0 };
            std::size_t size = TECHNOSOFTWARE_MAX_INT_STRING_LEN;
            bool ret = IntToStr(number, base, res, size, prefix, width, fill, thSep);
            result.assign(res, size);
            return ret;
        }

        /**
         * @fn  bool UIntToStr(T number, unsigned short base, std::string& result, bool prefix = false, int width = -1, char fill = ' ', char thSep = 0)
         *
         * @brief   Converts unsigned integer to string; This is a wrapper function, for details see see
         *          the bool uIntToStr(T, unsigned short, char*, int, int, char, char) implementation.
         *
         * @param   number          Number of.
         * @param   base            The base.
         * @param [in,out]  result  The result.
         * @param   prefix          (Optional) true to prefix.
         * @param   width           (Optional) the width.
         * @param   fill            (Optional) the fill.
         * @param   thSep           (Optional) the th separator.
         *
         * @return  true if it succeeds, false if it fails.
         *
         * @ingroup BaseCore
         */

        template <typename T>
        bool UIntToStr(T number, unsigned short base, std::string& result, bool prefix = false, int width = -1, char fill = ' ', char thSep = 0)
        {
            char res[TECHNOSOFTWARE_MAX_INT_STRING_LEN] = { 0 };
            std::size_t size = TECHNOSOFTWARE_MAX_INT_STRING_LEN;
            bool ret = UIntToStr(number, base, res, size, prefix, width, fill, thSep);
            result.assign(res, size);
            return ret;
        }


        //
        // Wrappers for double-conversion library (http://code.google.com/p/double-conversion/).
        //
        // Library is the implementation of the algorithm described in Florian Loitsch's paper:
        // http://florian.loitsch.com/publications/dtoa-pldi2010.pdf
        //

        /**
         * @fn    TECHNOSOFTWARE_API void FloatToStr(char* buffer, int bufferSize, float value, int lowDec = -std::numeric_limits<float>::digits10, int highDec = std::numeric_limits<float>::digits10);
         *
         * @brief    Converts a float value to string. Converted string must be shorter than bufferSize.
         *             Conversion is done by computing the shortest string of digits that correctly
         *             represents the input number. Depending on lowDec and highDec values, the function
         *             returns decimal or exponential representation.
         *
         * @param [in,out]    buffer    If non-null, the buffer.
         * @param    bufferSize          Size of the buffer.
         * @param    value              The value.
         * @param    lowDec              (Optional) the low decrement.
         * @param    highDec              (Optional) the high decrement.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API void FloatToStr(char* buffer,
            int bufferSize,
            float value,
            int lowDec = -std::numeric_limits<float>::digits10,
            int highDec = std::numeric_limits<float>::digits10);

        /**
         * @fn    TECHNOSOFTWARE_API void FloatToFixedStr(char* buffer, int bufferSize, float value, int precision);
         *
         * @brief    Converts a float value to string. Converted string must be shorter than bufferSize.
         *             Computes a decimal representation with a fixed number of digits after the decimal
         *             point.
         *
         * @param [in,out]    buffer    If non-null, the buffer.
         * @param    bufferSize          Size of the buffer.
         * @param    value              The value.
         * @param    precision          The precision.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API void FloatToFixedStr(char* buffer,
            int bufferSize,
            float value,
            int precision);

        /**
         * @fn    TECHNOSOFTWARE_API std::string& FloatToStr(std::string& str, float value, int precision = -1, int width = 0, char thSep = 0, char decSep = 0);
         *
         * @brief    Converts a float value, assigns it to the supplied string and returns the reference.
         *             This function calls floatToStr(char*, int, float, int, int) and formats the result
         *             according to precision (total number of digits after the decimal point, -1 means
         *             ignore precision argument)
         *             and width (total length of formatted string).
         *
         * @param [in,out]    str    The string.
         * @param    value           The value.
         * @param    precision      (Optional) the precision.
         * @param    width           (Optional) the width.
         * @param    thSep           (Optional) the th separator.
         * @param    decSep           (Optional) the decrement separator.
         *
         * @return    A reference to a std::string.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API std::string& FloatToStr(std::string& str,
            float value,
            int precision = -1,
            int width = 0,
            char thSep = 0,
            char decSep = 0);

        /**
         * @fn    TECHNOSOFTWARE_API std::string& FloatToFixedStr(std::string& str, float value, int precision, int width = 0, char thSep = 0, char decSep = 0);
         *
         * @brief    Converts a float value, assigns it to the supplied string and returns the reference.
         *             This function calls floatToFixedStr(char*, int, float, int) and formats the result
         *             according to precision (total number of digits after the decimal point) and width
         *             (total length of formatted string).
         *
         * @param [in,out]    str    The string.
         * @param    value           The value.
         * @param    precision      The precision.
         * @param    width           (Optional) the width.
         * @param    thSep           (Optional) the th separator.
         * @param    decSep           (Optional) the decrement separator.
         *
         * @return    A reference to a std::string.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API std::string& FloatToFixedStr(std::string& str,
            float value,
            int precision,
            int width = 0,
            char thSep = 0,
            char decSep = 0);

        /**
         * @fn    TECHNOSOFTWARE_API void DoubleToStr(char* buffer, int bufferSize, double value, int lowDec = -std::numeric_limits<double>::digits10, int highDec = std::numeric_limits<double>::digits10);
         *
         * @brief    Converts a double value to string. Converted string must be shorter than bufferSize.
         *             Conversion is done by computing the shortest string of digits that correctly
         *             represents the input number. Depending on lowDec and highDec values, the function
         *             returns decimal or exponential representation.
         *
         * @param [in,out]    buffer    If non-null, the buffer.
         * @param    bufferSize          Size of the buffer.
         * @param    value              The value.
         * @param    lowDec              (Optional) the low decrement.
         * @param    highDec              (Optional) the high decrement.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API void DoubleToStr(char* buffer,
            int bufferSize,
            double value,
            int lowDec = -std::numeric_limits<double>::digits10,
            int highDec = std::numeric_limits<double>::digits10);

        /**
         * @fn    TECHNOSOFTWARE_API void DoubleToFixedStr(char* buffer, int bufferSize, double value, int precision);
         *
         * @brief    Converts a double value to string. Converted string must be shorter than bufferSize.
         *             Computes a decimal representation with a fixed number of digits after the decimal
         *             point.
         *
         * @param [in,out]    buffer    If non-null, the buffer.
         * @param    bufferSize          Size of the buffer.
         * @param    value              The value.
         * @param    precision          The precision.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API void DoubleToFixedStr(char* buffer,
            int bufferSize,
            double value,
            int precision);

        /**
         * @fn    TECHNOSOFTWARE_API std::string& DoubleToStr(std::string& str, double value, int precision = -1, int width = 0, char thSep = 0, char decSep = 0);
         *
         * @brief    Converts a double value, assigns it to the supplied string and returns the reference.
         *             This function calls doubleToStr(char*, int, double, int, int) and formats the result
         *             according to precision (total number of digits after the decimal point, -1 means
         *             ignore precision argument)
         *             and width (total length of formatted string).
         *
         * @param [in,out]    str    The string.
         * @param    value           The value.
         * @param    precision      (Optional) the precision.
         * @param    width           (Optional) the width.
         * @param    thSep           (Optional) the th separator.
         * @param    decSep           (Optional) the decrement separator.
         *
         * @return    A reference to a std::string.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API std::string& DoubleToStr(std::string& str,
            double value,
            int precision = -1,
            int width = 0,
            char thSep = 0,
            char decSep = 0);

        /**
         * @fn    TECHNOSOFTWARE_API std::string& DoubleToFixedStr(std::string& str, double value, int precision = -1, int width = 0, char thSep = 0, char decSep = 0);
         *
         * @brief    Converts a double value, assigns it to the supplied string and returns the reference.
         *             This function calls doubleToFixedStr(char*, int, double, int) and formats the result
         *             according to precision (total number of digits after the decimal point) and width
         *             (total length of formatted string).
         *
         * @param [in,out]    str    The string.
         * @param    value           The value.
         * @param    precision      (Optional) the precision.
         * @param    width           (Optional) the width.
         * @param    thSep           (Optional) the th separator.
         * @param    decSep           (Optional) the decrement separator.
         *
         * @return    A reference to a std::string.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API std::string& DoubleToFixedStr(std::string& str,
            double value,
            int precision = -1,
            int width = 0,
            char thSep = 0,
            char decSep = 0);

        /**
         * @fn    TECHNOSOFTWARE_API float StrToFloat(const char* str);
         *
         * @brief    Converts the string of characters into single-precision floating point number.
         *             Function uses double_convesrion::DoubleToStringConverter to do the conversion.
         *
         * @param    str    The string.
         *
         * @return    str as a float.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API float StrToFloat(const char* str);

        /**
         * @fn    TECHNOSOFTWARE_API bool StrToFloat(const std::string&, float& result, char decSep = '.', char thSep = ',');
         *
         * @brief    Converts the string of characters into single-precision floating point number. The
         *             conversion result is assigned to the result parameter. If decimal separator and/or
         *             thousand separator are different from defaults, they should be supplied to ensure
         *             proper conversion.
         *             
         *             Returns true if succesful, false otherwise.
         *
         * @param [in,out]    result    The result.
         * @param    decSep              (Optional) the decrement separator.
         * @param    thSep              (Optional) the th separator.
         *
         * @return    The given data converted to a bool.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API bool StrToFloat(const std::string&, float& result, char decSep = '.', char thSep = ',');

        /**
         * @fn    TECHNOSOFTWARE_API double StrToDouble(const char* str);
         *
         * @brief    Converts the string of characters into double-precision floating point number.
         *
         * @param    str    The string.
         *
         * @return    str as a double.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API double StrToDouble(const char* str);

        /**
         * @fn    TECHNOSOFTWARE_API bool StrToDouble(const std::string& str, double& result, char decSep = '.', char thSep = ',');
         *
         * @brief    Converts the string of characters into double-precision floating point number. The
         *             conversion result is assigned to the result parameter. If decimal separator and/or
         *             thousand separator are different from defaults, they should be supplied to ensure
         *             proper conversion.
         *             
         *             Returns true if succesful, false otherwise.
         *
         * @param    str                  The string.
         * @param [in,out]    result    The result.
         * @param    decSep              (Optional) the decrement separator.
         * @param    thSep              (Optional) the th separator.
         *
         * @return    The given data converted to a bool.
         *
         * @ingroup BaseCore
         */

        TECHNOSOFTWARE_API bool StrToDouble(const std::string& str, double& result, char decSep = '.', char thSep = ',');
    }
}

#endif /* TECHNOSOFTWARE_NUMERICSTRING_H */
