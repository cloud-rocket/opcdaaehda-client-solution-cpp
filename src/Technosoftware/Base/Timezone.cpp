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

#include "Base/Timezone.h"
#include <ctime>


#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#if defined(_WIN32_WCE)
#include "Timezone_WINCE.cpp"
#else
#include "Timezone_WIN32.cpp"
#endif
#elif defined(TECHNOSOFTWARE_VXWORKS)
#include "Timezone_VX.cpp"
#else
#include "Timezone_UNIX.cpp"
#endif


namespace Technosoftware
{
    namespace Base
    {
        int Timezone::GetTimezoneDifference()
        {
            return GetUtcOffset() + GetDaylightSavingOffset();
        }
    }
} 
