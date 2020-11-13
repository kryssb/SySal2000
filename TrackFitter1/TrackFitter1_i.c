/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 08 13:41:23 2002
 */
/* Compiler settings for K:\SySal2\TrackFitter1\TrackFitter1.idl:
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


const IID IID_ITrackFitter = {0x9061992E,0x87FC,0x11D3,{0xA4,0x7C,0xCB,0xD9,0x48,0x9C,0x09,0x20}};


const IID IID_ITrackFitter2 = {0x950c2406,0xd41e,0x47d1,{0x9f,0x84,0xa1,0xbf,0xc0,0x40,0x29,0xc5}};


const IID LIBID_TRACKFITTER1Lib = {0x90619920,0x87FC,0x11D3,{0xA4,0x7C,0xCB,0xD9,0x48,0x9C,0x09,0x20}};


const CLSID CLSID_TrackFitter = {0x9061992F,0x87FC,0x11D3,{0xA4,0x7C,0xCB,0xD9,0x48,0x9C,0x09,0x20}};


#ifdef __cplusplus
}
#endif

