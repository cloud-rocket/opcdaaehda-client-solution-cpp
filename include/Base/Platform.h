/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Platform and architecture identification macros.
 *
 * NOTE: This file may be included from both C++ and C code, so it
 *       must not contain any C++ specific things.
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


#ifndef TECHNOSOFTWARE_PLATFORM_H
#define TECHNOSOFTWARE_PLATFORM_H


//
// Platform Identification
//
#define TECHNOSOFTWARE_OS_FREE_BSD      0x0001
#define TECHNOSOFTWARE_OS_AIX           0x0002
#define TECHNOSOFTWARE_OS_HPUX          0x0003
#define TECHNOSOFTWARE_OS_TRU64         0x0004
#define TECHNOSOFTWARE_OS_LINUX         0x0005
#define TECHNOSOFTWARE_OS_MAC_OS_X      0x0006
#define TECHNOSOFTWARE_OS_NET_BSD       0x0007
#define TECHNOSOFTWARE_OS_OPEN_BSD      0x0008
#define TECHNOSOFTWARE_OS_IRIX          0x0009
#define TECHNOSOFTWARE_OS_SOLARIS       0x000a
#define TECHNOSOFTWARE_OS_QNX           0x000b
#define TECHNOSOFTWARE_OS_VXWORKS       0x000c
#define TECHNOSOFTWARE_OS_CYGWIN        0x000d
#define TECHNOSOFTWARE_OS_NACL          0x000e
#define TECHNOSOFTWARE_OS_ANDROID       0x000f
#define TECHNOSOFTWARE_OS_UNKNOWN_UNIX  0x00ff
#define TECHNOSOFTWARE_OS_WINDOWS_NT    0x1001
#define TECHNOSOFTWARE_OS_WINDOWS_CE    0x1011
#define TECHNOSOFTWARE_OS_VMS           0x2001


#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS_FAMILY_BSD 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_FREE_BSD
#elif defined(_AIX) || defined(__TOS_AIX__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_AIX
#elif defined(hpux) || defined(_hpux) || defined(__hpux)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_HPUX
#elif defined(__digital__) || defined(__osf__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_TRU64
#elif defined(__NACL__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_NACL
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__) || defined(EMSCRIPTEN)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_LINUX
	#if defined(__ANDROID__)
		#define TECHNOSOFTWARE_OS POCO_OS_ANDROID
	#else
		#define TECHNOSOFTWARE_OS POCO_OS_LINUX
	#endif
#elif defined(__APPLE__) || defined(__TOS_MACOS__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS_FAMILY_BSD 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_MAC_OS_X
#elif defined(__NetBSD__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS_FAMILY_BSD 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_NET_BSD
#elif defined(__OpenBSD__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS_FAMILY_BSD 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_OPEN_BSD
#elif defined(sgi) || defined(__sgi)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_IRIX
#elif defined(sun) || defined(__sun)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_SOLARIS
#elif defined(__QNX__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_QNX
#elif defined(__CYGWIN__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_CYGWIN
#elif defined(TECHNOSOFTWARE_VXWORKS)
  #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
  #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_VXWORKS
#elif defined(unix) || defined(__unix) || defined(__unix__)
    #define TECHNOSOFTWARE_OS_FAMILY_UNIX 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_UNKNOWN_UNIX
#elif defined(_WIN32_WCE)
    #define TECHNOSOFTWARE_OS_FAMILY_WINDOWS 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_WINDOWS_CE
#elif defined(_WIN32) || defined(_WIN64)
    #define TECHNOSOFTWARE_OS_FAMILY_WINDOWS 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_WINDOWS_NT
#elif defined(__VMS)
    #define TECHNOSOFTWARE_OS_FAMILY_VMS 1
    #define TECHNOSOFTWARE_OS TECHNOSOFTWARE_OS_VMS
#endif


#if !defined(TECHNOSOFTWARE_OS)
    #error "Unknown Platform."
#endif


//
// Hardware Architecture and Byte Order
//
#define TECHNOSOFTWARE_ARCH_ALPHA   0x01
#define TECHNOSOFTWARE_ARCH_IA32    0x02
#define TECHNOSOFTWARE_ARCH_IA64    0x03
#define TECHNOSOFTWARE_ARCH_MIPS    0x04
#define TECHNOSOFTWARE_ARCH_HPPA    0x05
#define TECHNOSOFTWARE_ARCH_PPC     0x06
#define TECHNOSOFTWARE_ARCH_POWER   0x07
#define TECHNOSOFTWARE_ARCH_SPARC   0x08
#define TECHNOSOFTWARE_ARCH_AMD64   0x09
#define TECHNOSOFTWARE_ARCH_ARM     0x0a
#define TECHNOSOFTWARE_ARCH_M68K    0x0b
#define TECHNOSOFTWARE_ARCH_S390    0x0c
#define TECHNOSOFTWARE_ARCH_SH      0x0d
#define TECHNOSOFTWARE_ARCH_NIOS2   0x0e
#define TECHNOSOFTWARE_ARCH_AARCH64 0x0f


