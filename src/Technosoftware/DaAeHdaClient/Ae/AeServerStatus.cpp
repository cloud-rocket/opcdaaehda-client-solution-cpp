/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://www.technosoftware.com
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

#include "OpcInternal.h"
#include "DaAeHdaClient/Ae/AeServerStatus.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        AeServerStatus::AeServerStatus() throw ()
        {
            memset(&startTime_, 0, sizeof(Base::Timestamp));
            memset(&currentTime_, 0, sizeof(Base::Timestamp));
            memset(&lastUpdateTime_, 0, sizeof(Base::Timestamp));
            serverState_ = Technosoftware::Base::ServerStates::ServerState::Unknown;
            majorVersion_ = 0;
            minorVersion_ = 0;
            buildNumber_ = 0;
        }

        AeServerStatus::~AeServerStatus() throw () {}

        string AeServerStatus::GetVersionAsText()
        {
            string rval;
            char buf[30];
            sprintf(buf, "%d.%d (Build %d)", majorVersion_, minorVersion_, buildNumber_);
            rval = buf;
            return rval;
        }
    }
}