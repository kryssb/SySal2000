/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jul 14 19:37:59 2002
 */
/* Compiler settings for D:\SySal2\VertigoScan\VertigoScan.idl:
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


const IID LIBID_VERTIGOSCANLib = {0x3B2DE3E6,0x7425,0x45F2,{0x93,0x30,0xC6,0xB7,0x14,0xD7,0xC3,0x21}};


const CLSID CLSID_VertigoScan = {0x112E2F08,0x715A,0x4513,{0x8C,0xA9,0x3D,0x1E,0xC1,0x03,0x50,0x01}};


#ifdef __cplusplus
}
#endif

