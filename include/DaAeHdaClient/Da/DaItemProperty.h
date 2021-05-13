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

#ifndef TECHNOSOFTWARE_DAITEMPROPERTY_H
#define TECHNOSOFTWARE_DAITEMPROPERTY_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "Base/Status.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        /**
         * @class   DaItemProperty
         *
         * @brief   Contains all property elements of a single element within the Server Address Space.
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaItemProperty : protected OpcObject
        {
        public:

            /**
             * @fn  DaItemProperty::DaItemProperty() noexcept(false);
             *
             * @brief   Constructs a DaItemProperty object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             */

            DaItemProperty() noexcept(false);

            /**
             * @fn  DaItemProperty::DaItemProperty(const DaItemProperty& itemProperty) noexcept(false);
             *
             * @brief   Constructs a DaItemProperty object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param   itemProperty    Constructs a copy of an existing DaItemProperty object.
             */

            DaItemProperty(const DaItemProperty& itemProperty) noexcept(false);

            /**
             * @fn  DaItemProperty::DaItemProperty(void* itemProperty) noexcept(false);
             *
             * @brief   Constructor.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param [in,out]  itemProperty    If non-null, the item property.
             */

            explicit DaItemProperty(void* itemProperty) noexcept(false);

            /**
             * @fn  virtual DaItemProperty::~DaItemProperty() throw ();
             *
             * @brief   Destroys the object.
             */

            virtual ~DaItemProperty() noexcept;
        protected:

        public:

            /**
             * @fn  uint32_t DaItemProperty::GetId() const throw ()
             *
             * @brief   The property identifier.
             *
             * @return  An uint32_t.
             */

			uint32_t GetId() const noexcept { return itemPropertyId_; }

            /**
             * @fn  const string& DaItemProperty::GetDescription() const noexcept
             *
             * @brief   A short description of the property.
             *
             * @return  A string&amp;
             */

            const string& GetDescription() const noexcept { return description_; }

            /**
             * @fn  uint16_t DaItemProperty::GetDataType() const noexcept
             *
             * @brief   The canonical data type of the property.
             *
             * @return  An uint16_t.
             */

            uint16_t GetDataType() const noexcept { return dataType_; }

            /**
             * @fn  LPVARIANT DaItemProperty::GetValue() noexcept
             *
             * @brief   The value of the property. If values were not requested then vValue is of type
             *          VT_EMPTY.
             *
             * @return  A LPVARIANT.
             */

            LPVARIANT GetValue() noexcept { return &value_; }

            /**
             * @fn  const string& DaItemProperty::GetItemId() const noexcept
             *
             * @brief   A fully qualified ItemID that can be used to access this property or an empty string
             *          if this property cannot be accessed via an DaItem object.
             *
             * @return  A string&amp;
             */

            const string& GetItemId() const noexcept { return itemId_; }

            /**
             * @fn  Base::Status DaItemProperty::GetResult() const
             *
             * @brief   Specifies the validity of the other attributes.
             *          
             *          Description(), DataType(), Value() and ItemID() are only valid if the result is OK;
             *          otherwise only ID() will contain a valid value.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Base::Status GetResult() const { return result_; }

        public:

            /**
             * @fn  string DaItemProperty::GetDataTypeAsText(OpcTextMode textMode = Capitalize);
             *
             * @brief   Returns the Data Type as text string.
             *
             * @param   textMode   (Optional) = Capitalize.
             *
             * @return  A string.
             */

            string GetDataTypeAsText(OpcTextMode textMode = OpcTextMode::Capitalize);

            /**
             * @fn  string DaItemProperty::GetValueAsText();
             *
             * @brief   Returns the Value as text string.
             *
             * @return  A string.
             */

            string GetValueAsText();

        public:

            /**
             * @fn  DaItemProperty& DaItemProperty::operator=(const DaItemProperty& itemProperty) noexcept(false);
             *
             * @brief   Assigns an existing DaItemProperty object to another.
             *
             * @exception   Base::Exception                 Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             * @exception   e                               Thrown when an e error condition occurs.
             *
             * @param   itemProperty    The property.
             *
             * @return  A shallow copy of this object.
             */

            DaItemProperty& operator =(const DaItemProperty& itemProperty) noexcept(false);

        protected:
            friend class DaBrowseElement;
            uint32_t                    itemPropertyId_;
            string                      description_;
            uint16_t                    dataType_;
            VARIANT                     value_{};
            string                      itemId_;
            Base::Status                result_;
        };
    }
}

#endif /* TECHNOSOFTWARE_DAITEMPROPERTY_H */
