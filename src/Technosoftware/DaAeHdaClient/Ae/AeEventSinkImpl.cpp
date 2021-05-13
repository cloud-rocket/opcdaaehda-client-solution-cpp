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

#include "DaAeHdaClient/Ae/AeEventSinkImpl.h"
#include "DaAeHdaClient/Ae/AeEvent.h"
#include "DaAeHdaClient/Ae/AeSubscriptionImpl.h"
#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //----------------------------------------------------------------------------------------------------------------------
        // OPCEventSink Object
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    CComOPCEventSinkImpl::CComOPCEventSinkImpl()
         *
         * @brief    Default constructor.
         */

        CComOPCEventSinkImpl::CComOPCEventSinkImpl()
        {
            // cout << "CComOPCEventSinkImpl c'tor" << endl;
        }

        /**
         * @fn    CComOPCEventSinkImpl::~CComOPCEventSinkImpl()
         *
         * @brief    Destructor.
         */

        CComOPCEventSinkImpl::~CComOPCEventSinkImpl()
        {
            // cout << "CComOPCEventSinkImpl d'tor" << endl;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION IOPCEventSink
        //----------------------------------------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------------------------------------
        // IOPCEventSink::OnEvent
        // ----------------------
        //    The Event Sink which receives the Events from the OPC Event Server.
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    STDMETHODIMP CComOPCEventSinkImpl::OnEvent( OPCHANDLE hClientSubscription, BOOL bRefresh, BOOL bLastRefresh, DWORD dwCount, ONEVENTSTRUCT* pEvents )
         *
         * @brief    Executes the event action.
         *
         * @exception    E_OUTOFMEMORY    Thrown when an outofmemory error condition occurs.
         *
         * @param    hClientSubscription    The client subscription.
         * @param    bRefresh               true to refresh.
         * @param    bLastRefresh           true to last refresh.
         * @param    dwCount                   Number of.
         * @param [in,out]    pEvents           If non-null, the events.
         *
         * @return    A STDMETHODIMP.
         */

        STDMETHODIMP CComOPCEventSinkImpl::OnEvent(
            /* [in] */           OPCHANDLE      hClientSubscription,
            /* [in] */           BOOL           bRefresh,
            /* [in] */           BOOL           bLastRefresh,
            /* [in] */           DWORD          dwCount,
            /* [size_is][in] */  ONEVENTSTRUCT* pEvents)
        {
            AeNewEvents* pNewEvents = NULL;
            try {
                pNewEvents = new (std::nothrow) AeNewEvents(
                    hClientSubscription,
                    bRefresh ? true : false,
                    bLastRefresh ? true : false,
                    dwCount);
                if (!pNewEvents) throw Technosoftware::Base::OutOfMemoryException();

                AeEvent* pEvent;
                for (unsigned int i = 0; i < dwCount; i++) {
                    pEvent = new (std::nothrow) AeEvent(&pEvents[i]);
                    if (!pEvent) throw Technosoftware::Base::OutOfMemoryException();
                    pNewEvents->AddEvent(pEvent);
                }

                m_pSubscrRef->m_csNewEvents.Lock();
                m_pSubscrRef->m_qNewEvents.push(pNewEvents);
                m_pSubscrRef->m_csNewEvents.Unlock();
                SetEvent(m_pSubscrRef->m_hNewEvents);
            }
            catch (...) {
                if (pNewEvents)
                    delete pNewEvents;
            }
            return S_OK;                                 // Must be always S_OK
        }
    }
}
