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

#ifndef TECHNOSOFTWARE_HANDLES_H
#define TECHNOSOFTWARE_HANDLES_H


 // STD
#include <stdint.h>

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @typedef    uint64_t RequestHandle
         *
         * @brief    Each request will be assigned a handle that will remain unique during the lifetime of
         *             the client. The handle is 64 bit, meaning that even at 1 million requests per second,
         *             the client will be able to assign unique handles for more than 500000 years...
         *
         * @ingroup    BaseOPC
         */

        typedef uint64_t RequestHandle;

        /**
         * @typedef    uint32_t TransactionId
         *
         * @brief    A TransactionId is internally assigned and stored by the Technosoftware to keep track of
         *             asynchronous requests and their results.
         *
         * @ingroup    BaseOPC
         */

        typedef uint32_t TransactionId;

        /**
         * @typedef    uint32_t ClientConnectionId
         *
         * @brief    A ClientConnectionId is a 32-bit number assigned by the Technosoftware to newly created
         *             sessions. The number will be incremented on each new session creation, so in theory
         *             it will take 2**32 sessions that have to be created before the number starts to count
         *             from 0 again.
         *
         * @ingroup    BaseOPC
         */

        typedef uint32_t ClientConnectionId;

        /**
         * @typedef    uint32_t SubscriptionId
         *
         * @brief    A SubscriptionId is assigned to a subscription by the server (so NOT by the client!).
         *
         * @ingroup    BaseOPC
         */

        typedef uint32_t SubscriptionId;

        /**
         * @typedef    uint32_t ClientSubscriptionHandle
         *
         * @brief    A ClientSubscriptionHandle is a 32-bit number assigned by the Technosoftware to newly
         *             created subscriptions. The number will be incremented on each new subscription
         *             creation, so in theory it will take 2**32 subscriptions that have to be created
         *             before the number starts to count from 0 again. In practice, it will never happen.
         *
         * @ingroup    BaseOPC
         */

        typedef uint32_t ClientSubscriptionHandle;

        /**
         * @typedef    uint32_t MonitoredItemId
         *
         * @brief    A SubscriptionId is assigned to a monitored item by the server (so NOT by the
         *             client!).
         *
         * @ingroup    BaseOPC
         */

        typedef uint32_t MonitoredItemId;

        /**
         * @typedef    uint32_t ClientHandle
         *
         * @brief    A ClientHandle is a 32-bit number assigned by the Technosoftware to newly created
         *             monitored items. The number will be incremented on each new item creation, so in
         *             theory it will take 2**32 items that have to be created before the number starts to
         *             count from 0 again. In practice, it will never happen.
         *
         * @ingroup    BaseOPC
         */

        typedef uint32_t ClientHandle;

        /**
        * @typedef    uint32_t ServerHandle
        *
        * @brief    A ServerHandle is a 32-bit number assigned by the server to newly created
        *             monitored items.
        *
        * @ingroup    BaseOPC
        */

        typedef uint32_t ServerHandle;

        /**
         * @typedef    uint32_t ServerIndex
         *
         * @brief    A ServerIndex is an unsigned 32-bit integer, identifying a server in a ServerArray.
         *
         * @ingroup    BaseOPC
         */

        typedef uint32_t ServerIndex;

        /**
         * @typedef    uint16_t NameSpaceIndex
         *
         * @brief    An OPC UA namespace index is used to relate something (e.g. a NodeIdIdentifier) to a
         *             namespace URI via a namespace array.
         *
         * @ingroup    BaseOPC
         */

        typedef uint16_t NameSpaceIndex;
    }
}


#endif /* TECHNOSOFTWARE_HANDLES_H */
