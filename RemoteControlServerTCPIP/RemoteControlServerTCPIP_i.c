/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 27 10:46:25 2002
 */
/* Compiler settings for K:\SySal2\RemoteControlServerTCPIP\RemoteControlServerTCPIP.idl:
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


const IID IID_IRemoteControlServer = {0x09AFBFFE,0xBBA9,0x4A5A,{0x91,0x66,0x35,0x2A,0x73,0xCF,0xCA,0x32}};


const IID LIBID_REMOTECONTROLSERVERTCPIPLib = {0x1B11D019,0x4F75,0x43EB,{0xBD,0xDD,0x01,0x10,0xBA,0x57,0x2B,0x5C}};


const CLSID CLSID_RemoteControlServerTCPIP = {0x7D8FCEFA,0xE081,0x4559,{0xB6,0xD6,0xF8,0xAC,0x7A,0xB0,0x95,0x00}};


#ifdef __cplusplus
}
#endif

