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
#include "DaAeHdaClient/Hda/HdaAggregateId.h"
#include "DaAeHdaClient/Hda/HdaAggregate.h"
#include <comdef.h>
#include <comutil.h>

#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {

		HdaAggregate::HdaAggregate() noexcept(false) : OpcObject(NULL, "HdaAggregate")
        {
            try {
				aggregateIdentifier_ = (uint32_t)HdaAggregateId::NoAggregate;
			}
            catch (...) {
                throw Technosoftware::Base::UnhandledException();
            }
        }

		HdaAggregate::HdaAggregate(const HdaAggregate& aggregate) noexcept(false)
		{
            *this = aggregate;
        }

		HdaAggregate::HdaAggregate(DWORD id, string& name, string& description) noexcept(false)
		{
			aggregateIdentifier_ = id;
			aggregateName_ = name;
			aggregateDescription_ = description;
		}

		HdaAggregate::~HdaAggregate() throw ()
        {
            try {
            }
            catch (...) {}
        }

		HdaAggregate& HdaAggregate::operator =(const HdaAggregate& aggregate) noexcept(false)
		{
            try {
				if (this != &aggregate) {
					aggregateIdentifier_ = aggregate.aggregateIdentifier_;
					aggregateName_ = aggregate.aggregateName_;
					aggregateDescription_ = aggregate.aggregateDescription_;
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
