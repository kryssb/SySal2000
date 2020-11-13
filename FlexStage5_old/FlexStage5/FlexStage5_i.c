

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Wed Jun 18 19:02:54 2008
 */
/* Compiler settings for .\FlexStage5.idl:
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


MIDL_DEFINE_GUID(IID, IID_ISySalObjectMachineDefaults,0x455b5e46,0x0c34,0x443e,0x87,0x9b,0x53,0x94,0x1a,0x71,0x02,0x6f);


MIDL_DEFINE_GUID(IID, IID_IStage,0x075E1B0D,0xC472,0x11D3,0xA4,0x7E,0xDC,0x13,0x18,0xA5,0x1E,0x33);


MIDL_DEFINE_GUID(IID, IID_IStage2,0x3cf5ffa6,0x7919,0x4fd4,0x8b,0xd8,0x43,0xaa,0xaa,0x4d,0xe9,0xda);


MIDL_DEFINE_GUID(IID, IID_IStage3,0x29ca8106,0xdc50,0x4908,0xb3,0x96,0x4c,0xb8,0x4b,0x49,0x25,0x5e);


MIDL_DEFINE_GUID(IID, IID_IDigitalIO,0x4d37a06b,0xdb4d,0x4e6f,0xb5,0x3c,0x3e,0x95,0xf1,0xc8,0x1f,0xd3);


MIDL_DEFINE_GUID(IID, LIBID_FLEXSTAGELib,0x8194075d,0x71d9,0x46a2,0x93,0xa8,0x0b,0x43,0xf7,0x73,0x2b,0x50);


MIDL_DEFINE_GUID(CLSID, CLSID_FlexStage5,0x16cba222,0x432c,0x406d,0x97,0x43,0x62,0x5e,0xac,0xb8,0x2a,0x2d);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



