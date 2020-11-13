/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 11 13:43:53 2001
 */
/* Compiler settings for K:\SySal2\Genesis2\Genesis2.idl:
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


const IID LIBID_GENESISLib = {0xa0262202,0xf3c1,0x4101,{0xb8,0x2a,0xa2,0x54,0x13,0xf9,0xbb,0xed}};


const CLSID CLSID_Genesis2 = {0x06D29AE9,0x2C50,0x45BE,{0x8F,0xEA,0xEC,0xCC,0x06,0x8E,0xC8,0x9C}};


#ifdef __cplusplus
}
#endif

