/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the DateTimeFormatter class.
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

#ifndef TECHNOSOFTWARE_DATETIMEFORMATTER_H
#define TECHNOSOFTWARE_DATETIMEFORMATTER_H

#include "Base/Base.h"
#include "Base/DateTime.h"
#include "Base/LocalDateTime.h"

namespace Technosoftware
{
    namespace Base
    {
        class Timestamp;
        class Timespan;

        /**
         * @class    DateTimeFormatter
         *
         * @brief    This class converts dates and times into strings, supporting a  
         *             variety of standard and custom formats.
         *             
         *             There are two kind of static member functions:
         *                * format* functions return a std::string containing
         *                  the formatted value.
         *                * append* functions append the formatted value to
         *                  an existing string.
         *
         * @ingroup    BaseDateTime
         */

        class TECHNOSOFTWARE_API DateTimeFormatter
        {
        public:
            enum
            {
                UTC = 0xFFFF /// Special value for timeZoneDifferential denoting UTC. 
            };

            /**
             * @fn    static std::string DateTimeFormatter::Format(const Timestamp& timestamp, const std::string& fmt, int timeZoneDifferential = UTC);
             *
             * @brief    Formats the given timestamp according to the given format. The format string is used
             *             as a template to format the date and is copied character by character except for the
             *             following special characters, which are replaced by the corresponding value.
             *             
             *               * %w - abbreviated weekday (Mon, Tue, ...)
             *               * %W - full weekday (Monday, Tuesday, ...)
             *               * %b - abbreviated month (Jan, Feb, ...)
             *               * %B - full month (January, February, ...)
             *               * %d - zero-padded day of month (01 .. 31)
             *               * %e - day of month (1 .. 31)
             *               * %f - space-padded day of month ( 1 .. 31)
             *               * %m - zero-padded month (01 .. 12)
             *               * %n - month (1 .. 12)
             *               * %o - space-padded month ( 1 .. 12)
             *               * %y - year without century (70)
             *               * %Y - year with century (1970)
             *               * %H - hour (00 .. 23)
             *               * %h - hour (00 .. 12)
             *               * %a - am/pm
             *               * %A - AM/PM
             *               * %M - minute (00 .. 59)
             *               * %S - second (00 .. 59)
             *               * %s - seconds and microseconds (equivalent to %S.%F)
             *               * %i - millisecond (000 .. 999)
             *               * %c - centisecond (0 .. 9)
             *               * %F - fractional seconds/microseconds (000000 - 999999)
             *               * %z - time zone differential in ISO 8601 format (Z or +NN.NN)
             *               * %Z - time zone differential in RFC format (GMT or +NNNN)
             *               * %% - percent sign
             *             
             *             Class DateTimeFormat defines format strings for various standard date/time formats.
             *
             * @param    timestamp                The timestamp.
             * @param    fmt                        Describes the format to use.
             * @param    timeZoneDifferential    (Optional) the time zone differential.
             *
             * @return    The formatted value.
             */

            static std::string Format(const Timestamp& timestamp, const std::string& fmt, int timeZoneDifferential = UTC);

            /**
             * @fn    static std::string DateTimeFormatter::Format(const DateTime& dateTime, const std::string& fmt, int timeZoneDifferential = UTC);
             *
             * @brief    Formats the given date and time according to the given format. See format(const
             *             Timestamp&amp;, const std::string&amp;, int) for more information.
             *
             * @param    dateTime                The date time.
             * @param    fmt                        Describes the format to use.
             * @param    timeZoneDifferential    (Optional) the time zone differential.
             *
             * @return    The formatted value.
             */

            static std::string Format(const DateTime& dateTime, const std::string& fmt, int timeZoneDifferential = UTC);

