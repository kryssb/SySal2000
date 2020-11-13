/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Oct 09 17:00:06 1999
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

const IID IID_IClusterFinder = {0x9E060533,0x7AAA,0x11D3,{0xA4,0x7C,0xBC,0x68,0xBC,0x67,0x0E,0x2B}};


const IID IID_ILockUnlock = {0x9E060534,0x7AAA,0x11D3,{0xA4,0x7C,0xBC,0x68,0xBC,0x67,0x0E,0x2B}};


#ifdef __cplusplus
}
#endif

