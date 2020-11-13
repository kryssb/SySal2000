/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 08 13:37:27 2002
 */
/* Compiler settings for K:\SySal2\BetaBrain\BetaBrain.idl:
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


const IID LIBID_BETABRAINLib = {0x4EFD4EF2,0x010A,0x4770,{0xAA,0xBF,0x8A,0xC2,0xFE,0x56,0x0B,0xCD}};


const CLSID CLSID_BetaBrain = {0xBA1EBBCC,0x2B91,0x4D1F,{0xAD,0xAA,0x29,0x43,0xAD,0x5C,0x9F,0x7E}};


#ifdef __cplusplus
}
#endif

