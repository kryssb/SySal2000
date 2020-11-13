

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Dec 05 10:24:11 2008
 */
/* Compiler settings for .\Odyssey3.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "Odyssey3.h"

#define TYPE_FORMAT_STRING_SIZE   245                               
#define PROC_FORMAT_STRING_SIZE   2893                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISySalObject_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISySalObject_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IFrameGrabber_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IFrameGrabber_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisionProcessor_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisionProcessor_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisionProcessor2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisionProcessor2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAutomaticLightControl_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAutomaticLightControl_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisionProcessor3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisionProcessor3_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisionProcessor4_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisionProcessor4_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetName */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x50 ),	/* 80 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 24 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetName */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x4 ),	/* 4 */
/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 46 */	NdrFcShort( 0x50 ),	/* 80 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 60 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetConfig */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 74 */	NdrFcLong( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x5 ),	/* 5 */
/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 82 */	NdrFcShort( 0x91 ),	/* 145 */
/* 84 */	NdrFcShort( 0x8 ),	/* 8 */
/* 86 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 88 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pConfig */

/* 96 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 100 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetConfig */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x6 ),	/* 6 */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x91 ),	/* 145 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 124 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pConfig */

/* 132 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 136 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EditConfig */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0x7 ),	/* 7 */
/* 152 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 154 */	NdrFcShort( 0x99 ),	/* 153 */
/* 156 */	NdrFcShort( 0x8 ),	/* 8 */
/* 158 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 160 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pConfig */

/* 168 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 172 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Parameter hWnd */

/* 174 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableMonitor */

/* 186 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 188 */	NdrFcLong( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x8 ),	/* 8 */
/* 194 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 196 */	NdrFcShort( 0x5 ),	/* 5 */
/* 198 */	NdrFcShort( 0x8 ),	/* 8 */
/* 200 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 202 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bEnable */

/* 210 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 212 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 214 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 216 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 218 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetProgramCount */


	/* Procedure GetNumberOfConnections */

/* 222 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 224 */	NdrFcLong( 0x0 ),	/* 0 */
/* 228 */	NdrFcShort( 0x9 ),	/* 9 */
/* 230 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 232 */	NdrFcShort( 0x1c ),	/* 28 */
/* 234 */	NdrFcShort( 0x8 ),	/* 8 */
/* 236 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 238 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 244 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pCount */


	/* Parameter pNumber */

/* 246 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 248 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 252 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 254 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetConnection */

/* 258 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 260 */	NdrFcLong( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0xa ),	/* 10 */
/* 266 */	NdrFcShort( 0x54 ),	/* x86 Stack size/offset = 84 */
/* 268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 270 */	NdrFcShort( 0x8 ),	/* 8 */
/* 272 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 274 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter n */

/* 282 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 284 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter connection */

/* 288 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 290 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 292 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 296 */	NdrFcShort( 0x50 ),	/* x86 Stack size/offset = 80 */
/* 298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetConnection */

/* 300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 306 */	NdrFcShort( 0xb ),	/* 11 */
/* 308 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 310 */	NdrFcShort( 0x8 ),	/* 8 */
/* 312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 314 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 316 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 322 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter n */

/* 324 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pConnection */

/* 330 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 332 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 334 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetIcon */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0xc ),	/* 12 */
/* 350 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 352 */	NdrFcShort( 0x24 ),	/* 36 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 356 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 358 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter n */

/* 366 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 368 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 370 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pHICON */

/* 372 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 374 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 378 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetClassName */

/* 384 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 386 */	NdrFcLong( 0x0 ),	/* 0 */
/* 390 */	NdrFcShort( 0xd ),	/* 13 */
/* 392 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 394 */	NdrFcShort( 0x50 ),	/* 80 */
/* 396 */	NdrFcShort( 0x8 ),	/* 8 */
/* 398 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 400 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 406 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 408 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 412 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 416 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SyncExec */

/* 420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0xe ),	/* 14 */
/* 428 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 434 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 436 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 442 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 444 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 446 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 448 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncExec */

/* 450 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 452 */	NdrFcLong( 0x0 ),	/* 0 */
/* 456 */	NdrFcShort( 0xf ),	/* 15 */
/* 458 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 460 */	NdrFcShort( 0x8 ),	/* 8 */
/* 462 */	NdrFcShort( 0x8 ),	/* 8 */
/* 464 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 466 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 468 */	NdrFcShort( 0x0 ),	/* 0 */
/* 470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter HNotifyStatusChangeEvent */

/* 474 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 476 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 480 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 482 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncCheckStatus */

/* 486 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x10 ),	/* 16 */
/* 494 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 496 */	NdrFcShort( 0x1c ),	/* 28 */
/* 498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 500 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 502 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pStatus */

