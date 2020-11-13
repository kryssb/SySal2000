/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Sep 08 11:06:56 2002
 */
/* Compiler settings for D:\SySal2\FragmentLinker2\FragmentLinker2.idl:
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

const IID IID_IFragmentLinker = {0xE898E034,0xC562,0x4CFA,{0x87,0x15,0x62,0xFB,0xEC,0x72,0x33,0x0A}};


const IID LIBID_FRAGMENTLINKERLib = {0x599D722E,0x14AA,0x4138,{0xB7,0xA9,0x66,0x64,0x21,0x16,0xC4,0x43}};


const CLSID CLSID_FragmentLinker = {0xCB1F845A,0xAE8C,0x433B,{0xAE,0xFD,0x25,0xB8,0x26,0x97,0x4F,0xC9}};


#ifdef __cplusplus
}
#endif

