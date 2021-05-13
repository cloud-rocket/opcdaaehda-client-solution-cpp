/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Debugger class.
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

#include "Base/Debugger.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>
#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#include "Base/UnWindows.h"
#elif defined(TECHNOSOFTWARE_OS_FAMILY_UNIX) && !defined(TECHNOSOFTWARE_VXWORKS)
#include <unistd.h>
#include <signal.h>
#elif defined(TECHNOSOFTWARE_OS_FAMILY_VMS)
#include <lib$routines.h>
#include <ssdef.h>
#endif
#if defined(TECHNOSOFTWARE_WIN32_UTF8) && !defined(TECHNOSOFTWARE_NO_WSTRING)
#include "Base/UnicodeConverter.h"
#endif


// NOTE: In this module, we use the C library functions (fputs) for,
// output since, at the time we're called, the C++ iostream objects std::cout, etc.
// might not have been initialized yet.


namespace Technosoftware
{
    namespace Base
    {
        bool Debugger::IsAvailable()
        {
#if defined(_DEBUG)
#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#if defined(_WIN32_WCE)
#if (_WIN32_WCE >= 0x600)
            BOOL isDebuggerPresent;
            if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &isDebuggerPresent))
            {
                return isDebuggerPresent ? true : false;
            }
            return false;
#else
            return false;
#endif
#else
            return IsDebuggerPresent() ? true : false;
#endif
#elif defined(TECHNOSOFTWARE_VXWORKS)
            return false;
#elif defined(TECHNOSOFTWARE_OS_FAMILY_UNIX)
            return std::getenv("TECHNOSOFTWARE_ENABLE_DEBUGGER") ? true : false;
#elif defined(TECHNOSOFTWARE_OS_FAMILY_VMS)
            return true;
#endif
#else
            return false;
#endif
        }


        void Debugger::WriteMessage(const std::string& msg)
        {
#if defined(_DEBUG)
            std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
            std::fputs(msg.c_str(), stderr);
            std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
            if (IsAvailable())
            {
#if defined(TECHNOSOFTWARE_WIN32_UTF8) && !defined(TECHNOSOFTWARE_NO_WSTRING)
                std::wstring umsg;
                UnicodeConverter::toUTF16(msg, umsg);
                umsg += '\n';
                OutputDebugStringW(umsg.c_str());
#else
                OutputDebugStringA(msg.c_str());
                OutputDebugStringA("\n");
#endif
            }
#elif defined(TECHNOSOFTWARE_OS_FAMILY_UNIX)
#elif defined(TECHNOSOFTWARE_OS_FAMILY_VMS)
#endif
#endif
        }


        void Debugger::WriteMessage(const std::string& msg, const char* file, int line)
        {
#if defined(_DEBUG)
            std::ostringstream str;
            str << msg << " [in file \"" << file << "\", line " << line << "]";
            WriteMessage(str.str());
#endif
        }


        void Debugger::Enter()
        {
#if defined(_DEBUG)
#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
            if (IsAvailable())
            {
                DebugBreak();
            }
#elif defined(TECHNOSOFTWARE_VXWORKS)
            {
                // not supported
            }
#elif defined(TECHNOSOFTWARE_OS_FAMILY_UNIX)
            if (IsAvailable())
            {
                kill(getpid(), SIGINT);
            }
#elif defined(TECHNOSOFTWARE_OS_FAMILY_VMS)
            {
                const char* cmd = "\012SHOW CALLS";
                lib$signal(SS$_DEBUG, 1, cmd);
            }
#endif
#endif
        }


        void Debugger::Enter(const std::string& msg)
        {
#if defined(_DEBUG)
            WriteMessage(msg);
            Enter();
#endif
        }


        void Debugger::Enter(const std::string& msg, const char* file, int line)
        {
#if defined(_DEBUG)
            WriteMessage(msg, file, line);
            Enter();
#endif
        }


        void Debugger::Enter(const char* file, int line)
        {
#if defined(_DEBUG)
            WriteMessage("BREAK", file, line);
            Enter();
#endif
        }
    }
}

