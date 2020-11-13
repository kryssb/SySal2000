/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 04 17:06:07 2001
 */
/* Compiler settings for K:\SySal2\EGTotalScanWriter\EGTotalScanWriter.idl:
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

const IID IID_ITotalScanWriter = {0xF2F81CC6,0xDB70,0x4BC4,{0x9F,0x49,0x91,0x95,0x72,0xE9,0x2B,0xFC}};


const IID LIBID_EGTOTALSCANWRITERLib = {0xDA9084C2,0xD1CE,0x417F,{0xB4,0x5E,0xCB,0xE7,0x65,0x93,0x0F,0x93}};


const CLSID CLSID_EGTotalScanWriter = {0x39372219,0xD1FB,0x47E1,{0xA6,0xF9,0x78,0x60,0x8B,0xAD,0x26,0x25}};


#ifdef __cplusplus
}
#endif

