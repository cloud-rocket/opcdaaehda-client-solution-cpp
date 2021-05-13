/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com 
 * 
 * Purpose: 
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef  __OCSTK_H_230AC692_5F6C_11d2_88DD_00104B965F5E
#define  __OCSTK_H_230AC692_5F6C_11d2_88DD_00104B965F5E

#ifdef _WIN32

      #include "inc32\opccomn.h"        // IIDs and CLSIDs for OPC Common Definitions
      #include "inc32\OpcEnum.h"        // IIDs and CLSIDs for OPC Server List / Enumerator
      #include "inc32\opcda.h"          // IIDs and CLSIDs for OPC Data Access
      #include "inc32\opc_ae.h"         // IIDs and CLSIDs for OPC Alarsm & Events
      #include "inc32\opcda.h"          // IIDs and CLSIDs for OPC Data Access
      #include "inc32\opcaedef.h"        // OPC Alarms & Events Definitions
      #include "inc32\opchda.h"         // IIDs and CLSIDs for OPC Historical Data Access
      #include "inc32\OpcHda_Error.h"   // Errors for OPC Historical Data Access
#else

   #ifdef _WIN64

      #include "inc64\opccomn.h"        // IIDs and CLSIDs for OPC Common Definitions
      #include "inc64\OpcEnum.h"        // IIDs and CLSIDs for OPC Server List / Enumerator
      #include "inc64\opcda.h"          // IIDs and CLSIDs for OPC Data Access
      #include "inc64\opc_ae.h"         // IIDs and CLSIDs for OPC Alarsm & Events
      #include "inc64\opcaedef.h"        // OPC Alarms & Events Definitions
      #include "inc64\opchda.h"         // IIDs and CLSIDs for OPC Historical Data Access
      #include "inc64\OpcHda_Error.h"   // Errors for OPC Historical Data Access

   #else

      #error "Platform not supported"

   #endif // _WIN64

#endif // _WIN32

#endif // __OCSTK_H_230AC692_5F6C_11d2_88DD_00104B965F5E
