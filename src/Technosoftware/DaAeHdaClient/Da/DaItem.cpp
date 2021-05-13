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
#include "DaAeHdaClient/Da/DaGroup.h"
#include "DaAeHdaClient/Da/DaGroupImpl.h"
#include "DaAeHdaClient/Da/DaItem.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        DaItem::DaItem(DaGroupImpl* parent, Base::ClientHandle clientHandle
        ) noexcept(false) : OpcObject(parent, "DaItem")
        {
            parent_ = parent;
            clientHandle_ = clientHandle;
            internalClientHandle_ = 0;

            asyncCommandResult_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOTIMPL);
            // Write Value
            VariantInit(&writeValue_);

            // Values initialized by FinalConstruct()
            canonicalDataType_ = VT_EMPTY;
            serverHandle_ = 0;
            accessRights_ = OPC_READABLE + OPC_WRITEABLE;
        }


        //----------------------------------------------------------------------------------------------------------------------
        // FinalConstruct
        //    Must be called to finish the creation of an item instance.
        //----------------------------------------------------------------------------------------------------------------------

        void DaItem::FinalConstruct(OPCITEMRESULT* itemResult) noexcept
        {
            canonicalDataType_ = itemResult->vtCanonicalDataType;
            serverHandle_ = itemResult->hServer;
            accessRights_ = itemResult->dwAccessRights;
        }

        DaItem::~DaItem() noexcept
        {
            try {
                VariantClear(&writeValue_);
                m_cItems.erase(internalClientHandle_);
            }
            catch (...) {}
        }

        Base::Status DaItem::SetWriteValue(LPVARIANT value)
        {
            return Technosoftware::DaAeHdaClient::GetStatusFromHResult(VariantCopy(&writeValue_, value),Base::StatusCode::DaFuncCall);
        }

        void DaItem::Write()
        {
            HRESULT* pErrors = NULL;
            OPCHANDLE serverHandle = serverHandle_;
            HRESULT hr = parent_->m_pIOPCSyncIO->Write(
                1,          // Count
                &serverHandle,
                &writeValue_,
                &pErrors);
            if (SUCCEEDED(hr)) {
                hr = pErrors[0];
                CoTaskMemFree(pErrors);
            }
            writeResult_.Set(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));
        }

        Technosoftware::Base::Status DaItem::Write(LPVARIANT pvValue)
        {
            writeResult_.Set(SetWriteValue(pvValue));
            if (writeResult_.Result().IsGood()) {
                Write();
            }
            return writeResult_.Result();
        }

        Technosoftware::Base::Status& DaItem::WriteAsync(uint32_t dwTransactionID, uint32_t* pdwCancelID)
        {
            HRESULT* pErrors = NULL;
            OPCHANDLE serverHandle = serverHandle_;
            HRESULT hr = parent_->m_pIOPCAsyncIO2->Write(
                1,          // Count
                &serverHandle,
                &writeValue_,
                dwTransactionID,
                (DWORD*)pdwCancelID,
                &pErrors);
            if (SUCCEEDED(hr)) {
                hr = pErrors[0];
                CoTaskMemFree(pErrors);
            }
            asyncCommandResult_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
            return asyncCommandResult_;
        }

        Technosoftware::Base::Status& DaItem::WriteAsync(LPVARIANT pvValue, uint32_t dwTransactionID, uint32_t* pdwCancelID)
        {
            asyncCommandResult_ = SetWriteValue(pvValue);
            if (asyncCommandResult_.IsGood()) {
                WriteAsync(dwTransactionID, pdwCancelID);
                // Note: WriteAsync() already sets asyncCommandResult_.
            }
            return asyncCommandResult_;
        }

        void DaItem::Read(bool fFromCache /* = true */)
        {
            OPCITEMSTATE*  pItemState = NULL;
            HRESULT*       pErrors = NULL;
            OPCHANDLE serverHandle = serverHandle_;
            HRESULT hr = parent_->m_pIOPCSyncIO->Read(
                fFromCache ? OPC_DS_CACHE : OPC_DS_DEVICE,
                1,          // Count
                &serverHandle,
                &pItemState,
                &pErrors);
            if (SUCCEEDED(hr)) {
                hr = pErrors[0];
                CoTaskMemFree(pErrors);
            }
            readResult_.Set(pItemState, Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall));
            if (SUCCEEDED(hr)) {
                VariantClear(&pItemState->vDataValue);
                CoTaskMemFree(pItemState);
            }
        }

        Technosoftware::Base::Status& DaItem::ReadAsync(uint32_t dwTransactionID, uint32_t* pdwCancelID)
        {
            HRESULT* pErrors = NULL;
            OPCHANDLE serverHandle = serverHandle_;
            HRESULT hr = parent_->m_pIOPCAsyncIO2->Read(
                1,          // Count
                &serverHandle,
                dwTransactionID,
                (DWORD*)pdwCancelID,
                &pErrors);
            if (SUCCEEDED(hr)) {
                hr = pErrors[0];
                CoTaskMemFree(pErrors);
            }
            asyncCommandResult_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr,Base::StatusCode::DaFuncCall);
            return asyncCommandResult_;
        }

        Technosoftware::Base::Status& DaItem::Cancel(uint32_t cancelId)
        {
            asyncCommandResult_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(parent_->m_pIOPCAsyncIO2->Cancel2(cancelId),Base::StatusCode::DaFuncCall);
            return asyncCommandResult_;
        }

        /**
         * @fn    DaItem::DaReadResult::DaReadResult()
         *
         * @brief    Default constructor.
         */

        DaItem::DaReadResult::DaReadResult()
        {
            VariantInit(&value_);
            quality_ = OPC_QUALITY_BAD;
            result_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOTIMPL);
        }

        /**
         * @fn    DaItem::DaReadResult::~DaReadResult()
         *
         * @brief    Destructor.
         */

        DaItem::DaReadResult::~DaReadResult()
        {
            VariantClear(&value_);
        }

        /**
         * @fn    bool DaItem::DaReadResult::Set(LPVARIANT pvValue, const FILETIME* pftTimeStamp, uint16_t wQuality, Technosoftware::Base::Status& Result)
         *
         * @brief    Sets.
         *
         * @param    pvValue              The pv value.
         * @param    pftTimeStamp      The pft time stamp.
         * @param    wQuality          The quality.
         * @param [in,out]    Result    The result.
         *
         * @return    true if it succeeds, false if it fails.
         */

        bool DaItem::DaReadResult::Set(LPVARIANT pvValue, const FILETIME* pftTimeStamp, uint16_t wQuality, Technosoftware::Base::Status& Result)
        {
            result_ = Result;
            if (result_.IsGood()) {
                timestamp_ = Technosoftware::Base::Timestamp::FromFileTime(pftTimeStamp->dwLowDateTime, pftTimeStamp->dwHighDateTime);
                quality_ = wQuality;
                HRESULT hr = VariantCopy(&value_, pvValue);
                if (FAILED(hr)) {
                    result_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr);
                    return false;
                }
            }
            return true;
        }

        /**
         * @fn    void DaItem::DaReadResult::Attach( OPCITEMSTATE* pItemState, Technosoftware::Base::Status& Result )
         *
         * @brief    Attaches.
         *
         * @param [in,out]    pItemState    If non-null, state of the item.
         * @param [in,out]    Result          The result.
         */

        void DaItem::DaReadResult::Attach(OPCITEMSTATE* pItemState, Technosoftware::Base::Status& Result)
        {
            result_ = Result;
            if (result_.IsGood()) {
                timestamp_ = Base::Timestamp::FromFileTime(pItemState->ftTimeStamp.dwLowDateTime, pItemState->ftTimeStamp.dwHighDateTime);
                quality_ = pItemState->wQuality;
                VariantClear(&value_);
                value_ = pItemState->vDataValue;  // Shallow copy (Attach)
            }
        }

        /**
         * @fn    string DaItem::DaReadResult::QualityAsText()
         *
         * @brief    Quality as text.
         *
         * @return    A string.
         */

        string DaItem::DaReadResult::GetQualityAsText()
        {
            return Technosoftware::DaAeHdaClient::QualityAsText(quality_);
        }

        /**
         * @fn    DaItem::DaWriteResult::DaWriteResult()
         *
         * @brief    Default constructor.
         */

        DaItem::DaWriteResult::DaWriteResult()
        {
            status_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(E_NOTIMPL);
        }

        /**
         * @fn    DaItem::DaWriteResult::~DaWriteResult()
         *
         * @brief    Destructor.
         */

        DaItem::DaWriteResult::~DaWriteResult()
        {
        }
    }
}

