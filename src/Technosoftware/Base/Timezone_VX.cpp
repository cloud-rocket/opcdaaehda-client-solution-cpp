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
#include "Base/Environment.h"
#include <ctime>


namespace Technosoftware
{
    namespace Base
    {


int Timezone::GetUtcOffset()
{
    std::time_t now = std::time(NULL);
    struct std::tm t;
    gmtime_r(&now, &t);
    std::time_t utc = std::mktime(&t);
    return now - utc;
}

    
int Timezone::GetDaylightSavingOffset()
{
    std::time_t now = std::time(NULL);
    struct std::tm t;
    if (localtime_r(&now, &t) != OK)
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
    // format of TIMEZONE environment variable:
    // name_of_zone:<(unused)>:time_in_minutes_from_UTC:daylight_start:daylight_end
    std::string tz = Environment::get("TIMEZONE", "UTC");
    std::string::size_type pos = tz.find(':');
    if (pos != std::string::npos)
        return tz.substr(0, pos);
    else
        return tz;
}

    
std::string Timezone::GetStandardName()
{
    return name();
}

    
std::string Timezone::GetDaylightSavingName()
{
    return name();
}


    }
}
