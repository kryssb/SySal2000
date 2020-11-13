

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jul 11 08:43:48 2008
 */
/* Compiler settings for .\SmartTracker8.idl:
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


#include "SmartTracker8.h"

#define TYPE_FORMAT_STRING_SIZE   357                               
#define PROC_FORMAT_STRING_SIZE   1381                              
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


extern const MIDL_SERVER_INFO ISySalObject2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISySalObject2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITracker_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITracker_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITracker2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITracker2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITracker3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITracker3_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITracker4_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITracker4_ProxyInfo;



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

	/* Parameter pNumber */

/* 246 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 248 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

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

	/* Procedure SetConfigManagerInterface */

/* 684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x16 ),	/* 22 */
/* 692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 694 */	NdrFcShort( 0x40 ),	/* 64 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 700 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pCMI */

/* 708 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 710 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 712 */	NdrFcShort( 0x5a ),	/* Type Offset=90 */

	/* Return value */

/* 714 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 716 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCLSID */

/* 720 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 722 */	NdrFcLong( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x17 ),	/* 23 */
/* 728 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 730 */	NdrFcShort( 0x44 ),	/* 68 */
/* 732 */	NdrFcShort( 0x8 ),	/* 8 */
/* 734 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 736 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pCLSID */

/* 744 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 748 */	NdrFcShort( 0x6e ),	/* Type Offset=110 */

	/* Return value */

/* 750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartFilling */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x3 ),	/* 3 */
/* 764 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 772 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 780 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 782 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCameraSpec */

/* 786 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 788 */	NdrFcLong( 0x0 ),	/* 0 */
/* 792 */	NdrFcShort( 0x4 ),	/* 4 */
/* 794 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 796 */	NdrFcShort( 0x30 ),	/* 48 */
/* 798 */	NdrFcShort( 0x8 ),	/* 8 */
/* 800 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 802 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Spec */

/* 810 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 812 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 814 */	NdrFcShort( 0x7a ),	/* Type Offset=122 */

	/* Return value */

/* 816 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 818 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 820 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCameraSpec */

/* 822 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 824 */	NdrFcLong( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x5 ),	/* 5 */
/* 830 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 832 */	NdrFcShort( 0x44 ),	/* 68 */
/* 834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 836 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 838 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSpec */

/* 846 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 848 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 850 */	NdrFcShort( 0x7a ),	/* Type Offset=122 */

	/* Return value */

/* 852 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 854 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PutClusters */

/* 858 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0x6 ),	/* 6 */
/* 866 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 868 */	NdrFcShort( 0x10 ),	/* 16 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 874 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pClusters */

/* 882 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 884 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 886 */	NdrFcShort( 0x98 ),	/* Type Offset=152 */

	/* Parameter CountOfClusters */

/* 888 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 890 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 892 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Z */

/* 894 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 896 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 898 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 902 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetTracks */

/* 906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 912 */	NdrFcShort( 0x7 ),	/* 7 */
/* 914 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 916 */	NdrFcShort( 0x2c ),	/* 44 */
/* 918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 920 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 922 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSpace */

/* 930 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 932 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 934 */	NdrFcShort( 0xb6 ),	/* Type Offset=182 */

	/* Parameter pMaxNumber */

/* 936 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 938 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter StartLayer */

/* 942 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 944 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 946 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter EndLayer */

/* 948 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 950 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 952 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 954 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 956 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 958 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetClusters */

/* 960 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 962 */	NdrFcLong( 0x0 ),	/* 0 */
/* 966 */	NdrFcShort( 0x8 ),	/* 8 */
/* 968 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 970 */	NdrFcShort( 0x40 ),	/* 64 */
/* 972 */	NdrFcShort( 0x8 ),	/* 8 */
/* 974 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 976 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Layer */

/* 984 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 986 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 988 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pSpace */

/* 990 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 992 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 994 */	NdrFcShort( 0x98 ),	/* Type Offset=152 */

	/* Parameter pMaxNumber */

/* 996 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 998 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1000 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pZ */

/* 1002 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1004 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1006 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 1008 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1010 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PresetSlope */

/* 1014 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1016 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1022 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1024 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1026 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1028 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 1030 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter SX */

/* 1038 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1040 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1042 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter SY */

/* 1044 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1046 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1048 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter AccX */

