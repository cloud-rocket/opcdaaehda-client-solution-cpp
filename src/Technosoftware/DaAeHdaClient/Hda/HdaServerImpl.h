/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __HDASERVERIMPL_H
#define __HDASERVERIMPL_H

#include "DaAeHdaClient/OpcBase.h"
#include "OpcAccess.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //----------------------------------------------------------------------------------------------------------------------
        // CLASS HdaServerImpl
        //----------------------------------------------------------------------------------------------------------------------
        class HdaServerImpl
        {
        protected:
            typedef void(*PFN_StatusSink)(Technosoftware::Base::Status&, HdaServerStatus&);
            typedef void(*PFN_StatusSinkWithCookie)(Technosoftware::Base::Status&, HdaServerStatus&, void*);

            // Construction / Destruction
        public:
            HdaServerImpl() throw ();
            ~HdaServerImpl() throw ();

            // Operations
            inline Technosoftware::Base::Status Connect(const string& sServerName, const string& sMachineName, DWORD dwCoInit);
            void Disconnect();
            HRESULT UpdateStatus();
            HRESULT PollStatus(PFN_StatusSinkWithCookie pfnStatusSinkWithCookie, uint32_t dwRefreshRate, void* pCookie);
            Technosoftware::Base::Status SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason));
            inline Technosoftware::Base::Status RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix);
			Technosoftware::Base::Status GetItemAttributes(HdaItemAttributes& hdaitemAtttributes);
			Technosoftware::Base::Status GetAggregates(HdaAggregates& hdaÂggregates);
			Technosoftware::Base::Status ReadRaw(const char* itemId, Base::Timestamp startTime, Base::Timestamp endTime, DWORD maxValues, BOOL bounds, HdaItem* hdaItem, HRESULT* error);

            // Implementation
        protected:
            friend class HdaServer;

            OpcAccess           m_OPCHDASrv;
            HdaServerStatus    m_Status;
            CComPtr<IOPCCommon>  m_pIOPCCommon;

            //
            // PollStatus
            //
            friend unsigned __stdcall PollHdaStatusThread(LPVOID pAttr);

            // Handles for the PollHdaStatusThread
            HANDLE            m_hTerminate;           // Event Handle
            HANDLE            m_hPollStatusThread;    // Thread Handle
            CInterlockedValue m_StatusRefreshRate;    // in ms

            void*                      m_pPollStatusCookie;
            PFN_StatusSink             m_pfnStatusSink;
            PFN_StatusSinkWithCookie   m_pfnStatusSinkWithCookie;

            // Called by the PollStatus Thread and by UpdateStatus()
            HRESULT  GetStatus(IOPCHDA_Server* pIOPCServer, HdaServerStatus* pStatus);
            OPCHANDLE GetItemHandle(const char* itemId);
            void GetTimeFromStringCleanup(OPCHDA_TIME* pTime);

            // Members for Shutdown Request Subscription
            CComPtr<IConnectionPoint>  m_ICP;
            DWORD                      m_dwShutdownRequestCookie;
            CComObjectOPCShutdown*     m_pShutdownCallbackRef;
        };
    }
}
#endif // __HDASERVERIMPL_H