/* 510 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 512 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 516 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 518 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncWait */

/* 522 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 524 */	NdrFcLong( 0x0 ),	/* 0 */
/* 528 */	NdrFcShort( 0x11 ),	/* 17 */
/* 530 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	NdrFcShort( 0x8 ),	/* 8 */
/* 536 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 538 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 546 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 548 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 550 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPWaitForClusters */


	/* Procedure AsyncPause */

/* 552 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 554 */	NdrFcLong( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0x12 ),	/* 18 */
/* 560 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x8 ),	/* 8 */
/* 566 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 568 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */


	/* Return value */

/* 576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 578 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncStop */

/* 582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x13 ),	/* 19 */
/* 590 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x8 ),	/* 8 */
/* 596 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 598 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 606 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncResume */

/* 612 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0x14 ),	/* 20 */
/* 620 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 626 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 628 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 636 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 638 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsReady */

/* 642 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 644 */	NdrFcLong( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0x15 ),	/* 21 */
/* 650 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 652 */	NdrFcShort( 0x38 ),	/* 56 */
/* 654 */	NdrFcShort( 0x8 ),	/* 8 */
/* 656 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 658 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pWrongConn */

/* 666 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 668 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetCode */

/* 672 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 674 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 676 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 680 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VideoInfo */

/* 684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x3 ),	/* 3 */
/* 692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 700 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter VIS */

/* 708 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 710 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 712 */	NdrFcShort( 0x54 ),	/* Type Offset=84 */

	/* Return value */

/* 714 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 716 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GrabInfo */

/* 720 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 722 */	NdrFcLong( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x4 ),	/* 4 */
/* 728 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 730 */	NdrFcShort( 0x38 ),	/* 56 */
/* 732 */	NdrFcShort( 0x8 ),	/* 8 */
/* 734 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 736 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter GIS */

/* 744 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 748 */	NdrFcShort( 0x6c ),	/* Type Offset=108 */

	/* Return value */

/* 750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPalette */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x5 ),	/* 5 */
/* 764 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 766 */	NdrFcShort( 0x45 ),	/* 69 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 772 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter PS */

/* 780 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 782 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 784 */	NdrFcShort( 0x80 ),	/* Type Offset=128 */

	/* Return value */

/* 786 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 788 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetPalette */

/* 792 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 794 */	NdrFcLong( 0x0 ),	/* 0 */
/* 798 */	NdrFcShort( 0x6 ),	/* 6 */
/* 800 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 802 */	NdrFcShort( 0x45 ),	/* 69 */
/* 804 */	NdrFcShort( 0x8 ),	/* 8 */
/* 806 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 808 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter PS */

/* 816 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 818 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 820 */	NdrFcShort( 0x80 ),	/* Type Offset=128 */

	/* Return value */

/* 822 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 824 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 826 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetDefaultPalette */

/* 828 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 830 */	NdrFcLong( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x7 ),	/* 7 */
/* 836 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x8 ),	/* 8 */
/* 842 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 844 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 852 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 854 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetColorCode */

/* 858 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 866 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 868 */	NdrFcShort( 0x24 ),	/* 36 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 874 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Color */

/* 882 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 884 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 886 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pCode */

/* 888 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 890 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 892 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 894 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 896 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 898 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Dot */

/* 900 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 902 */	NdrFcLong( 0x0 ),	/* 0 */
/* 906 */	NdrFcShort( 0x9 ),	/* 9 */
/* 908 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 910 */	NdrFcShort( 0x18 ),	/* 24 */
/* 912 */	NdrFcShort( 0x8 ),	/* 8 */
/* 914 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 916 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x0 ),	/* 0 */
/* 922 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter X */

/* 924 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 926 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 928 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 930 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 932 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 936 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 938 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 942 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 944 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 946 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Fill */

/* 948 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 950 */	NdrFcLong( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0xa ),	/* 10 */
/* 956 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 958 */	NdrFcShort( 0x18 ),	/* 24 */
/* 960 */	NdrFcShort( 0x8 ),	/* 8 */
/* 962 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 964 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 966 */	NdrFcShort( 0x0 ),	/* 0 */
/* 968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 970 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter X */

/* 972 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 974 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 978 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 980 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 982 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 984 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 986 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 988 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 990 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 992 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 994 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Arc */

/* 996 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 998 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1002 */	NdrFcShort( 0xb ),	/* 11 */
/* 1004 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 1006 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1008 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1010 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x8,		/* 8 */
/* 1012 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1014 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1018 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter XC */

/* 1020 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1022 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1024 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YC */

/* 1026 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1028 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1030 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XR */

/* 1032 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1034 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1036 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YR */

/* 1038 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1040 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1042 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter SA */