/* 1050 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1052 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1054 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter AccY */

/* 1056 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1058 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1060 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 1062 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1064 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1066 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableSlopePresetting */

/* 1068 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1070 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1074 */	NdrFcShort( 0xa ),	/* 10 */
/* 1076 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1078 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1080 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1082 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1084 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1090 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter SlPresEnable */

/* 1092 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1094 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1096 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 1098 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1100 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1102 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSlopePresetStatus */

/* 1104 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1106 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1110 */	NdrFcShort( 0xb ),	/* 11 */
/* 1112 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1114 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1116 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1118 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1120 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1126 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSlPresEnable */

/* 1128 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1130 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1132 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 1134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1136 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFlatTracks */

/* 1140 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1142 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1146 */	NdrFcShort( 0xc ),	/* 12 */
/* 1148 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1150 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1154 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1156 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSpace */

/* 1164 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1166 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1168 */	NdrFcShort( 0x102 ),	/* Type Offset=258 */

	/* Parameter pMaxNumber */

/* 1170 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1172 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1174 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter MaxStripsInTrack */

/* 1176 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1178 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1180 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter StartLayer */

/* 1182 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1184 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1186 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter EndLayer */

/* 1188 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1190 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1192 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1194 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1196 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1198 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFlatStrips */

/* 1200 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1202 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1206 */	NdrFcShort( 0xd ),	/* 13 */
/* 1208 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1210 */	NdrFcShort( 0x90 ),	/* 144 */
/* 1212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1214 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 1216 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1222 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Layer */

/* 1224 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1226 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pSpace */

/* 1230 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 1232 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1234 */	NdrFcShort( 0xf4 ),	/* Type Offset=244 */

	/* Parameter pMaxNumber */

/* 1236 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1238 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pZ */

/* 1242 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1244 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1246 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 1248 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1250 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetTracks2 */

/* 1254 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1256 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1260 */	NdrFcShort( 0xe ),	/* 14 */
/* 1262 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1264 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1266 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1268 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1270 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1272 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1276 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSpace */

/* 1278 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1280 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1282 */	NdrFcShort( 0x140 ),	/* Type Offset=320 */

	/* Parameter pMaxNumber */

/* 1284 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1286 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter StartLayer */

/* 1290 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1292 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter EndLayer */

/* 1296 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1298 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1302 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1304 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1306 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetMaxGrainsPerTrack */

/* 1308 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1310 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1314 */	NdrFcShort( 0xf ),	/* 15 */
/* 1316 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1318 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1320 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1322 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1324 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1330 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pMaxGrains */

/* 1332 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1334 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1338 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1340 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartFilling2 */

/* 1344 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1346 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1350 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1352 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1356 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1358 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1360 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1366 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Side */

/* 1368 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1370 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1376 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1378 */	0x8,		/* FC_LONG */
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
/* 82 */	NdrFcShort( 0x8 ),	/* Offset= 8 (90) */
/* 84 */	
			0x1d,		/* FC_SMFARRAY */
			0x3,		/* 3 */
/* 86 */	NdrFcShort( 0x8 ),	/* 8 */
/* 88 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 90 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 92 */	NdrFcShort( 0xc ),	/* 12 */
/* 94 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 96 */	0x0,		/* 0 */
			NdrFcShort( 0xfff3 ),	/* Offset= -13 (84) */
			0x5b,		/* FC_END */
/* 100 */	
			0x11, 0x0,	/* FC_RP */
/* 102 */	NdrFcShort( 0x8 ),	/* Offset= 8 (110) */
/* 104 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 106 */	NdrFcShort( 0x8 ),	/* 8 */
/* 108 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 110 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 112 */	NdrFcShort( 0x10 ),	/* 16 */
/* 114 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 116 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 118 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (104) */
			0x5b,		/* FC_END */
/* 122 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 124 */	NdrFcShort( 0x20 ),	/* 32 */
/* 126 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 128 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 130 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 132 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 134 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 136 */	
			0x11, 0x0,	/* FC_RP */
/* 138 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (122) */
/* 140 */	
			0x11, 0x0,	/* FC_RP */
/* 142 */	NdrFcShort( 0xa ),	/* Offset= 10 (152) */
/* 144 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 146 */	NdrFcShort( 0x18 ),	/* 24 */
/* 148 */	0xc,		/* FC_DOUBLE */
			0xc,		/* FC_DOUBLE */
