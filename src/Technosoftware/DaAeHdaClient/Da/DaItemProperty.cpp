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
#include "DaAeHdaClient/Da/DaItemProperty.h"
#include <comdef.h>
#include <comutil.h>

#include "Base/Exception.h"
namespace Technosoftware
{
    namespace DaAeHdaClient
    {

        DaItemProperty::DaItemProperty() noexcept(false) : OpcObject(nullptr, "DaItemProperty")
        {
            try {
                VariantInit(&value_);
                dataType_ = 0;
                itemPropertyId_ = 0;
            }
            catch (...) {
                throw Base::UnhandledException();
            }
        }

        DaItemProperty::DaItemProperty(const DaItemProperty& itemProperty) noexcept(false)
        {
            *this = itemProperty;
        }

        DaItemProperty::DaItemProperty(void* itemProperty) noexcept(false) : OpcObject(nullptr, "DaItemProperty")
        {
            try {
                OPCITEMPROPERTY* _pItemProperty = static_cast<OPCITEMPROPERTY*>(itemProperty);
                _ASSERTE(_pItemProperty);

                VariantInit((LPVARIANT)&value_);

                // The Property ID is always set
                itemPropertyId_ = _pItemProperty->dwPropertyID;

                result_ = Technosoftware::DaAeHdaClient::GetStatusFromHResult(_pItemProperty->hrErrorID,Base::StatusCode::DaFuncCall);
                if (result_.IsGood()) {
                    USES_CONVERSION;

                    if (_pItemProperty->szDescription != NULL)
                    {
                        description_ = OLE2A(_pItemProperty->szDescription);
                    }
                    else
                    {
                        description_ = "";
                    }


                    // Note: some servers returns a null pointer and not a NULL string
                    itemId_ = _pItemProperty->szItemID ? OLE2A(_pItemProperty->szItemID) : "";
                    dataType_ = _pItemProperty->vtDataType;

                    // Workaround for some servers
                    // Use the Data Type from the Value (if specified) if dataType_ is not specified         
                    if (dataType_ == VT_EMPTY && V_VT(&_pItemProperty->vValue) != VT_EMPTY) {
                        dataType_ = V_VT(&_pItemProperty->vValue);
                    }

                    HRESULT hr = VariantCopy(&value_, &_pItemProperty->vValue);
                    if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr));
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
        }

        DaItemProperty::~DaItemProperty() noexcept
        {
            try {
                VariantClear(&value_);
            }
            catch (...) {}
        }

