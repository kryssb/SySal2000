

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Dec 05 10:24:11 2008
 */
/* Compiler settings for .\Odyssey3.idl:
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


MIDL_DEFINE_GUID(IID, IID_IFrameGrabber,0xDFFC86AE,0x7C46,0x11D3,0xA4,0x7C,0xC0,0xB8,0x89,0xFF,0x7C,0x20);


MIDL_DEFINE_GUID(IID, IID_IVisionProcessor,0xC1C2E8BC,0xC241,0x423F,0xB0,0xD7,0x24,0x2B,0x07,0x02,0x4F,0x7E);


MIDL_DEFINE_GUID(IID, IID_IVisionProcessor2,0x673ec4de,0x0d86,0x4155,0xbb,0x0b,0xc2,0xa8,0x04,0x69,0xfa,0x19);


MIDL_DEFINE_GUID(IID, IID_IAutomaticLightControl,0xb6ac7f16,0x130a,0x4f55,0x92,0x72,0x12,0x4a,0x2f,0xff,0x17,0x67);


MIDL_DEFINE_GUID(IID, IID_IVisionProcessor3,0x3373d52b,0x6c8f,0x4518,0xb0,0x41,0xfc,0x64,0x84,0x99,0x2c,0x14);


MIDL_DEFINE_GUID(IID, IID_IVisionProcessor4,0x766b15ef,0x46f9,0x4541,0x9e,0x2e,0x4f,0xf8,0xa0,0x9d,0xee,0x45);


MIDL_DEFINE_GUID(IID, LIBID_OdysseyLib,0x48b7a011,0xba80,0x4c0a,0x8c,0x9b,0x8d,0x3a,0xa3,0x50,0x9d,0x47);


MIDL_DEFINE_GUID(CLSID, CLSID_Odyssey,0xaca929f0,0x3f96,0x4f17,0x94,0x15,0xc7,0xf8,0x5d,0xae,0x3b,0x27);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



