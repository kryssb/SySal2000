/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Apr 15 20:23:28 2001
 */
/* Compiler settings for K:\SySal2\DBSySalIO\DBSySalIO.idl:
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


const IID IID_ISySalDataIO = {0x4B47E8CD,0x894C,0x11D3,{0xA4,0x7C,0x9F,0x37,0x35,0x22,0x60,0x36}};


const IID LIBID_DBSYSALIOLib = {0x8ABBFDCA,0xF81F,0x4636,{0xAB,0xCA,0x8D,0x56,0x93,0xB2,0x6F,0x05}};


const CLSID CLSID_DBSySalIO = {0x0FA1DF57,0x68A4,0x494E,{0xB3,0x31,0xEF,0x2A,0x03,0x5B,0x66,0x1C}};


#ifdef __cplusplus
}
#endif

