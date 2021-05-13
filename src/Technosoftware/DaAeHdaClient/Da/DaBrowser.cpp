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
#include "OpcUti.h"
#include "DaAeHdaClient/Da/DaBrowser.h"
#include "DaBrowserImpl.h"
#include "DaAeHdaClient/Da/DaServer.h"
#include "DaServerImpl.h"
#include "matchpattern.h"

#include "Base/Exception.h"

 /**
  * @def    _CRTDBG_MAP_ALLOC
  *
  * @brief    A macro that defines crtdbg map allocate.
  */

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

namespace Technosoftware
{
    namespace DaAeHdaClient
    {

        DaBrowseFilters::DaBrowseFilters(DaBrowseElementFilter browseElementFilter,
            const string& elementNameFilter,
            const string& vendorFilter,
            uint32_t maxElementsReturned,
            bool returnAllProperties,
            bool returnPropertyValues,
            VARTYPE dataTypeFilter,
            uint32_t accessRightsFilter) noexcept(false)
        {
            try {
                browseElementFilter_ = browseElementFilter;
                elementNameFilter_ = elementNameFilter;
                vendorFilter_ = vendorFilter;
                mDwMaxElementsReturned_ = maxElementsReturned;
                returnAllProperties_ = returnAllProperties;
                returnPropertyValues_ = returnPropertyValues;
                dataTypeFilter_ = dataTypeFilter;
                accessRightsFilter_ = accessRightsFilter;
            }
            catch (...) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
        }

        DaBrowseFilters::DaBrowseFilters(OpcObject* parent,
            DaBrowseElementFilter browseElementFilter /* = All */,
            const string& elementNameFilter /* = "" */,
            const string& vendorFilter /* = "" */,
            uint32_t maxElementsReturned /* = 0 */,
            bool returnAllProperties /* = false */,
            bool returnPropertyValues /* = false */,
            VARTYPE dataTypeFilter /* = VT_EMPTY */,
            uint32_t accessRightsFilter /* = OPC_READABLE + OPC_WRITEABLE */
        ) noexcept(false) : OpcObject(parent, "DaBrowseFilters")
        {
            try {
                browseElementFilter_ = browseElementFilter;
                elementNameFilter_ = elementNameFilter;
                vendorFilter_ = vendorFilter;
                mDwMaxElementsReturned_ = maxElementsReturned;
                returnAllProperties_ = returnAllProperties;
                returnPropertyValues_ = returnPropertyValues;
                dataTypeFilter_ = dataTypeFilter;
                accessRightsFilter_ = accessRightsFilter;
            }
            catch (...) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
        }

        DaBrowseFilters::~DaBrowseFilters() noexcept {}

        DaBrowseFilters& DaBrowseFilters::operator =(const DaBrowseFilters& Filters) noexcept(false)
        {
            try {
                if (this != &Filters) {
                    browseElementFilter_ = Filters.browseElementFilter_;
                    elementNameFilter_ = Filters.elementNameFilter_;
                    vendorFilter_ = Filters.vendorFilter_;
                    mDwMaxElementsReturned_ = Filters.mDwMaxElementsReturned_;
                    returnAllProperties_ = Filters.returnAllProperties_;
                    returnPropertyValues_ = Filters.returnPropertyValues_;
                    dataTypeFilter_ = Filters.dataTypeFilter_;
                    accessRightsFilter_ = Filters.accessRightsFilter_;
                }
            }
            catch (...) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
            return *this;
        }

        bool DaBrowseElement::IsItem() const throw() { return m_dwFlagValue & OPC_BROWSE_ISITEM ? true : false; }

        bool DaBrowseElement::HasChildren() const throw() { return m_dwFlagValue & OPC_BROWSE_HASCHILDREN ? true : false; }

        DaBrowseElement::DaBrowseElement(LPVOID pOPCBROWSEELEMENT) noexcept(false) : OpcObject(NULL, "DaBrowseElement")
        {
            OPCBROWSEELEMENT* pEl = static_cast<OPCBROWSEELEMENT*>(pOPCBROWSEELEMENT);
            if (!pEl) throw Technosoftware::Base::InvalidArgumentException();
            try {
                USES_CONVERSION;
                name_ = W2A(pEl->szName);
                itemId_ = W2A(pEl->szItemID);
                m_dwFlagValue = pEl->dwFlagValue;

                // Add the available Properties
                if (SUCCEEDED(pEl->ItemProperties.hrErrorID)) {
                    for (DWORD z = 0; z < pEl->ItemProperties.dwNumProperties; z++) {
                        DaItemProperty prop(&pEl->ItemProperties.pItemProperties[z]);
                        itemProperties_.push_back(prop);
                    }
                }
            }
            catch (Technosoftware::Base::Status e) {
                throw e;
            }
            catch (...) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
        }

