

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Jan 17 19:13:38 2011
 */
/* Compiler settings for .\opc_ae.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_OPCEventServerCATID,0x58E13251,0xAC87,0x11d1,0x84,0xD5,0x00,0x60,0x8C,0xB8,0xA7,0xE9);


MIDL_DEFINE_GUID(IID, IID_IOPCEventServer,0x65168851,0x5783,0x11D1,0x84,0xA0,0x00,0x60,0x8C,0xB8,0xA7,0xE9);


MIDL_DEFINE_GUID(IID, IID_IOPCEventSubscriptionMgt,0x65168855,0x5783,0x11D1,0x84,0xA0,0x00,0x60,0x8C,0xB8,0xA7,0xE9);


MIDL_DEFINE_GUID(IID, IID_IOPCEventAreaBrowser,0x65168857,0x5783,0x11D1,0x84,0xA0,0x00,0x60,0x8C,0xB8,0xA7,0xE9);


MIDL_DEFINE_GUID(IID, IID_IOPCEventSink,0x6516885F,0x5783,0x11D1,0x84,0xA0,0x00,0x60,0x8C,0xB8,0xA7,0xE9);


MIDL_DEFINE_GUID(IID, IID_IOPCEventServer2,0x71BBE88E,0x9564,0x4bcd,0xBC,0xFC,0x71,0xC5,0x58,0xD9,0x4F,0x2D);


MIDL_DEFINE_GUID(IID, IID_IOPCEventSubscriptionMgt2,0x94C955DC,0x3684,0x4ccb,0xAF,0xAB,0xF8,0x98,0xCE,0x19,0xAA,0xC3);


MIDL_DEFINE_GUID(IID, LIBID_OPC_AE,0x65168844,0x5783,0x11D1,0x84,0xA0,0x00,0x60,0x8C,0xB8,0xA7,0xE9);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



