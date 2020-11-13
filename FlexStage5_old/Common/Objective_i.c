/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 07 21:44:55 1999
 */
/* Compiler settings
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

const IID IID_IObjective = {0xE056524D,0x7CFD,0x11D3,{0xA4,0x7C,0xAC,0x71,0xB6,0xA4,0x1C,0x20}};

const IID IID_IObjective2 = {0x9e7b8b40,0x7b28,0x4f5f,{0x80,0x9f,0x00,0x2c,0xba,0xc9,0x72,0x41}};


#ifdef __cplusplus
}
#endif