/* 1044 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1046 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1048 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter EA */

/* 1050 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1052 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1054 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter C */

/* 1056 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1058 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 1060 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1062 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1064 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 1066 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ArcFill */

/* 1068 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1070 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1074 */	NdrFcShort( 0xc ),	/* 12 */
/* 1076 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 1078 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1080 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1082 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x8,		/* 8 */
/* 1084 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1090 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter XC */

/* 1092 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1094 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1096 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YC */

/* 1098 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1100 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1102 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XR */

/* 1104 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1106 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1108 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YR */

/* 1110 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1112 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1114 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter SA */

/* 1116 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1118 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1120 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter EA */

/* 1122 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1124 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1126 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter C */

/* 1128 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1130 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 1132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1136 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 1138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Rect */

/* 1140 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1142 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1146 */	NdrFcShort( 0xd ),	/* 13 */
/* 1148 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1150 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1154 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x6,		/* 6 */
/* 1156 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter XS */

/* 1164 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1166 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1170 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1172 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1174 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XE */

/* 1176 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1178 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1180 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YE */

/* 1182 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1184 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1186 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1188 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1190 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1192 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1194 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1196 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1198 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RectFill */

/* 1200 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1202 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1206 */	NdrFcShort( 0xe ),	/* 14 */
/* 1208 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1210 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1214 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x6,		/* 6 */
/* 1216 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1222 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter XS */

/* 1224 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1226 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1230 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1232 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XE */

/* 1236 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1238 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YE */

/* 1242 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1244 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1246 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1248 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1250 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1256 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Line */

/* 1260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1266 */	NdrFcShort( 0xf ),	/* 15 */
/* 1268 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1270 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1274 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x6,		/* 6 */
/* 1276 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1282 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter XS */

/* 1284 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1286 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1290 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1292 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XE */

/* 1296 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1298 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YE */

/* 1302 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1304 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1306 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1308 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1310 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1312 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1314 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1316 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1318 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Text */

/* 1320 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1322 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1326 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1328 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1330 */	NdrFcShort( 0x31 ),	/* 49 */
/* 1332 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1334 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 1336 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1342 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter XS */

/* 1344 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1346 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1348 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1350 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1352 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1354 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter S */

/* 1356 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1358 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1360 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Parameter C */

/* 1362 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1364 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1368 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1370 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure TextFont */

/* 1374 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1382 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1384 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1388 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1390 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1396 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter F */

/* 1398 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1400 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1406 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure TextScale */

/* 1410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1416 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1418 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1420 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1424 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1426 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1432 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter XS */

/* 1434 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1436 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1438 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1440 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1442 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1444 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1446 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1448 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1450 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clear */

/* 1452 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1454 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1458 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1460 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1462 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1464 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1466 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1468 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1474 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter C */

/* 1476 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1478 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1480 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1482 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1484 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetZoom */

/* 1488 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1496 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1498 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1502 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1504 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1510 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ZX */

/* 1512 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1514 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1516 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ZY */

/* 1518 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1520 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1524 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1526 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1528 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetOffset */

/* 1530 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1532 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1536 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1538 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1540 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1542 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1544 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1546 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1552 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter X */

/* 1554 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1556 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1560 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1562 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1566 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1570 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadCursor */

/* 1572 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1574 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1578 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1580 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1582 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1584 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1586 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1588 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1594 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter CursorFile */

/* 1596 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1598 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1600 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Return value */

/* 1602 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1604 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DeleteCursor */

/* 1608 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1610 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1614 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1616 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1620 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1622 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1624 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1630 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1632 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1634 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1636 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HideCursor */

/* 1638 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1640 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1644 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1646 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1650 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1652 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1654 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1660 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1664 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowCursor */

/* 1668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1676 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1682 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1684 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1692 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1696 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCursorPos */

/* 1698 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1700 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1704 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1706 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1708 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1710 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1712 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1714 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1720 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter X */

/* 1722 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1724 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1728 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1730 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1732 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1734 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1736 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1738 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCursorPos */

/* 1740 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1742 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1748 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1750 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1754 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1756 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1762 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter X */

/* 1764 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1766 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1768 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1770 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1772 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1774 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1776 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1778 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetNoGrab */

/* 1782 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1788 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1790 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1794 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1796 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1798 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1804 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1808 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetLiveGrab */

/* 1812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1818 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1820 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1826 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1828 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1834 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1836 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1838 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowLive */

/* 1842 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1844 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1848 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1850 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1854 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1856 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1858 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1860 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1864 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1866 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1868 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1870 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowFrozen */

/* 1872 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1874 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1878 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1880 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1886 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1888 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1894 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1896 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1898 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1900 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FreezeFrame */

