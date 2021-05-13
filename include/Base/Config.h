/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Feature configuration for the Technosoftware libraries.
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


#ifndef TECHNOSOFTWARE_CONFIG_H
#define TECHNOSOFTWARE_CONFIG_H


// Define to enable Windows Unicode (UTF-8) support
// NOTE: Compiling Technosoftware
// without TECHNOSOFTWARE_WIN32_UTF8 defined on Windows is deprecated.
#define TECHNOSOFTWARE_WIN32_UTF8


// Define to enable C++11 support
// #define TECHNOSOFTWARE_ENABLE_CPP11


// Define to disable implicit linking
// #define TECHNOSOFTWARE_NO_AUTOMATIC_LIBS


// Define to disable automatic initialization
// Defining this will disable ALL automatic 
// initialization framework-wide (e.g. Net
// on Windows, all Data back-ends, etc).
// 
// #define TECHNOSOFTWARE_NO_AUTOMATIC_LIB_INIT


// Define to disable FPEnvironment support
// #define TECHNOSOFTWARE_NO_FPENVIRONMENT


// Define if std::wstring is not available
// #define TECHNOSOFTWARE_NO_WSTRING


// Define to disable shared memory
// #define TECHNOSOFTWARE_NO_SHAREDMEMORY


// Define if no <locale> header is available (such as on WinCE)
// #define TECHNOSOFTWARE_NO_LOCALE


// Define to desired default thread stack size
// Zero means OS default
#ifndef TECHNOSOFTWARE_THREAD_STACK_SIZE
    #define TECHNOSOFTWARE_THREAD_STACK_SIZE 0
#endif


// Define to override system-provided
// minimum thread priority value on POSIX
// platforms (returned by Technosoftware::Thread::getMinOSPriority()).
// #define TECHNOSOFTWARE_THREAD_PRIORITY_MIN 0


// Define to override system-provided
// maximum thread priority value on POSIX
// platforms (returned by Technosoftware::Thread::getMaxOSPriority()).
// #define TECHNOSOFTWARE_THREAD_PRIORITY_MAX 31


// Define to disable small object optimization. If not 
// defined, Any and Dynamic::Var (and similar optimization
// candidates) will be auto-allocated on the stack in 
// cases when value holder fits into TECHNOSOFTWARE_SMALL_OBJECT_SIZE
// (see below).
// 
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! NOTE: Any/Dynamic::Var SOO will NOT work reliably   !!!
// !!! without C++11 (std::aligned_storage in particular). !!!
// !!! Only comment this out if your compiler has support  !!!
// !!! for std::aligned_storage.                           !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
#ifndef TECHNOSOFTWARE_ENABLE_SOO
#define TECHNOSOFTWARE_NO_SOO
#endif


// Small object size in bytes. When assigned to Any or Var,
// objects larger than this value will be alocated on the heap,
// while those smaller will be placement new-ed into an
// internal buffer.
#if !defined(TECHNOSOFTWARE_SMALL_OBJECT_SIZE) && !defined(TECHNOSOFTWARE_NO_SOO)
    #define TECHNOSOFTWARE_SMALL_OBJECT_SIZE 32
#endif


// Define to disable compilation of DirectoryWatcher
// on platforms with no inotify.
// #define TECHNOSOFTWARE_NO_INOTIFY


// Following are options to remove certain features
// to reduce library/executable size for smaller
// embedded platforms. By enabling these options,
// the size of a statically executable can be
// reduced by a few 100 Kbytes.


// No automatic registration of FileChannel in
// LoggingFactory - avoids FileChannel and friends 
// being linked to executable.
// #define TECHNOSOFTWARE_NO_FILECHANNEL


// No automatic registration of SplitterChannel in
// LoggingFactory - avoids SplitterChannel being
// linked to executable.
// #define TECHNOSOFTWARE_NO_SPLITTERCHANNEL


// No automatic registration of SyslogChannel in
// LoggingFactory - avoids SyslogChannel being
// linked to executable on Unix/Linux systems.
// #define TECHNOSOFTWARE_NO_SYSLOGCHANNEL


// Define to enable MSVC secure warnings
// #define TECHNOSOFTWARE_MSVC_SECURE_WARNINGS


// No support for INI file configurations in
// Technosoftware::Util::Application.
// #define TECHNOSOFTWARE_UTIL_NO_INIFILECONFIGURATION


// No support for JSON configuration in 
// Technosoftware::Util::Application. Avoids linking of JSON
// library and saves a few 100 Kbytes.
// #define TECHNOSOFTWARE_UTIL_NO_JSONCONFIGURATION


// No support for XML configuration in 
// Technosoftware::Util::Application. Avoids linking of XML
// library and saves a few 100 Kbytes.
// #define TECHNOSOFTWARE_UTIL_NO_XMLCONFIGURATION


// No IPv6 support
// Define to disable IPv6
// #define TECHNOSOFTWARE_NET_NO_IPv6


// Windows CE has no locale support
#if defined(_WIN32_WCE)
    #define TECHNOSOFTWARE_NO_LOCALE
#endif


// Enable the technosoftware_debug_* and technosoftware_trace_* macros
// even if the _DEBUG variable is not set.
// This allows the use of these macros in a release version.
// #define TECHNOSOFTWARE_LOG_DEBUG



//
// OpenSSL options
//

// Poco has its own OpenSSL build system.
// See https://github.com/pocoproject/openssl/blob/master/README.md
// for details
//
// These options are Windows only.

// Disable the use of Poco OpenSSL binaries
// (external OpenSSL libraries must be provided).
// #define POCO_EXTERNAL_OPENSSL

//
// End OpenSSL options
//


// Define to prevent changing the suffix for shared libraries
// to "d.so", "d.dll", etc. for _DEBUG builds in Poco::SharedLibrary.
// #define TECHNOSOFTWARE_NO_SHARED_LIBRARY_DEBUG_SUFFIX

#endif /* TECHNOSOFTWARE_CONFIG_H */
