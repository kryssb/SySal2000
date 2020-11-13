/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 20 16:01:04 2002
 */
/* Compiler settings for D:\SySal2\GenK66Clustering_1\GenK66Clustering_1.idl:
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


const IID IID_IClusterFinder = {0x9E060533,0x7AAA,0x11D3,{0xA4,0x7C,0xBC,0x68,0xBC,0x67,0x0E,0x2B}};


const IID IID_ILockUnlock = {0x9E060534,0x7AAA,0x11D3,{0xA4,0x7C,0xBC,0x68,0xBC,0x67,0x0E,0x2B}};


const IID IID_IBoundedClusterFinder = {0x57FB9192,0x0F6A,0x4263,{0x87,0xE4,0xD1,0x4B,0x39,0x26,0x44,0xF0}};


const IID LIBID_GENK66CLUSTERING_1Lib = {0x4AD314C0,0xA033,0x11D3,{0xA4,0x7D,0xA9,0xA7,0x7D,0x89,0x89,0x3C}};


const CLSID CLSID_GenK66_1 = {0x4AD314CE,0xA033,0x11D3,{0xA4,0x7D,0xA9,0xA7,0x7D,0x89,0x89,0x3C}};


#ifdef __cplusplus
}
#endif

