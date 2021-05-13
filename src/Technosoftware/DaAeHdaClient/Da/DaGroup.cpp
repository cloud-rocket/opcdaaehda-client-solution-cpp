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

#include <vector>

#include "OpcInternal.h"
#include "DaAeHdaClient/Da/DaGroup.h"
#include "DaGroupImpl.h"
#include "DaAeHdaClient/Da/DaServer.h"
#include "DaServerImpl.h"
#include "DaAeHdaClient/Da/DaItem.h"

#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        DaGroup::DaGroup(DaServer*  parent,
            const char*             name,
            bool                    active,
            uint32_t                requestedUpdateRate,
            Base::ClientHandle      handleClientGroup,
            long*                   timeBias,
            float*                  percentDeadband,
            uint32_t                lcId) noexcept(false) : OpcObject((OpcObject*)parent, "DaGroup")
        {
            try {
                impl_.Attach(new (std::nothrow) DaGroupImpl(
                    parent,
                    this,
                    name,
                    active,
                    requestedUpdateRate,
                    handleClientGroup,
                    timeBias,
                    percentDeadband,
                    lcId));
                if (!impl_) throw Technosoftware::Base::OutOfMemoryException();
            }
            catch (Technosoftware::Base::Status &e) {
                // Use this instance as source of the error
                throw Technosoftware::Base::Status(e);
            }
        }

        DaGroup::~DaGroup() throw ()
        {
            try {
                impl_->SetDataSubscription(NULL);      // Unsubscribe Data Change Notifications
                DeleteAllChildren();                      // Deletes all items
            }
            catch (...) {}
        }

        bool DaGroup::IsActive() const throw () { return impl_->m_fActive; }

        bool DaGroup::IsEnabled() const throw () { return impl_->m_fEnabled; }

        bool DaGroup::HasDataSubscription() const throw () { return impl_->m_pDataCallbackRef ? true : false; }

        uint32_t DaGroup::GetRevisedUpdateRate() const throw () { return impl_->m_dwRevisedUpdateRate; }

        Base::ServerHandle DaGroup::GetServerHandle() const throw () { return impl_->m_hServerGroup; }

        Base::ClientHandle DaGroup::GetClientHandle()  const throw () { return impl_->m_hClientGroup; }

        Base::Status DaGroup::SetActive(bool active) { return GetStatusFromHResult(impl_->SetActive(active)); }

        Base::Status DaGroup::AddItems(DaItemDefinitions& itemDefinitions,
            vector<DaItem*>& items,
            void(*errorHandler)(const DaItemDefinition& itemDefinitions, Base::Status status)) {
            return impl_->AddItems(itemDefinitions, items, errorHandler);
        }

        Base::Status DaGroup::Read(vector<DaItem*>& items, bool fromCache) { return impl_->Read(items, fromCache); }

        Base::Status DaGroup::Write(vector<DaItem*>& items) { return impl_->Write(items); }

        Base::Status DaGroup::SetDataSubscription(DaIDataCallback* userDataCallback) { return impl_->SetDataSubscription(userDataCallback); }

        Base::Status DaGroup::ReadAsync(vector<DaItem*>& items, uint32_t transactionId, uint32_t* cancelId) { return impl_->ReadAsync(items, transactionId, (DWORD*)cancelId); }

        Base::Status DaGroup::WriteAsync(vector<DaItem*>& items, uint32_t transactionId, uint32_t* cancelId) { return impl_->WriteAsync(items, transactionId, (DWORD*)cancelId); }

        Base::Status DaGroup::SetEnable(bool enable) { return GetStatusFromHResult(impl_->SetEnable(enable)); }

        Base::Status DaGroup::Cancel(uint32_t cancelId) { return GetStatusFromHResult(impl_->Cancel(cancelId)); }

        Base::Status DaGroup::Refresh(uint32_t transactionId, uint32_t* cancelId, bool fromCache) { return Technosoftware::DaAeHdaClient::GetStatusFromHResult(impl_->Refresh(transactionId, cancelId, fromCache)); }


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS DaGroupImpl
        //----------------------------------------------------------------------------------------------------------------------
        //
        // Please refer to class DaGroup for the description and documentation of attributes and member functions.
        //
        // Since the ...Impl classes are used only by one object all function members which are used only once are declared
        // as inline functions.
        //

        //----------------------------------------------------------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    DaGroupImpl::DaGroupImpl( DaServer* pParent, DaGroup* pImplOwner, const char* pszName, bool isActive_, uint32_t dwRequestedUpdateRate, ClientHandle hClientGroup, long* pTimeBias, float* pPercentDeadband, LCID dwLCID ) throw (Technosoftware::Base::Exception)
         *
         * @brief    Constructor.
         *
         * @exception    Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
         *
         * @param [in,out]    pParent                If non-null, the parent.
         * @param [in,out]    pImplOwner            If non-null, the owner of the implementation.
         * @param    pszName                        The name.
         * @param    isActive_                        true to active.
         * @param    dwRequestedUpdateRate       The requested update rate.
         * @param    hClientGroup                Group the client belongs to.
         * @param [in,out]    pTimeBias            If non-null, the time bias.
         * @param [in,out]    pPercentDeadband    If non-null, the percent deadband.
         * @param    dwLCID                        The lcid.
         */

        DaGroupImpl::DaGroupImpl(DaServer*   pParent,
            DaGroup*    pImplOwner,
            const char*    pszName,
            bool           fActive,
            uint32_t        dwRequestedUpdateRate,
            Base::ClientHandle    hClientGroup,
            long*          pTimeBias,
            float*         pPercentDeadband,
            LCID           dwLCID) throw (Technosoftware::Base::Exception)   // TODO: LCID
        {
            if (!pParent) throw Technosoftware::Base::InvalidArgumentException();

            // The server object must be connected to an DA server
            if (!pParent->IsConnected()) throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);

            m_pIMalloc = pParent->m_Impl->m_OPCDASrv.m_pIMalloc;
            if (!m_pIMalloc) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE));

            m_pIOPCServer = pParent->m_Impl->m_OPCDASrv.m_pIOPCServer;
            if (!m_pIOPCServer) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::DaFuncCall));

            // Group Name
            USES_CONVERSION;
            LPWSTR pwszName = L"";
            if (pszName) pwszName = A2W(pszName);

            // Add the Group
            HRESULT hr = m_pIOPCServer->AddGroup(
                pwszName,                     // Group Name
                fActive,                      // Active State
                dwRequestedUpdateRate,        // Requested Update Rate
                g_uGroupCount,                  // Client Group Handle
                pTimeBias,                    // TimeBias
                pPercentDeadband,             // Percent Deadband
                dwLCID,                       // The Locale ID (language)
                &m_hServerGroup,              // The generated unique server group handle is stored here
                &m_dwRevisedUpdateRate,       // Revised update rate
                IID_IOPCGroupStateMgt,        // The interface for the Group State Management is requested
                // The returned interface is stored here
                (LPUNKNOWN*)&m_pIOPCGroupStateMgt);

            if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));

            m_hGroup = g_uGroupCount;
            m_cGroups[g_uGroupCount++] = pImplOwner;

            m_pIOPCItemMgt = m_pIOPCGroupStateMgt;
            if (!m_pIOPCItemMgt) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::DaFuncCall));

            m_pIOPCSyncIO = m_pIOPCGroupStateMgt;
            if (!m_pIOPCSyncIO) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::DaFuncCall));

            m_pIOPCAsyncIO2 = m_pIOPCGroupStateMgt;
            if (!m_pIOPCAsyncIO2) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::DaFuncCall));

            m_hClientGroup = hClientGroup;
            m_dwDataCallbackCookie = 0;
            m_pDataCallbackRef = NULL;
            m_fEnabled = false;                          // Subscription State
            m_fActive = fActive;                         // Group State
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Destructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    DaGroupImpl::~DaGroupImpl() throw ()
         *
         * @brief    Destructor.
         */

        DaGroupImpl::~DaGroupImpl() throw ()
        {
            try {
                SetDataSubscription(NULL);
                m_pIOPCServer->RemoveGroup(m_hServerGroup, FALSE);
                m_cGroups.erase(m_hGroup);
            }
            catch (...) {}
        }


        //----------------------------------------------------------------------------------------------------------------------
        // SetActive
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    HRESULT DaGroupImpl::SetActive( bool isActive_ )
         *
         * @brief    Sets an active.
         *
         * @param    isActive_    true to active.
         *
         * @return    A HRESULT.
         */

        HRESULT DaGroupImpl::SetActive(bool fActive)
        {
            BOOL fActiveTmp = fActive ? TRUE : FALSE;
            HRESULT hr = m_pIOPCGroupStateMgt->SetState(NULL, &m_dwRevisedUpdateRate,
                &fActiveTmp,
                NULL, NULL, NULL, NULL);
            if (SUCCEEDED(hr)) {
                m_fActive = fActive;                      // Store the last state
            }
            return hr;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // AddItems
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaGroupImpl::AddItems(DaItemDefinitions& ItemDefs,
            vector<DaItem*>& arItems,
            void(*pfnErrHandler)(const DaItemDefinition& ItemDef, Technosoftware::Base::Status res))
        {
            Technosoftware::Base::Status res;
            DaItem*  pItem = NULL;
            DWORD       i, dwCreatedItemInstancesCount = 0;

            try {
                DWORD          dwCount;
                HRESULT        hr = S_OK;
                HRESULT*       pErrors = NULL;
                OPCITEMRESULT* pItemResults = NULL;

                // Replace the client handle with item instances
                dwCount = ItemDefs.parItemDefs_->GetSize();
                if (dwCount == 0)  throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_FALSE);

                OPCHANDLE* pHandle = NULL;
                for (i = 0; i < dwCount; i++) {
                    pHandle = &ItemDefs.parItemDefs_->m_aT[i].hClient;
                    pItem = new DaItem(this, *pHandle);
                    if (!pItem) throw Technosoftware::Base::OutOfMemoryException();
                    arItems.push_back(pItem);
                    *pHandle = (OPCHANDLE)g_uItemCount;
                    pItem->internalClientHandle_ = g_uItemCount;
                    m_cItems[g_uItemCount++] = pItem;
                    dwCreatedItemInstancesCount++;
                }

                hr = m_pIOPCItemMgt->AddItems(dwCount,
                    ItemDefs.parItemDefs_->GetData(),
                    &pItemResults,
                    &pErrors);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));

                for (i = 0; i < dwCount; i++) {
                    // Restore the client item handles
                    auto result = m_cItems.find(ItemDefs.parItemDefs_->m_aT[i].hClient);
                    if (result != m_cItems.end()) {
                        pItem = result->second;
                    }
                    else {
                        cout << "Element not found." << endl;
                    }
                    //pItem = (DaItem*)ItemDefs.parItemDefs_->m_aT[i].clientHandle_;
                    ItemDefs.parItemDefs_->m_aT[i].hClient = pItem->clientHandle_;

                    if (FAILED(pErrors[i])) {
                        if (pfnErrHandler) {
                            USES_CONVERSION;
                            OPCITEMDEF*    pItemDef = &(*ItemDefs.parItemDefs_)[i];
                            DaItemDefinition   def;
                            def.ItemIdentifier = W2A(pItemDef->szItemID);
                            def.ClientHandle = pItem->clientHandle_;
                            def.RequestedDataType = pItemDef->vtRequestedDataType;
                            def.IsActive = pItemDef->bActive == TRUE ? true : false;
                            def.AccessPath = W2A(pItemDef->szAccessPath);
                            def.BlobSize = pItemDef->dwBlobSize;
                            def.Blob = pItemDef->pBlob;
                            pfnErrHandler(def, Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i]));
                        }
                        std::vector<DaItem*>::iterator it = std::find(arItems.begin(), arItems.end(), pItem);
                        if (it != arItems.end()) {
                            arItems.erase(it);                    // Remove the item if not added successfully
                            delete pItem;                       // Delete not used local item instance
                        }
                    }
                    else {
                        pItem->FinalConstruct(&pItemResults[i]);

                        // Blob is not yet supported by this version so the memory can be alraedy released here.
                        // Move this section of code if Blob is supported in future versions.
                        if (pItemResults[i].pBlob) {
                            m_pIMalloc->Free(pItemResults[i].pBlob);
                        }
                    }
                }
                // Release all server allocated memory
                m_pIMalloc->Free(pItemResults);
                m_pIMalloc->Free(pErrors);
            }
            catch (Technosoftware::Base::Status& resEx) {
                res = resEx;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            // Restore the client handles and remove the item instances for all
            // elements which could not be added successfully to the server.
            if (res.IsNotGood()) {
                for (i = 0; i < dwCreatedItemInstancesCount; i++) {
                    auto result = m_cItems.find(ItemDefs.parItemDefs_->m_aT[i].hClient);
                    if (result != m_cItems.end()) {
                        pItem = result->second;
                    }
                    else {
                        cout << "Element not found." << endl;
                    }
                    ItemDefs.parItemDefs_->m_aT[i].hClient = pItem->clientHandle_;
                    delete pItem;
                }
            }

            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // CODE CComOPCDataCallbackImpl
        //----------------------------------------------------------------------------------------------------------------------

        CComOPCDataCallbackImpl::CComOPCDataCallbackImpl()
        {
            m_pIUserDataCallback = NULL;
        }


        void CComOPCDataCallbackImpl::Create(DaIDataCallback* pIUserDataCallback)
        {
            _ASSERTE(pIUserDataCallback);
            m_pIUserDataCallback = pIUserDataCallback;
        }


        CComOPCDataCallbackImpl::~CComOPCDataCallbackImpl()
        {
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IOPCDataCallback::OnDataChange
        // ------------------------------
        //    Handles exception based data changes and refreshes.
        //----------------------------------------------------------------------------------------------------------------------
        STDMETHODIMP CComOPCDataCallbackImpl::OnDataChange(
            /* [in] */           DWORD       dwTransid,
            /* [in] */           OPCHANDLE   hGroup,
            /* [in] */           HRESULT     hrMasterquality,
            /* [in] */           HRESULT     hrMastererror,
            /* [in] */           DWORD       dwCount,
            /* [size_is][in] */  OPCHANDLE*  phClientItems,
            /* [size_is][in] */  VARIANT*    pvValues,
            /* [size_is][in] */  WORD*       pwQualities,
            /* [size_is][in] */  FILETIME*   pftTimeStamps,
            /* [size_is][in] */  HRESULT*    pErrors)
        {
            DaItem*  pItem;
            DWORD       i;

            std::vector<DaItem*> items = std::vector<DaItem*>(dwCount);

            //OpcArray<DaItem*> items = OpcArray<DaItem*>(dwCount);

            for (i = 0; i < dwCount; i++) {
                auto result = m_cItems.find(phClientItems[i]);
                if (result != m_cItems.end()) {
                    pItem = result->second;
                }
                else {
                    cout << "Element not found." << endl;
                }
                items[i] = pItem;
                if (!pItem->GetReadAsyncResult().Set(
                    &pvValues[i],
                    &pftTimeStamps[i], pwQualities[i], Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i],Base::StatusCode::DaFuncCall)))
                {
                    hrMastererror = S_FALSE;
                }
            }

            DaGroup* pGroup;
            auto result = m_cGroups.find(hGroup);
            if (result != m_cGroups.end()) {
                pGroup = result->second;
            }
            else {
                cout << "Element not found." << endl;
            }

            m_pIUserDataCallback->DataChange(
                dwTransid,
                pGroup,
                (hrMasterquality == S_OK) ? true : false,
                (hrMastererror == S_OK) ? true : false,
                dwCount,
                (DaItem**)items.data()
            );
            items.clear();
            return S_OK;                                 // Must be be always S_OK
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IOPCDataCallback::OnReadComplete
        // --------------------------------
        //    Handles completion of async reads.
        //----------------------------------------------------------------------------------------------------------------------
        STDMETHODIMP CComOPCDataCallbackImpl::OnReadComplete(
            /* [in] */           DWORD       dwTransid,
            /* [in] */           OPCHANDLE   hGroup,
            /* [in] */           HRESULT     hrMasterquality,
            /* [in] */           HRESULT     hrMastererror,
            /* [in] */           DWORD       dwCount,
            /* [size_is][in] */  OPCHANDLE*  phClientItems,
            /* [size_is][in] */  VARIANT*    pvValues,
            /* [size_is][in] */  WORD*       pwQualities,
            /* [size_is][in] */  FILETIME*   pftTimeStamps,
            /* [size_is][in] */  HRESULT*    pErrors)
        {
            DaItem*  pItem;
            DWORD       i;

            std::vector<DaItem*> items = std::vector<DaItem*>(dwCount);
            //OpcArray<DaItem*> items = OpcArray<DaItem*>(dwCount);

            for (i = 0; i < dwCount; i++) {
                auto result = m_cItems.find(phClientItems[i]);
                if (result != m_cItems.end()) {
                    pItem = result->second;
                }
                else {
                    cout << "Element not found." << endl;
                }
                items[i] = pItem;
                if (!pItem->GetReadAsyncResult().Set(
                    &pvValues[i],
                    &pftTimeStamps[i], pwQualities[i], Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i],Base::StatusCode::DaFuncCall))) {
                    hrMastererror = S_FALSE;
                }
            }

            DaGroup* pGroup;
            auto result = m_cGroups.find(hGroup);
            if (result != m_cGroups.end()) {
                pGroup = result->second;
            }
            else {
                cout << "Element not found." << endl;
            }

            m_pIUserDataCallback->ReadComplete(
                dwTransid,
                pGroup,
                (hrMasterquality == S_OK) ? true : false,
                (hrMastererror == S_OK) ? true : false,
                dwCount,
                (DaItem**)items.data()
            );
            items.clear();
            return S_OK;                                 // Must be be always S_OK
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IOPCDataCallback::OnWriteComplete
        // ---------------------------------
        //    Handles completion of async writes.
        //----------------------------------------------------------------------------------------------------------------------
        STDMETHODIMP CComOPCDataCallbackImpl::OnWriteComplete(
            /* [in] */           DWORD       dwTransid,
            /* [in] */           OPCHANDLE   hGroup,
            /* [in] */           HRESULT     hrMastererr,
            /* [in] */           DWORD       dwCount,
            /* [size_is][in] */  OPCHANDLE*  phClientItems,
            /* [size_is][in] */  HRESULT*    pErrors)
        {
            DaItem*  pItem;
            DWORD       i;

            std::vector<DaItem*> items = std::vector<DaItem*>(dwCount);
            //OpcArray<DaItem*> items = OpcArray<DaItem*>(dwCount);

            for (i = 0; i < dwCount; i++) {
                auto result = m_cItems.find(phClientItems[i]);
                if (result != m_cItems.end()) {
                    pItem = result->second;
                }
                else {
                    cout << "Element not found." << endl;
                }
                items[i] = pItem;
                //pItem = (DaItem*)(phClientItems[i]);
                pItem->GetWriteAsyncResult().Set(Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i],Base::StatusCode::DaFuncCall));
        }

            DaGroup* pGroup;
            auto result = m_cGroups.find(hGroup);
            if (result != m_cGroups.end()) {
                pGroup = result->second;
            }
            else {
                cout << "Element not found." << endl;
            }

            m_pIUserDataCallback->WriteComplete(
                dwTransid,
                pGroup,
                (hrMastererr == S_OK) ? true : false,
                dwCount,
                (DaItem**)items.data()
            );
            items.clear();
            return S_OK;                                 // Must be be always S_OK
    }


        //----------------------------------------------------------------------------------------------------------------------
        // IOPCDataCallback::OnCancelComplete
        // -----------------------------------
        //    Handles completion of async cancel.
        //----------------------------------------------------------------------------------------------------------------------
        STDMETHODIMP CComOPCDataCallbackImpl::OnCancelComplete(
            /* [in] */           DWORD       dwTransid,
            /* [in] */           OPCHANDLE   hGroup)
        {
            DaGroup* pGroup;
            auto result = m_cGroups.find(hGroup);
            if (result != m_cGroups.end()) {
                pGroup = result->second;
            }
            else {
                cout << "Element not found." << endl;
            }

            m_pIUserDataCallback->CancelComplete(dwTransid, pGroup);
            return S_OK;                                 // Must be be always S_OK
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Read
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaGroupImpl::Read(vector<DaItem*>& arItems, bool fFromCache)
        {
            OPCHANDLE*  phServer = NULL;
            Technosoftware::Base::Status res;

            try {
                DWORD          i;
                DWORD          dwCount = arItems.size();
                HRESULT*       pErrors = NULL;
                OPCITEMSTATE*  pItemState = NULL;

                phServer = new OPCHANDLE[dwCount];
                if (!phServer) Technosoftware::Base::OutOfMemoryException();

                for (i = 0; i < dwCount; i++) {
                    phServer[i] = arItems[i]->GetServerHandle();
                }

                HRESULT hr = m_pIOPCSyncIO->Read(
                    fFromCache ? OPC_DS_CACHE : OPC_DS_DEVICE,
                    dwCount,
                    phServer,
                    &pItemState,
                    &pErrors);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (FAILED(hr)) throw res;

                for (i = 0; i < dwCount; i++) {
                    arItems[i]->readResult_.Attach(&pItemState[i], Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i]));
                }
                m_pIMalloc->Free(pItemState);
                m_pIMalloc->Free(pErrors);
            }
            catch (HRESULT hr) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
            }
            catch (Technosoftware::Base::Status& resEx) {
                res = resEx;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            if (phServer) delete[] phServer;

            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Write
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaGroupImpl::Write(vector<DaItem*>& arItems)
        {
            LPVARIANT   pValues = NULL;
            OPCHANDLE*  phServer = NULL;
            Technosoftware::Base::Status res;

            try {
                DWORD    i;
                DWORD    dwCount = arItems.size();
                HRESULT* pErrors = NULL;

                // Create an array with shallow copies of the values to be written.
                pValues = new VARIANT[dwCount];
                if (!pValues) Technosoftware::Base::OutOfMemoryException();

                phServer = new OPCHANDLE[dwCount];
                if (!phServer) Technosoftware::Base::OutOfMemoryException();

                for (i = 0; i < dwCount; i++) {
                    memcpy(&pValues[i], &arItems[i]->writeValue_, sizeof(VARIANT));    // Shallow Copy
                    phServer[i] = arItems[i]->GetServerHandle();
                }

                HRESULT hr = m_pIOPCSyncIO->Write(
                    dwCount,
                    phServer,
                    pValues,
                    &pErrors);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (FAILED(hr)) throw res;

                for (i = 0; i < dwCount; i++) {
                    arItems[i]->writeResult_.Set(Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i],Base::StatusCode::DaFuncCall));
                }
                m_pIMalloc->Free(pErrors);
            }
            catch (HRESULT hr) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
            }
            catch (Technosoftware::Base::Status& resEx) {
                res = resEx;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            if (pValues) delete[] pValues;
            if (phServer) delete[] phServer;

            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // SetDataSubscription
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaGroupImpl::SetDataSubscription(DaIDataCallback* pIUserDataCallback)
        {
            HRESULT hr = S_OK;

            //
            // Unsubscibe Data Change Notifications
            //
            if (pIUserDataCallback == NULL) {
                if (m_ICP) {
                    if (m_dwDataCallbackCookie) {
                        hr = m_ICP->Unadvise(m_dwDataCallbackCookie);
                        m_dwDataCallbackCookie = 0;
                        m_pDataCallbackRef = NULL;
                    }
                    m_ICP = NULL;                          // Connection Point no longer used.
                }
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
            }

            //
            // Subscibe Data Change Notifications
            //
            Technosoftware::Base::Status res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
            try {
                CComQIPtr<IConnectionPointContainer, &IID_IConnectionPointContainer> ICPC(m_pIOPCGroupStateMgt);
                if (!ICPC) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::DaFuncCall));

                hr = ICPC->FindConnectionPoint(IID_IOPCDataCallback, &m_ICP);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::DaFuncCall));

                // Create an instance of the callback function
                m_pDataCallbackRef = new (std::nothrow) CComObjectOPCDataCallback;
                if (!m_pDataCallbackRef) throw Technosoftware::Base::OutOfMemoryException();
                m_pDataCallbackRef->Create(pIUserDataCallback);
                m_pDataCallbackRef->AddRef();                // Add temporary reference during creation

                // Create a connection between the connection point
                // and the created callback function.
                // Note : A Pointer to the IUnknown interface of the
                // created Event Sink must be passed to the advise function.
                CComPtr<IUnknown> IUnkCallback(m_pDataCallbackRef);
                if (!IUnkCallback) {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE);
                }
                else {
                    hr = m_ICP->Advise(IUnkCallback, &m_dwDataCallbackCookie);
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                }
                m_pDataCallbackRef->Release();               // Release temporary reference
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
                m_pDataCallbackRef = NULL;
            }
            else {
                m_fEnabled = true;                           // Successfully subscribed
            }                                               // New subscriptions are enabled by default
            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // ReadAsync
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaGroupImpl::ReadAsync(vector<DaItem*>& arItems, DWORD dwTransactionID, DWORD* pdwCancelID)
        {
            OPCHANDLE*  phServer = NULL;
            Technosoftware::Base::Status res;

            try {
                DWORD    i;
                DWORD    dwCount = arItems.size();
                HRESULT* pErrors = NULL;

                phServer = new OPCHANDLE[dwCount];
                if (!phServer) throw Technosoftware::Base::OutOfMemoryException();

                for (i = 0; i < dwCount; i++) {
                    phServer[i] = arItems[i]->GetServerHandle();
                }

                HRESULT hr = m_pIOPCAsyncIO2->Read(
                    dwCount,
                    phServer,
                    dwTransactionID,
                    pdwCancelID,
                    &pErrors);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (FAILED(hr)) throw res;

                for (i = 0; i < dwCount; i++) {
                    arItems[i]->asyncCommandResult_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i],Base::StatusCode::DaFuncCall);
                }
                m_pIMalloc->Free(pErrors);
            }
            catch (HRESULT hr) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
            }
            catch (Technosoftware::Base::Status& resEx) {
                res = resEx;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            if (phServer) delete[] phServer;

            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // WriteAsync
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaGroupImpl::WriteAsync(vector<DaItem*>& arItems, DWORD dwTransactionID, DWORD* pdwCancelID)
        {
            LPVARIANT   pValues = NULL;
            OPCHANDLE*  phServer = NULL;
            Technosoftware::Base::Status res;

            try {
                DWORD    i;
                DWORD    dwCount = arItems.size();
                HRESULT* pErrors = NULL;

                // Create an array with shallow copies of the values to be written.
                pValues = new VARIANT[dwCount];
                if (!pValues) throw Technosoftware::Base::OutOfMemoryException();

                phServer = new OPCHANDLE[dwCount];
                if (!phServer) throw Technosoftware::Base::OutOfMemoryException();

                for (i = 0; i < dwCount; i++) {
                    memcpy(&pValues[i], &arItems[i]->writeValue_, sizeof(VARIANT));    // Shallow Copy
                    phServer[i] = arItems[i]->GetServerHandle();
                }

                HRESULT hr = m_pIOPCAsyncIO2->Write(
                    dwCount,
                    phServer,
                    pValues,
                    dwTransactionID,
                    pdwCancelID,
                    &pErrors);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (FAILED(hr)) throw res;

                for (i = 0; i < dwCount; i++) {
                    arItems[i]->asyncCommandResult_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(pErrors[i],Base::StatusCode::DaFuncCall);
                }
                m_pIMalloc->Free(pErrors);
            }
            catch (HRESULT hr) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
            }
            catch (Technosoftware::Base::Status& resEx) {
                res = resEx;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            if (pValues) delete[] pValues;
            if (phServer) delete[] phServer;

            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // SetEnable
        //----------------------------------------------------------------------------------------------------------------------
        HRESULT DaGroupImpl::SetEnable(bool fEnable)
        {
            HRESULT hr = m_pIOPCAsyncIO2->SetEnable(fEnable ? TRUE : FALSE);
            if (SUCCEEDED(hr)) {
                m_fEnabled = fEnable;                     // Store the new state
            }
            return hr;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // GetEnable
        //----------------------------------------------------------------------------------------------------------------------
        HRESULT DaGroupImpl::GetEnable(bool* pfEnable)
        {
            BOOL  fEnable = FALSE;
            HRESULT hr = m_pIOPCAsyncIO2->GetEnable(&fEnable);
            *pfEnable = fEnable ? true : false;
            return hr;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Cancel
        //----------------------------------------------------------------------------------------------------------------------
        HRESULT DaGroupImpl::Cancel(uint32_t dwCancelID)
        {
            return m_pIOPCAsyncIO2->Cancel2(dwCancelID);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Refresh
        //----------------------------------------------------------------------------------------------------------------------
        HRESULT DaGroupImpl::Refresh(uint32_t dwTransactionID, uint32_t* pdwCancelID, bool fFromCache)
        {
            return m_pIOPCAsyncIO2->Refresh2(
                fFromCache ? OPC_DS_CACHE : OPC_DS_DEVICE,
                dwTransactionID,
                (DWORD*)pdwCancelID);
        }
}}