            /**
             * @fn    static std::string DateTimeFormatter::Format(const LocalDateTime& dateTime, const std::string& fmt);
             *
             * @brief    Formats the given local date and time according to the given format. See format(const
             *             Timestamp&amp;, const std::string&amp;, int) for more information.
             *
             * @param    dateTime    The date time.
             * @param    fmt            Describes the format to use.
             *
             * @return    The formatted value.
             */

            static std::string Format(const LocalDateTime& dateTime, const std::string& fmt);

            /**
             * @fn    static std::string DateTimeFormatter::Format(const Timespan& timespan, const std::string& fmt = "%dd %H:%M:%S.%i");
             *
             * @brief    Formats the given timespan according to the given format. The format string is used
             *             as a template to format the date and is copied character by character except for the
             *             following special characters, which are replaced by the corresponding value.
             *             
             *               * %d - days
             *               * %H - hours     (00 .. 23)
             *               * %h - total hours (0 .. n)
             *               * %M - minutes (00 .. 59)
             *               * %m - total minutes (0 .. n)
             *               * %S - seconds (00 .. 59)
             *               * %s - total seconds (0 .. n)
             *               * %i - milliseconds (000 .. 999)
             *               * %c - centisecond (0 .. 9)
             *               * %F - fractional seconds/microseconds (000000 - 999999)
             *               * %% - percent sign.
             *
             * @param    timespan    The timespan.
             * @param    fmt            (Optional) describes the format to use.
             *
             * @return    The formatted value.
             */

            static std::string Format(const Timespan& timespan, const std::string& fmt = "%dd %H:%M:%S.%i");

            /**
             * @fn    static void DateTimeFormatter::Append(std::string& str, const Timestamp& timestamp, const std::string& fmt, int timeZoneDifferential = UTC);
             *
             * @brief    Formats the given timestamp according to the given format and appends it to str.
             *             
             *             See Format() for documentation of the formatting string.
             *
             * @param [in,out]    str                The string.
             * @param    timestamp                The timestamp.
             * @param    fmt                        Describes the format to use.
             * @param    timeZoneDifferential    (Optional) the time zone differential.
             */

            static void Append(std::string& str, const Timestamp& timestamp, const std::string& fmt, int timeZoneDifferential = UTC);

            /**
             * @fn    static void DateTimeFormatter::Append(std::string& str, const DateTime& dateTime, const std::string& fmt, int timeZoneDifferential = UTC);
             *
             * @brief    Formats the given date and time according to the given format and appends it to str.
             *             
             *             See Format() for documentation of the formatting string.
             *
             * @param [in,out]    str                The string.
             * @param    dateTime                The date time.
             * @param    fmt                        Describes the format to use.
             * @param    timeZoneDifferential    (Optional) the time zone differential.
             */

            static void Append(std::string& str, const DateTime& dateTime, const std::string& fmt, int timeZoneDifferential = UTC);

            /**
             * @fn    static void DateTimeFormatter::Append(std::string& str, const LocalDateTime& dateTime, const std::string& fmt);
             *
             * @brief    Formats the given local date and time according to the given format and appends it to
             *             str.
             *             
             *             See Format() for documentation of the formatting string.
             *
             * @param [in,out]    str    The string.
             * @param    dateTime       The date time.
             * @param    fmt               Describes the format to use.
             */

            static void Append(std::string& str, const LocalDateTime& dateTime, const std::string& fmt);

            /**
             * @fn    static void DateTimeFormatter::Append(std::string& str, const Timespan& timespan, const std::string& fmt = "%dd %H:%M:%S.%i");
             *
             * @brief    Formats the given timespan according to the given format and appends it to str.
             *             
             *             See Format() for documentation of the formatting string.
             *
             * @param [in,out]    str    The string.
             * @param    timespan       The timespan.
             * @param    fmt               (Optional) describes the format to use.
             */

            static void Append(std::string& str, const Timespan& timespan, const std::string& fmt = "%dd %H:%M:%S.%i");

