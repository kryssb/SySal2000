

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Oct 10 23:35:00 2008
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


MIDL_DEFINE_GUID(IID, LIBID_SMARTTRACKERLib,0xc7529081,0x2014,0x4fb6,0xa5,0x68,0x59,0xec,0x5e,0xc3,0x1f,0x0e);


MIDL_DEFINE_GUID(CLSID, CLSID_SmartTracker8,0x70ad22dc,0x78c6,0x49fa,0xb1,0xf0,0x47,0x59,0x28,0xf5,0xab,0x33);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



