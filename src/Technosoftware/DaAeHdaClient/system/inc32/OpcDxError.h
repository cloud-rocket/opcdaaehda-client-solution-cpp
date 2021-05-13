//==============================================================================
// TITLE: OpcDxError.h
//
// CONTENTS:
// 
// Defines error codes for the OPC Data Exchange specification.
//
// (c) Copyright 2002 The OPC Foundation
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

#ifndef _OpcDxError_H_
#define _OpcDxError_H_

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
// MessageId: OPCDX_E_PERSISTING
//
// MessageText:
//
// Could not process request because the configuration is currently being persisted.
//
#define OPCDX_E_PERSISTING               ((HRESULT)0xC0040700L)

//
// MessageId: OPCDX_E_NOITEMLIST
//
// MessageText:
//
// No item list was passed in the request.
//
#define OPCDX_E_NOITEMLIST               ((HRESULT)0xC0040701L)

//
// MessageId: OPCDX_E_SERVER_STATE
//
// MessageText:
//
// The operation failed because the server is in the wrong state.
//
#define OPCDX_E_SERVER_STATE             ((HRESULT)0xC0040702L)

//
// MessageId: OPCDX_E_VERSION_MISMATCH
//
// MessageText:
//
// The current object version does not match the specified version.
//
#define OPCDX_E_VERSION_MISMATCH         ((HRESULT)0xC0040703L)

//
// MessageId: OPCDX_E_UNKNOWN_ITEM_PATH
//
// MessageText:
//
// The specified item path no longer exists in the DX server's address space.
//
#define OPCDX_E_UNKNOWN_ITEM_PATH        ((HRESULT)0xC0040704L)

//
// MessageId: OPCDX_E_UNKNOWN_ITEM_NAME
//
// MessageText:
//
// The specified item name no longer exists in the DX server's address space.
//
#define OPCDX_E_UNKNOWN_ITEM_NAME        ((HRESULT)0xC0040705L)

//
// MessageId: OPCDX_E_INVALID_ITEM_PATH
//
// MessageText:
//
// The specified item path does not conform to the DX server syntax.
//
#define OPCDX_E_INVALID_ITEM_PATH        ((HRESULT)0xC0040706L)

//
// MessageId: OPCDX_E_INVALID_ITEM_NAME
//
// MessageText:
//
// The specified item name does not conform to the DX server syntax.
//
#define OPCDX_E_INVALID_ITEM_NAME        ((HRESULT)0xC0040707L)

//
// MessageId: OPCDX_E_INVALID_NAME
//
// MessageText:
//
// The source server name or connection name does not conform to the server syntax.
//
#define OPCDX_E_INVALID_NAME             ((HRESULT)0xC0040708L)

//
// MessageId: OPCDX_E_DUPLICATE_NAME
//
// MessageText:
//
// The connection name or source server name is already in use.
//
#define OPCDX_E_DUPLICATE_NAME           ((HRESULT)0xC0040709L)

//
// MessageId: OPCDX_E_INVALID_BROWSE_PATH
//
// MessageText:
//
// The browse path does not conform to the DX server syntax or it cannot be modified.
//
#define OPCDX_E_INVALID_BROWSE_PATH      ((HRESULT)0xC004070AL)

//
// MessageId: OPCDX_E_INVALID_SERVER_URL
//
// MessageText:
//
// The syntax of the source server URL is not correct.
//
#define OPCDX_E_INVALID_SERVER_URL       ((HRESULT)0xC004070BL)

//
// MessageId: OPCDX_E_INVALID_SERVER_TYPE
//
// MessageText:
//
// The source server type is not recognized.
//
#define OPCDX_E_INVALID_SERVER_TYPE      ((HRESULT)0xC004070CL)

//
// MessageId: OPCDX_E_UNSUPPORTED_SERVER_TYPE
//
// MessageText:
//
// The source server does not support the specified server type.
//
#define OPCDX_E_UNSUPPORTED_SERVER_TYPE  ((HRESULT)0xC004070DL)

//
// MessageId: OPCDX_E_CONNECTIONS_EXIST
//
// MessageText:
//
// The source server cannot be deleted because connections exist.
//
#define OPCDX_E_CONNECTIONS_EXIST        ((HRESULT)0xC004070EL)

//
// MessageId: OPCDX_E_TOO_MANY_CONNECTIONS
//
// MessageText:
//
// The total number of connections would exceed the maximum supported by the DX server.
//
#define OPCDX_E_TOO_MANY_CONNECTIONS     ((HRESULT)0xC004070FL)

