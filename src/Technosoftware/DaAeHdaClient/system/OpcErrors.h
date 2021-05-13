/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com 
 * 
 * Purpose: 
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef  __OCSERROR_H_14EB9DC1_6E64_11d2_88EE_00104B965F5E
#define  __OCSERROR_H_14EB9DC1_6E64_11d2_88EE_00104B965F5E

#ifdef _WIN32

      #include "inc32\opcerror.h"        // IIDs and CLSIDs for OPC Common Definitions
      #include "inc32\opcae_er.h"        // IIDs and CLSIDs for OPC Server List / Enumerator

#else

   #ifdef _WIN64

      #include "inc64\opcerror.h"        // IIDs and CLSIDs for OPC Common Definitions
      #include "inc64\opcae_er.h"        // IIDs and CLSIDs for OPC Server List / Enumerator

   #else

      #error "Platform not supported"

   #endif // _WIN64

#endif // _WIN32

#endif // __OCSERROR_H_14EB9DC1_6E64_11d2_88EE_00104B965F5E
