/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com 
 * 
 * Purpose: 
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */



#ifndef __MATCHPATTERN_H
#define __MATCHPATTERN_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


// By redefining MCHAR, _M and _ismdigit you may alter the type
// of string MatchPattern() works with. For example to operate on
// wide strings, make the following definitions:
// #define MCHAR        WCHAR
// #define _M(x)        L ## x
// #define _ismdigit   iswdigit



#ifndef MCHAR
                              // The ClientSdk requires a wide-char version
#define MCHAR           WCHAR
#define _M(a)           L ## a
#define _ismdigit    iswdigit

//#define MCHAR           TCHAR
//#define _M(a)           _T(a)
//#define _ismdigit    _istdigit

#endif



extern BOOL  MatchPattern( const MCHAR* String, const MCHAR * Pattern, BOOL bCaseSensitive = FALSE );


#endif

