/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 01 10:42:53 2004
 */
/* Compiler settings for D:\SySal2\FlexStage2\FlexStage2.idl:
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


const IID LIBID_FLEXSTAGELib = {0x936311f9,0x5ab5,0x4483,{0x8c,0x7a,0x3b,0x26,0x4b,0x14,0x7a,0x09}};


const CLSID CLSID_FlexStage2 = {0xead9ce32,0xa109,0x4b0c,{0x85,0x86,0xda,0x2f,0xa4,0x8e,0x41,0x3e}};


#ifdef __cplusplus
}
#endif

