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

#ifndef TECHNOSOFTWARE_STATUS_H
#define TECHNOSOFTWARE_STATUS_H

#include "Base/Base.h"

// STD
#include <string>
#include <vector>
#include <iostream>

// Technosoftware
#include "StatusCodes.h"

namespace Technosoftware
{
    namespace Base
    {

        /**
         * @class	StatusCode
         *
         * @brief	The StatusCode class is the base class of the result and error handling classes
         * 			Status and OpcError.
         *
         * 			The StatusCode class is used only as base class by several ClientSdk classes.
         *
         * @ingroup BaseOPC
         */

        class TECHNOSOFTWARE_API StatusCode
        {
        public:

            /**
             * @enum    StatusCodeType
             *
             * @brief   Specifies the type identifier of the result or error code.
             */

            enum StatusCodeType {

                /**
                 * @brief	System specific code (result/error) returned by a system function
                 */

                SysCode,

                /**
                 * @brief	System specific code (result/error) returned by an OPC function
                 */

                OpcSysCode,

                /**
                 * @brief	Data Access specific code (result/error) returned by an OPC function
                 */

                DaCode,

                /**
                 * @brief	Alarms & Events specific code (result/error) returned by an OPC function
                 */

                AeCode,

                /**
                 * @brief	Historical Data Access specific code (result/error) returned by an OPC function
                 */

                HdaCode,

                /**
                 * @brief	Unified Architecture specific code (result/error) returned by an OPC function
                 */

                UaCode
            };

            /**
             * @enum	FuncCallType
             *
             * @brief	Specifies the type of function call which returned the result or error code. This
             * 			enumeration values are used only by the constructor of the StatusCode object.
             */

            enum FuncCallType {
                /**
                 * @brief	Identifies the code (result/error) passed to the constructor as a result of a system function
                 */

                SysFuncCall,

                /**
                 * @brief	Identifies the code (result/error) passed to the constructor as a result of an OPC Data Access function
                 */

                DaFuncCall,

                /**
                 * @brief	Identifies the code (result/error) passed to the constructor as a result of an OPC Alarms & Events function
                 */

                AeFuncCall,

                /**
                 * @brief	Identifies the code (result/error) passed to the constructor as a result of an OPC Historical Data Access function
                 */

                HdaFuncCall,

                /**
                 * @brief	Identifies the code (result/error) passed to the constructor as a result of an OPC Unified Architecture function
                 */

                UaFuncCall
            };

        public:

            /**
             * @fn  StatusCode::StatusCode(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t code, FuncCallType funcCallType) throw ();
             *
             * @brief   Constructs a StatusCode object.
             *
             * @param   statusCode      The Technosoftware Status Code.
             * @param   code            The code returned by a system function or OPC function. The code can
             *                          be retrieved with the member function Code() and a description text can
             *                          be retrieved with the member function Description().
             * @param   funcCallType    Specifies the type of function which has returned the code. This
             *                          parameter is used to create the code type which can be retrieved with the
             *                          member function Type().
             */

            StatusCode(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t code, FuncCallType funcCallType) throw ();

            /**
             * @fn  StatusCode::StatusCode(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t code, const std::string& message, FuncCallType funcCallType) throw ();
             *
             * @brief   Constructs a StatusCode object.
             *
             * @param   statusCode      The Technosoftware Status Code.
             * @param   code            The code returned by a system function or OPC function. The code can
             *                          be retrieved with the member function Code() and a description text can
             *                          be retrieved with the member function Description().
             * @param   message         The message.
             * @param   funcCallType    Specifies the type of function which has returned the code. This
             *                          parameter is used to create the code type which can be retrieved with the
             *                          member function Type().
             */

            StatusCode(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t code, const std::string& message, FuncCallType funcCallType) throw ();

            /**
             * @fn  virtual StatusCode::~StatusCode() throw ();
             *
             * @brief   Destroys a StatusCode object.
             */

