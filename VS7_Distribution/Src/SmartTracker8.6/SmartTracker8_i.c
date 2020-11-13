

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Tue Aug 05 01:29:04 2008
 */
/* Compiler settings for .\SmartTracker8.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
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

MIDL_DEFINE_GUID(IID, IID_ISySalObject,0xC022EEAD,0x748A,0x11D3,0xA4,0x7B,0xE8,0x9C,0x0B,0xCE,0x97,0x20);


MIDL_DEFINE_GUID(IID, IID_ISySalObject2,0x68659AF8,0x12E6,0x4EF9,0x98,0x77,0xA7,0xDD,0x63,0xBF,0x19,0x50);


MIDL_DEFINE_GUID(IID, IID_ITracker,0xE416C46D,0x7F68,0x11D3,0xA4,0x7C,0xFA,0x1E,0x4A,0xFA,0x27,0x21);


MIDL_DEFINE_GUID(IID, IID_ITracker2,0x67a71430,0xf2e4,0x42ae,0x89,0x10,0x28,0x27,0x9a,0x76,0x16,0xd6);


MIDL_DEFINE_GUID(IID, IID_ITracker3,0x7a9e779c,0xaa32,0x4565,0x8e,0x69,0x5f,0x1b,0xc4,0xe3,0x62,0xb7);


MIDL_DEFINE_GUID(IID, IID_ITracker4,0x04e5187b,0x933e,0x4d9e,0x9a,0x7f,0xeb,0x20,0x84,0x0d,0xa9,0xd0);


MIDL_DEFINE_GUID(IID, LIBID_SMARTTRACKERLib,0x42331e8a,0x56e9,0x402e,0xb7,0xc6,0x01,0x3f,0x91,0x6f,0x49,0x1e);


MIDL_DEFINE_GUID(CLSID, CLSID_SmartTracker8,0x99865850,0x4e2d,0x446e,0xac,0xdc,0x87,0x16,0x51,0x30,0x67,0x9e);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



