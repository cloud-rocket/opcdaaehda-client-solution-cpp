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


#include "Base/Timestamp.h"
#include "Base/Timespan.h"
#include <algorithm>
#undef min
#undef max
#include <limits>
#if defined(TECHNOSOFTWARE_OS_FAMILY_UNIX)
#include <time.h>
#include <unistd.h>
#if defined(TECHNOSOFTWARE_VXWORKS)
#include <timers.h>
#else
#include <sys/time.h>
#include <sys/times.h>
#endif
#elif defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#include "Base/UnWindows.h"
#if defined(_WIN32_WCE)
#include <cmath>
#endif
#endif


#ifndef POCO_HAVE_CLOCK_GETTIME
	#if (defined(_POSIX_TIMERS) && defined(CLOCK_REALTIME)) || defined(POCO_VXWORKS) || defined(__QNX__)
		#ifndef __APPLE__ // See GitHub issue #1453 - not available before Mac OS 10.12/iOS 10
			#define TECHNOSOFTWARE_HAVE_CLOCK_GETTIME
		#endif
	#endif
#endif


#if defined(_WIN32_WCE) && defined(TECHNOSOFTWARE_WINCE_TIMESTAMP_HACK)


 //
 // See <http://community.opennetcf.com/articles/cf/archive/2007/11/20/getting-a-millisecond-resolution-datetime-under-windows-ce.aspx>
 // for an explanation of the following code.
 //
 // In short: Windows CE system time in most cases only has a resolution of one second.
 // But we want millisecond resolution.
 //


namespace {


    class TickOffset
    {
    public:
        TickOffset()
        {
            SYSTEMTIME st1, st2;
            std::memset(&st1, 0, sizeof(SYSTEMTIME));
            std::memset(&st2, 0, sizeof(SYSTEMTIME));
            GetSystemTime(&st1);
            while (true)
            {
                GetSystemTime(&st2);

                // wait for a rollover
                if (st1.wSecond != st2.wSecond)
                {
                    _offset = GetTickCount() % 1000;
                    break;
                }
            }
        }

        void calibrate(int seconds)
        {
            SYSTEMTIME st1, st2;
            systemTime(&st1);

            WORD s = st1.wSecond;
            int sum = 0;
            int remaining = seconds;
            while (remaining > 0)
            {
                systemTime(&st2);
                WORD s2 = st2.wSecond;

                if (s != s2)
                {
                    remaining--;
                    // store the offset from zero
                    sum += (st2.wMilliseconds > 500) ? (st2.wMilliseconds - 1000) : st2.wMilliseconds;
                    s = st2.wSecond;
                }
            }

            // adjust the offset by the average deviation from zero (round to the integer farthest from zero)
            if (sum < 0)
                _offset += (int)std::floor(sum / (float)seconds);
            else
                _offset += (int)std::ceil(sum / (float)seconds);
        }

        void systemTime(SYSTEMTIME* pST)
        {
            std::memset(pST, 0, sizeof(SYSTEMTIME));

            WORD tick = GetTickCount() % 1000;
            GetSystemTime(pST);
            WORD ms = (tick >= _offset) ? (tick - _offset) : (1000 - (_offset - tick));
            pST->wMilliseconds = ms;
        }

        void systemTimeAsFileTime(FILETIME* pFT)
        {
            SYSTEMTIME st;
            systemTime(&st);
            SystemTimeToFileTime(&st, pFT);
        }

    private:
        WORD _offset;
    };


    static TickOffset offset;


    void GetSystemTimeAsFileTimeWithMillisecondResolution(FILETIME* pFT)
    {
        offset.systemTimeAsFileTime(pFT);
    }


} // namespace


#endif // defined(_WIN32_WCE) && defined(TECHNOSOFTWARE_WINCE_TIMESTAMP_HACK)


namespace Technosoftware
{
    namespace Base
    {


