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

#ifndef TECHNOSOFTWARE_DABROWSER_H
#define TECHNOSOFTWARE_DABROWSER_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "DaCommon.h"
#include "DaItemProperty.h"
#include "Base/Status.h"
#include <vector>

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class DaServer;
        class DaBrowserImpl;

        /**
         * @enum    DaBrowseElementFilter
         *
         * @brief   Specifies which type of Server Address Space elements are returned by function DaBrowser::Browse().
         *
         * @ingroup  DAClient
         */

        enum class DaBrowseElementFilter {

            /**
             * @brief    All type of elements are returned.
             */
            All,

            /**
             * @brief    Only elements with children elements are returned.
             */

            Branches,

            /**
             * @brief    Only elements with children elements are returned.
             */

            Items
        };

        /**
         * @class   DaBrowseFilters
         *
         * @brief   Defines the filters which are used if the Server Address Space is browsed.
         *          
         *          If the constructor is used with no arguments then an empty filter object with no
         *          filters is created and the function DaBrowser::Browse() returns all available
         *          elements from the current position.
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaBrowseFilters : protected OpcObject
        {
        public:

            /**
             * @fn  DaBrowseFilters::DaBrowseFilters(DaBrowseElementFilter browseElementFilter = DaBrowseElementFilter::All, const string& elementNameFilter = "", const string& vendorFilter = "", uint32_t maxElementsReturned = 0, bool returnAllProperties = false, bool returnPropertyValues = false, VARTYPE dataTypeFilter = VT_EMPTY, uint32_t accessRightsFilter = OPC_READABLE + OPC_WRITEABLE) noexcept(false);
             *
             * @brief   Constructs a DaBrowseFilters object.
             *          
             *          No other object takes the ownership of this filter object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param   browseElementFilter     (Optional) Specifies which type of elements are returned.
             * @param   elementNameFilter       (Optional) Specifies the text string which will be used to
             *                                  filter the element names. This text string may contain wildcard
             *                                  characters that conforms to the LIKE operator from Visual Basic.
             *                                  An empty text strings turns this filter off.
             * @param   vendorFilter            (Optional) Specifies the text string which will be used for
             *                                  vendor specific filtering. An empty text strings turns this
             *                                  filter off. This filter is only used if the OPC 3.0 Browse
             *                                  functions are used, means DaBrowser::IsBrowse3Used() returns true.
             * @param   maxElementsReturned     (Optional) Specifies the maximum number of elements returned
             *                                  by the server. A value 0 turns this filter off.
             *                                  - For OPC 2.0 Browse functions\n
             *                                  If there are more than maxElementsReturned elements
             *                                  DaBrowser::HasMoreElements() returns true. Note that continuation
             *                                  points are not supported and therefore DaBrowser::BrowseNext()
             *                                  always returns with a success result code and the element list
             *                                  contains no elements.\n\n
             *                                  - For OPC 3.0 Browse functions\n
             *                                  If the server supports continuation points then the next elements
             *                                  can be obtained with function DaBrowser::BrowseNext(). If the
             *                                  server does not support continuation points and more than
             *                                  maxElementsReturned elements are available then the behavior is
             *                                  as if OPC 2.0 Browse functions are used.
             * @param   returnAllProperties     (Optional) Specifies if each returned single element contains
             *                                  all available properties.
             * @param   returnPropertyValues    (Optional) Specifies if the returned properties contains the
             *                                  property value too. This value is ignored if parameter
             *                                  returnAllProperties is false.
             * @param   dataTypeFilter          (Optional) Specifies the data type filter. All elements which
             *                                  match this data type are returned. The data type VT_EMPTY turns
             *                                  this filter off. This filter is only used if the OPC 2.0 Browse
             *                                  functions are used, means DaBrowser::IsBrowse2Used returns true.
             * @param   accessRightsFilter      (Optional) Specifies the access rights filter. All elements
             *                                  which match this access rights are returned. This filter is only
             *                                  used if the OPC 2.0 Browse functions are used, means
             *                                  DaBrowser::IsBrowse2Used()
             *                                  returns true. Possible access rights filter values:
             *                                     - OPC_READABLE                   readable items are returned
             *                                     - OPC_WRITEABLE                  writeable items are returned
             *                                     - OPC_READABLE + OPC_WRITEABLE   this filter is off
             *                                     - 0                              this filter is off.
             */

            DaBrowseFilters(DaBrowseElementFilter browseElementFilter = DaBrowseElementFilter::All,
                const string& elementNameFilter = "",
                const string& vendorFilter = "",
                uint32_t maxElementsReturned = 0,
                bool returnAllProperties = false,
                bool returnPropertyValues = false,
                VARTYPE dataTypeFilter = VT_EMPTY,
                uint32_t accessRightsFilter = OPC_READABLE + OPC_WRITEABLE) noexcept(false);

            /**
             * @fn  DaBrowseFilters::DaBrowseFilters(OpcObject* parent, DaBrowseElementFilter browseElementFilter = DaBrowseElementFilter::All, const string& elementNameFilter = "", const string& vendorFilter = "", uint32_t maxElementsReturned = 0, bool returnAllProperties = false, bool returnPropertyValues = false, VARTYPE dataTypeFilter = VT_EMPTY, uint32_t accessRightsFilter = OPC_READABLE + OPC_WRITEABLE) noexcept(false);
             *
             * @brief   Constructs a DaBrowseFilters object.
             *          
             *            The object which takes the ownership of this filter object can be specified.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param [in,out]  parent                  Address of a DaServer object which takes the
             *                                          ownership of this filter object.
             * @param           browseElementFilter     (Optional) Specifies which type of elements are
             *                                          returned.
             * @param           elementNameFilter       (Optional) Specifies the text string which will be
             *                                          used to filter the element names. This text string may
             *                                          contain wildcard characters that conforms to the LIKE
             *                                          operator from Visual Basic. An empty text strings turns
             *                                          this filter off.
             * @param           vendorFilter            (Optional) Specifies the text string which will be
             *                                          used for vendor specific filtering. An empty text strings
             *                                          turns this filter off. This filter is only used if the
             *                                          OPC 3.0 Browse functions are used, means
             *                                          DaBrowser::IsBrowse3Used() returns true.
             * @param           maxElementsReturned     (Optional) Specifies the maximum number of elements
             *                                          returned by the server. A value 0 turns this filter off.
             *                                          - For OPC 2.0 Browse functions\n
             *                                          If there are more than maxElementsReturned elements
             *                                          DaBrowser::HasMoreElements() returns true. Note that
             *                                          continuation points are not supported and therefore
             *                                          DaBrowser::BrowseNext() always returns with a success
             *                                          result code and the element list contains no elements.\n\n
             *                                          - For OPC 3.0 Browse functions\n
             *                                          If the server supports continuation points then the next
             *                                          elements can be obtained with function
             *                                          DaBrowser::BrowseNext(). If the server does not support
             *                                          continuation points and more than maxElementsReturned
             *                                          elements are available then the behavior is as if OPC 2.0
             *                                          Browse functions are used.
             * @param           returnAllProperties     (Optional) Specifies if each returned single element
             *                                          contains all available properties.
             * @param           returnPropertyValues    (Optional) Specifies if the returned properties
             *                                          contains the property value too. This value is ignored if
             *                                          parameter returnAllProperties is false.
             * @param           dataTypeFilter          (Optional) Specifies the data type filter. All
             *                                          elements which match this data type are returned. The
             *                                          data type VT_EMPTY turns this filter off. This filter is
             *                                          only used if the OPC 2.0 Browse functions are used, means
             *                                          DaBrowser::IsBrowse2Used returns true.
             * @param           accessRightsFilter      (Optional) Specifies the access rights filter. All
             *                                          elements which match this access rights are returned.
             *                                          This filter is only used if the OPC 2.0 Browse functions
             *                                          are used, means DaBrowser::IsBrowse2Used()
             *                                          returns true. Possible access rights filter values:
             *                                            - OPC_READABLE                   readable items are
             *                                            returned
             *                                            - OPC_WRITEABLE                  writeable items are
             *                                            returned
             *                                            - OPC_READABLE + OPC_WRITEABLE   this filter is off
             *                                            - 0                              this filter is off.
             */

            DaBrowseFilters(OpcObject* parent,
                DaBrowseElementFilter browseElementFilter = DaBrowseElementFilter::All,
                const string& elementNameFilter = "",
                const string& vendorFilter = "",
                uint32_t maxElementsReturned = 0,
                bool returnAllProperties = false,
                bool returnPropertyValues = false,
                VARTYPE dataTypeFilter = VT_EMPTY,
                uint32_t accessRightsFilter = OPC_READABLE + OPC_WRITEABLE) noexcept(false);

            /**
             * @fn  DaBrowseFilters::~DaBrowseFilters() throw ();
             *
             * @brief   Destroys a DaBrowseFilters object.
             */

            ~DaBrowseFilters() noexcept;

        public:

            /**
             * @fn  DaBrowseElementFilter DaBrowseFilters::GetBrowseElementFilter() const noexcept
             *
             * @brief   The element type filter.
             *
             * @return  A DaBrowseElementFilter.
             */

            DaBrowseElementFilter GetBrowseElementFilter() const noexcept { return browseElementFilter_; }

            /**
             * @fn  const string& DaBrowseFilters::GetElementNameFilter() const noexcept
             *
             * @brief   The element name filter.
             *
             * @return  A string&amp;
             */

            const string& GetElementNameFilter() const noexcept { return elementNameFilter_; }

            /**
             * @fn  const string& DaBrowseFilters::GetVendorFilter() const noexcept
             *
             * @brief   The vendor specific filter.
             *
             * @return  A string&amp;
             */

            const string& GetVendorFilter() const noexcept { return vendorFilter_; }

            /**
             * @fn  inline bool DaBrowseFilters::IsReturnAllProperties() const noexcept
             *
             * @brief   The filter which specifies if the available properties should be returned.
             *
             * @return  true if it succeeds, false if it fails.
             */

            inline bool IsReturnAllProperties() const noexcept { return returnAllProperties_; }

            /**
             * @fn  inline bool DaBrowseFilters::GetReturnPropertyValues() const throw ()
             *
             * @brief   The filter which specifies if the values of all available properties should be
             *          returned.
             *
             * @return  true if it succeeds, false if it fails.
             */

            inline bool GetReturnPropertyValues() const noexcept { return returnPropertyValues_; }

            /**
             * @fn  inline uint32_t DaBrowseFilters::GetMaxElementsReturned() const noexcept
             *
             * @brief   The maximum number of returned elements.
             *
             * @return  An uint32_t.
             */

            inline uint32_t GetMaxElementsReturned() const noexcept { return mDwMaxElementsReturned_; }

            /**
             * @fn  inline VARTYPE DaBrowseFilters::GetDataTypeFilter() const throw ()
             *
             * @brief   The data type filter.
             *
             * @return  A VARTYPE.
             */

            inline VARTYPE GetDataTypeFilter() const noexcept { return dataTypeFilter_; }

            /**
             * @fn  inline uint32_t DaBrowseFilters::GetAccessRightsFilter() const throw ()
             *
             * @brief   The access rights filter.
             *
             * @return  An uint32_t.
             */

            inline uint32_t GetAccessRightsFilter() const noexcept { return accessRightsFilter_; }

        public:

            /**
             * @fn  DaBrowseFilters& DaBrowseFilters::operator=(const DaBrowseFilters& Filters) noexcept(false);
             *
             * @brief   Assigns an existing DaBrowseFilters object to another.
             *
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param   Filters The filters.
             *
             * @return  A shallow copy of this object.
             */

            DaBrowseFilters& operator =(const DaBrowseFilters& Filters) noexcept(false);

        protected:
            DaBrowseElementFilter       browseElementFilter_;
            string                      elementNameFilter_;
            string                      vendorFilter_;
            uint32_t                    mDwMaxElementsReturned_;
            bool                        returnAllProperties_;
            bool                        returnPropertyValues_;
            VARTYPE                     dataTypeFilter_;
            uint32_t                    accessRightsFilter_;
        };


        typedef vector<DaItemProperty> DaItemProperties;

        /**
         * @class   DaBrowseElement
         *
         * @brief   Represents a single element within the Server Address Space.
         *          
         *          The type of the element is specified by IsItem() and HasChildren().
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaBrowseElement : protected OpcObject
        {
        public:

            /**
             * @fn  DaBrowseElement::DaBrowseElement(const DaBrowseElement& BrowseElement) noexcept(false);
             *
             * @brief   Constructs a DaBrowseElement object.
             *          
             *          This is the only public constructor. All other constructors are declared as protected
             *          member functions an can be used only by ClientSdk classes.
             *
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param   BrowseElement   The browse element.
             */

            DaBrowseElement(const DaBrowseElement& BrowseElement) noexcept(false);

            /**
             * @fn  DaBrowseElement::~DaBrowseElement() throw ();
             *
             * @brief   Destroys a DaBrowseElement object.
             */

            ~DaBrowseElement() noexcept;

        protected:
            friend class DaBrowserImpl;

            /**
             * @fn  DaBrowseElement::DaBrowseElement(LPVOID pOPCBROWSEELEMENT) noexcept(false);
             *
             * @brief   Constructor
             *
             * @param   pOPCBROWSEELEMENT   The opcbrowseelement.
             */

            DaBrowseElement(LPVOID pOPCBROWSEELEMENT) noexcept(false);

            /**
             * @fn  DaBrowseElement::DaBrowseElement(const char* pszName, LPVOID pOPCITEMPROPERTIES) noexcept(false);
             *
             * @brief   Constructor
             *
             * @param   pszName             The name.
             * @param   pOPCITEMPROPERTIES  The opcitemproperties.
             */

            DaBrowseElement(const char* pszName, LPVOID pOPCITEMPROPERTIES) noexcept(false);

            /**
             * @fn  DaBrowseElement::DaBrowseElement(const char* name, const char* itemId, bool isItem, LPVOID itemProperties) noexcept(false);
             *
             * @brief   Constructor
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             *
             * @param   name            The name.
             * @param   itemId          Identifier for the item.
             * @param   isItem          True if element is an item.
             * @param   itemProperties  The opcitemproperties.
             */

            DaBrowseElement(const char* name, const char* itemId, bool isItem, LPVOID itemProperties) noexcept(false);

        public:

            /**
             * @fn  inline const string& DaBrowseElement::GetName() const noexcept
             *
             * @brief   A short user friendly name of the element.
             *          
             *          E.g. this name can be used to display the element in a tree control.
             *
             * @return  A string&amp;
             */

            inline const string& GetName() const noexcept { return name_; }

            /**
             * @fn    inline const string& DaBrowseElement::GetItemId() const throw ()
             *
             * @brief    The unique identifier of the element.
             *             
             *           If HasChildren() is true then this identifier can be used as start position for
             *           further DaBrowser::Browse() calls. If IsItem() is true then this identifier can be
             *           used to add an item to a group object.
             *
             * @return    A string&amp;
             */

            inline const string& GetItemId() const noexcept { return itemId_; }

            /**
             * @fn  bool DaBrowseElement::IsItem() const noexcept;
             *
             * @brief   Indicates if the element is an item element.
             *          
             *          If this function returns true then ItemID() can be used to add an item to a group
             *          object. Note, that an element can be an item and have children.
             *
             * @return  true if item, false if not.
             */

            bool IsItem() const noexcept;

            /**
             * @fn  bool DaBrowseElement::HasChildren() const throw();
             *
             * @brief   Indicates if the element has children elements.
             *          
             *          If this function returns true then ItemID() can be used as start position for further
             *          DaBrowser::Browse() calls. Note, that an element can be an item and have children.
             *
             * @return  true if children, false if not.
             */

            bool HasChildren() const noexcept;

            /**
             * @fn  DaItemProperties& DaBrowseElement::GetProperties() throw ()
             *
             * @brief   The set of properties of the element.
             *
             * @return  A DaItemProperties&amp;
             */

            DaItemProperties& GetProperties() noexcept { return itemProperties_; }

        public:

            /**
             * @fn  DaBrowseElement& DaBrowseElement::operator=(const DaBrowseElement& browseElement) throw (Technosoftware::Base::Exception);
             *
             * @brief   Assigns an existing DaBrowseElement object to another.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param   browseElement   The browse element.
             *
             * @return  A shallow copy of this object.
             */

            DaBrowseElement& operator =(const DaBrowseElement& browseElement) noexcept(false);

        protected:
            string                name_;
            string                itemId_;
            uint32_t            m_dwFlagValue;
            DaItemProperties    itemProperties_;
        };

        typedef vector<DaBrowseElement> DaBrowseElements;

        /**
         * @class   DaBrowser
         *
         * @brief   The DaBrowser is the ClientSdk class to browse the OPC DA Server Address Space.
         *          
         *          With an instance of this class the entire Server Address Space of the connected OPC
         *          Data Access Server can be browsed and allows access to all elements of it (without
         *          item properties).
         *
         * @ingroup DAClient
         */

        class OPCCLIENTSDK_API DaBrowser : protected OpcObject
        {
        public:

            /**
             * @fn  DaBrowser::DaBrowser(DaServer* parent, DaBrowseFilters* filters = NULL) noexcept(false);
             *
             * @brief   Constructs a DaBrowser object.
             *          
             *          The OPC 3.0 Browse functions are used by this object if supported by the server;
             *          otherwise the OPC 2.0 Browse functions are used.
             *
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param [in,out]  parent  Address of a DaServer object which takes the ownership of this
             *                          browser object.
             * @param [in,out]  filters (Optional) Optional parameter which defines the filters to be used.
             */

            DaBrowser(DaServer* parent, DaBrowseFilters* filters = nullptr) noexcept(false);

            /**
             * @fn  DaBrowser::~DaBrowser() noexcept;
             *
             * @brief   Destroys a DaBrowser object.
             */

            ~DaBrowser() noexcept;

        public:

            /**
             * @fn    DaBrowseElements& DaBrowser::GetElements() const;
             *
             * @brief    Allows the access to the Server Address Space elements returned by the last Browse()
             *             resp. BrowseNext() function call.
             *
             * @return    A DaBrowseElements&amp;
             */

            DaBrowseElements& GetElements() const;

            /**
             * @fn    DaBrowseFilters& DaBrowser::GetFilters() const;
             *
             * @brief    The currently used filters.
             *
             * @return    A DaBrowseFilters&amp;
             */

            DaBrowseFilters& GetFilters() const;

            /**
             * @fn  bool DaBrowser::HasMoreElements() const noexcept;
             *
             * @brief   Indicates if Elements() contains all available elements from the current position or
             *          not.
             *          
             *          This function is required only if the filter 'MaxElementsReturned' is enabled. Refer
             *          to the DaBrowseFilters constructor for additional information and a description of
             *          this filter type.
             *
             * @return  true if more elements, false if not.
             */

            bool HasMoreElements() const noexcept;

            /**
             * @fn  bool DaBrowser::IsBrowse2Used() const noexcept;
             *
             * @brief   Indicates if the browser object uses the OPC 2.0 Browse functions.
             *
             * @return  true if browse 2 used, false if not.
             */

            bool IsBrowse2Used() const noexcept;

            /**
             * @fn  bool DaBrowser::IsBrowse3Used() const noexcept;
             *
             * @brief   Indicates if the browser object uses the OPC 3.0 Browse functions.
             *
             * @return  true if browse 3 used, false if not.
             */

            bool IsBrowse3Used() const noexcept;

            /**
             * @fn  Technosoftware::Base::Status DaBrowser::Browse(const string& position);
             *
             * @brief   Returns all elements from the specified position which matches the filter criteria.
             *          
             *          The returned elements can be accessed via the function member Elements(). If this
             *          function is called then all elements returned by a previous call are removed.
             *
             * @param   position    The position within the Server Address Space which is used as start
             *                      position for the browse operation. This position ist the name of an existing
             *                      element which has children. An empty string represents the root position.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status Browse(const string& position);

            /**
             * @fn  Technosoftware::Base::Status DaBrowser::BrowseNext();
             *
             * @brief   Returns the next elements from the current position.
             *          
             *          This function is required only if the filter 'MaxElementsReturned' is enabled. Refer
             *          to the DaBrowseFilters constructor for additional information and a description of
             *          this filter type.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status BrowseNext();

            /**
             * @fn  Technosoftware::Base::Status DaBrowser::SetFilters(const DaBrowseFilters& filters) noexcept;
             *
             * @brief   Sets new filters.
             *
             * @param   filters The filters which are used by the next Browse() or BrowseNext() function call.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status SetFilters(const DaBrowseFilters& filters) noexcept;

            /**
             * @fn  string DaBrowser::GetPropertyValueAsText(const string& itemId, DWORD propertyId);
             *
             * @brief   Gets property value as text.
             *
             * @param   itemId          Identifier for the item.
             * @param   propertyId    Identifier for the property.
             *
             * @return  The property value as text.
             */

            string GetPropertyValueAsText(const string& itemId, DWORD propertyId);

            /**
             * @fn  DaItemProperties& DaBrowser::GetProperties(const string& itemId) noexcept;
             *
             * @brief   Returns the item properties of the specified item ID.
             *
             * @param   itemId  The full item name to get the item properties for.
             *
             * @return  The properties.
             */

            DaItemProperties& GetProperties(const string& itemId) noexcept;

        protected:
            OpcAutoPtr<DaBrowserImpl> impl_;
        };
    }
}

#endif // TECHNOSOFTWARE_DABROWSER_H
