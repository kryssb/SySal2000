/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 02 23:17:15 2001
 */
/* Compiler settings for K:\SySal2\EGClusterDumpReader\EGClusterDumpReader.idl:
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

const IID IID_IEGClusterDumpReader = {0xB707E25A,0xF9F3,0x4619,{0x9C,0xBB,0xDF,0xAC,0x5E,0x4C,0xB6,0xB9}};


const IID LIBID_EGCLUSTERDUMPREADERLib = {0xF108D1D4,0x8E39,0x4B0F,{0x86,0x51,0x79,0x2C,0x99,0xE4,0xE6,0x6A}};


const CLSID CLSID_CEGClusterDumpReader = {0xE45649A5,0x108D,0x41CA,{0xBA,0xEA,0x7E,0xA6,0xC6,0xE4,0x0B,0xFE}};


#ifdef __cplusplus
}
#endif

