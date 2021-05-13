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

#ifndef TECHNOSOFTWARE_DACOMMON_H
#define TECHNOSOFTWARE_DACOMMON_H

#include "DaAeHdaClient/OpcBase.h"
#ifdef _WIN64
#include "Classic/inc64/opcda.h"
#else
#include "Classic/inc32/opcda.h"
#endif // _WIN64
#include "Base/Status.h"
#include "Base/Handles.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class OpcItemDefArray;

        /**
         * @struct  DaItemDefinition
         *
         * @brief   Contains the required definitions of those items which one would like to create.
         *          
         *          The list of item definitions is used as parameter of method DaGroup::AddItems()
         *          to create item instances.
         *
         * @ingroup  DaAeHdaClient
         */

        typedef struct DaItemDefinition {

            /** @brief   Identifier for the item. */

            const char*             ItemIdentifier;

            /** @brief   The client. */

            Base::ClientHandle      ClientHandle;

            /** @brief   Type of the vt requested data. */

            VARTYPE                 RequestedDataType;

            /** @brief   true to active. */

            bool                    IsActive;

            /** @brief   Full pathname of the access file. */

            const char*             AccessPath;

            /** @brief   Size of the BLOB. */

            uint32_t                BlobSize;

            /** @brief   The BLOB. */

            unsigned char*          Blob;

        } DaItemDefinition;

        /**
         * @class   DaItemDefinitions
         *
         * @brief   Contains the required definitions of those items which one would like to create.
         *          
         *          The list of item definitions is used as parameter of method DaGroup::AddItems() to
         *          create item instances.
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaItemDefinitions : protected OpcObject
        {
        public:

            /**
             * @fn  DaItemDefinitions::DaItemDefinitions(OpcObject* parent = NULL) throw (Technosoftware::Base::Exception);
             *
             * @brief   Constructs a DaItemDefinitions object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param [in,out]  parent (Optional) If non-null, (Optional) the parent.
             */

            DaItemDefinitions(OpcObject* parent = nullptr) noexcept(false);

            /**
             * @fn  DaItemDefinitions::~DaItemDefinitions() noexcept;
             *
             * @brief   Destroys a DaItemDefinitions object.
             */

            ~DaItemDefinitions() noexcept;

            /**
             * @fn  Technosoftware::Base::Status DaItemDefinitions::Add( const char* itemIdentifier, Base::ClientHandle clientHandle = 0, VARTYPE requestedDataType = VT_EMPTY, bool isActive = true, const char* accessPath = NULL, uint32_t blobSize = 0, unsigned char* blob = NULL);
             *
             * @brief   Adds the definitions of a new Item instance.
             *          
             *          Please refer to the OPC DA Specification for a detailed description of item
             *          definitions (OPCITEMDEF).
             *
             * @param           itemIdentifier      Identifier for the item.
             * @param           clientHandle        (Optional) the client.
             * @param           requestedDataType   (Optional) type of the vt requested data.
             * @param           isActive            (Optional) true to active.
             * @param           accessPath          (Optional) full pathname of the access file.
             * @param           blobSize            (Optional) size of the BLOB.
             * @param [in,out]  blob                (Optional) If non-null, (Optional) the BLOB.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status Add(   const char*         itemIdentifier,
                                                Base::ClientHandle  clientHandle = 0,
                                                VARTYPE             requestedDataType = VT_EMPTY,
                                                bool                isActive = true,
                                                const char*         accessPath = nullptr,
                                                uint32_t            blobSize = 0,
                                                unsigned char*      blob = nullptr);

            /**
             * @fn  void DaItemDefinitions::RemoveAll();
             *
             * @brief   Removes all previously added definitions.
             */

            void RemoveAll();


        protected:

            /**
             * @class   DaGroupImpl
             *
             * @brief   Only DaGroupImpl::AddItems() needs access to data member parItemDefs_.
             */

            friend class DaGroupImpl;
            /** @brief    The par item defs. */
            OpcAutoPtr<OpcItemDefArray>  parItemDefs_;
        };
    }
}

#endif // TECHNOSOFTWARE_DACOMMON_H