/* 1902 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1904 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1908 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1910 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1912 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1914 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1916 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1918 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1920 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1924 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppImage */

/* 1926 */	NdrFcShort( 0x200a ),	/* Flags:  must free, in, srv alloc size=8 */
/* 1928 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1930 */	NdrFcShort( 0x9c ),	/* Type Offset=156 */

	/* Return value */

/* 1932 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1934 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1936 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ClearFrozen */

/* 1938 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1940 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1944 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1946 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1948 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1950 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1952 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1954 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1960 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1962 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1964 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1966 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetSingleFrameGrab */

/* 1968 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1970 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1974 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1976 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1980 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1982 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1984 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1988 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1990 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1992 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1994 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1996 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HoldFrame */

/* 1998 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2000 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2004 */	NdrFcShort( 0x23 ),	/* 35 */
/* 2006 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2008 */	NdrFcShort( 0x2d ),	/* 45 */
/* 2010 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2012 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2014 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2020 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppImage */

/* 2022 */	NdrFcShort( 0x200a ),	/* Flags:  must free, in, srv alloc size=8 */
/* 2024 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2026 */	NdrFcShort( 0x9c ),	/* Type Offset=156 */

	/* Return value */

/* 2028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2030 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowHeldFrame */

/* 2034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2042 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2048 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2050 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2056 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2058 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2060 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReleaseFrame */

/* 2064 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2070 */	NdrFcShort( 0x25 ),	/* 37 */
/* 2072 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2076 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2078 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2080 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2086 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2088 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2090 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCurrentFrameGrabDelay */

/* 2094 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2096 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2100 */	NdrFcShort( 0x26 ),	/* 38 */
/* 2102 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2104 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2106 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2108 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2110 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2116 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDelay */

/* 2118 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2120 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2124 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2126 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FlushGrabBackBuffers */

/* 2130 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2132 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2136 */	NdrFcShort( 0x27 ),	/* 39 */
/* 2138 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2142 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2144 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2146 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2152 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2154 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2156 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2158 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsGrabCycleLockable */

/* 2160 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2162 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2166 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2168 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2170 */	NdrFcShort( 0x19 ),	/* 25 */
/* 2172 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2174 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2176 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2182 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pAnswer */

/* 2184 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2186 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2188 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2190 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2192 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsGrabCycleLocked */

/* 2196 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2198 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2202 */	NdrFcShort( 0x29 ),	/* 41 */
/* 2204 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2206 */	NdrFcShort( 0x19 ),	/* 25 */
/* 2208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2210 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2212 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2218 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pAnswer */

/* 2220 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2222 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2224 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2226 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2228 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2230 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadStockCursor */

/* 2232 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2234 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2238 */	NdrFcShort( 0x2a ),	/* 42 */
/* 2240 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2244 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2246 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2248 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2254 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter StockCursorId */

/* 2256 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2262 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2264 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPLock */

/* 2268 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2274 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2276 */	NdrFcShort( 0x30 ),	/* x86 Stack size/offset = 48 */
/* 2278 */	NdrFcShort( 0x50 ),	/* 80 */
/* 2280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2282 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0xb,		/* 11 */
/* 2284 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2290 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Threshold */

/* 2292 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2294 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Width */

/* 2298 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2300 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2302 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Height */

/* 2304 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2306 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2308 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter OffX */

/* 2310 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2312 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2314 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter OffY */

/* 2316 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2318 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2320 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter WinWidth */

/* 2322 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2324 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter WinHeight */

/* 2328 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2330 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter PresetFrames */

/* 2334 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2336 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 2338 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pfnFrameStartCallBack */

/* 2340 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2342 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 2344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Context */

/* 2346 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2348 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 2350 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2352 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2354 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 2356 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPUnlock */

/* 2358 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2360 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2364 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2366 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2370 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2372 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2374 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2380 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2382 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2384 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2386 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPStart */

/* 2388 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2390 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2394 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2396 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2400 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2402 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2404 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2410 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2412 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2414 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2416 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPIterate */

/* 2418 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2420 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2424 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2426 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2428 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2430 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2432 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2434 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2440 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSpace */

/* 2442 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2444 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2446 */	NdrFcShort( 0xb4 ),	/* Type Offset=180 */

	/* Parameter pMaxClusters */

/* 2448 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2450 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2454 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2456 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2458 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPFlush */

/* 2460 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2462 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2466 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2468 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2470 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2472 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2474 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2476 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2478 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2482 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSpace */

/* 2484 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2486 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2488 */	NdrFcShort( 0xb4 ),	/* Type Offset=180 */

	/* Parameter pMaxClusters */

/* 2490 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2492 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2494 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2496 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2498 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2500 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetFrameDelay */

/* 2502 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2508 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2510 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2512 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2516 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2518 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2524 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDelay */

/* 2526 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2528 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2532 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2534 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2536 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetProgram */

/* 2538 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2540 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2544 */	NdrFcShort( 0xa ),	/* 10 */
/* 2546 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2548 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2552 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2554 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2560 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pProgram */

/* 2562 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2564 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2566 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2568 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2570 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2572 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPSetProgram */

/* 2574 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2576 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2580 */	NdrFcShort( 0xb ),	/* 11 */
/* 2582 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2584 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2586 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2588 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2590 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2596 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Program */

/* 2598 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2600 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2604 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2606 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2608 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPLock2 */

/* 2610 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2612 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2616 */	NdrFcShort( 0xc ),	/* 12 */
/* 2618 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2620 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2622 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2624 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2626 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2632 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfnFrameStartCallBack */

/* 2634 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2636 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Context */

/* 2640 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2642 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2644 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2646 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2648 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2650 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetPrimaryImage */

/* 2652 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2654 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2658 */	NdrFcShort( 0xd ),	/* 13 */
/* 2660 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2662 */	NdrFcShort( 0x19 ),	/* 25 */
/* 2664 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2666 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2668 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2674 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pImage */

/* 2676 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2678 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2680 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Return value */

/* 2682 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2684 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2686 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetLightLevel */

/* 2688 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2690 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2694 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2696 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2700 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2702 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2704 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2710 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2712 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2714 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPPrepareAsyncProcessing */

/* 2718 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2720 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2724 */	NdrFcShort( 0xe ),	/* 14 */
/* 2726 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 2728 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2730 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2732 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2734 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2740 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Program */

/* 2742 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2744 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2746 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ImageSeq */

/* 2748 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2750 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2752 */	NdrFcShort( 0xdc ),	/* Type Offset=220 */

	/* Return value */

/* 2754 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2756 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 2758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPStartAsyncProcessing */

/* 2760 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2762 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2766 */	NdrFcShort( 0xf ),	/* 15 */
/* 2768 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2772 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2774 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2776 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2782 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2784 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2786 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2788 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPWaitForProcessingComplete */

/* 2790 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2792 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2796 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2798 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2802 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2804 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2806 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2812 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2814 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2816 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetCurrentImageSequenceDelay */

/* 2820 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2822 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2826 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2828 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2830 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2832 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2834 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2836 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2842 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDelay */

/* 2844 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2846 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2848 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2850 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2852 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2854 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPWaitForProcessingCompleteAndExtractImages */

/* 2856 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2858 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2862 */	NdrFcShort( 0x13 ),	/* 19 */
/* 2864 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2866 */	NdrFcShort( 0x2d ),	/* 45 */
/* 2868 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2870 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2872 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2878 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppImages */

/* 2880 */	NdrFcShort( 0x200a ),	/* Flags:  must free, in, srv alloc size=8 */
/* 2882 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2884 */	NdrFcShort( 0x9c ),	/* Type Offset=156 */

	/* Return value */

/* 2886 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2888 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2890 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/*  4 */	NdrFcShort( 0x40 ),	/* 64 */
/*  6 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/*  8 */	
			0x11, 0x0,	/* FC_RP */
/* 10 */	NdrFcShort( 0x2 ),	/* Offset= 2 (12) */
/* 12 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 14 */	NdrFcShort( 0x48 ),	/* 72 */
/* 16 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 18 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 20 */	NdrFcShort( 0x44 ),	/* 68 */
/* 22 */	NdrFcShort( 0x44 ),	/* 68 */
/* 24 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 26 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 28 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 30 */	0x0,		/* 0 */
			NdrFcShort( 0xffe3 ),	/* Offset= -29 (2) */
			0x8,		/* FC_LONG */
/* 34 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 36 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 38 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 40 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 52 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 54 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 56 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 58 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 60 */	NdrFcShort( 0x48 ),	/* 72 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0xc ),	/* Offset= 12 (76) */
/* 66 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 68 */	0x0,		/* 0 */
			NdrFcShort( 0xffbd ),	/* Offset= -67 (2) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 72 */	0x0,		/* 0 */
			NdrFcShort( 0xffdf ),	/* Offset= -33 (40) */
			0x5b,		/* FC_END */
/* 76 */	
			0x11, 0x0,	/* FC_RP */
/* 78 */	NdrFcShort( 0xffec ),	/* Offset= -20 (58) */
/* 80 */	
			0x11, 0x0,	/* FC_RP */
/* 82 */	NdrFcShort( 0x2 ),	/* Offset= 2 (84) */
/* 84 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 86 */	NdrFcShort( 0x1c ),	/* 28 */
/* 88 */	NdrFcShort( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x0 ),	/* Offset= 0 (90) */
/* 92 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 94 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 96 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 98 */	0x8,		/* FC_LONG */
			0x1,		/* FC_BYTE */
