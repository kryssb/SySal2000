/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 26 15:37:13 1999
 */
/* Compiler settings:
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

const IID IID_ITrackFitter = {0x9061992E,0x87FC,0x11D3,{0xA4,0x7C,0xCB,0xD9,0x48,0x9C,0x09,0x20}};


const IID IID_ITrackFitter2 = {0x950c2406,0xd41e,0x47d1,{0x9f,0x84,0xa1,0xbf,0xc0,0x40,0x29,0xc5}};


const IID IID_ITrackFitter3 = {0x855fe3ff,0xb30f,0x4ad2,{0x98,0x10,0x47,0x1e,0xdf,0xc9,0xf4,0xb8}};


#ifdef __cplusplus
}
#endif

