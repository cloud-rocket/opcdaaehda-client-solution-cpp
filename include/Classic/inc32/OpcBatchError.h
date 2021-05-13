//==============================================================================
// TITLE: OpcBatchError.h
//
// CONTENTS:
// 
// Defines error codes for the Batch specifications.
//
// (c) Copyright 2000-2003 The OPC Foundation
// ALL RIGHTS RESERVED.
//
// DISCLAIMER:
//  This code is provided by the OPC Foundation solely to assist in 
//  understanding and use of the appropriate OPC Specification(s) and may be 
//  used as set forth in the License Grant section of the OPC Specification.
//  This code is provided as-is and without warranty or support of any sort
//  and is subject to the Warranty and Liability Disclaimers which appear
//  in the printed OPC Specification.
//
// MODIFICATION LOG:
//
// Date       By    Notes
// ---------- ---   -----
// 2000/01/17 OPC   Created.
// 2003/01/06 RSA   Updated formatting. Added messages to proxy/stub resource block.
//

#ifndef __OPCBATCHERROR_H
#define __OPCBATCHERROR_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// The 'Facility' is set to the standard for COM interfaces or FACILITY_ITF (i.e. 0x004)
// The 'Code' is set in the range defined OPC Commmon for Batch (i.e. 0x0500 to 0x05FF)
// Note that for backward compatibility not all existing codes use this range.

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: OPCB_E_NOT_MEANINGFUL
//
// MessageText:
//
// The data is not meaningful at the present time.
//
#define OPCB_E_NOT_MEANINGFUL            ((HRESULT)0xC0040300L)

#endif // __OPCBATCHERROR_H
