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
#include "DaAeHdaClient/Ae/AeSubscription.h"
#include "DaAeHdaClient/Ae/AeSubscriptionImpl.h"
#include "DaAeHdaClient/Ae/AeServer.h"
#include "DaAeHdaClient/Ae/AeServerImpl.h"
#include "DaAeHdaClient/Ae/AeEvent.h"

#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {

        //----------------------------------------------------------------------------------------------------------------------
        // EventNotifierThread                                                                                            THREAD
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    unsigned __stdcall EventNotifierThread( LPVOID pAttr )
         *
         * @brief    Event notifier thread.
         *
         * @param    pAttr    The attribute.
         *
         * @return    An unsigned.
         */

        unsigned __stdcall EventNotifierThread(LPVOID pAttr)
        {
            AeSubscriptionImpl* pSubscr = static_cast<AeSubscriptionImpl *>(pAttr);
            _ASSERTE(pSubscr);

            DWORD    dwWaitSignal;
            HANDLE   hObjects[2];

            hObjects[0] = pSubscr->m_hTerminate;
            hObjects[1] = pSubscr->m_hNewEvents;

            do {                                         // Thread Loop
                dwWaitSignal = WaitForMultipleObjects(
                    2, hObjects,
                    FALSE,         // Only one object must be signaled
                    INFINITE);

                if (dwWaitSignal == (WAIT_OBJECT_0 + 1)) {  // There are new Events

                    pSubscr->m_csNewEvents.Lock();         // Take ownership of new events
                    queue<AeNewEvents*> stagingArea;

                    while (!pSubscr->m_qNewEvents.empty())
                    {
                        AeNewEvents* pNewEvents = pSubscr->m_qNewEvents.front();
                        _ASSERTE(pNewEvents);                // Should not be NULL if thread is signaled
                        pSubscr->m_qNewEvents.pop();
                        stagingArea.push(pNewEvents);
                    }

                    pSubscr->m_csNewEvents.Unlock();

                    while (!stagingArea.empty())
                    {
                        AeNewEvents * pNewEvents = stagingArea.front();
                        stagingArea.pop();

                        // Forward the new Events to the user callback
                        pSubscr->m_pIUserEventSink->NewEvents(pNewEvents);
                    }
                }
            } while (dwWaitSignal != WAIT_OBJECT_0);     // Not terminate event

            _endthreadex(0);                           // The thread terminates.
            return 0;

        } // EventNotifierThread


        AeSubscription::AeSubscription(AeServer* pParent,
            AeIEventSink* pIUserEventSink,
            uint32_t hClientSubscription,
            bool  fActive,
            uint32_t dwBufferTime,
            uint32_t dwMaxSize
        ) noexcept(false) : OpcObject((OpcObject*)pParent, "AeSubscription")
        {
            try {
                impl_.Attach(new (std::nothrow) AeSubscriptionImpl(
                    pParent,
                    pIUserEventSink,
                    hClientSubscription,
                    fActive,
                    dwBufferTime,
                    dwMaxSize));
                if (!impl_) throw Technosoftware::Base::OutOfMemoryException();
            }
            catch (Technosoftware::Base::Status &e) {
                // Use this instance as source of the error
                throw Technosoftware::Base::Status(e);
            }
        }


        AeSubscription::~AeSubscription() throw () {}


        bool AeSubscription::IsActive() const throw () { return impl_->m_fActive; }


        Base::ClientHandle AeSubscription::GetClientHandle() const throw () { return impl_->m_hClientSubscription; }


        uint32_t AeSubscription::RevisedBufferTime() const throw () { return impl_->m_dwRevisedBufferTime; }



        uint32_t AeSubscription::RevisedMaxSize() const throw () { return impl_->m_dwRevisedMaxSize; }



        Technosoftware::Base::Status AeSubscription::SetActive(bool fActive) { return Technosoftware::DaAeHdaClient::GetStatusFromHResult(impl_->SetActive(fActive),Base::StatusCode::AeFuncCall); }


        Technosoftware::Base::Status AeSubscription::ToggleActive() { return Technosoftware::DaAeHdaClient::GetStatusFromHResult(impl_->ToggleActive(),Base::StatusCode::AeFuncCall); }


        Technosoftware::Base::Status AeSubscription::Refresh() { return Technosoftware::DaAeHdaClient::GetStatusFromHResult(impl_->Refresh(),Base::StatusCode::AeFuncCall); }


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS AeSubscriptionImpl
        //----------------------------------------------------------------------------------------------------------------------
        //
        // Please refer to class AeNewEvents for the description and documentation of attributes and member functions.
        //
        // Since the ...Impl classes are used only by one object all function members which are used only once are declared as
        // inline functions.
        //

        //----------------------------------------------------------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    AeSubscriptionImpl::AeSubscriptionImpl( AeServer* pParent, AeIEventSink* pIUserEventSink, uint32_t hClientSubscription, bool isActive_, uint32_t dwBufferTime, uint32_t dwMaxSize ) throw (Technosoftware::Base::Exception)
         *
         * @brief    Constructor.
         *
         * @exception    Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
         *
         * @param [in,out]    pParent               If non-null, the parent.
         * @param [in,out]    pIUserEventSink    If non-null, the i user event sink.
         * @param    hClientSubscription           The client subscription.
         * @param    isActive_                       true to active.
         * @param    dwBufferTime               The buffer time.
         * @param    dwMaxSize                   Size of the maximum.
         */

        AeSubscriptionImpl::AeSubscriptionImpl(AeServer* pParent,
            AeIEventSink* pIUserEventSink,
            uint32_t hClientSubscription,
            bool  fActive,
            uint32_t dwBufferTime,
            uint32_t dwMaxSize) throw (Technosoftware::Base::Exception) : OpcObject(NULL, "AeSubscriptionImpl")
        {
            if (!pParent) throw Technosoftware::Base::InvalidArgumentException();
            if (!pIUserEventSink) throw Technosoftware::Base::InvalidArgumentException();

            // The server object must be connected to an AE server
            if (!pParent->IsConnected()) throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);

            m_dwEventSinkCookie = 0;
            m_pEventCallbackRef = NULL;
            m_fActive = fActive;
            m_hClientSubscription = hClientSubscription;
            m_pIUserEventSink = pIUserEventSink;

            CComPtr<IOPCEventServer> IOPCEventServer = pParent->impl_->opcAESrv_.iOPCEventServer_;
            if (!IOPCEventServer) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE));

            m_hNewEvents.Attach(CreateEvent(NULL, FALSE, FALSE, NULL));
            if (!m_hNewEvents) throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(HRESULT_FROM_WIN32(GetLastError()));

            m_hTerminate.Attach(CreateEvent(NULL, FALSE, FALSE, NULL));
            if (!m_hTerminate) throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(HRESULT_FROM_WIN32(GetLastError()));

            unsigned uThreadID;                          // Thread identifier
            HANDLE h = (HANDLE)_beginthreadex(
                NULL,                // No thread security attributes
                0,                   // Default stack size  
                EventNotifierThread, // Pointer to thread function
                this,                // Pass class to new thread for access to the update functions
                0,                   // Run thread immediately
                &uThreadID);        // Thread identifier

            if (!h) throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(HRESULT_FROM_WIN32(GetLastError()));
            m_hEventNotifierThread.Attach(h);

            Technosoftware::Base::Status hr = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
            try {
                CreateSubscription(IOPCEventServer,
                    hClientSubscription,
                    fActive,
                    dwBufferTime,
                    dwMaxSize);
            }
            catch (Technosoftware::Base::Status e) {
                hr = e;
            }
            catch (...) {
                hr = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }
            if (hr.IsNotGood()) {
                // Terminate the Event Notifier Thread
                if (!SetEvent(m_hTerminate) || (WaitForSingleObject(m_hEventNotifierThread, 1000) == WAIT_TIMEOUT)) {
                    TerminateThread(m_hEventNotifierThread, 1);
                }
                throw hr;
            }
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Destructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    AeSubscriptionImpl::~AeSubscriptionImpl() throw ()
         *
         * @brief    Destructor.
         */

        AeSubscriptionImpl::~AeSubscriptionImpl() throw ()
        {
            try {
                if (m_dwEventSinkCookie) {
                    m_ICP->Unadvise(m_dwEventSinkCookie);
                }
                if (!SetEvent(m_hTerminate) || (WaitForSingleObject(m_hEventNotifierThread, 1000) == WAIT_TIMEOUT)) {
                    TerminateThread(m_hEventNotifierThread, 1);
                }

                // remove all events which was not forwarded to the user event sink
                AeNewEvents* pNewEvents;
                while (!m_qNewEvents.empty()) {
                    pNewEvents = m_qNewEvents.front();
                    m_qNewEvents.pop();
                    delete pNewEvents;
                }
            }
            catch (...) {}
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Activate
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT AeSubscriptionImpl::SetActive( bool isActive_ )
         *
         * @brief    Sets an active.
         *
         * @param    isActive_    true to active.
         *
         * @return    A HRESULT.
         */

        HRESULT AeSubscriptionImpl::SetActive(bool fActive)
        {
            if (fActive == m_fActive) {                  // Already in the requested state
                return S_OK;
            }
            return ToggleActive();
        }


        //----------------------------------------------------------------------------------------------------------------------
        // ToggleActiveState
        //----------------------------------------------------------------------------------------------------------------------
        inline HRESULT AeSubscriptionImpl::ToggleActive()
        {
            BOOL  fNewState = !m_fActive;
            DWORD dwDummyTime;
            DWORD dwDummySize;

            HRESULT hr = m_IOPCEventSubscriptionMgt->SetState(
                &fNewState,          // New Active State
                NULL,                // Ignore Max. Time
                NULL,                // ignore Max. Size
                m_hClientSubscription,
                &dwDummyTime,
                &dwDummySize);

            if (SUCCEEDED(hr)) {
                m_fActive = fNewState ? true : false;
            }
            return hr;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Refresh
        //----------------------------------------------------------------------------------------------------------------------
        inline HRESULT AeSubscriptionImpl::Refresh()
        {
            return m_IOPCEventSubscriptionMgt->Refresh(m_dwEventSinkCookie);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // CreateSubscription
        // ------------------
        //    Creates the subscription.
        //----------------------------------------------------------------------------------------------------------------------
        inline void AeSubscriptionImpl::CreateSubscription(
            CComPtr<IOPCEventServer> IOPCEventServer,
            DWORD hClientSubscription,
            bool  fActive,
            DWORD dwBufferTime,
            DWORD dwMaxSize) throw (Technosoftware::Base::Exception)
        {
            HRESULT hr = IOPCEventServer->CreateEventSubscription(
                fActive,                // Current active state
                dwBufferTime,           // Buffer Time
                dwMaxSize,              // Max Size
                hClientSubscription,    // Client Handle
                IID_IOPCEventSubscriptionMgt,
                (LPUNKNOWN*)&m_IOPCEventSubscriptionMgt,
                &m_dwRevisedBufferTime,
                &m_dwRevisedMaxSize);
            if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::AeFuncCall));

            CComQIPtr<IConnectionPointContainer, &IID_IConnectionPointContainer> ICPC(m_IOPCEventSubscriptionMgt);
            if (!ICPC) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::AeFuncCall));

            ICPC->FindConnectionPoint(IID_IOPCEventSink, &m_ICP);
            if (!m_ICP) throw Technosoftware::Base::StatusException(Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::AeFuncCall)));

            // Create an instance of the callback function
            m_pEventCallbackRef = new (std::nothrow) CComObjectOPCEventSink;
            if (!m_pEventCallbackRef) throw Technosoftware::Base::OutOfMemoryException();
            m_pEventCallbackRef->SetSubscriptionRef(this);
            m_pEventCallbackRef->AddRef();               // Add temporary reference during creation
            hr = S_OK;
            try {
                // Create a connection between the connection point
                // and the created callback function.
                // Note : A Pointer to the IUnknown interface of the
                // created Event Sink must be passed to the advise function.
                CComPtr<IUnknown> IUnkCallback(m_pEventCallbackRef);
                if (!IUnkCallback) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE));

                hr = m_ICP->Advise(IUnkCallback, &m_dwEventSinkCookie);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr)));
            }
            catch (HRESULT hrEx) {
                hr = hrEx;
            }
            m_pEventCallbackRef->Release();              // Release temporary reference
                                                         // This also destroys the instance of the callback
                                                         // function if the advise function failed.
            if (FAILED(hr)) {
                m_pEventCallbackRef = NULL;
                throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::AeFuncCall);
            }
        }
    }
}