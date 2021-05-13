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
#include "DaAeHdaClient/Hda/HdaItemAttributeId.h"
#include "DaAeHdaClient/Hda/HdaItemAttribute.h"
#include <comdef.h>
#include <comutil.h>

#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {

		HdaItemAttribute::HdaItemAttribute() noexcept(false) : OpcObject(NULL, "HdaItemAttribute")
        {
            try {
				attributeId_ = (uint32_t)HdaItemAttributeId::NoItemAttribute;
			}
            catch (...) {
                throw Technosoftware::Base::UnhandledException();
            }
        }

		HdaItemAttribute::HdaItemAttribute(const HdaItemAttribute& itemAttribute) noexcept(false)
		{
			*this = itemAttribute;
        }

		HdaItemAttribute::HdaItemAttribute(DWORD id, string& name, string& description, VARTYPE itemAttributeDataType)
		noexcept(false)
		{
			attributeId_ = id;
			attributeName_ = name;
			attributeDescription_ = description;
			itemAttributeDataType_ = itemAttributeDataType;
		}

		HdaItemAttribute::~HdaItemAttribute() throw ()
        {
            try {
            }
            catch (...) {}
        }

		HdaItemAttribute& HdaItemAttribute::operator =(const HdaItemAttribute& itemAttribute) noexcept(false)
		{
            try {
				if (this != &itemAttribute) {
					attributeId_ = itemAttribute.attributeId_;
					attributeName_ = itemAttribute.attributeName_;
					attributeDescription_ = itemAttribute.attributeDescription_;
					itemAttributeDataType_ = itemAttribute.itemAttributeDataType_;
				}
            }
            catch (Technosoftware::Base::Status e) {
                throw e;
            }
            catch (std::bad_alloc) {
                throw Technosoftware::Base::OutOfMemoryException();
            }
            catch (...) {
                throw Technosoftware::Base::UnhandledException();
            }
            return *this;
        }
    }
}