        DaItemProperty& DaItemProperty::operator =(const DaItemProperty& itemProperty) noexcept(false)
        {
            try {
                if (this != &itemProperty) {
                    VariantInit(&value_);
                    HRESULT hr = VariantCopy(&value_, (LPVARIANT)&itemProperty.value_);
                    if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr));

                    itemPropertyId_ = itemProperty.itemPropertyId_;
                    description_ = itemProperty.description_;
                    dataType_ = itemProperty.dataType_;
                    itemId_ = itemProperty.itemId_;
                    result_ = itemProperty.result_;
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

        string DaItemProperty::GetDataTypeAsText(OpcTextMode eTextMode /* = Capitalize */) /* throw (...) */
        {
            return Technosoftware::DaAeHdaClient::DataTypeAsText(dataType_, eTextMode);
        }


        //----------------------------------------------------------------------------------------------------------------------
        // VariantFromVariantArrayElement                                                                               INTERNAL
        // ------------------------------
        //    Creates a Variant from the element of an Array-Variant.
        //    The data pointer must be locked outside of this function.
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    static HRESULT VariantFromVariantArrayElement( LPVARIANT pvDest, VARTYPE vtRequested, const void HUGEP* pData, DWORD dwNdx, VARTYPE vtElement )
         *
         * @brief    Variant from variant array element.
         *
         * @param    pvDest           The pv destination.
         * @param    vtRequested    The vt requested.
         * @param    pData           The data.
         * @param    dwNdx           The ndx.
         * @param    vtElement      The vt element.
         *
         * @return    A HRESULT.
         */

        static HRESULT VariantFromVariantArrayElement(
            /* [out] */    LPVARIANT pvDest,
            /* [in]  */    VARTYPE vtRequested,
            /* [in]  */    const void HUGEP* pData,
            /* [in]  */    DWORD dwNdx,
            /* [in]  */    VARTYPE vtElement)
        {
            HRESULT  hr = S_OK;
            VARIANT  vTmpByRef;

            VariantInit(&vTmpByRef);

            V_VT(&vTmpByRef) = vtElement | VT_BYREF;
            switch (vtElement) {
            case VT_I1:       V_I1REF(&vTmpByRef) = &((CHAR*)pData)[dwNdx];           break;
            case VT_UI1:      V_UI1REF(&vTmpByRef) = &((BYTE*)pData)[dwNdx];           break;
            case VT_I2:       V_I2REF(&vTmpByRef) = &((SHORT*)pData)[dwNdx];          break;
            case VT_UI2:      V_UI2REF(&vTmpByRef) = &((USHORT*)pData)[dwNdx];         break;
            case VT_I4:       V_I4REF(&vTmpByRef) = &((LONG*)pData)[dwNdx];           break;
            case VT_UI4:      V_UI4REF(&vTmpByRef) = &((ULONG*)pData)[dwNdx];          break;
            case VT_R4:       V_R4REF(&vTmpByRef) = &((FLOAT*)pData)[dwNdx];          break;
            case VT_R8:       V_R8REF(&vTmpByRef) = &((DOUBLE*)pData)[dwNdx];         break;
            case VT_CY:       V_CYREF(&vTmpByRef) = &((CY*)pData)[dwNdx];             break;
            case VT_DATE:     V_DATEREF(&vTmpByRef) = &((DATE*)pData)[dwNdx];           break;
            case VT_BSTR:     V_BSTRREF(&vTmpByRef) = &((BSTR*)pData)[dwNdx];           break;
            case VT_BOOL:     V_BOOLREF(&vTmpByRef) = &((VARIANT_BOOL*)pData)[dwNdx];   break;
            case VT_VARIANT:  V_VARIANTREF(&vTmpByRef) = &((VARIANT*)pData)[dwNdx];        break;
            default:          hr = OPC_E_BADTYPE;                                            break;
            }

            if (SUCCEEDED(hr)) {
                hr = VariantChangeType(pvDest, &vTmpByRef, 0, vtRequested);
                if ((V_VT(pvDest) == VT_EMPTY) && SUCCEEDED(hr)) {
                    hr = OPC_E_BADTYPE;                    // It may happen that VariantChangeType returns SUCCEEDED,
                }                                         // but the conversion failed.
            }

            VariantClear(&vTmpByRef);
            return hr;

        } // VariantFromVariantArrayElement

        string DaItemProperty::GetValueAsText() /* throw (...) */
        {
            if (V_ISARRAY(&value_)) {
                //
                // Convert an Array-Variant to a BSTR-Variant
                //
                void HUGEP* pData = NULL;
                SAFEARRAY*  psa = V_ARRAY(&value_);

                HRESULT hr = SafeArrayAccessData(psa, &pData);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr));

                _bstr_t  bstr;

                DWORD dwLBound = psa->rgsabound[0].lLbound;
                DWORD dwUBound = dwLBound + psa->rgsabound[0].cElements;

                for (DWORD i = dwLBound; i < dwUBound; i++) {
                    _variant_t  vTmp;

                    hr = VariantFromVariantArrayElement(&vTmp, VT_BSTR,
                        pData, i,
                        V_VT(&value_) & VT_TYPEMASK);      // Variant Type of the Source Element
                    if (FAILED(hr)) {
                        SafeArrayUnaccessData(psa);
                        return "<unsupported data conversion>";
                    }

                    bstr += V_BSTR(&vTmp);
                    if (i < dwUBound - 1) {                 // If not last element value
                        bstr += "; ";                       // then insert a delimiter character
                    }
                }
                hr = SafeArrayUnaccessData(psa);
                if (FAILED(hr)) throw Technosoftware::Base::StatusException(Technosoftware::DaAeHdaClient::GetStatusFromHResult(hr));
                return (char*)bstr;
            }
            else {
                return (char*)_bstr_t(value_);
            }
        }
    }
}
