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
#include "DaAeHdaClient/Ae/AeServer.h"
#include "AeServerImpl.h"
#include "Base/Timestamp.h"
#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        AeServer::AeServer() noexcept(false) : OpcObject(NULL, "AeServer")
        {
            impl_.Attach(new (std::nothrow) AeServerImpl);
            if (!impl_) throw Technosoftware::Base::OutOfMemoryException();
        }

        AeServer::~AeServer() noexcept
        {
            DeleteAllChildren();                         // Deletes all subscriptions
        }

        AeServerStatus& AeServer::GetStatus() const { return impl_->status_; }

        bool AeServer::IsConnected() const noexcept { return impl_->opcAESrv_.iOPCEventServer_ ? true : false; }

        Technosoftware::Base::Status AeServer::Connect(const string& serverName, const string& machineName, uint32_t dcoInit)
        {
            return impl_->Connect(serverName, machineName, dcoInit);
        }

        void AeServer::Disconnect()
        {
            DeleteAllChildren();                         // Deletes all subscriptions
            impl_->Disconnect();
        }

        Technosoftware::Base::Status AeServer::UpdateStatus() { return Technosoftware::DaAeHdaClient::GetStatusFromHResult(impl_->UpdateStatus(),Base::StatusCode::AeFuncCall); }

        Technosoftware::Base::Status AeServer::PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& status, AeServerStatus& serverStatus), uint32_t refreshRate)
        {
            // Use _OpcSysResult because there are only local system function calls.
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(impl_->PollStatus(pfnStatusSink, refreshRate));
        }

        Technosoftware::Base::Status AeServer::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& reason))
        {
            return impl_->SetShutdownRequestSubscription(*pfnShutdownRequestSink);
        }

        Technosoftware::Base::Status AeServer::RegisterClientName(const string& clientName, bool machineNameAsPrefix)
        {
            return impl_->RegisterClientName(clientName, machineNameAsPrefix);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS AeServerImpl
        //----------------------------------------------------------------------------------------------------------------------
        //
        // Please refer to class AeServer for the description and documentation of attributes and member functions.
        //
        // Since the ...Impl classes are used only by one object all function members which are used only once are declared as
        // inline functions.
        //

        //----------------------------------------------------------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    AeServerImpl::AeServerImpl() throw ()
         *
         * @brief    Default constructor.
         */

        AeServerImpl::AeServerImpl() throw ()
        {
            terminate_ = NULL;
            pollStatusThread_ = NULL;
            statusSink_ = NULL;
            shutdownRequestCookie_ = 0;
            shutdownCallbackRef_ = NULL;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Destructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    AeServerImpl::~AeServerImpl() throw ()
         *
         * @brief    Destructor.
         */

        AeServerImpl::~AeServerImpl() throw ()
        {
            try {
                Disconnect();
            }
            catch (...) {}
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Connect
        //----------------------------------------------------------------------------------------------------------------------
        inline Technosoftware::Base::Status AeServerImpl::Connect(const string& sServerName, const string& sMachineName, DWORD dwCoInit)
        {
            if (opcAESrv_.iOPCEventServer_) {         // Must not be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            USES_CONVERSION;
            HRESULT hr = opcAESrv_.ConnectToEventServer(A2CT(sMachineName.c_str()), A2CT(sServerName.c_str()), FALSE, dwCoInit);
            // Note: Use _OpcSysResult and not _OpcAeResult because impl_->Connect() doesn't return
            // OPC Specific Error codes but the CO_E... error codes includes also facility code ITF.
            if (FAILED(hr)) return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);

            hr = opcAESrv_.iOPCEventServer_->QueryInterface(IID_IOPCCommon, (LPVOID*)&iOPCCommon_);
            if (SUCCEEDED(hr)) {
                hr = UpdateStatus();
            }
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::AeFuncCall);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Disconnect
        //----------------------------------------------------------------------------------------------------------------------
        inline void AeServerImpl::Disconnect()
        {
            SetShutdownRequestSubscription(NULL);      // Unsubscribe Sutdown Request
            PollStatus(0, NULL);                       // Remove PollStatus Thread
            iOPCCommon_ = NULL;
            opcAESrv_.DisconnectFromEventServer();
        }


        //----------------------------------------------------------------------------------------------------------------------
        // UpdateStatus
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT AeServerImpl::UpdateStatus()
         *
         * @brief    Updates the status.
         *
         * @return    A HRESULT.
         */

        HRESULT AeServerImpl::UpdateStatus()
        {
            if (!opcAESrv_.iOPCEventServer_) {        // Must be connected
                return OPC_E_SRVNOTCONNECTED;
            }
            return GetStatus(opcAESrv_.iOPCEventServer_, &status_);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // PollAeStatusThread                                                                                             THREAD
        // ------------------
        //    Retrieves periodically the status from the connected OPC Server.
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    unsigned __stdcall PollAeStatusThread( LPVOID pAttr )
         *
         * @brief    Poll ae status thread.
         *
         * @param    pAttr    The attribute.
         *
         * @return    An unsigned.
         */

        unsigned __stdcall PollAeStatusThread(LPVOID pAttr)
        {
            AeServerImpl* pAeServerImpl = static_cast<AeServerImpl*>(pAttr);
            _ASSERTE(pAeServerImpl);                   // Must not be NULL.

            {  // This braces defines a scope which guarantees that the
               // destructor of the used class instances is called.

                Technosoftware::Base::Status       res;
                AeServerStatus Status;
                IOPCEventServer*  iOPCEventServer_ = pAeServerImpl->opcAESrv_.iOPCEventServer_;

                do {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(pAeServerImpl->GetStatus(iOPCEventServer_, &Status),Base::StatusCode::AeFuncCall);
                    pAeServerImpl->statusSink_(res, Status);

                } while (WaitForSingleObject(pAeServerImpl->terminate_,
                    pAeServerImpl->statusRefreshRate_.GetValue()) == WAIT_TIMEOUT);
            }

            _endthreadex(0);                           // The thread terminates.
            return 0;

        } // PollAeStatusThread


        //----------------------------------------------------------------------------------------------------------------------
        // PollStatus
        //----------------------------------------------------------------------------------------------------------------------
        HRESULT AeServerImpl::PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& res, AeServerStatus& Status), uint32_t dwRefreshRate)
        {
            HRESULT hr = S_OK;
            if (pfnStatusSink) {                         // Enable Status polling

                if (!opcAESrv_.iOPCEventServer_) {     // Must be connected
                    return OPC_E_SRVNOTCONNECTED;
                }
                if (dwRefreshRate < 100) {
                    return E_INVALIDARG;
                }
                // Change or set the refresh rate
                statusRefreshRate_.SetValue(dwRefreshRate);

                if (pollStatusThread_) {                // Allready installed
                    return S_OK;                           // Only the refresh rate changed
                }
                pfnStatusSink = pfnStatusSink;

                if ((terminate_ = CreateEvent(
                    NULL,                // Event Attributes
                    FALSE,               // Manual Reset
                    FALSE,               // Initial State   
                    NULL)) == 0) {      // Object Name     

                                         // Cannot create Event to terminate teh PollStatus Thread
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    return hr;
                }

                unsigned uThreadID;                       // Thread identifier
                pollStatusThread_ = (HANDLE)_beginthreadex(
                    NULL,                // No thread security attributes
                    0,                   // Default stack size  
                    PollAeStatusThread,  // Pointer to thread function 
                    this,                // Pass class to new thread for access to the update functions
                    0,                   // Run thread immediately
                    &uThreadID);        // Thread identifier


                if (pollStatusThread_ == 0) {           // Cannot create the thread
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    CloseHandle(terminate_);
                    terminate_ = NULL;
                    return hr;
                }
            }
            else {                                       // Disable Status polling
                if (pollStatusThread_) {                // Only if installed

                    SetEvent(terminate_);
                    // Wait max 30 secs until the PollStatus Thread has terminated.
                    if (WaitForSingleObject(pollStatusThread_, 30000) == WAIT_TIMEOUT) {
                        TerminateThread(pollStatusThread_, 1);
                    }
                    CloseHandle(pollStatusThread_);
                    pollStatusThread_ = NULL;

                    CloseHandle(terminate_);
                    terminate_ = NULL;

                    pfnStatusSink = NULL;
                    statusRefreshRate_.SetValue(0);
                }
            }
            return S_OK;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // RegisterClientName
        //----------------------------------------------------------------------------------------------------------------------
        inline Technosoftware::Base::Status AeServerImpl::RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix)
        {
            if (!opcAESrv_.iOPCEventServer_) {        // Must be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
            }
            string sRegisterName;
            try {
                USES_CONVERSION;
                if (fMachineNameAsPrefix) {
                    TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
                    DWORD dwNameLen = _countof(szComputerName);

                    if (!GetComputerName(szComputerName, &dwNameLen)) {
                        return Technosoftware::DaAeHdaClient::GetStatusFromHResult(HRESULT_FROM_WIN32(GetLastError()));
                    }
                    sRegisterName = "\\\\";
                    sRegisterName += T2A(szComputerName);
                    sRegisterName += "\\";
                }
                sRegisterName += sClientName;

                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(iOPCCommon_->SetClientName(A2CW(sRegisterName.c_str())),Base::StatusCode::AeFuncCall);
            }
            catch (...) {
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_OUTOFMEMORY);
            }
        }


        //----------------------------------------------------------------------------------------------------------------------
        // SetShutdownRequestSubscription
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status AeServerImpl::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason))
        {
            if (!opcAESrv_.iOPCEventServer_) {        // Must be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
            }

            //
            // Unsubscibe Shutdown Request Notifications
            //
            HRESULT hr = S_OK;
            if (pfnShutdownRequestSink == NULL) {
                if (icp_) {
                    if (shutdownRequestCookie_) {
                        hr = icp_->Unadvise(shutdownRequestCookie_);
                        shutdownRequestCookie_ = 0;
                        shutdownCallbackRef_ = NULL;
                    }
                    icp_ = NULL;                          // Connection Point no longer used.
                }
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::AeFuncCall);
            }

            //
            // Subscibe Shutdown Request Notifications
            //
            Technosoftware::Base::Status res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
            try {
                CComQIPtr<IConnectionPointContainer, &IID_IConnectionPointContainer> ICPC(opcAESrv_.iOPCEventServer_);
                if (!ICPC) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::AeFuncCall));

                hr = ICPC->FindConnectionPoint(IID_IOPCShutdown, &icp_);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::AeFuncCall));

                // Create an instance of the callback function
                shutdownCallbackRef_ = new (std::nothrow) CComObjectOPCShutdown;
                if (!shutdownCallbackRef_) throw Technosoftware::Base::OutOfMemoryException();
                shutdownCallbackRef_->Create(pfnShutdownRequestSink);
                shutdownCallbackRef_->AddRef();            // Add temporary reference during creation

                                                             // Create a connection between the connection point
                                                             // and the created callback function.
                                                             // Note : A Pointer to the IUnknown interface of the
                                                             // created Shutdown Sink must be passed to the advise function.
                CComPtr<IUnknown> IUnkCallback(shutdownCallbackRef_);
                if (!IUnkCallback) {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE);
                }
                else {
                    hr = icp_->Advise(IUnkCallback, &shutdownRequestCookie_);
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
                }
                shutdownCallbackRef_->Release();           // Release temporary reference
                                                             // This also destroys the instance of the callback
                                                             // function if the advise function failed.
            }
            catch (Technosoftware::Base::Status e) {
                res = e;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            if (res.IsNotGood()) {
                if (icp_) icp_.Release();
                shutdownCallbackRef_ = NULL;
            }
            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // GetStatus                                                                                                    INTERNAL
        //----------------------------------------------------------------------------------------------------------------------
        HRESULT AeServerImpl::GetStatus(IOPCEventServer* iOPCEventServer_, AeServerStatus* pStatus)
        {
            _ASSERTE(iOPCEventServer_);
            _ASSERTE(pStatus);

            OPCEVENTSERVERSTATUS* pStatusResult;
            HRESULT hr = iOPCEventServer_->GetStatus(&pStatusResult);
            if (SUCCEEDED(hr)) {
                USES_CONVERSION;
                pStatus->startTime_ = Base::Timestamp::FromFileTime(pStatusResult->ftStartTime.dwLowDateTime, pStatusResult->ftStartTime.dwHighDateTime);
                pStatus->currentTime_ = Base::Timestamp::FromFileTime(pStatusResult->ftCurrentTime.dwLowDateTime, pStatusResult->ftCurrentTime.dwHighDateTime);
                pStatus->lastUpdateTime_ = Base::Timestamp::FromFileTime(pStatusResult->ftLastUpdateTime.dwLowDateTime, pStatusResult->ftLastUpdateTime.dwHighDateTime);
                switch (pStatusResult->dwServerState) {
                case OPCAE_STATUS_RUNNING:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Running;
                    break;
                case OPCAE_STATUS_FAILED:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Failed;
                    break;
                case OPCAE_STATUS_NOCONFIG:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::NoConfiguration;
                    break;
                case OPCAE_STATUS_SUSPENDED:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Suspended;
                    break;
                case OPCAE_STATUS_TEST:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Test;
                    break;
                case OPCAE_STATUS_COMM_FAULT:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::CommunicationFault;
                    break;
                default:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Unknown;
                }
                pStatus->majorVersion_ = pStatusResult->wMajorVersion;
                pStatus->minorVersion_ = pStatusResult->wMinorVersion;
                pStatus->buildNumber_ = pStatusResult->wBuildNumber;
                pStatus->vendorInfo_ = OLE2A(pStatusResult->szVendorInfo);

                opcAESrv_.m_pIMalloc->Free(pStatusResult->szVendorInfo);
                opcAESrv_.m_pIMalloc->Free(pStatusResult);
            }
            return hr;
        }
    }
}
