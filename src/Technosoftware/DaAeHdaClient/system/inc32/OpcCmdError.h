//==============================================================================
// TITLE: OpcCmdError.h
//
// CONTENTS:
// 
// Defines error codes for the OPC Command Execution specification.
//
// (c) Copyright 2004 The OPC Foundation
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
// 2002/12/12 RSA   Created.
//

#ifndef _OpcCmdError_H_
#define _OpcCmdError_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


// The 'Facility' is set to the standard for COM interfaces or FACILITY_ITF (i.e. 0x004)
// The 'Code' is set in the range defined OPC Commmon for DX (i.e. 0x0700 to 0x07FF)
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
// MessageId: OPCCMD_E_INVALIDBRANCH
//
// MessageText:
//
// The Target ID specified in the request is not a valid branch.
//
#define OPCCMD_E_INVALIDBRANCH           ((HRESULT)0xC0040900L)

//
// MessageId: OPCCMD_E_INVALIDNAMESPACE
//
// MessageText:
//
// The specified namespace is not a valid namespace for this server.
//
#define OPCCMD_E_INVALIDNAMESPACE        ((HRESULT)0xC0040901L)

//
// MessageId: OPCCMD_E_INVALIDCOMMANDNAME
//
// MessageText:
//
// The specified command name is not valid for this server.
//
#define OPCCMD_E_INVALIDCOMMANDNAME      ((HRESULT)0xC0040902L)

//
// MessageId: OPCCMD_E_BUSY
//
// MessageText:
//
// The server is currently not able to process this command.
//
#define OPCCMD_E_BUSY                    ((HRESULT)0xC0040903L)

//
// MessageId: OPCCMD_E_EVENTFILTER_NOTSUPPORTED
//
// MessageText:
//
// The server does not support filtering of events.
//
#define OPCCMD_E_EVENTFILTER_NOTSUPPORTED ((HRESULT)0xC0040904L)

//
// MessageId: OPCCMD_E_NO_SUCH_COMMAND
//
// MessageText:
//
// A command with the specified UUID is neither executing nor completed (and still stored in the cache).
//
#define OPCCMD_E_NO_SUCH_COMMAND         ((HRESULT)0xC0040905L)

//
// MessageId: OPCCMD_E_ALREADY_CONNECTED
//
// MessageText:
//
// A client is already connected for the specified Invoke UUID.
//
#define OPCCMD_E_ALREADY_CONNECTED       ((HRESULT)0xC0040906L)

//
// MessageId: OPCCMD_E_NOT_CONNECTED
//
// MessageText:
//
// No Callback ID is currently connected for the specified command.
//
#define OPCCMD_E_NOT_CONNECTED           ((HRESULT)0xC0040907L)

//
// MessageId: OPCCMD_E_CONTROL_NOTSUPPORTED
//
// MessageText:
//
// The server does not support the specified control for this command.
//
#define OPCCMD_E_CONTROL_NOTSUPPORTED    ((HRESULT)0xC0040908L)

//
// MessageId: OPCCMD_E_INVALID_CONTROL
//
// MessageText:
//
// The specified control is not possible in the current state of execution.
//
#define OPCCMD_E_INVALID_CONTROL         ((HRESULT)0xC0040909L)

#endif // ifndef _OpcCmdError_H_