#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_ALPHA
    #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86) || defined(EMSCRIPTEN)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_IA32
    #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_IA64
    #if defined(hpux) || defined(_hpux)
        #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
    #else
        #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
    #endif
#elif defined(__x86_64__) || defined(_M_X64)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_AMD64
    #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_MIPS
    #if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
        // Is this OK? Supports windows only little endian??
        #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
    #elif defined(__MIPSEB__) || defined(_MIPSEB) || defined(__MIPSEB)
        #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
    #elif defined(__MIPSEL__) || defined(_MIPSEL) || defined(__MIPSEL)
        #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
    #else
        #error "MIPS but neither MIPSEL nor MIPSEB?"
    #endif
#elif defined(__hppa) || defined(__hppa__)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_HPPA
    #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || \
      defined(__powerpc__) || defined(__ppc__) || defined(__ppc) || defined(_ARCH_PPC) || defined(_M_PPC)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_PPC
	#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
		#define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
	#else
		#define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
	#endif
#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || \
      defined(_ARCH_PWR4) || defined(__THW_RS6000)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_POWER
    #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_SPARC
    #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_ARM
    #if defined(__ARMEB__)
        #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
    #else
        #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
    #endif
#elif defined(__arm64__) || defined(__arm64) 
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_ARM64
    #if defined(__ARMEB__)
        #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
    #elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
    #else
        #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
    #endif
#elif defined(__m68k__)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_M68K
    #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
#elif defined(__s390__)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_S390
    #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
#elif defined(__sh__) || defined(__sh) || defined(SHx) || defined(_SHX_)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_SH
    #if defined(__LITTLE_ENDIAN__) || (TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_WINDOWS_CE)
        #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
    #else
        #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
    #endif
#elif defined (nios2) || defined(__nios2) || defined(__nios2__)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_NIOS2
    #if defined(__nios2_little_endian) || defined(nios2_little_endian) || defined(__nios2_little_endian__)
        #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
    #else
        #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
    #endif
#elif defined(__AARCH64EL__)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_AARCH64
    #define TECHNOSOFTWARE_ARCH_LITTLE_ENDIAN 1
#elif defined(__AARCH64EB__)
    #define TECHNOSOFTWARE_ARCH TECHNOSOFTWARE_ARCH_AARCH64
    #define TECHNOSOFTWARE_ARCH_BIG_ENDIAN 1
#endif


#if defined(_MSC_VER)
    #define TECHNOSOFTWARE_COMPILER_MSVC
#elif defined(__clang__)
    #define TECHNOSOFTWARE_COMPILER_CLANG
#elif defined (__GNUC__)
    #define TECHNOSOFTWARE_COMPILER_GCC
#elif defined (__MINGW32__) || defined (__MINGW64__)
    #define TECHNOSOFTWARE_COMPILER_MINGW
#elif defined (__INTEL_COMPILER) || defined(__ICC) || defined(__ECC) || defined(__ICL)
    #define TECHNOSOFTWARE_COMPILER_INTEL
#elif defined (__SUNPRO_CC)
    #define TECHNOSOFTWARE_COMPILER_SUN
#elif defined (__MWERKS__) || defined(__CWCC__)
    #define TECHNOSOFTWARE_COMPILER_CODEWARRIOR
#elif defined (__sgi) || defined(sgi)
    #define TECHNOSOFTWARE_COMPILER_SGI
#elif defined (__HP_aCC)
    #define TECHNOSOFTWARE_COMPILER_HP_ACC
#elif defined (__BORLANDC__) || defined(__CODEGEARC__)
    #define TECHNOSOFTWARE_COMPILER_CBUILDER
#elif defined (__DMC__)
    #define TECHNOSOFTWARE_COMPILER_DMARS
#elif defined (__DECCXX)
    #define TECHNOSOFTWARE_COMPILER_COMPAC
#elif (defined (__xlc__) || defined (__xlC__)) && defined(__IBMCPP__)
    #define TECHNOSOFTWARE_COMPILER_IBM_XLC // IBM XL C++
#elif defined (__IBMCPP__) && defined(__COMPILER_VER__)
    #define TECHNOSOFTWARE_COMPILER_IBM_XLC_ZOS // IBM z/OS C++
#endif


#ifdef __GNUC__
#define TECHNOSOFTWARE_UNUSED __attribute__((unused))
#else
#define TECHNOSOFTWARE_UNUSED
#endif // __GNUC__


#if !defined(TECHNOSOFTWARE_ARCH)
    #error "Unknown Hardware Architecture."
#endif


#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
    #define TECHNOSOFTWARE_DEFAULT_NEWLINE_CHARS "\r\n"
#else
    #define TECHNOSOFTWARE_DEFAULT_NEWLINE_CHARS "\n"
#endif


#endif /* TECHNOSOFTWARE_PLATFORM_H */
