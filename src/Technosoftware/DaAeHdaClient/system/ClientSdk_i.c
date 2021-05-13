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



#ifndef  TECHNOSOFTWARE_CLIENTSDK_I_C_
#define  TECHNOSOFTWARE_CLIENTSDK_I_C_

#ifdef _WIN32

      #include "Classic/inc32/opccomn_i.c"         // IIDs and CLSIDs for OPC Common Definitions
      #include "Classic/inc32/OpcEnum_i.c"         // IIDs and CLSIDs for OPC Server List / Enumerator
      #include "Classic/inc32/opcda_i.c"           // IIDs and CLSIDs for OPC Data Access
      #include "Classic/inc32/opc_ae_i.c"          // IIDs and CLSIDs for OPC Alarsm & Events
	  #include "Classic/inc32/opchda_i.c"          // IIDs and CLSIDs for OPC Historical Data Access

#else

   #ifdef _WIN64

      #include "Classic/inc64/opccomn_i.c"         // IIDs and CLSIDs for OPC Common Definitions
      #include "Classic/inc64/OpcEnum_i.c"         // IIDs and CLSIDs for OPC Server List / Enumerator
      #include "Classic/inc64/opcda_i.c"           // IIDs and CLSIDs for OPC Data Access
      #include "Classic/inc64/opc_ae_i.c"          // IIDs and CLSIDs for OPC Alarsm & Events
  	  #include "Classic/inc64/opchda_i.c"          // IIDs and CLSIDs for OPC Historical Data Access

   #else

      #error "Platform not supported"

   #endif // _WIN64

#endif // _WIN32
#endif // TECHNOSOFTWARE_CLIENTSDK_I_C_
