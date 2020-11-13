/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 01 10:01:47 2005
 */
/* Compiler settings for D:\SySal2\VertigoScan3\VertigoScan3.idl:
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


const IID LIBID_VERTIGOSCAN3Lib = {0x0a856de9,0x492f,0x441b,{0x89,0xa9,0x9b,0x8e,0x5b,0xb1,0xf0,0x37}};


const CLSID CLSID_VertigoScan3 = {0xfab96ed6,0xab4c,0x4e2e,{0x9b,0x73,0x4d,0x71,0xd2,0x9b,0xa1,0x05}};


#ifdef __cplusplus
}
#endif

