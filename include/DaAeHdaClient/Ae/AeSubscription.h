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

#ifndef TECHNOSOFTWARE_AESUBSCRIPTION_H
#define TECHNOSOFTWARE_AESUBSCRIPTION_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "Base/Status.h"
#include "Base/Handles.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class AeServer;
        class AeIEventSink;
        class AeSubscriptionImpl;

        /**
         * @class	AeSubscription
         *
         * @brief	Represents the client's subscription for event notifications.
         *
         * 			Event Notifications can be controlled and handled through subscription objects. The
         * 			AeSubscription class offers functions to activate and deactivate event notifications.
         * 			Clients receives only events from active subscription objects. Also the event sinks
         * 			of clients can be specified with AeSubscription.
         *
         * @ingroup	AEClient
         */

        class OPCCLIENTSDK_API AeSubscription : protected OpcObject
        {
        public:

            /**
             * @fn	AeSubscription::AeSubscription(AeServer* pParent, AeIEventSink* pIUserEventSink, uint32_t hClientSubscription = 0, bool fActive = true, uint32_t dwBufferTime = 0, uint32_t dwMaxSize = 0) throw (Technosoftware::Base::Exception);
             *
             * @brief	Constructs a new event subscription object.
             *
             * @exception	Technosoftware::Base::Exception	Thrown when an exception error condition occurs.
             * @exception	Technosoftware::Base::Status   	Raised when an Opc error condition occurs.
             *
             * @param [in,out]	pParent			   	Address of a AeServer object which takes the ownership of
             * 										this subscription object.
             * @param [in,out]	pIUserEventSink	   	Address of the object which implements the sink for the
             * 										events.
             * @param 		  	hClientSubscription	(Optional) Client provided handle for this subscription.
             * @param 		  	fActive			   	(Optional) true if the Event Subscription is to be
             * 										created active and false if the Event Subscription is to
             * 										be created inactive.
             * @param 		  	dwBufferTime	   	(Optional) The requested buffer time.
             * @param 		  	dwMaxSize		   	(Optional) The requested maximum number of events.
             *
             * ### remarks	The AeServer object specified as parent must be connected to an OPC Alarms &amp;
             * 				Events Server; otherwise an exception 'Object is not connected to server' is
             * 				thrown.
             */

            AeSubscription(AeServer* pParent,
                AeIEventSink* pIUserEventSink,
                uint32_t hClientSubscription = 0,
                bool  fActive = true,
                uint32_t dwBufferTime = 0,
                uint32_t dwMaxSize = 0) noexcept(false);

            /**
             * @fn	AeSubscription::~AeSubscription() noexcept;
             *
             * @brief	Removes the client's subscription and destroys the object. All events which are not
             * 			  forwarded to the event sink are removed.
             */

            ~AeSubscription() noexcept;

            /**
             * @fn	bool AeSubscription::IsActive() const noexcept;
             *
             * @brief	Query if this object is active.
             *
             * @return	Returns the current active state of the subscription.
             */

            bool    IsActive() const noexcept;

            /**
             * @fn	Base::ClientHandle AeSubscription::GetClientHandle() const noexcept;
             *
             * @brief	Get the Client handle.
             *
             * @return	Returns the client supplied subscription handle.
             */

            Base::ClientHandle GetClientHandle() const noexcept;

            /**
             * @fn	uint32_t AeSubscription::RevisedBufferTime() const noexcept;
             *
             * @brief	Get the Revised buffer time.
             *
             * @return	Returns the current buffer time for the event notification to to the ClientSdk from
             * 			the server.
             */

            uint32_t RevisedBufferTime() const noexcept;

            /**
             * @fn	uint32_t AeSubscription::RevisedMaxSize() const throw ();
             *
             * @brief	Get the Revised maximum size.
             *
             * @return	Returns the current max number of events that will be sent in a single callback to
             * 			the ClientSdk from the server.
             */

            uint32_t RevisedMaxSize() const noexcept;

            /**
             * @fn  Technosoftware::Base::Status AeSubscription::SetActive(bool fActive = true);
             *
             * @brief   Sets the active state of the Event Subscription object. If the active state of the
             *          Event Subscription object is inactive, then the server will not send event
             *          notifications to the event sink registered with this object.
             *
             * @param   fActive (Optional) The new active state of the Event Subscription object. Use true to
             *                  activate and false to deactivate the Event Subscription object.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status SetActive(bool fActive = true);

            /**
             * @fn  Technosoftware::Base::Status AeSubscription::ToggleActive();
             *
             * @brief   Toggles the current active state of the Event Subscription object.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status ToggleActive();

            /**
             * @fn  Technosoftware::Base::Status AeSubscription::Refresh();
             *
             * @brief   Forces a Refresh for all active conditions and inactive, unacknowledged conditions
             *          whose event notifications match the filter of the Event Subscription.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status Refresh();

        protected:
            OpcAutoPtr<AeSubscriptionImpl> impl_;
        };
    }
}

#endif /* TECHNOSOFTWARE_AESUBSCRIPTION_H */
