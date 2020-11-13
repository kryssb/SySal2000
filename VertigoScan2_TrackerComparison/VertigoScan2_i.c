/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 25 15:49:44 2003
 */
/* Compiler settings for D:\SySal2\VertigoScan2\VertigoScan2.idl:
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


const IID LIBID_VERTIGOSCAN2Lib = {0x73e98c55,0x403e,0x4ffc,{0x9c,0xc9,0x9a,0xb9,0xd8,0x33,0x30,0xed}};


const CLSID CLSID_VertigoScan2 = {0xebbb5a33,0xd6b6,0x49df,{0x93,0x14,0x1d,0xa7,0xc9,0xd4,0x66,0x5c}};


#ifdef __cplusplus
}
#endif

