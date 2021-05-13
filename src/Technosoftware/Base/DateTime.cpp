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

#include "Base/DateTime.h"
#include "Base/Timespan.h"
#include <algorithm>
#include <cmath>

namespace Technosoftware
{
    namespace Base
    {


        inline double DateTime::ToJulianDay(Timestamp::UtcTimeVal utcTime)
        {
            double utcDays = double(utcTime) / 864000000000.0;
            return utcDays + 2299160.5; // first day of Gregorian reform (Oct 15 1582)
        }


        inline Timestamp::UtcTimeVal DateTime::ToUtcTime(double GetJulianDay)
        {
            return Timestamp::UtcTimeVal((GetJulianDay - 2299160.5)*864000000000.0);
        }


        DateTime::DateTime()
        {
            Timestamp now;
            utcTime_ = now.GetUtcTime();
            ComputeGregorian(GetJulianDay());
            ComputeDaytime();
        }


        DateTime::DateTime(const Timestamp& timestamp) :
            utcTime_(timestamp.GetUtcTime())
        {
            ComputeGregorian(GetJulianDay());
            ComputeDaytime();
        }


        DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond) :
            year_(year),
            month_(month),
            day_(day),
            hour_(hour),
            minute_(minute),
            second_(second),
            millisecond_(millisecond),
            microsecond_(microsecond)
        {
            technosoftware_assert(year >= 0 && year <= 9999);
            technosoftware_assert(month >= 1 && month <= 12);
            technosoftware_assert(day >= 1 && day <= GetDaysOfMonth(year, month));
            technosoftware_assert(hour >= 0 && hour <= 23);
            technosoftware_assert(minute >= 0 && minute <= 59);
            technosoftware_assert(second >= 0 && second <= 60); // allow leap seconds
            technosoftware_assert(millisecond >= 0 && millisecond <= 999);
            technosoftware_assert(microsecond >= 0 && microsecond <= 999);

            utcTime_ = ToUtcTime(ToJulianDay(year, month, day)) + 10 * (hour*Timespan::HOURS + minute*Timespan::MINUTES + second*Timespan::SECONDS + millisecond*Timespan::MILLISECONDS + microsecond);
        }


        DateTime::DateTime(double GetJulianDay) :
            utcTime_(ToUtcTime(GetJulianDay))
        {
            ComputeGregorian(GetJulianDay);
        }


