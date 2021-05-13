/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __AeSUBSCRIPTIONIMPL_H
#define __AeSUBSCRIPTIONIMPL_H

#include "DaAeHdaClient/OpcBase.h"
#include "AeEventSinkImpl.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class AeServer;
        class AeIEventSink;
        class AeNewEvents;


#if _ATL_VER < 0x700
        class CHandle
        {
        public:
            inline CHandle() throw () : m_h(NULL) {}
            inline ~CHandle() throw () { if (m_h) ::CloseHandle(m_h); }

            inline operator HANDLE() const throw () { return m_h; }

            // Attach to an existing handle (takes ownership).
            inline void Attach(HANDLE h) throw ()
            {
                ATLASSERT(m_h == NULL);
                m_h = h;    // Take ownership
            }

        public:
            HANDLE m_h;
    };
#endif // _ATL_VER < 0x700


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS AeSubscriptionImpl
        //----------------------------------------------------------------------------------------------------------------------
        class AeSubscriptionImpl : protected OpcObject
        {
        public:
            AeSubscriptionImpl(AeServer* pParent,
                AeIEventSink* pIUserEventSink,
                uint32_t hClientSubscription,
                bool  fActive,
                uint32_t dwBufferTime,
                uint32_t dwMaxSize) throw (Technosoftware::Base::Exception);
            ~AeSubscriptionImpl() throw ();

            // Operations
            HRESULT SetActive(bool fActive);
            inline HRESULT ToggleActive();
            inline HRESULT Refresh();

            // Implementation
            inline void CreateSubscription(CComPtr<IOPCEventServer> IOPCEventServer,
                DWORD hClientSubscription,
                bool  fActive,
                DWORD dwBufferTime,
                DWORD dwMaxSize) throw (Technosoftware::Base::Exception);

            bool                                    m_fActive;
            DWORD                                m_dwEventSinkCookie;
            OPCHANDLE                            m_hClientSubscription;
            DWORD                                m_dwRevisedBufferTime;
            DWORD                                m_dwRevisedMaxSize;
            CComPtr<IOPCEventSubscriptionMgt>    m_IOPCEventSubscriptionMgt;
            CComPtr<IConnectionPoint>            m_ICP;
            CComObjectOPCEventSink*                m_pEventCallbackRef;

            friend unsigned __stdcall EventNotifierThread(LPVOID pAttr);
            friend class CComOPCEventSinkImpl;

            CComAutoCriticalSection                m_csNewEvents;
            queue<AeNewEvents*>                    m_qNewEvents;
            AeIEventSink*                        m_pIUserEventSink;
            CHandle                                m_hNewEvents;           // Event Handle
            CHandle                                m_hTerminate;           // Event Handle
            CHandle                                m_hEventNotifierThread; // Thread Handle
        };
}
}
#endif // __AeSUBSCRIPTIONIMPL_H