/* 150 */	0xc,		/* FC_DOUBLE */
			0x5b,		/* FC_END */
/* 152 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 154 */	NdrFcShort( 0x28 ),	/* 40 */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x0 ),	/* Offset= 0 (158) */
/* 160 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 162 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 164 */	0x0,		/* 0 */
			NdrFcShort( 0xffeb ),	/* Offset= -21 (144) */
			0xa,		/* FC_FLOAT */
/* 168 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 170 */	
			0x11, 0x0,	/* FC_RP */
/* 172 */	NdrFcShort( 0xa ),	/* Offset= 10 (182) */
/* 174 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 176 */	NdrFcShort( 0xc ),	/* 12 */
/* 178 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 180 */	0xa,		/* FC_FLOAT */
			0x5b,		/* FC_END */
/* 182 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 184 */	NdrFcShort( 0x50 ),	/* 80 */
/* 186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 188 */	NdrFcShort( 0x1c ),	/* Offset= 28 (216) */
/* 190 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 192 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 194 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 196 */	NdrFcShort( 0xffea ),	/* Offset= -22 (174) */
/* 198 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 200 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (174) */
/* 202 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 204 */	0xa,		/* FC_FLOAT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 206 */	0x0,		/* 0 */
			NdrFcShort( 0xffdf ),	/* Offset= -33 (174) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 210 */	0x0,		/* 0 */
			NdrFcShort( 0xffdb ),	/* Offset= -37 (174) */
			0x3,		/* FC_SMALL */
/* 214 */	0x3f,		/* FC_STRUCTPAD3 */
			0x5b,		/* FC_END */
/* 216 */	
			0x12, 0x0,	/* FC_UP */
/* 218 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (174) */
/* 220 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 222 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 224 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 226 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 228 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 230 */	0x3,		/* FC_SMALL */
			0x5c,		/* FC_PAD */
/* 232 */	
			0x11, 0x0,	/* FC_RP */
/* 234 */	NdrFcShort( 0x18 ),	/* Offset= 24 (258) */
/* 236 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 240 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 242 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 244 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 246 */	NdrFcShort( 0x1c ),	/* 28 */
/* 248 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 250 */	0xa,		/* FC_FLOAT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 252 */	0x0,		/* 0 */
			NdrFcShort( 0xffef ),	/* Offset= -17 (236) */
			0xa,		/* FC_FLOAT */
/* 256 */	0xa,		/* FC_FLOAT */
			0x5b,		/* FC_END */
/* 258 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 260 */	NdrFcShort( 0x54 ),	/* 84 */
/* 262 */	NdrFcShort( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0x1e ),	/* Offset= 30 (294) */
/* 266 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 268 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 270 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 272 */	NdrFcShort( 0xff9e ),	/* Offset= -98 (174) */
/* 274 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 276 */	NdrFcShort( 0xff9a ),	/* Offset= -102 (174) */
/* 278 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 280 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 282 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 284 */	NdrFcShort( 0xff92 ),	/* Offset= -110 (174) */
/* 286 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 288 */	NdrFcShort( 0xff8e ),	/* Offset= -114 (174) */
/* 290 */	0x3,		/* FC_SMALL */
			0x3f,		/* FC_STRUCTPAD3 */
/* 292 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 294 */	
			0x12, 0x0,	/* FC_UP */
/* 296 */	NdrFcShort( 0xffcc ),	/* Offset= -52 (244) */
/* 298 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 300 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 302 */	
			0x11, 0x0,	/* FC_RP */
/* 304 */	NdrFcShort( 0xffc4 ),	/* Offset= -60 (244) */
/* 306 */	
			0x11, 0x0,	/* FC_RP */
/* 308 */	NdrFcShort( 0xc ),	/* Offset= 12 (320) */
/* 310 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 312 */	NdrFcShort( 0x10 ),	/* 16 */
/* 314 */	0x6,		/* FC_SHORT */
			0x3e,		/* FC_STRUCTPAD2 */
/* 316 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 318 */	0xa,		/* FC_FLOAT */
			0x5b,		/* FC_END */