            virtual ~StatusCode() throw ();

            /**
             * @fn  const Technosoftware::Base::StatusCodes::StatusCode StatusCode::GetStatusCode() const throw ();
             *
             * @brief   Retrieves the StatusCode.
             *          
             *          For OPC DA, AE and HDA functionality this is automatically converted based on the
             *          HRESULT, see GetResultCode().
             *
             * @return  An Technosoftware::Base::StatusCodes::StatusCode.
             */

            const Technosoftware::Base::StatusCodes::StatusCode GetStatusCode() const throw ();

            /**
             * @fn  const uint32_t StatusCode::GetResultCode() const throw ();
             *
             * @brief   Retrieves the code passed to the constructor.
             *          
             *          The value is equivalent to HRESULT on Windows platforms.
             *
             * @return  An uint32_t.
             */

            const uint32_t GetResultCode() const throw ();

            /**
             * @fn  const StatusCode::StatusCodeType StatusCode::GetStatusCodeType() const throw ();
             *
             * @brief   Retrieves the type identifier of the code passed to the constructor.
             *
             * @return  An StatusCode::CodeType.
             */

            const StatusCode::StatusCodeType GetStatusCodeType() const throw ();

            /**
             * @fn  const std::string& StatusCode::ToString() throw ();
             *
             * @brief   Retrieves a text string with a description for the code stored in the StatusCode
             *          object.
             *
             * @return  This method returns the description for the code recorded within the StatusCode
             *          object. If no description text is found, then a generic message "Unknown error
             *          0x#\&lt;
             *          dwErrorCode\&gt;" is returned.
             */

            const std::string& ToString() throw ();

        protected:
            Technosoftware::Base::StatusCodes::StatusCode   statusCode_;
            uint32_t                                    resultCode_;
            StatusCodeType                              statusCodeType_;
            std::string                                 message_;
        private:
            virtual bool IsResult() const = 0;
        };

        inline StatusCode::~StatusCode() throw () {}
        inline const Technosoftware::Base::StatusCodes::StatusCode StatusCode::GetStatusCode() const throw () { return statusCode_; }
        inline const uint32_t StatusCode::GetResultCode() const throw () { return resultCode_; }
        inline const StatusCode::StatusCodeType StatusCode::GetStatusCodeType() const throw () { return statusCodeType_; }

        /**
         * @class   Status
         *
         * @brief   The Status class is the return value of most ClientSdk class member functions.
         *          
         *          Use method IsSuccess() to test the associated result code for success and method
         *          IsError() to test for error. Some functions succeeds only partially so the method
         *          IsOk() can be used to test the level of success. Most of these functions which can
         *          partly be successful has array based parameters. The documentation says if a method
         *          can partly be successful.
         *
         * @ingroup BaseOPC
         */

        class TECHNOSOFTWARE_API Status : public StatusCode
        {
        public:

            /**
             * @fn  Status::Status() throw ();
             *
             * @brief   Constructs a Status object with result code 0.
             */

            Status() throw ();

            /**
             * @fn  Status::Status(const Status& res) throw ();
             *
             * @brief   Copy constructor.
             *
             * @param   res The resource.
             */

            Status(const Status& res) throw ();

            /**
             * @fn  Status::Status(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t code, const std::string& message = NULL, FuncCallType funcCallType = SysFuncCall) throw ();
             *
             * @brief   Constructs a Status object from another Status value.
             *
             * @param   statusCode      The Technosoftware Status Code.
             * @param   code            The code returned by a system function or OPC function. The code can
             *                          be retrieved with the member function Code() and a description text can
             *                          be retrieved with the member function Description().
             * @param   message         (Optional) The message.
             * @param   funcCallType    (Optional) Specifies the type of function which has returned the
             *                          code. This parameter is used to create the code type which can be
             *                          retrieved with the member function Type().
             */

            Status(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t code, const std::string& message = NULL, FuncCallType funcCallType = SysFuncCall) throw ();

