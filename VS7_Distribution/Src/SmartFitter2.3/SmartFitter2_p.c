

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Thu May 14 17:52:51 2009
 */
/* Compiler settings for .\SmartFitter2.idl:
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


#include "SmartFitter2.h"

#define TYPE_FORMAT_STRING_SIZE   301                               
#define PROC_FORMAT_STRING_SIZE   1201                              
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


extern const MIDL_SERVER_INFO ITrackFitter_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITrackFitter_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITrackFitter2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITrackFitter2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITrackFitter3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITrackFitter3_ProxyInfo;



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

	/* Procedure Fit */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x3 ),	/* 3 */
/* 764 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 766 */	NdrFcShort( 0x2c ),	/* 44 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 772 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTracks */

/* 780 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 782 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 784 */	NdrFcShort( 0x86 ),	/* Type Offset=134 */

	/* Parameter pMaxNumber */

/* 786 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 788 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ZBase */

/* 792 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 794 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 796 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter Thickness */

/* 798 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 800 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 802 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 804 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 806 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 808 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Correct */

/* 810 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 812 */	NdrFcLong( 0x0 ),	/* 0 */
/* 816 */	NdrFcShort( 0x4 ),	/* 4 */
/* 818 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	NdrFcShort( 0x8 ),	/* 8 */
/* 824 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 826 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTrack */

/* 834 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 836 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 838 */	NdrFcShort( 0x86 ),	/* Type Offset=134 */

	/* Return value */

/* 840 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 842 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 844 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PresetSlope */

/* 846 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 848 */	NdrFcLong( 0x0 ),	/* 0 */
/* 852 */	NdrFcShort( 0x5 ),	/* 5 */
/* 854 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 856 */	NdrFcShort( 0x20 ),	/* 32 */
/* 858 */	NdrFcShort( 0x8 ),	/* 8 */
/* 860 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 862 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter SlopeX */

/* 870 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 872 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 874 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter SlopeY */

/* 876 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 878 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 880 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter TolX */

/* 882 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 884 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 886 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter TolY */

/* 888 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 890 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 892 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 894 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 896 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 898 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableSlopePresetting */

/* 900 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 902 */	NdrFcLong( 0x0 ),	/* 0 */
/* 906 */	NdrFcShort( 0x6 ),	/* 6 */
/* 908 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 910 */	NdrFcShort( 0x5 ),	/* 5 */
/* 912 */	NdrFcShort( 0x8 ),	/* 8 */
/* 914 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 916 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x0 ),	/* 0 */
/* 922 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter SlPresEnable */

/* 924 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 926 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 928 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 930 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 932 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSlopePresetStatus */

/* 936 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 938 */	NdrFcLong( 0x0 ),	/* 0 */
/* 942 */	NdrFcShort( 0x7 ),	/* 7 */
/* 944 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 946 */	NdrFcShort( 0x19 ),	/* 25 */
/* 948 */	NdrFcShort( 0x8 ),	/* 8 */
/* 950 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 952 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 954 */	NdrFcShort( 0x0 ),	/* 0 */
/* 956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 958 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSlPresEnable */

/* 960 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 962 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 964 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 966 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 968 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCorrectionDataSize */

/* 972 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 974 */	NdrFcLong( 0x0 ),	/* 0 */
/* 978 */	NdrFcShort( 0x8 ),	/* 8 */
/* 980 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 982 */	NdrFcShort( 0x1c ),	/* 28 */
/* 984 */	NdrFcShort( 0x8 ),	/* 8 */
/* 986 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 988 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSize */

/* 996 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 998 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1000 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1002 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1004 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1006 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Fit2 */

/* 1008 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1010 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1014 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1016 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 1018 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1020 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1022 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 1024 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1026 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1030 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTracks */

/* 1032 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1034 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1036 */	NdrFcShort( 0x86 ),	/* Type Offset=134 */

	/* Parameter pMaxTracks */

/* 1038 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1040 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1042 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pFlatTracks */

/* 1044 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1046 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1048 */	NdrFcShort( 0xce ),	/* Type Offset=206 */

	/* Parameter pMaxFlatTracks */

/* 1050 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1052 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1054 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ZBase */

/* 1056 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1058 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1060 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter Thickness */

/* 1062 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1064 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1066 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 1068 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1070 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1072 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Correct2 */

/* 1074 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1076 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1080 */	NdrFcShort( 0xa ),	/* 10 */
/* 1082 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1086 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1088 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1090 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1096 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFlatTrack */

/* 1098 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1100 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1102 */	NdrFcShort( 0xce ),	/* Type Offset=206 */

	/* Return value */

/* 1104 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1106 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1108 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Fit3 */

