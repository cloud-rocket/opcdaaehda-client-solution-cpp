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
#include "DaAeHdaClient/Da/DaCommon.h"

#include "Base/Exception.h"
#include "Base/Handles.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        DaItemDefinitions::DaItemDefinitions(OpcObject* parent /* = NULL */) noexcept(false) : OpcObject(parent, "DaItemDefinitions")
        {
            parItemDefs_.Attach(new (std::nothrow) OpcItemDefArray);
            if (!parItemDefs_) throw Technosoftware::Base::OutOfMemoryException();
        }

        DaItemDefinitions::~DaItemDefinitions() noexcept
        {
            try {
                RemoveAll();
            }
            catch (...) {}
        }

        Technosoftware::Base::Status DaItemDefinitions::Add(const char*         itemIdentifier,
            Base::ClientHandle  clientHandle,
            VARTYPE             requestedDataType,
            bool                isActive,
            const char*         accessPath,
            uint32_t            blobSize,
            unsigned char*      blob)
        {
            if (!itemIdentifier) return Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_INVALIDARG);

            OPCITEMDEF  ItemDef;
            memset(&ItemDef, 0, sizeof(ItemDef));

            HRESULT hr = S_OK;
            try {
                USES_CONVERSION;

                ItemDef.vtRequestedDataType = requestedDataType;
                ItemDef.hClient = clientHandle;
                ItemDef.bActive = isActive;
                ItemDef.dwBlobSize = blobSize;
                ItemDef.wReserved = 0;

                // SzItemID, szAccessPath and blob_
                ItemDef.szItemID = _wcsdup(A2W(itemIdentifier));
                if (!ItemDef.szItemID) throw Technosoftware::Base::OutOfMemoryException();

                if (accessPath) {
                    ItemDef.szAccessPath = _wcsdup(A2W(accessPath));
                    if (!ItemDef.szAccessPath) Technosoftware::Base::OutOfMemoryException();
                }

                if (blob) {
                    ItemDef.pBlob = (LPBYTE)malloc(blobSize);
                    if (!ItemDef.pBlob) throw Technosoftware::Base::OutOfMemoryException();
                    memcpy(ItemDef.pBlob, blob, blobSize);
                }

                // Add the the definiton to the array
                if (!parItemDefs_->Add(ItemDef)) throw Technosoftware::Base::OutOfMemoryException();
            }
            catch (HRESULT hrEx) {
                if (ItemDef.szItemID)      free(ItemDef.szItemID);
                if (ItemDef.szAccessPath)  free(ItemDef.szAccessPath);
                if (ItemDef.pBlob)         free(ItemDef.pBlob);
                hr = hrEx;
            }
            catch (...) {
                hr = E_FAIL;
            }
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
        }


        //----------------------------------------------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------------------------------------------
        //const DaItemDefinition& DaItemDefinitions::operator [] ( DWORD dwNdx ) const
        //{
        //   USES_CONVERSION;
        //   OPCITEMDEF* pItemDef = &(parItemDefs_->m_aT[ dwNdx ]);
        //   DaItemDefinition   def;
        //
        //   def.itemIdentifier_           = W2A(pItemDef->szItemID);
        //   def.clientHandle_             = pItemDef->clientHandle_;
        //   def.requestedDataType_ = pItemDef->requestedDataType_;
        //   def.isActive_             = pItemDef->bActive == TRUE ? true : false;
        //   def.accessPath_       = W2A(pItemDef->szAccessPath);
        //   def.blobSize_          = pItemDef->blobSize_;
        //   def.blob_               = pItemDef->blob_;
        //   return def;
        //}


        //----------------------------------------------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------------------------------------------
        //void DaItemDefinitions::Get( DaItemDefinition& def, uint32_t dwNdx )
        //{
        //   USES_CONVERSION;
        //   OPCITEMDEF* pItemDef = &(parItemDefs_->m_aT[ dwNdx ]);
        //
        //   def.itemIdentifier_           = W2A(pItemDef->szItemID);
        //   def.clientHandle_             = pItemDef->clientHandle_;
        //   def.requestedDataType_ = pItemDef->requestedDataType_;
        //   def.isActive_             = pItemDef->bActive == TRUE ? true : false;
        //   def.accessPath_       = W2A(pItemDef->szAccessPath);
        //   def.blobSize_          = pItemDef->blobSize_;
        //   def.blob_               = pItemDef->blob_;
        //}

        void DaItemDefinitions::RemoveAll()
        {
            OPCITEMDEF ItemDef;
            DWORD i = parItemDefs_->GetSize();
            while (i--) {
                ItemDef = (*parItemDefs_)[i];
                if (ItemDef.szItemID)      free(ItemDef.szItemID);
                if (ItemDef.szAccessPath)  free(ItemDef.szAccessPath);
                if (ItemDef.pBlob)         free(ItemDef.pBlob);
            }
            parItemDefs_->RemoveAll();
        }
    }
}
