/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __OPCINTERNAL_H
#define __OPCINTERNAL_H

#include <atlbase.h>
#include <atlcom.h>

#include <queue>
using std::queue;

using std::transform;

#ifdef _OPC_EVALUATION_VERSION
//#include "License\OpcTrial.h"
//extern OpcTrial gOpcTrial;
#endif

#include "ClientSdk.h"
#include "OpcErrors.h"


#include "DaAeHdaClient/OpcBase.h"
#include "OpcUti.h"
#include "OpcDefs.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //----------------------------------------------------------------------------------------------------------------------
        // DUMMY CLASSES
        //----------------------------------------------------------------------------------------------------------------------
        // Dummy class to hide CSimpleArray from the ClientSdk interface.
        class OpcItemDefArray : public CSimpleArray<OPCITEMDEF> {};


        //----------------------------------------------------------------------------------------------------------------------
        // CLASS CInterlockedValue
        //----------------------------------------------------------------------------------------------------------------------
        // Utility class which prevents unsafe access of a variable
        // used by multiple threads.
        class CInterlockedValue
        {
        public:
            CInterlockedValue() : m_lValue(0) {}
            ~CInterlockedValue() {}

        public:
            inline LONG  GetValue() {
                return InterlockedExchange(&m_lValue, m_lValue);
            }
            //   inline LONG  CompareAndSetValue( LONG lNewValue, LONG lComperand ) {
            //            return (LONG)InterlockedCompareExchange( (PVOID*)&m_lValue, (PVOID)lNewValue, (PVOID)lComperand );
            //         }
            inline void  SetValue(LONG lNewValue) {
                InterlockedExchange(&m_lValue, lNewValue);
            }

        private:
            LONG  m_lValue;
        };


        //----------------------------------------------------------------------------------------------------------------------
        // OPCShutdown Object
        //----------------------------------------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------------------------------------
        // CLASS CComOPCShutdownImpl
        //----------------------------------------------------------------------------------------------------------------------
        class CComOPCShutdownImpl : public IOPCShutdown
        {
        public:
            // Construction
            CComOPCShutdownImpl();
            void Create(void(*pfnShutdownRequestSink)(string& sReason));

            // Destruction
            ~CComOPCShutdownImpl();

            // IOPCShutdown functions
            STDMETHODIMP ShutdownRequest(
                /* [in] */           LPCWSTR     szReason);

        protected:
            void(*m_pfnShutdownRequestSink)(string&);
        };


        //----------------------------------------------------------------------------------------------------------------------
        // CLASS CComOPCShutdown
        //----------------------------------------------------------------------------------------------------------------------
        template <class ThreadModel = CComObjectThreadModel>
        class ATL_NO_VTABLE CComOPCShutdown :
            public CComOPCShutdownImpl,
            public CComObjectRootEx< ThreadModel >
        {
        public:
            BEGIN_COM_MAP(CComOPCShutdown)
                COM_INTERFACE_ENTRY_IID(IID_IOPCShutdown, CComOPCShutdownImpl)
            END_COM_MAP()
        };


        //----------------------------------------------------------------------------------------------------------------------
        // TYPEDEF CComObject CComObjectOPCShutdown
        //----------------------------------------------------------------------------------------------------------------------
        typedef  CComObjectNoLock< CComOPCShutdown<> > CComObjectOPCShutdown;

    }
}
#endif // __OPCINTERNAL_H
