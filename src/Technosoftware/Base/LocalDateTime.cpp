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

#include "Base/LocalDateTime.h"
#include "Base/Timezone.h"
#include "Base/Timespan.h"
#include "Base/Exception.h"
#include <algorithm>
#include <ctime>
#if defined(_WIN32_WCE) && _WIN32_WCE < 0x800
#include "wce_time.h"
#endif

namespace Technosoftware
{
    namespace Base
    {
        LocalDateTime::LocalDateTime()
        {
            DetermineTzd(true);
        }

        LocalDateTime::LocalDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond) :
            dateTime_(year, month, day, hour, minute, second, millisecond, microsecond)
        {
            DetermineTzd();
        }

        LocalDateTime::LocalDateTime(double julianDay) :
            dateTime_(julianDay)
        {
            DetermineTzd(true);
        }

        LocalDateTime::LocalDateTime(const DateTime& dateTime) :
            dateTime_(dateTime)
        {
            DetermineTzd(true);
        }

        LocalDateTime::LocalDateTime(const LocalDateTime& dateTime) :
            dateTime_(dateTime.dateTime_),
            tzd_(dateTime.tzd_)
        {
        }

        LocalDateTime::LocalDateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff, int tzd) :
            dateTime_(utcTime, diff),
            tzd_(tzd)
        {
            AdjustForTzd();
        }

        LocalDateTime::~LocalDateTime()
        {
        }

        LocalDateTime& LocalDateTime::operator = (const LocalDateTime& dateTime)
        {
            if (&dateTime != this)
            {
                dateTime_ = dateTime.dateTime_;
                tzd_ = dateTime.tzd_;
            }
            return *this;
        }

        LocalDateTime& LocalDateTime::operator = (const Timestamp& timestamp)
        {
            if (timestamp != this->GetTimestamp())
            {
                dateTime_ = timestamp;
                DetermineTzd(true);
            }
            return *this;
        }

        LocalDateTime& LocalDateTime::operator = (double julianDay)
        {
            dateTime_ = julianDay;
            DetermineTzd(true);
            return *this;
        }

        LocalDateTime& LocalDateTime::Assign(int year, int month, int day, int hour, int minute, int second, int millisecond, int microseconds)
        {
            dateTime_.Assign(year, month, day, hour, minute, second, millisecond, microseconds);
            DetermineTzd(false);
            return *this;
        }

        void LocalDateTime::Swap(LocalDateTime& dateTime)
        {
            dateTime_.Swap(dateTime.dateTime_);
            std::swap(tzd_, dateTime.tzd_);
        }

        DateTime LocalDateTime::GetUTC() const
        {
            return DateTime(dateTime_.GetUtcTime(), -((Timestamp::TimeDiff) tzd_)*Timespan::SECONDS);
        }

        bool LocalDateTime::operator == (const LocalDateTime& dateTime) const
        {
            return GetUTCTime() == dateTime.GetUTCTime();
        }

        bool LocalDateTime::operator != (const LocalDateTime& dateTime) const
        {
            return GetUTCTime() != dateTime.GetUTCTime();
        }

        bool LocalDateTime::operator <  (const LocalDateTime& dateTime) const
        {
            return GetUTCTime() < dateTime.GetUTCTime();
        }

        bool LocalDateTime::operator <= (const LocalDateTime& dateTime) const
        {
            return GetUTCTime() <= dateTime.GetUTCTime();
        }

        bool LocalDateTime::operator >  (const LocalDateTime& dateTime) const
        {
            return GetUTCTime() > dateTime.GetUTCTime();
        }

        bool LocalDateTime::operator >= (const LocalDateTime& dateTime) const
        {
            return GetUTCTime() >= dateTime.GetUTCTime();
        }

        LocalDateTime LocalDateTime::operator + (const Timespan& span) const
        {
            // First calculate the adjusted UTC time, then calculate the
            // locally adjusted time by constructing a new LocalDateTime.
            DateTime tmp(GetUTCTime(), span.GetTotalMicroseconds());
            return LocalDateTime(tmp);
        }

        LocalDateTime LocalDateTime::operator - (const Timespan& span) const
        {
            // First calculate the adjusted UTC time, then calculate the
            // locally adjusted time by constructing a new LocalDateTime.
            DateTime tmp(GetUTCTime(), -span.GetTotalMicroseconds());
            return LocalDateTime(tmp);
        }

        Timespan LocalDateTime::operator - (const LocalDateTime& dateTime) const
        {
            return Timespan((GetUTCTime() - dateTime.GetUTCTime()) / 10);
        }

        LocalDateTime& LocalDateTime::operator += (const Timespan& span)
        {
            // Use the same trick as in operator+. Create a UTC time, adjust
            // it for the span, and convert back to LocalDateTime. This will
            // recalculate the tzd correctly in the case where the addition
            // crosses a DST boundary.
            *this = DateTime(GetUTCTime(), span.GetTotalMicroseconds());
            return *this;
        }

        LocalDateTime& LocalDateTime::operator -= (const Timespan& span)
        {
            // Use the same trick as in operator-. Create a UTC time, adjust
            // it for the span, and convert back to LocalDateTime. This will
            // recalculate the tzd correctly in the case where the subtraction
            // crosses a DST boundary.
            *this = DateTime(GetUTCTime(), -span.GetTotalMicroseconds());
            return *this;
        }

        void LocalDateTime::DetermineTzd(bool adjust)
        {
            if (adjust)
            {
                std::time_t epochTime = dateTime_.GetTimestamp().GetEpochTime();
#if defined(_WIN32) || defined(TECHNOSOFTWARE_NO_POSIX_TSF)
#if defined(_WIN32_WCE) && _WIN32_WCE < 0x800
                std::tm* broken = wceex_localtime(&epochTime);
#else
                std::tm* broken = std::localtime(&epochTime);
#endif
                if (!broken) throw Base::SystemException("cannot get local time");
                tzd_ = (Timezone::GetUtcOffset() + ((broken->tm_isdst == 1) ? 3600 : 0));
#else
                std::tm broken;
#if defined(TECHNOSOFTWARE_VXWORKS)
                if (localtime_r(&epochTime, &broken) != OK)
                    throw Base::SystemException("cannot get local time");
#else
                if (!localtime_r(&epochTime, &broken))
                    throw Base::SystemException("cannot get local time");
#endif
                tzd_ = (Timezone::utcOffset() + ((broken.tm_isdst == 1) ? 3600 : 0));
#endif
                AdjustForTzd();
            }
            else
            {
                int dst;
                GetDstOffset(dst);
                tzd_ = (Timezone::GetUtcOffset() + dst);
            }
        }


        std::time_t LocalDateTime::GetDstOffset(int& dstOffset) const
        {
            std::time_t local;
            std::tm     broken;

            broken.tm_year = (dateTime_.GetYear() - 1900);
            broken.tm_mon = (dateTime_.GetMonth() - 1);
            broken.tm_mday = dateTime_.GetDay();
            broken.tm_hour = dateTime_.GetHour();
            broken.tm_min = dateTime_.GetMinute();
            broken.tm_sec = dateTime_.GetSecond();
            broken.tm_isdst = -1;
#if defined(_WIN32_WCE) && _WIN32_WCE < 0x800
            local = wceex_mktime(&broken);
#else
            local = std::mktime(&broken);
#endif

            dstOffset = (broken.tm_isdst == 1) ? 3600 : 0;
            return local;
        }
    }
}