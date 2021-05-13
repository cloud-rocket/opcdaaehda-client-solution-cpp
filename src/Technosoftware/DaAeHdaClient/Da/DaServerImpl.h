/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __DaSERVERIMPL_H
#define __DaSERVERIMPL_H

#include "DaAeHdaClient/OpcBase.h"
#include "OpcAccess.h"

#include "Base/Status.h"


namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //----------------------------------------------------------------------------------------------------------------------
        // CLASS DaServerImpl
        //----------------------------------------------------------------------------------------------------------------------
        class DaServerImpl
        {
        protected:
            typedef void(*PFN_StatusSink)(Technosoftware::Base::Status&, DaServerStatus&);
            typedef void(*PFN_StatusSinkWithCookie)(Technosoftware::Base::Status&, DaServerStatus&, void*);

            // Construction / Destruction
        public:
            DaServerImpl() throw ();
            ~DaServerImpl() throw ();

            // Operations
            inline Technosoftware::Base::Status Connect(const string& sServerName, const string& sMachineName, DWORD dwCoInit);
            void Disconnect();
            Technosoftware::Base::Status UpdateStatus();
            Technosoftware::Base::Status PollStatus(PFN_StatusSinkWithCookie pfnStatusSinkWithCookie, uint32_t dwRefreshRate, void* pCookie);
            Technosoftware::Base::Status SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason));
            inline Technosoftware::Base::Status RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix);

            // Implementation
        protected:
            friend class DaServer;
            friend class DaGroup;
            friend class DaGroupImpl;
            friend class DaBrowserImpl;

            OpcAccess           m_OPCDASrv;
            DaServerStatus    m_Status;
            CComPtr<IOPCCommon>  m_pIOPCCommon;

            //
            // PollStatus
            //
            friend unsigned __stdcall PollDaStatusThread(LPVOID pAttr);

            // Handles for the PollDaStatusThread
            HANDLE            m_hTerminate;           // Event Handle
            HANDLE            m_hPollStatusThread;    // Thread Handle
            CInterlockedValue m_StatusRefreshRate;    // in ms

            void*                      m_pPollStatusCookie;
            PFN_StatusSink             m_pfnStatusSink;
            PFN_StatusSinkWithCookie   m_pfnStatusSinkWithCookie;

            // Called by the PollStatus Thread and by UpdateStatus()
            Technosoftware::Base::Status  GetStatus(IOPCServer* pIOPCServer, DaServerStatus* pStatus);

            // Members for Shutdown Request Subscription
            CComPtr<IConnectionPoint>  m_ICP;
            DWORD                      m_dwShutdownRequestCookie;
            CComObjectOPCShutdown*     m_pShutdownCallbackRef;
        };
    }
}

#endif // __DaSERVERIMPL_H
