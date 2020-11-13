/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jul 06 17:46:52 2006
 */
/* Compiler settings for D:\SySal2\PlateChanger\PlateChanger.idl:
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


const IID IID_IPlateChanger = {0x11c61d6e,0x34b8,0x4562,{0xb7,0xf5,0xd1,0x7f,0xf6,0x4d,0x85,0x6b}};


const IID LIBID_PLATECHANGERLib = {0x17db0e83,0x2ed1,0x4d98,{0xb3,0x6d,0xb0,0x0a,0xe0,0x25,0x45,0xfb}};


const CLSID CLSID_PlateChanger = {0x25e7bc2b,0xb7a1,0x4a42,{0xa6,0x87,0x5b,0xb8,0x15,0xa3,0x1a,0xdf}};


#ifdef __cplusplus
}
#endif