/* 320 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 322 */	NdrFcShort( 0x3c ),	/* 60 */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x16 ),	/* Offset= 22 (348) */
/* 328 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 330 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 332 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 334 */	0x0,		/* 0 */
			NdrFcShort( 0xff5f ),	/* Offset= -161 (174) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 338 */	0x0,		/* 0 */
			NdrFcShort( 0xff5b ),	/* Offset= -165 (174) */
			0xa,		/* FC_FLOAT */
/* 342 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 344 */	0x3,		/* FC_SMALL */
			0x3f,		/* FC_STRUCTPAD3 */
/* 346 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 348 */	
			0x12, 0x0,	/* FC_UP */
/* 350 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (310) */
/* 352 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 354 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */

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


/* Object interface: ISySalObject2, ver. 0.0,
   GUID={0x68659AF8,0x12E6,0x4EF9,{0x98,0x77,0xA7,0xDD,0x63,0xBF,0x19,0x50}} */

#pragma code_seg(".orpc")
static const unsigned short ISySalObject2_FormatStringOffsetTable[] =
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
    642,
    684,
    720
    };

static const MIDL_STUBLESS_PROXY_INFO ISySalObject2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISySalObject2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISySalObject2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISySalObject2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(24) _ISySalObject2ProxyVtbl = 
{
    &ISySalObject2_ProxyInfo,
    &IID_ISySalObject2,
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
    (void *) (INT_PTR) -1 /* ISySalObject::IsReady */ ,
    (void *) (INT_PTR) -1 /* ISySalObject2::SetConfigManagerInterface */ ,
    (void *) (INT_PTR) -1 /* ISySalObject2::GetCLSID */
};

