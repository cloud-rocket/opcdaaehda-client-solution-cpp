/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __AeEVENTSINK_H
#define __AeEVENTSINK_H

#include "OpcInternal.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class AeEventQueue;
        class AeSubscriptionImpl;


        //----------------------------------------------------------------------------------------------------------------------
        // OPCEventSink Object
        //----------------------------------------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------------------------------------
        // CLASS CComOPCEventSinkImpl
        //----------------------------------------------------------------------------------------------------------------------
        class CComOPCEventSinkImpl : public IOPCEventSink
        {
        public:
            // Construction
            CComOPCEventSinkImpl();

            // Destruction
            ~CComOPCEventSinkImpl();

            inline void SetSubscriptionRef(AeSubscriptionImpl* pSubscrRef) { m_pSubscrRef = pSubscrRef; }

            // IOPCEventSink functions
            STDMETHODIMP OnEvent(
                /* [in] */           OPCHANDLE      hClientSubscription,
                /* [in] */           BOOL           bRefresh,
                /* [in] */           BOOL           bLastRefresh,
                /* [in] */           DWORD          dwCount,
                /* [size_is][in] */  ONEVENTSTRUCT* pEvents);

        protected:
            AeSubscriptionImpl*  m_pSubscrRef;
        };


        //----------------------------------------------------------------------------------------------------------------------
        // CLASS CComOPCEventSink
        //----------------------------------------------------------------------------------------------------------------------
        template <class ThreadModel = CComObjectThreadModel>
        class ATL_NO_VTABLE CComOPCEventSink :
            public CComOPCEventSinkImpl,
            public CComObjectRootEx< ThreadModel >
        {
        public:
            BEGIN_COM_MAP(CComOPCEventSink)
                COM_INTERFACE_ENTRY_IID(IID_IOPCEventSink, CComOPCEventSinkImpl)
            END_COM_MAP()
        };


        //----------------------------------------------------------------------------------------------------------------------
        // TYPEDEF CComObject CComObjectOPCEventSink
        //----------------------------------------------------------------------------------------------------------------------
        typedef  CComObjectNoLock< CComOPCEventSink<> > CComObjectOPCEventSink;
    }
}

#endif // __AeEVENTSINK_H
