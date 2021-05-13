/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of various Technosoftware exception classes.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
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

#include "Base/Exception.h"
#include <typeinfo>

namespace Technosoftware
{
    namespace Base
    {
        Exception::Exception(int code) : nestedException_(0), code_(code)
        {
        }

        Exception::Exception(const std::string& msg, int code) : message_(msg), nestedException_(0), code_(code)
        {
        }

        Exception::Exception(const std::string& msg, const std::string& arg, int code) : message_(msg), nestedException_(0), code_(code)
        {
            if (!arg.empty())
            {
                message_.append(": ");
                message_.append(arg);
            }
        }

        Exception::Exception(const std::string& msg, const Exception& nested, int code) : message_(msg), nestedException_(nested.Clone()), code_(code)
        {
        }

        Exception::Exception(const Exception& exc) :
            std::exception(exc),
            message_(exc.message_),
            code_(exc.code_)
        {
            nestedException_ = exc.nestedException_ ? exc.nestedException_->Clone() : 0;
        }

        Exception::~Exception() throw()
        {
            delete nestedException_;
        }

        Exception& Exception::operator = (const Exception& exc)
        {
            if (&exc != this)
            {
                Exception* newPNested = exc.nestedException_ ? exc.nestedException_->Clone() : 0;
                delete nestedException_;
                message_ = exc.message_;
                nestedException_ = newPNested;
                code_ = exc.code_;
            }
            return *this;
        }

        const char* Exception::GetName() const throw()
        {
            return "Exception";
        }


        const char* Exception::GetClassName() const throw()
        {
            return typeid(*this).name();
        }


        const char* Exception::GetDescription() const throw()
        {
            return GetName();
        }


        std::string Exception::GetDisplayText() const
        {
            std::string txt = GetName();
            if (!message_.empty())
            {
                txt.append(": ");
                txt.append(message_);
            }
            return txt;
        }


        void Exception::GetExtendedMessage(const std::string& arg)
        {
            if (!arg.empty())
            {
                if (!message_.empty()) message_.append(": ");
                message_.append(arg);
            }
        }


        Exception* Exception::Clone() const
        {
            return new Exception(*this);
        }


        void Exception::Rethrow() const
        {
            throw *this;
        }


        TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(AssertionViolationException, LogicException, "Assertion violation")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(NullValueException, LogicException, "Null value")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(BugcheckException, LogicException, "Bugcheck")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException, "Invalid argument")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException, "Not implemented")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(IllegalStateException, LogicException, "Illegal state")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(InvalidAccessException, LogicException, "Invalid access")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(SignalException, LogicException, "Signal received")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(UnhandledException, LogicException, "Unhandled exception")

            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(RuntimeException, Exception, "Runtime exception")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException, "Not found")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException, "Exists")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException, "Timeout")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(SystemException, RuntimeException, "System exception")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(RegularExpressionException, RuntimeException, "Error in regular expression")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(LibraryLoadException, RuntimeException, "Cannot load library")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException, "Library already loaded")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(NoThreadAvailableException, RuntimeException, "No thread available")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(PropertyNotSupportedException, RuntimeException, "Property not supported")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(PoolOverflowException, RuntimeException, "Pool overflow")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException, "No permission")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(OutOfMemoryException, RuntimeException, "Out of memory")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(DataException, RuntimeException, "Data error")

            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(DataFormatException, DataException, "Bad data format")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(SyntaxException, DataException, "Syntax error")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(CircularReferenceException, DataException, "Circular reference")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(PathSyntaxException, SyntaxException, "Bad path syntax")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(IOException, RuntimeException, "I/O error")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(ProtocolException, IOException, "Protocol error")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(FileException, IOException, "File access error")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(FileExistsException, FileException, "File exists")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(FileNotFoundException, FileException, "File not found")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(PathNotFoundException, FileException, "Path not found")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(FileReadOnlyException, FileException, "File is read-only")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(FileAccessDeniedException, FileException, "Access to file denied")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(CreateFileException, FileException, "Cannot create file")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(OpenFileException, FileException, "Cannot open file")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(WriteFileException, FileException, "Cannot write file")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(ReadFileException, FileException, "Cannot read file")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(DirectoryNotEmptyException, FileException, "Directory not empty")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(UnknownURISchemeException, RuntimeException, "Unknown URI scheme")
TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(TooManyURIRedirectsException, RuntimeException, "Too many URI redirects")
TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(URISyntaxException, SyntaxException, "Bad URI syntax")

            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(ApplicationException, Exception, "Application exception")
            TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(BadCastException, RuntimeException, "Bad cast exception")


        StatusException::StatusException(const Status& status, const std::string& msg) : Exception(msg), status_(status)
        {
        }

        StatusException::StatusException(const StatusException& exc) :
            Exception(exc),
            status_(exc.status_)
        {
        }

        StatusException::~StatusException() throw()
        {
            delete this;
        }

        StatusException* StatusException::Clone() const
        {
            return new StatusException(*this);
        }
    }
}
