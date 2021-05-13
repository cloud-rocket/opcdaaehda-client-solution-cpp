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

#ifndef TECHNOSOFTWARE_HDASERVERSTATUS_H
#define TECHNOSOFTWARE_HDASERVERSTATUS_H

#include "DaAeHdaClient/OpcBase.h"
#include "Base/Status.h"
#include "Base/Timestamp.h"
#include "Base/ServerStates.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        /**
         * @class    HdaServerStatus
         *
         * @brief    Encapsulates the current version information of the server.
         *
         * @remarks    The information is only valid if the associated HdaServer object is connected to an OPC Historical Data Access (HDA) Server.
         *
         * @ingroup    HDAClient
         */

        class HdaServerStatus
        {
        protected:

            /**
             * @fn    HdaServerStatus::HdaServerStatus() throw ();
             *
             * @brief    Constructs a HdaServerStatus object.
             *
             * @remarks    Only ClientSdk classes can create HdaServerStatus instances.
             */

            HdaServerStatus() throw ();

            /**
             * @fn    HdaServerStatus::~HdaServerStatus() throw ();
             *
             * @brief    Destroys the object.
             *
             * @remarks    Only ClientSdk classes can destroy HdaServerStatus instances.
             */

            ~HdaServerStatus() throw ();

        public:

            /**
             * @fn    inline Base::Timestamp HdaServerStatus::GetStartTime() const throw ()
             *
             * @brief    The time (UTC) the event server was started.
             *
             * @return    A Base::Timestamp.
             */

            inline Base::Timestamp GetStartTime() const throw () { return m_ftStartTime; }

            /**
             * @fn    inline Base::Timestamp HdaServerStatus::GetCurrentTime() const throw ()
             *
             * @brief    The current time (UTC) as known by the server.
             *
             * @return    A Base::Timestamp.
             */

            inline Base::Timestamp GetCurrentTime() const throw () { return m_ftCurrentTime; }

            /**
             * @fn    inline Base::Timestamp HdaServerStatus::GetLastUpdateTime() const throw ()
             *
             * @brief    The time (UTC) the server sent the last event notification.
             *
             * @return    A Base::Timestamp.
             */

            inline Base::Timestamp GetLastUpdateTime() const throw () { return m_ftLastUpdateTime; }

            /**
             * @fn  inline Technosoftware::Base::ServerStates::ServerState HdaServerStatus::GetServerState() const throw ()
             *
             * @brief   The current status of the server.
             *
             * @return  An uint32_t.
             */

            inline Technosoftware::Base::ServerStates::ServerState GetServerState() const throw () { return m_dwServerState; }

            /**
             * @fn    inline uint32_t HdaServerStatus::GetMaxReturnValues() const throw ()
             *
             * @brief    The maximum number of values that can be returned by the server on a per item basis.
             *             A value of 0 indicates that the server forces no limit on the number of values it can
             *             return.
             *
             * @return    An uint32_t.
             */

            inline uint32_t GetMaxReturnValues() const throw () { return m_dwMaxReturnValues; }

            /**
             * @fn    inline uint16_t HdaServerStatus::GetMajorVersion() const throw ()
             *
             * @brief    The major version of the used server issue.
             *
             * @return    An uint16_t.
             */

            inline uint16_t GetMajorVersion() const throw () { return m_wMajorVersion; }

            /**
             * @fn    inline uint16_t HdaServerStatus::GetMinorVersion() const throw ()
             *
             * @brief    The minor version of the used server issue.
             *
             * @return    An uint16_t.
             */

            inline uint16_t GetMinorVersion() const throw () { return m_wMinorVersion; }

            /**
             * @fn    inline uint16_t HdaServerStatus::GetBuildNumber() const throw ()
             *
             * @brief    The build number of the used server issue.
             *
             * @return    An uint16_t.
             */

            inline uint16_t GetBuildNumber() const throw () { return m_wBuildNumber; }

            /**
             * @fn    inline const string& HdaServerStatus::GetVendorInfo() const throw ()
             *
             * @brief    Retruns vendor specific server information.
             *
             * @return    A string&amp;
             */

            inline const string& GetVendorInfo() const throw () { return m_sVendorInfo; }

        public:

            /**
             * @fn    string HdaServerStatus::GetVersionAsText();
             *
             * @brief    Returns the current server version as text string.
             *             
             *             The version string is returned in the format "&lt;MajorVersion&gt;.&lt;
             *             MinorVersion&gt; (Build &lt;BuildNumber&gt;)".
             *
             * @return    A string.
             */

            string GetVersionAsText();

        protected:
            friend class HdaServerImpl;
            friend unsigned __stdcall PollHdaStatusThread(void far * pAttr);
            Base::Timestamp    m_ftStartTime;
            Base::Timestamp    m_ftCurrentTime;
            Base::Timestamp    m_ftLastUpdateTime;
            Technosoftware::Base::ServerStates::ServerState        m_dwServerState;
            uint32_t        m_dwMaxReturnValues;
            uint16_t        m_wMajorVersion;
            uint16_t        m_wMinorVersion;
            uint16_t        m_wBuildNumber;
            string            m_sVendorInfo;
        };
    }
}

#endif /* TECHNOSOFTWARE_HDASERVERSTATUS_H */