//
// MessageId: OPCDX_E_OVERRIDE_BADTYPE
//
// MessageText:
//
// The override value is not valid and overridden flag is set to true.
//
#define OPCDX_E_OVERRIDE_BADTYPE         ((HRESULT)0xC0040710L)

//
// MessageId: OPCDX_E_OVERRIDE_RANGE
//
// MessageText:
//
// The override value is outside of the target item’s range and overridden flag is set to true.
//
#define OPCDX_E_OVERRIDE_RANGE           ((HRESULT)0xC0040711L)

//
// MessageId: OPCDX_E_SUBSTITUTE_BADTYPE
//
// MessageText:
//
// The substitute  value is not valid and the enable substitute value flag is set to true.
//
#define OPCDX_E_SUBSTITUTE_BADTYPE       ((HRESULT)0xC0040712L)

//
// MessageId: OPCDX_E_SUBSTITUTE_RANGE
//
// MessageText:
//
// The substitute value is outside of the target item’s range the enable substitute value flag is set to true.
//
#define OPCDX_E_SUBSTITUTE_RANGE         ((HRESULT)0xC0040713L)

//
// MessageId: OPCDX_E_INVALID_TARGET_ITEM
//
// MessageText:
//
// The target item does not conform to the DX server syntax or the item cannot be used as a target.
//
#define OPCDX_E_INVALID_TARGET_ITEM      ((HRESULT)0xC0040714L)

//
// MessageId: OPCDX_E_UNKNOWN_TARGET_ITEM
//
// MessageText:
//
// The target item no longer exists in the DX server’s address space.
//
#define OPCDX_E_UNKNOWN_TARGET_ITEM      ((HRESULT)0xC0040715L)

//
// MessageId: OPCDX_E_TARGET_ALREADY_CONNECTED
//
// MessageText:
//
// The target item is already connected or may not be changed in the method.
//
#define OPCDX_E_TARGET_ALREADY_CONNECTED ((HRESULT)0xC0040716L)

//
// MessageId: OPCDX_E_UNKNOWN_SERVER_NAME
//
// MessageText:
//
// The specified source server does not exist.
//
#define OPCDX_E_UNKNOWN_SERVER_NAME      ((HRESULT)0xC0040717L)

//
// MessageId: OPCDX_E_UNKNOWN_SOURCE_ITEM
//
// MessageText:
//
// The source item is no longer in the source server’s address space.
//
#define OPCDX_E_UNKNOWN_SOURCE_ITEM      ((HRESULT)0xC0040718L)

//
// MessageId: OPCDX_E_INVALID_SOURCE_ITEM
//
// MessageText:
//
// The source item does not confirm to the source server’s syntax.
//
#define OPCDX_E_INVALID_SOURCE_ITEM      ((HRESULT)0xC0040719L)

//
// MessageId: OPCDX_E_INVALID_QUEUE_SIZE
//
// MessageText:
//
// The update queue size is not valid.
//
#define OPCDX_E_INVALID_QUEUE_SIZE       ((HRESULT)0xC004071AL)

//
// MessageId: OPCDX_E_INVALID_DEADBAND
//
// MessageText:
//
// The deadband is not valid.
//
#define OPCDX_E_INVALID_DEADBAND         ((HRESULT)0xC004071BL)

//
// MessageId: OPCDX_E_INVALID_CONFIG_FILE
//
// MessageText:
//
// The DX server configuration file is not acessable.
//
#define OPCDX_E_INVALID_CONFIG_FILE      ((HRESULT)0xC004071CL)

//
// MessageId: OPCDX_E_PERSIST_FAILED
//
// MessageText:
//
// Could not save the DX server configuration.
//
#define OPCDX_E_PERSIST_FAILED           ((HRESULT)0xC004071DL)

//
// MessageId: OPCDX_E_TARGET_FAULT
//
// MessageText:
//
// Target is online, but cannot service any request due to being in a fault state.
//
#define OPCDX_E_TARGET_FAULT             ((HRESULT)0xC004071EL)

//
// MessageId: OPCDX_E_TARGET_NO_ACCESS
//
// MessageText:
//
// Target is not online and may not be accessed.
//
#define OPCDX_E_TARGET_NO_ACCESS         ((HRESULT)0xC004071FL)

