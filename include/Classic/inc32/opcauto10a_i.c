/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Mar 02 14:11:12 1999
 */
/* Compiler settings for opcauto10a.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID IID_IOPCServerDisp = {0x39c13a57,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCServerPublicGroupsDisp = {0x39c13a58,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCBrowseServerAddressSpaceDisp = {0x39c13a59,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCItemMgtDisp = {0x39c13a5a,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCGroupStateMgtDisp = {0x39c13a5b,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCSyncIODisp = {0x39c13a5c,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCAsyncIODisp = {0x39c13a5d,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCPublicGroupStateMgtDisp = {0x39c13a5e,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID IID_IOPCItemDisp = {0x39c13a5f,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3}};


const IID LIBID_OPCSDKLib = {0x5F66E430,0xFC32,0x11D0,{0xA2,0x5F,0x00,0x00,0xE8,0x1E,0x90,0x85}};


const CLSID CLSID_OPCGroup = {0x94003F74,0xFE18,0x11D0,{0xA2,0x65,0x00,0x00,0xE8,0x1E,0x90,0x85}};


const CLSID CLSID_OPCItem = {0x94003F76,0xFE18,0x11D0,{0xA2,0x65,0x00,0x00,0xE8,0x1E,0x90,0x85}};


#ifdef __cplusplus
}
#endif

