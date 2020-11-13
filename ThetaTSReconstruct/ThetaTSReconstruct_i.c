/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 22 00:18:12 2002
 */
/* Compiler settings for D:\SySal2\ThetaTSReconstruct\ThetaTSReconstruct.idl:
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


const IID IID_ISySalObject2 = {0x68659AF8,0x12E6,0x4EF9,{0x98,0x77,0xA7,0xDD,0x63,0xBF,0x19,0x50}};


const IID LIBID_THETATSRECONSTRUCTLib = {0x46f18c4b,0x3e26,0x4687,{0xb1,0xc9,0xdc,0x41,0x88,0x78,0x17,0x90}};


const CLSID CLSID_ThetaTSReconstruct = {0x27011d15,0x11a2,0x4fbe,{0x8a,0xd7,0xbd,0x6f,0x16,0x10,0x42,0xfa}};


#ifdef __cplusplus
}
#endif
