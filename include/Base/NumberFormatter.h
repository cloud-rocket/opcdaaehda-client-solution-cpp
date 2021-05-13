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

#ifndef TECHNOSOFTWARE_NUMBERFORMATTER_H
#define TECHNOSOFTWARE_NUMBERFORMATTER_H

#include "Base/Base.h"
#include "Base/NumericString.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   NumberFormatter
         *
         * @brief   The NumberFormatter class provides static methods for formatting numeric values into
         *          strings.
         *          
         *          There are two kind of static member functions:
         *             * format* functions return a std::string containing
         *               the formatted value.
         *             * append* functions append the formatted value to
         *               an existing string.
         *
         * @ingroup BaseCore
         */

        class TECHNOSOFTWARE_API NumberFormatter
        {
        public:
            enum BoolFormat
            {
                FMT_TRUE_FALSE,
                FMT_YES_NO,
                FMT_ON_OFF
            };

            static const unsigned NF_MAX_INT_STRING_LEN = 32; // increase for 64-bit binary formatting support
            static const unsigned NF_MAX_FLT_STRING_LEN = TECHNOSOFTWARE_MAX_FLT_STRING_LEN;

            /**
             * @fn  static std::string NumberFormatter::Format(int value);
             *
             * @brief   Formats an integer value in decimal notation.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(int value);

            /**
             * @fn  static std::string NumberFormatter::Format(int value, int width);
             *
             * @brief   Formats an integer value in decimal notation, right justified in a field having at
             *          least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted value.
             */

            static std::string Format(int value, int width);

            /**
             * @fn  static std::string NumberFormatter::Format0(int value, int width);
             *
             * @brief   Formats an integer value in decimal notation, right justified and zero-padded in a
             *          field having at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted 0.
             */

            static std::string Format0(int value, int width);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(int value, bool prefix = false);
             *
             * @brief   Formats an int value in hexadecimal notation. If prefix is true, "0x" prefix is
             *          prepended to the resulting string. The value is treated as unsigned.
             *
             * @param   value   The value.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(int value, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(int value, int width, bool prefix = false);
             *
             * @brief   Formats a int value in hexadecimal notation, right justified and zero-padded in a
             *          field having at least the specified width. If prefix is true, "0x" prefix is
             *          prepended to the resulting string. The value is treated as unsigned.
             *
             * @param   value   The value.
             * @param   width   The width.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(int value, int width, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::Format(unsigned value);
             *
             * @brief   Formats an unsigned int value in decimal notation.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(unsigned value);

            /**
             * @fn  static std::string NumberFormatter::Format(unsigned value, int width);
             *
             * @brief   Formats an unsigned long int in decimal notation, right justified in a field having
             *          at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted value.
             */

            static std::string Format(unsigned value, int width);

            /**
             * @fn  static std::string NumberFormatter::Format0(unsigned int value, int width);
             *
             * @brief   Formats an unsigned int value in decimal notation, right justified and zero-padded in
             *          a field having at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted 0.
             */

            static std::string Format0(unsigned int value, int width);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(unsigned value, bool prefix = false);
             *
             * @brief   Formats an unsigned int value in hexadecimal notation. If prefix is true, "0x" prefix
             *          is prepended to the resulting string.
             *
             * @param   value   The value.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(unsigned value, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(unsigned value, int width, bool prefix = false);
             *
             * @brief   Formats a int value in hexadecimal notation, right justified and zero-padded in a
             *          field having at least the specified width. If prefix is true, "0x" prefix is
             *          prepended to the resulting string.
             *
             * @param   value   The value.
             * @param   width   The width.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(unsigned value, int width, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::Format(long value);
             *
             * @brief   Formats a long value in decimal notation.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(long value);

            /**
             * @fn  static std::string NumberFormatter::Format(long value, int width);
             *
             * @brief   Formats a long value in decimal notation, right justified in a field having at least
             *          the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted value.
             */

            static std::string Format(long value, int width);

            /**
             * @fn  static std::string NumberFormatter::Format0(long value, int width);
             *
             * @brief   Formats a long value in decimal notation, right justified and zero-padded in a field
             *          having at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted 0.
             */

            static std::string Format0(long value, int width);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(long value, bool prefix = false);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation. If prefix is true, "0x"
             *          prefix is prepended to the resulting string. The value is treated as unsigned.
             *
             * @param   value   The value.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(long value, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(long value, int width, bool prefix = false);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width. If prefix is true, "0x" prefix
             *          is prepended to the resulting string. The value is treated as unsigned.
             *
             * @param   value   The value.
             * @param   width   The width.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(long value, int width, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::Format(unsigned long value);
             *
             * @brief   Formats an unsigned long value in decimal notation.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(unsigned long value);

            /**
             * @fn  static std::string NumberFormatter::Format(unsigned long value, int width);
             *
             * @brief   Formats an unsigned long value in decimal notation, right justified in a field having
             *          at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted value.
             */

            static std::string Format(unsigned long value, int width);

            /**
             * @fn  static std::string NumberFormatter::Format0(unsigned long value, int width);
             *
             * @brief   Formats an unsigned long value in decimal notation, right justified and zero-padded
             *          in a field having at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted 0.
             */

            static std::string Format0(unsigned long value, int width);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(unsigned long value, bool prefix = false);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation. If prefix is true, "0x"
             *          prefix is prepended to the resulting string.
             *
             * @param   value   The value.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(unsigned long value, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(unsigned long value, int width, bool prefix = false);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width. If prefix is true, "0x" prefix
             *          is prepended to the resulting string.
             *
             * @param   value   The value.
             * @param   width   The width.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(unsigned long value, int width, bool prefix = false);

#if defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)

            /**
             * @fn  static std::string NumberFormatter::Format(Int64 value);
             *
             * @brief   Formats a 64-bit integer value in decimal notation.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(Int64 value);

            /**
             * @fn  static std::string NumberFormatter::Format(Int64 value, int width);
             *
             * @brief   Formats a 64-bit integer value in decimal notation, right justified in a field having
             *          at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted value.
             */

            static std::string Format(Int64 value, int width);

            /**
             * @fn  static std::string NumberFormatter::Format0(Int64 value, int width);
             *
             * @brief   Formats a 64-bit integer value in decimal notation, right justified and zero-padded
             *          in a field having at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted 0.
             */

            static std::string Format0(Int64 value, int width);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(Int64 value, bool prefix = false);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation. If prefix is true, "0x"
             *          prefix is prepended to the resulting string. The value is treated as unsigned.
             *
             * @param   value   The value.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(Int64 value, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(Int64 value, int width, bool prefix = false);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width. The value is treated as
             *          unsigned. If prefix is true, "0x" prefix is prepended to the resulting string.
             *
             * @param   value   The value.
             * @param   width   The width.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(Int64 value, int width, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::Format(UInt64 value);
             *
             * @brief   Formats an unsigned 64-bit integer value in decimal notation.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(UInt64 value);

            /**
             * @fn  static std::string NumberFormatter::Format(UInt64 value, int width);
             *
             * @brief   Formats an unsigned 64-bit integer value in decimal notation, right justified in a
             *          field having at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted value.
             */

            static std::string Format(UInt64 value, int width);

            /**
             * @fn  static std::string NumberFormatter::Format0(UInt64 value, int width);
             *
             * @brief   Formats an unsigned 64-bit integer value in decimal notation, right justified and
             *          zero-padded in a field having at least the specified width.
             *
             * @param   value   The value.
             * @param   width   The width.
             *
             * @return  The formatted value.
             */

            static std::string Format0(UInt64 value, int width);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(UInt64 value, bool prefix = false);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation. If prefix is true, "0x"
             *          prefix is prepended to the resulting string.
             *
             * @param   value   The value.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(UInt64 value, bool prefix = false);

            /**
             * @fn  static std::string NumberFormatter::FormatHex(UInt64 value, int width, bool prefix = false);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width. If prefix is true, "0x" prefix
             *          is prepended to the resulting string.
             *
             * @param   value   The value.
             * @param   width   The width.
             * @param   prefix  (Optional) true to prefix.
             *
             * @return  The formatted hexadecimal.
             */

            static std::string FormatHex(UInt64 value, int width, bool prefix = false);

#endif // defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)

            /**
             * @fn  static std::string NumberFormatter::Format(float value);
             *
             * @brief   Formats a float value in decimal floating-point notation, according to std::printf's
             *          %g format with a precision of 8 fractional digits.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(float value);

            /**
             * @fn  static std::string NumberFormatter::Format(float value, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, according to std::printf's
             *          %f format with the given precision.
             *
             * @param   value       The value.
             * @param   precision   The precision.
             *
             * @return  The formatted value.
             */

            static std::string Format(float value, int precision);

            /**
             * @fn  static std::string NumberFormatter::Format(float value, int width, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, right justified in a field
             *          of the specified width, with the number of fractional digits given in precision.
             *
             * @param   value       The value.
             * @param   width       The width.
             * @param   precision   The precision.
             *
             * @return  The formatted value.
             */

            static std::string Format(float value, int width, int precision);

            /**
             * @fn  static std::string NumberFormatter::Format(double value);
             *
             * @brief   Formats a double value in decimal floating-point notation, according to std::printf's
             *          %g format with a precision of 16 fractional digits.
             *
             * @param   value   The value.
             *
             * @return  The formatted value.
             */

            static std::string Format(double value);

            /**
             * @fn  static std::string NumberFormatter::Format(double value, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, according to std::printf's
             *          %f format with the given precision.
             *
             * @param   value       The value.
             * @param   precision   The precision.
             *
             * @return  The formatted value.
             */

            static std::string Format(double value, int precision);

            /**
             * @fn  static std::string NumberFormatter::Format(double value, int width, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, right justified in a field
             *          of the specified width, with the number of fractional digits given in precision.
             *
             * @param   value       The value.
             * @param   width       The width.
             * @param   precision   The precision.
             *
             * @return  The formatted value.
             */

            static std::string Format(double value, int width, int precision);

            /**
             * @fn  static std::string NumberFormatter::Format(const void* ptr);
             *
             * @brief   Formats a pointer in an eight (32-bit architectures) or sixteen (64-bit
             *          architectures) characters wide field in hexadecimal notation.
             *
             * @param   ptr The pointer.
             *
             * @return  The formatted value.
             */

            static std::string Format(const void* ptr);

            /**
             * @fn  static std::string NumberFormatter::Format(bool value, BoolFormat format = FMT_TRUE_FALSE);
             *
             * @brief   Formats a bool value in decimal/text notation, according to format parameter.
             *
             * @param   value   true to value.
             * @param   format  (Optional) describes the format to use.
             *
             * @return  The formatted value.
             */

            static std::string Format(bool value, BoolFormat format = FMT_TRUE_FALSE);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, int value);
             *
             * @brief   Formats an integer value in decimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, int value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, int value, int width);
             *
             * @brief   Formats an integer value in decimal notation, right justified in a field having at
             *          least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append(std::string& str, int value, int width);

            /**
             * @fn  static void NumberFormatter::Append0(std::string& str, int value, int width);
             *
             * @brief   Formats an integer value in decimal notation, right justified and zero-padded in a
             *          field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append0(std::string& str, int value, int width);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, int value);
             *
             * @brief   Formats an int value in hexadecimal notation. The value is treated as unsigned.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void AppendHex(std::string& str, int value);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, int value, int width);
             *
             * @brief   Formats a int value in hexadecimal notation, right justified and zero-padded in a
             *          field having at least the specified width. The value is treated as unsigned.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void AppendHex(std::string& str, int value, int width);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, unsigned value);
             *
             * @brief   Formats an unsigned int value in decimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, unsigned value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, unsigned value, int width);
             *
             * @brief   Formats an unsigned long int in decimal notation, right justified in a field having
             *          at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append(std::string& str, unsigned value, int width);

            /**
             * @fn  static void NumberFormatter::Append0(std::string& str, unsigned int value, int width);
             *
             * @brief   Formats an unsigned int value in decimal notation, right justified and zero-padded in
             *          a field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append0(std::string& str, unsigned int value, int width);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, unsigned value);
             *
             * @brief   Formats an unsigned int value in hexadecimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void AppendHex(std::string& str, unsigned value);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, unsigned value, int width);
             *
             * @brief   Formats a int value in hexadecimal notation, right justified and zero-padded in a
             *          field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void AppendHex(std::string& str, unsigned value, int width);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, long value);
             *
             * @brief   Formats a long value in decimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, long value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, long value, int width);
             *
             * @brief   Formats a long value in decimal notation, right justified in a field having at least
             *          the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append(std::string& str, long value, int width);

            /**
             * @fn  static void NumberFormatter::Append0(std::string& str, long value, int width);
             *
             * @brief   Formats a long value in decimal notation, right justified and zero-padded in a field
             *          having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append0(std::string& str, long value, int width);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, long value);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation. The value is treated as
             *          unsigned.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void AppendHex(std::string& str, long value);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, long value, int width);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width. The value is treated as
             *          unsigned.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void AppendHex(std::string& str, long value, int width);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, unsigned long value);
             *
             * @brief   Formats an unsigned long value in decimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, unsigned long value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, unsigned long value, int width);
             *
             * @brief   Formats an unsigned long value in decimal notation, right justified in a field having
             *          at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append(std::string& str, unsigned long value, int width);

            /**
             * @fn  static void NumberFormatter::Append0(std::string& str, unsigned long value, int width);
             *
             * @brief   Formats an unsigned long value in decimal notation, right justified and zero-padded
             *          in a field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append0(std::string& str, unsigned long value, int width);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, unsigned long value);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void AppendHex(std::string& str, unsigned long value);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, unsigned long value, int width);
             *
             * @brief   Formats an unsigned long value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void AppendHex(std::string& str, unsigned long value, int width);

#if defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, Int64 value);
             *
             * @brief   Formats a 64-bit integer value in decimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, Int64 value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, Int64 value, int width);
             *
             * @brief   Formats a 64-bit integer value in decimal notation, right justified in a field having
             *          at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append(std::string& str, Int64 value, int width);

            /**
             * @fn  static void NumberFormatter::Append0(std::string& str, Int64 value, int width);
             *
             * @brief   Formats a 64-bit integer value in decimal notation, right justified and zero-padded
             *          in a field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append0(std::string& str, Int64 value, int width);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, Int64 value);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation. The value is treated as
             *          unsigned.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void AppendHex(std::string& str, Int64 value);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, Int64 value, int width);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width. The value is treated as
             *          unsigned.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void AppendHex(std::string& str, Int64 value, int width);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, UInt64 value);
             *
             * @brief   Formats an unsigned 64-bit integer value in decimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, UInt64 value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, UInt64 value, int width);
             *
             * @brief   Formats an unsigned 64-bit integer value in decimal notation, right justified in a
             *          field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append(std::string& str, UInt64 value, int width);

            /**
             * @fn  static void NumberFormatter::Append0(std::string& str, UInt64 value, int width);
             *
             * @brief   Formats an unsigned 64-bit integer value in decimal notation, right justified and
             *          zero-padded in a field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void Append0(std::string& str, UInt64 value, int width);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, UInt64 value);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void AppendHex(std::string& str, UInt64 value);

            /**
             * @fn  static void NumberFormatter::AppendHex(std::string& str, UInt64 value, int width);
             *
             * @brief   Formats a 64-bit integer value in hexadecimal notation, right justified and zero-
             *          padded in a field having at least the specified width.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             */

            static void AppendHex(std::string& str, UInt64 value, int width);

#endif // defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, float value);
             *
             * @brief   Formats a float value in decimal floating-point notation, according to std::printf's
             *          %g format with a precision of 8 fractional digits.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, float value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, float value, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, according to std::printf's
             *          %f format with the given precision.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   precision   The precision.
             */

            static void Append(std::string& str, float value, int precision);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, float value, int width, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, right justified in a field
             *          of the specified width, with the number of fractional digits given in precision.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             * @param   precision   The precision.
             */

            static void Append(std::string& str, float value, int width, int precision);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, double value);
             *
             * @brief   Formats a double value in decimal floating-point notation, according to std::printf's
             *          %g format with a precision of 16 fractional digits.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             */

            static void Append(std::string& str, double value);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, double value, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, according to std::printf's
             *          %f format with the given precision.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   precision   The precision.
             */

            static void Append(std::string& str, double value, int precision);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, double value, int width, int precision);
             *
             * @brief   Formats a double value in decimal floating-point notation, right justified in a field
             *          of the specified width, with the number of fractional digits given in precision.
             *
             * @param [in,out]  str The string.
             * @param   value       The value.
             * @param   width       The width.
             * @param   precision   The precision.
             */

            static void Append(std::string& str, double value, int width, int precision);

            /**
             * @fn  static void NumberFormatter::Append(std::string& str, const void* ptr);
             *
             * @brief   Formats a pointer in an eight (32-bit architectures) or sixteen (64-bit
             *          architectures) characters wide field in hexadecimal notation.
             *
             * @param [in,out]  str The string.
             * @param   ptr         The pointer.
             */

            static void Append(std::string& str, const void* ptr);

        private:
        };


        //
        // inlines
        //

        inline std::string NumberFormatter::Format(int value)
        {
            std::string result;
            IntToStr(value, 10, result);
            return result;
        }


        inline std::string NumberFormatter::Format(int value, int width)
        {
            std::string result;
            IntToStr(value, 10, result, false, width, ' ');
            return result;
        }


        inline std::string NumberFormatter::Format0(int value, int width)
        {
            std::string result;
            IntToStr(value, 10, result, false, width, '0');
            return result;
        }


        inline std::string NumberFormatter::FormatHex(int value, bool prefix)
        {
            std::string result;
            UIntToStr(static_cast<unsigned int>(value), 0x10, result, prefix);
            return result;
        }


        inline std::string NumberFormatter::FormatHex(int value, int width, bool prefix)
        {
            std::string result;
            UIntToStr(static_cast<unsigned int>(value), 0x10, result, prefix, width, '0');
            return result;
        }


        inline std::string NumberFormatter::Format(unsigned value)
        {
            std::string result;
            UIntToStr(value, 10, result);
            return result;
        }


        inline std::string NumberFormatter::Format(unsigned value, int width)
        {
            std::string result;
            UIntToStr(value, 10, result, false, width, ' ');
            return result;
        }


        inline std::string NumberFormatter::Format0(unsigned int value, int width)
        {
            std::string result;
            UIntToStr(value, 10, result, false, width, '0');
            return result;
        }


        inline std::string NumberFormatter::FormatHex(unsigned value, bool prefix)
        {
            std::string result;
            UIntToStr(value, 0x10, result, prefix);
            return result;
        }


        inline std::string NumberFormatter::FormatHex(unsigned value, int width, bool prefix)
        {
            std::string result;
            UIntToStr(value, 0x10, result, prefix, width, '0');
            return result;
        }


        inline std::string NumberFormatter::Format(long value)
        {
            std::string result;
            IntToStr(value, 10, result);
            return result;
        }


        inline std::string NumberFormatter::Format(long value, int width)
        {
            std::string result;
            IntToStr(value, 10, result, false, width, ' ');
            return result;
        }


        inline std::string NumberFormatter::Format0(long value, int width)
        {
            std::string result;
            IntToStr(value, 10, result, false, width, '0');
            return result;
        }


        inline std::string NumberFormatter::FormatHex(long value, bool prefix)
        {
            std::string result;
            UIntToStr(static_cast<unsigned long>(value), 0x10, result, prefix);
            return result;
        }


        inline std::string NumberFormatter::FormatHex(long value, int width, bool prefix)
        {
            std::string result;
            UIntToStr(static_cast<unsigned long>(value), 0x10, result, prefix, width, '0');
            return result;
        }


        inline std::string NumberFormatter::Format(unsigned long value)
        {
            std::string result;
            UIntToStr(value, 10, result);
            return result;
        }


        inline std::string NumberFormatter::Format(unsigned long value, int width)
        {
            std::string result;
            UIntToStr(value, 10, result, false, width, ' ');
            return result;
        }


        inline std::string NumberFormatter::Format0(unsigned long value, int width)
        {
            std::string result;
            UIntToStr(value, 10, result, false, width, '0');
            return result;
        }


        inline std::string NumberFormatter::FormatHex(unsigned long value, bool prefix)
        {
            std::string result;
            UIntToStr(value, 0x10, result, prefix);
            return result;
        }


        inline std::string NumberFormatter::FormatHex(unsigned long value, int width, bool prefix)
        {
            std::string result;
            UIntToStr(value, 0x10, result, prefix, width, '0');
            return result;
        }


#if defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)


        inline std::string NumberFormatter::Format(Int64 value)
        {
            std::string result;
            IntToStr(value, 10, result);
            return result;
        }


        inline std::string NumberFormatter::Format(Int64 value, int width)
        {
            std::string result;
            IntToStr(value, 10, result, false, width, ' ');
            return result;
        }


        inline std::string NumberFormatter::Format0(Int64 value, int width)
        {
            std::string result;
            IntToStr(value, 10, result, false, width, '0');
            return result;
        }


        inline std::string NumberFormatter::FormatHex(Int64 value, bool prefix)
        {
            std::string result;
            UIntToStr(static_cast<UInt64>(value), 0x10, result, prefix);
            return result;
        }


        inline std::string NumberFormatter::FormatHex(Int64 value, int width, bool prefix)
        {
            std::string result;
            UIntToStr(static_cast<UInt64>(value), 0x10, result, prefix, width, '0');
            return result;
        }


        inline std::string NumberFormatter::Format(UInt64 value)
        {
            std::string result;
            UIntToStr(value, 10, result);
            return result;
        }


        inline std::string NumberFormatter::Format(UInt64 value, int width)
        {
            std::string result;
            UIntToStr(value, 10, result, false, width, ' ');
            return result;
        }


        inline std::string NumberFormatter::Format0(UInt64 value, int width)
        {
            std::string result;
            UIntToStr(value, 10, result, false, width, '0');
            return result;
        }


        inline std::string NumberFormatter::FormatHex(UInt64 value, bool prefix)
        {
            std::string result;
            UIntToStr(value, 0x10, result, prefix);
            return result;
        }


        inline std::string NumberFormatter::FormatHex(UInt64 value, int width, bool prefix)
        {
            std::string result;
            UIntToStr(value, 0x10, result, prefix, width, '0');
            return result;
        }


#endif // defined(TECHNOSOFTWARE_HAVE_INT64) && !defined(TECHNOSOFTWARE_LONG_IS_64_BIT)


        inline std::string NumberFormatter::Format(float value)
        {
            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            FloatToStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value);
            return std::string(buffer);
        }


        inline std::string NumberFormatter::Format(float value, int precision)
        {
            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            FloatToFixedStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value, precision);
            return std::string(buffer);
        }


        inline std::string NumberFormatter::Format(float value, int width, int precision)
        {
            std::string result;
            FloatToFixedStr(result, value, precision, width);
            return result;
        }


        inline std::string NumberFormatter::Format(double value)
        {
            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            DoubleToStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value);
            return std::string(buffer);
        }


        inline std::string NumberFormatter::Format(double value, int precision)
        {
            char buffer[TECHNOSOFTWARE_MAX_FLT_STRING_LEN];
            DoubleToFixedStr(buffer, TECHNOSOFTWARE_MAX_FLT_STRING_LEN, value, precision);
            return std::string(buffer);
        }


        inline std::string NumberFormatter::Format(double value, int width, int precision)
        {
            std::string result;
            DoubleToFixedStr(result, value, precision, width);
            return result;
        }


        inline std::string NumberFormatter::Format(const void* ptr)
        {
            std::string result;
            Append(result, ptr);
            return result;
        }
    }
}

#endif /* TECHNOSOFTWARE_NUMBERFORMATTER_H */
