/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jun 12 11:33:05 2006
 */
/* Compiler settings for C:\sysal2000\VertigoScan5\VertigoScan5.idl:
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


const IID LIBID_VERTIGOSCAN5Lib = {0x01a2fa2f,0x8803,0x49ad,{0xbb,0xbe,0x15,0xa3,0x7a,0x96,0x17,0x12}};


const CLSID CLSID_VertigoScan5 = {0x85bb9f69,0x35c3,0x4600,{0x89,0x58,0x16,0xd7,0xd0,0x4b,0x71,0x57}};


#ifdef __cplusplus
}
#endif

