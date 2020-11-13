/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Apr 02 09:25:08 2002
 */
/* Compiler settings for K:\SySal2\SmartTracker\SmartTracker.idl:
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


const IID LIBID_SMARTTRACKERLib = {0xa0d0e0ef,0x677a,0x4031,{0x81,0xdf,0xf0,0xf7,0xee,0x99,0x85,0x23}};


const CLSID CLSID_SmartTracker = {0x9fca9469,0xaf77,0x48ec,{0xae,0x52,0x01,0x62,0xa8,0xd3,0x67,0x7a}};


#ifdef __cplusplus
}
#endif

