/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Oct 17 18:34:27 2001
 */
/* Compiler settings for K:\SySal2\IdentityMap\IdentityMap.idl:
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


const IID IID_ISheetMap = {0xD0FEF450,0xB910,0x4D5D,{0x90,0x8C,0x9E,0x1E,0x64,0xEA,0x7F,0xA1}};


const IID LIBID_IDENTITYMAPLib = {0x17F3B4B3,0x35D0,0x450B,{0xBC,0x8A,0x29,0x4D,0x78,0x68,0xCA,0x56}};


const CLSID CLSID_IdentityMap = {0x20AF3AA0,0xF048,0x4EF7,{0xA6,0x27,0x5B,0x39,0x47,0xDE,0x6A,0x62}};


#ifdef __cplusplus
}
#endif

