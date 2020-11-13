/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Apr 15 19:34:30 2001
 */
/* Compiler settings for K:\SySal2\EtaTracking\EtaTracking.idl:
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


const IID LIBID_ETATRACKINGLib = {0x3B651EB3,0xF4D8,0x11D3,{0xBF,0x85,0x00,0x20,0x18,0xB8,0x09,0x60}};


const CLSID CLSID_EtaTracking = {0x3B651EC1,0xF4D8,0x11D3,{0xBF,0x85,0x00,0x20,0x18,0xB8,0x09,0x60}};


#ifdef __cplusplus
}
#endif
