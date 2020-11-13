/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 21 15:28:53 2007
 */
/* Compiler settings for D:\SySal2\TecnoCutPlateChanger\TecnoCutPlateChanger.idl:
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


const IID LIBID_TECNOCUTPLATECHANGERLib = {0x2c4cb907,0xe8b4,0x44ff,{0xb6,0xb3,0x9a,0x52,0x4f,0xa4,0x85,0xa6}};


const CLSID CLSID_TecnoCutPlateChanger = {0xa188396f,0x5919,0x4687,{0xa7,0x1d,0x95,0xee,0x34,0xf1,0x56,0x49}};


#ifdef __cplusplus
}
#endif