const CInterfaceStubVtbl _ISySalObject2StubVtbl =
{
    &IID_ISySalObject2,
    &ISySalObject2_ServerInfo,
    24,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITracker, ver. 0.0,
   GUID={0xE416C46D,0x7F68,0x11D3,{0xA4,0x7C,0xFA,0x1E,0x4A,0xFA,0x27,0x21}} */

#pragma code_seg(".orpc")
static const unsigned short ITracker_FormatStringOffsetTable[] =
    {
    756,
    786,
    822,
    858,
    906,
    960,
    1014,
    1068,
    1104
    };

static const MIDL_STUBLESS_PROXY_INFO ITracker_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITracker_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITracker_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITracker_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _ITrackerProxyVtbl = 
{
    &ITracker_ProxyInfo,
    &IID_ITracker,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITracker::StartFilling */ ,
    (void *) (INT_PTR) -1 /* ITracker::SetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::PutClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetTracks */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::PresetSlope */ ,
    (void *) (INT_PTR) -1 /* ITracker::EnableSlopePresetting */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetSlopePresetStatus */
};

const CInterfaceStubVtbl _ITrackerStubVtbl =
{
    &IID_ITracker,
    &ITracker_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITracker2, ver. 0.0,
   GUID={0x67a71430,0xf2e4,0x42ae,{0x89,0x10,0x28,0x27,0x9a,0x76,0x16,0xd6}} */

#pragma code_seg(".orpc")
static const unsigned short ITracker2_FormatStringOffsetTable[] =
    {
    756,
    786,
    822,
    858,
    906,
    960,
    1014,
    1068,
    1104,
    1140,
    1200
    };

static const MIDL_STUBLESS_PROXY_INFO ITracker2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITracker2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITracker2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITracker2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _ITracker2ProxyVtbl = 
{
    &ITracker2_ProxyInfo,
    &IID_ITracker2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITracker::StartFilling */ ,
    (void *) (INT_PTR) -1 /* ITracker::SetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::PutClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetTracks */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::PresetSlope */ ,
    (void *) (INT_PTR) -1 /* ITracker::EnableSlopePresetting */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetSlopePresetStatus */ ,
    (void *) (INT_PTR) -1 /* ITracker2::GetFlatTracks */ ,
    (void *) (INT_PTR) -1 /* ITracker2::GetFlatStrips */
};

const CInterfaceStubVtbl _ITracker2StubVtbl =
{
    &IID_ITracker2,
    &ITracker2_ServerInfo,
    14,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITracker3, ver. 0.0,
   GUID={0x7a9e779c,0xaa32,0x4565,{0x8e,0x69,0x5f,0x1b,0xc4,0xe3,0x62,0xb7}} */

#pragma code_seg(".orpc")
static const unsigned short ITracker3_FormatStringOffsetTable[] =
    {
    756,
    786,
    822,
    858,
    906,
    960,
    1014,
    1068,
    1104,
    1140,
    1200,
    1254
    };

static const MIDL_STUBLESS_PROXY_INFO ITracker3_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITracker3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITracker3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITracker3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _ITracker3ProxyVtbl = 
{
    &ITracker3_ProxyInfo,
    &IID_ITracker3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITracker::StartFilling */ ,
    (void *) (INT_PTR) -1 /* ITracker::SetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::PutClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetTracks */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::PresetSlope */ ,
    (void *) (INT_PTR) -1 /* ITracker::EnableSlopePresetting */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetSlopePresetStatus */ ,
    (void *) (INT_PTR) -1 /* ITracker2::GetFlatTracks */ ,
    (void *) (INT_PTR) -1 /* ITracker2::GetFlatStrips */ ,
    (void *) (INT_PTR) -1 /* ITracker3::GetTracks2 */
};

const CInterfaceStubVtbl _ITracker3StubVtbl =
{
    &IID_ITracker3,
    &ITracker3_ServerInfo,
    15,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITracker4, ver. 0.0,
   GUID={0x04e5187b,0x933e,0x4d9e,{0x9a,0x7f,0xeb,0x20,0x84,0x0d,0xa9,0xd0}} */

#pragma code_seg(".orpc")
static const unsigned short ITracker4_FormatStringOffsetTable[] =
    {
    756,
    786,
    822,
    858,
    906,
    960,
    1014,
    1068,
    1104,
    1140,
    1200,
    1254,
    1308,
    1344
    };

static const MIDL_STUBLESS_PROXY_INFO ITracker4_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITracker4_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITracker4_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITracker4_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _ITracker4ProxyVtbl = 
{
    &ITracker4_ProxyInfo,
    &IID_ITracker4,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITracker::StartFilling */ ,
    (void *) (INT_PTR) -1 /* ITracker::SetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetCameraSpec */ ,
    (void *) (INT_PTR) -1 /* ITracker::PutClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetTracks */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetClusters */ ,
    (void *) (INT_PTR) -1 /* ITracker::PresetSlope */ ,
    (void *) (INT_PTR) -1 /* ITracker::EnableSlopePresetting */ ,
    (void *) (INT_PTR) -1 /* ITracker::GetSlopePresetStatus */ ,
    (void *) (INT_PTR) -1 /* ITracker2::GetFlatTracks */ ,
    (void *) (INT_PTR) -1 /* ITracker2::GetFlatStrips */ ,
    (void *) (INT_PTR) -1 /* ITracker3::GetTracks2 */ ,
    (void *) (INT_PTR) -1 /* ITracker4::GetMaxGrainsPerTrack */ ,
    (void *) (INT_PTR) -1 /* ITracker4::StartFilling2 */
};

const CInterfaceStubVtbl _ITracker4StubVtbl =
{
    &IID_ITracker4,
    &ITracker4_ServerInfo,
    17,
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

const CInterfaceProxyVtbl * _SmartTracker8_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ITracker2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITrackerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITracker4ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITracker3ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISySalObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISySalObject2ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _SmartTracker8_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ITracker2StubVtbl,
    ( CInterfaceStubVtbl *) &_ITrackerStubVtbl,
    ( CInterfaceStubVtbl *) &_ITracker4StubVtbl,
    ( CInterfaceStubVtbl *) &_ITracker3StubVtbl,
    ( CInterfaceStubVtbl *) &_ISySalObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_ISySalObject2StubVtbl,
    0
};

PCInterfaceName const _SmartTracker8_InterfaceNamesList[] = 
{
    "ITracker2",
    "ITracker",
    "ITracker4",
    "ITracker3",
    "ISySalObject",
    "ISySalObject2",
    0
};


#define _SmartTracker8_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _SmartTracker8, pIID, n)

int __stdcall _SmartTracker8_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _SmartTracker8, 6, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _SmartTracker8, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _SmartTracker8, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _SmartTracker8, 6, *pIndex )
    
}

const ExtendedProxyFileInfo SmartTracker8_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _SmartTracker8_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _SmartTracker8_StubVtblList,
    (const PCInterfaceName * ) & _SmartTracker8_InterfaceNamesList,
    0, // no delegation
    & _SmartTracker8_IID_Lookup, 
    6,
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

