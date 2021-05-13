/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the LocalDateTime class.
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

#ifndef TECHNOSOFTWARE_LOCALDATETIME_H
#define TECHNOSOFTWARE_LOCALDATETIME_H

#include "Base/Base.h"
#include "Base/DateTime.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   LocalDateTime
         *
         * @brief   This class represents an instant in local time (as opposed to UTC), expressed in
         *          years, months, days, hours, minutes, seconds and milliseconds based on the Gregorian
         *          calendar.
         *          
         *          In addition to the date and time, the class also maintains a time zone differential,
         *          which denotes the difference in seconds from UTC to local time,
         *          i.e. UTC = local time - time zone differential.
         *          
         *          Although LocalDateTime supports relational and arithmetic operators, all date/time
         *          comparisons and date/time arithmetics should be done in UTC, using the DateTime or
         *          Timestamp class for better performance. The relational operators normalize the
         *          dates/times involved to UTC before carrying out the comparison.
         *          
         *          The time zone differential is based on the input date and time and current time zone.
         *          A number of constructors accept an explicit time zone differential parameter. These
         *          should not be used since daylight savings time processing is impossible since the
         *          time zone is unknown. Each of the constructors accepting a tzd parameter have been
         *          marked as deprecated and may be removed in a future revision.
         *
         * @ingroup BaseDateTime
         */

        class TECHNOSOFTWARE_API LocalDateTime
        {
        public:

            /**
             * @fn  LocalDateTime::LocalDateTime();
             *
             * @brief   Creates a LocalDateTime with the current date/time for the current time zone.
             */

            LocalDateTime();

            /**
             * @fn  LocalDateTime::LocalDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
             *
             * @brief   Creates a LocalDateTime for the given Gregorian local date and time.
             *            * year is from 0 to 9999.
             *            * month is from 1 to 12.
             *            * day is from 1 to 31.
             *            * hour is from 0 to 23.
             *            * minute is from 0 to 59.
             *            * second is from 0 to 59.
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

            LocalDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

            /**
             * @fn  LocalDateTime::LocalDateTime(const DateTime& dateTime);
             *
             * @brief   Creates a LocalDateTime from the UTC time given in dateTime, using the time zone
             *          differential of the current time zone.
             *
             * @param   dateTime    The date time.
             */

            LocalDateTime(const DateTime& dateTime);

            /**
             * @fn  LocalDateTime::LocalDateTime(double julianDay);
             *
             * @brief   Creates a LocalDateTime for the given Julian day in the local time zone.
             *
             * @param   julianDay   The julian day.
             */

            LocalDateTime(double julianDay);

            /**
             * @fn  LocalDateTime::LocalDateTime(const LocalDateTime& dateTime);
             *
             * @brief   Copy constructor. Creates the LocalDateTime from another one.
             *
             * @param   dateTime    The date time.
             */

            LocalDateTime(const LocalDateTime& dateTime);

            /**
             * @fn  LocalDateTime::~LocalDateTime();
             *
             * @brief   Destroys the LocalDateTime.
             */

            ~LocalDateTime();

            /**
             * @fn  LocalDateTime& LocalDateTime::operator= (const LocalDateTime& dateTime);
             *
             * @brief   Assigns another LocalDateTime.
             *
             * @param   dateTime    The date time.
             *
             * @return  A shallow copy of this object.
             */

            LocalDateTime& operator = (const LocalDateTime& dateTime);

            /**
             * @fn  LocalDateTime& LocalDateTime::operator= (const Timestamp& timestamp);
             *
             * @brief   Assigns a timestamp.
             *
             * @param   timestamp   The timestamp.
             *
             * @return  A shallow copy of this object.
             */

            LocalDateTime& operator = (const Timestamp& timestamp);

            /**
             * @fn  LocalDateTime& LocalDateTime::operator= (double julianDay);
             *
             * @brief   Assigns a Julian day in the local time zone.
             *
             * @param   julianDay   The julian day.
             *
             * @return  A shallow copy of this object.
             */

            LocalDateTime& operator = (double julianDay);

            /**
             * @fn  LocalDateTime& LocalDateTime::Assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0);
             *
             * @brief   Assigns a Gregorian local date and time.
             *            * year is from 0 to 9999.
             *            * month is from 1 to 12.
             *            * day is from 1 to 31.
             *            * hour is from 0 to 23.
             *            * minute is from 0 to 59.
             *            * second is from 0 to 59.
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
             * @return  A reference to a LocalDateTime.
             */

            LocalDateTime& Assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0);

            /**
             * @fn  void LocalDateTime::Swap(LocalDateTime& dateTime);
             *
             * @brief   Swaps the LocalDateTime with another one.
             *
             * @param [in,out]  dateTime    The date time.
             */

            void Swap(LocalDateTime& dateTime);

            /**
             * @fn  int LocalDateTime::GetYear() const;
             *
             * @brief   Returns the year.
             *
             * @return  The year.
             */

            int GetYear() const;

            /**
             * @fn  int LocalDateTime::GetMonth() const;
             *
             * @brief   Returns the month (1 to 12).
             *
             * @return  The month.
             */

            int GetMonth() const;

            /**
             * @fn  int LocalDateTime::GetWeek(int firstDayOfWeek = DateTime::MONDAY) const;
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

            int GetWeek(int firstDayOfWeek = DateTime::MONDAY) const;

            /**
             * @fn  int LocalDateTime::GetDay() const;
             *
             * @brief   Returns the day witin the month (1 to 31).
             *
             * @return  The dday.
             */

            int GetDay() const;

            /**
             * @fn  int LocalDateTime::GetDayOfWeek() const;
             *
             * @brief   Returns the weekday (0 to 6, where 0 = Sunday, 1 = Monday, ..., 6 = Saturday).
             *
             * @return  The day of week.
             */

            int GetDayOfWeek() const;

            /**
             * @fn  int LocalDateTime::GetDayOfYear() const;
             *
             * @brief   Returns the number of the day in the year. January 1 is 1, February 1 is 32, etc.
             *
             * @return  The day of year.
             */

            int GetDayOfYear() const;

            /**
             * @fn  int LocalDateTime::GetHour() const;
             *
             * @brief   Returns the hour (0 to 23).
             *
             * @return  The hour.
             */

            int GetHour() const;

            /**
             * @fn  int LocalDateTime::GetHourAMPM() const;
             *
             * @brief   Returns the hour (0 to 12).
             *
             * @return  The hour a mpm.
             */

            int GetHourAMPM() const;

            /**
             * @fn  bool LocalDateTime::IsAM() const;
             *
             * @brief   Returns true if hour &lt; 12;
             *
             * @return  true if a m, false if not.
             */

            bool IsAM() const;

            /**
             * @fn  bool LocalDateTime::IsPM() const;
             *
             * @brief   Returns true if hour >= 12.
             *
             * @return  true if pm, false if not.
             */

            bool IsPM() const;

            /**
             * @fn  int LocalDateTime::GetMinute() const;
             *
             * @brief   Returns the minute (0 to 59).
             *
             * @return  The minute.
             */

            int GetMinute() const;

            /**
             * @fn  int LocalDateTime::GetSecond() const;
             *
             * @brief   Returns the second (0 to 59).
             *
             * @return  The second.
             */

            int GetSecond() const;

            /**
             * @fn  int LocalDateTime::GetMillisecond() const;
             *
             * @brief   Returns the millisecond (0 to 999)
             *
             * @return  The millisecond.
             */

            int GetMillisecond() const;

            /**
             * @fn  int LocalDateTime::GetMicrosecond() const;
             *
             * @brief   Returns the microsecond (0 to 999)
             *
             * @return  The microsecond.
             */

            int GetMicrosecond() const;

            /**
             * @fn  double LocalDateTime::GetJulianDay() const;
             *
             * @brief   Returns the julian day for the date.
             *
             * @return  The julian day.
             */

            double GetJulianDay() const;

            /**
             * @fn  int LocalDateTime::GetTimezoneDifference() const;
             *
             * @brief   Returns the time zone differential.
             *
             * @return  The timezome difference.
             */

            int GetTimezoneDifference() const;

            /**
             * @fn  DateTime LocalDateTime::GetUTC() const;
             *
             * @brief   Returns the UTC equivalent for the local date and time.
             *
             * @return  The UTC.
             */

            DateTime GetUTC() const;

            /**
             * @fn  Timestamp LocalDateTime::GetTimestamp() const;
             *
             * @brief   Returns the date and time expressed as a Timestamp.
             *
             * @return  The timestamp.
             */

            Timestamp GetTimestamp() const;

            /**
             * @fn  Timestamp::UtcTimeVal LocalDateTime::GetUTCTime() const;
             *
             * @brief   Returns the UTC equivalent for the local date and time.
             *
             * @return  The UTC time.
             */

            Timestamp::UtcTimeVal GetUTCTime() const;

            bool operator == (const LocalDateTime& dateTime) const;
            bool operator != (const LocalDateTime& dateTime) const;
            bool operator <  (const LocalDateTime& dateTime) const;
            bool operator <= (const LocalDateTime& dateTime) const;
            bool operator >  (const LocalDateTime& dateTime) const;
            bool operator >= (const LocalDateTime& dateTime) const;

            LocalDateTime  operator +  (const Timespan& span) const;
            LocalDateTime  operator -  (const Timespan& span) const;
            Timespan       operator -  (const LocalDateTime& dateTime) const;
            LocalDateTime& operator += (const Timespan& span);
            LocalDateTime& operator -= (const Timespan& span);

        protected:
            LocalDateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff, int tzd);

            /**
             * @fn  void LocalDateTime::DetermineTzd(bool adjust = false);
             *
             * @brief   Recalculate the tzd based on the dateTime_ member based on the current timezone using
             *          the Standard C runtime functions. If adjust is true, then adjustForTzd() is called
             *          after the differential is calculated.
             *
             * @param   adjust  (Optional) true to adjust.
             */

            void DetermineTzd(bool adjust = false);

            /**
             * @fn  void LocalDateTime::AdjustForTzd();
             *
             * @brief   Adjust the dateTime_ member based on the tzd_ member.
             */

            void AdjustForTzd();

            /**
             * @fn  std::time_t LocalDateTime::GetDstOffset(int& dstOffset) const;
             *
             * @brief   Determine the DST offset for the current date/time.
             *
             * @param [in,out]  dstOffset   Destination offset.
             *
             * @return  The destination offset.
             */

            std::time_t GetDstOffset(int& dstOffset) const;

        private:
            DateTime dateTime_;
            int      tzd_;

            friend class DateTimeFormatter;
            friend class DateTimeParser;
        };


        //
        // inlines
        //
        inline int LocalDateTime::GetYear() const
        {
            return dateTime_.GetYear();
        }


        inline int LocalDateTime::GetMonth() const
        {
            return dateTime_.GetMonth();
        }


        inline int LocalDateTime::GetWeek(int firstDayOfWeek) const
        {
            return dateTime_.GetWeek(firstDayOfWeek);
        }


        inline int LocalDateTime::GetDay() const
        {
            return dateTime_.GetDay();
        }


        inline int LocalDateTime::GetDayOfWeek() const
        {
            return dateTime_.GetDayOfWeek();
        }


        inline int LocalDateTime::GetDayOfYear() const
        {
            return dateTime_.GetDayOfYear();
        }


        inline int LocalDateTime::GetHour() const
        {
            return dateTime_.GetHour();
        }


        inline int LocalDateTime::GetHourAMPM() const
        {
            return dateTime_.GetHourAMPM();
        }


        inline bool LocalDateTime::IsAM() const
        {
            return dateTime_.IsAM();
        }


        inline bool LocalDateTime::IsPM() const
        {
            return dateTime_.IsPM();
        }


        inline int LocalDateTime::GetMinute() const
        {
            return dateTime_.GetMinute();
        }


        inline int LocalDateTime::GetSecond() const
        {
            return dateTime_.GetSecond();
        }


        inline int LocalDateTime::GetMillisecond() const
        {
            return dateTime_.GetMillisecond();
        }


        inline int LocalDateTime::GetMicrosecond() const
        {
            return dateTime_.GetMicrosecond();
        }


        inline double LocalDateTime::GetJulianDay() const
        {
            return dateTime_.GetJulianDay();
        }


        inline int LocalDateTime::GetTimezoneDifference() const
        {
            return tzd_;
        }


        inline Timestamp LocalDateTime::GetTimestamp() const
        {
            return Timestamp::FromUtcTime(dateTime_.GetUtcTime());
        }


        inline Timestamp::UtcTimeVal LocalDateTime::GetUTCTime() const
        {
            return dateTime_.GetUtcTime() - ((Timestamp::TimeDiff) tzd_) * 10000000;
        }


        inline void LocalDateTime::AdjustForTzd()
        {
            dateTime_ += Timespan(((Timestamp::TimeDiff) tzd_)*Timespan::SECONDS);
        }


        inline void Swap(LocalDateTime& d1, LocalDateTime& d2)
        {
            d1.Swap(d2);
        }
    }
} 

#endif /* TECHNOSOFTWARE_LOCALDATETIME_H */
