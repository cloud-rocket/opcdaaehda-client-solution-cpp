/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the DateTimeParser class.
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

#ifndef TECHNOSOFTWARE_DATETIMEPARSER_H
#define TECHNOSOFTWARE_DATETIMEPARSER_H

#include "Base/Base.h"
#include "Base/DateTime.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   DateTimeParser
         *
         * @brief   This class provides a method for parsing dates and times from strings. All parsing
         *          methods do their best to parse a meaningful result, even from malformed input strings.
         *          
         *          The returned DateTime will always contain a time in the same timezone as the time in
         *          the string. Call DateTime::makeUTC()
         *          with the timeZoneDifferential returned by Parse() to convert the DateTime to UTC.
         *          
         *          Note: When parsing a time in 12-hour (AM/PM) format, the hour (%h) must be parsed
         *          before the AM/PM designator (%a, %A), otherwise the AM/PM designator will be ignored.
         *          
         *          See the DateTimeFormatter class for a list of supported format specifiers. In
         *          addition to the format specifiers supported by DateTimeFormatter, an additional
         *          specifier is supported: %r will parse a year given by either two or four digits.
         *          Years 69-00 are interpreted in the 20th century (1969-2000), years 01-68 in the 21th
         *          century (2001-2068).
         *          
         *          Note that in the current implementation all characters other than format specifiers
         *          in the format string are ignored/not matched against the date/time string. This may
         *          lead to non-error results even with nonsense input strings. This may change in a
         *          future version to a more strict behavior. If more strict format validation of
         *          date/time strings is required, a regular expression could be used for initial
         *          validation, before passing the string to DateTimeParser.
         *
         * @ingroup BaseDateTime
         */

        class TECHNOSOFTWARE_API DateTimeParser
        {
        public:

            /**
             * @fn  static void DateTimeParser::Parse(const std::string& fmt, const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
             *
             * @brief   Parses a date and time in the given format from the given string. Throws a
             *          SyntaxException if the string cannot be successfully parsed. Please see
             *          DateTimeFormatter::format() for a description of the format string. Class
             *          DateTimeFormat defines format strings for various standard date/time formats.
             *
             * @param   fmt                             Describes the format to use.
             * @param   str                             The string.
             * @param [in,out]  dateTime                The date time.
             * @param [in,out]  timeZoneDifferential    The time zone differential.
             */

            static void Parse(const std::string& fmt, const std::string& str, DateTime& dateTime, int& timeZoneDifferential);

            /**
             * @fn  static DateTime DateTimeParser::Parse(const std::string& fmt, const std::string& str, int& timeZoneDifferential);
             *
             * @brief   Parses a date and time in the given format from the given string. Throws a
             *          SyntaxException if the string cannot be successfully parsed. Please see
             *          DateTimeFormatter::format() for a description of the format string. Class
             *          DateTimeFormat defines format strings for various standard date/time formats.
             *
             * @param   fmt                             Describes the format to use.
             * @param   str                             The string.
             * @param [in,out]  timeZoneDifferential    The time zone differential.
             *
             * @return  A DateTime.
             */

            static DateTime Parse(const std::string& fmt, const std::string& str, int& timeZoneDifferential);

            /**
             * @fn  static bool DateTimeParser::TryParse(const std::string& fmt, const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
             *
             * @brief   Parses a date and time in the given format from the given string. Returns true if the
             *          string has been successfully parsed, false otherwise. Please see
             *          DateTimeFormatter::format() for a description of the format string. Class
             *          DateTimeFormat defines format strings for various standard date/time formats.
             *
             * @param   fmt                             Describes the format to use.
             * @param   str                             The string.
             * @param [in,out]  dateTime                The date time.
             * @param [in,out]  timeZoneDifferential    The time zone differential.
             *
             * @return  true if it succeeds, false if it fails.
             */

            static bool TryParse(const std::string& fmt, const std::string& str, DateTime& dateTime, int& timeZoneDifferential);

            /**
             * @fn  static void DateTimeParser::Parse(const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
             *
             * @brief   Parses a date and time from the given dateTime string. Before parsing, the method
             *          examines the dateTime string for a known date/time format. Throws a SyntaxException
             *          if the string cannot be successfully parsed. Please see DateTimeFormatter::format()
             *          for a description of the format string. Class DateTimeFormat defines format strings
             *          for various standard date/time formats.
             *
             * @param   str                             The string.
             * @param [in,out]  dateTime                The date time.
             * @param [in,out]  timeZoneDifferential    The time zone differential.
             */

            static void Parse(const std::string& str, DateTime& dateTime, int& timeZoneDifferential);

            /**
             * @fn  static DateTime DateTimeParser::Parse(const std::string& str, int& timeZoneDifferential);
             *
             * @brief   Parses a date and time from the given dateTime string. Before parsing, the method
             *          examines the dateTime string for a known date/time format. Please see
             *          DateTimeFormatter::format() for a description of the format string. Class
             *          DateTimeFormat defines format strings for various standard date/time formats.
             *
             * @param   str                             The string.
             * @param [in,out]  timeZoneDifferential    The time zone differential.
             *
             * @return  A DateTime.
             */

            static DateTime Parse(const std::string& str, int& timeZoneDifferential);

            /**
             * @fn  static bool DateTimeParser::TryParse(const std::string& str, DateTime& dateTime, int& timeZoneDifferential);
             *
             * @brief   Parses a date and time from the given dateTime string. Before parsing, the method
             *          examines the dateTime string for a known date/time format. Please see
             *          DateTimeFormatter::format() for a description of the format string. Class
             *          DateTimeFormat defines format strings for various standard date/time formats.
             *
             * @param   str                             The string.
             * @param [in,out]  dateTime                The date time.
             * @param [in,out]  timeZoneDifferential    The time zone differential.
             *
             * @return  true if it succeeds, false if it fails.
             */

            static bool TryParse(const std::string& str, DateTime& dateTime, int& timeZoneDifferential);

            /**
             * @fn  static int DateTimeParser::ParseMonth(std::string::const_iterator& it, const std::string::const_iterator& end);
             *
             * @brief   Tries to interpret the given range as a month name. The range must be at least three
             *          characters long. Returns the month number (1 .. 12) if the month name is valid.
             *          Otherwise throws a SyntaxException.
             *
             * @param   it  The iterator.
             * @param   end The end.
             *
             * @return  An int.
             */

            static int ParseMonth(std::string::const_iterator& it, const std::string::const_iterator& end);

            /**
             * @fn  static int DateTimeParser::ParseDayOfWeek(std::string::const_iterator& it, const std::string::const_iterator& end);
             *
             * @brief   Tries to interpret the given range as a weekday name. The range must be at least
             *          three characters long. Returns the weekday number (0 .. 6, where 0 = Synday, 1 =
             *          Monday, etc.) if the weekday name is valid. Otherwise throws a SyntaxException.
             *
             * @param   it  The iterator.
             * @param   end The end.
             *
             * @return  An int.
             */

            static int ParseDayOfWeek(std::string::const_iterator& it, const std::string::const_iterator& end);

        protected:

            /**
             * @fn  static int DateTimeParser::ParseTZD(std::string::const_iterator& it, const std::string::const_iterator& end);
             *
             * @brief   Parse tzd.
             *
             * @param   it  The iterator.
             * @param   end The end.
             *
             * @return  An int.
             */

            static int ParseTZD(std::string::const_iterator& it, const std::string::const_iterator& end);

            /**
             * @fn  static int DateTimeParser::ParseAMPM(std::string::const_iterator& it, const std::string::const_iterator& end, int hour);
             *
             * @brief   Parse a mpm.
             *
             * @param   it      The iterator.
             * @param   end     The end.
             * @param   hour    The hour.
             *
             * @return  An int.
             */

            static int ParseAMPM(std::string::const_iterator& it, const std::string::const_iterator& end, int hour);
        };
    }
} 

#endif /* TECHNOSOFTWARE_DATETIMEPARSER_H */
