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
#include "DaAeHdaClient/OpcBase.h"
#include <ctime>
#include <comdef.h>
#include "Base/Status.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        std::string QualityAsText(uint16_t quality)
        {
            std::string str;

            switch (quality & OPC_QUALITY_MASK) {
            case OPC_QUALITY_BAD:
                str = "Bad: ";
                break;
            case OPC_QUALITY_GOOD:
                str = "Good: ";
                break;
            case OPC_QUALITY_UNCERTAIN:
                str = "Uncertain: ";
                break;
            default:
                str = "N/A: ";
                break;
            }

            switch (quality & OPC_STATUS_MASK) {
            case OPC_QUALITY_CONFIG_ERROR:
                str += "Configuration Error";
                break;
            case OPC_QUALITY_NOT_CONNECTED:
                str += "Not Connected";
                break;
            case OPC_QUALITY_DEVICE_FAILURE:
                str += "Device Failure";
                break;
            case OPC_QUALITY_SENSOR_FAILURE:
                str += "Sensor Failure";
                break;
            case OPC_QUALITY_LAST_KNOWN:
                str += "Last Known Value";
                break;
            case OPC_QUALITY_COMM_FAILURE:
                str += "Communication Failure";
                break;
            case OPC_QUALITY_OUT_OF_SERVICE:
                str += "Out of Service";
                break;
            case OPC_QUALITY_WAITING_FOR_INITIAL_DATA:
                str += "Waiting for Initial Data";
                break;
            case OPC_QUALITY_LAST_USABLE:
                str += "Last Usable Value";
                break;
            case OPC_QUALITY_SENSOR_CAL:
                str += "Sensor Not Accurate";
                break;
            case OPC_QUALITY_EGU_EXCEEDED:
                str += "Engineering Units Exceeded";
                break;
            case OPC_QUALITY_SUB_NORMAL:
                str += "Sub-Normal";
                break;
            case OPC_QUALITY_LOCAL_OVERRIDE:
                str += "Local Override";
                break;
            case OPC_QUALITY_BAD:
            case OPC_QUALITY_UNCERTAIN:
            case OPC_QUALITY_GOOD:
                str += "Non-specific";
                break;
            default:
                str += "N/A";
                break;
            }

            str += ", Limit: ";
            switch (quality & OPC_LIMIT_MASK)
            {
            case OPC_LIMIT_OK:
                str += "Not Limited";
                break;
            case OPC_LIMIT_LOW:
                str += "Low Limited";
                break;
            case OPC_LIMIT_HIGH:
                str += "High Limited";
                break;
            case OPC_LIMIT_CONST:
                str += "Constant";
                break;
            default:
                str += "N/A";
                break;
            }
            return str;
        }

        std::string DataTypeAsText(VARTYPE value, OpcTextMode textMode /* = Capitalize */)
        {
            string str;

            if (textMode == OpcTextMode::Valuename) {

                if (value & VT_ARRAY) {
                    str = "VT_ARRAY | ";
                }
                switch (value & VT_TYPEMASK) {
                case VT_BOOL:
                    str += "VT_BOOL";
                    break;
                case VT_INT:
                    str += "VT_INT";
                    break;
                case VT_I2:
                    str += "VT_I2";
                    break;
                case VT_I4:
                    str += "VT_I4";
                    break;
                case VT_I8:
                    str += "VT_I8";
                    break;
                case VT_R4:
                    str += "VT_R4";
                    break;
                case VT_R8:
                    str += "VT_R8";
                    break;
                case VT_DATE:
                    str += "VT_DATE";
                    break;
                case VT_BSTR:
                    str += "VT_BSTR";
                    break;
                case VT_UI1:
                    str += "VT_UI1";
                    break;
                case VT_I1:
                    str += "VT_I1";
                    break;
                case VT_UINT:
                    str += "VT_UINT";
                    break;
                case VT_UI2:
                    str += "VT_UI2";
                    break;
                case VT_UI4:
                    str += "VT_UI4";
                    break;
                case VT_UI8:
                    str += "VT_UI8";
                    break;
                case VT_CY:
                    str += "VT_CY";
                    break;
                case VT_EMPTY:
                    str += "VT_EMPTY";
                    break;
                case VT_VARIANT:
                    str += "VT_VARIANT";
                    break;
                default:
                    str += "???";
                    break;
                }
                return str;
            }


            if (value & VT_ARRAY) {
                str = "Array Of ";
            }
            switch (value & VT_TYPEMASK) {
            case VT_BOOL:
                str += "Boolean";
                break;
            case VT_INT:
                str += "Integer";
                break;
            case VT_I2:
                str += "Short Integer";
                break;
            case VT_I4:
                str += "Long Integer";
                break;
            case VT_I8:
                str += "64bit Integer";
                break;
            case VT_R4:
                str += "Single Float";
                break;
            case VT_R8:
                str += "Double Float";
                break;
            case VT_DATE:
                str += "Date";
                break;
            case VT_BSTR:
                str += "String";
                break;
            case VT_UI1:
                str += "Byte";
                break;
            case VT_I1:
                str += "Character";
                break;
            case VT_UINT:
                str += "Unsigned Integer";
                break;
            case VT_UI2:
                str += "Unsigned Short";
                break;
            case VT_UI4:
                str += "Unsigned Long";
                break;
            case VT_UI8:
                str += "64bit Unsigned Integer";
                break;
            case VT_CY:
                str += "Currency";
                break;
            case VT_EMPTY:
                str += "Empty";
                break;
            case VT_VARIANT:
                str += "Variant";
                break;
            default:
                str += "???";
                break;
            }

            if (textMode == OpcTextMode::Lowercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                        // destination
                    tolower);                           // operation

            else if (textMode == OpcTextMode::Uppercase)
                transform(str.begin(), str.end(),       // source
                    str.begin(),                        // destination
                    toupper);                           // operation

            return str;
        }

        /**
        * @fn  bool Status::GetProxyFileName(StatusType statusType, string& proxyFileName)
        *
        * @brief   Returns the filename of the specified Proxy/Stub DLL.
        *
        *          Returns true if all succeeded; othrwise false.
        *
        * @param           statusType      Type of the status.
        * @param [in,out]  proxyFileName   Filename of the proxy file.
        *
        * @StatusCode =  true if it succeeds, false if it fails.
        */

        static bool GetProxyFileName(Base::Status::StatusCodeType statusType, std::string& proxyFileName)
        {
            // The defined filenames are used
            if (statusType == Base::Status::StatusCodeType::DaCode) {
                proxyFileName = "OPCProxy";
            }
            else if (statusType == Base::Status::StatusCodeType::AeCode) {
                proxyFileName = "opc_aeps";
            }
            else if (statusType == Base::Status::StatusCodeType::HdaCode) {
                proxyFileName = "opchda_ps";
            }
            else {
                return false;
            }

            if (proxyFileName.empty()) {
                return false;                               // out of memory
            }
            return true;                                    // all succeeded
        }

        /**
        * @fn  HRESULT Status::GetProxyDLLHandle(LPCTSTR pszProxyDLL, HMODULE& hModule, bool& fLoaded)
        *
        * @brief   Returns the module handle of the specified OPC Proxy/Stub DLL.
        *
        * @param           pszProxyDLL The proxy DLL.
        * @param [in,out]  hModule     The module.
        * @param [in,out]  fLoaded     The loaded.
        *
        * @StatusCode =  The proxy DLL handle.
        */

        static HRESULT GetProxyDLLHandle(LPCTSTR pszProxyDLL, HMODULE& hModule, bool& fLoaded)
        {
            fLoaded = false;
            hModule = GetModuleHandle(pszProxyDLL);
            if (hModule == nullptr) {
                hModule = LoadLibrary(pszProxyDLL);
                if (hModule == nullptr) {
                    return E_FAIL;
                }
                else {
                    fLoaded = true;
                }
            }
            return S_OK;
        }

        /**
        * @fn  static std::string GetErrorStringFromModule( HMODULE handleModule, HRESULT dwError, LCID dwLcid, bool isResult)
        *
        * @brief   Returns an error message from the message table of the specified module or from.
        *
        * @param   handleModule     searches in the module with this handle or in the system if NULL.
        * @param   dwError     The error.
        * @param   dwLcid      The lcid.
        * @param   isResult   true if this object is result.
        *
        * @StatusCode =  The error string from module.
        */

        static std::string GetErrorStringFromModule(
            /* [in] */                 HMODULE  handleModule,
            /* [in] */                 HRESULT  dwError,
            /* [in] */                 LCID     dwLcid,
            /* [in] */                 bool     isResult) /* throw (...) */
        {
            LPTSTR   lpMsgBuf = nullptr;
            DWORD    dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS;

            if (handleModule)   dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;
            else                dwFlags |= FORMAT_MESSAGE_FROM_SYSTEM;

            DWORD dwRTC = FormatMessage(
                dwFlags,
                handleModule,                                   // From Module or System
                dwError,                                        // Error Code
                LANGIDFROMLCID(dwLcid),                         // Language Identifier
                reinterpret_cast<LPTSTR>(&lpMsgBuf),            // Output string buffer
                0,                                              // no static message buffer
                nullptr);                                       // no message insertion.

            string str;
            if (dwRTC == 0) {                                   // Error occured.

                if (GetLastError() == ERROR_RESOURCE_LANG_NOT_FOUND) {
                    str = "Cannot get error message: The specified resource language identifier cannot be found in the image file.";
                }
                else {
                    char stmp[30];
                    sprintf_s(stmp, sizeof(stmp), "Unknown %s 0x%0lX", isResult ? "result" : "error", dwError);
                    str = stmp;
                }
            }
            else {                                              // Message found.

                TCHAR* pc = &lpMsgBuf[dwRTC - 1];               // Truncate \r\n
                while (pc && (*pc == static_cast<TCHAR>('\r') || (*pc == static_cast<TCHAR>('\n')))) {
                    *pc = static_cast<TCHAR>('\0');
                    pc--;
                    dwRTC--;
                }
                USES_CONVERSION;
                str = T2A(lpMsgBuf);
            }
            if (lpMsgBuf) {                                     // Free the temporary buffer.
                LocalFree(lpMsgBuf);
            }
            return str;
        }

        static std::string GetErrorDescription(uint32_t result, Base::Status::StatusCodeType statusType, bool isResult)
        {
            std::string str;
            try {
                HMODULE  hModule = nullptr;
                bool     fLoaded = false;
                string   sProxyFileName;
                HRESULT  hr = E_FAIL;

                if (statusType != Base::Status::StatusCodeType::SysCode && statusType != Base::Status::StatusCodeType::OpcSysCode) {
                    if (GetProxyFileName(statusType, sProxyFileName)) {
                        USES_CONVERSION;
                        hr = GetProxyDLLHandle(A2CT(sProxyFileName.c_str()), hModule, fLoaded);
                    }
                }
                else {
                    hr = S_OK;
                }
                if (FAILED(hr)) {
                    char stmp[30];
                    sprintf_s(stmp, sizeof(stmp), "Unknown %s 0x%0lX", isResult ? "result" : "error", result);
                    str = stmp;
                }
                else {
                    str = GetErrorStringFromModule(
                        hModule,
                        result,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        isResult);
                }
                if (hModule && fLoaded) {
                    FreeLibrary(hModule);                // Release the loaded library
                }
            }
            catch (...) {
            }
            return str;
        }

        Base::Status GetStatusFromHResult(const HRESULT result, Base::StatusCode::FuncCallType funcCallType /* = Base::Status::StatusCode::SysFuncCall */, bool isResult /* = false */)
        {
            Base::StatusCodes::StatusCode statusCode;

            Base::Status::StatusCodeType statusCodeType;

            if (funcCallType == Base::Status::StatusCode::SysFuncCall) {
                statusCodeType = Base::Status::StatusCodeType::SysCode;                        // System specific errror returned by a system function
            }
            else if (HRESULT_FACILITY(result) == FACILITY_ITF) {
                if (funcCallType == Base::Status::StatusCode::DaFuncCall)       statusCodeType = Base::Status::StatusCodeType::DaCode;
                else if (funcCallType == Base::Status::StatusCode::AeFuncCall)  statusCodeType = Base::Status::StatusCodeType::AeCode;
                else                                                            statusCodeType = Base::Status::StatusCodeType::HdaCode;
            }
            else {
                statusCodeType = Base::Status::StatusCodeType::OpcSysCode;                     // System specific error returned by an OPC function
            }


            const std::string& description = GetErrorDescription(result, statusCodeType, isResult);

            if (result == HRESULT_FROM_WIN32(ERROR_ACCOUNT_EXPIRED)) {
                statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadLicenseExpired;
            }
            else {
                switch (result)
                {
                case S_OK:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::Good;
                    break;
                case OPC_E_SRVNOTCONNECTED:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadOutOfService;
                    break;
                case E_OUTOFMEMORY:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadOutOfMemory;
                    break;
                case OPC_E_INVALIDHANDLE:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadNodeIdUnknown;
                    break;
                case OPC_E_BADRIGHTS:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadNotReadable;
                    break;
                case OPC_E_UNKNOWNITEMID:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadNodeIdUnknown;
                    break;
                case OPC_E_INVALIDITEMID:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadNodeIdInvalid;
                    break;
                case OPC_E_INVALID_PID:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadNodeIdInvalid;
                    break;
                case E_ACCESSDENIED:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadOutOfService;
                    break;
                case DISP_E_TYPEMISMATCH:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadTypeMismatch;
                    break;
                case OPC_E_BADTYPE:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadTypeMismatch;
                    break;
                case OPC_E_RANGE:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadTypeMismatch;
                    break;
                case DISP_E_OVERFLOW:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadTypeMismatch;
                    break;
                case OPC_E_NOTSUPPORTED:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadNotSupported;
                    break;
                case OPC_S_CLAMP:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::GoodClamped;
                    break;
                default:
                    statusCode = Technosoftware::Base::StatusCodes::StatusCode::BadUnexpectedError;
                }
            }
            return Technosoftware::Base::Status(statusCode, result, description, funcCallType);
        }
    }
}