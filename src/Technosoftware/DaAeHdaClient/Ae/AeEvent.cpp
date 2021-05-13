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
#include "DaAeHdaClient/Ae/AeEvent.h"
#include "Base/Timestamp.h"

#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        AeEvent::AeEvent(void* pOnEvent) noexcept(false) : OpcObject(NULL, "AeEvent")
        {
            ONEVENTSTRUCT* _pOnEvent = static_cast<ONEVENTSTRUCT*>(pOnEvent);
            _ASSERTE(_pOnEvent);

            USES_CONVERSION;
            changeMask_ = _pOnEvent->wChangeMask;
            newState_ = _pOnEvent->wNewState;
            source_ = OLE2A(_pOnEvent->szSource);
            timestamp_ = Base::Timestamp::FromFileTime(_pOnEvent->ftTime.dwLowDateTime, _pOnEvent->ftTime.dwHighDateTime);
            message_ = OLE2A(_pOnEvent->szMessage);
            eventType_ = _pOnEvent->dwEventType;
            eventCategory_ = _pOnEvent->dwEventCategory;
            severity_ = _pOnEvent->dwSeverity;
            conditionName_ = OLE2A(_pOnEvent->szConditionName);
            subconditionName_ = OLE2A(_pOnEvent->szSubconditionName);
            quality_ = _pOnEvent->wQuality;
            reserved_ = _pOnEvent->wReserved;
            ackRequired_ = _pOnEvent->bAckRequired ? true : false;
            activeTime_ = Base::Timestamp::FromFileTime(_pOnEvent->ftActiveTime.dwLowDateTime, _pOnEvent->ftActiveTime.dwHighDateTime);
            cookie_ = _pOnEvent->dwCookie;

            //
            // Event Attributes
            //
            numberEventAttributes_ = _pOnEvent->dwNumEventAttrs;

            // Copy Variant data members
            if ((eventAttributes_ = (OpcVariant*)new VARIANT[numberEventAttributes_]) == NULL) throw Technosoftware::Base::OutOfMemoryException();
            HRESULT        hr = S_OK;
            unsigned int   i;
            for (i = 0; i < numberEventAttributes_; i++) {
                VariantInit((LPVARIANT)&eventAttributes_[i]);
                hr = VariantCopy((LPVARIANT)&eventAttributes_[i], &_pOnEvent->pEventAttributes[i]);
                if (FAILED(hr)) break;
            }
            if (FAILED(hr)) {                          // Release successfully copied Variants if something goes wrong
                while (i--) {
                    VariantClear((LPVARIANT)&eventAttributes_[i]);
                }
                delete[] eventAttributes_;
                throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr));
            }

            //
            // Actor ID
            //
            // According to the specification a server should return a NUL string
            // and not a NULL pointer. To avoid conflicts with incompatible servers
            // we test for a NULL pointer.
            actorId_ = _pOnEvent->szActorID ? OLE2A(_pOnEvent->szActorID) : "";
        }

        AeEvent::~AeEvent() throw ()
        {
            try {
                while (numberEventAttributes_--) {
                    VariantClear((LPVARIANT)&eventAttributes_[numberEventAttributes_]);
                }
                delete[] eventAttributes_;
            }
            catch (...) {}
        }

        string AeEvent::GetEventTypeAsText(OpcTextMode eTextMode)
        {
            if (eTextMode == OpcTextMode::Valuename) {
                switch (eventType_) {
                case OPC_SIMPLE_EVENT:     return "OPC_SIMPLE_EVENT";
                case OPC_CONDITION_EVENT:  return "OPC_CONDITION_EVENT";
                case OPC_TRACKING_EVENT:   return "OPC_TRACKING_EVENT";
                default:                   return "OPC_???_EVENT";
                }
            }

            string str;
            switch (eventType_) {
            case OPC_SIMPLE_EVENT:     str = "Simple";      break;
            case OPC_CONDITION_EVENT:  str = "Condition";   break;
            case OPC_TRACKING_EVENT:   str = "Tracking";    break;
            default:                   str = "???";         break;
            }

            if (eTextMode == OpcTextMode::Lowercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                  // destination
                    tolower);                    // operation

            else if (eTextMode == OpcTextMode::Uppercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                  // destination
                    toupper);                    // operation

            return str;
        }

        string AeEvent::GetChangeMaskAsText(OpcTextMode eTextMode)
        {
            string str;
            if (eTextMode == OpcTextMode::Valuename) {
                if (changeMask_ & OPC_CHANGE_ACTIVE_STATE) str = "OPC_CHANGE_ACTIVE_STATE, ";
                if (changeMask_ & OPC_CHANGE_ACK_STATE)    str += "OPC_CHANGE_ACK_STATE, ";
                if (changeMask_ & OPC_CHANGE_ENABLE_STATE) str += "OPC_CHANGE_ENABLE_STATE, ";
                if (changeMask_ & OPC_CHANGE_QUALITY)      str += "OPC_CHANGE_QUALITY, ";
                if (changeMask_ & OPC_CHANGE_SEVERITY)     str += "OPC_CHANGE_SEVERITY, ";
                if (changeMask_ & OPC_CHANGE_SUBCONDITION) str += "OPC_CHANGE_SUBCONDITION, ";
                if (changeMask_ & OPC_CHANGE_MESSAGE)      str += "OPC_CHANGE_MESSAGE, ";
                if (changeMask_ & OPC_CHANGE_ATTRIBUTE)    str += "OPC_CHANGE_ATTRIBUTE";
                return str;
            }

            if (changeMask_ & OPC_CHANGE_ACTIVE_STATE) str = "Active State, ";
            if (changeMask_ & OPC_CHANGE_ACK_STATE)    str += "Ack State, ";
            if (changeMask_ & OPC_CHANGE_ENABLE_STATE) str += "Enable State, ";
            if (changeMask_ & OPC_CHANGE_QUALITY)      str += "Quality, ";
            if (changeMask_ & OPC_CHANGE_SEVERITY)     str += "Serverity, ";
            if (changeMask_ & OPC_CHANGE_SUBCONDITION) str += "Subconditionn, ";
            if (changeMask_ & OPC_CHANGE_MESSAGE)      str += "Message, ";
            if (changeMask_ & OPC_CHANGE_ATTRIBUTE)    str += "Attribute";

            if (eTextMode == OpcTextMode::Lowercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                  // destination
                    tolower);                    // operation

            else if (eTextMode == OpcTextMode::Uppercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                  // destination
                    toupper);                    // operation

            return str;
        }

        string AeEvent::GetNewStateAsText(OpcTextMode eTextMode)
        {
            string str;
            if (eTextMode == OpcTextMode::Valuename) {
                if (newState_ & OPC_CONDITION_ACTIVE)   str = "OPC_CONDITION_ACTIVE, ";
                if (newState_ & OPC_CONDITION_ACKED)    str += "OPC_CONDITION_ACKED, ";
                if (newState_ & OPC_CONDITION_ENABLED)  str += "OPC_CONDITION_ENABLED";
                return str;
            }

            str = (newState_ & OPC_CONDITION_ACTIVE) ? "Active, " : "Inactive, ";
            str += (newState_ & OPC_CONDITION_ACKED) ? "Acked, " : "Unacked, ";
            str += (newState_ & OPC_CONDITION_ENABLED) ? "Enabled" : "Disabled";

            if (eTextMode == OpcTextMode::Lowercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                  // destination
                    tolower);                    // operation

            else if (eTextMode == OpcTextMode::Uppercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                  // destination
                    toupper);                    // operation

            return str;
        }



        string AeEvent::GetQualityAsText()
        {
            return Technosoftware::DaAeHdaClient::QualityAsText(quality_);
        }

        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS AeNewEventsImpl
        //----------------------------------------------------------------------------------------------------------------------
        //
        // Please refer to class AeNewEvents for the description and documentation of attributes and member functions.
        //
        // Since the ...Impl classes are used only by one object all function members which are used only once are declared as
        // inline functions.
        //

        /**
         * @class    AeNewEventsImpl
         *
         * @brief    An ae new events implementation.
         */

        class AeNewEventsImpl
        {
        public:

            /**
             * @fn    AeNewEventsImpl( ClientHandle hClientSubscription, bool bRefresh, bool bLastRefresh, uint32_t dwCount );
             *
             * @brief    Constructor.
             *
             * @param    hClientSubscription    The client subscription.
             * @param    bRefresh               true to refresh.
             * @param    bLastRefresh           true to last refresh.
             * @param    dwCount                   Number of.
             */

            AeNewEventsImpl(Base::ClientHandle hClientSubscription, bool bRefresh, bool bLastRefresh, uint32_t dwCount);
            ~AeNewEventsImpl() throw ();

            AeEvent* DetachEvent();

            /**
             * @brief    The client subscription.
             */

            Base::ClientHandle          m_hClientSubscription;

            /**
             * @brief    true to refresh.
             */

            bool                 m_fRefresh;

            /**
             * @brief    true to last refresh.
             */

            bool                 m_fLastRefresh;

            /**
             * @brief    Number of.
             */

            uint32_t              m_dwCount;

            /**
             * @brief    The events.
             */

            queue<AeEvent*>   m_qEvents;
        };


        //----------------------------------------------------------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------------------------------------------------------
        inline AeNewEventsImpl::AeNewEventsImpl(Base::ClientHandle hClientSubscription, bool bRefresh, bool bLastRefresh, uint32_t dwCount)
        {
            m_hClientSubscription = hClientSubscription;
            m_fRefresh = bRefresh;
            m_fLastRefresh = bLastRefresh;
            m_dwCount = dwCount;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Destructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    inline AeNewEventsImpl::~AeNewEventsImpl() throw ()
         *
         * @brief    Destructor.
         */

        inline AeNewEventsImpl::~AeNewEventsImpl() throw ()
        {
            try {
                AeEvent* pEvent = NULL;
                while ((pEvent = DetachEvent()) != 0) {
                    delete pEvent;
                }
            }
            catch (...) {}
        }


        //----------------------------------------------------------------------------------------------------------------------
        // DetachEvent
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    inline AeEvent* AeNewEventsImpl::DetachEvent()
         *
         * @brief    Detach event.
         *
         * @return    null if it fails, else an AeEvent*.
         */

        inline AeEvent* AeNewEventsImpl::DetachEvent()
        {
            AeEvent* pEvent = NULL;
            if (!m_qEvents.empty()) {
                pEvent = m_qEvents.front();
                m_qEvents.pop();
            }
            return pEvent;
        }


        /// <summary>
        /// Constructs a new collection object of received events.
        /// 
        /// 
        /// </summary>
        /// <remarks>
        /// Only ClientSdk classes can create AeNewEvents
        /// instances. 
        /// </remarks>                                            
        AeNewEvents::AeNewEvents(Base::ClientHandle hClientSubscription, bool bRefresh, bool bLastRefresh, uint32_t dwCount
        ) throw (Technosoftware::Base::Exception) : OpcObject(NULL, "AeNewEvents")
        {
            impl_.Attach(new (std::nothrow) AeNewEventsImpl(hClientSubscription, bRefresh, bLastRefresh, dwCount));
            if (!impl_) throw Technosoftware::Base::OutOfMemoryException();
        }


        /// <summary>
        /// Destroys the object. 
        /// </summary>           
        AeNewEvents::~AeNewEvents() throw () {}


        /// <summary>
        /// </summary>                                                  
        Base::ClientHandle AeNewEvents::GetSubscriptionHandle() const { return impl_->m_hClientSubscription; }


        /// <summary>
        /// </summary>                                                  
        bool AeNewEvents::IsRefresh() const { return impl_->m_fRefresh; }


        /// <summary>
        /// </summary>                                                  
        bool AeNewEvents::IsLastRefresh() const { return impl_->m_fLastRefresh; }


        /// <summary>
        /// </summary>                                                  
        uint32_t AeNewEvents::GetCount() const { return impl_->m_dwCount; }


        /// <summary>
        /// </summary>                                                  
        AeEvent* AeNewEvents::DetachEvent() { return impl_->DetachEvent(); }


        /// <summary>
        /// </summary>                                                  
        void AeNewEvents::AddEvent(AeEvent* pEvent) { impl_->m_qEvents.push(pEvent); }

    }
}
