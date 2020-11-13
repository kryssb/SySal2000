/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 11 16:28:30 2002
 */
/* Compiler settings for D:\SySal2\FlexStageFiberOpticLamp\FlexStageFiberOpticLamp.idl:
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


const IID LIBID_FLEXSTAGELib = {0x04377cd3,0x366c,0x4904,{0xbb,0x2e,0x2e,0x94,0xaa,0xa9,0x5f,0x37}};


const CLSID CLSID_FlexStageFiberOpticLamp = {0x13efec72,0x9442,0x434b,{0x9f,0xa4,0x91,0x09,0x73,0xbf,0xc9,0x3f}};


#ifdef __cplusplus
}
#endif

