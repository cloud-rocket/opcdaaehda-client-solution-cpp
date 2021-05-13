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

#ifndef TECHNOSOFTWARE_EXCEPTION_H
#define TECHNOSOFTWARE_EXCEPTION_H

#include "Base/Base.h"
#include "Base/Status.h"

#include <stdexcept>

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   Exception
         *
         * @brief   This is the base class for all exceptions defined in the Technosoftware class library.
         *
         * @ingroup BaseCore
         */

        class TECHNOSOFTWARE_API Exception : public std::exception
        {
        public:
            /**
             * @fn  Exception::Exception(const std::string& msg, int code = 0);
             *
             * @brief   Creates an exception.
             *
             * @param   msg     The message.
             * @param   code    (Optional) the code.
             */

            Exception(const std::string& msg, int code = 0);

            /**
             * @fn  Exception::Exception(const std::string& msg, const std::string& arg, int code = 0);
             *
             * @brief   Creates an exception.
             *
             * @param   msg     The message.
             * @param   arg     The argument.
             * @param   code    (Optional) the code.
             */

            Exception(const std::string& msg, const std::string& arg, int code = 0);

            /**
             * @fn  Exception::Exception(const std::string& msg, const Exception& nested, int code = 0);
             *
             * @brief   Creates an exception and stores a clone of the nested exception.
             *
             * @param   msg     The message.
             * @param   nested  The nested.
             * @param   code    (Optional) the code.
             */

            Exception(const std::string& msg, const Exception& nested, int code = 0);

            /**
             * @fn  Exception::Exception(const Exception& exception);
             *
             * @brief   Copy constructor.
             *
             * @param   exception   The exception.
             */

            Exception(const Exception& exception);

            /**
             * @fn  Exception::~Exception() throw();
             *
             * @brief   Destroys the exception and deletes the nested exception.
             */

            ~Exception() throw();

            /**
             * @fn  Exception& Exception::operator= (const Exception& exc);
             *
             * @brief   Assignment operator.
             *
             * @param   exc The exc.
             *
             * @return  A shallow copy of this object.
             */

            Exception& operator = (const Exception& exc);

            /**
             * @fn  virtual const char* Exception::GetName() const throw();
             *
             * @brief   Returns a static string describing the exception.
             *
             * @return  null if it fails, else the name.
             */

            virtual const char* GetName() const throw();

            /**
             * @fn  virtual const char* Exception::GetClassName() const throw();
             *
             * @brief   Returns the name of the exception class.
             *
             * @return  null if it fails, else the class name.
             */

            virtual const char* GetClassName() const throw();

            /**
             * @fn  virtual const char* Exception::GetDescription() const throw();
             *
             * @brief   Returns a static string describing the exception.
             *          
             *          Same as GetName(), but for compatibility with std::exception.
             *
             * @return  null if it fails, else the description.
             */

            virtual const char* GetDescription() const throw();

            /**
             * @fn  const Exception* Exception::GetNested() const;
             *
             * @brief   Returns a pointer to the nested exception, or null if no nested exception exists.
             *
             * @return  null if it fails, else the nested.
             */

            const Exception* GetNested() const;

            /**
             * @fn  const std::string& Exception::GetMessage() const;
             *
             * @brief   Returns the message text.
             *
             * @return  The message.
             */

            const std::string& GetMessage() const;

            /**
             * @fn  int Exception::GetCode() const;
             *
             * @brief   Returns the exception code if defined.
             *
             * @return  The code.
             */

            int GetCode() const;

            /**
             * @fn  std::string Exception::GetDisplayText() const;
             *
             * @brief   Returns a string consisting of the message name and the message text.
             *
             * @return  The display text.
             */

            std::string GetDisplayText() const;

            /**
             * @fn  virtual Exception* Exception::Clone() const;
             *
             * @brief   Creates an exact copy of the exception.
             *          
             *          The copy can later be thrown again by invoking rethrow() on it.
             *
             * @return  null if it fails, else a copy of this object.
             */

            virtual Exception* Clone() const;

            /**
             * @fn  virtual void Exception::Rethrow() const;
             *
             * @brief   (Re)Throws the exception.
             *          
             *          This is useful for temporarily storing a copy of an exception (see clone()), then
             *          throwing it again.
             */

            virtual void Rethrow() const;

        protected:

            /**
             * @fn  Exception::Exception(int code = 0);
             *
             * @brief   Standard constructor.
             *
             * @param   code    (Optional) the code.
             */

            Exception(int code = 0);

            /**
             * @fn  void Exception::GetMessage(const std::string& msg);
             *
             * @brief   Gets the message for the exception.
             *
             * @param   msg The message.
             */

            void GetMessage(const std::string& msg);

            /**
             * @fn  void Exception::GetExtendedMessage(const std::string& arg);
             *
             * @brief   Gets the extended message for the exception.
             *
             * @param   arg The argument.
             */

            void GetExtendedMessage(const std::string& arg);

        private:
            std::string     message_;
            Exception*      nestedException_;
            int             code_;
        };


        //
        // inlines
        //
        inline const Exception* Exception::GetNested() const
        {
            return nestedException_;
        }


        inline const std::string& Exception::GetMessage() const
        {
            return message_;
        }


        inline void Exception::GetMessage(const std::string& msg)
        {
            message_ = msg;
        }


        inline int Exception::GetCode() const
        {
            return code_;
        }

