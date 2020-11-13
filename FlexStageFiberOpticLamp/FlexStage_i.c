/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 11 12:03:27 2002
 */
/* Compiler settings for D:\SySal2\FlexStage\FlexStage.idl:
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


const IID LIBID_FLEXSTAGELib = {0xDD99D358,0x8B3C,0x40F5,{0xB8,0xF6,0x9C,0xDE,0xE0,0x3B,0x06,0x03}};


const CLSID CLSID_FlexStage = {0x9c0bd047,0x82c1,0x4ab1,{0x83,0xb8,0x97,0x5d,0xe9,0xd8,0x9c,0x18}};


#ifdef __cplusplus
}
#endif

