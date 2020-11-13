/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Apr 19 16:06:23 2006
 */
/* Compiler settings for C:\sysal\VertigoScan4VC7\VertigoScan4.idl:
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


const IID LIBID_VERTIGOSCAN4Lib = {0x855b30ec,0x30fe,0x4921,{0xad,0x2a,0x79,0x0e,0x2d,0x38,0x0a,0x62}};


const CLSID CLSID_VertigoScan4 = {0x0be1bbe0,0x977b,0x4fc6,{0x89,0xfe,0x11,0xda,0x10,0x81,0xdd,0x69}};


#ifdef __cplusplus
}
#endif

