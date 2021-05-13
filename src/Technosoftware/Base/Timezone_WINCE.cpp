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
#include "Base/UnicodeConverter.h"
#include "Base/Exception.h"
#include "Base/UnWindows.h"
#include <ctime>
#if _WIN32_WCE >= 0x800
#include "time.h"
#else
#include "wce_time.h"
#endif

namespace Technosoftware
{
    namespace Base
    {


int Timezone::GetUtcOffset()
{
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    return -tzInfo.Bias*60;
}

    
int Timezone::GetDaylightSavingOffset()
{
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    return dstFlag == TIME_ZONE_ID_DAYLIGHT ? -tzInfo.DaylightBias*60 : 0;
}


bool Timezone::IsDaylightSaving(const Timestamp& timestamp)
{
    std::time_t time = timestamp.epochTime();
#if _WIN32_WCE >= 0x800
    struct std::tm* tms = localtime(&time);
#else
    struct std::tm* tms = wceex_localtime(&time);
#endif
    if (!tms) throw SystemException("cannot get local time DST flag");
    return tms->tm_isdst > 0;
}

    
std::string Timezone::GetName()
{
    std::string result;
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR* ptr = dstFlag == TIME_ZONE_ID_DAYLIGHT ? tzInfo.DaylightName : tzInfo.StandardName;
    UnicodeConverter::toUTF8(ptr, result);
    return result;
}

    
std::string Timezone::GetStandardName()
{
    std::string result;
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR* ptr = tzInfo.StandardName;
    UnicodeConverter::toUTF8(ptr, result);
    return result;
}

    
std::string Timezone::GetDaylightSavingName()
{
    std::string result;
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR* ptr = tzInfo.DaylightName;
    UnicodeConverter::toUTF8(ptr, result);
    return result;
}


}
}
