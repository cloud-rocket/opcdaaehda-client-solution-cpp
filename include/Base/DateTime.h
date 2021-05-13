/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the DateTime class.
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

#ifndef TECHNOSOFTWARE_DATETIME_H
#define TECHNOSOFTWARE_DATETIME_H

#include "Base/Base.h"
#include "Base/Timestamp.h"
#include "Base/Timespan.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   DateTime
         *
         * @brief   This class represents an instant in time, expressed in years, months, days, hours,
         *          minutes, seconds and milliseconds based on the Gregorian calendar. The class is
         *          mainly useful for conversions between UTC, Julian day and Gregorian calendar dates.
         *          
         *          The date and time stored in a DateTime is always in UTC (Coordinated Universal Time)
         *          and thus independent of the timezone in effect on the system.
         *          
         *          Conversion calculations are based on algorithms collected and described by Peter Baum
         *          at http://vsg.cape.com/~pbaum/date/date0.htm
         *          
         *          Internally, this class stores a date/time in two forms (UTC and broken down) for
         *          performance reasons. Only use this class for conversions between date/time
         *          representations. Use the Timestamp class for everything else.
         *          
         *          Notes:
         *            * Zero is a valid year (in accordance with ISO 8601 and astronomical year numbering)
         *            * Year zero (0) is a leap year
         *            * Negative years (years preceding 1 BC) are not supported
         *          
         *          For more information, please see:
         *            * http://en.wikipedia.org/wiki/Gregorian_Calendar
         *            * http://en.wikipedia.org/wiki/Julian_day
         *            * http://en.wikipedia.org/wiki/UTC
         *            * http://en.wikipedia.org/wiki/ISO_8601.
         *
         * @ingroup BaseDateTime
         */

        class TECHNOSOFTWARE_API DateTime
        {
        public:

            /**
             * @enum    Months
             *
             * @brief   Symbolic names for month numbers (1 to 12).
             */

            enum Months
            {
                JANUARY = 1,
                FEBRUARY,
                MARCH,
                APRIL,
                MAY,
                JUNE,
                JULY,
                AUGUST,
                SEPTEMBER,
                OCTOBER,
                NOVEMBER,
                DECEMBER
            };

            /**
             * @enum    DaysOfWeek
             *
             * @brief   Symbolic names for week day numbers (0 to 6).
             */

            enum DaysOfWeek
            {
                SUNDAY = 0,
                MONDAY,
                TUESDAY,
                WEDNESDAY,
                THURSDAY,
                FRIDAY,
                SATURDAY
            };

            /**
             * @fn  DateTime::DateTime();
             *
             * @brief   Creates a DateTime for the current date and time.
             */

            DateTime();

            /**
             * @fn  DateTime::DateTime(const Timestamp& timestamp);
             *
             * @brief   Creates a DateTime for the date and time given in a Timestamp.
             *
             * @param   timestamp   The timestamp.
             */

            DateTime(const Timestamp& timestamp);

            /**
             * @fn  DateTime::DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
             *
             * @brief   Creates a DateTime for the given Gregorian date and time.
             *            * year is from 0 to 9999.
             *            * month is from 1 to 12.
             *            * day is from 1 to 31.
             *            * hour is from 0 to 23.
             *            * minute is from 0 to 59.
             *            * second is from 0 to 60 (allowing leap seconds).
             *            * millisecond is from 0 to 999.
             *            * microsecond is from 0 to 999.
             *
             * @param   year        The year.
             * @param   month       The month.
             * @param   day         The day.
             * @param   hour        (Optional) the hour.
             * @param   minute      (Optional) the minute.
             * @param   second      (Optional) the second.
             * @param   millisecond (Optional) the millisecond.
             * @param   microsecond (Optional) the microsecond.
             */

            DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

            /**
             * @fn  DateTime::DateTime(double julianDay);
             *
             * @brief   Creates a DateTime for the given Julian day.
             *
             * @param   julianDay   The julian day.
             */

            DateTime(double julianDay);

            /**
             * @fn  DateTime::DateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff);
             *
             * @brief   Creates a DateTime from an UtcTimeVal and a TimeDiff.
             *          
             *          Mainly used internally by DateTime and friends.
             *
             * @param   utcTime The UTC time.
             * @param   diff    The difference.
             */

            DateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff);

            /**
             * @fn  DateTime::DateTime(const DateTime& dateTime);
             *
             * @brief   Copy constructor. Creates the DateTime from another one.
             *
             * @param   dateTime    The date time.
             */

            DateTime(const DateTime& dateTime);

            /**
             * @fn  DateTime::~DateTime();
             *
             * @brief   Destroys the DateTime.
             */

            ~DateTime();

            /**
             * @fn  DateTime& DateTime::operator= (const DateTime& dateTime);
             *
             * @brief   Assigns another DateTime.
             *
             * @param   dateTime    The date time.
             *
             * @return  A shallow copy of this object.
             */

            DateTime& operator = (const DateTime& dateTime);

            /**
             * @fn  DateTime& DateTime::operator= (const Timestamp& timestamp);
             *
             * @brief   Assigns a Timestamp.
             *
             * @param   timestamp   The timestamp.
             *
             * @return  A shallow copy of this object.
             */

            DateTime& operator = (const Timestamp& timestamp);

            /**
             * @fn  DateTime& DateTime::operator= (double julianDay);
             *
             * @brief   Assigns a Julian day.
             *
             * @param   julianDay   The julian day.
             *
             * @return  A shallow copy of this object.
             */

            DateTime& operator = (double julianDay);

            /**
             * @fn  DateTime& DateTime::Assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0);
             *
             * @brief   Assigns a Gregorian date and time.
             *            * year is from 0 to 9999.
             *            * month is from 1 to 12.
             *            * day is from 1 to 31.
             *            * hour is from 0 to 23.
             *            * minute is from 0 to 59.
             *            * second is from 0 to 60 (allowing leap seconds).
             *            * millisecond is from 0 to 999.
             *            * microsecond is from 0 to 999.
             *
             * @param   year            The year.
             * @param   month           The month.
             * @param   day             The day.
             * @param   hour            (Optional) the hour.
             * @param   minute          (Optional) the minute.
             * @param   second          (Optional) the second.
             * @param   millisecond     (Optional) the millisecond.
             * @param   microseconds    (Optional) the microseconds.
             *
             * @return  A reference to a DateTime.
             */

            DateTime& Assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0);

            /**
             * @fn  void DateTime::Swap(DateTime& dateTime);
             *
             * @brief   Swaps the DateTime with another one.
             *
             * @param [in,out]  dateTime    The date time.
             */

            void Swap(DateTime& dateTime);

            /**
             * @fn  int DateTime::GetYear() const;
             *
             * @brief   Returns the year.
             *
             * @return  The year.
             */

            int GetYear() const;

            /**
             * @fn  int DateTime::GetMonth() const;
             *
             * @brief   Returns the month (1 to 12).
             *
             * @return  The month.
             */

            int GetMonth() const;

            /**
             * @fn  int DateTime::GetWeek(int firstDayOfWeek = MONDAY) const;
             *
             * @brief   Returns the week number within the year. FirstDayOfWeek should be either SUNDAY (0)
             *          or MONDAY (1). The returned week number will be from 0 to 53. Week number 1 is the
             *          week containing January 4. This is in accordance to ISO 8601.
             *          
             *          The following example assumes that firstDayOfWeek is MONDAY. For 2005, which started
             *          on a Saturday, week 1 will be the week starting on Monday, January 3. January 1 and 2
             *          will fall within week 0 (or the last week of the previous year).
             *          
             *          For 2007, which starts on a Monday, week 1 will be the week startung on Monday,
             *          January 1. There will be no week 0 in 2007.
             *
             * @param   firstDayOfWeek  (Optional) the first day of week.
             *
             * @return  The week.
             */

            int GetWeek(int firstDayOfWeek = MONDAY) const;

            /**
             * @fn  int DateTime::GetDay() const;
             *
             * @brief   Returns the day witin the month (1 to 31).
             *
             * @return  The day.
             */

            int GetDay() const;

            /**
             * @fn  int DateTime::GetDayOfWeek() const;
             *
             * @brief   Returns the weekday (0 to 6, where 0 = Sunday, 1 = Monday, ..., 6 = Saturday).
             *
             * @return  The day of week.
             */

            int GetDayOfWeek() const;

            /**
             * @fn  int DateTime::GetDayOfYear() const;
             *
             * @brief   Returns the number of the day in the year. January 1 is 1, February 1 is 32, etc.
             *
             * @return  The day of year.
             */

            int GetDayOfYear() const;

            /**
             * @fn  int DateTime::GetHour() const;
             *
             * @brief   Returns the hour (0 to 23).
             *
             * @return  The hour.
             */

            int GetHour() const;

            /**
             * @fn  int DateTime::GetHourAMPM() const;
             *
             * @brief   Returns the hour (0 to 12).
             *
             * @return  The hour a mpm.
             */

            int GetHourAMPM() const;

            /**
             * @fn  bool DateTime::IsAM() const;
             *
             * @brief   Returns true if hour &lt; 12;
             *
             * @return  true if a m, false if not.
             */

            bool IsAM() const;

            /**
             * @fn  bool DateTime::IsPM() const;
             *
             * @brief   Returns true if hour >= 12.
             *
             * @return  true if pm, false if not.
             */

            bool IsPM() const;

            /**
             * @fn  int DateTime::GetMinute() const;
             *
             * @brief   Returns the minute (0 to 59).
             *
             * @return  The minute.
             */

            int GetMinute() const;

            /**
             * @fn  int DateTime::GetSecond() const;
             *
             * @brief   Returns the second (0 to 59).
             *
             * @return  The second.
             */

            int GetSecond() const;

            /**
             * @fn  int DateTime::GetMillisecond() const;
             *
             * @brief   Returns the millisecond (0 to 999)
             *
             * @return  The millisecond.
             */

            int GetMillisecond() const;

            /**
             * @fn  int DateTime::GetMicrosecond() const;
             *
             * @brief   Returns the microsecond (0 to 999)
             *
             * @return  The microsecond.
             */

            int GetMicrosecond() const;

            /**
             * @fn  double DateTime::GetJulianDay() const;
             *
             * @brief   Returns the julian day for the date and time.
             *
             * @return  The julian day.
             */

            double GetJulianDay() const;

            /**
             * @fn  Timestamp DateTime::GetTimestamp() const;
             *
             * @brief   Returns the date and time expressed as a Timestamp.
             *
             * @return  The timestamp.
             */

            Timestamp GetTimestamp() const;

            /**
             * @fn  Timestamp::UtcTimeVal DateTime::GetUtcTime() const;
             *
             * @brief   Returns the date and time expressed in UTC-based time. UTC base time is midnight,
             *          October 15, 1582. Resolution is 100 nanoseconds.
             *
             * @return  The UTC time.
             */

            Timestamp::UtcTimeVal GetUtcTime() const;

            bool operator == (const DateTime& dateTime) const;
            bool operator != (const DateTime& dateTime) const;
            bool operator <  (const DateTime& dateTime) const;
            bool operator <= (const DateTime& dateTime) const;
            bool operator >  (const DateTime& dateTime) const;
            bool operator >= (const DateTime& dateTime) const;

            DateTime  operator +  (const Timespan& span) const;
            DateTime  operator -  (const Timespan& span) const;
            Timespan  operator -  (const DateTime& dateTime) const;
            DateTime& operator += (const Timespan& span);
            DateTime& operator -= (const Timespan& span);

            /**
             * @fn  void DateTime::MakeUtc(int tzd);
             *
             * @brief   Converts a local time into UTC, by applying the given time zone differential.
             *
             * @param   tzd The tzd.
             */

            void MakeUtc(int tzd);

            /**
             * @fn  void DateTime::MakeLocal(int tzd);
             *
             * @brief   Converts a UTC time into a local time, by applying the given time zone differential.
             *
             * @param   tzd The tzd.
             */

            void MakeLocal(int tzd);

            /**
             * @fn  static bool DateTime::IsLeapYear(int year);
             *
             * @brief   Returns true if the given year is a leap year;
             *          false otherwise.
             *
             * @param   year    The year.
             *
             * @return  true if leap year, false if not.
             */

            static bool IsLeapYear(int year);

            /**
             * @fn  static int DateTime::GetDaysOfMonth(int year, int month);
             *
             * @brief   Returns the number of days in the given month and year. Month is from 1 to 12.
             *
             * @param   year    The year.
             * @param   month   The month.
             *
             * @return  The days of month.
             */

            static int GetDaysOfMonth(int year, int month);

            /**
             * @fn  static bool DateTime::IsValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
             *
             * @brief   Checks if the given date and time is valid (all arguments are within a proper range).
             *          
             *          Returns true if all arguments are valid, false otherwise.
             *
             * @param   year        The year.
             * @param   month       The month.
             * @param   day         The day.
             * @param   hour        (Optional) the hour.
             * @param   minute      (Optional) the minute.
             * @param   second      (Optional) the second.
             * @param   millisecond (Optional) the millisecond.
             * @param   microsecond (Optional) the microsecond.
             *
             * @return  true if valid, false if not.
             */

            static bool IsValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

        protected:

            /**
             * @fn  static double DateTime::ToJulianDay(Timestamp::UtcTimeVal utcTime);
             *
             * @brief   Computes the Julian day for an UTC time.
             *
             * @param   utcTime The UTC time.
             *
             * @return  utcTime as a double.
             */

            static double ToJulianDay(Timestamp::UtcTimeVal utcTime);

            /**
             * @fn  static double DateTime::ToJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
             *
             * @brief   Computes the Julian day for a gregorian calendar date and time. See &lt;
             *          http://vsg.cape.com/~pbaum/date/jdimp.htm&gt;, section 2.3.1 for the algorithm.
             *
             * @param   year        The year.
             * @param   month       The month.
             * @param   day         The day.
             * @param   hour        (Optional) the hour.
             * @param   minute      (Optional) the minute.
             * @param   second      (Optional) the second.
             * @param   millisecond (Optional) the millisecond.
             * @param   microsecond (Optional) the microsecond.
             *
             * @return  The given data converted to a double.
             */

            static double ToJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

            /**
             * @fn  static Timestamp::UtcTimeVal DateTime::ToUtcTime(double julianDay);
             *
             * @brief   Computes the UTC time for a Julian day.
             *
             * @param   julianDay   The julian day.
             *
             * @return  julianDay as a Timestamp::UtcTimeVal.
             */

            static Timestamp::UtcTimeVal ToUtcTime(double julianDay);

            /**
             * @fn  void DateTime::ComputeGregorian(double julianDay);
             *
             * @brief   Computes the Gregorian date for the given Julian day. See &lt;
             *          http://vsg.cape.com/~pbaum/date/injdimp.htm&gt;, section 3.3.1 for the algorithm.
             *
             * @param   julianDay   The julian day.
             */

            void ComputeGregorian(double julianDay);

            /**
             * @fn  void DateTime::ComputeDaytime();
             *
             * @brief   Extracts the daytime (hours, minutes, seconds, etc.) from the stored utcTime.
             */

            void ComputeDaytime();

        private:
            void CheckLimit(short& lower, short& higher, short limit);
            ///utility functions used to correct the overflow in computeGregorian
            void Normalize();

            Timestamp::UtcTimeVal utcTime_;
            short  year_;
            short  month_;
            short  day_;
            short  hour_;
            short  minute_;
            short  second_;
            short  millisecond_;
            short  microsecond_;
        };


        //
        // inlines
        //
        inline Timestamp DateTime::GetTimestamp() const
        {
            return Timestamp::FromUtcTime(utcTime_);
        }


        inline Timestamp::UtcTimeVal DateTime::GetUtcTime() const
        {
            return utcTime_;
        }


        inline int DateTime::GetYear() const
        {
            return year_;
        }


        inline int DateTime::GetMonth() const
        {
            return month_;
        }


        inline int DateTime::GetDay() const
        {
            return day_;
        }


        inline int DateTime::GetHour() const
        {
            return hour_;
        }


        inline int DateTime::GetHourAMPM() const
        {
            if (hour_ < 1)
                return 12;
            else if (hour_ > 12)
                return hour_ - 12;
            else
                return hour_;
        }


        inline bool DateTime::IsAM() const
        {
            return hour_ < 12;
        }


        inline bool DateTime::IsPM() const
        {
            return hour_ >= 12;
        }


        inline int DateTime::GetMinute() const
        {
            return minute_;
        }


        inline int DateTime::GetSecond() const
        {
            return second_;
        }


        inline int DateTime::GetMillisecond() const
        {
            return millisecond_;
        }


        inline int DateTime::GetMicrosecond() const
        {
            return microsecond_;
        }


        inline bool DateTime::operator == (const DateTime& dateTime) const
        {
            return utcTime_ == dateTime.utcTime_;
        }


        inline bool DateTime::operator != (const DateTime& dateTime) const
        {
            return utcTime_ != dateTime.utcTime_;
        }


        inline bool DateTime::operator <  (const DateTime& dateTime) const
        {
            return utcTime_ < dateTime.utcTime_;
        }


        inline bool DateTime::operator <= (const DateTime& dateTime) const
        {
            return utcTime_ <= dateTime.utcTime_;
        }


        inline bool DateTime::operator >  (const DateTime& dateTime) const
        {
            return utcTime_ > dateTime.utcTime_;
        }


        inline bool DateTime::operator >= (const DateTime& dateTime) const
        {
            return utcTime_ >= dateTime.utcTime_;
        }


        inline bool DateTime::IsLeapYear(int year)
        {
            return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
        }


        inline void Swap(DateTime& d1, DateTime& d2)
        {
            d1.Swap(d2);
        }
    }
}

#endif /* TECHNOSOFTWARE_DATETIME_H */
