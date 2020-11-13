

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Tue Aug 05 01:29:08 2008
 */
/* Compiler settings for .\VertigoScan6.idl:
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


MIDL_DEFINE_GUID(IID, IID_IDAQSynchronize,0xb1785d91,0x3ecf,0x403b,0xbb,0xe9,0x3b,0x14,0xcb,0x80,0x66,0x17);


MIDL_DEFINE_GUID(IID, LIBID_VERTIGOSCAN6Lib,0xa764e28d,0x4a33,0x49a6,0xb2,0x14,0x4e,0x59,0xf1,0x75,0x15,0x4d);


MIDL_DEFINE_GUID(CLSID, CLSID_VertigoScan6,0xb3b78a42,0x0c68,0x49ee,0xa2,0xe6,0xb9,0x3b,0x24,0x8e,0xcc,0xd4);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



