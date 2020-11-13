/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 16 10:04:38 2002
 */
/* Compiler settings for D:\SySal2\Genesis3\Genesis3.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

const IID IID_ISySalObject = {0xC022EEAD,0x748A,0x11D3,{0xA4,0x7B,0xE8,0x9C,0x0B,0xCE,0x97,0x20}};


const IID IID_IFrameGrabber = {0xDFFC86AE,0x7C46,0x11D3,{0xA4,0x7C,0xC0,0xB8,0x89,0xFF,0x7C,0x20}};


const IID IID_IGenesis = {0xDFFC86AD,0x7C46,0x11D3,{0xA4,0x7C,0xC0,0xB8,0x89,0xFF,0x7C,0x20}};


const IID IID_IVisionProcessor = {0xC1C2E8BC,0xC241,0x423F,{0xB0,0xD7,0x24,0x2B,0x07,0x02,0x4F,0x7E}};


const IID IID_IVisionProcessor2 = {0x673ec4de,0x0d86,0x4155,{0xbb,0x0b,0xc2,0xa8,0x04,0x69,0xfa,0x19}};


const IID LIBID_GENESISLib = {0xc93a8cd1,0x5a74,0x4906,{0xa1,0x1d,0x16,0xac,0xc7,0x05,0x62,0x98}};


const CLSID CLSID_Genesis3 = {0x8773a38d,0x8d52,0x4ecf,{0x8c,0x0d,0xd9,0x8b,0x6d,0x87,0xb1,0xca}};


#ifdef __cplusplus
}
#endif

