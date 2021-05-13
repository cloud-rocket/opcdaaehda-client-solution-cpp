/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Bugcheck class and the self-testing macros.
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

#ifndef TECHNOSOFTWARE_BUGCHECK_H
#define TECHNOSOFTWARE_BUGCHECK_H


#include "Base/Base.h"
#include <string>
#include <cstdlib>
#if defined(_DEBUG)
#    include <iostream>
#endif


namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   Bugcheck
         *
         * @brief   This class provides some static methods that are used by the technosoftware_assert_dbg(),
         *          technosoftware_assert(), technosoftware_check_ptr(), technosoftware_bugcheck() and
         *          technosoftware_unexpected() macros. You should not invoke these methods directly. Use the
         *          macros instead, as they automatically provide useful context information.
         *
         * @ingroup BaseCore
         */

        class TECHNOSOFTWARE_API Bugcheck
        {
        public:

            /**
             * @fn  static void Bugcheck::Assertion(const char* cond, const char* file, int line, const char* text = 0);
             *
             * @brief   An assertion failed. Break into the debugger, if possible, then throw an
             *          AssertionViolationException.
             *
             * @param   cond    The condition.
             * @param   file    The file.
             * @param   line    The line.
             * @param   text    (Optional) the text.
             */

            static void Assertion(const char* cond, const char* file, int line, const char* text = 0);

            /**
             * @fn  static void Bugcheck::NullPointer(const char* ptr, const char* file, int line);
             *
             * @brief   An null pointer was encountered. Break into the debugger, if possible, then throw an
             *          NullPointerException.
             *
             * @param   ptr     The pointer.
             * @param   file    The file.
             * @param   line    The line.
             */

            static void NullPointer(const char* ptr, const char* file, int line);

            /**
             * @fn  static void Bugcheck::InternalError(const char* file, int line);
             *
             * @brief   An internal error was encountered. Break into the debugger, if possible, then throw
             *          an BugcheckException.
             *
             * @param   file    The file.
             * @param   line    The line.
             */

            static void InternalError(const char* file, int line);

            /**
             * @fn  static void Bugcheck::InternalError(const char* msg, const char* file, int line);
             *
             * @brief   An internal error was encountered. Break into the debugger, if possible, then throw
             *          an BugcheckException.
             *
             * @param   msg     The message.
             * @param   file    The file.
             * @param   line    The line.
             */

            static void InternalError(const char* msg, const char* file, int line);

            /**
             * @fn  static void Bugcheck::Unexpected(const char* file, int line);
             *
             * @brief   An exception was caught in a destructor. Break into debugger, if possible and report
             *          exception. Must only be called from within a catch () block as it rethrows the
             *          exception to determine its class.
             *
             * @param   file    The file.
             * @param   line    The line.
             */

            static void Unexpected(const char* file, int line);

            /**
             * @fn  static void Bugcheck::Debugger(const char* file, int line);
             *
             * @brief   An internal error was encountered. Break into the debugger, if possible.
             *
             * @param   file    The file.
             * @param   line    The line.
             */

            static void Debugger(const char* file, int line);

            /**
             * @fn  static void Bugcheck::Debugger(const char* msg, const char* file, int line);
             *
             * @brief   An internal error was encountered. Break into the debugger, if possible.
             *
             * @param   msg     The message.
             * @param   file    The file.
             * @param   line    The line.
             */

            static void Debugger(const char* msg, const char* file, int line);

        protected:
            static std::string what(const char* msg, const char* file, int line, const char* text = 0);
        };
    }
}

//
// useful macros (these automatically supply line number and file name)
//
#if defined(__KLOCWORK__) || defined(__clang_analyzer__)


// Short-circuit these macros when under static analysis.
// Ideally, static analysis tools should understand and reason correctly about
// noreturn methods such as Bugcheck::bugcheck(). In practice, they don't.
// Help them by turning these macros into std::abort() as described here:
// https://developer.klocwork.com/documentation/en/insight/10-1/tuning-cc-analysis#Usingthe__KLOCWORK__macro

