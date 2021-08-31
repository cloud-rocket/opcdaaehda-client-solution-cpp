/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __DaGROUPIMPL_H
#define __DaGROUPIMPL_H

#include "Base/Status.h"
#include "Base/HashMap.h"
#include "DaAeHdaClient/OpcBase.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class DaServer;

        //======================================================================================================================
        // OPCDataCallback Object
        //======================================================================================================================

        //----------------------------------------------------------------------------------------------------------------------
        // CLASS CComOPCDataCallbackImpl
        //----------------------------------------------------------------------------------------------------------------------
        class CComOPCDataCallbackImpl : public IOPCDataCallback
        {
        public:
            // Construction
            CComOPCDataCallbackImpl();
            void Create(DaIDataCallback* pIUserDataCallback);

            // Destruction
            ~CComOPCDataCallbackImpl();

            // IOPCDataCallback functions
            STDMETHODIMP OnDataChange(
                /* [in] */           DWORD       dwTransid,
                /* [in] */           OPCHANDLE   hGroup,
                /* [in] */           HRESULT     hrMasterquality,
                /* [in] */           HRESULT     hrMastererror,
                /* [in] */           DWORD       dwCount,
                /* [size_is][in] */  OPCHANDLE*  phClientItems,
                /* [size_is][in] */  VARIANT*    pvValues,
                /* [size_is][in] */  WORD*       pwQualities,
                /* [size_is][in] */  FILETIME*   pftTimeStamps,
                /* [size_is][in] */  HRESULT*    pErrors);

            STDMETHODIMP OnReadComplete(
                /* [in] */           DWORD       dwTransid,
                /* [in] */           OPCHANDLE   hGroup,
                /* [in] */           HRESULT     hrMasterquality,
                /* [in] */           HRESULT     hrMastererror,
                /* [in] */           DWORD       dwCount,
                /* [size_is][in] */  OPCHANDLE*  phClientItems,
                /* [size_is][in] */  VARIANT*    pvValues,
                /* [size_is][in] */  WORD*       pwQualities,
                /* [size_is][in] */  FILETIME*   pftTimeStamps,
                /* [size_is][in] */  HRESULT*    pErrors);

            STDMETHODIMP OnWriteComplete(
                /* [in] */           DWORD       dwTransid,
                /* [in] */           OPCHANDLE   hGroup,
                /* [in] */           HRESULT     hrMastererr,
                /* [in] */           DWORD       dwCount,
                /* [size_is][in] */  OPCHANDLE*  phClientItems,
                /* [size_is][in] */  HRESULT*    pErrors);

            STDMETHODIMP OnCancelComplete(
                /* [in] */           DWORD       dwTransid,
                /* [in] */           OPCHANDLE   hGroup);

        protected:
            DaIDataCallback*  m_pIUserDataCallback;

        };


        //----------------------------------------------------------------------------------------------------------------------
        // CLASS CComOPCDataCallback
        //----------------------------------------------------------------------------------------------------------------------
        template <class ThreadModel = CComObjectThreadModel>
        class ATL_NO_VTABLE CComOPCDataCallback :
            public CComOPCDataCallbackImpl,
            public CComObjectRootEx< ThreadModel >
        {
        public:
            BEGIN_COM_MAP(CComOPCDataCallback)
                COM_INTERFACE_ENTRY_IID(IID_IOPCDataCallback, CComOPCDataCallbackImpl)
            END_COM_MAP()
        };


        //----------------------------------------------------------------------------------------------------------------------
        // TYPEDEF CComObject CComObjectOPCDataCallback
        //----------------------------------------------------------------------------------------------------------------------
        typedef  CComObjectNoLock< CComOPCDataCallback<> > CComObjectOPCDataCallback;


        //======================================================================================================================

        //----------------------------------------------------------------------------------------------------------------------
        // CLASS DaGroupImpl
        //----------------------------------------------------------------------------------------------------------------------
        class DaGroupImpl : protected OpcObject
        {
            // Construction / Destruction
        public:
            DaGroupImpl(DaServer*   pParent,
                DaGroup*    pOwner,
                const char*    pszName,
                bool           fActive,
                uint32_t        dwRequestedUpdateRate,
                Base::ClientHandle    hClientGroup,
                long*          pTimeBias,
                float*         pPercentDeadband,
                LCID           dwLCID)  throw (Technosoftware::Base::Exception);
            ~DaGroupImpl() throw ();

            // Operations
            inline HRESULT SetActive(bool fActive);
            inline Technosoftware::Base::Status AddItems(DaItemDefinitions& ItemDefs,
                vector<DaItem*>& arItems,
                const std::function<void(const DaItemDefinition&, Base::Status)>& pfnErrHandler);
            inline Technosoftware::Base::Status Read(vector<DaItem*>& arItems, bool fFromCache);
            inline Technosoftware::Base::Status Write(vector<DaItem*>& arItems);
            inline Technosoftware::Base::Status SetDataSubscription(DaIDataCallback* pIUserDataCallback);
            inline Technosoftware::Base::Status ReadAsync(vector<DaItem*>& arItems, DWORD dwTransactionID, DWORD* pdwCancelID);
            inline Technosoftware::Base::Status WriteAsync(vector<DaItem*>& arItems, DWORD dwTransactionID, DWORD* pdwCancelID);
            inline HRESULT SetEnable(bool fEnable);
            inline HRESULT GetEnable(bool* pfEnable);
            inline HRESULT Cancel(uint32_t dwCancelID);
            inline HRESULT Refresh(uint32_t dwTransactionID, uint32_t* pdwCancelID, bool fFromCache);


            // Implementation
        protected:
            friend class DaGroup;
            friend class DaItem;
            CComPtr<IMalloc>           m_pIMalloc;
            CComPtr<IOPCServer>        m_pIOPCServer;
            CComPtr<IOPCGroupStateMgt> m_pIOPCGroupStateMgt;
            CComPtr<IOPCItemMgt>       m_pIOPCItemMgt;
            CComPtr<IOPCSyncIO>        m_pIOPCSyncIO;
            CComPtr<IOPCAsyncIO2>      m_pIOPCAsyncIO2;
            OPCHANDLE                  m_hServerGroup;
            OPCHANDLE                  m_hClientGroup;
            unsigned long               m_hGroup;
            DWORD                      m_dwRevisedUpdateRate;
            CComPtr<IConnectionPoint>  m_ICP;
            DWORD                      m_dwDataCallbackCookie;
            CComObjectOPCDataCallback* m_pDataCallbackRef;
            bool                       m_fEnabled;       // Subscription State
            bool                       m_fActive;        // Group State
        };

        static Base::HashMap<Base::ServerHandle, DaItem*> m_cItems;
        static unsigned long g_uItemCount = 0;

        static Base::HashMap<Base::ServerHandle, DaGroup*> m_cGroups;
        static unsigned long g_uGroupCount = 0;

    }
}
#endif // __DaGROUPIMPL_H
