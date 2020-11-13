/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Apr 12 11:09:27 2000
 */
/* Compiler settings for C:\DX7APPS\EmuDisplay\EmuDisplay.idl:
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

const IID IID_IEmulsionDisplay = {0xB8E981FE,0x3C7B,0x43A5,{0xA3,0x57,0x90,0xAC,0x81,0x11,0x2A,0xA1}};


const IID LIBID_EMUDISPLAYLib = {0xA5051DCE,0xCD2B,0x4A90,{0x92,0x74,0x40,0xF1,0x8C,0x7C,0x7E,0x28}};


const CLSID CLSID_EmulsionDisplay = {0x479A3154,0x0C9C,0x4414,{0x9C,0x21,0xEC,0x03,0xAB,0x31,0xBF,0xEE}};


#ifdef __cplusplus
}
#endif