/* 100 */	0x1,		/* FC_BYTE */
			0x3e,		/* FC_STRUCTPAD2 */
/* 102 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 104 */	
			0x11, 0x0,	/* FC_RP */
/* 106 */	NdrFcShort( 0x2 ),	/* Offset= 2 (108) */
/* 108 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 110 */	NdrFcShort( 0x14 ),	/* 20 */
/* 112 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 114 */	0x8,		/* FC_LONG */
			0x1,		/* FC_BYTE */
/* 116 */	0x1,		/* FC_BYTE */
			0x1,		/* FC_BYTE */
/* 118 */	0x1,		/* FC_BYTE */
			0x1,		/* FC_BYTE */
/* 120 */	0x3f,		/* FC_STRUCTPAD3 */
			0x8,		/* FC_LONG */
/* 122 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 124 */	
			0x11, 0x0,	/* FC_RP */
/* 126 */	NdrFcShort( 0x2 ),	/* Offset= 2 (128) */
/* 128 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 130 */	NdrFcShort( 0xc ),	/* 12 */
/* 132 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 134 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 136 */	NdrFcShort( 0x8 ),	/* 8 */
/* 138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 140 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 142 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 144 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 146 */	0x1,		/* FC_BYTE */
			0x1,		/* FC_BYTE */
/* 148 */	0x3e,		/* FC_STRUCTPAD2 */
			0x8,		/* FC_LONG */
/* 150 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 152 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 154 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 156 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 158 */	NdrFcShort( 0x2 ),	/* Offset= 2 (160) */
/* 160 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 162 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 164 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 166 */	0x3,		/* FC_SMALL */
			0x5c,		/* FC_PAD */
/* 168 */	
			0x11, 0x0,	/* FC_RP */
/* 170 */	NdrFcShort( 0xa ),	/* Offset= 10 (180) */
/* 172 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 174 */	NdrFcShort( 0x18 ),	/* 24 */
/* 176 */	0xc,		/* FC_DOUBLE */
			0xc,		/* FC_DOUBLE */
/* 178 */	0xc,		/* FC_DOUBLE */
			0x5b,		/* FC_END */
/* 180 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 182 */	NdrFcShort( 0x28 ),	/* 40 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x0 ),	/* Offset= 0 (186) */
/* 188 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 190 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 192 */	0x0,		/* 0 */
			NdrFcShort( 0xffeb ),	/* Offset= -21 (172) */
			0xa,		/* FC_FLOAT */
/* 196 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 198 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 200 */	NdrFcShort( 0xc ),	/* 12 */
/* 202 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 204 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 206 */	NdrFcShort( 0x8 ),	/* 8 */
/* 208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 210 */	0x12, 0x0,	/* FC_UP */
/* 212 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (180) */
/* 214 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 216 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 218 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 220 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 222 */	NdrFcShort( 0x18 ),	/* 24 */
/* 224 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 226 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 228 */	NdrFcShort( 0x4 ),	/* 4 */
/* 230 */	NdrFcShort( 0x4 ),	/* 4 */
/* 232 */	0x12, 0x0,	/* FC_UP */
/* 234 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (198) */
/* 236 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 238 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 240 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 242 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISySalObject, ver. 0.0,
   GUID={0xC022EEAD,0x748A,0x11D3,{0xA4,0x7B,0xE8,0x9C,0x0B,0xCE,0x97,0x20}} */

#pragma code_seg(".orpc")
static const unsigned short ISySalObject_FormatStringOffsetTable[] =
    {
    0,
    36,
    72,
    108,
    144,
    186,
    222,
    258,
    300,
    342,
    384,
    420,
    450,
    486,
    522,
    552,
    582,
    612,
    642
    };

static const MIDL_STUBLESS_PROXY_INFO ISySalObject_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISySalObject_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISySalObject_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISySalObject_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(22) _ISySalObjectProxyVtbl = 
{
    &ISySalObject_ProxyInfo,
    &IID_ISySalObject,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISySalObject::SetName */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::GetName */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::SetConfig */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::GetConfig */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::EditConfig */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::EnableMonitor */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::GetNumberOfConnections */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::SetConnection */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::GetConnection */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::GetIcon */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::GetClassName */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::SyncExec */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::AsyncExec */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::AsyncCheckStatus */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::AsyncWait */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::AsyncPause */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::AsyncStop */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::AsyncResume */ ,
    (void *) (INT_PTR) -1 /* ISySalObject::IsReady */
};

