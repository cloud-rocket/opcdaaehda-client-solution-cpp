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

#ifndef TECHNOSOFTWARE_TIMEZONE_H
#define TECHNOSOFTWARE_TIMEZONE_H

#include "Base/Base.h"
#include "Base/Timestamp.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    Timezone
         *
         * @brief    This class provides information about the current timezone.
         *
         * @ingroup BaseDateTime
         */

        class TECHNOSOFTWARE_API Timezone
        {
        public:

            /**
             * @fn  static int Timezone::GetUtcOffset();
             *
             * @brief   Returns the offset of local time to UTC, in seconds. local time = UTC +
             *          GetUtcOffset() + GetDaylightSavingOffset().
             *
             * @return  The UTC offset.
             */

            static int GetUtcOffset();

            /**
             * @fn  static int Timezone::GetDaylightSavingOffset();
             *
             * @brief   Returns the daylight saving time offset in seconds if daylight saving time is in use.
             *          local time = UTC + GetUtcOffset() + GetDaylightSavingOffset().
             *
             * @return  The daylight saving offset.
             */

            static int GetDaylightSavingOffset();

            /**
             * @fn  static bool Timezone::IsDaylightSaving(const Timestamp& timestamp);
             *
             * @brief   Returns true if daylight saving time is in effect for the given time. Depending on
             *          the operating system platform this might only work reliably for certain date ranges,
             *          as the C library's localtime() function is used.
             *
             * @param   timestamp   The timestamp.
             *
             * @return  true if daylight saving, false if not.
             */

            static bool IsDaylightSaving(const Timestamp& timestamp);

            /**
             * @fn  static int Timezone::GetTimezoneDifference();
             *
             * @brief   Returns the time zone differential for the current timezone. The timezone
             *          differential is computed as GetUtcOffset() + GetDaylightSavingOffset()
             *          and is expressed in seconds.
             *
             * @return  The timezone difference.
             */

            static int GetTimezoneDifference();

            /**
             * @fn  static std::string Timezone::GetName();
             *
             * @brief   Returns the timezone name currently in effect.
             *
             * @return  The name.
             */

            static std::string GetName();

            /**
             * @fn  static std::string Timezone::GetStandardName();
             *
             * @brief   Returns the timezone name if not daylight saving time is in effect.
             *
             * @return  The standard name.
             */

            static std::string GetStandardName();

            /**
             * @fn  static std::string Timezone::GetDaylightSavingName();
             *
             * @brief   Returns the timezone name if daylight saving time is in effect.
             *
             * @return  The daylight saving name.
             */

            static std::string GetDaylightSavingName();
        };
    }
}

#endif /* TECHNOSOFTWARE_TIMEZONE_H */
