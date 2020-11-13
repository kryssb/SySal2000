

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Sep 05 18:47:27 2008
 */
/* Compiler settings for .\SmartFitter2.idl:
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


MIDL_DEFINE_GUID(IID, IID_ITrackFitter,0x9061992E,0x87FC,0x11D3,0xA4,0x7C,0xCB,0xD9,0x48,0x9C,0x09,0x20);


MIDL_DEFINE_GUID(IID, IID_ITrackFitter2,0x950c2406,0xd41e,0x47d1,0x9f,0x84,0xa1,0xbf,0xc0,0x40,0x29,0xc5);


MIDL_DEFINE_GUID(IID, IID_ITrackFitter3,0x855fe3ff,0xb30f,0x4ad2,0x98,0x10,0x47,0x1e,0xdf,0xc9,0xf4,0xb8);


MIDL_DEFINE_GUID(IID, LIBID_SMARTFITTERLib,0x7e8de6c1,0x7710,0x48a5,0xa2,0xc5,0x82,0x13,0xa1,0xae,0x24,0x6f);


MIDL_DEFINE_GUID(CLSID, CLSID_SmartFitter2,0x0078daf5,0x9fd2,0x4e17,0x9e,0xc8,0x84,0x5e,0x8b,0xbf,0x7d,0x0d);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