        DaBrowseElement::DaBrowseElement(const char* pszName, LPVOID pOPCITEMPROPERTIES) noexcept(false) : OpcObject(NULL, "DaBrowseElement")
        {
            if (!pszName) throw Technosoftware::Base::InvalidArgumentException();

            OPCITEMPROPERTIES* pProperties = static_cast<OPCITEMPROPERTIES*>(pOPCITEMPROPERTIES);
            if (!pProperties) throw Technosoftware::Base::InvalidArgumentException();

            try {
                name_ = pszName;
                itemId_ = pszName;
                m_dwFlagValue = OPC_BROWSE_ISITEM;

                // Add the available Properties
                if (SUCCEEDED(pProperties->hrErrorID)) {
                    for (DWORD z = 0; z < pProperties->dwNumProperties; z++) {
                        DaItemProperty prop(&pProperties->pItemProperties[z]);
                        itemProperties_.push_back(prop);
                    }
                }
            }
            catch (Technosoftware::Base::Status e) {
                throw e;
            }
            catch (...) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
        }

        DaBrowseElement::DaBrowseElement(const char* name, const char* itemId, bool isItem, LPVOID itemProperties) noexcept(false) : OpcObject(NULL, "DaBrowseElement")
        {
            if (!name || !itemId) throw Technosoftware::Base::InvalidArgumentException();

            OPCITEMPROPERTIES* pProperties = static_cast<OPCITEMPROPERTIES*>(itemProperties);
            if (!pProperties) throw Technosoftware::Base::InvalidArgumentException();

            try {
                name_ = name;
                itemId_ = itemId;

                if (isItem) m_dwFlagValue = OPC_BROWSE_ISITEM;
                else         m_dwFlagValue = OPC_BROWSE_HASCHILDREN;

                // Add the available Properties
                if (SUCCEEDED(pProperties->hrErrorID)) {
                    for (DWORD z = 0; z < pProperties->dwNumProperties; z++) {
                        DaItemProperty prop(&pProperties->pItemProperties[z]);
                        itemProperties_.push_back(prop);
                    }
                }
            }
            catch (Technosoftware::Base::Status e) {
                throw e;
            }
            catch (...) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
        }

        DaBrowseElement::DaBrowseElement(const DaBrowseElement& BrowseElement) noexcept(false) : OpcObject(NULL, "DaBrowseElement")
        {
            *this = BrowseElement;
        }

        DaBrowseElement::~DaBrowseElement() throw () {}

        DaBrowseElement& DaBrowseElement::operator =(const DaBrowseElement& browseElement) noexcept(false)
        {
            try {
                if (this != &browseElement) {
                    name_ = browseElement.name_;
                    itemId_ = browseElement.itemId_;
                    m_dwFlagValue = browseElement.m_dwFlagValue;
                    itemProperties_ = browseElement.itemProperties_;
                }
            }
            catch (...) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
            return *this;
        }

        DaBrowser::DaBrowser(DaServer* parent,
            DaBrowseFilters* filters /* = NULL */
        ) noexcept(false) : OpcObject((OpcObject*)parent, "DaBrowser")
        {
            try {
                impl_.Attach(new (std::nothrow) DaBrowserImpl(
                    parent,
                    filters));
                if (!impl_) throw Technosoftware::Base::OutOfMemoryException();
            }
            catch (Technosoftware::Base::Status &e) {
                // Use this instance as source of the error
                throw Technosoftware::Base::Status(e);
            }
        }

        DaBrowser::~DaBrowser() throw () {}

        DaBrowseElements& DaBrowser::GetElements() const { return impl_->m_Elements; }

        DaBrowseFilters& DaBrowser::GetFilters() const { return impl_->m_Filters; }

        bool DaBrowser::HasMoreElements() const throw() { return impl_->m_fMoreElements ? true : false; }

        bool DaBrowser::IsBrowse2Used() const noexcept { return impl_->m_pIOPCBrowseSAS ? true : false; }

        bool DaBrowser::IsBrowse3Used() const noexcept { return impl_->m_pIOPCBrowse ? true : false; }

        Technosoftware::Base::Status DaBrowser::Browse(const string& position) { return impl_->Browse(position); }

        Technosoftware::Base::Status DaBrowser::BrowseNext() { return impl_->BrowseNext(); }

        Technosoftware::Base::Status DaBrowser::SetFilters(const DaBrowseFilters& filters) noexcept { return impl_->SetFilters(filters); }

        string DaBrowser::GetPropertyValueAsText(const string& itemId, DWORD propertyId) { return impl_->GetPropertyValueAsText(itemId, propertyId); };

        DaItemProperties& DaBrowser::GetProperties(const string& itemId) noexcept { return impl_->GetProperties(itemId); };


