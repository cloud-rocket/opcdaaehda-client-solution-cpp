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

#include "Base/DateTimeFormatter.h"
#include "Base/DateTimeFormat.h"
#include "Base/Timestamp.h"
#include "Base/NumberFormatter.h"

namespace Technosoftware
{
    namespace Base
    {
        void DateTimeFormatter::Append(std::string& str, const LocalDateTime& dateTime, const std::string& fmt)
        {
            DateTimeFormatter::Append(str, dateTime.dateTime_, fmt, dateTime.GetTimezoneDifference());
        }


        void DateTimeFormatter::Append(std::string& str, const DateTime& dateTime, const std::string& fmt, int timeZoneDifferential)
        {
            std::string::const_iterator it = fmt.begin();
            std::string::const_iterator end = fmt.end();
            while (it != end)
            {
                if (*it == '%')
                {
                    if (++it != end)
                    {
                        switch (*it)
                        {
                        case 'w': str.append(DateTimeFormat::WEEKDAY_NAMES[dateTime.GetDayOfWeek()], 0, 3); break;
                        case 'W': str.append(DateTimeFormat::WEEKDAY_NAMES[dateTime.GetDayOfWeek()]); break;
                        case 'b': str.append(DateTimeFormat::MONTH_NAMES[dateTime.GetMonth() - 1], 0, 3); break;
                        case 'B': str.append(DateTimeFormat::MONTH_NAMES[dateTime.GetMonth() - 1]); break;
                        case 'd': NumberFormatter::Append0(str, dateTime.GetDay(), 2); break;
                        case 'e': NumberFormatter::Append(str, dateTime.GetDay()); break;
                        case 'f': NumberFormatter::Append(str, dateTime.GetDay(), 2); break;
                        case 'm': NumberFormatter::Append0(str, dateTime.GetMonth(), 2); break;
                        case 'n': NumberFormatter::Append(str, dateTime.GetMonth()); break;
                        case 'o': NumberFormatter::Append(str, dateTime.GetMonth(), 2); break;
                        case 'y': NumberFormatter::Append0(str, dateTime.GetYear() % 100, 2); break;
                        case 'Y': NumberFormatter::Append0(str, dateTime.GetYear(), 4); break;
                        case 'H': NumberFormatter::Append0(str, dateTime.GetHour(), 2); break;
                        case 'h': NumberFormatter::Append0(str, dateTime.GetHourAMPM(), 2); break;
                        case 'a': str.append(dateTime.IsAM() ? "am" : "pm"); break;
                        case 'A': str.append(dateTime.IsAM() ? "AM" : "PM"); break;
                        case 'M': NumberFormatter::Append0(str, dateTime.GetMinute(), 2); break;
                        case 'S': NumberFormatter::Append0(str, dateTime.GetSecond(), 2); break;
                        case 's': NumberFormatter::Append0(str, dateTime.GetSecond(), 2);
                            str += '.';
                            NumberFormatter::Append0(str, dateTime.GetMillisecond() * 1000 + dateTime.GetMicrosecond(), 6);
                            break;
                        case 'i': NumberFormatter::Append0(str, dateTime.GetMillisecond(), 3); break;
                        case 'c': NumberFormatter::Append(str, dateTime.GetMillisecond() / 100); break;
                        case 'F': NumberFormatter::Append0(str, dateTime.GetMillisecond() * 1000 + dateTime.GetMicrosecond(), 6); break;
                        case 'z': TimezoneDifferenzeISO(str, timeZoneDifferential); break;
                        case 'Z': TimezoneDifferenzeRFC(str, timeZoneDifferential); break;
                        default:  str += *it;
                        }
                        ++it;
                    }
                }
                else str += *it++;
            }
        }


        void DateTimeFormatter::Append(std::string& str, const Timespan& timespan, const std::string& fmt)
        {
            std::string::const_iterator it = fmt.begin();
            std::string::const_iterator end = fmt.end();
            while (it != end)
            {
                if (*it == '%')
                {
                    if (++it != end)
                    {
                        switch (*it)
                        {
                        case 'd': NumberFormatter::Append(str, timespan.GetDays()); break;
                        case 'H': NumberFormatter::Append0(str, timespan.GetHours(), 2); break;
                        case 'h': NumberFormatter::Append(str, timespan.GetTotalHours()); break;
                        case 'M': NumberFormatter::Append0(str, timespan.GetMinutes(), 2); break;
                        case 'm': NumberFormatter::Append(str, timespan.GetTotalMinutes()); break;
                        case 'S': NumberFormatter::Append0(str, timespan.GetSeconds(), 2); break;
                        case 's': NumberFormatter::Append(str, timespan.GetTotalSeconds()); break;
                        case 'i': NumberFormatter::Append0(str, timespan.GetMilliseconds(), 3); break;
                        case 'c': NumberFormatter::Append(str, timespan.GetMilliseconds() / 100); break;
                        case 'F': NumberFormatter::Append0(str, timespan.GetMilliseconds() * 1000 + timespan.GetMicroseconds(), 6); break;
                        default:  str += *it;
                        }
                        ++it;
                    }
                }
                else str += *it++;
            }
        }


        void DateTimeFormatter::TimezoneDifferenzeISO(std::string& str, int timeZoneDifferential)
        {
            if (timeZoneDifferential != UTC)
            {
                if (timeZoneDifferential >= 0)
                {
                    str += '+';
                    NumberFormatter::Append0(str, timeZoneDifferential / 3600, 2);
                    str += ':';
                    NumberFormatter::Append0(str, (timeZoneDifferential % 3600) / 60, 2);
                }
                else
                {
                    str += '-';
                    NumberFormatter::Append0(str, -timeZoneDifferential / 3600, 2);
                    str += ':';
                    NumberFormatter::Append0(str, (-timeZoneDifferential % 3600) / 60, 2);
                }
            }
            else str += 'Z';
        }


        void DateTimeFormatter::TimezoneDifferenzeRFC(std::string& str, int timeZoneDifferential)
        {
            if (timeZoneDifferential != UTC)
            {
                if (timeZoneDifferential >= 0)
                {
                    str += '+';
                    NumberFormatter::Append0(str, timeZoneDifferential / 3600, 2);
                    NumberFormatter::Append0(str, (timeZoneDifferential % 3600) / 60, 2);
                }
                else
                {
                    str += '-';
                    NumberFormatter::Append0(str, -timeZoneDifferential / 3600, 2);
                    NumberFormatter::Append0(str, (-timeZoneDifferential % 3600) / 60, 2);
                }
            }
            else str += "GMT";
        }
    }

}
