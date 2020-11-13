/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 09 19:22:12 2004
 */
/* Compiler settings for C:\sysal2000\Odyssey2\Odyssey2.idl:
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


const IID IID_IVisionProcessor4 = {0x766b15ef,0x46f9,0x4541,{0x9e,0x2e,0x4f,0xf8,0xa0,0x9d,0xee,0x45}};


#ifdef __cplusplus
}
#endif

