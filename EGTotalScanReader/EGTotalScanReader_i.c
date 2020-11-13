/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 05 12:19:51 2001
 */
/* Compiler settings for K:\SySal2\EGTotalScanReader\EGTotalScanReader.idl:
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

const IID IID_ITotalScanReader = {0x4FFCE093,0xA083,0x4E0A,{0xB2,0x66,0xC7,0x66,0x00,0x81,0xC3,0xF3}};


const IID LIBID_EGTOTALSCANREADERLib = {0x57530DB5,0xD2B2,0x4351,{0xA1,0x88,0xE2,0xB8,0x04,0x6A,0x2D,0xCA}};


const CLSID CLSID_EGTotalScanReader = {0xA3FF8D06,0x9C71,0x41F9,{0x87,0x55,0x35,0x2D,0x41,0xF0,0x68,0xEA}};


#ifdef __cplusplus
}
#endif

