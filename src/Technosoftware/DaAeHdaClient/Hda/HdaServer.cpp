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
#include "DaAeHdaClient/Hda/HdaServer.h"
#include "DaAeHdaClient/Hda/HdaServerImpl.h"

#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        HdaServer::HdaServer() throw (Technosoftware::Base::Exception) : OpcObject(NULL, "HdaServer")
        {
            m_Impl.Attach(new (std::nothrow) HdaServerImpl);
            if (!m_Impl) throw Technosoftware::Base::OutOfMemoryException();
        }

        HdaServer::~HdaServer() throw ()
        {
            DeleteAllChildren();                         // Deletes all subscriptions
        }


        //----------------------------------------------------------------------------------------------------------------------
        // ATTRIBUTES
        //----------------------------------------------------------------------------------------------------------------------

        HdaServerStatus& HdaServer::GetStatus() const { return m_Impl->m_Status; }

        bool HdaServer::IsConnected() const throw () { return m_Impl->m_OPCHDASrv.m_pIOPCHistoricalServer ? true : false; }

        Technosoftware::Base::Status HdaServer::Connect(const string& sServerName, const string& sMachineName, uint32_t dwCoInit)
        {
            return m_Impl->Connect(sServerName, sMachineName, dwCoInit);
        }

        void HdaServer::Disconnect()
        {
            DeleteAllChildren();                         // Deletes all subscriptions
            m_Impl->Disconnect();
        }

        Technosoftware::Base::Status HdaServer::UpdateStatus() { return Technosoftware::DaAeHdaClient::GetStatusFromHResult(m_Impl->UpdateStatus()); }

        Technosoftware::Base::Status HdaServer::PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& res, HdaServerStatus& Status), uint32_t dwRefreshRate /* = 1000 */)
        {
            // Use _OpcSysResult because there are only local system function calls.
            return  Technosoftware::DaAeHdaClient::GetStatusFromHResult(m_Impl->PollStatus((HdaServerImpl::PFN_StatusSinkWithCookie)pfnStatusSink, dwRefreshRate, NULL));
        }

        Technosoftware::Base::Status HdaServer::PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& res, HdaServerStatus& Status, void* pCookie), void* pCookie, uint32_t dwRefreshRate /* = 1000 */)
        {
            // Use _OpcSysResult because there are only local system function calls.
            if (!pCookie) return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_INVALIDARG);
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(m_Impl->PollStatus(pfnStatusSink, dwRefreshRate, pCookie));
        }

        Technosoftware::Base::Status HdaServer::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason))
        {
            return m_Impl->SetShutdownRequestSubscription(*pfnShutdownRequestSink);
        }

        Technosoftware::Base::Status HdaServer::RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix /* = false */)
        {
            return m_Impl->RegisterClientName(sClientName, fMachineNameAsPrefix);
        }

		Technosoftware::Base::Status HdaServer::GetItemAttributes(HdaItemAttributes& hdaitemAtttributes)
		{
			return m_Impl->GetItemAttributes(hdaitemAtttributes);
		}

		Technosoftware::Base::Status HdaServer::GetAggregates(HdaAggregates& hdaAggregates)
		{
			return m_Impl->GetAggregates(hdaAggregates);
		}

        Technosoftware::Base::Status HdaServer::ReadRaw(const char* itemId, Base::Timestamp startTime, Base::Timestamp endTime, DWORD maxValues, BOOL bounds, HdaItem* hdaItem, HRESULT* error)
        {
            return m_Impl->ReadRaw(itemId, startTime, endTime, maxValues, bounds, hdaItem, error);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS HdaServerImpl
        //----------------------------------------------------------------------------------------------------------------------
        //
        // Please refer to class HdaServer for the description and documentation of attributes and member functions.
        //
        // Since the ...Impl classes are used only by one object all function members which are used only once are declared
        // as inline functions.
        //

        //----------------------------------------------------------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HdaServerImpl::HdaServerImpl() throw ()
         *
         * @brief    Default constructor.
         */

        HdaServerImpl::HdaServerImpl() throw ()
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
         * @fn    HdaServerImpl::~HdaServerImpl() throw ()
         *
         * @brief    Destructor.
         */

        HdaServerImpl::~HdaServerImpl() throw ()
        {
            try {
                Disconnect();
            }
            catch (...) {}
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Connect
        //----------------------------------------------------------------------------------------------------------------------
        inline Technosoftware::Base::Status HdaServerImpl::Connect(const string& sServerName, const string& sMachineName, DWORD dwCoInit)
        {
            if (m_OPCHDASrv.m_pIOPCHistoricalServer) {              // Must not be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            USES_CONVERSION;
            HRESULT hr = m_OPCHDASrv.ConnectToHistoricalServer(A2CT(sMachineName.c_str()), A2CT(sServerName.c_str()), FALSE, dwCoInit);
            // Note: Use _OpcSysResult and not throw Technosoftware::DaAeHdaClient::GetStatusFromHResult( because impl_->Connect() doesn't return
            // OPC Specific Error codes but the CO_E... error codes includes also facility code ITF.
            if (FAILED(hr)) return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);

            m_OPCHDASrv.m_pIOPCHistoricalServer->QueryInterface(IID_IOPCCommon, (LPVOID*)&m_pIOPCCommon);
            if (SUCCEEDED(hr)) {
                hr = UpdateStatus();
            }
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::HdaFuncCall);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Disconnect
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    void HdaServerImpl::Disconnect()
         *
         * @brief    Disconnects this object.
         */

        void HdaServerImpl::Disconnect()
        {
            SetShutdownRequestSubscription(NULL);      // Unsubscribe Sutdown Request
            PollStatus(0, NULL, NULL);                 // Remove PollStatus Thread
            m_pIOPCCommon = NULL;
            m_OPCHDASrv.DisconnectFromHistoricalServer();
        }


        //----------------------------------------------------------------------------------------------------------------------
        // UpdateStatus
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT HdaServerImpl::UpdateStatus()
         *
         * @brief    Updates the status.
         *
         * @return    A HRESULT.
         */

        HRESULT HdaServerImpl::UpdateStatus()
        {
            if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {             // Must be connected
                return OPC_E_SRVNOTCONNECTED;
            }
            return GetStatus(m_OPCHDASrv.m_pIOPCHistoricalServer, &m_Status);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // PollHdaStatusThread                                                                                             THREAD
        // ------------------
        //    Retrieves periodically the status from the connected OPC Server.
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    unsigned __stdcall PollHdaStatusThread( LPVOID pAttr )
         *
         * @brief    Poll HDA status thread.
         *
         * @param    pAttr    The attribute.
         *
         * @return    An unsigned.
         */

        unsigned __stdcall PollHdaStatusThread(LPVOID pAttr)
        {
            HdaServerImpl* pHdaServerImpl = static_cast<HdaServerImpl*>(pAttr);
            _ASSERTE(pHdaServerImpl);                   // Must not be NULL.

            {  // This braces defines a scope which guarantees that the
               // destructor of the used class instances is called.

                Technosoftware::Base::Status       res;
                HdaServerStatus Status;
                IOPCHDA_Server*       pIOPCServer = pHdaServerImpl->m_OPCHDASrv.m_pIOPCHistoricalServer;

                do {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(pHdaServerImpl->GetStatus(pIOPCServer, &Status),Base::StatusCode::HdaFuncCall);

                    if (pHdaServerImpl->m_pPollStatusCookie)
                        pHdaServerImpl->m_pfnStatusSinkWithCookie(res, Status, pHdaServerImpl->m_pPollStatusCookie);
                    else
                        pHdaServerImpl->m_pfnStatusSink(res, Status);

                } while (WaitForSingleObject(pHdaServerImpl->m_hTerminate,
                    pHdaServerImpl->m_StatusRefreshRate.GetValue()) == WAIT_TIMEOUT);
            }

            _endthreadex(0);                           // The thread terminates.
            return 0;

        } // PollHdaStatusThread


        //----------------------------------------------------------------------------------------------------------------------
        // PollStatus
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT HdaServerImpl::PollStatus( PFN_StatusSinkWithCookie pfnStatusSinkWithCookie, uint32_t dwRefreshRate, void* pCookie )
         *
         * @brief    Poll status.
         *
         * @param    pfnStatusSinkWithCookie    The pfn status sink with cookie.
         * @param    dwRefreshRate               The refresh rate.
         * @param [in,out]    pCookie               If non-null, the cookie.
         *
         * @return    A HRESULT.
         */

        HRESULT HdaServerImpl::PollStatus(PFN_StatusSinkWithCookie pfnStatusSinkWithCookie, uint32_t dwRefreshRate, void* pCookie)
        {
            HRESULT hr = S_OK;

            if (pfnStatusSinkWithCookie) {              // Enable Status polling

                if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {          // Must be connected
                    return OPC_E_SRVNOTCONNECTED;
                }
                if (dwRefreshRate < 100) {
                    return E_INVALIDARG;
                }
                // Change or set the refresh rate
                m_StatusRefreshRate.SetValue(dwRefreshRate);

                if (m_hPollStatusThread) {                // Allready installed
                    return S_OK;                           // Only the refresh rate changed
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
                    return hr;
                }

                unsigned uThreadID;                       // Thread identifier
                m_hPollStatusThread = (HANDLE)_beginthreadex(
                    NULL,                // No thread security attributes
                    0,                   // Default stack size  
                    PollHdaStatusThread,  // Pointer to thread function 
                    this,                // Pass class to new thread for access to the update functions
                    0,                   // Run thread immediately
                    &uThreadID);        // Thread identifier


                if (m_hPollStatusThread == 0) {           // Cannot create the thread
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    CloseHandle(m_hTerminate);
                    m_hTerminate = NULL;
                    return hr;
                }
            }
            else {                                       // Disable Status polling
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
            return S_OK;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // RegisterClientName
        //----------------------------------------------------------------------------------------------------------------------
        inline Technosoftware::Base::Status HdaServerImpl::RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix)
        {
            if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {             // Must be connected
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

                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(m_pIOPCCommon->SetClientName(A2CW(sRegisterName.c_str())),Base::StatusCode::HdaFuncCall);
            }
            catch (...) {
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_OUTOFMEMORY);
            }
        }


        //----------------------------------------------------------------------------------------------------------------------
        // SetShutdownRequestSubscription
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    Technosoftware::Base::Status HdaServerImpl::SetShutdownRequestSubscription( void (*pfnShutdownRequestSink)( string& sReason ) )
         *
         * @brief    Sets shutdown request subscription.
         *
         * @exception    throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(     Thrown when an opc da result error condition occurs.
         * @exception    _OpcSysResult    Thrown when an opc system result error condition occurs.
         *
         * @param [in,out]    pfnShutdownRequestSink    If non-null, the pfn shutdown request sink.
         *
         * @return    An Technosoftware::Base::Status.
         */

        Technosoftware::Base::Status HdaServerImpl::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason))
        {
            if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {             // Must be connected
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
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::HdaFuncCall);
            }

            //
            // Subscibe Shutdown Request Notifications
            //
            Technosoftware::Base::Status res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
            try {
                CComQIPtr<IConnectionPointContainer, &IID_IConnectionPointContainer> ICPC(m_OPCHDASrv.m_pIOPCHistoricalServer);
                if (!ICPC) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::HdaFuncCall));

                hr = ICPC->FindConnectionPoint(IID_IOPCShutdown, &m_ICP);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::HdaFuncCall)));

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
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::HdaFuncCall);
                }
                m_pShutdownCallbackRef->Release();           // Release temporary reference
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
                if (m_ICP) m_ICP.Release();
                m_pShutdownCallbackRef = NULL;
            }
            return res;
        }

		//----------------------------------------------------------------------------------------------------------------------
		// GetAggregates
		//----------------------------------------------------------------------------------------------------------------------

		Technosoftware::Base::Status HdaServerImpl::GetItemAttributes(HdaItemAttributes& hdaitemAtttributes)
		{
			string			strText;
			string			strParam;
			string			strTemp;
			DWORD			dwIndex;

			if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {             // Must be connected
				return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
			}
			Technosoftware::Base::Status res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);

			HRESULT					hr = E_FAIL;
			DWORD					count = 0;
			DWORD*					attributeIds = NULL;
			LPWSTR*					attributeNames = NULL;
			LPWSTR*					attributeDescriptions = NULL;
			VARTYPE*				attributeDataTypes = NULL;

			// get item attributes
			hr = m_OPCHDASrv.m_pIOPCHistoricalServer->GetItemAttributes(&count, &attributeIds, &attributeNames, &attributeDescriptions, &attributeDataTypes);

			if (FAILED(hr) || m_OPCHDASrv.m_pIOPCHistoricalServer == NULL)
			{
				res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
			}
			else
			{
				for (dwIndex = 0L; dwIndex < count; dwIndex++)
				{
					USES_CONVERSION;
					string name = OLE2A(attributeNames[dwIndex]);
					string description = OLE2A(attributeDescriptions[dwIndex]);

					HdaItemAttribute itemAttribute(attributeIds[dwIndex], name, description, attributeDataTypes[dwIndex]);
					hdaitemAtttributes.push_back(itemAttribute);
				}

				////////////////////////////////////////////////////////////////////////////
				// clean up
				for (dwIndex = 0L; dwIndex < count; dwIndex++)
				{
					if (attributeNames[dwIndex])
					{
						::CoTaskMemFree((void*)attributeNames[dwIndex]);
					}
					if (attributeDescriptions[dwIndex])
					{
						::CoTaskMemFree((void*)attributeDescriptions[dwIndex]);
					}
				}
				if (attributeIds)
				{
					::CoTaskMemFree(attributeIds);
				}
			}
			return res;
		}

		//----------------------------------------------------------------------------------------------------------------------
		// GetAggregates
		//----------------------------------------------------------------------------------------------------------------------

		Technosoftware::Base::Status HdaServerImpl::GetAggregates(HdaAggregates& hdaAggregates)
		{
			string			strText;
			string			strParam;
			string			strTemp;
			DWORD			dwIndex;

			if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {             // Must be connected
				return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
			}
			Technosoftware::Base::Status res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);

			HRESULT					hr = E_FAIL;
			DWORD					count = 0;
			DWORD*					aggregateIds = NULL;
			LPWSTR*					aggregateNames = NULL;
			LPWSTR*					aggregateDescriptions = NULL;

			// get aggregates
			hr = m_OPCHDASrv.m_pIOPCHistoricalServer->GetAggregates(&count, &aggregateIds, &aggregateNames, &aggregateDescriptions);

			if (FAILED(hr) || m_OPCHDASrv.m_pIOPCHistoricalServer == NULL)
			{
				res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
			}
			else
			{
				for (dwIndex = 0L; dwIndex < count; dwIndex++)
				{
					USES_CONVERSION;
					string name = OLE2A(aggregateNames[dwIndex]);
					string description = OLE2A(aggregateDescriptions[dwIndex]);

					HdaAggregate aggregate(aggregateIds[dwIndex], name, description);
					hdaAggregates.push_back(aggregate);
				}

				////////////////////////////////////////////////////////////////////////////
				// clean up
				for (dwIndex = 0L; dwIndex < count; dwIndex++)
				{
					if (aggregateNames[dwIndex])
					{
						::CoTaskMemFree((void*)aggregateNames[dwIndex]);
					}
					if (aggregateDescriptions[dwIndex])
					{
						::CoTaskMemFree((void*)aggregateDescriptions[dwIndex]);
					}
				}
				if (aggregateIds)
				{
					::CoTaskMemFree(aggregateIds);
				}
			}
			return res;
		}

        //----------------------------------------------------------------------------------------------------------------------
        // ReadRaw
        //----------------------------------------------------------------------------------------------------------------------

        Technosoftware::Base::Status HdaServerImpl::ReadRaw(const char* itemId, Base::Timestamp startTime, Base::Timestamp endTime, DWORD maxValues, BOOL bounds, HdaItem* hdaItem, HRESULT* error)
        {
            if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {             // Must be connected
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);
            }
            Technosoftware::Base::Status res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);

            OPCHANDLE itemHandle = GetItemHandle(itemId);
            if (itemHandle != 0) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
                HRESULT                hr = E_FAIL;

                IOPCHDA_SyncRead*    pOPCHDASyncRead = NULL;

                //////////////////////////////////////////////////////////////
                // get the IOPCHDA_SyncRead
                hr = m_OPCHDASrv.m_pIOPCHistoricalServer->QueryInterface(IID_IOPCHDA_SyncRead, (LPVOID*)&pOPCHDASyncRead);
                if (FAILED(hr) || pOPCHDASyncRead == NULL)
                {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
                    return res;
                }

                OPCHDA_TIME start;
                OPCHDA_TIME end;
                DWORD                dwNumItems;
                OPCHDA_ITEM*        pOpcHdaItem;
                HRESULT*            pErrors;
                DWORD                dwIndex;

                dwNumItems = 1;
                start.bString = false;
                start.szTime = NULL;
                startTime.ToFileTime(start.ftTime.dwLowDateTime, start.ftTime.dwHighDateTime);

                end.bString = false;
                end.szTime = NULL;
                endTime.ToFileTime(end.ftTime.dwLowDateTime, end.ftTime.dwHighDateTime);

                // sync read raw
                hr = pOPCHDASyncRead->ReadRaw(&start, &end, maxValues, bounds, dwNumItems, &itemHandle, &pOpcHdaItem, &pErrors);
                // handle returned errors
                if (FAILED(hr) || pOpcHdaItem == NULL || pErrors == NULL)
                {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
                    return res;
                }
                else
                {
                    // if data exists
                    if (pErrors[0] == S_OK || pErrors[0] == OPC_S_MOREDATA)
                    {
                        *error = pErrors[0];
                        hdaItem->Count = pOpcHdaItem[0].dwCount;
                        hdaItem->Aggregate = pOpcHdaItem[0].haAggregate;
                        hdaItem->ClientHandle = pOpcHdaItem[0].hClient;
                        hdaItem->Qualities = new DWORD[pOpcHdaItem[0].dwCount];
                        hdaItem->TimeStamps = new FILETIME[pOpcHdaItem[0].dwCount];
                        hdaItem->DataValues = new VARIANT[pOpcHdaItem[0].dwCount];
                        for (dwIndex = 0L; dwIndex < pOpcHdaItem[0].dwCount; dwIndex++)
                        {
                            hdaItem->Qualities[dwIndex] = pOpcHdaItem[0].pdwQualities[dwIndex];
                            hdaItem->TimeStamps[dwIndex] = pOpcHdaItem[0].pftTimeStamps[dwIndex];
                            hdaItem->DataValues[dwIndex] = pOpcHdaItem[0].pvDataValues[dwIndex];
                        }
                    }
                    else
                    {
                        res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
                        return res;
                    }

                    //////////////////////////////////////////////////////////////
                    // cleanup

                    if (pOpcHdaItem)
					{
						::CoTaskMemFree((void*)pOpcHdaItem);
					}
					pOpcHdaItem = NULL;

                    if (pErrors)
					{
						::CoTaskMemFree((void*)pErrors);
					}
					pErrors = NULL;

                    if (pOPCHDASyncRead)
                    {
                        pOPCHDASyncRead->Release();
                        pOPCHDASyncRead = NULL;
                    }
                    return res;
                }
            }
            return res;
        }

        //----------------------------------------------------------------------------------------------------------------------
        // GetStatus                                                                                                    INTERNAL
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT HdaServerImpl::GetStatus( IOPCServer* pIOPCServer, HdaServerStatus* pStatus )
         *
         * @brief    Gets the status.
         *
         * @param [in,out]    pIOPCServer    If non-null, the iopc server.
         * @param [in,out]    pStatus           If non-null, the status.
         *
         * @return    The status.
         */

        HRESULT HdaServerImpl::GetStatus(IOPCHDA_Server* pIOPCServer, HdaServerStatus* pStatus)
        {
            _ASSERTE(pIOPCServer);
            _ASSERTE(pStatus);

            OPCHDA_SERVERSTATUS    pwStatus;
            FILETIME*            pftCurrentTime;
            FILETIME*            pftStartTime;
            WORD                    pwMajorVersion;
            WORD                    pwMinorVersion;
            WORD                    pwBuildNumber;
            DWORD                pdwMaxReturnValues;
            LPWSTR                pszStatusString;
            LPWSTR                pszVendorInfo;

            HRESULT hr = pIOPCServer->GetHistorianStatus(&pwStatus, &pftCurrentTime, &pftStartTime,
                &pwMajorVersion, &pwMinorVersion, &pwBuildNumber,
                &pdwMaxReturnValues, &pszStatusString, &pszVendorInfo);
            if (SUCCEEDED(hr)) {
                USES_CONVERSION;
                pStatus->m_ftStartTime = *(Base::Timestamp*)&pftStartTime;
                pStatus->m_ftCurrentTime = *(Base::Timestamp*)&pftCurrentTime;
                switch (pwStatus) {
                case OPCHDA_UP:
                    pStatus->m_dwServerState = Technosoftware::Base::ServerStates::ServerState::Running;
                    break;
                case OPCHDA_DOWN:
                    pStatus->m_dwServerState = Technosoftware::Base::ServerStates::ServerState::Failed;
                    break;
                case OPCHDA_INDETERMINATE:
                default:
                    pStatus->m_dwServerState = Technosoftware::Base::ServerStates::ServerState::Unknown;
                }
                pStatus->m_dwMaxReturnValues = pdwMaxReturnValues;
                pStatus->m_wMajorVersion = pwMajorVersion;
                pStatus->m_wMinorVersion = pwMinorVersion;
                pStatus->m_wBuildNumber = pwBuildNumber;
                pStatus->m_sVendorInfo = OLE2A(pszVendorInfo);

                if (pftStartTime)
                    CoTaskMemFree(pftStartTime);
                if (pftCurrentTime)
                    CoTaskMemFree(pftCurrentTime);
                if (pszStatusString)
                    CoTaskMemFree(pszStatusString);
                if (pszVendorInfo)
                    CoTaskMemFree(pszVendorInfo);
            }
            return hr;
        }

        //----------------------------------------------------------------------------------------------------------------------
        // GetItemHandles                                                                                               INTERNAL
        //----------------------------------------------------------------------------------------------------------------------
        OPCHANDLE HdaServerImpl::GetItemHandle(const char* itemId)
        {
            DWORD                dwCount = 0;
            BSTR                bstrItemID;
            OPCHANDLE            phClient = 0L;
            OPCHANDLE*            phServer = NULL;
            HRESULT*            pErrors;
            HRESULT                hr;

            if (!m_OPCHDASrv.m_pIOPCHistoricalServer) {             // Must be connected
                return NULL;
            }

            // setup function parameters
            dwCount = 1;
            // SzItemID, szAccessPath and blob_
            USES_CONVERSION;
            bstrItemID = _wcsdup(A2W(itemId));
            if (!bstrItemID) throw Technosoftware::Base::OutOfMemoryException();
            phClient = 1;
            phServer = NULL;
            pErrors = NULL;


            // get hda item handles
            hr = m_OPCHDASrv.m_pIOPCHistoricalServer->GetItemHandles(dwCount,
                &bstrItemID,
                &phClient,
                &phServer,
                &pErrors);

            OPCHANDLE opcHandle = phServer[0];

            ///////////////////////////////////////
            // cleanup
            if (bstrItemID)
                free(bstrItemID);
            if (phServer)
                ::CoTaskMemFree(phServer);
            if (pErrors)
                ::CoTaskMemFree(pErrors);

            return opcHandle;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //    cleanup the OPCHDA_TIME structure, realse string from memory and release structure itself
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void HdaServerImpl::GetTimeFromStringCleanup(OPCHDA_TIME* pTime)
        {
            if (pTime)
            {
                if (pTime->bString)
                {
                    if (pTime->szTime)
                        ::CoTaskMemFree(pTime->szTime);
                    pTime->szTime = NULL;
                }
                ::CoTaskMemFree((void*)pTime);
                pTime = NULL;
            }
        }
    }
}
