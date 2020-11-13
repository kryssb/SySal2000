/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 14 21:32:50 2004
 */
/* Compiler settings for D:\SySal2\FlexStage3\FlexStage3.idl:
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


const IID IID_IStage = {0x075E1B0D,0xC472,0x11D3,{0xA4,0x7E,0xDC,0x13,0x18,0xA5,0x1E,0x33}};


const IID IID_IStage2 = {0x3cf5ffa6,0x7919,0x4fd4,{0x8b,0xd8,0x43,0xaa,0xaa,0x4d,0xe9,0xda}};


const IID LIBID_FLEXSTAGELib = {0x49a6994a,0x8cba,0x41f6,{0x85,0xb7,0x2d,0x1a,0xd0,0x8c,0x57,0x93}};


const CLSID CLSID_FlexStage3 = {0x65f0bf0a,0xc417,0x40ca,{0x9f,0xa6,0xf1,0x53,0x99,0xb6,0x0b,0xf2}};


#ifdef __cplusplus
}
#endif

