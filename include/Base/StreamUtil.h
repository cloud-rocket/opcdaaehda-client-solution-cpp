/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Stream implementation support.
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

#ifndef TECHNOSOFTWARE_STREAMUTIL_H
#define TECHNOSOFTWARE_STREAMUTIL_H

#include "Base/Base.h"


// technosoftware_ios_init
// 
// This is a workaround for a bug in the Dinkumware implementation of iostreams.
// 
// Calling basic_ios::init() multiple times for the same basic_ios instance results in a memory
// leak caused by the ios' locale being allocated more than once, each time overwriting the old
// pointer. This usually occurs in the following scenario:
// 
// class MyStreamBuf: public std::streambuf
// {
//     ...
// };
// 
// class MyIOS: public virtual std::ios
// {
// public:
//     MyIOS()
//     {
//         init(&_buf);
//     }
// protected:
//     MyStreamBuf _buf;
// };
// 
// class MyIStream: public MyIOS, public std::istream
// {
//     ...
// };
// 
// In this scenario, std::ios::init() is called twice (the first time by the MyIOS constructor, the
// second time by the std::istream constructor), resulting in two locale objects being allocated,
// the pointer second one overwriting the pointer to the first one and thus causing a memory leak.
// 
// The workaround is to call init() only once for each stream object - by the istream, ostream or
// iostream constructor, and not calling init() in ios-derived base classes.
// 
// Some stream implementations, however, require that init() is called in the MyIOS constructor.
// Therefore we replace each call to init() with the technosoftware_ios_init macro defined below. 


#if !defined(TECHNOSOFTWARE_IOS_INIT_HACK)
    // Microsoft Visual Studio with Dinkumware STL (but not STLport)
#    if defined(_MSC_VER) && (!defined(_STLP_MSVC) || defined(_STLP_NO_OWN_IOSTREAMS))
#        define TECHNOSOFTWARE_IOS_INIT_HACK 1
    // QNX with Dinkumware but not GNU C++ Library
#    elif defined(__QNX__) && !defined(__GLIBCPP__)
#        define TECHNOSOFTWARE_IOS_INIT_HACK 1
#    endif
#endif


#if defined(TECHNOSOFTWARE_IOS_INIT_HACK)
#    define technosoftware_ios_init(buf)
#else
#    define technosoftware_ios_init(buf) init(buf)
#endif

#endif /* TECHNOSOFTWARE_STREAMUTIL_H */