        //----------------------------------------------------------------------------------------------------------------------
        // IMPLEMENTATION CLASS DaBrowserImpl
        //----------------------------------------------------------------------------------------------------------------------
        //
        // Please refer to class DaBrowser for the description and documentation of attributes and member functions.
        //
        // Since the ...Impl classes are used only by one object all function members which are used only once are declared
        // as inline functions.
        //

        //----------------------------------------------------------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    DaBrowserImpl::DaBrowserImpl( DaServer* pParent, DaBrowseFilters* pFilters ) throw (Technosoftware::Base::Exception)
         *
         * @brief    Constructor.
         *
         * @exception    Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
         *
         * @param [in,out]    pParent     If non-null, the parent.
         * @param [in,out]    pFilters    If non-null, the filters.
         */

        DaBrowserImpl::DaBrowserImpl(DaServer* pParent,
            DaBrowseFilters* pFilters) throw (Technosoftware::Base::Exception)
        {
            if (!pParent) throw Technosoftware::Base::InvalidArgumentException();

            // The server object must be connected to an DA server
            if (!pParent->IsConnected()) throw Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_SRVNOTCONNECTED);

            m_pIMalloc = pParent->m_Impl->m_OPCDASrv.m_pIMalloc;
            if (!m_pIMalloc) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE));

            pParent->m_Impl->m_OPCDASrv.m_pIOPCServer->QueryInterface(IID_IOPCBrowse, (LPVOID*)&m_pIOPCBrowse);
            if (!m_pIOPCBrowse) {                        // There is no OPC 3.0 Browse Interface
                pParent->m_Impl->m_OPCDASrv.m_pIOPCServer->QueryInterface(IID_IOPCBrowseServerAddressSpace, (LPVOID*)&m_pIOPCBrowseSAS);
                if (!m_pIOPCBrowseSAS) {
                    throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE));  // The specified server doesn't support browse interfaces
                }

                pParent->m_Impl->m_OPCDASrv.m_pIOPCServer->QueryInterface(IID_IOPCItemProperties, (LPVOID*)&m_pIOPCItemProperties);
                if (!m_pIOPCItemProperties) {
                    throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOINTERFACE,Base::StatusCode::DaFuncCall));   // IOPCItemProperties is mandatory for OPC 2.0
                }

                HRESULT hr = m_pIOPCBrowseSAS->QueryOrganization(&m_NameSpaceType);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));

                // Check if 'Browse To' is supported if the SAS is hierarchical (Note: is not supported by OPC 1.0)
                if (m_NameSpaceType == OPC_NS_HIERARCHIAL) {
                    hr = m_pIOPCBrowseSAS->ChangeBrowsePosition(OPC_BROWSE_TO, L"");   // Browse to root for test
                    if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));
                }
            }

            //m_pszContinuationPoint = (LPWSTR)CoTaskMemAlloc( sizeof (WCHAR) );
            //wcscpy( m_pszContinuationPoint, L"" );

            m_pszContinuationPoint = NULL;

            if (pFilters) {
                m_Filters = *pFilters;
            }

            m_fMoreElements = FALSE;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Destructor
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    DaBrowserImpl::~DaBrowserImpl() throw ()
         *
         * @brief    Destructor.
         */

        DaBrowserImpl::~DaBrowserImpl() throw ()
        {
            try {
                if (m_pszContinuationPoint) {             // Always check the pointer to NULL although initialized
                    // always by the c'tor. A server modifies this string but if
                    // something goes wrong a server can set the pointer to NULL.
                    CoTaskMemFree(m_pszContinuationPoint);
                }
            }
            catch (...) {}
        }


        //----------------------------------------------------------------------------------------------------------------------
        // Browse
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaBrowserImpl::Browse(const string& sPosition) noexcept
        {
            USES_CONVERSION;
            Technosoftware::Base::Status res;

            // Remove all existing elements
            m_Elements.clear();

            if (m_pIOPCBrowse) {
                //
                // OPC 3.0 SAS
                //
                DWORD             dwPropertyCount = 0;                            // Dummy
                DWORD             adwPropertyIDs[1] = { OPC_PROPERTY_DATATYPE };  // Dummy

                DWORD             dwElementCount = 0;
                OPCBROWSEELEMENT* pBrowseElements = NULL;
                OPCBROWSEFILTER   dwGetBrowseElementFilter;

                // Map the Element Filter
                if (m_Filters.GetBrowseElementFilter() == DaBrowseElementFilter::All)           dwGetBrowseElementFilter = OPC_BROWSE_FILTER_ALL;
                else if (m_Filters.GetBrowseElementFilter() == DaBrowseElementFilter::Branches) dwGetBrowseElementFilter = OPC_BROWSE_FILTER_BRANCHES;
                else                                                  dwGetBrowseElementFilter = OPC_BROWSE_FILTER_ITEMS;

                HRESULT hr = m_pIOPCBrowse->Browse(
                    A2W(sPosition.c_str()),
                    &m_pszContinuationPoint,
                    m_Filters.GetMaxElementsReturned(),
                    dwGetBrowseElementFilter,
                    A2W(m_Filters.GetElementNameFilter().c_str()),
                    A2W(m_Filters.GetVendorFilter().c_str()),
                    m_Filters.IsReturnAllProperties() ? TRUE : FALSE,
                    m_Filters.GetReturnPropertyValues() ? TRUE : FALSE,
                    dwPropertyCount,
                    adwPropertyIDs,
                    &m_fMoreElements,
                    &dwElementCount,
                    &pBrowseElements);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (res.IsNotGood()) return res;

                //
                // Add the browse 

                //
                DWORD i = 0;
                try {
                    for (i = 0; i < dwElementCount; i++) {
                        OPCBROWSEELEMENT* pEl = &pBrowseElements[i];
                        DaBrowseElement el(pEl);
                        m_Elements.push_back(el);
                        m_pIMalloc->Free(pEl->szName);
                        m_pIMalloc->Free(pEl->szItemID);
                        ReleaseOPCITEMPROPERTIES(&pEl->ItemProperties);
                    }
                }
                catch (Technosoftware::Base::Status e) {
                    // Map the exception objject to an Technosoftware::Base::Status object
                    res = e;
                }
                catch (...) {
                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
                }

                // Release all not yet released memory in case of error
                if (res.IsNotGood()) {
                    for (; i < dwElementCount; i++) {
                        m_pIMalloc->Free(pBrowseElements[i].szName);
                        m_pIMalloc->Free(pBrowseElements[i].szItemID);
                        ReleaseOPCITEMPROPERTIES(&pBrowseElements[i].ItemProperties);
                    }
                    // Release all previously successfully added elements
                    m_Elements.clear();
                }
                m_pIMalloc->Free(pBrowseElements);
            }
            else {
                //
                // OPC 2.0 SAS
                //
                m_fMoreElements = FALSE;                  // New Browse operation resets this flag

                if (m_NameSpaceType == OPC_NS_FLAT) {
                    //
                    // OPC 2.0 SAS is flat
                    //
                    if (m_Filters.GetBrowseElementFilter() == DaBrowseElementFilter::Branches) {
                        return Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);     // There are no branches if the SAS is flat.
                    }
                    if (sPosition.length() > 0) {          // Only root is accepted as branch name because the SAS is flat and has no other branches
                        return Technosoftware::DaAeHdaClient::GetStatusFromHResult(OPC_E_UNKNOWNITEMID,Base::StatusCode::DaFuncCall);
                    }

                    LPENUMSTRING pIEnumString = NULL;
                    HRESULT hr = m_pIOPCBrowseSAS->BrowseOPCItemIDs(
                        OPC_FLAT,
                        A2W(m_Filters.GetElementNameFilter().c_str()),
                        m_Filters.GetDataTypeFilter(),
                        m_Filters.GetAccessRightsFilter(),
                        &pIEnumString);

                    res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                    if (res.IsNotGood()) return res;

                    res = AddElementsFromIEnumString(pIEnumString, false, false);
                }
                else {
                    //
                    // OPC 2.0 SAS is hierarchical
                    //
                    res = BrowseHierarchical2(m_Filters.GetBrowseElementFilter(), sPosition);
                }
            }
            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // BrowseNext
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaBrowserImpl::BrowseNext() throw ()
        {
            if (wcslen(m_pszContinuationPoint) == 0) {
                m_Elements.clear();
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
            }
            return Browse("");
        }


        //----------------------------------------------------------------------------------------------------------------------
        // SetFilters
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaBrowserImpl::SetFilters(const DaBrowseFilters& Filters) throw ()
        {
            try {
                m_Filters = Filters;
                return Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
            }
            catch (Technosoftware::Base::Status &e) {
                return e;
            }
        }

        string DaBrowserImpl::GetPropertyValueAsText(const string& sItemID, DWORD dwPropertyId) throw()
        {
            USES_CONVERSION;
            Technosoftware::Base::Status res;

            DWORD             dwPropertyCount = 0;                            // Dummy
            DWORD             adwPropertyIDs[1] = { OPC_PROPERTY_DATATYPE };  // Dummy

            DWORD             dwElementCount = 0;
            OPCBROWSEELEMENT* pBrowseElements = NULL;
            OPCBROWSEFILTER   dwGetBrowseElementFilter;
            OPCITEMPROPERTIES* pProperties;
            LPWSTR sItemName = A2W(sItemID.c_str());

            // Map the Element Filter
            if (m_Filters.GetBrowseElementFilter() == DaBrowseElementFilter::All)           dwGetBrowseElementFilter = OPC_BROWSE_FILTER_ALL;
            else if (m_Filters.GetBrowseElementFilter() == DaBrowseElementFilter::Branches) dwGetBrowseElementFilter = OPC_BROWSE_FILTER_BRANCHES;
            else                                                  dwGetBrowseElementFilter = OPC_BROWSE_FILTER_ITEMS;

            if (m_pIOPCBrowse) {
                //
                // OPC 3.0 SAS
                //

                HRESULT hr = m_pIOPCBrowse->GetProperties(
                    1,
                    &sItemName,
                    m_Filters.GetReturnPropertyValues() ? TRUE : FALSE,
                    dwPropertyCount,
                    adwPropertyIDs,
                    &pProperties);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
            }
            else
            {
                //
                // OPC 2.0 SAS
                //
                OPCITEMPROPERTIES Properties;

                res = GetProperties2(sItemName, true, m_Filters.GetReturnPropertyValues(), &Properties);
                pProperties = &Properties;
            }
            if (res.IsNotGood()) return "";

            // Get the Property value
            for (DWORD z = 0; z < pProperties->dwNumProperties; z++) {
                if (pProperties->pItemProperties[z].dwPropertyID == dwPropertyId)
                {
                    DaItemProperty prop(&pProperties->pItemProperties[z]);
                    ReleaseOPCITEMPROPERTIES(pProperties);
                    return prop.GetValueAsText();
                }
            }

            ReleaseOPCITEMPROPERTIES(pProperties);
            return "";
        }

        DaItemProperties& DaBrowserImpl::GetProperties(const string& sItemID)
        {
            USES_CONVERSION;
            Technosoftware::Base::Status res;

            m_ItemProperties.clear();

            DWORD             dwPropertyCount = 0;                            // Dummy
            DWORD             adwPropertyIDs[1] = { OPC_PROPERTY_DATATYPE };  // Dummy

            DWORD             dwElementCount = 0;
            OPCBROWSEELEMENT* pBrowseElements = NULL;
            OPCBROWSEFILTER   dwGetBrowseElementFilter;
            OPCITEMPROPERTIES* pProperties;
            LPWSTR sItemName = A2W(sItemID.c_str());

            // Map the Element Filter
            if (m_Filters.GetBrowseElementFilter() == DaBrowseElementFilter::All)           dwGetBrowseElementFilter = OPC_BROWSE_FILTER_ALL;
            else if (m_Filters.GetBrowseElementFilter() == DaBrowseElementFilter::Branches) dwGetBrowseElementFilter = OPC_BROWSE_FILTER_BRANCHES;
            else                                                  dwGetBrowseElementFilter = OPC_BROWSE_FILTER_ITEMS;

            if (m_pIOPCBrowse) {
                //
                // OPC 3.0 SAS
                //

                HRESULT hr = m_pIOPCBrowse->GetProperties(
                    1,
                    &sItemName,
                    m_Filters.GetReturnPropertyValues() ? TRUE : FALSE,
                    dwPropertyCount,
                    adwPropertyIDs,
                    &pProperties);

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
            }
            else
            {
                //
                // OPC 2.0 SAS
                //
                OPCITEMPROPERTIES Properties;

                res = GetProperties2(sItemName, true, m_Filters.GetReturnPropertyValues(), &Properties);
                pProperties = &Properties;
            }
            if (res.IsNotGood()) return m_ItemProperties;

            // Add the available Properties
            for (DWORD z = 0; z < pProperties->dwNumProperties; z++) {
                DaItemProperty prop(&pProperties->pItemProperties[z]);
                m_ItemProperties.push_back(prop);
            }

            ReleaseOPCITEMPROPERTIES(pProperties);
            return m_ItemProperties;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // BrowseHierarchical2
        // -------------------
        //    Browsing of a OPC 2.0 hierarchical SAS.
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    Technosoftware::Base::Status DaBrowserImpl::BrowseHierarchical2( const DaBrowseElementFilter& eGetBrowseElementFilter, const string& sPosition ) throw ()
         *
         * @brief    Browse hierarchical 2.
         *
         * @param    eGetBrowseElementFilter    A filter specifying the browse element.
         * @param    sPosition                The position.
         *
         * @return    An Technosoftware::Base::Status.
         */

        Technosoftware::Base::Status DaBrowserImpl::BrowseHierarchical2(const DaBrowseElementFilter& eGetBrowseElementFilter, const string& sPosition) throw ()
        {
            Technosoftware::Base::Status res;

            if (eGetBrowseElementFilter == DaBrowseElementFilter::All) {
                res = BrowseHierarchical2(DaBrowseElementFilter::Branches, sPosition);
                if (res.IsGood()) {
                    res = BrowseHierarchical2(DaBrowseElementFilter::Items, sPosition);
                }
            }
            else {
                USES_CONVERSION;
                HRESULT        hr;
                LPENUMSTRING   pIEnumString;

                // Change position to the branch to be browsing
                hr = m_pIOPCBrowseSAS->ChangeBrowsePosition(
                    OPC_BROWSE_TO,
                    A2W(sPosition.c_str()));
                if (hr == E_FAIL) {
                    hr = OPC_E_UNKNOWNITEMID;              // Use the same error code like OPC 3.0 Servers
                }
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (res.IsNotGood()) return res;

                // Browse the current position
                if (eGetBrowseElementFilter == DaBrowseElementFilter::Items) {
                    hr = m_pIOPCBrowseSAS->BrowseOPCItemIDs(
                        OPC_LEAF,
                        A2W(m_Filters.GetElementNameFilter().c_str()),
                        m_Filters.GetDataTypeFilter(),
                        m_Filters.GetAccessRightsFilter(),
                        &pIEnumString);
                }
                else {
                    // Ignore all filters if branches are browsed
                    hr = m_pIOPCBrowseSAS->BrowseOPCItemIDs(
                        OPC_BRANCH,
                        L"",
                        VT_EMPTY,
                        0,
                        &pIEnumString);
                }

                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
                if (res.IsNotGood()) return res;

                res = AddElementsFromIEnumString(pIEnumString, true, eGetBrowseElementFilter == DaBrowseElementFilter::Items ? true : false);
            }
            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // GetProperties2
        // --------------
        //    Returns the Properties of the specified Item in a OPCITEMPROPERTIES Structure (OPC 3.0) from an OPC 2.0 Server.
        //    The IOPCItemProperties functions QueryAvailableProperties(), LookupItemIDs() and GetItemProperties() are used.
        //----------------------------------------------------------------------------------------------------------------------
        Technosoftware::Base::Status DaBrowserImpl::GetProperties2(LPWSTR szItemID, bool fIsItem, bool fWithValue, OPCITEMPROPERTIES* pProperties) throw ()
        {
            Technosoftware::Base::Status res;

            DWORD*      pPropertyIDs = NULL;
            LPWSTR*     pDescriptions = NULL;
            VARTYPE*    pvtDataTypes = NULL;
            HRESULT*    pErrItemIDs = NULL;
            LPWSTR*     pItemIDs = NULL;
            HRESULT*    pErrData = NULL;
            LPVARIANT   pData = NULL;

            try {
                memset(pProperties, 0, sizeof(OPCITEMPROPERTIES));

                HRESULT hr = m_pIOPCItemProperties->QueryAvailableProperties(
                    szItemID,
                    &pProperties->dwNumProperties,
                    &pPropertyIDs,
                    &pDescriptions,
                    &pvtDataTypes);

                if (hr == OPC_E_UNKNOWNITEMID && !fIsItem) {
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);               // Some servers returns this code if szItemID specifies a Branch
                }
                if (pProperties->dwNumProperties == 0) {
                    return Technosoftware::DaAeHdaClient::GetStatusFromHResult(S_OK);
                }

                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));

                hr = m_pIOPCItemProperties->LookupItemIDs(
                    szItemID,
                    pProperties->dwNumProperties,
                    pPropertyIDs,
                    &pItemIDs,
                    &pErrItemIDs);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall)));

                if (fWithValue) {
                    hr = m_pIOPCItemProperties->GetItemProperties(
                        szItemID,
                        pProperties->dwNumProperties,
                        pPropertyIDs,
                        &pData,
                        &pErrData);
                    if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));
                }

                // Allocate memory for all Properties of this Item
                pProperties->pItemProperties = (OPCITEMPROPERTY*)CoTaskMemAlloc(pProperties->dwNumProperties * sizeof(OPCITEMPROPERTY));
                if (!pProperties->pItemProperties) throw Technosoftware::Base::OutOfMemoryException();

                // Initialize all properties with the result of
                // QueryAvailableProperties(), LookupItemIDs() and GetItemProperties()
                for (DWORD i = 0; i < pProperties->dwNumProperties; i++) {
                    OPCITEMPROPERTY* pProp = &pProperties->pItemProperties[i];

                    pProp->dwPropertyID = pPropertyIDs[i];   // The Property ID is always set
                    pProp->hrErrorID = S_OK;

                    //
                    // LookupItemIDs() result
                    //
                    // OPC_E_INVALID_PID is the result code for PropertyIDs of Set1 so we don't handle
                    // it as error because the IDs are passed with function LookupItemIDs.
                    //
                    if (pErrItemIDs[i] == OPC_E_INVALID_PID && pPropertyIDs[i] < OPC_PROPERTY_EU_UNITS) {
                        pErrItemIDs[i] = E_FAIL;
                    }
                    // E_FAIL means there is no corresponig ItemID so it can be ignored
                    if (FAILED(pErrItemIDs[i]) && pErrItemIDs[i] != E_FAIL) {
                        pProp->hrErrorID = pErrItemIDs[i];
                    }

                    //
                    // optional GetItemProperties() result
                    //
                    if (fWithValue && FAILED(pErrData[i])) {

                        pProp->hrErrorID = pErrData[i];
                    }

                    if (FAILED(pProp->hrErrorID)) {         // Release the members of this Property because ReleaseOPCITEMPROPERTIES() 
                        m_pIMalloc->Free(pDescriptions[i]);  // releases it only if hrErrorID is an error free value
                        m_pIMalloc->Free(pItemIDs[i]);
                        if (fWithValue) {                      // Value is optional
                            VariantClear(&pData[i]);
                        }
                        continue;                              // Do not set other the other property members
                    }

                    if (fWithValue) {
                        pProp->vValue = pData[i];              // vValue takes ownership of VARIANT memory
                    }
                    else {
                        VariantInit(&pProp->vValue);
                    }

                    pProp->vtDataType = pvtDataTypes[i];
                    pProp->wReserved = 0;
                    pProp->szDescription = pDescriptions[i];  // szDescription takes ownership of string memory        

                    // Note: Some server returns pErrItemIDs[i] = S_OK but
                    //       nevertheless pItemIDs[i] is a NULL pointer.
                    //       The pointer is checked in DaItemProperty c'tor
                    pProp->szItemID = pItemIDs[i];            // szItemID takes ownership of string memory
                }
            }
            catch (Technosoftware::Base::Status e) {
                res = e;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            // Cleanup in case of error
            if (res.IsNotGood()) {
                for (DWORD i = 0; i < pProperties->dwNumProperties; i++) {
                    if (pDescriptions)   m_pIMalloc->Free(pDescriptions[i]);
                    if (pData)           VariantClear(&pData[i]);
                    if (pItemIDs) { if (pItemIDs[i]) m_pIMalloc->Free(pItemIDs[i]); }
                }
                if (pProperties->pItemProperties) {
                    m_pIMalloc->Free(pProperties->pItemProperties);
                }
                // Revoke ownership of memory
                memset(pProperties, 0, sizeof(OPCITEMPROPERTIES));
            }

            // Common cleanup in any case
            if (pPropertyIDs)    m_pIMalloc->Free(pPropertyIDs);
            if (pvtDataTypes)    m_pIMalloc->Free(pvtDataTypes);
            if (pDescriptions)   m_pIMalloc->Free(pDescriptions);
            if (pErrItemIDs)     m_pIMalloc->Free(pErrItemIDs);
            if (pItemIDs)        m_pIMalloc->Free(pItemIDs);
            if (pData)           m_pIMalloc->Free(pData);
            if (pErrData)        m_pIMalloc->Free(pErrData);

            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // AddElementsFromIEnumString
        // --------------------------
        //    Creates and adds 'Browse Elements' from the specified string enumeration object. Also the OPC 3.0 SAS Filters
        //    are used. After all is done the string enumeration object will be released.
        //
        // parameters:
        //    pIEnumString            The string enumerator object
        //    fGetFullyQualifiedID    If 'true' then the fully qualified ItemID will be retrieved for each Item Name in the
        //                            enumeration object. Otherwise the enumeration object already contains the fully qualified
        //                            ItemIDs (e.g. if the SAS is flat).
        //    fIsItem                 If 'true' the enumeration object contains ItemIDs, otherwise it contains 'Branch' names.
        //
        // modified data members:
        //    m_Elements
        //    m_fMoreElements 
        //----------------------------------------------------------------------------------------------------------------------
#ifdef __BORLANDC__
        Technosoftware::Base::Status DaBrowserImpl::AddElementsFromIEnumString(LPENUMSTRING pIEnumString, bool fGetFullyQualifiedID, bool fIsItem)
#else

/**
 * @fn    Technosoftware::Base::Status DaBrowserImpl::AddElementsFromIEnumString( LPENUMSTRING pIEnumString, bool fGetFullyQualifiedID, bool fIsItem ) throw () #endif
 *
 * @brief    Adds the elements from i enum string.
 *
 * @exception    res    Thrown when a resource error condition occurs.
 * @exception    e      Thrown when an e error condition occurs.
 *
 * @param    pIEnumString            The i enum string.
 * @param    fGetFullyQualifiedID    true to get fully qualified identifier.
 * @param    fIsItem                    true if this object is item.
 *
 * @return    An Technosoftware::Base::Status.
 */

        Technosoftware::Base::Status DaBrowserImpl::AddElementsFromIEnumString(LPENUMSTRING pIEnumString, bool fGetFullyQualifiedID, bool fIsItem) throw ()
#endif
        {
            const DWORD RECSIZE_NEXT = 10;

            Technosoftware::Base::Status res;
            LPOLESTR    apOleStrings[RECSIZE_NEXT];
            ULONG       ul = 0, ulNum = 0;
            LPWSTR      pItemID = NULL;
            DWORD       dwAddedElements = 0;

            try {
                HRESULT hr = pIEnumString->Reset();       // Resets the enumeration sequence to the beginning 
                while (hr == S_OK) {
                    // Read array of strings
                    hr = pIEnumString->Next(RECSIZE_NEXT, apOleStrings, &ulNum);

                    for (ul = 0; ul < ulNum; ul++) {
                        USES_CONVERSION;

                        bool fAddThisElementElement = true;

                        // Use OPC 3.0 SAS Filters
                        if (m_Filters.GetMaxElementsReturned() && dwAddedElements >= m_Filters.GetMaxElementsReturned()) {
                            fAddThisElementElement = false;
                            m_fMoreElements = TRUE;
                        }
                        if (fAddThisElementElement && m_Filters.GetElementNameFilter().length() > 0) {
                            fAddThisElementElement = MatchPattern(
                                apOleStrings[ul],
                                A2CW(m_Filters.GetElementNameFilter().c_str())
                            ) ? true : false;
                        }

                        if (fAddThisElementElement) {
                            if (fGetFullyQualifiedID) {      // The fully qualified ItemID is required
                                hr = m_pIOPCBrowseSAS->GetItemID(apOleStrings[ul], &pItemID);
                                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));

                                OPCITEMPROPERTIES Properties;
                                res = GetProperties2(pItemID, fIsItem, m_Filters.GetReturnPropertyValues(), &Properties);
                                if (res.IsNotGood()) throw res;

                                try {
                                    DaBrowseElement el(OLE2A(apOleStrings[ul]), OLE2A(pItemID), fIsItem, &Properties);
                                    ReleaseOPCITEMPROPERTIES(&Properties);
                                    m_Elements.push_back(el);
                                }
                                catch (Technosoftware::Base::Status e) {
                                    ReleaseOPCITEMPROPERTIES(&Properties);
                                    throw e;
                                }

                                m_pIMalloc->Free(pItemID);
                                pItemID = NULL;
                            }
                            else {
                                // The Name is identically with the fully qualified ItemID
                                OPCITEMPROPERTIES Properties;
                                res = GetProperties2(apOleStrings[ul], true, m_Filters.GetReturnPropertyValues(), &Properties);
                                if (res.IsNotGood()) throw res;

                                try {
                                    DaBrowseElement el(OLE2A(apOleStrings[ul]), &Properties);
                                    ReleaseOPCITEMPROPERTIES(&Properties);
                                    m_Elements.push_back(el);
                                }
                                catch (Technosoftware::Base::Status e) {
                                    ReleaseOPCITEMPROPERTIES(&Properties);
                                    throw e;
                                }
                            }
                            // The client must free the returned string
                            m_pIMalloc->Free(apOleStrings[ul]);
                            dwAddedElements++;               // Successfully added element
                        }
                        else {                              // There are more elements than requested
                            for (; ul < ulNum; ul++) {
                                m_pIMalloc->Free(apOleStrings[ul]);
                            }
                            hr = S_FALSE;
                            break;
                        }
                    }
                } // while not all strings read
            }
            catch (Technosoftware::Base::Status e) {
                // Map the exception objject to an Technosoftware::Base::Status object
                res = e;
            }
            catch (...) {
                res = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_FAIL);
            }

            // Release all not yet released memory in case of +error
            if (res.IsNotGood()) {
                for (; ul < ulNum; ul++) {
                    m_pIMalloc->Free(apOleStrings[ul]);
                }
                if (pItemID) {
                    m_pIMalloc->Free(pItemID);
                }
                // Release all previously successfully added elements
                m_Elements.clear();
            }
            pIEnumString->Release();
            return res;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // ReleaseOPCITEMPROPERTIES
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    void DaBrowserImpl::ReleaseOPCITEMPROPERTIES( OPCITEMPROPERTIES* pProperties )
         *
         * @brief    Releases the opcitemproperties described by pProperties.
         *
         * @param [in,out]    pProperties    If non-null, the properties.
         */

        void DaBrowserImpl::ReleaseOPCITEMPROPERTIES(OPCITEMPROPERTIES* pProperties)
        {
            if (SUCCEEDED(pProperties->hrErrorID)) {
                for (DWORD z = 0; z < pProperties->dwNumProperties; z++) {
                    OPCITEMPROPERTY* pProp = &pProperties->pItemProperties[z];
                    if (SUCCEEDED(pProp->hrErrorID)) {
                        if (&pProp->vValue != NULL)
                        {
                            VariantClear(&pProp->vValue);
                        }
                        if (pProp->szDescription != NULL)
                        {
                            m_pIMalloc->Free(pProp->szDescription);
                        }
                        if (pProp->szItemID != NULL)
                        {
                            m_pIMalloc->Free(pProp->szItemID);
                        }
                    }
                }
                m_pIMalloc->Free(pProperties->pItemProperties);
            }
            /* The following code is not required because the properties are always a normal variable */
            //m_pIMalloc->Free( pProperties );
        }
    }
}