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

#ifndef TECHNOSOFTWARE_SERVERSTATES_H
#define TECHNOSOFTWARE_SERVERSTATES_H

#include <string>

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        namespace ServerStates
        {
            /**
             * @enum    ServerState
             *
             * @brief   The possible server states.
             *
             * @ingroup BaseOPC
             */

            enum ServerState
            {
                /** @brief The server is running normally. */
                Running = 0,
                /** @brief A vendor-specific fatal error has occurred within the server. The server is no longer functioning. The recovery procedure from this situation is vendor-specific. Most Service requests should be expected to fail. */
                Failed = 1,
                /** @brief The server is running but has no configuration information loaded and therefore does not transfer data. */
                NoConfiguration = 2,
                /** @brief The server has been temporarily suspended by some vendor-specific method and is not receiving or sending data. */
                Suspended = 3,
                /** @brief The server has shut down or is in the process of shutting down. Depending on the implementation, this might or might not be visible to clients. */
                Shutdown = 4,
                /** @brief The server is in Test Mode. The outputs are disconnected from the real hardware, but the server will otherwise behave normally. Inputs may be real or may be simulated depending on the vendor implementation. StatusCode will generally be returned normally. */
                Test = 5,
                /** @brief The server is running properly, but is having difficulty accessing data from its data sources. This may be due to communication problems or some other problem preventing the underlying device, control system, etc. from returning valid data. It may be a complete failure, meaning that no data is available, or a partial failure, meaning that some data is still available. It is expected that items affected by the fault will individually return with a BAD FAILURE status code indication for the items. */
                CommunicationFault = 6,
                /** @brief This state is used only to indicate that the OPC server does not know the state of underlying servers. */
                Unknown = 7
            };

            /**
             * @fn  std::string TECHNOSOFTWARE_API ToString(Technosoftware::Core::ServerStates::ServerState state);
             *
             * @brief   Get a string representation of the server state.
             *
             * @param   state   The server state (as an enum value).
             *
             * @return  The corresponding name.
             *
             * @ingroup BaseOPC
             */

            std::string TECHNOSOFTWARE_API ToString(Technosoftware::Base::ServerStates::ServerState state);
        }
    }
}

#endif /* TECHNOSOFTWARE_SERVERSTATES_H */
