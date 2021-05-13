/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

 // STD
#include <stdint.h>

// Technosoftware
#include "Base/Status.h"

namespace Technosoftware
{
    namespace Base
    {
        using namespace Technosoftware::Base;
        using std::string;
        using std::vector;

        StatusCode::StatusCode(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t dwCode, FuncCallType eFuncType) throw ()
        {
            statusCode_ = statusCode;
            resultCode_ = dwCode;

            if (eFuncType == SysFuncCall) {
                statusCodeType_ = SysCode;                        // System specific errror returned by a system function
            }
            else if (HRESULT_FACILITY(resultCode_) == FACILITY_ITF) {
                if (eFuncType == DaFuncCall)        statusCodeType_ = DaCode;
                else if (eFuncType == AeFuncCall)   statusCodeType_ = AeCode;
                else                                statusCodeType_ = HdaCode;
            }
            else {
                statusCodeType_ = OpcSysCode;                     // System specific error returned by an OPC function
            }
        }

        StatusCode::StatusCode(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t dwCode, const std::string& message, FuncCallType eFuncType) throw ()
        {
            message_ = message;
            statusCode_ = statusCode;
            resultCode_ = dwCode;

            if (eFuncType == SysFuncCall) {
                statusCodeType_ = SysCode;                        // System specific errror returned by a system function
            }
            else if (HRESULT_FACILITY(resultCode_) == FACILITY_ITF) {
                if (eFuncType == DaFuncCall)        statusCodeType_ = DaCode;
                else if (eFuncType == AeFuncCall)   statusCodeType_ = AeCode;
                else                                statusCodeType_ = HdaCode;
            }
            else {
                statusCodeType_ = OpcSysCode;                     // System specific error returned by an OPC function
            }
        }

        const std::string& StatusCode::ToString() throw ()
        {
            try {
                if (message_.empty()) {
                   //message_ = GetErrorDescription(m_dwCode, statusCodeType_, IsResult() /* false = called from OpcError */);
                }
            }
            catch (...) {
            }
            return message_;
        }

        /**
        * @fn	const bool Status::IsError() const throw ()
        *
        * @brief	Query if this object is error.
        *
        * @return	true if error, false if not.
        */

        const bool Status::IsError() const throw () { return FAILED(resultCode_) ? true : false; }

        /**
        * @fn	const bool Status::IsSuccess() const throw ()
        *
        * @brief	Query if this object is success.
        *
        * @return	true if success, false if not.
        */

        const bool Status::IsSuccess() const throw () { return SUCCEEDED(resultCode_) ? true : false; }

        /**
        * @fn	const bool Status::IsOk() const throw ()
        *
        * @brief	Query if this object is ok.
        *
        * @return	true if ok, false if not.
        */

        const bool Status::IsOk() const throw () { return (resultCode_ == S_OK) ? true : false; }

        /**
        * @fn	Status& Status::operator=( const Status& res ) throw ()
        *
        * @brief	Assignment operator.
        *
        * @param	res	The resource.
        *
        * @return	A shallow copy of this object.
        */

        Status& Status::operator =(const Status& res) throw ()
        {
            try {
                if (this != &res) {
                    statusCode_ = res.statusCode_;
                    resultCode_ = res.resultCode_;
                    statusCodeType_ = res.statusCodeType_;
                    message_ = res.message_;
                }
            }
            catch (...) {
            }
            return *this;
        }

        const std::string& Status::ToString() throw ()
        {
            return message_;
        }
    }
}

