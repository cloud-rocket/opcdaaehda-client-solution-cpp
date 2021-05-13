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
#include "DaAeHdaClient/Da/DaServer.h"
#include "DaAeHdaClient/Da/DaServerImpl.h"
#include "Base/Status.h"

#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        /**
         * @fn  DaServer::DaServer() throw (Technosoftware::Base::Exception)
         *
         * @brief   Default constructor.
         *
         * @exception   Technosoftware::Base::Exception             Thrown when an exception error condition
         *                                                      occurs.
         * @exception   Technosoftware::Base::OutOfMemoryException  Thrown when a low memory situation occurs.
         */

        DaServer::DaServer() noexcept(false) : OpcObject(nullptr, "DaServer")
        {
            m_Impl.Attach(new (std::nothrow) DaServerImpl);
            if (!m_Impl) throw Base::OutOfMemoryException();
        }

        /**
         * @fn  DaServer::~DaServer() throw ()
         *
         * @brief   Destructor.
         */

        DaServer::~DaServer() throw ()
        {
            DeleteAllChildren();                         // Deletes all subscriptions
        }


        //----------------------------------------------------------------------------------------------------------------------
        // ATTRIBUTES
        //----------------------------------------------------------------------------------------------------------------------

        DaServerStatus& DaServer::GetStatus() const { return m_Impl->m_Status; }

        bool DaServer::IsConnected() const throw () { return m_Impl->m_OPCDASrv.m_pIOPCServer ? true : false; }

        Base::Status DaServer::Connect(const string& serverName, const string& machineName, uint32_t coInit)
        {
            return m_Impl->Connect(serverName, machineName, coInit);
        }

        void DaServer::Disconnect()
        {
            DeleteAllChildren();                         // Deletes all subscriptions
            m_Impl->Disconnect();
        }

        Base::Status DaServer::UpdateStatus() { return m_Impl->UpdateStatus(); }

        Base::Status DaServer::PollStatus(void(*statusSink)(Base::Status& status, DaServerStatus& serverStatus), uint32_t refreshRate /* = 1000 */)
        {
            return m_Impl->PollStatus((DaServerImpl::PFN_StatusSinkWithCookie)statusSink, refreshRate, NULL);
        }

        Technosoftware::Base::Status DaServer::PollStatus(void(*statusSink)(Base::Status& status, DaServerStatus& serverStatus, void* cookie), void* cookie, uint32_t refreshRate /* = 1000 */)
        {
            // Use _OpcSysResult because there are only local system function calls.
            if (!cookie) return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_INVALIDARG);
            return m_Impl->PollStatus(statusSink, refreshRate, cookie);
        }

        Technosoftware::Base::Status DaServer::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason))
        {
            return m_Impl->SetShutdownRequestSubscription(*pfnShutdownRequestSink);
        }

        Technosoftware::Base::Status DaServer::RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix /* = false */)
        {
            return m_Impl->RegisterClientName(sClientName, fMachineNameAsPrefix);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS DaServerImpl
        //----------------------------------------------------------------------------------------------------------------------
        //
        // Please refer to class DaServer for the description and documentation of attributes and member functions.
        //
        // Since the ...Impl classes are used only by one object all function members which are used only once are declared
        // as inline functions.
        //

        //----------------------------------------------------------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    DaServerImpl::DaServerImpl() throw ()
         *
         * @brief    Default constructor.
         */

        DaServerImpl::DaServerImpl() throw ()
        {
            m_hTerminate = NULL;
            m_hPollStatusThread = NULL;
            m_pPollStatusCookie = NULL;
            m_pfnStatusSink = NULL;
            m_pfnStatusSinkWithCookie = NULL;
            m_dwShutdownRequestCookie = 0;
            m_pShutdownCallbackRef = NULL;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Destructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    DaServerImpl::~DaServerImpl() throw ()
         *
         * @brief    Destructor.
         */

        DaServerImpl::~DaServerImpl() throw ()
        {
            try {
                Disconnect();
            }
            catch (...) {}
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Connect
        //----------------------------------------------------------------------------------------------------------------------
        inline Technosoftware::Base::Status DaServerImpl::Connect(const string& sServerName, const string& sMachineName, DWORD dwCoInit)
        {
            if (m_OPCDASrv.m_pIOPCServer) {              // Must not be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            USES_CONVERSION;
            HRESULT hr = m_OPCDASrv.ConnectToServer(A2CT(sMachineName.c_str()), A2CT(sServerName.c_str()), FALSE, dwCoInit);
            // Note: Use _OpcSysResult and not throw Technosoftware::DaAeHdaClient::GetStatusFromHResult( because impl_->Connect() doesn't return
            // OPC Specific Error codes but the CO_E... error codes includes also facility code ITF.
            if (FAILED(hr)) {
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
            }
            m_OPCDASrv.m_pIOPCServer->QueryInterface(IID_IOPCCommon, (LPVOID*)&m_pIOPCCommon);
            if (SUCCEEDED(hr)) {
                return UpdateStatus();
            }
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Disconnect
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    void DaServerImpl::Disconnect()
         *
         * @brief    Disconnects this object.
         */

        void DaServerImpl::Disconnect()
        {
            SetShutdownRequestSubscription(NULL);      // Unsubscribe Sutdown Request
            PollStatus(0, NULL, NULL);                 // Remove PollStatus Thread
            m_pIOPCCommon = NULL;
            m_OPCDASrv.DisconnectFromServer();
        }


        //----------------------------------------------------------------------------------------------------------------------
        // UpdateStatus
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT DaServerImpl::UpdateStatus()
         *
         * @brief    Updates the status.
         *
         * @return    A HRESULT.
         */

        Technosoftware::Base::Status DaServerImpl::UpdateStatus()
        {
            if (!m_OPCDASrv.m_pIOPCServer) {             // Must be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
            }
            return GetStatus(m_OPCDASrv.m_pIOPCServer, &m_Status);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // PollDaStatusThread                                                                                             THREAD
        // ------------------
        //    Retrieves periodically the status from the connected OPC Server.
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    unsigned __stdcall PollDaStatusThread( LPVOID pAttr )
         *
         * @brief    Poll da status thread.
         *
         * @param    pAttr    The attribute.
         *
         * @return    An unsigned.
         */

        unsigned __stdcall PollDaStatusThread(void far * pAttr)
        {
            DaServerImpl* pDaServerImpl = static_cast<DaServerImpl*>(pAttr);
            _ASSERTE(pDaServerImpl);                   // Must not be NULL.

            {  // This braces defines a scope which guarantees that the
               // destructor of the used class instances is called.

                Technosoftware::Base::Status res;
                DaServerStatus Status;
                IOPCServer*       pIOPCServer = pDaServerImpl->m_OPCDASrv.m_pIOPCServer;

                do {
                    res = pDaServerImpl->GetStatus(pIOPCServer, &Status);

                    if (pDaServerImpl->m_pPollStatusCookie)
                        pDaServerImpl->m_pfnStatusSinkWithCookie(res, Status, pDaServerImpl->m_pPollStatusCookie);
                    else
                        pDaServerImpl->m_pfnStatusSink(res, Status);

                } while (WaitForSingleObject(pDaServerImpl->m_hTerminate,
                    pDaServerImpl->m_StatusRefreshRate.GetValue()) == WAIT_TIMEOUT);
            }

            _endthreadex(0);                           // The thread terminates.
            return 0;

        } // PollDaStatusThread


        //----------------------------------------------------------------------------------------------------------------------
        // PollStatus
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT DaServerImpl::PollStatus( PFN_StatusSinkWithCookie pfnStatusSinkWithCookie, uint32_t dwRefreshRate, void* cookie )
         *
         * @brief    Poll status.
         *
         * @param    pfnStatusSinkWithCookie    The pfn status sink with cookie.
         * @param    dwRefreshRate               The refresh rate.
         * @param [in,out]    pCookie               If non-null, the cookie.
         *
         * @return    A HRESULT.
         */

        Technosoftware::Base::Status DaServerImpl::PollStatus(PFN_StatusSinkWithCookie pfnStatusSinkWithCookie, uint32_t dwRefreshRate, void* pCookie)
        {
            HRESULT hr = S_OK;

            if (pfnStatusSinkWithCookie) {              // Enable serverStatus polling

                if (!m_OPCDASrv.m_pIOPCServer) {          // Must be connected
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
                }
                if (dwRefreshRate < 100) {
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_INVALIDARG);
                }
                // Change or set the refresh rate
                m_StatusRefreshRate.SetValue(dwRefreshRate);

                if (m_hPollStatusThread) {                // Allready installed
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);        // Only the refresh rate changed
                }

                if (pCookie)   m_pfnStatusSinkWithCookie = pfnStatusSinkWithCookie;
                else           m_pfnStatusSink = (PFN_StatusSink)pfnStatusSinkWithCookie;
                m_pPollStatusCookie = pCookie;            // Take the Cookie only at activation

                if ((m_hTerminate = CreateEvent(
                    NULL,                // Event Attributes
                    FALSE,               // Manual Reset
                    FALSE,               // Initial State   
                    NULL)) == 0) {      // Object Name     

                                         // Cannot create Event to terminate teh PollStatus Thread
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
                }

                unsigned uThreadID;                       // Thread identifier
                m_hPollStatusThread = (HANDLE)_beginthreadex(
                    NULL,                // No thread security attributes
                    0,                   // Default stack size  
                    PollDaStatusThread,  // Pointer to thread function 
                    this,                // Pass class to new thread for access to the update functions
                    0,                   // Run thread immediately
                    &uThreadID);        // Thread identifier


                if (m_hPollStatusThread == 0) {           // Cannot create the thread
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    CloseHandle(m_hTerminate);
                    m_hTerminate = NULL;
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
                }
            }
            else {                                       // Disable serverStatus polling
                if (m_hPollStatusThread) {                // Only if installed

                    SetEvent(m_hTerminate);
                    // Wait max 30 secs until the PollStatus Thread has terminated.
                    if (WaitForSingleObject(m_hPollStatusThread, 30000) == WAIT_TIMEOUT) {
                        TerminateThread(m_hPollStatusThread, 1);
                    }
                    CloseHandle(m_hPollStatusThread);
                    m_hPollStatusThread = NULL;

                    CloseHandle(m_hTerminate);
                    m_hTerminate = NULL;

                    m_pfnStatusSink = NULL;
                    m_StatusRefreshRate.SetValue(0);
                }
            }
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // RegisterClientName
        //----------------------------------------------------------------------------------------------------------------------
        inline Technosoftware::Base::Status DaServerImpl::RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix)
        {
            if (!m_OPCDASrv.m_pIOPCServer) {             // Must be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
            }
            string sRegisterName;
            try {

                if (m_pIOPCCommon == NULL)
                {
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOTIMPL);
                }

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

                HRESULT hr = m_pIOPCCommon->SetClientName(A2CW(sRegisterName.c_str()));
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
            }
            catch (...) {
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_OUTOFMEMORY);
            }
        }


        //----------------------------------------------------------------------------------------------------------------------
        // SetShutdownRequestSubscription
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    Technosoftware::Base::serverStatus DaServerImpl::SetShutdownRequestSubscription( void (*pfnShutdownRequestSink)( string& sReason ) )
         *
         * @brief    Sets shutdown request subscription.
         *
         * @exception    throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(     Thrown when an opc da result error condition occurs.
         * @exception    _OpcSysResult    Thrown when an opc system result error condition occurs.
         *
         * @param [in,out]    pfnShutdownRequestSink    If non-null, the pfn shutdown request sink.
         *
         * @return    An Technosoftware::Base::serverStatus.
         */

        Technosoftware::Base::Status DaServerImpl::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason))
        {
            if (!m_OPCDASrv.m_pIOPCServer) {             // Must be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
            }

            //
            // Unsubscibe Shutdown Request Notifications
            //
            HRESULT hr = S_OK;
            if (pfnShutdownRequestSink == NULL) {
                if (m_ICP) {
                    if (m_dwShutdownRequestCookie) {
                        hr = m_ICP->Unadvise(m_dwShutdownRequestCookie);
                        if (FAILED(hr)) {
                            // This releases the sink instance too if the connection to the server was lost.
                            CoDisconnectObject(m_pShutdownCallbackRef, 0);
                        }
                        m_dwShutdownRequestCookie = 0;
                        m_pShutdownCallbackRef = NULL;
                    }
                    m_ICP = NULL;                          // Connection Point no longer used.
                }
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
            }

            //
            // Subscibe Shutdown Request Notifications
            //
            Technosoftware::Base::Status res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
            try {
                CComQIPtr<IConnectionPointContainer, &IID_IConnectionPointContainer> ICPC(m_OPCDASrv.m_pIOPCServer);
                if (!ICPC) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE));

                hr = ICPC->FindConnectionPoint(IID_IOPCShutdown, &m_ICP);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE)));

                // Create an instance of the callback function
                m_pShutdownCallbackRef = new (std::nothrow) CComObjectOPCShutdown;
                if (!m_pShutdownCallbackRef) throw Technosoftware::Base::OutOfMemoryException();
                m_pShutdownCallbackRef->Create(pfnShutdownRequestSink);
                m_pShutdownCallbackRef->AddRef();            // Add temporary reference during creation

                                                             // Create a connection between the connection point
                                                             // and the created callback function.
                                                             // Note : A Pointer to the IUnknown interface of the
                                                             // created Shutdown Sink must be passed to the advise function.
                CComPtr<IUnknown> IUnkCallback(m_pShutdownCallbackRef);
                if (!IUnkCallback) {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE);
                }
                else {
                    hr = m_ICP->Advise(IUnkCallback, &m_dwShutdownRequestCookie);
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                }
                m_pShutdownCallbackRef->Release();           // Release temporary reference
                                                             // This also destroys the instance of the callback
                                                             // function if the advise function failed.
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            if (res.IsError()) {
                if (m_ICP) m_ICP.Release();
                m_pShutdownCallbackRef = NULL;
            }
            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // GetStatus                                                                                                    INTERNAL
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT DaServerImpl::GetStatus( IOPCServer* pIOPCServer, DaServerStatus* pStatus )
         *
         * @brief    Gets the status.
         *
         * @param [in,out]    pIOPCServer    If non-null, the iopc server.
         * @param [in,out]    pStatus           If non-null, the status.
         *
         * @return    The status.
         */

        Technosoftware::Base::Status DaServerImpl::GetStatus(IOPCServer* pIOPCServer, DaServerStatus* pStatus)
        {
            _ASSERTE(pIOPCServer);
            _ASSERTE(pStatus);

            OPCSERVERSTATUS* pStatusResult;
            HRESULT hr = pIOPCServer->GetStatus(&pStatusResult);
            if (SUCCEEDED(hr)) {
                USES_CONVERSION;
                pStatus->startTime_ = Base::Timestamp::FromFileTime((uint32_t)pStatusResult->ftStartTime.dwLowDateTime, (uint32_t)pStatusResult->ftStartTime.dwHighDateTime);
                pStatus->currentTime_ = Base::Timestamp::FromFileTime((uint32_t)pStatusResult->ftCurrentTime.dwLowDateTime, (uint32_t)pStatusResult->ftCurrentTime.dwHighDateTime);
                pStatus->lastUpdateTime_ = Base::Timestamp::FromFileTime((uint32_t)pStatusResult->ftLastUpdateTime.dwLowDateTime, (uint32_t)pStatusResult->ftLastUpdateTime.dwHighDateTime);
                switch(pStatusResult->dwServerState) {
                case OPC_STATUS_RUNNING:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Running;
                    break;
                case OPC_STATUS_FAILED:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Failed;
                    break;
                case OPC_STATUS_NOCONFIG:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::NoConfiguration;
                    break;
                case OPC_STATUS_SUSPENDED:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Suspended;
                    break;
                case OPC_STATUS_TEST:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Test;
                    break;
                case OPC_STATUS_COMM_FAULT:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::CommunicationFault;
                    break;
                default:
                    pStatus->serverState_ = Technosoftware::Base::ServerStates::ServerState::Unknown;
                }
                pStatus->groupCount_ = pStatusResult->dwGroupCount;
                pStatus->bandWidth_ = pStatusResult->dwBandWidth;
                pStatus->majorVersion_ = pStatusResult->wMajorVersion;
                pStatus->minorVersion_ = pStatusResult->wMinorVersion;
                pStatus->buildNumber_ = pStatusResult->wBuildNumber;
                pStatus->reserved_ = pStatusResult->wReserved;
                pStatus->vendorInfo_ = OLE2A(pStatusResult->szVendorInfo);

                CoTaskMemFree(pStatusResult->szVendorInfo);
                CoTaskMemFree(pStatusResult);
            }
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
        }
    }
}
