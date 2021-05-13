/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
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


#include "Base/Timespan.h"
#include <algorithm>


namespace Technosoftware
{
    namespace Base
    {


        const Timespan::TimeDiff Timespan::MILLISECONDS = 1000;
        const Timespan::TimeDiff Timespan::SECONDS = 1000 * Timespan::MILLISECONDS;
        const Timespan::TimeDiff Timespan::MINUTES = 60 * Timespan::SECONDS;
        const Timespan::TimeDiff Timespan::HOURS = 60 * Timespan::MINUTES;
        const Timespan::TimeDiff Timespan::DAYS = 24 * Timespan::HOURS;


        Timespan::Timespan() :
            _span(0)
        {
        }


        Timespan::Timespan(TimeDiff microSeconds) :
            _span(microSeconds)
        {
        }


        Timespan::Timespan(long seconds, long microSeconds) :
            _span(TimeDiff(seconds)*SECONDS + microSeconds)
        {
        }


        Timespan::Timespan(int days, int hours, int minutes, int seconds, int microSeconds) :
            _span(TimeDiff(microSeconds) + TimeDiff(seconds)*SECONDS + TimeDiff(minutes)*MINUTES + TimeDiff(hours)*HOURS + TimeDiff(days)*DAYS)
        {
        }


        Timespan::Timespan(const Timespan& timespan) :
            _span(timespan._span)
        {
        }


        Timespan& Timespan::operator = (const Timespan& timespan)
        {
            _span = timespan._span;
            return *this;
        }


        Timespan& Timespan::operator = (TimeDiff microSeconds)
        {
            _span = microSeconds;
            return *this;
        }


        Timespan& Timespan::Assign(int days, int hours, int minutes, int seconds, int microSeconds)
        {
            _span = TimeDiff(microSeconds) + TimeDiff(seconds)*SECONDS + TimeDiff(minutes)*MINUTES + TimeDiff(hours)*HOURS + TimeDiff(days)*DAYS;
            return *this;
        }


        Timespan& Timespan::Assign(long seconds, long microSeconds)
        {
            _span = TimeDiff(seconds)*SECONDS + TimeDiff(microSeconds);
            return *this;
        }


        void Timespan::Swap(Timespan& timespan)
        {
            std::swap(_span, timespan._span);
        }


        Timespan Timespan::operator + (const Timespan& d) const
        {
            return Timespan(_span + d._span);
        }


        Timespan Timespan::operator - (const Timespan& d) const
        {
            return Timespan(_span - d._span);
        }


        Timespan& Timespan::operator += (const Timespan& d)
        {
            _span += d._span;
            return *this;
        }


        Timespan& Timespan::operator -= (const Timespan& d)
        {
            _span -= d._span;
            return *this;
        }


        Timespan Timespan::operator + (TimeDiff microSeconds) const
        {
            return Timespan(_span + microSeconds);
        }


        Timespan Timespan::operator - (TimeDiff microSeconds) const
        {
            return Timespan(_span - microSeconds);
        }


        Timespan& Timespan::operator += (TimeDiff microSeconds)
        {
            _span += microSeconds;
            return *this;
        }


        Timespan& Timespan::operator -= (TimeDiff microSeconds)
        {
            _span -= microSeconds;
            return *this;
        }
    }

}
