// MatchPattern.h
//
// © Copyright 1997,1998 The OPC Foundation
// ALL RIGHTS RESERVED.
//
// DISCLAIMER:
//  This sample code is provided by the OPC Foundation solely to assist 
//  in understanding the OPC Alarms and Events Specification and may be used 
//  as set forth in the License Grant section of the OPC Specification.  
//  This code is provided as-is and without warranty or support of any sort 
//  and is subject to the Warranty and Liability Disclaimers which appear 
//  in the printed OPC Specification.
//
// CREDITS:
//  This code was generously provided to the OPC Foundation by 
//  ICONICS, Inc.  http://www.iconics.com
//
// CONTENTS:
//
//  
//
//-------------------------------------------------------------------------
//
//   $Workfile: MatchPattern.h $
//
//
// Org. Author: Jim Luth
//     $Author: thomasjohannhson $
//   $Revision: 1 $
//       $Date: 2015-05-18 17:27:17 +0200 (Mo, 18 Mai 2015) $
//    $Archive: /OPC/AlarmEvents/SampleServer/MatchPattern.h $
//
//      System: GENESIS-32
//   Subsystem: Security
//
//
// Description: 
//
// Functions:   
//
//
//
//
//
/*   $History: MatchPattern.h $
 * 
 * *****************  Version 8  *****************
 * User: Jiml         Date: 8/19/98    Time: 1:52p
 * Updated in $/OPC/AlarmEvents/SampleServer
 * 
 * *****************  Version 7  *****************
 * User: Jiml         Date: 4/23/98    Time: 2:28p
 * Updated in $/OPC/AlarmEvents/SampleServer
 * 
 * *****************  Version 6  *****************
 * User: Jiml         Date: 3/17/98    Time: 5:04p
 * Updated in $/OPC/AlarmEvents/SampleServer
 * 
 * *****************  Version 5  *****************
 * User: Jiml         Date: 2/18/98    Time: 11:55a
 * Updated in $/Security/Server
 * 
 * *****************  Version 4  *****************
 * User: Jiml         Date: 12/29/97   Time: 7:00p
 * Updated in $/OPC/AlarmEvents/SampleServer
 * 
 * *****************  Version 3  *****************
 * User: Jiml         Date: 10/27/97   Time: 5:50p
 * Updated in $/Security/Server
*/
//
//
//*************************************************************************          

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
// #define _ismdigit    iswdigit



#ifndef MCHAR
                              // The OCS Server Toolkit requires a wide-char version
//#define MCHAR        WCHAR
//#define _M(a)        L ## a
//#define _ismdigit    iswdigit

                              // The OCS Registry Check requires a t-char version
#define MCHAR        TCHAR
#define _M(a)        _T(a)
#define _ismdigit    _istdigit

#endif

extern BOOL  MatchPattern( const MCHAR* String, const MCHAR * Pattern, BOOL bCaseSensitive = FALSE );

#endif

