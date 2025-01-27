/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 06 08:48:06 2002
 */
/* Compiler settings for D:\SySal2\StageTest\StageTest.idl:
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


const IID LIBID_STAGETESTLib = {0x24646D75,0x90E9,0x4303,{0x89,0xCE,0xAC,0xB8,0x89,0x50,0x1C,0xB4}};


const CLSID CLSID_StageTest = {0xCF858251,0xD5A2,0x4373,{0x8A,0x24,0x71,0x96,0x04,0x07,0xB0,0xBC}};


#ifdef __cplusplus
}
#endif