const CInterfaceStubVtbl _ISySalObjectStubVtbl =
{
    &IID_ISySalObject,
    &ISySalObject_ServerInfo,
    22,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IFrameGrabber, ver. 0.0,
   GUID={0xDFFC86AE,0x7C46,0x11D3,{0xA4,0x7C,0xC0,0xB8,0x89,0xFF,0x7C,0x20}} */

#pragma code_seg(".orpc")
static const unsigned short IFrameGrabber_FormatStringOffsetTable[] =
    {
    684,
    720,
    756,
    792,
    828,
    858,
    900,
    948,
    996,
    1068,
    1140,
    1200,
    1260,
    1320,
    1374,
    1410,
    1452,
    1488,
    1530,
    1572,
    1608,
    1638,
    1668,
    1698,
    1740,
    1782,
    1812,
    1842,
    1872,
    1902,
    1938,
    1968,
    1998,
    2034,
    2064,
    2094,
    2130,
    2160,
    2196,
    2232
    };

static const MIDL_STUBLESS_PROXY_INFO IFrameGrabber_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IFrameGrabber_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IFrameGrabber_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IFrameGrabber_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(43) _IFrameGrabberProxyVtbl = 
{
    &IFrameGrabber_ProxyInfo,
    &IID_IFrameGrabber,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::VideoInfo */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::GrabInfo */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::GetPalette */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetPalette */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetDefaultPalette */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::GetColorCode */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::Dot */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::Fill */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::Arc */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::ArcFill */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::Rect */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::RectFill */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::Line */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::Text */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::TextFont */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::TextScale */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::Clear */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetZoom */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetOffset */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::LoadCursor */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::DeleteCursor */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::HideCursor */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::ShowCursor */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetCursorPos */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::GetCursorPos */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetNoGrab */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetLiveGrab */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::ShowLive */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::ShowFrozen */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::FreezeFrame */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::ClearFrozen */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::SetSingleFrameGrab */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::HoldFrame */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::ShowHeldFrame */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::ReleaseFrame */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::GetCurrentFrameGrabDelay */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::FlushGrabBackBuffers */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::IsGrabCycleLockable */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::IsGrabCycleLocked */ ,
    (void *) (INT_PTR) -1 /* IFrameGrabber::LoadStockCursor */
};

const CInterfaceStubVtbl _IFrameGrabberStubVtbl =
{
    &IID_IFrameGrabber,
    &IFrameGrabber_ServerInfo,
    43,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVisionProcessor, ver. 0.0,
   GUID={0xC1C2E8BC,0xC241,0x423F,{0xB0,0xD7,0x24,0x2B,0x07,0x02,0x4F,0x7E}} */

#pragma code_seg(".orpc")
static const unsigned short IVisionProcessor_FormatStringOffsetTable[] =
    {
    2268,
    2358,
    2388,
    2418,
    2460,
    2502
    };

static const MIDL_STUBLESS_PROXY_INFO IVisionProcessor_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisionProcessor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IVisionProcessorProxyVtbl = 
{
    &IVisionProcessor_ProxyInfo,
    &IID_IVisionProcessor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPLock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPUnlock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPStart */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPIterate */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPFlush */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPGetFrameDelay */
};

const CInterfaceStubVtbl _IVisionProcessorStubVtbl =
{
    &IID_IVisionProcessor,
    &IVisionProcessor_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVisionProcessor2, ver. 0.0,
   GUID={0x673ec4de,0x0d86,0x4155,{0xbb,0x0b,0xc2,0xa8,0x04,0x69,0xfa,0x19}} */

#pragma code_seg(".orpc")
static const unsigned short IVisionProcessor2_FormatStringOffsetTable[] =
    {
    2268,
    2358,
    2388,
    2418,
    2460,
    2502,
    222,
    2538,
    2574,
    2610,
    2652
    };

static const MIDL_STUBLESS_PROXY_INFO IVisionProcessor2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisionProcessor2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IVisionProcessor2ProxyVtbl = 
{
    &IVisionProcessor2_ProxyInfo,
    &IID_IVisionProcessor2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPLock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPUnlock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPStart */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPIterate */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPFlush */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPGetFrameDelay */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetProgramCount */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetProgram */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPSetProgram */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPLock2 */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetPrimaryImage */
};

const CInterfaceStubVtbl _IVisionProcessor2StubVtbl =
{
    &IID_IVisionProcessor2,
    &IVisionProcessor2_ServerInfo,
    14,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IAutomaticLightControl, ver. 0.0,
   GUID={0xb6ac7f16,0x130a,0x4f55,{0x92,0x72,0x12,0x4a,0x2f,0xff,0x17,0x67}} */

#pragma code_seg(".orpc")
static const unsigned short IAutomaticLightControl_FormatStringOffsetTable[] =
    {
    2688
    };

static const MIDL_STUBLESS_PROXY_INFO IAutomaticLightControl_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAutomaticLightControl_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAutomaticLightControl_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAutomaticLightControl_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IAutomaticLightControlProxyVtbl = 
{
    &IAutomaticLightControl_ProxyInfo,
    &IID_IAutomaticLightControl,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IAutomaticLightControl::SetLightLevel */
};

const CInterfaceStubVtbl _IAutomaticLightControlStubVtbl =
{
    &IID_IAutomaticLightControl,
    &IAutomaticLightControl_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVisionProcessor3, ver. 0.0,
   GUID={0x3373d52b,0x6c8f,0x4518,{0xb0,0x41,0xfc,0x64,0x84,0x99,0x2c,0x14}} */

#pragma code_seg(".orpc")
static const unsigned short IVisionProcessor3_FormatStringOffsetTable[] =
    {
    2268,
    2358,
    2388,
    2418,
    2460,
    2502,
    222,
    2538,
    2574,
    2610,
    2652,
    2718,
    2760,
    2790,
    2820,
    552
    };

static const MIDL_STUBLESS_PROXY_INFO IVisionProcessor3_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisionProcessor3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(19) _IVisionProcessor3ProxyVtbl = 
{
    &IVisionProcessor3_ProxyInfo,
    &IID_IVisionProcessor3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPLock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPUnlock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPStart */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPIterate */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPFlush */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPGetFrameDelay */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetProgramCount */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetProgram */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPSetProgram */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPLock2 */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetPrimaryImage */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPPrepareAsyncProcessing */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPStartAsyncProcessing */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPWaitForProcessingComplete */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPGetCurrentImageSequenceDelay */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPWaitForClusters */
};

const CInterfaceStubVtbl _IVisionProcessor3StubVtbl =
{
    &IID_IVisionProcessor3,
    &IVisionProcessor3_ServerInfo,
    19,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVisionProcessor4, ver. 0.0,
   GUID={0x766b15ef,0x46f9,0x4541,{0x9e,0x2e,0x4f,0xf8,0xa0,0x9d,0xee,0x45}} */

#pragma code_seg(".orpc")
static const unsigned short IVisionProcessor4_FormatStringOffsetTable[] =
    {
    2268,
    2358,
    2388,
    2418,
    2460,
    2502,
    222,
    2538,
    2574,
    2610,
    2652,
    2718,
    2760,
    2790,
    2820,
    552,
    2856
    };

static const MIDL_STUBLESS_PROXY_INFO IVisionProcessor4_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor4_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisionProcessor4_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor4_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(20) _IVisionProcessor4ProxyVtbl = 
{
    &IVisionProcessor4_ProxyInfo,
    &IID_IVisionProcessor4,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPLock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPUnlock */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPStart */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPIterate */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPFlush */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor::VPGetFrameDelay */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetProgramCount */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetProgram */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPSetProgram */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPLock2 */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor2::VPGetPrimaryImage */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPPrepareAsyncProcessing */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPStartAsyncProcessing */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPWaitForProcessingComplete */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPGetCurrentImageSequenceDelay */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor3::VPWaitForClusters */ ,
    (void *) (INT_PTR) -1 /* IVisionProcessor4::VPWaitForProcessingCompleteAndExtractImages */
};

const CInterfaceStubVtbl _IVisionProcessor4StubVtbl =
{
    &IID_IVisionProcessor4,
    &IVisionProcessor4_ServerInfo,
    20,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x600016e, /* MIDL Version 6.0.366 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _Odyssey3_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAutomaticLightControlProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisionProcessor3ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISySalObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IFrameGrabberProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisionProcessorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisionProcessor2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisionProcessor4ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _Odyssey3_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAutomaticLightControlStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisionProcessor3StubVtbl,
    ( CInterfaceStubVtbl *) &_ISySalObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_IFrameGrabberStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisionProcessorStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisionProcessor2StubVtbl,
    ( CInterfaceStubVtbl *) &_IVisionProcessor4StubVtbl,
    0
};

PCInterfaceName const _Odyssey3_InterfaceNamesList[] = 
{
    "IAutomaticLightControl",
    "IVisionProcessor3",
    "ISySalObject",
    "IFrameGrabber",
    "IVisionProcessor",
    "IVisionProcessor2",
    "IVisionProcessor4",
    0
};


#define _Odyssey3_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Odyssey3, pIID, n)

int __stdcall _Odyssey3_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Odyssey3, 7, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _Odyssey3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _Odyssey3, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Odyssey3, 7, *pIndex )
    
}

const ExtendedProxyFileInfo Odyssey3_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Odyssey3_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Odyssey3_StubVtblList,
    (const PCInterfaceName * ) & _Odyssey3_InterfaceNamesList,
    0, // no delegation
    & _Odyssey3_IID_Lookup, 
    7,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

