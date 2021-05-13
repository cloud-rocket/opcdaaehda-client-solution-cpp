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

#ifndef  __OPCSDK_H
#define  __OPCSDK_H


#ifdef _WIN32

      #include "inc32\opccomn.h"        // IIDs and CLSIDs for OPC Common Definitions
      #include "inc32\OpcEnum.h"        // IIDs and CLSIDs for OPC Server List / Enumerator
      #include "inc32\opcda.h"          // IIDs and CLSIDs for OPC Data Access
      #include "inc32\opc_ae.h"         // IIDs and CLSIDs for OPC Alarsm & Events
      #include "inc32\opcaedef.h"        // OPC Alarms & Events Definitions
      #include "inc32\opchda.h"
      #include "inc32\opchda.h"
      #include "inc32\opcerror.h"
      #include "inc32\opcae_er.h"
      #include "inc32\OpcHda_Error.h"

#else

   #ifdef _WIN64

      #include "inc64\opccomn.h"        // IIDs and CLSIDs for OPC Common Definitions
      #include "inc64\OpcEnum.h"        // IIDs and CLSIDs for OPC Server List / Enumerator
      #include "inc64\opcda.h"          // IIDs and CLSIDs for OPC Data Access
      #include "inc64\opc_ae.h"         // IIDs and CLSIDs for OPC Alarsm & Events
      #include "inc64\opcaedef.h"        // OPC Alarms & Events Definitions
      #include "inc64\opcerror.h"
      #include "inc64\opcae_er.h"
      #include "inc64\OpcHda_Error.h"

   #else

      #error "Platform not supported"

   #endif // _WIN64

#endif // _WIN32

#endif // __OPCSDK_H