//
// MessageId: OPCDX_E_SOURCE_SERVER_FAULT
//
// MessageText:
//
// Source server is online, but cannot service any request due to being in a fault state.
//
#define OPCDX_E_SOURCE_SERVER_FAULT      ((HRESULT)0xC0040720L)

//
// MessageId: OPCDX_E_SOURCE_SERVER_NO_ACCESS
//
// MessageText:
//
// Source server is not online and may not be accessed.
//
#define OPCDX_E_SOURCE_SERVER_NO_ACCESS  ((HRESULT)0xC0040721L)

//
// MessageId: OPCDX_E_SUBSCRIPTION_FAULT
//
// MessageText:
//
// Source server is connected, however it could not create a subscription for the connection.
//
#define OPCDX_E_SUBSCRIPTION_FAULT       ((HRESULT)0xC0040722L)

//
// MessageId: OPCDX_E_SOURCE_ITEM_BADRIGHTS
//
// MessageText:
//
// The source items access rights ddo not permit the operation.
//
#define OPCDX_E_SOURCE_ITEM_BADRIGHTS    ((HRESULT)0xC0040723L)

//
// MessageId: OPCDX_E_SOURCE_ITEM_BAD_QUALITY
//
// MessageText:
//
// The source item value could be used because it has bad quality.
//
#define OPCDX_E_SOURCE_ITEM_BAD_QUALITY  ((HRESULT)0xC0040724L)

//
// MessageId: OPCDX_E_SOURCE_ITEM_BADTYPE
//
// MessageText:
//
// The source item cannot be converted to the target’s data type. This error reported by the source server.
//
#define OPCDX_E_SOURCE_ITEM_BADTYPE      ((HRESULT)0xC0040725L)

//
// MessageId: OPCDX_E_SOURCE_ITEM_RANGE
//
// MessageText:
//
// The source item is out of the  range for the requested type. This error reported by the source server.
//
#define OPCDX_E_SOURCE_ITEM_RANGE        ((HRESULT)0xC0040726L)

//
// MessageId: OPCDX_E_SOURCE_SERVER_NOT_CONNECTED
//
// MessageText:
//
// The source server is not connected.
//
#define OPCDX_E_SOURCE_SERVER_NOT_CONNECTED ((HRESULT)0xC0040727L)

//
// MessageId: OPCDX_E_SOURCE_SERVER_TIMEOUT
//
// MessageText:
//
// The source server was disconnected because to failed to respond to pings.
//
#define OPCDX_E_SOURCE_SERVER_TIMEOUT    ((HRESULT)0xC0040728L)

//
// MessageId: OPCDX_E_TARGET_ITEM_DISCONNECTED
//
// MessageText:
//
// The target item is disconnected.
//
#define OPCDX_E_TARGET_ITEM_DISCONNECTED ((HRESULT)0xC0040729L)

//
// MessageId: OPCDX_E_TARGET_NO_WRITES_ATTEMPTED
//
// MessageText:
//
// The DX server has not attempted to write to the target.
//
#define OPCDX_E_TARGET_NO_WRITES_ATTEMPTED ((HRESULT)0xC004072AL)

//
// MessageId: OPCDX_E_TARGET_ITEM_BADTYPE
//
// MessageText:
//
// The target item cannot be converted to the target’s data type.
//
#define OPCDX_E_TARGET_ITEM_BADTYPE      ((HRESULT)0xC004072BL)

//
// MessageId: OPCDX_E_TARGET_ITEM_RANGE
//
// MessageText:
//
// The target item is outside the value range for the item.
//
#define OPCDX_E_TARGET_ITEM_RANGE        ((HRESULT)0xC004072CL)

//
// MessageId: OPCDX_S_TARGET_SUBSTITUTED
//
// MessageText:
//
// The substitute value was written to the target.
//
#define OPCDX_S_TARGET_SUBSTITUTED       ((HRESULT)0x00040780L)

//
// MessageId: OPCDX_S_TARGET_OVERRIDEN
//
// MessageText:
//
// The override value was written to the target.
//
#define OPCDX_S_TARGET_OVERRIDEN         ((HRESULT)0x00040781L)

//
// MessageId: OPCDX_S_CLAMP
//
// MessageText:
//
// Value written was accepted but the output was clamped.
//
#define OPCDX_S_CLAMP                    ((HRESULT)0x00040782L)

#endif // ifndef _OpcDxError_H_