        const Timestamp::TimeVal Timestamp::TIMEVAL_MIN = std::numeric_limits<Timestamp::TimeVal>::min();
        const Timestamp::TimeVal Timestamp::TIMEVAL_MAX = std::numeric_limits<Timestamp::TimeVal>::max();


        Timestamp::Timestamp()
        {
            Update();
        }


        Timestamp::Timestamp(TimeVal tv)
        {
            ts_ = tv;
        }


        Timestamp::Timestamp(const Timestamp& other)
        {
            ts_ = other.ts_;
        }


        Timestamp::~Timestamp()
        {
        }


        Timestamp& Timestamp::operator = (const Timestamp& other)
        {
            ts_ = other.ts_;
            return *this;
        }


        Timestamp& Timestamp::operator = (TimeVal tv)
        {
            ts_ = tv;
            return *this;
        }


        void Timestamp::Swap(Timestamp& timestamp)
        {
            std::swap(ts_, timestamp.ts_);
        }


        Timestamp Timestamp::FromEpochTime(std::time_t t)
        {
            return Timestamp(TimeVal(t)*GetResolution());
        }


        Timestamp Timestamp::FromUtcTime(UtcTimeVal val)
        {
            val -= (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
            val /= 10;
            return Timestamp(val);
        }


        void Timestamp::Update()
        {
#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)

            FILETIME ft;
#if defined(_WIN32_WCE) && defined(TECHNOSOFTWARE_WINCE_TIMESTAMP_HACK)
            GetSystemTimeAsFileTimeWithMillisecondResolution(&ft);
#else
            GetSystemTimeAsFileTime(&ft);
#endif

            ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
            epoch.LowPart = 0xD53E8000;
            epoch.HighPart = 0x019DB1DE;

            ULARGE_INTEGER ts;
            ts.LowPart = ft.dwLowDateTime;
            ts.HighPart = ft.dwHighDateTime;
            ts.QuadPart -= epoch.QuadPart;
            ts_ = ts.QuadPart / 10;

#elif defined(TECHNOSOFTWARE_HAVE_CLOCK_GETTIME)

            struct timespec ts;
            if (clock_gettime(CLOCK_REALTIME, &ts))
                throw SystemException("cannot get time of day");
            ts_ = TimeVal(ts.tv_sec)*resolution() + ts.tv_nsec / 1000;

#else

            struct timeval tv;
            if (gettimeofday(&tv, NULL))
                throw SystemException("cannot get time of day");
            ts_ = TimeVal(tv.tv_sec)*resolution() + tv.tv_usec;

#endif
        }


        Timestamp  Timestamp::operator +  (const Timespan& span) const
        {
            return *this + span.GetTotalMicroseconds();
        }


        Timestamp  Timestamp::operator -  (const Timespan& span) const
        {
            return *this - span.GetTotalMicroseconds();
        }


        Timestamp& Timestamp::operator += (const Timespan& span)
        {
            return *this += span.GetTotalMicroseconds();
        }


        Timestamp& Timestamp::operator -= (const Timespan& span)
        {
            return *this -= span.GetTotalMicroseconds();
        }


#if defined(_WIN32)


        Timestamp Timestamp::FromFileTime(DWORD fileTimeLow, DWORD fileTimeHigh)
        {
            ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
            epoch.LowPart = 0xD53E8000;
            epoch.HighPart = 0x019DB1DE;

            ULARGE_INTEGER ts;
            ts.LowPart = fileTimeLow;
            ts.HighPart = fileTimeHigh;
            ts.QuadPart -= epoch.QuadPart;

            return Timestamp(ts.QuadPart / 10);
        }


        void Timestamp::ToFileTime(DWORD& fileTimeLow, DWORD& fileTimeHigh) const
        {
            ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
            epoch.LowPart = 0xD53E8000;
            epoch.HighPart = 0x019DB1DE;

            ULARGE_INTEGER ts;
            ts.QuadPart = ts_ * 10;
            ts.QuadPart += epoch.QuadPart;
            fileTimeLow = ts.LowPart;
            fileTimeHigh = ts.HighPart;
        }


#endif
    }

}