/**
 * @def TECHNOSOFTWARE_DECLARE_EXCEPTION_CODE(API, CLS, BASE, CODE)
 *
 * @brief   Macros for quickly declaring and implementing exception classes. Unfortunately, we
 *          cannot use a template here because character pointers (which we need for specifying
 *          the exception name) are not allowed as template arguments.
 *
 * @param   API     The API.
 * @param   CLS     The cls.
 * @param   BASE    The base.
 * @param   CODE    The code.
 */

#define TECHNOSOFTWARE_DECLARE_EXCEPTION_CODE(API, CLS, BASE, CODE)                                     \
    class API CLS: public BASE                                                                      \
    {                                                                                               \
    public:                                                                                         \
        CLS(int code = CODE);                                                                       \
        CLS(const std::string& msg, int code = CODE);                                               \
        CLS(const std::string& msg, const std::string& arg, int code = CODE);                       \
        CLS(const std::string& msg, const Base::Exception& exc, int code = CODE);                   \
        CLS(const CLS& exc);                                                                        \
        ~CLS() throw();                                                                             \
        CLS& operator = (const CLS& exc);                                                           \
        const char* GetName() const throw();                                                        \
        const char* GetClassName() const throw();                                                   \
        Base::Exception* Clone() const;                                                             \
        void Rethrow() const;                                                                       \
    };

#define TECHNOSOFTWARE_DECLARE_EXCEPTION(API, CLS, BASE) \
    TECHNOSOFTWARE_DECLARE_EXCEPTION_CODE(API, CLS, BASE, 0)

#define TECHNOSOFTWARE_IMPLEMENT_EXCEPTION(CLS, BASE, NAME)                                             \
    CLS::CLS(int code): BASE(code)                                                                  \
    {                                                                                               \
    }                                                                                               \
    CLS::CLS(const std::string& msg, int code): BASE(msg, code)                                     \
    {                                                                                               \
    }                                                                                               \
    CLS::CLS(const std::string& msg, const std::string& arg, int code): BASE(msg, arg, code)        \
    {                                                                                               \
    }                                                                                               \
    CLS::CLS(const std::string& msg, const Base::Exception& exc, int code): BASE(msg, exc, code)    \
    {                                                                                               \
    }                                                                                               \
    CLS::CLS(const CLS& exc): BASE(exc)                                                             \
    {                                                                                               \
    }                                                                                               \
    CLS::~CLS() throw()                                                                             \
    {                                                                                               \
    }                                                                                               \
    CLS& CLS::operator = (const CLS& exc)                                                           \
    {                                                                                               \
        BASE::operator = (exc);                                                                     \
        return *this;                                                                               \
    }                                                                                               \
    const char* CLS::GetName() const throw()                                                        \
    {                                                                                               \
        return NAME;                                                                                \
    }                                                                                               \
    const char* CLS::GetClassName() const throw()                                                   \
    {                                                                                               \
        return typeid(*this).name();                                                                \
    }                                                                                               \
    Base::Exception* CLS::Clone() const                                                             \
    {                                                                                               \
        return new CLS(*this);                                                                      \
    }                                                                                               \
    void CLS::Rethrow() const                                                                       \
    {                                                                                               \
        throw *this;                                                                                \
    }


