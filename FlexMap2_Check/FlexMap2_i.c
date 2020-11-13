/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 11 07:45:19 2002
 */
/* Compiler settings for K:\SySal2\FlexMap2\FlexMap2.idl:
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


const IID IID_ISheetMap = {0xD0FEF450,0xB910,0x4D5D,{0x90,0x8C,0x9E,0x1E,0x64,0xEA,0x7F,0xA1}};


const IID LIBID_FLEXMAPLib = {0xfa98c542,0x08bf,0x43b4,{0x8d,0x17,0x6f,0xc5,0x4e,0x91,0x9f,0xa5}};


const CLSID CLSID_FlexibleMap = {0x37ebf8f8,0x73d6,0x4893,{0x9e,0xfb,0xd3,0x64,0x47,0x52,0x9f,0xa0}};


#ifdef __cplusplus
}
#endif

