/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Mar 10 23:03:06 2003
 */
/* Compiler settings for D:\SySal2000\TSReconstruct\TSReconstruct.idl:
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


const IID LIBID_TSRECONSTRUCTLib = {0x5E500E03,0x2669,0x437C,{0x89,0xBC,0x25,0xC3,0xD3,0x77,0x50,0x69}};


const CLSID CLSID_TSReconstruct = {0x86AC0EA2,0xDFA9,0x4844,{0xA7,0x7F,0xAF,0xB9,0xBA,0x0B,0x9C,0x77}};


#ifdef __cplusplus
}
#endif

