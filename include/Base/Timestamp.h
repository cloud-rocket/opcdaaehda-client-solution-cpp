/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Timestamp class.
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

#ifndef TECHNOSOFTWARE_TIMESTAMP_H
#define TECHNOSOFTWARE_TIMESTAMP_H

// STD
#include <ctime>

// Technosoftware
#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        class Timespan;

        /**
         * @class   Timestamp
         *
         * @brief   A Timestamp stores a monotonic* time value with (theoretical) microseconds
         *          resolution. Timestamps can be compared with each other and simple arithmetics are
         *          supported. [*] Note that Timestamp values are only monotonic as long as the systems's
         *          clock is monotonic as well (and not, e.g. set back due to time synchronization or
         *          other reasons). Timestamps are UTC (Coordinated Universal Time)    based and thus
         *          independent of the timezone in effect on the system. The internal reference time is
         *          the Unix epoch, midnight, January 1, 1970.
         *
         * @ingroup  BaseDateTime
         */

        class TECHNOSOFTWARE_API Timestamp
        {
        public:

            /**
             * @typedef int64_t TimeVal
             *
             * @brief   Monotonic UTC time value in microsecond resolution, with base time midnight, January
             *          1, 1970.
             */

            typedef int64_t TimeVal;

            /**
             * @typedef int64_t UtcTimeVal
             *
             * @brief   Monotonic UTC time value in 100 nanosecond resolution, with base time midnight,
             *          October 15, 1582.
             */

            typedef int64_t UtcTimeVal;

            /**
             * @typedef int64_t TimeDiff
             *
             * @brief   Difference between two TimeVal values in microseconds.
             */

            typedef int64_t TimeDiff;

            /** @brief   Minimum timestamp value. */
            static const TimeVal TIMEVAL_MIN; 

            /** @brief   Maximum timestamp value. */
            static const TimeVal TIMEVAL_MAX; 

            /**
             * @fn  Timestamp::Timestamp();
             *
             * @brief   Creates a timestamp with the current time.
             */

            Timestamp();

            /**
             * @fn  Timestamp::Timestamp(TimeVal tv);
             *
             * @brief   Creates a timestamp from the given time value (microseconds since midnight, January 1,
             *          1970).
             *
             * @param   tv  The TimeVal.
             */

            Timestamp(TimeVal tv);

            /**
             * @fn  Timestamp::Timestamp(const Timestamp& other);
             *
             * @brief   Copy constructor.
             *
             * @param   other   The other.
             */

            Timestamp(const Timestamp& other);

            /**
             * @fn  Timestamp::~Timestamp();
             *
             * @brief   Destroys the timestamp.
             */

            ~Timestamp();

            /**
             * @fn  Timestamp& Timestamp::operator= (const Timestamp& other);
             *
             * @brief   Assignment operator.
             *
             * @param   other   The other TimeStamp.
             *
             * @return  A shallow copy of this object.
             */

            Timestamp& operator = (const Timestamp& other);

            /**
             * @fn  Timestamp& Timestamp::operator= (TimeVal tv);
             *
             * @brief   Assignment operator.
             *
             * @param   tv  The TimeVal.
             *
             * @return  A shallow copy of this object.
             */

            Timestamp& operator = (TimeVal tv);

            /**
             * @fn  void Timestamp::Swap(Timestamp& timestamp);
             *
             * @brief   Swaps the Timestamp with another one.
             *
             * @param [in,out]  timestamp   The timestamp.
             */

            void Swap(Timestamp& timestamp);

            /**
             * @fn  void Timestamp::Update();
             *
             * @brief   Updates the Timestamp with the current time.
             */

            void Update();

            /**
             * @fn  bool Timestamp::operator== (const Timestamp& ts) const;
             *
             * @brief   Equality operator.
             *
             * @param   ts  The Timestamp.
             *
             * @return  true if the parameters are considered equivalent.
             */

            bool operator == (const Timestamp& ts) const;

            /**
             * @fn  bool Timestamp::operator!= (const Timestamp& ts) const;
             *
             * @brief   Inequality operator.
             *
             * @param   ts  The Timestamp.
             *
             * @return  true if the parameters are not considered equivalent.
             */

            bool operator != (const Timestamp& ts) const;

            /**
             * @fn  bool Timestamp::operator> (const Timestamp& ts) const;
             *
             * @brief   Greater-than comparison operator.
             *
             * @param   ts  The Timestamp.
             *
             * @return  true if the first parameter is greater than to the second.
             */

            bool operator >  (const Timestamp& ts) const;

            /**
             * @fn  bool Timestamp::operator>= (const Timestamp& ts) const;
             *
             * @brief   Greater-than-or-equal comparison operator.
             *
             * @param   ts  The Timestamp.
             *
             * @return  true if the first parameter is greater than or equal to the second.
             */

            bool operator >= (const Timestamp& ts) const;

            /**
             * @fn  bool Timestamp::operator< (const Timestamp& ts) const;
             *
             * @brief   Less-than comparison operator.
             *
             * @param   ts  The Timestamp.
             *
             * @return  true if the first parameter is less than the second.
             */

            bool operator <  (const Timestamp& ts) const;

            /**
             * @fn  bool Timestamp::operator<= (const Timestamp& ts) const;
             *
             * @brief   Less-than-or-equal comparison operator.
             *
             * @param   ts  The Timestamp.
             *
             * @return  true if the first parameter is less than or equal to the second.
             */

            bool operator <= (const Timestamp& ts) const;

            Timestamp  operator +  (TimeDiff d) const;
            Timestamp  operator +  (const Timespan& span) const;
            Timestamp  operator -  (TimeDiff d) const;
            Timestamp  operator -  (const Timespan& span) const;
            TimeDiff   operator -  (const Timestamp& ts) const;
            Timestamp& operator += (TimeDiff d);
            Timestamp& operator += (const Timespan& span);
            Timestamp& operator -= (TimeDiff d);
            Timestamp& operator -= (const Timespan& span);

            /**
             * @fn  std::time_t Timestamp::GetEpochTime() const;
             *
             * @brief   Returns the timestamp expressed in time_t. time_t base time is midnight, January 1,
             *          1970. Resolution is one second.
             *
             * @return  The epoch time.
             */

            std::time_t GetEpochTime() const;

            /**
             * @fn  UtcTimeVal Timestamp::GetUtcTime() const;
             *
             * @brief   Returns the timestamp expressed in UTC-based time. UTC base time is midnight, October
             *          15, 1582. Resolution is 100 nanoseconds.
             *
             * @return  The UTC time.
             */

            UtcTimeVal GetUtcTime() const;

            /**
             * @fn  TimeVal Timestamp::GetEpochMicroseconds() const;
             *
             * @brief   Returns the timestamp expressed in microseconds since the Unix epoch, midnight,
             *          January 1, 1970.
             *
             * @return  The epoch microseconds.
             */

            TimeVal GetEpochMicroseconds() const;

            /**
             * @fn  TimeDiff Timestamp::GetElapsed() const;
             *
             * @brief   Returns the time elapsed since the time denoted by the timestamp. Equivalent to
             *          Timestamp() - *this.
             *
             * @return  The elapsed.
             */

            TimeDiff GetElapsed() const;

            /**
             * @fn  bool Timestamp::IsElapsed(TimeDiff interval) const;
             *
             * @brief   Returns true iff the given interval has passed since the time denoted by the
             *          timestamp.
             *
             * @param   interval    The interval.
             *
             * @return  true if elapsed, false if not.
             */

            bool IsElapsed(TimeDiff interval) const;

            /**
             * @fn  TimeVal Timestamp::GetRaw() const;
             *
             * @brief   Returns the raw time value.
             *          
             *            Same as GetEpochMicroseconds().
             *
             * @return  The raw.
             */

            TimeVal GetRaw() const;

            /**
             * @fn  static Timestamp Timestamp::FromEpochTime(std::time_t t);
             *
             * @brief   Creates a timestamp from a std::time_t.
             *
             * @param   t   The std::time_t to process.
             *
             * @return  A Timestamp.
             */

            static Timestamp FromEpochTime(std::time_t t);

            /**
             * @fn  static Timestamp Timestamp::FromUtcTime(UtcTimeVal val);
             *
             * @brief   Creates a timestamp from a UTC time value (100 nanosecond intervals since midnight,
             *          October 15, 1582).
             *
             * @param   val The value.
             *
             * @return  A Timestamp.
             */

            static Timestamp FromUtcTime(UtcTimeVal val);

            /**
             * @fn  static TimeDiff Timestamp::GetResolution();
             *
             * @brief   Returns the resolution in units per second. Since the timestamp has microsecond
             *          resolution, the returned value is always 1000000.
             *
             * @return  The resolution.
             */

            static TimeDiff GetResolution();

#if defined(_WIN32)

            /**
             * @fn  static Timestamp Timestamp::FromFileTime(DWORD fileTimeLow, DWORD fileTimeHigh);
             *
             * @brief   Creates a timestamp from a FILETIME time value.
             *
             * @param   fileTimeLow     The file time low.
             * @param   fileTimeHigh    The file time high.
             *
             * @return  A Timestamp.
             */

            static Timestamp FromFileTime(DWORD fileTimeLow, DWORD fileTimeHigh);

            /**
             * @fn  void Timestamp::FromFileTime(DWORD& fileTimeLow, DWORD& fileTimeHigh) const;
             *
             * @brief   Converts the timestamp to a FILETIME value.
             *
             * @param [in,out]  fileTimeLow     The file time low.
             * @param [in,out]  fileTimeHigh    The file time high.
             */

            void ToFileTime(DWORD& fileTimeLow, DWORD& fileTimeHigh) const;
#endif

        private:
            TimeVal ts_;
        };


        //
        // inlines
        //
        inline bool Timestamp::operator == (const Timestamp& ts) const
        {
            return ts_ == ts.ts_;
        }


        inline bool Timestamp::operator != (const Timestamp& ts) const
        {
            return ts_ != ts.ts_;
        }


        inline bool Timestamp::operator >  (const Timestamp& ts) const
        {
            return ts_ > ts.ts_;
        }


        inline bool Timestamp::operator >= (const Timestamp& ts) const
        {
            return ts_ >= ts.ts_;
        }


        inline bool Timestamp::operator <  (const Timestamp& ts) const
        {
            return ts_ < ts.ts_;
        }


        inline bool Timestamp::operator <= (const Timestamp& ts) const
        {
            return ts_ <= ts.ts_;
        }


        inline Timestamp Timestamp::operator + (Timestamp::TimeDiff d) const
        {
            return Timestamp(ts_ + d);
        }


        inline Timestamp Timestamp::operator - (Timestamp::TimeDiff d) const
        {
            return Timestamp(ts_ - d);
        }


        inline Timestamp::TimeDiff Timestamp::operator - (const Timestamp& ts) const
        {
            return ts_ - ts.ts_;
        }


        inline Timestamp& Timestamp::operator += (Timestamp::TimeDiff d)
        {
            ts_ += d;
            return *this;
        }


        inline Timestamp& Timestamp::operator -= (Timestamp::TimeDiff d)
        {
            ts_ -= d;
            return *this;
        }


        inline std::time_t Timestamp::GetEpochTime() const
        {
            return std::time_t(ts_ / GetResolution());
        }


        inline Timestamp::UtcTimeVal Timestamp::GetUtcTime() const
        {
            return ts_ * 10 + (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
        }


        inline Timestamp::TimeVal Timestamp::GetEpochMicroseconds() const
        {
            return ts_;
        }


        inline Timestamp::TimeDiff Timestamp::GetElapsed() const
        {
            Timestamp now;
            return now - *this;
        }


        inline bool Timestamp::IsElapsed(Timestamp::TimeDiff interval) const
        {
            Timestamp now;
            Timestamp::TimeDiff diff = now - *this;
            return diff >= interval;
        }


        inline Timestamp::TimeDiff Timestamp::GetResolution()
        {
            return 1000000;
        }


        inline void Swap(Timestamp& s1, Timestamp& s2)
        {
            s1.Swap(s2);
        }


        inline Timestamp::TimeVal Timestamp::GetRaw() const
        {
            return ts_;
        }
    }
}

#endif /* TECHNOSOFTWARE_TIMESTAMP_H */
