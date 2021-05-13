/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Timespan class.
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

#ifndef TECHNOSOFTWARE_TIMESPAN_H
#define TECHNOSOFTWARE_TIMESPAN_H

// Technosoftware
#include "Base/Base.h"
#include "Base/Timestamp.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   Timespan
         *
         * @brief   A class that represents time spans up to microsecond resolution.
         *
         * @ingroup  BaseDateTime
         */

        class TECHNOSOFTWARE_API Timespan
        {
        public:
            typedef Timestamp::TimeDiff TimeDiff;

            /**
             * @fn  Timespan::Timespan();
             *
             * @brief   Creates a zero Timespan.
             */

            Timespan();

            /**
             * @fn  Timespan::Timespan(TimeDiff microseconds);
             *
             * @brief   Creates a Timespan.
             *
             * @param   microseconds    The microseconds.
             */

            Timespan(TimeDiff microseconds);

            /**
             * @fn  Timespan::Timespan(long seconds, long microseconds);
             *
             * @brief   Creates a Timespan. Useful for creating a Timespan from a struct timeval.
             *
             * @param   seconds         The seconds.
             * @param   microseconds    The microseconds.
             */

            Timespan(long seconds, long microseconds);

            /**
             * @fn  Timespan::Timespan(int days, int hours, int minutes, int seconds, int microSeconds);
             *
             * @brief   Creates a Timespan.
             *
             * @param   days            The days.
             * @param   hours           The hours.
             * @param   minutes         The minutes.
             * @param   seconds         The seconds.
             * @param   microSeconds    The micro in seconds.
             */

            Timespan(int days, int hours, int minutes, int seconds, int microSeconds);

            /**
             * @fn  Timespan::Timespan(const Timespan& timespan);
             *
             * @brief   Creates a Timespan from another one.
             *
             * @param   timespan    The timespan.
             */

            Timespan(const Timespan& timespan);

            /**
             * @fn  Timespan::~Timespan();
             *
             * @brief   Destroys the Timespan.
             */

            ~Timespan();

            /**
             * @fn  Timespan& Timespan::operator= (const Timespan& timespan);
             *
             * @brief   Assignment operator.
             *
             * @param   timespan    The timespan.
             *
             * @return  A shallow copy of this object.
             */

            Timespan& operator = (const Timespan& timespan);

            /**
             * @fn  Timespan& Timespan::operator= (TimeDiff microseconds);
             *
             * @brief   Assignment operator.
             *
             * @param   microseconds    The microseconds.
             *
             * @return  A shallow copy of this object.
             */

            Timespan& operator = (TimeDiff microseconds);

            /**
             * @fn  Timespan& Timespan::Assign(int days, int hours, int minutes, int seconds, int microSeconds);
             *
             * @brief   Assigns a new span.
             *
             * @param   days            The days.
             * @param   hours           The hours.
             * @param   minutes         The minutes.
             * @param   seconds         The seconds.
             * @param   microSeconds    The micro in seconds.
             *
             * @return  A reference to a Timespan.
             */

            Timespan& Assign(int days, int hours, int minutes, int seconds, int microSeconds);

            /**
             * @fn  Timespan& Timespan::Assign(long seconds, long microseconds);
             *
             * @brief   Assigns a new span. Useful for assigning from a struct timeval.
             *
             * @param   seconds         The seconds.
             * @param   microseconds    The microseconds.
             *
             * @return  A reference to a Timespan.
             */

            Timespan& Assign(long seconds, long microseconds);

            /**
             * @fn  void Timespan::Swap(Timespan& timespan);
             *
             * @brief   Swaps the Timespan with another one.
             *
             * @param [in,out]  timespan    The timespan.
             */

            void Swap(Timespan& timespan);

            bool operator == (const Timespan& ts) const;
            bool operator != (const Timespan& ts) const;
            bool operator >  (const Timespan& ts) const;
            bool operator >= (const Timespan& ts) const;
            bool operator <  (const Timespan& ts) const;
            bool operator <= (const Timespan& ts) const;

            bool operator == (TimeDiff microSeconds) const;
            bool operator != (TimeDiff microSeconds) const;
            bool operator >  (TimeDiff microSeconds) const;
            bool operator >= (TimeDiff microSeconds) const;
            bool operator <  (TimeDiff microSeconds) const;
            bool operator <= (TimeDiff microSeconds) const;

            Timespan operator + (const Timespan& d) const;
            Timespan operator - (const Timespan& d) const;
            Timespan& operator += (const Timespan& d);
            Timespan& operator -= (const Timespan& d);

            Timespan operator + (TimeDiff microSeconds) const;
            Timespan operator - (TimeDiff microSeconds) const;
            Timespan& operator += (TimeDiff microSeconds);
            Timespan& operator -= (TimeDiff microSeconds);

            /**
             * @fn  int Timespan::GetDays() const;
             *
             * @brief   Returns the number of days.
             *
             * @return  The days.
             */

            int GetDays() const;

            /**
             * @fn  int Timespan::GetHours() const;
             *
             * @brief   Returns the number of hours (0 to 23).
             *
             * @return  The hours.
             */

            int GetHours() const;

            /**
             * @fn  int Timespan::GetTotalHours() const;
             *
             * @brief   Returns the total number of hours.
             *
             * @return  The total hours.
             */

            int GetTotalHours() const;

            /**
             * @fn  int Timespan::GetMinutes() const;
             *
             * @brief   Returns the number of minutes (0 to 59).
             *
             * @return  The minutes.
             */

            int GetMinutes() const;

            /**
             * @fn  int Timespan::GetTotalMinutes() const;
             *
             * @brief   Returns the total number of minutes.
             *
             * @return  The total minutes.
             */

            int GetTotalMinutes() const;

            /**
             * @fn  int Timespan::GetSeconds() const;
             *
             * @brief   Returns the number of seconds (0 to 59).
             *
             * @return  The seconds.
             */

            int GetSeconds() const;

            /**
             * @fn  int Timespan::GetTotalSeconds() const;
             *
             * @brief   Returns the total number of seconds.
             *
             * @return  The total seconds.
             */

            int GetTotalSeconds() const;

            /**
             * @fn  int Timespan::GetMilliseconds() const;
             *
             * @brief   Returns the number of milliseconds (0 to 999).
             *
             * @return  The milliseconds.
             */

            int GetMilliseconds() const;

            /**
             * @fn  TimeDiff Timespan::GetTotalMilliseconds() const;
             *
             * @brief   Returns the total number of milliseconds.
             *
             * @return  The total milliseconds.
             */

            TimeDiff GetTotalMilliseconds() const;

            /**
             * @fn  int Timespan::GetMicroseconds() const;
             *
             * @brief   Returns the fractions of a millisecond in microseconds (0 to 999).
             *
             * @return  The microseconds.
             */

            int GetMicroseconds() const;

            /**
             * @fn  int Timespan::GetFractionsOfSeconds() const;
             *
             * @brief   Returns the fractions of a second in microseconds (0 to 999999).
             *
             * @return  The fractions of seconds.
             */

            int GetFractionsOfSeconds() const;

            /**
             * @fn  TimeDiff Timespan::GetTotalMicroseconds() const;
             *
             * @brief   Returns the total number of microseconds.
             *
             * @return  The total microseconds.
             */

            TimeDiff GetTotalMicroseconds() const;

            /** @brief   The number of microseconds in a millisecond. */
            static const TimeDiff MILLISECONDS;
            /** @brief   The number of microseconds in a second. */
            static const TimeDiff SECONDS;
            /** @brief   The number of microseconds in a minute. */
            static const TimeDiff MINUTES;
            /** @brief   The number of microseconds in a hour. */
            static const TimeDiff HOURS;
            /** @brief   The number of microseconds in a day. */
            static const TimeDiff DAYS;

        private:
            TimeDiff _span;
        };


        //
        // inlines
        //
        inline int Timespan::GetDays() const
        {
            return int(_span / DAYS);
        }


        inline int Timespan::GetHours() const
        {
            return int((_span / HOURS) % 24);
        }


        inline int Timespan::GetTotalHours() const
        {
            return int(_span / HOURS);
        }


        inline int Timespan::GetMinutes() const
        {
            return int((_span / MINUTES) % 60);
        }


        inline int Timespan::GetTotalMinutes() const
        {
            return int(_span / MINUTES);
        }


        inline int Timespan::GetSeconds() const
        {
            return int((_span / SECONDS) % 60);
        }


        inline int Timespan::GetTotalSeconds() const
        {
            return int(_span / SECONDS);
        }


        inline int Timespan::GetMilliseconds() const
        {
            return int((_span / MILLISECONDS) % 1000);
        }


        inline Timespan::TimeDiff Timespan::GetTotalMilliseconds() const
        {
            return _span / MILLISECONDS;
        }


        inline int Timespan::GetMicroseconds() const
        {
            return int(_span % 1000);
        }


        inline int Timespan::GetFractionsOfSeconds() const
        {
            return int(_span % 1000000);
        }


        inline Timespan::TimeDiff Timespan::GetTotalMicroseconds() const
        {
            return _span;
        }


        inline bool Timespan::operator == (const Timespan& ts) const
        {
            return _span == ts._span;
        }


        inline bool Timespan::operator != (const Timespan& ts) const
        {
            return _span != ts._span;
        }


        inline bool Timespan::operator >  (const Timespan& ts) const
        {
            return _span > ts._span;
        }


        inline bool Timespan::operator >= (const Timespan& ts) const
        {
            return _span >= ts._span;
        }


        inline bool Timespan::operator <  (const Timespan& ts) const
        {
            return _span < ts._span;
        }


        inline bool Timespan::operator <= (const Timespan& ts) const
        {
            return _span <= ts._span;
        }


        inline bool Timespan::operator == (TimeDiff microSeconds) const
        {
            return _span == microSeconds;
        }


        inline bool Timespan::operator != (TimeDiff microSeconds) const
        {
            return _span != microSeconds;
        }


        inline bool Timespan::operator >  (TimeDiff microSeconds) const
        {
            return _span > microSeconds;
        }


        inline bool Timespan::operator >= (TimeDiff microSeconds) const
        {
            return _span >= microSeconds;
        }


        inline bool Timespan::operator <  (TimeDiff microSeconds) const
        {
            return _span < microSeconds;
        }


        inline bool Timespan::operator <= (TimeDiff microSeconds) const
        {
            return _span <= microSeconds;
        }


        inline void swap(Timespan& s1, Timespan& s2)
        {
            s1.Swap(s2);
        }

inline Timespan::~Timespan()
{
}
    }
}

#endif /* TECHNOSOFTWARE_TIMESPAN_H */