            /**
             * @fn    static std::string DateTimeFormatter::TimezoneDifferenzeISO(int timeZoneDifferential);
             *
             * @brief    Formats the given timezone differential in ISO format. If timeZoneDifferential is UTC,
             *             "Z" is returned, otherwise, +HH.MM (or -HH.MM) is returned.
             *
             * @param    timeZoneDifferential    The time zone differential.
             *
             * @return    A std::string.
             */

            static std::string TimezoneDifferenzeISO(int timeZoneDifferential);

            /**
             * @fn    static std::string DateTimeFormatter::TimezoneDifferenzeRFC(int timeZoneDifferential);
             *
             * @brief    Formats the given timezone differential in RFC format. If timeZoneDifferential is UTC,
             *             "GMT" is returned, otherwise ++HHMM (or -HHMM) is returned.
             *
             * @param    timeZoneDifferential    The time zone differential.
             *
             * @return    A std::string.
             */

            static std::string TimezoneDifferenzeRFC(int timeZoneDifferential);

            /**
             * @fn    static void DateTimeFormatter::TimezoneDifferenzeISO(std::string& str, int timeZoneDifferential);
             *
             * @brief    Formats the given timezone differential in ISO format and appends it to the given
             *             string. If timeZoneDifferential is UTC, "Z" is returned, otherwise, +HH.MM (or -
             *             HH.MM) is returned.
             *
             * @param [in,out]    str                The string.
             * @param    timeZoneDifferential    The time zone differential.
             */

            static void TimezoneDifferenzeISO(std::string& str, int timeZoneDifferential);

            /**
             * @fn    static void DateTimeFormatter::TimezoneDifferenzeRFC(std::string& str, int timeZoneDifferential);
             *
             * @brief    Formats the given timezone differential in RFC format and appends it to the given
             *             string. If timeZoneDifferential is UTC, "GMT" is returned, otherwise ++HHMM (or -
             *             HHMM) is returned.
             *
             * @param [in,out]    str                The string.
             * @param    timeZoneDifferential    The time zone differential.
             */

            static void TimezoneDifferenzeRFC(std::string& str, int timeZoneDifferential);
        };


        //
        // inlines
        //
        inline std::string DateTimeFormatter::Format(const Timestamp& timestamp, const std::string& fmt, int timeZoneDifferential)
        {
            DateTime dateTime(timestamp);
            return Format(dateTime, fmt, timeZoneDifferential);
        }


        inline std::string DateTimeFormatter::Format(const DateTime& dateTime, const std::string& fmt, int timeZoneDifferential)
        {
            std::string result;
            result.reserve(64);
            Append(result, dateTime, fmt, timeZoneDifferential);
            return result;
        }


        inline std::string DateTimeFormatter::Format(const LocalDateTime& dateTime, const std::string& fmt)
        {
            return Format(dateTime.dateTime_, fmt, dateTime.tzd_);
        }


        inline std::string DateTimeFormatter::Format(const Timespan& timespan, const std::string& fmt)
        {
            std::string result;
            result.reserve(32);
            Append(result, timespan, fmt);
            return result;
        }


        inline void DateTimeFormatter::Append(std::string& str, const Timestamp& timestamp, const std::string& fmt, int timeZoneDifferential)
        {
            DateTime dateTime(timestamp);
            Append(str, dateTime, fmt, timeZoneDifferential);
        }


        inline std::string DateTimeFormatter::TimezoneDifferenzeISO(int timeZoneDifferential)
        {
            std::string result;
            result.reserve(8);
            TimezoneDifferenzeISO(result, timeZoneDifferential);
            return result;
        }


        inline std::string DateTimeFormatter::TimezoneDifferenzeRFC(int timeZoneDifferential)
        {
            std::string result;
            result.reserve(8);
            TimezoneDifferenzeRFC(result, timeZoneDifferential);
            return result;
        }
    }
}

#endif /* TECHNOSOFTWARE_DATETIMEFORMATTER_H */
