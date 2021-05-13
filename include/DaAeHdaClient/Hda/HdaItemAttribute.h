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

#ifndef TECHNOSOFTWARE_HDATTRIBUTE_H
#define TECHNOSOFTWARE_HDATTRIBUTE_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        /**
         * @class    HdaItemAttribute
         *
         * @brief    Contains all property elements of a single HDA item attribute.
         *
         * @ingroup    HDAClient
         */

		class OPCCLIENTSDK_API HdaItemAttribute : protected OpcObject
        {
        public:

            /**
             * @fn  HdaItemAttribute::HdaItemAttribute() noexcept(false);
             *
             * @brief   Constructs a HdaItemAttribute object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             */

			HdaItemAttribute() noexcept(false);

            /**
             * @fn  HdaItemAttribute::HdaItemAttribute(const HdaItemAttribute& itemAttribute) noexcept(false);
             *
             * @brief   Constructs a HdaItemAttribute object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param   itemAttribute   Constructs a copy of an existing HdaItemAttribute object.
             */

			HdaItemAttribute(const HdaItemAttribute& itemAttribute) noexcept(false);

            /**
             * @fn  virtual HdaItemAttribute::~HdaItemAttribute() noexcept;
             *
             * @brief   Destroys the object.
             */

			virtual ~HdaItemAttribute() noexcept;


		public:

            /**
             * @fn  HdaItemAttribute& HdaItemAttribute::operator=(const HdaItemAttribute& itemAttribute) noexcept(false);
             *
             * @brief   Assigns an existing aggregate object to another.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             * @exception   e                               Thrown when an e error condition occurs.
             *
             * @param   itemAttribute   The HdaItemAttribute.
             *
             * @return  A shallow copy of this object.
             */

			HdaItemAttribute& operator =(const HdaItemAttribute& itemAttribute) noexcept(false);

        protected:

            /**
             * @fn  HdaItemAttribute::HdaItemAttribute(DWORD id, string& name, string& description, VARTYPE itemAttributeDataType) noexcept(false);
             *
             * @brief   Constructor.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param           id                      The identifier.
             * @param [in,out]  name                    The name.
             * @param [in,out]  description             The description.
             * @param           itemAttributeDataType   Type of the item attribute data.
             */

			HdaItemAttribute(DWORD id, string& name, string& description, VARTYPE itemAttributeDataType) noexcept(false);

        public:

            /**
             * @fn  uint32_t HdaItemAttribute::GetId() const noexcept
             *
             * @brief   The HDA item attribute identifier.
             *
             * @return  An uint32_t.
             */

			uint32_t GetId() const noexcept { return attributeId_; }

            /**
             * @fn  const string& HdaItemAttribute::GetName() const noexcept
             *
             * @brief   The name of the HDA item attribute.
             *
             * @return  A string&amp;
             */

			const string& GetName() const noexcept { return attributeName_; }

            /**
             * @fn  const string& HdaItemAttribute::GetDescription() const noexcept
             *
             * @brief   A short description of the HDA item attribute.
             *
             * @return  A string&amp;
             */

            const string& GetDescription() const noexcept { return attributeDescription_; }

            /**
             * @fn  const VARTYPE& HdaItemAttribute::GetDataType() const noexcept
             *
             * @brief   The data type of the HDA item attribute.
             *
             * @return  A VARTYPE&amp;
             */

			const VARTYPE& GetDataType() const noexcept { return itemAttributeDataType_; }

        public:

        protected:
			friend class HdaServerImpl;
			uint32_t					attributeId_;
			string                      attributeName_;
			string                      attributeDescription_;
			VARTYPE						itemAttributeDataType_;
        };
    }
}

#endif /* TECHNOSOFTWARE_HDATTRIBUTE_H */