#include <cstdlib> // for abort
#define technosoftware_assert_dbg(cond)           do { if (!(cond)) std::abort(); } while (0)
#define technosoftware_assert_msg_dbg(cond, text) do { if (!(cond)) std::abort(); } while (0)
#define technosoftware_assert(cond)               do { if (!(cond)) std::abort(); } while (0)
#define technosoftware_assert_msg(cond, text)     do { if (!(cond)) std::abort(); } while (0)
#define technosoftware_check_ptr(ptr)             do { if (!(ptr)) std::abort(); } while (0)
#define technosoftware_bugcheck()                 do { std::abort(); } while (0)
#define technosoftware_bugcheck_msg(msg)          do { std::abort(); } while (0)


#else // defined(__KLOCWORK__) || defined(__clang_analyzer__)


#if defined(_DEBUG)
#define technosoftware_assert_dbg(cond) \
        if (!(cond)) Technosoftware::Base::Bugcheck::Assertion(#cond, __FILE__, __LINE__); else (void) 0

#define technosoftware_assert_msg_dbg(cond, text) \
        if (!(cond)) Technosoftware::Base::Bugcheck::Assertion(#cond, __FILE__, __LINE__, text); else (void) 0
#else
#define technosoftware_assert_msg_dbg(cond, text)
#define technosoftware_assert_dbg(cond)
#endif


#define technosoftware_assert(cond) \
    if (!(cond)) Technosoftware::Base::Bugcheck::Assertion(#cond, __FILE__, __LINE__); else (void) 0


#define technosoftware_assert_msg(cond, text) \
    if (!(cond)) Technosoftware::Base::Bugcheck::Assertion(#cond, __FILE__, __LINE__, text); else (void) 0


#define technosoftware_check_ptr(ptr) \
    if (!(ptr)) Technosoftware::Base::Bugcheck::NullPointer(#ptr, __FILE__, __LINE__); else (void) 0


#define technosoftware_bugcheck() \
    Technosoftware::Base::Bugcheck::InternalError(__FILE__, __LINE__)


#define technosoftware_bugcheck_msg(msg) \
    Technosoftware::Base::Bugcheck::InternalError(msg, __FILE__, __LINE__)


#endif // defined(__KLOCWORK__) || defined(__clang_analyzer__)


#define technosoftware_unexpected() \
    Technosoftware::Base::Bugcheck::Unexpected(__FILE__, __LINE__);


#define technosoftware_debugger() \
    Technosoftware::Base::Bugcheck::Debugger(__FILE__, __LINE__)


#define technosoftware_debugger_msg(msg) \
    Technosoftware::Base::Bugcheck::Debugger(msg, __FILE__, __LINE__)


#if defined(_DEBUG)
#    define technosoftware_stdout_dbg(outstr) \
    std::cout << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#    define technosoftware_stdout_dbg(outstr)
#endif


#if defined(_DEBUG)
#    define technosoftware_stderr_dbg(outstr) \
        std::cerr << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#    define technosoftware_stderr_dbg(outstr)
#endif


//
// technosoftware_static_assert
//
// The following was ported from <boost/static_assert.hpp>
//


template <bool x>
struct TECHNOSOFTWARE_STATIC_ASSERTION_FAILURE;


template <>
struct TECHNOSOFTWARE_STATIC_ASSERTION_FAILURE<true>
{
	enum
	{
		value = 1
	};
};


template <int x> 
struct technosoftware_static_assert_test
{
};


#if defined(__GNUC__) && (__GNUC__ == 3) && ((__GNUC_MINOR__ == 3) || (__GNUC_MINOR__ == 4))
#define technosoftware_static_assert(B) \
	typedef char TECHNOSOFTWARE_JOIN(technosoftware_static_assert_typedef_, __LINE__) \
        [TECHNOSOFTWARE_STATIC_ASSERTION_FAILURE<(bool) (B)>::value]
#else
#define technosoftware_static_assert(B) \
	typedef technosoftware_static_assert_test<sizeof(TECHNOSOFTWARE_STATIC_ASSERTION_FAILURE<(bool) (B)>)> \
		TECHNOSOFTWARE_JOIN(technosoftware_static_assert_typedef_, __LINE__) TECHNOSOFTWARE_UNUSED
#endif


#endif /* TECHNOSOFTWARE_BUGCHECK_H */
