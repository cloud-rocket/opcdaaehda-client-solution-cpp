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
#include "DaAeHdaClient/Hda/HdaServerStatus.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        HdaServerStatus::HdaServerStatus() throw ()
        {
            memset(&m_ftStartTime, 0, sizeof(Base::Timestamp));
            memset(&m_ftCurrentTime, 0, sizeof(Base::Timestamp));
            memset(&m_ftLastUpdateTime, 0, sizeof(Base::Timestamp));
            m_dwServerState = Technosoftware::Base::ServerStates::ServerState::Unknown;
            m_dwMaxReturnValues = 0;
            m_wMajorVersion = 0;
            m_wMinorVersion = 0;
            m_wBuildNumber = 0;
        }

        HdaServerStatus::~HdaServerStatus() throw () {}

        string HdaServerStatus::GetVersionAsText()
        {
            string rval;
            char buf[30];
            sprintf(buf, "%d.%d (Build %d)", m_wMajorVersion, m_wMinorVersion, m_wBuildNumber);
            rval = buf;
            return rval;
        }
    }
}
