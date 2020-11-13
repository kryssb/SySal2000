/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Mar 22 12:44:00 2004
 */
/* Compiler settings for D:\SySal2\SmartTracker6\SmartTracker6.idl:
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


const IID IID_ITracker = {0xE416C46D,0x7F68,0x11D3,{0xA4,0x7C,0xFA,0x1E,0x4A,0xFA,0x27,0x21}};


const IID IID_ITracker2 = {0x67a71430,0xf2e4,0x42ae,{0x89,0x10,0x28,0x27,0x9a,0x76,0x16,0xd6}};


const IID IID_ITracker3 = {0x7a9e779c,0xaa32,0x4565,{0x8e,0x69,0x5f,0x1b,0xc4,0xe3,0x62,0xb7}};


const IID LIBID_SMARTTRACKERLib = {0x0d4bad6e,0xc5d9,0x4641,{0x87,0x6a,0xd7,0xd7,0xd9,0x88,0x3a,0x9a}};


const CLSID CLSID_SmartTracker6 = {0x92342e96,0x2d1f,0x409c,{0xa9,0x9a,0x15,0xe0,0xb7,0x89,0x42,0x43}};


#ifdef __cplusplus
}
#endif

