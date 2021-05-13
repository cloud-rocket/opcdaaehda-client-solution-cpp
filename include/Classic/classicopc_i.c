/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com 
 * 
 * Purpose: 
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement, 
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef  __OPCSDK_I_C_
#define  __OPCSDK_I_C_

#ifdef _WIN32

      #include "inc32\opccomn_i.c"         // IIDs and CLSIDs for OPC Common Definitions
      #include "inc32\opcda_i.c"           // IIDs and CLSIDs for OPC Data Access
      #include "inc32\opc_ae_i.c"          // IIDs and CLSIDs for OPC Alarms & Events
      #include "inc32\opchda_i.c"          // IIDs and CLSIDs for OPC Historical Data Access
#else

   #ifdef _WIN64

      #include "inc64\opccomn_i.c"         // IIDs and CLSIDs for OPC Common Definitions
      #include "inc64\OpcEnum_i.c"         // IIDs and CLSIDs for OPC Server List / Enumerator
      #include "inc64\opcda_i.c"           // IIDs and CLSIDs for OPC Data Access
      #include "inc64\opc_ae_i.c"          // IIDs and CLSIDs for OPC Alarsm & Events

   #else

      #error "Platform not supported"

   #endif // _WIN64

#endif // _WIN32
#endif // __OPCSDK_I_C_