//
// Standard exception classes
//
        TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, LogicException, Exception)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, AssertionViolationException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, NullPointerException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, NullValueException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, BugcheckException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, InvalidArgumentException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, NotImplementedException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, RangeException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, IllegalStateException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, InvalidAccessException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, SignalException, LogicException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, UnhandledException, LogicException)

            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, RuntimeException, Exception)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, NotFoundException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, ExistsException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, TimeoutException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, SystemException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, RegularExpressionException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, LibraryLoadException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, LibraryAlreadyLoadedException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, NoThreadAvailableException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, PropertyNotSupportedException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, PoolOverflowException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, NoPermissionException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, OutOfMemoryException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, DataException, RuntimeException)

            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, DataFormatException, DataException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, SyntaxException, DataException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, CircularReferenceException, DataException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, PathSyntaxException, SyntaxException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, IOException, RuntimeException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, ProtocolException, IOException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, FileException, IOException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, FileExistsException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, FileNotFoundException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, PathNotFoundException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, FileReadOnlyException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, FileAccessDeniedException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, CreateFileException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, OpenFileException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, WriteFileException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, ReadFileException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, DirectoryNotEmptyException, FileException)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, UnknownURISchemeException, RuntimeException)
TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, TooManyURIRedirectsException, RuntimeException)
TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, URISyntaxException, SyntaxException)

            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, ApplicationException, Exception)
            TECHNOSOFTWARE_DECLARE_EXCEPTION(TECHNOSOFTWARE_API, BadCastException, RuntimeException)

        /**
         * @class   StatusException
         *
         * @brief   This is the base class for all OPC Status exceptions defined in the Technosoftware class
         *          library.
         *
         * “ingroup  BaseCore
         */

        class TECHNOSOFTWARE_API StatusException : public Technosoftware::Base::Exception
        {
        public:

            /**
             * @fn  StatusException::StatusException(const Status& status, const std::string& msg = "OPC Status Exception");
             *
             * @brief   Creates an exception.
             *
             * @param   status  The status.
             * @param   msg     (Optional) The message.
             */

            StatusException(const Status& status, const std::string& msg = "OPC Status Exception");

            /**
             * @fn  StatusException::StatusException(const StatusException& exception);
             *
             * @brief   Copy constructor.
             *
             * @param   exception   The exception.
             */

            StatusException(const StatusException& exception);

            /**
             * @fn  StatusException::~StatusException() throw();
             *
             * @brief   Destroys the exception and deletes the nested exception.
             */

            ~StatusException() throw();

            /**
             * @fn  StatusException& StatusException::operator= (const StatusException& exc);
             *
             * @brief   Assignment operator.
             *
             * @param   exc The exc.
             *
             * @return  A shallow copy of this object.
             */

            StatusException& operator = (const StatusException& exc);
            
            virtual StatusException* Clone() const;

            /**
             * @fn  Status StatusException::GetStatus() const;
             *
             * @brief   Returns the exception code if defined.
             *
             * @return  The Status.
             */

            Status GetStatus() const;

        protected:

        private:
            Status          status_;
        };

        //
        // inlines
        //        
        inline Status StatusException::GetStatus() const
        {
            return status_;
        }
    }
}

#endif /* TECHNOSOFTWARE_EXCEPTION_H */
