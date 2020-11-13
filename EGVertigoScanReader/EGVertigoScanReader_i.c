/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 18 16:05:23 2001
 */
/* Compiler settings for K:\SySal2\EGVertigoScanReader\EGVertigoScanReader.idl:
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

const IID IID_IEGVSCatalog = {0xFFEB0997,0x2C45,0x4B3A,{0xBF,0xA6,0xF9,0x65,0x1D,0xBB,0xF1,0xEC}};


const IID IID_IEGVSFragment = {0xA4EB4D71,0xD295,0x4933,{0x85,0x47,0x90,0x36,0xB8,0x76,0x6D,0x63}};


const IID LIBID_EGVERTIGOSCANREADERLib = {0xB6AF5F56,0x9B24,0x4885,{0xA2,0x8D,0x33,0x60,0x30,0x5B,0x4D,0xE4}};


const CLSID CLSID_EGVSCatalog = {0xAA3E984D,0x7CD0,0x4329,{0x92,0x67,0x7A,0x2D,0x58,0x63,0xB2,0x9D}};


const CLSID CLSID_EGVSFragment = {0x6898CEEA,0xFB49,0x4C31,{0xB9,0x45,0x86,0xD9,0x1F,0x29,0x81,0xA6}};


#ifdef __cplusplus
}
#endif

