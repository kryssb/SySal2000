/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Mar 31 17:46:04 2002
 */
/* Compiler settings for K:\SySal2\Thin3DTracker\Thin3DTracker.idl:
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


const IID LIBID_THIN3DTRACKERLib = {0x976b9330,0x745c,0x4315,{0x91,0x01,0xe3,0xfe,0xf6,0x80,0xad,0xd1}};


const CLSID CLSID_Thin3DTrk = {0x27d4a7c9,0x05e8,0x4691,{0xbb,0x60,0xcb,0xbc,0x0c,0x39,0x7d,0xec}};


#ifdef __cplusplus
}
#endif

