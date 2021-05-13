/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Timezone class.
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
    std::time_t time = timestamp.GetEpochTime();
    struct std::tm* tms = std::localtime(&time);
    if (!tms) throw Base::SystemException("cannot get local time DST flag");
    return tms->tm_isdst > 0;
}

    
std::string Timezone::GetName()
{
    std::string result;
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR* ptr = dstFlag == TIME_ZONE_ID_DAYLIGHT ? tzInfo.DaylightName : tzInfo.StandardName;
#if defined(TECHNOSOFTWARE_WIN32_UTF8)
    UnicodeConverter::toUTF8(ptr, result);
#else
    char buffer[256];
    DWORD rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, buffer, sizeof(buffer), NULL, NULL);
    if (rc) result = buffer;
#endif
    return result;
}

    
std::string Timezone::GetStandardName()
{
    std::string result;
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR* ptr = tzInfo.StandardName;
#if defined(TECHNOSOFTWARE_WIN32_UTF8)
    UnicodeConverter::toUTF8(ptr, result);
#else
    char buffer[256];
    DWORD rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, buffer, sizeof(buffer), NULL, NULL);
    if (rc) result = buffer;
#endif
    return result;
}

    
std::string Timezone::GetDaylightSavingName()
{
    std::string result;
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR* ptr = tzInfo.DaylightName;
#if defined(TECHNOSOFTWARE_WIN32_UTF8)
    UnicodeConverter::toUTF8(ptr, result);
#else
    char buffer[256];
    DWORD rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, buffer, sizeof(buffer), NULL, NULL);
    if (rc) result = buffer;
#endif
    return result;
}
    }

} 