/* 1110 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1112 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1116 */	NdrFcShort( 0xb ),	/* 11 */
/* 1118 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1120 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1122 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1124 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1126 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1132 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTracks */

/* 1134 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1136 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1138 */	NdrFcShort( 0x108 ),	/* Type Offset=264 */

	/* Parameter pMaxNumber */

/* 1140 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 1142 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ZBase */

/* 1146 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1148 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1150 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter Thickness */

/* 1152 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1154 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1156 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 1158 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1160 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Correct3 */

/* 1164 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1166 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1170 */	NdrFcShort( 0xc ),	/* 12 */
/* 1172 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1178 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1180 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1186 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTrack */

/* 1188 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1190 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1192 */	NdrFcShort( 0x108 ),	/* Type Offset=264 */

	/* Return value */

/* 1194 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1196 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1198 */	0x8,		/* FC_LONG */
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
			0x11, 0x0,	/* FC_RP */
/* 124 */	NdrFcShort( 0xa ),	/* Offset= 10 (134) */
/* 126 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 128 */	NdrFcShort( 0xc ),	/* 12 */
/* 130 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 132 */	0xa,		/* FC_FLOAT */
			0x5b,		/* FC_END */
/* 134 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 136 */	NdrFcShort( 0x50 ),	/* 80 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0x1c ),	/* Offset= 28 (168) */
/* 142 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 144 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 146 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 148 */	NdrFcShort( 0xffea ),	/* Offset= -22 (126) */
/* 150 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 152 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (126) */
/* 154 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 156 */	0xa,		/* FC_FLOAT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 158 */	0x0,		/* 0 */
			NdrFcShort( 0xffdf ),	/* Offset= -33 (126) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 162 */	0x0,		/* 0 */
			NdrFcShort( 0xffdb ),	/* Offset= -37 (126) */
			0x3,		/* FC_SMALL */
/* 166 */	0x3f,		/* FC_STRUCTPAD3 */
			0x5b,		/* FC_END */
/* 168 */	
			0x12, 0x0,	/* FC_UP */
/* 170 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (126) */
/* 172 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 174 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 176 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 178 */	0x3,		/* FC_SMALL */
			0x5c,		/* FC_PAD */
/* 180 */	
			0x11, 0x0,	/* FC_RP */
/* 182 */	NdrFcShort( 0x18 ),	/* Offset= 24 (206) */
/* 184 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 188 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 190 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 192 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 194 */	NdrFcShort( 0x1c ),	/* 28 */
/* 196 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 198 */	0xa,		/* FC_FLOAT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 200 */	0x0,		/* 0 */
			NdrFcShort( 0xffef ),	/* Offset= -17 (184) */
			0xa,		/* FC_FLOAT */
/* 204 */	0xa,		/* FC_FLOAT */
			0x5b,		/* FC_END */
/* 206 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 208 */	NdrFcShort( 0x54 ),	/* 84 */
/* 210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 212 */	NdrFcShort( 0x1e ),	/* Offset= 30 (242) */
/* 214 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 216 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 218 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 220 */	NdrFcShort( 0xffa2 ),	/* Offset= -94 (126) */
/* 222 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 224 */	NdrFcShort( 0xff9e ),	/* Offset= -98 (126) */
/* 226 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 228 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 230 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 232 */	NdrFcShort( 0xff96 ),	/* Offset= -106 (126) */
/* 234 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 236 */	NdrFcShort( 0xff92 ),	/* Offset= -110 (126) */
/* 238 */	0x3,		/* FC_SMALL */
			0x3f,		/* FC_STRUCTPAD3 */
/* 240 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 242 */	
			0x12, 0x0,	/* FC_UP */
/* 244 */	NdrFcShort( 0xffcc ),	/* Offset= -52 (192) */
/* 246 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 248 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 250 */	
			0x11, 0x0,	/* FC_RP */
/* 252 */	NdrFcShort( 0xc ),	/* Offset= 12 (264) */
/* 254 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 256 */	NdrFcShort( 0x10 ),	/* 16 */
/* 258 */	0x6,		/* FC_SHORT */
			0x3e,		/* FC_STRUCTPAD2 */
/* 260 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 262 */	0xa,		/* FC_FLOAT */
			0x5b,		/* FC_END */
/* 264 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 266 */	NdrFcShort( 0x3c ),	/* 60 */
/* 268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x16 ),	/* Offset= 22 (292) */
/* 272 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 274 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 276 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 278 */	0x0,		/* 0 */
			NdrFcShort( 0xff67 ),	/* Offset= -153 (126) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 282 */	0x0,		/* 0 */
			NdrFcShort( 0xff63 ),	/* Offset= -157 (126) */
			0xa,		/* FC_FLOAT */
/* 286 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 288 */	0x3,		/* FC_SMALL */
			0x3f,		/* FC_STRUCTPAD3 */
