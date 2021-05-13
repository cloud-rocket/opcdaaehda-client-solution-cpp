/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the AeServer class.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_AESERVERIMPL_H
#define TECHNOSOFTWARE_AESERVERIMPL_H

#include "DaAeHdaClient/OpcBase.h"
#include "OpcAccess.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //----------------------------------------------------------------------------------------------------------------------
        // CLASS AeServerImpl
        //----------------------------------------------------------------------------------------------------------------------
        class AeServerImpl
        {
            // Construction / Destruction
        public:
            AeServerImpl() throw ();
            ~AeServerImpl() throw ();

            // Operations
            inline Technosoftware::Base::Status Connect(const string& sServerName, const string& sMachineName, DWORD dwCoInit);
            inline void Disconnect();
            HRESULT UpdateStatus();
            HRESULT PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status&, AeServerStatus&), uint32_t dwRefreshRate);
            Technosoftware::Base::Status SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason));
            inline Technosoftware::Base::Status RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix);

            // Implementation
        protected:
            friend class AeServer;
            friend class AeSubscriptionImpl;

            OpcAccess           opcAESrv_;
            AeServerStatus      status_;
            CComPtr<IOPCCommon> iOPCCommon_;

            //
            // PollStatus
            //
            friend unsigned __stdcall PollAeStatusThread(LPVOID pAttr);

            // Handles for the PollAeStatusThread
            HANDLE              terminate_;           // Event Handle
            HANDLE              pollStatusThread_;    // Thread Handle
            CInterlockedValue   statusRefreshRate_;   // in ms

            void(*statusSink_)(Technosoftware::Base::Status&, AeServerStatus&);
            // Called by the PollStatus Thread and by UpdateStatus()
            HRESULT  GetStatus(IOPCEventServer* pIOPCEventServer, AeServerStatus* pStatus);

            // Members for Shutdown Request Subscription
            CComPtr<IConnectionPoint>  icp_;
            DWORD                      shutdownRequestCookie_;
            CComObjectOPCShutdown*     shutdownCallbackRef_;
        };
    }
}

#endif /* TECHNOSOFTWARE_AESERVERIMPL_H */
