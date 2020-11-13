
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Feb 01 17:31:47 2005
 */
/* Compiler settings for VSScanServerNET.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "VSScanServerNET.h"

#define TYPE_FORMAT_STRING_SIZE   85                                
#define PROC_FORMAT_STRING_SIZE   633                               
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


extern const MIDL_SERVER_INFO IScanServer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IScanServer_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf.
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
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 16 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetName */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 38 */	NdrFcShort( 0x50 ),	/* 80 */
/* 40 */	NdrFcShort( 0x8 ),	/* 8 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 44 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetConfig */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x5 ),	/* 5 */
/* 64 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 66 */	NdrFcShort( 0x91 ),	/* 145 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pConfig */

/* 72 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 74 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 76 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetConfig */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x6 ),	/* 6 */
/* 92 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 94 */	NdrFcShort( 0x91 ),	/* 145 */
/* 96 */	NdrFcShort( 0x8 ),	/* 8 */
/* 98 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pConfig */

/* 100 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 102 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 104 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Return value */

/* 106 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 108 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EditConfig */

/* 112 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0x7 ),	/* 7 */
/* 120 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 122 */	NdrFcShort( 0x99 ),	/* 153 */
/* 124 */	NdrFcShort( 0x8 ),	/* 8 */
/* 126 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter pConfig */

/* 128 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 130 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 132 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Parameter hWnd */

/* 134 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 136 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 142 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableMonitor */

/* 146 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 148 */	NdrFcLong( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 154 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 156 */	NdrFcShort( 0x5 ),	/* 5 */
/* 158 */	NdrFcShort( 0x8 ),	/* 8 */
/* 160 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bEnable */

/* 162 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 164 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 166 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 168 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 170 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetNumberOfConnections */

/* 174 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x9 ),	/* 9 */
/* 182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 184 */	NdrFcShort( 0x1c ),	/* 28 */
/* 186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 188 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pNumber */

/* 190 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 192 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 196 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 198 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetConnection */

/* 202 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 204 */	NdrFcLong( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0xa ),	/* 10 */
/* 210 */	NdrFcShort( 0x54 ),	/* x86 Stack size/offset = 84 */
/* 212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 214 */	NdrFcShort( 0x8 ),	/* 8 */
/* 216 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter n */

/* 218 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 220 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter connection */

/* 224 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 226 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 228 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 230 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 232 */	NdrFcShort( 0x50 ),	/* x86 Stack size/offset = 80 */
/* 234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetConnection */

/* 236 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 238 */	NdrFcLong( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0xb ),	/* 11 */
/* 244 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 248 */	NdrFcShort( 0x8 ),	/* 8 */
/* 250 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter n */

/* 252 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 254 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pConnection */

/* 258 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 260 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 262 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 264 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 266 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetIcon */

/* 270 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 272 */	NdrFcLong( 0x0 ),	/* 0 */
/* 276 */	NdrFcShort( 0xc ),	/* 12 */
/* 278 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 280 */	NdrFcShort( 0x24 ),	/* 36 */
/* 282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 284 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter n */

/* 286 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 288 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 290 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pHICON */

/* 292 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 294 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 298 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 300 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 302 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetClassName */

/* 304 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 306 */	NdrFcLong( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0xd ),	/* 13 */
/* 312 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 314 */	NdrFcShort( 0x50 ),	/* 80 */
/* 316 */	NdrFcShort( 0x8 ),	/* 8 */
/* 318 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 320 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 322 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 324 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 326 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 328 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SyncExec */

/* 332 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0xe ),	/* 14 */
/* 340 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 346 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 348 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 350 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncExec */

/* 354 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 356 */	NdrFcLong( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0xf ),	/* 15 */
/* 362 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 366 */	NdrFcShort( 0x8 ),	/* 8 */
/* 368 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter HNotifyStatusChangeEvent */

/* 370 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 372 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 378 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncCheckStatus */

/* 382 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 388 */	NdrFcShort( 0x10 ),	/* 16 */
/* 390 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 392 */	NdrFcShort( 0x1c ),	/* 28 */
/* 394 */	NdrFcShort( 0x8 ),	/* 8 */
/* 396 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pStatus */

/* 398 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 400 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 406 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncWait */

/* 410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 416 */	NdrFcShort( 0x11 ),	/* 17 */
/* 418 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 424 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 426 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncPause */

/* 432 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 434 */	NdrFcLong( 0x0 ),	/* 0 */
/* 438 */	NdrFcShort( 0x12 ),	/* 18 */
/* 440 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0x8 ),	/* 8 */
/* 446 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 448 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 450 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncStop */

/* 454 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 456 */	NdrFcLong( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x13 ),	/* 19 */
/* 462 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	NdrFcShort( 0x8 ),	/* 8 */
/* 468 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 470 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 472 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncResume */

/* 476 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 482 */	NdrFcShort( 0x14 ),	/* 20 */
/* 484 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 490 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 492 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 494 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsReady */

/* 498 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x15 ),	/* 21 */
/* 506 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 508 */	NdrFcShort( 0x38 ),	/* 56 */
/* 510 */	NdrFcShort( 0x8 ),	/* 8 */
/* 512 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter pWrongConn */

/* 514 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 516 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 518 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetCode */

/* 520 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 522 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 528 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Connect */

/* 532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x3 ),	/* 3 */
/* 540 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 546 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 548 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 552 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Disconnect */

/* 554 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 556 */	NdrFcLong( 0x0 ),	/* 0 */
/* 560 */	NdrFcShort( 0x4 ),	/* 4 */
/* 562 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x8 ),	/* 8 */
/* 568 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 570 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 572 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Send */

/* 576 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 578 */	NdrFcLong( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x5 ),	/* 5 */
/* 584 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 586 */	NdrFcShort( 0x19 ),	/* 25 */
/* 588 */	NdrFcShort( 0x8 ),	/* 8 */
/* 590 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pMessage */

/* 592 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 594 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 596 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Return value */

/* 598 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 600 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Receive */

/* 604 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 606 */	NdrFcLong( 0x0 ),	/* 0 */
/* 610 */	NdrFcShort( 0x6 ),	/* 6 */
/* 612 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 614 */	NdrFcShort( 0x19 ),	/* 25 */
/* 616 */	NdrFcShort( 0x8 ),	/* 8 */
/* 618 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pMessageSpace */

/* 620 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 624 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Return value */

/* 626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 628 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 630 */	0x8,		/* FC_LONG */
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
			NdrFcShort( 0xffffffe3 ),	/* Offset= -29 (2) */
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
			NdrFcShort( 0xffffffbd ),	/* Offset= -67 (2) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 72 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffdf ),	/* Offset= -33 (40) */
			0x5b,		/* FC_END */
/* 76 */	
			0x11, 0x0,	/* FC_RP */
/* 78 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (58) */
/* 80 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 82 */	0x1,		/* FC_BYTE */
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
    28,
    56,
    84,
    112,
    146,
    174,
    202,
    236,
    270,
    304,
    332,
    354,
    382,
    410,
    432,
    454,
    476,
    498
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


/* Object interface: IScanServer, ver. 0.0,
   GUID={0x32E3C1FF,0x0C60,0x45B7,{0xB6,0x6F,0x36,0xDB,0x81,0x62,0x76,0xDD}} */

#pragma code_seg(".orpc")
static const unsigned short IScanServer_FormatStringOffsetTable[] =
    {
    532,
    554,
    576,
    604
    };

static const MIDL_STUBLESS_PROXY_INFO IScanServer_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IScanServer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IScanServer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IScanServer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IScanServerProxyVtbl = 
{
    &IScanServer_ProxyInfo,
    &IID_IScanServer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IScanServer::Connect */ ,
    (void *) (INT_PTR) -1 /* IScanServer::Disconnect */ ,
    (void *) (INT_PTR) -1 /* IScanServer::Send */ ,
    (void *) (INT_PTR) -1 /* IScanServer::Receive */
};

const CInterfaceStubVtbl _IScanServerStubVtbl =
{
    &IID_IScanServer,
    &IScanServer_ServerInfo,
    7,
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
    0x20000, /* Ndr library version */
    0,
    0x600015b, /* MIDL Version 6.0.347 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _VSScanServerNET_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISySalObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IScanServerProxyVtbl,
    0
};

const CInterfaceStubVtbl * _VSScanServerNET_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ISySalObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_IScanServerStubVtbl,
    0
};

PCInterfaceName const _VSScanServerNET_InterfaceNamesList[] = 
{
    "ISySalObject",
    "IScanServer",
    0
};


#define _VSScanServerNET_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _VSScanServerNET, pIID, n)

int __stdcall _VSScanServerNET_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _VSScanServerNET, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _VSScanServerNET, 2, *pIndex )
    
}

const ExtendedProxyFileInfo VSScanServerNET_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _VSScanServerNET_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _VSScanServerNET_StubVtblList,
    (const PCInterfaceName * ) & _VSScanServerNET_InterfaceNamesList,
    0, // no delegation
    & _VSScanServerNET_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