        DateTime::DateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff) :
            utcTime_(utcTime + diff * 10)
        {
            ComputeGregorian(GetJulianDay());
            ComputeDaytime();
        }


        DateTime::DateTime(const DateTime& dateTime) :
            utcTime_(dateTime.utcTime_),
            year_(dateTime.year_),
            month_(dateTime.month_),
            day_(dateTime.day_),
            hour_(dateTime.hour_),
            minute_(dateTime.minute_),
            second_(dateTime.second_),
            millisecond_(dateTime.millisecond_),
            microsecond_(dateTime.microsecond_)
        {
        }


        DateTime::~DateTime()
        {
        }


        DateTime& DateTime::operator = (const DateTime& dateTime)
        {
            if (&dateTime != this)
            {
                utcTime_ = dateTime.utcTime_;
                year_ = dateTime.year_;
                month_ = dateTime.month_;
                day_ = dateTime.day_;
                hour_ = dateTime.hour_;
                minute_ = dateTime.minute_;
                second_ = dateTime.second_;
                millisecond_ = dateTime.millisecond_;
                microsecond_ = dateTime.microsecond_;
            }
            return *this;
        }


        DateTime& DateTime::operator = (const Timestamp& timestamp)
        {
            utcTime_ = timestamp.GetUtcTime();
            ComputeGregorian(GetJulianDay());
            ComputeDaytime();
            return *this;
        }


        DateTime& DateTime::operator = (double GetJulianDay)
        {
            utcTime_ = ToUtcTime(GetJulianDay);
            ComputeGregorian(GetJulianDay);
            return *this;
        }


        DateTime& DateTime::Assign(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
        {
            technosoftware_assert(year >= 0 && year <= 9999);
            technosoftware_assert(month >= 1 && month <= 12);
            technosoftware_assert(day >= 1 && day <= GetDaysOfMonth(year, month));
            technosoftware_assert(hour >= 0 && hour <= 23);
            technosoftware_assert(minute >= 0 && minute <= 59);
            technosoftware_assert(second >= 0 && second <= 60); // allow leap seconds
            technosoftware_assert(millisecond >= 0 && millisecond <= 999);
            technosoftware_assert(microsecond >= 0 && microsecond <= 999);

            utcTime_ = ToUtcTime(ToJulianDay(year, month, day)) + 10 * (hour*Timespan::HOURS + minute*Timespan::MINUTES + second*Timespan::SECONDS + millisecond*Timespan::MILLISECONDS + microsecond);
            year_ = year;
            month_ = month;
            day_ = day;
            hour_ = hour;
            minute_ = minute;
            second_ = second;
            millisecond_ = millisecond;
            microsecond_ = microsecond;

            return *this;
        }


        void DateTime::Swap(DateTime& dateTime)
        {
            std::swap(utcTime_, dateTime.utcTime_);
            std::swap(year_, dateTime.year_);
            std::swap(month_, dateTime.month_);
            std::swap(day_, dateTime.day_);
            std::swap(hour_, dateTime.hour_);
            std::swap(minute_, dateTime.minute_);
            std::swap(second_, dateTime.second_);
            std::swap(millisecond_, dateTime.millisecond_);
            std::swap(microsecond_, dateTime.microsecond_);
        }


        int DateTime::GetDayOfWeek() const
        {
            return int((std::floor(GetJulianDay() + 1.5))) % 7;
        }


        int DateTime::GetDayOfYear() const
        {
            int doy = 0;
            for (int month = 1; month < month_; ++month)
                doy += GetDaysOfMonth(year_, month);
            doy += day_;
            return doy;
        }


        int DateTime::GetDaysOfMonth(int year, int month)
        {
            technosoftware_assert(month >= 1 && month <= 12);

            static int daysOfMonthTable[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            if (month == 2 && IsLeapYear(year))
                return 29;
            else
                return daysOfMonthTable[month];
        }


        bool DateTime::IsValid(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
        {
            return
                (year >= 0 && year <= 9999) &&
                (month >= 1 && month <= 12) &&
                (day >= 1 && day <= GetDaysOfMonth(year, month)) &&
                (hour >= 0 && hour <= 23) &&
                (minute >= 0 && minute <= 59) &&
                (second >= 0 && second <= 60) &&
                (millisecond >= 0 && millisecond <= 999) &&
                (microsecond >= 0 && microsecond <= 999);
        }


        int DateTime::GetWeek(int firstDayOfWeek) const
        {
            technosoftware_assert(firstDayOfWeek >= 0 && firstDayOfWeek <= 6);

            /// find the first firstDayOfWeek.
            int baseDay = 1;
            while (DateTime(year_, 1, baseDay).GetDayOfWeek() != firstDayOfWeek) ++baseDay;

            int doy = GetDayOfYear();
            int offs = baseDay <= 4 ? 0 : 1;
            if (doy < baseDay)
                return offs;
            else
                return (doy - baseDay) / 7 + 1 + offs;
        }


        double DateTime::GetJulianDay() const
        {
            return ToJulianDay(utcTime_);
        }


        DateTime DateTime::operator + (const Timespan& span) const
        {
            return DateTime(utcTime_, span.GetTotalMicroseconds());
        }


        DateTime DateTime::operator - (const Timespan& span) const
        {
            return DateTime(utcTime_, -span.GetTotalMicroseconds());
        }


        Timespan DateTime::operator - (const DateTime& dateTime) const
        {
            return Timespan((utcTime_ - dateTime.utcTime_) / 10);
        }


        DateTime& DateTime::operator += (const Timespan& span)
        {
            utcTime_ += span.GetTotalMicroseconds() * 10;
            ComputeGregorian(GetJulianDay());
            ComputeDaytime();
            return *this;
        }


        DateTime& DateTime::operator -= (const Timespan& span)
        {
            utcTime_ -= span.GetTotalMicroseconds() * 10;
            ComputeGregorian(GetJulianDay());
            ComputeDaytime();
            return *this;
        }


        void DateTime::MakeUtc(int tzd)
        {
            operator -= (Timespan(((Timestamp::TimeDiff) tzd)*Timespan::SECONDS));
        }


        void DateTime::MakeLocal(int tzd)
        {
            operator += (Timespan(((Timestamp::TimeDiff) tzd)*Timespan::SECONDS));
        }


        double DateTime::ToJulianDay(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
        {
            // lookup table for (153*month - 457)/5 - note that 3 <= month <= 14.
            static int lookup[] = { -91, -60, -30, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337 };

            // day to double
            double dday = double(day) + ((double((hour * 60 + minute) * 60 + second) * 1000 + millisecond) * 1000 + microsecond) / 86400000000.0;
            if (month < 3)
            {
                month += 12;
                --year;
            }
            double dyear = double(year);
            return dday + lookup[month] + 365 * year + std::floor(dyear / 4) - std::floor(dyear / 100) + std::floor(dyear / 400) + 1721118.5;
        }


        void DateTime::CheckLimit(short& lower, short& higher, short limit)
        {
            if (lower >= limit)
            {
                higher += short(lower / limit);
                lower = short(lower % limit);
            }
        }


        void DateTime::Normalize()
        {
            CheckLimit(microsecond_, millisecond_, 1000);
            CheckLimit(millisecond_, second_, 1000);
            CheckLimit(second_, minute_, 60);
            CheckLimit(minute_, hour_, 60);
            CheckLimit(hour_, day_, 24);

            if (day_ > GetDaysOfMonth(year_, month_))
            {
                day_ -= GetDaysOfMonth(year_, month_);
                if (++month_ > 12)
                {
                    ++year_;
                    month_ -= 12;
                }
            }
        }


        void DateTime::ComputeGregorian(double GetJulianDay)
        {
            double z = std::floor(GetJulianDay - 1721118.5);
            double r = GetJulianDay - 1721118.5 - z;
            double g = z - 0.25;
            double a = std::floor(g / 36524.25);
            double b = a - std::floor(a / 4);
            year_ = short(std::floor((b + g) / 365.25));
            double c = b + z - std::floor(365.25*year_);
            month_ = short(std::floor((5 * c + 456) / 153));
            double dday = c - std::floor((153.0*month_ - 457) / 5) + r;
            day_ = short(dday);
            if (month_ > 12)
            {
                ++year_;
                month_ -= 12;
            }
            r *= 24;
            hour_ = short(std::floor(r));
            r -= std::floor(r);
            r *= 60;
            minute_ = short(std::floor(r));
            r -= std::floor(r);
            r *= 60;
            second_ = short(std::floor(r));
            r -= std::floor(r);
            r *= 1000;
            millisecond_ = short(std::floor(r));
            r -= std::floor(r);
            r *= 1000;
            microsecond_ = short(r + 0.5);

            Normalize();

            technosoftware_assert_dbg(month_ >= 1 && month_ <= 12);
            technosoftware_assert_dbg(day_ >= 1 && day_ <= GetDaysOfMonth(year_, month_));
            technosoftware_assert_dbg(hour_ >= 0 && hour_ <= 23);
            technosoftware_assert_dbg(minute_ >= 0 && minute_ <= 59);
            technosoftware_assert_dbg(second_ >= 0 && second_ <= 59);
            technosoftware_assert_dbg(millisecond_ >= 0 && millisecond_ <= 999);
            technosoftware_assert_dbg(microsecond_ >= 0 && microsecond_ <= 999);
        }


        void DateTime::ComputeDaytime()
        {
            Timespan span(utcTime_ / 10);
            int hour = span.GetHours();
            // Due to double rounding issues, the previous call to ComputeGregorian()
            // may have crossed into the next or previous day. We need to correct that.
            if (hour == 23 && hour_ == 0)
            {
                day_--;
                if (day_ == 0)
                {
                    month_--;
                    if (month_ == 0)
                    {
                        month_ = 12;
                        year_--;
                    }
                    day_ = GetDaysOfMonth(year_, month_);
                }
            }
            else if (hour == 0 && hour_ == 23)
            {
                day_++;
                if (day_ > GetDaysOfMonth(year_, month_))
                {
                    month_++;
                    if (month_ > 12)
                    {
                        month_ = 1;
                        year_++;
                    }
                    day_ = 1;
                }
            }
            hour_ = hour;
            minute_ = span.GetMinutes();
            second_ = span.GetSeconds();
            millisecond_ = span.GetMilliseconds();
            microsecond_ = span.GetMicroseconds();
        }

    }
}
