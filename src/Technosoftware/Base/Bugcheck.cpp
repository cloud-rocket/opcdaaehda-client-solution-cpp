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

#include "Base/Bugcheck.h"
#include "Base/Debugger.h"
#include "Base/Exception.h"
#include <sstream>

namespace Technosoftware
{
    namespace Base
    {
        void Bugcheck::Assertion(const char* cond, const char* file, int line, const char* text)
        {
            std::string message("Assertion violation: ");
            message += cond;
            if (text)
            {
                message += " (";
                message += text;
                message += ")";
            }
            Debugger::Enter(message, file, line);
            throw AssertionViolationException(what(cond, file, line, text));
        }


        void Bugcheck::NullPointer(const char* ptr, const char* file, int line)
        {
            Debugger::Enter(std::string("NULL pointer: ") + ptr, file, line);
            throw NullPointerException(what(ptr, file, line));
        }


        void Bugcheck::InternalError(const char* file, int line)
        {
            Debugger::Enter("Bugcheck", file, line);
            throw BugcheckException(what(0, file, line));
        }


        void Bugcheck::InternalError(const char* msg, const char* file, int line)
        {
            std::string m("Bugcheck");
            if (msg)
            {
                m.append(": ");
                m.append(msg);
            }
            Debugger::Enter(m, file, line);
            throw BugcheckException(what(msg, file, line));
        }


        void Bugcheck::Unexpected(const char* file, int line)
        {
#ifdef _DEBUG
            try
            {
                std::string msg("Unexpected exception in noexcept function or destructor: ");
                try
                {
                    throw;
                }
                catch (Base::Exception& exc)
                {
                    msg += exc.GetDisplayText();
                }
                catch (std::exception& exc)
                {
                    msg += exc.what();
                }
                catch (...)
                {
                    msg += "unknown exception";
                }
                Debugger::Enter(msg, file, line);
            }
            catch (...)
            {
            }
#endif    
        }


        void Bugcheck::Debugger(const char* file, int line)
        {
            Debugger::Enter(file, line);
        }


        void Bugcheck::Debugger(const char* msg, const char* file, int line)
        {
            Debugger::Enter(msg, file, line);
        }


        std::string Bugcheck::what(const char* msg, const char* file, int line, const char* text)
        {
            std::ostringstream str;
            if (msg) str << msg << " ";
            if (text != NULL) str << "(" << text << ") ";
            str << "in file \"" << file << "\", line " << line;
            return str.str();
        }
    }

}
