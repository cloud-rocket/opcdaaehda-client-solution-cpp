/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __DABROWSERIMPL_H
#define __DABROWSERIMPL_H

#include "DaAeHdaClient/OpcBase.h"

class DaServer;

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //----------------------------------------------------------------------------------------------------------------------
        // CLASS 
        //----------------------------------------------------------------------------------------------------------------------
        class DaBrowserImpl : protected OpcObject
        {
            // Construction / Destruction
        public:
            DaBrowserImpl(DaServer* pParent, DaBrowseFilters* pFilters) throw (Technosoftware::Base::Exception);
            ~DaBrowserImpl() throw ();

            // Operations
            Technosoftware::Base::Status Browse(const string& sPosition) throw ();
            Technosoftware::Base::Status BrowseNext() throw ();
            DaItemProperties& GetProperties(const string& sItemID);
            string GetPropertyValueAsText(const string& sItemID, DWORD dwPropertyId) throw();
            Technosoftware::Base::Status SetFilters(const DaBrowseFilters& Filters) throw ();

            // Implementation
            Technosoftware::Base::Status BrowseHierarchical2(const DaBrowseElementFilter& eBrowseElementFilter, const string& sPosition) throw ();
            Technosoftware::Base::Status GetProperties2(LPWSTR szItemID, bool fIsItem, bool fWithValue, OPCITEMPROPERTIES* pProperties) throw ();
            Technosoftware::Base::Status AddElementsFromIEnumString(LPENUMSTRING pIEnumString, bool fGetFullyQualifiedID, bool fIsItem) throw ();
            void ReleaseOPCITEMPROPERTIES(OPCITEMPROPERTIES* pProperties);

            DaBrowseElements                        m_Elements;
            DaBrowseFilters                         m_Filters;
            DaItemProperties                        m_ItemProperties;

            LPWSTR                                  m_pszContinuationPoint;
            BOOL                                    m_fMoreElements;

            CComPtr<IMalloc>                        m_pIMalloc;
            CComPtr<IOPCBrowse>                     m_pIOPCBrowse;          // OPC DA 3.0
            CComPtr<IOPCBrowseServerAddressSpace>   m_pIOPCBrowseSAS;       // OPC DA 2.0
            CComPtr<IOPCItemProperties>             m_pIOPCItemProperties;  // used only by OPC DA 2.0 SAS

            OPCNAMESPACETYPE                        m_NameSpaceType;        // used only by OPC DA 2.0 SAS
        };
    }
}
#endif // __DABROWSERIMPL_H