/* 290 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 292 */	
			0x12, 0x0,	/* FC_UP */
/* 294 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (254) */
/* 296 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 298 */	0x1,		/* FC_BYTE */
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


/* Object interface: ITrackFitter, ver. 0.0,
   GUID={0x9061992E,0x87FC,0x11D3,{0xA4,0x7C,0xCB,0xD9,0x48,0x9C,0x09,0x20}} */

#pragma code_seg(".orpc")
static const unsigned short ITrackFitter_FormatStringOffsetTable[] =
    {
    756,
    810,
    846,
    900,
    936,
    972
    };

static const MIDL_STUBLESS_PROXY_INFO ITrackFitter_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITrackFitter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITrackFitter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITrackFitter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _ITrackFitterProxyVtbl = 
{
    &ITrackFitter_ProxyInfo,
    &IID_ITrackFitter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITrackFitter::Fit */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::Correct */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::PresetSlope */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::EnableSlopePresetting */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::GetSlopePresetStatus */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::GetCorrectionDataSize */
};

const CInterfaceStubVtbl _ITrackFitterStubVtbl =
{
    &IID_ITrackFitter,
    &ITrackFitter_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITrackFitter2, ver. 0.0,
   GUID={0x950c2406,0xd41e,0x47d1,{0x9f,0x84,0xa1,0xbf,0xc0,0x40,0x29,0xc5}} */

#pragma code_seg(".orpc")
static const unsigned short ITrackFitter2_FormatStringOffsetTable[] =
    {
    756,
    810,
    846,
    900,
    936,
    972,
    1008,
    1074
    };

static const MIDL_STUBLESS_PROXY_INFO ITrackFitter2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITrackFitter2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITrackFitter2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITrackFitter2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _ITrackFitter2ProxyVtbl = 
{
    &ITrackFitter2_ProxyInfo,
    &IID_ITrackFitter2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITrackFitter::Fit */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::Correct */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::PresetSlope */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::EnableSlopePresetting */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::GetSlopePresetStatus */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::GetCorrectionDataSize */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter2::Fit2 */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter2::Correct2 */
};

const CInterfaceStubVtbl _ITrackFitter2StubVtbl =
{
    &IID_ITrackFitter2,
    &ITrackFitter2_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITrackFitter3, ver. 0.0,
   GUID={0x855fe3ff,0xb30f,0x4ad2,{0x98,0x10,0x47,0x1e,0xdf,0xc9,0xf4,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short ITrackFitter3_FormatStringOffsetTable[] =
    {
    756,
    810,
    846,
    900,
    936,
    972,
    1008,
    1074,
    1110,
    1164
    };

static const MIDL_STUBLESS_PROXY_INFO ITrackFitter3_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITrackFitter3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITrackFitter3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITrackFitter3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _ITrackFitter3ProxyVtbl = 
{
    &ITrackFitter3_ProxyInfo,
    &IID_ITrackFitter3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITrackFitter::Fit */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::Correct */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::PresetSlope */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::EnableSlopePresetting */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::GetSlopePresetStatus */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter::GetCorrectionDataSize */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter2::Fit2 */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter2::Correct2 */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter3::Fit3 */ ,
    (void *) (INT_PTR) -1 /* ITrackFitter3::Correct3 */
};

const CInterfaceStubVtbl _ITrackFitter3StubVtbl =
{
    &IID_ITrackFitter3,
    &ITrackFitter3_ServerInfo,
    13,
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

const CInterfaceProxyVtbl * _SmartFitter2_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ITrackFitter2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITrackFitterProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISySalObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISySalObject2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITrackFitter3ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _SmartFitter2_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ITrackFitter2StubVtbl,
    ( CInterfaceStubVtbl *) &_ITrackFitterStubVtbl,
    ( CInterfaceStubVtbl *) &_ISySalObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_ISySalObject2StubVtbl,
    ( CInterfaceStubVtbl *) &_ITrackFitter3StubVtbl,
    0
};

PCInterfaceName const _SmartFitter2_InterfaceNamesList[] = 
{
    "ITrackFitter2",
    "ITrackFitter",
    "ISySalObject",
    "ISySalObject2",
    "ITrackFitter3",
    0
};


#define _SmartFitter2_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _SmartFitter2, pIID, n)

int __stdcall _SmartFitter2_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _SmartFitter2, 5, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _SmartFitter2, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _SmartFitter2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _SmartFitter2, 5, *pIndex )
    
}

const ExtendedProxyFileInfo SmartFitter2_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _SmartFitter2_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _SmartFitter2_StubVtblList,
    (const PCInterfaceName * ) & _SmartFitter2_InterfaceNamesList,
    0, // no delegation
    & _SmartFitter2_IID_Lookup, 
    5,
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

