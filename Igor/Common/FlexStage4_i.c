/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 08 15:31:39 2005
 */
/* Compiler settings for C:\sysal\FlexStage4\FlexStage4.idl:
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


const IID IID_ISySalObjectMachineDefaults = {0x455b5e46,0x0c34,0x443e,{0x87,0x9b,0x53,0x94,0x1a,0x71,0x02,0x6f}};


const IID IID_IStage = {0x075E1B0D,0xC472,0x11D3,{0xA4,0x7E,0xDC,0x13,0x18,0xA5,0x1E,0x33}};


const IID IID_IStage2 = {0x3cf5ffa6,0x7919,0x4fd4,{0x8b,0xd8,0x43,0xaa,0xaa,0x4d,0xe9,0xda}};


const IID IID_IStage3 = {0x29ca8106,0xdc50,0x4908,{0xb3,0x96,0x4c,0xb8,0x4b,0x49,0x25,0x5e}};


const IID LIBID_FLEXSTAGELib = {0x0ea23723,0xd304,0x476a,{0xba,0xf1,0x4e,0xed,0xec,0x17,0xb9,0x64}};


const CLSID CLSID_FlexStage4 = {0x15475b85,0xc802,0x4b7d,{0xbd,0xb3,0x9a,0x35,0x6e,0xe3,0x63,0x0b}};


#ifdef __cplusplus
}
#endif

