

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jul 31 14:44:09 2009
 */
/* Compiler settings for .\FlexMapX.idl:
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


MIDL_DEFINE_GUID(IID, IID_ISheetMap,0xD0FEF450,0xB910,0x4D5D,0x90,0x8C,0x9E,0x1E,0x64,0xEA,0x7F,0xA1);


MIDL_DEFINE_GUID(IID, IID_ISheetMap2,0x6bc68332,0x752b,0x489c,0xae,0x7d,0xa4,0x5d,0xb6,0x23,0xb7,0x33);


MIDL_DEFINE_GUID(IID, LIBID_FLEXMAPLib,0x92fa5986,0x0196,0x4917,0xbb,0x22,0xf6,0x7f,0x5c,0x78,0xeb,0x67);


MIDL_DEFINE_GUID(CLSID, CLSID_FlexibleMap,0x20907edd,0xf7ff,0x46ed,0x86,0x4f,0xa1,0x13,0x9a,0xe7,0xe6,0xc4);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



