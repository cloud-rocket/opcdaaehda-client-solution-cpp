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

#ifndef TECHNOSOFTWARE_AEEVENT_H
#define TECHNOSOFTWARE_AEEVENT_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "Base/Handles.h"
#include "Base/Timestamp.h"
#include "Base/AutoPtr.h"


namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class AeNewEvents;
        class AeNewEventsImpl;

        /**
         * @class   AeIEventSink
         *
         * @brief   Defines the interface of the user specific callback function.
         *          
         *          To receive events the user must define an event sink class which inherits from class
         *          AeIEventSink. Also the pure virtual function NewEvents() must be implemented.
         *          
         *          The user event sink class is used as parameter when AeSubscription objects are
         *          instantiated.
         *
         * @ingroup  AEClient
         */

        class OPCCLIENTSDK_API AeIEventSink                           // The Interface of the User Event Sink
        {
        public:

            /**
             * @fn  virtual void AeIEventSink::NewEvents(AeNewEvents* pNewEvents) = 0;
             *
             * @brief   The event sink function to handle the new received events.
             *
             * @param [in,out]  pNewEvents  A collection of new received events from the OPC AE Server. All
             *                              events inclusive the event collection instance pNewEvents itself
             *                              must be released with the delete operator.
             */

            virtual void NewEvents(AeNewEvents* pNewEvents) = 0;
        };

        /**
         * @class   AeEvent
         *
         * @brief   The AeEvent class encapsulates all information of a single event.
         *          
         *          Only ClientSdk classes can create AeEvent instances
         *
         * @ingroup  AEClient
         */

        class OPCCLIENTSDK_API AeEvent : protected OpcObject
        {
        public:

            /**
             * @fn  AeEvent::~AeEvent() noexcept;
             *
             * @brief   Destroys a AeEvent object. If the object is still connected to an OPC AE Server then
             *          all existing subscriptions will be removed and the object disconnected from the
             *          server.
             */

            ~AeEvent() noexcept;

            // Attributes
        public:

            /**
             * @fn  inline uint16_t AeEvent::GetChangeMask() const throw ()
             *
             * @brief   Indicates which properties of the condition have changed.
             *
             *          Validity: Only condition-related events.
             *
             * @return  An uint16_t.
             */

            inline uint16_t GetChangeMask() const noexcept { return changeMask_; }

            /**
             * @fn  inline uint16_t AeEvent::SetNewState() const throw ()
             *
             * @brief   Specifies the new state of the condition.
             *          
             *          Validity: Only condition-related events.
             *
             * @return  An uint16_t.
             */

            inline uint16_t SetNewState() const noexcept { return newState_; }

            /**
             * @fn  inline const string& AeEvent::GetSource() const throw ()
             *
             * @brief   Describes the source of the event notification.
             *          
             *          Validity: All event types.
             *
             * @return  A reference to a const string.
             */

            inline const string& GetSource() const noexcept { return source_; }

            /**
             * @fn  inline Base::Timestamp AeEvent::GetTime() const throw ()
             *
             * @brief   The time (UTC) of the event occurence. For conditional events it is the time when the
             *          condition changed into the new state or sub-condition.
             *          
             *          Validity: All event types.
             *
             * @return  A Base::Timestamp.
             */

            inline Base::Timestamp GetTime() const noexcept { return timestamp_; }

            /**
             * @fn  inline const string& AeEvent::GetMessage() const noexcept
             *
             * @brief   Returns the message describing the event.
             *          
             *          Validity: All event types.
             *
             * @return  A reference to a const string.
             */

            inline const string& GetMessage() const noexcept { return message_; }

            /**
             * @fn  inline uint32_t AeEvent::GetEventType() const throw ()
             *
             * @brief   Specifies the type of the event.
             *          
             *          Validity: All event types.
             *
             * @return  An uint32_t.
             */

            inline uint32_t GetEventType() const noexcept { return eventType_; }

            /**
             * @fn  inline uint32_t AeEvent::GetEventCategory() const throw ()
             *
             * @brief   Specifies the category of the event.
             *          
             *          Validity: All event types.
             *
             * @return  An uint32_t.
             */

            inline uint32_t GetEventCategory() const noexcept { return eventCategory_; }

            /**
             * @fn  inline uint32_t AeEvent::GetSeverity() const throw ()
             *
             * @brief   The severity of the event in the range 1...1000.
             *          
             *          Validity: All event types.
             *
             * @return  An uint32_t.
             */

            inline uint32_t GetSeverity() const noexcept { return severity_; }

            /**
             * @fn  inline const string& AeEvent::GetConditionName() const throw ()
             *
             * @brief   Returns the name of the condition related to this event notification.
             *          
             *          Validity: Only condition-related events.
             *
             * @return  A reference to a const string.
             */

            inline const string& GetConditionName() const noexcept { return conditionName_; }

            /**
             * @fn  inline const string& AeEvent::GetSubconditionName() const throw ()
             *
             * @brief   Returns the name of the sub condition for multi-state conditions or the condition
             *          name for single-state conditions.
             *          
             *          Validity: Only condition-related events.
             *
             * @return  A reference to a const string.
             */

            inline const string& GetSubconditionName() const noexcept { return subconditionName_; }

            /**
             * @fn  inline uint16_t AeEvent::GetQuality() const throw ()
             *
             * @brief   Specifies the quality associated with the condition state.
             *          
             *          Validity: Only condition-related events.
             *
             * @return  An uint16_t.
             */

            inline uint16_t GetQuality() const noexcept { return quality_; }

            /**
             * @fn  inline uint16_t AeEvent::GetReserved() const throw ()
             *
             * @brief   A not used field.
             *          
             *          Validity: All event types.
             *
             * @return  An uint16_t.
             */

            inline uint16_t GetReserved() const noexcept { return reserved_; }

            /**
             * @fn  inline bool AeEvent::IsAckRequired() const throw ()
             *
             * @brief   Indicates if the event requires acknowledgment.
             *          
             *          Validity: Only condition-related events.
             *
             * @return  true if it succeeds, false if it fails.
             */

            inline bool IsAckRequired() const noexcept { return ackRequired_; }

            /**
             * @fn  inline Base::Timestamp AeEvent::GetActiveTime() const throw ()
             *
             * @brief   Returns the time (UTC) that the condition became active. For single-state conditions
             *          it is the time that the condition became active. For multi-state conditions its the
             *          time of transition into the current sub-condition.
             *          
             *          Validity: Only condition-related events.
             *
             * @return  A Base::Timestamp.
             */

            inline Base::Timestamp GetActiveTime() const noexcept { return activeTime_; }

            /**
             * @fn  inline uint32_t AeEvent::GetCookie() const noexcept
             *
             * @brief   Returns the server defined cookie associated with the event.
             *          
             *          Validity: Only condition-related events.
             *
             * @return  An uint32_t.
             */

            inline uint32_t GetCookie() const noexcept { return cookie_; }

            /**
             * @fn  inline uint32_t AeEvent::GetNumberEventAttributes() const noexcept
             *
             * @brief   Returns the number of elements in the vendor specific event attribute array.
             *          
             *          The Array can be accessed with function member function EventAttributes().
             *          
             *          Validity: All event types.
             *
             * @return  The total number of event attributes.
             */

            inline uint32_t GetNumberEventAttributes() const noexcept { return numberEventAttributes_; }

            /**
             * @fn  inline OpcVariant* AeEvent::GetEventAttributes() const noexcept
             *
             * @brief   Returns a pointer to an array of vendor specific event attributes.
             *          
             *          Validity: All event types.
             *
             * @return  null if it fails, else a pointer to an OpcVariant.
             */

            inline OpcVariant* GetEventAttributes() const noexcept { return eventAttributes_; }

            /**
             * @fn  inline const string& AeEvent::GetActorId() const throw ()
             *
             * @brief   Returns the actor ID.
             *          
             *          Specifies the actor ID if the event is a tracking event. For condition-related events
             *          this is the AcknowledgerID or an empty string if the event was automatically
             *          acknowledget by the server.
             *          
             *          Validity: Only tracking events and condition-related events which are acknowledgment
             *          notifications.
             *
             * @return  A reference to a const string.
             */

            inline const string& GetActorId() const noexcept { return actorId_; }

        public:

            /**
             * @fn    string AeEvent::GetEventTypeAsText(OpcTextMode eTextMode = Capitalize);
             *
             * @brief    Returns the Event Type as text string.
             *
             * @remarks    Validity: All event types.
             *
             * @param    eTextMode    (Optional) Optional parameter which specifies the format of the returned
             *                         text string.
             *
             * @return    A string.
             */

            string GetEventTypeAsText(OpcTextMode eTextMode = OpcTextMode::Capitalize);

            /**
             * @fn    string AeEvent::GetChangeMaskAsText(OpcTextMode eTextMode = Capitalize);
             *
             * @brief    Returns the Change Mask as text string.
             *
             * @remarks    Validity: Only condition-related events.
             *
             * @param    eTextMode    (Optional) Optional parameter which specifies the format of the returned
             *                         text string.
             *
             * @return    A string.
             */

            string GetChangeMaskAsText(OpcTextMode eTextMode = OpcTextMode::Capitalize);

            /**
             * @fn    string AeEvent::GetNewStateAsText(OpcTextMode eTextMode = Capitalize);
             *
             * @brief    Returns the New State as text string.
             *
             * @remarks    Validity: Only condition-related events.
             *
             * @param    eTextMode    (Optional) Optional parameter which specifies the format of the returned
             *                         text string.
             *
             * @return    A string.
             */

            string GetNewStateAsText(OpcTextMode eTextMode = OpcTextMode::Capitalize);

            /**
             * @fn    string AeEvent::GetQualityAsText();
             *
             * @brief    Returns the decoded quality flags as text string.
             *
             * @return    A string.
             */

            string GetQualityAsText();

        protected:
            friend class CComOPCEventSinkImpl;
            AeEvent(void* pOnEvent) noexcept(false);

            uint16_t            changeMask_;
            uint16_t            newState_;
            string              source_;
            Base::Timestamp     timestamp_;
            string              message_;
            uint32_t            eventType_;
            uint32_t            eventCategory_;
            uint32_t            severity_;
            string              conditionName_;
            string              subconditionName_;
            uint16_t            quality_;
            uint16_t            reserved_;
            bool                ackRequired_;
            Base::Timestamp     activeTime_;
            uint32_t            cookie_;
            uint32_t            numberEventAttributes_;
            OpcVariant*         eventAttributes_;
            string              actorId_;
        };

        /**
         * @class   AeNewEvents
         *
         * @brief   A collection of new received events from the OPC AE Server.
         *
         * @ingroup  AEClient
         */

        class OPCCLIENTSDK_API AeNewEvents : protected OpcObject
        {
        public:
            ~AeNewEvents() noexcept;

        public:

            /**
             * @fn  Base::ClientSubscriptionHandle AeNewEvents::GetSubscriptionHandle() const;
             *
             * @brief   The client handle for the subscription object which sent the events.
             *
             * @return  A ClientHandle.
             */

            Base::ClientSubscriptionHandle GetSubscriptionHandle() const;

            /**
             * @fn  bool AeNewEvents::IsRefresh() const;
             *
             * @brief   Indicates if the events are the result of a subscription refresh.
             *
             * @return  true if refresh, false if not.
             */

            bool IsRefresh() const;

            /**
             * @fn  bool AeNewEvents::IsLastRefresh() const;
             *
             * @brief   Indicates if it is the last result of a subscription refresh.
             *
             * @return  true if last refresh, false if not.
             */

            bool IsLastRefresh() const;

            /**
             * @fn  uint32_t AeNewEvents::GetCount() const;
             *
             * @brief   Gets the count.
             *
             * @return  Returns the number of event notifications. This is the original number of events when
             *          received from the OPC AE Server and it's not modified even if events are detached
             *          from the collection class (with function DetachEvent()).
             */

            uint32_t GetCount() const;

            /**
             * @fn  AeEvent* AeNewEvents::DetachEvent();
             *
             * @brief   Detaches the next AeEvent object from the collection.
             *
             * @return  The next AeEvent object or a NULL pointer if the collection is empty.
             *
             * ### remarks  The returned object must be released by the caller with the delete operator.
             */

            AeEvent* DetachEvent();

        protected:
            friend class CComOPCEventSinkImpl;
            AeNewEvents(Base::ClientHandle hClientSubscription, bool bRefresh, bool bLastRefresh, uint32_t dwCount) throw (Technosoftware::Base::Exception);
            void AddEvent(AeEvent* pEvent);

        private:
            OpcAutoPtr<AeNewEventsImpl> impl_;
        };
    }
}

#endif // TECHNOSOFTWARE_AEEVENT_H
