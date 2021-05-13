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

#ifndef TECHNOSOFTWARE_DASERVERSTATUS_H
#define TECHNOSOFTWARE_DASERVERSTATUS_H

#include "DaAeHdaClient/ClientBase.h"
#include "Base/Timestamp.h"
#include "Base/ServerStates.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        /**
         * @class   DaServerStatus
         *
         * @brief   Encapsulates the current version information of the server.
         *          
         *          The information is only valid if the associated DaServer object is connected to an
         *          OPC Data Access Server.
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaServerStatus
        {
        protected:

            /**
             * @fn  DaServerStatus::DaServerStatus() noexcept;
             *
             * @brief   Constructs a DaServerStatus object.
             *          
             *          Only ClientSdk classes can create DaServerStatus instances.
             */

            DaServerStatus() noexcept;

            /**
             * @fn  DaServerStatus::~DaServerStatus() noexcept;
             *
             * @brief   Destroys the object.
             *          
             *          Only ClientSdk classes can destroy DaServerStatus instances.
             */

            ~DaServerStatus() noexcept;

        public:

            /**
             * @fn  Base::Timestamp DaServerStatus::GetStartTime() const noexcept
             *
             * @brief   The time (UTC) the event server was started.
             *
             * @return  A Base::Timestamp.
             */

            Base::Timestamp GetStartTime() const noexcept { return startTime_; }

            /**
             * @fn  Base::Timestamp DaServerStatus::GetCurrentTime() const noexcept
             *
             * @brief   The current time (UTC) as known by the server.
             *
             * @return  A Base::Timestamp.
             */

            Base::Timestamp GetCurrentTime() const noexcept { return currentTime_; }

            /**
             * @fn  Base::Timestamp DaServerStatus::GetLastUpdateTime() const noexcept
             *
             * @brief   The time (UTC) the server sent the last event notification.
             *
             * @return  A Base::Timestamp.
             */

            Base::Timestamp GetLastUpdateTime() const noexcept { return lastUpdateTime_; }

            /**
             * @fn  Base::ServerStates::ServerState DaServerStatus::GetServerState() const noexcept
             *
             * @brief   The current status of the server.
             *
             * @return  An uint32_t.
             */

            Base::ServerStates::ServerState GetServerState() const noexcept { return serverState_; }

            /**
             * @fn  uint32_t DaServerStatus::GetGroupCount() const noexcept
             *
             * @brief   The total number of groups being managed by the server instance.
             *
             * @return  An uint32_t.
             */

            uint32_t GetGroupCount() const noexcept { return groupCount_; }

            /**
             * @fn  uint32_t DaServerStatus::GetBandWidth() const noexcept
             *
             * @brief   The behavior of of this value is server specific
             *          
             *          Refer to the OPC Data Access Specification for a detailed description of suggested
             *          usage.
             *
             * @return  An uint32_t.
             */

            uint32_t GetBandWidth() const noexcept { return bandWidth_; }

            /**
             * @fn  uint16_t DaServerStatus::GetMajorVersion() const noexcept
             *
             * @brief   The major version of the used server issue.
             *
             * @return  An uint16_t.
             */

            uint16_t GetMajorVersion() const noexcept { return majorVersion_; }

            /**
             * @fn  uint16_t DaServerStatus::GetMinorVersion() const noexcept
             *
             * @brief   The minor version of the used server issue.
             *
             * @return  An uint16_t.
             */

            uint16_t GetMinorVersion() const noexcept { return minorVersion_; }

            /**
             * @fn  uint16_t DaServerStatus::GetBuildNumber() const noexcept
             *
             * @brief   The build number of the used server issue.
             *
             * @return  An uint16_t.
             */

            uint16_t GetBuildNumber() const noexcept { return buildNumber_; }

            /**
             * @fn  uint16_t DaServerStatus::GetReserved() const noexcept
             *
             * @brief   A reserverd value field returned by the server.
             *
             * @return  An uint16_t.
             */

            uint16_t GetReserved() const noexcept { return reserved_; }

            /**
             * @fn    inline const string& DaServerStatus::GetVendorInfo() const throw ()
             *
             * @brief    Retruns vendor specific server information.
             *
             * @return    A string&amp;
             */

            const string& GetVendorInfo() const noexcept { return vendorInfo_; }

        public:

            /**
             * @fn  string DaServerStatus::GetVersionAsText();
             *
             * @brief   Returns the current server version as text string.
             *          
             *          The version string is returned in the format "&lt;MajorVersion&gt;.&lt;
             *          MinorVersion&gt; (Build &lt;BuildNumber&gt;)".
             *
             * @return  A string.
             */

            string GetVersionAsText();

        protected:
            friend class DaServerImpl;

            /**
             * @fn  friend unsigned __stdcall DaServerStatus::PollDaStatusThread(void far * pAttr);
             *
             * @brief   Poll DA Server status thread
             *
             * @param [in,out]  pAttr   If non-null, the attribute.
             *
             * @return  An unsigned.
             */

            friend unsigned __stdcall PollDaStatusThread(void far * pAttr);
            Base::Timestamp                             startTime_;
            Base::Timestamp                             currentTime_;
            Base::Timestamp                             lastUpdateTime_;
            Base::ServerStates::ServerState             serverState_;
            uint32_t                                    groupCount_;
            uint32_t                                    bandWidth_;
            uint16_t                                    majorVersion_;
            uint16_t                                    minorVersion_;
            uint16_t                                    buildNumber_;
            uint16_t                                    reserved_;
            string                                      vendorInfo_;
        };
    }
}

#endif /* TECHNOSOFTWARE_DASERVERSTATUS_H */
