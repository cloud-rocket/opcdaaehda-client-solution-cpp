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

#ifndef TECHNOSOFTWARE_AESERVERSTATUS_H
#define TECHNOSOFTWARE_AESERVERSTATUS_H

#include "DaAeHdaClient/ClientBase.h"
#include "Base/Timestamp.h"
#include "Base/ServerStates.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class AeServerImpl;

        /**
         * @class   AeServerStatus
         *
         * @brief   Encapsulates the current version information of the server.
         *          
         *          The information is only valid if the associated AeServer object is connected to an
         *          OPC Alarms and Events Server.
         *
         * @ingroup  AEClient
         */

        class OPCCLIENTSDK_API AeServerStatus
        {
        protected:

            /**
             * @fn  AeServerStatus::AeServerStatus() noexcept;
             *
             * @brief   Constructs a AeServerStatus object.
             *          
             *          Only ClientSdk classes can create AeServerStatus instances.
             */

            AeServerStatus() noexcept;

            /**
             * @fn  AeServerStatus::~AeServerStatus() noexcept;
             *
             * @brief   Destroys the object.
             *          
             *          Only ClientSdk classes can destroy AeServerStatus instances.
             */

            ~AeServerStatus() noexcept;

        public:

            /**
             * @fn  inline Base::Timestamp AeServerStatus::GetStartTime() const throw ()
             *
             * @brief   The time (UTC) the event server was started.
             *
             * @return  A Base::Timestamp.
             */

            inline Base::Timestamp GetStartTime() const noexcept { return startTime_; }

            /**
             * @fn  inline Base::Timestamp AeServerStatus::GetCurrentTime() const noexcept
             *
             * @brief   The current time (UTC) as known by the server.
             *
             * @return  A Base::Timestamp.
             */

            inline Base::Timestamp GetCurrentTime() const noexcept { return currentTime_; }

            /**
             * @fn  inline Base::Timestamp AeServerStatus::GetLastUpdateTime() const throw ()
             *
             * @brief   The time (UTC) the server sent the last event notification.
             *
             * @return  A Base::Timestamp.
             */

            inline Base::Timestamp GetLastUpdateTime() const noexcept { return lastUpdateTime_; }

            /**
             * @fn  inline Technosoftware::Base::ServerStates::ServerState AeServerStatus::GetServerState() const throw ()
             *
             * @brief   The current status of the server.
             *
             * @return  An uint32_t.
             */

            inline Technosoftware::Base::ServerStates::ServerState GetServerState() const noexcept { return serverState_; }

            /**
             * @fn  inline uint16_t AeServerStatus::GetMajorVersion() const noexcept
             *
             * @brief   The major version of the used server issue.
             *
             * @return  An uint16_t.
             */

            inline uint16_t GetMajorVersion() const noexcept { return majorVersion_; }

            /**
             * @fn  inline uint16_t AeServerStatus::GetMinorVersion() const throw ()
             *
             * @brief   The minor version of the used server issue.
             *
             * @return  An uint16_t.
             */

            inline uint16_t GetMinorVersion() const noexcept { return minorVersion_; }

            /**
             * @fn  inline uint16_t AeServerStatus::GetBuildNumber() const noexcept
             *
             * @brief   The build number of the used server issue.
             *
             * @return  An uint16_t.
             */

            inline uint16_t GetBuildNumber() const noexcept { return buildNumber_; }

            /**
             * @fn  inline const string& AeServerStatus::GetVendorInfo() const throw ()
             *
             * @brief   Retruns vendor specific server information.
             *
             * @return  A string&amp;
             */

            inline const string& GetVendorInfo() const noexcept { return vendorInfo_; }

        public:

            /**
             * @fn  string AeServerStatus::GetVersionAsText();
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
            friend class AeServerImpl;

            /**
             * @fn  friend unsigned __stdcall AeServerStatus::PollAeStatusThread(void far * pAttr);
             *
             * @brief   Poll AE status thread.
             *
             * @param [in,out]  pAttr   The attribute.
             *
             * @return  An unsigned.
             */

            friend unsigned __stdcall PollAeStatusThread(void far * pAttr);
            Base::Timestamp                                         startTime_;
            Base::Timestamp                                         currentTime_;
            Base::Timestamp                                         lastUpdateTime_;
            Technosoftware::Base::ServerStates::ServerState         serverState_;
            uint16_t                                                majorVersion_;
            uint16_t                                                minorVersion_;
            uint16_t                                                buildNumber_;
            string                                                  vendorInfo_;
        };
    }
}

#endif // TECHNOSOFTWARE_AESERVERSTATUS_H