            /**
             * @fn  virtual Status::~Status() throw ();
             *
             * @brief   Destroys the object.
             */

            virtual ~Status() throw ();

            /**
             * @fn  const bool Status::IsError() const throw ();
             *
             * @brief   Indicates whether the result code represents an error value.
             *
             * @return  true if error, false if not.
             */

            const bool IsError() const throw ();

            /**
             * @fn  const bool Status::IsSuccess() const throw ();
             *
             * @brief   Indicates whether the result code represents an error free value.
             *
             * @return  true if success, false if not.
             */

            const bool IsSuccess() const throw ();

            /**
             * @fn  const bool Status::IsOk() const throw ();
             *
             * @brief   Indicates whether the result code represents a special type of an error free value.
             *          
             *          This funtion returns true if the associated result code is 0.
             *
             * @return  true if ok, false if not.
             */

            const bool IsOk() const throw ();

            /**
             * @fn  Status& Status::operator=(const Status& res) throw();
             *
             * @brief   Assigns an existing Status object to another.
             *
             * @param   res The resource.
             *
             * @return  A shallow copy of this object.
             */
            
            Status& operator =(const Status& res) throw();

            /**
             * @fn  bool Status::IsUncertain() const
             *
             * @brief   Check if the StatusCode is uncertain.
             *
             * @return  true if uncertain, false if not.
             */

            bool IsUncertain()      const { return statusCode_ == Technosoftware::Base::StatusCodes::Uncertain; }

            /**
             * @fn  bool Status::IsGood() const
             *
             * @brief   Check if the StatusCode is good.
             *
             * @return  true if good, false if not.
             */

            bool IsGood()           const { return statusCode_ == Technosoftware::Base::StatusCodes::Good; }

            /**
             * @fn  bool Status::IsBad() const
             *
             * @brief   Check if the StatusCode is bad.
             *
             * @return  true if bad, false if not.
             */

            bool IsBad()            const { return !(IsUncertain() || IsGood()); }

            /**
             * @fn  bool Status::IsNotUncertain() const
             *
             * @brief   Check if the StatusCode is not uncertain.
             *
             * @return  true if not uncertain, false if not.
             */

            bool IsNotUncertain()   const { return !IsUncertain(); }

            /**
             * @fn  bool Status::IsNotGood() const
             *
             * @brief   Check if the StatusCode is not good.
             *
             * @return  true if not good, false if not.
             */

            bool IsNotGood()        const { return !IsGood(); }

            /**
             * @fn  bool Status::IsNotBad() const
             *
             * @brief   Check if the StatusCode is not bad.
             *
             * @return  true if not bad, false if not.
             */

            bool IsNotBad()         const { return !IsBad(); }

            /**
             * @fn  const std::string& Status::ToString() throw ();
             *
             * @brief   Retrieves a text string with a description for the code stored in the StatusCode
             *          object.
             *
             * @return  This method returns the description for the code recorded within the StatusCode
             *          object. If no description text is found, then a generic message "Unknown error
             *          0x#\&lt;dwErrorCode\&gt;" is returned.
             */

            const std::string& ToString() throw ();

        private:
            bool IsResult() const { return true; }
        };

        inline Status::Status() throw () : StatusCode(Technosoftware::Base::StatusCodes::Good, 0, StatusCode::SysFuncCall) {}
        inline Status::Status(const Status& res) throw () : StatusCode(Technosoftware::Base::StatusCodes::Good, 0, StatusCode::SysFuncCall) { *this = res; }
        inline Status::Status(Technosoftware::Base::StatusCodes::StatusCode statusCode, uint32_t code, const std::string& message /* = NULL */, FuncCallType funcCallType /* = SysFuncCall */) throw () : StatusCode(statusCode, code, message, funcCallType) {}
        inline Status::~Status() throw () {}
    }
}

#endif /* TECHNOSOFTWARE_STATUS_H */
