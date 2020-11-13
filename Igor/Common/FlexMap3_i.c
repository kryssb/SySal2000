/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jun 13 15:22:30 2005
 */
/* Compiler settings for C:\sysal\FlexMap3\FlexMap3.idl:
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



const IID IID_ISheetMap = {0xD0FEF450,0xB910,0x4D5D,{0x90,0x8C,0x9E,0x1E,0x64,0xEA,0x7F,0xA1}};


const IID IID_ISheetMap2 = {0x6bc68332,0x752b,0x489c,{0xae,0x7d,0xa4,0x5d,0xb6,0x23,0xb7,0x33}};


const IID LIBID_FLEXMAPLib = {0xb6029934,0xa40f,0x44a0,{0xac,0x39,0x21,0x3a,0xbc,0xd4,0xe6,0x30}};


const CLSID CLSID_FlexibleMap = {0x21f86780,0x9e04,0x4b5a,{0x8a,0xb0,0xbe,0x55,0x32,0x45,0x34,0xd3}};


#ifdef __cplusplus
}
#endif

