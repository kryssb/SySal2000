/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 16:24:12 2002
 */
/* Compiler settings for K:\SySal2\Objective\Objective.idl:
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


const IID IID_IObjective = {0xE056524D,0x7CFD,0x11D3,{0xA4,0x7C,0xAC,0x71,0xB6,0xA4,0x1C,0x20}};


const IID IID_IObjective2 = {0x9e7b8b40,0x7b28,0x4f5f,{0x80,0x9f,0x00,0x2c,0xba,0xc9,0x72,0x41}};


const IID LIBID_OBJECTIVELib = {0xE0565240,0x7CFD,0x11D3,{0xA4,0x7C,0xAC,0x71,0xB6,0xA4,0x1C,0x20}};


const CLSID CLSID_Objective = {0xE056524E,0x7CFD,0x11D3,{0xA4,0x7C,0xAC,0x71,0xB6,0xA4,0x1C,0x20}};


#ifdef __cplusplus
}
#endif

