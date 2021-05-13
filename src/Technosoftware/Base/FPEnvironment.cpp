/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of class FPEnvironment.
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

// pull in platform identification macros needed below
#include "Base/Platform.h"

#if defined(TECHNOSOFTWARE_NO_FPENVIRONMENT)
#include "FPEnvironment_DUMMY.cpp"
#elif defined(__osf__) || defined(__VMS)
#include "FPEnvironment_DEC.cpp"
#elif defined(sun) || defined(__sun)
#include "FPEnvironment_SUN.cpp"
#elif defined(TECHNOSOFTWARE_OS_FAMILY_UNIX)
#include "FPEnvironment_C99.cpp"
#elif defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#include "FPEnvironment_WIN32.cpp"
#else
#include "FPEnvironment_DUMMY.cpp"
#endif

// header file must be included after platform-specific part
// due to _XOPEN_SOURCE conflict on Tru64 (see FPEnvironment_DEC.cpp)
#include "Base/FPEnvironment.h"

namespace Technosoftware
{
    namespace Base
    {


        FPEnvironment::FPEnvironment()
        {
        }


        FPEnvironment::FPEnvironment(RoundingMode rm)
        {
            SetRoundingMode(rm);
        }


        FPEnvironment::FPEnvironment(const FPEnvironment& env) : FPEnvironmentImpl(env)
        {
        }


        FPEnvironment::~FPEnvironment()
        {
        }


        FPEnvironment& FPEnvironment::operator = (const FPEnvironment& env)
        {
            if (&env != this)
            {
                FPEnvironmentImpl::operator = (env);
            }
            return *this;
        }


        void FPEnvironment::KeepCurrent()
        {
            KeepCurrentImpl();
        }


        void FPEnvironment::ClearFlags()
        {
            ClearFlagsImpl();
        }

    }
}
