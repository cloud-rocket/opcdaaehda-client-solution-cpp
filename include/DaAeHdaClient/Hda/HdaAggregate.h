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

#ifndef TECHNOSOFTWARE_HDAAGGREGATE_H
#define TECHNOSOFTWARE_HDAAGGREGATE_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
		/**
		 * @class	HdaAggregate
		 *
		 * @brief	Contains all property elements of a single HDA aggregate.
		 *
		 * @ingroup	HDAClient
		 */

		class OPCCLIENTSDK_API HdaAggregate : protected OpcObject
        {
        public:

            /**
             * @fn  HdaAggregate::HdaAggregate() noexcept(false);
             *
             * @brief   Constructs a HdaAggregate object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             */

			HdaAggregate() noexcept(false);

            /**
             * @fn  HdaAggregate::HdaAggregate(const HdaAggregate& aggregate) noexcept(false);
             *
             * @brief   Constructs a HdaAggregate object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param   aggregate   Constructs a copy of an existing HdaAggregate object.
             */

			HdaAggregate(const HdaAggregate& aggregate) noexcept(false);

            /**
             * @fn  virtual HdaAggregate::~HdaAggregate() noexcept;
             *
             * @brief   Destroys the object.
             */

			virtual ~HdaAggregate() noexcept;


		public:

            /**
             * @fn  HdaAggregate& HdaAggregate::operator=(const HdaAggregate& aggregate) noexcept(false);
             *
             * @brief   Assigns an existing aggregate object to another.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             * @exception   e                               Thrown when an e error condition occurs.
             *
             * @param   aggregate   The HdaAggregate.
             *
             * @return  A shallow copy of this object.
             */

			HdaAggregate& operator =(const HdaAggregate& aggregate) noexcept(false);

        protected:

            /**
             * @fn  HdaAggregate::HdaAggregate(DWORD id, string& name, string& description) noexcept(false);
             *
             * @brief   Constructor.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param           id          The identifier.
             * @param [in,out]  name        The name.
             * @param [in,out]  description The description.
             */

			HdaAggregate(DWORD id, string& name, string& description) noexcept(false);

        public:

			/**
			 * @fn	uint32_t HdaAggregate::GetId() const throw ()
			 *
			 * @brief	The HDA aggregate identifier.
			 *
			 * @return	An uint32_t.
			 */

			uint32_t GetId() const noexcept { return aggregateIdentifier_; }

            /**
             * @fn  const string& HdaAggregate::GetName() const noexcept
             *
             * @brief   The name of the HDA aggregate.
             *
             * @return  A string&amp;
             */

			const string& GetName() const noexcept { return aggregateName_; }

            /**
             * @fn  const string& HdaAggregate::GetDescription() const noexcept
             *
             * @brief   A short description of the HDA aggregate.
             *
             * @return  A string&amp;
             */

            const string& GetDescription() const noexcept { return aggregateDescription_; }

        public:

        protected:
			friend class HdaServerImpl;
			uint32_t					aggregateIdentifier_;
			string                      aggregateName_;
			string                      aggregateDescription_;
        };
    }
}

#endif /* TECHNOSOFTWARE_HDAAGGREGATE_H */
