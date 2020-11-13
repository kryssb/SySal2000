/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 23 12:41:12 2002
 */
/* Compiler settings:
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

const IID IID_IVisionProcessor = {0xC1C2E8BC,0xC241,0x423F,{0xB0,0xD7,0x24,0x2B,0x07,0x02,0x4F,0x7E}};


const IID IID_IVisionProcessor2 = {0x673ec4de,0x0d86,0x4155,{0xbb,0x0b,0xc2,0xa8,0x04,0x69,0xfa,0x19}};


const IID IID_IVisionProcessor3 = {0x3373d52b,0x6c8f,0x4518,{0xb0,0x41,0xfc,0x64,0x84,0x99,0x2c,0x14}};


#ifdef __cplusplus
}
#endif

