/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Jun 08 10:38:56 2002
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


const IID IID_ISySalObject2 = {0x68659AF8,0x12E6,0x4EF9,{0x98,0x77,0xA7,0xDD,0x63,0xBF,0x19,0x50}};


const IID LIBID_STAGETESTLib = {0x3B56F8C6,0x4E1C,0x47B4,{0x86,0x5E,0x95,0x05,0x12,0x7A,0x27,0xE1}};


const CLSID CLSID_StageTest = {0xD654A077,0xEB78,0x4B30,{0xB3,0x94,0xEB,0xF6,0xA2,0x41,0x01,0xBB}};


#ifdef __cplusplus
}
#endif

