/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Platform and architecture identification macros
 * and platform-specific definitions for various POSIX platforms
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_PLATFORM_POSIX_H
#define TECHNOSOFTWARE_PLATFORM_POSIX_H


//
// PA-RISC based HP-UX platforms have some issues...
//
#if defined(hpux) || defined(_hpux)
    #if defined(__hppa) || defined(__hppa__)
        #define TECHNOSOFTWARE_NO_SYS_SELECT_H 1
        #if defined(__HP_aCC)
            #define TECHNOSOFTWARE_NO_TEMPLATE_ICOMPARE 1
        #endif
    #endif
#endif


//
// Thread-safety of local static initialization
//
#if __cplusplus >= 201103L || __GNUC__ >= 4 || defined(__clang__)
    #ifndef TECHNOSOFTWARE_LOCAL_STATIC_INIT_IS_THREADSAFE
        #define TECHNOSOFTWARE_LOCAL_STATIC_INIT_IS_THREADSAFE 1
    #endif
#endif


//
// No syslog.h on QNX/BB10
//
#if defined(__QNXNTO__)
    #define TECHNOSOFTWARE_NO_SYSLOGCHANNEL
#endif


#endif /* TECHNOSOFTWARE_PLATFORM_POSIX_H */
