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

#ifndef TECHNOSOFTWARE_DEBUGGER_H
#define TECHNOSOFTWARE_DEBUGGER_H

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   Debugger
         *
         * @brief   The Debugger class provides an interface to the debugger. The presence of a debugger
         *          can be checked for, messages can be written to the debugger's log window and a break
         *          into the debugger can be enforced. The methods only work if the program is compiled
         *          in debug mode (the macro _DEBUG is defined).
         *
         * @ingroup BaseCore
         */

        class TECHNOSOFTWARE_API Debugger
        {
        public:

            /**
             * @fn  static bool Debugger::IsAvailable();
             *
             * @brief   Returns true if a debugger is available, false otherwise. On Windows, this function
             *          uses the IsDebuggerPresent()
             *          function. On Unix, this function returns true if the environment variable
             *          TECHNOSOFTWARE_ENABLE_DEBUGGER is set. On OpenVMS, this function always returns true in
             *          debug, mode, false otherwise.
             *
             * @return  true if available, false if not.
             */

            static bool IsAvailable();

            /**
             * @fn  static void Debugger::WriteMessage(const std::string& msg);
             *
             * @brief   Writes a message to the debugger log, if available, otherwise to standard error
             *          output.
             *
             * @param   msg The message.
             */

            static void WriteMessage(const std::string& msg);

            /**
             * @fn  static void Debugger::WriteMessage(const std::string& msg, const char* file, int line);
             *
             * @brief   Writes a message to the debugger log, if available, otherwise to standard error
             *          output.
             *
             * @param   msg     The message.
             * @param   file    The file.
             * @param   line    The line.
             */

            static void WriteMessage(const std::string& msg, const char* file, int line);

            /**
             * @fn  static void Debugger::Enter();
             *
             * @brief   Breaks into the debugger, if it is available. On Windows, this is done using the
             *          DebugBreak() function. On Unix, the SIGINT signal is raised. On OpenVMS, the
             *          SS$_DEBUG signal is raised.
             */

            static void Enter();

            /**
             * @fn  static void Debugger::Enter(const std::string& msg);
             *
             * @brief   Writes a debug message to the debugger log and breaks into it.
             *
             * @param   msg The message.
             */

            static void Enter(const std::string& msg);

            /**
             * @fn  static void Debugger::Enter(const std::string& msg, const char* file, int line);
             *
             * @brief   Writes a debug message to the debugger log and breaks into it.
             *
             * @param   msg     The message.
             * @param   file    The file.
             * @param   line    The line.
             */

            static void Enter(const std::string& msg, const char* file, int line);

            /**
             * @fn  static void Debugger::Enter(const char* file, int line);
             *
             * @brief   Writes a debug message to the debugger log and breaks into it.
             *
             * @param   file    The file.
             * @param   line    The line.
             */

            static void Enter(const char* file, int line);
        };
    }
}

#endif /* TECHNOSOFTWARE_DEBUGGER_H */
