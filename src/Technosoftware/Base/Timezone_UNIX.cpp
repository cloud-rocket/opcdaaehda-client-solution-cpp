/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Timezone class.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */
 
#include "Base/Timezone.h"
#include "Base/Exception.h"
#include "Base/Mutex.h"
#include <ctime>


namespace Technosoftware
{
    namespace Base
    {


class TZInfo
{
public:
    TZInfo()
    {
        tzset();
    }
    
    int timeZone()
    {
        Base::FastMutex::ScopedLock lock(mutex_);

    #if defined(__APPLE__)  || defined(__FreeBSD__) || defined (__OpenBSD__) || TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_ANDROID // no timezone global var
        std::time_t now = std::time(NULL);
        struct std::tm t;
        gmtime_r(&now, &t);
        std::time_t utc = std::mktime(&t);
        return now - utc;
    #elif defined(__CYGWIN__)
        tzset();
        return -_timezone;
    #else
        tzset();
        return -timezone;
    #endif
    }
    
    const char* name(bool dst)
    {
        Base::FastMutex::ScopedLock lock(mutex_);

        tzset();        
        return tzname[dst ? 1 : 0];
    }
        
private:
    Base::FastMutex mutex_;
};


static TZInfo tzInfo;


int Timezone::GetUtcOffset()
{
    return tzInfo.timeZone();
}

    
int Timezone::GetDaylightSavingOffset()
{
    std::time_t now = std::time(NULL);
    struct std::tm t;
    if (!localtime_r(&now, &t))
        throw Base::SystemException("cannot get local time DST offset");
    return t.tm_isdst == 1 ? 3600 : 0;
}


bool Timezone::IsDaylightSaving(const Timestamp& timestamp)
{
    std::time_t time = timestamp.epochTime();
    struct std::tm* tms = std::localtime(&time);
    if (!tms) throw Base::SystemException("cannot get local time DST flag");
    return tms->tm_isdst > 0;
}

    
std::string Timezone::GetName()
{
    return std::string(tzInfo.name(dst() != 0));
}

    
std::string Timezone::GetStandardName()
{
    return std::string(tzInfo.name(false));
}

    
std::string Timezone::GetDaylightSavingName()
{
    return std::string(tzInfo.name(true));
}


}
}
