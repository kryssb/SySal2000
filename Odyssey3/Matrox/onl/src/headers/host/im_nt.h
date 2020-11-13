/*******************************************************************
 *
 * COPYRIGHT (c) 2000 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IM_NT_H__
#define __IM_NT_H__

#if defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif


#define TIME_TYPE    double

/* ---------------------------------------------------------------------- */
#if defined(_IM_COMP_MICROSOFT)

#if !defined(_IM_DRIVER_CODE)

#if defined(D_EXCEPTION)
// #define _DEBUG_MSDEV_CRT
#endif

#if defined(_DEBUG_MSDEV_CRT) && defined(D_EXCEPTION)
#define _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

#pragma pack( push, enter_im_nt_h)
#pragma pack( 8 )
#include <ctype.h>
#include <malloc.h>

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <conio.h>

#if defined(_DEBUG_MSDEV_CRT)
#include <crtdbg.h>
#endif

#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0400
#endif
#include <string.h>
#include <windows.h>    /* Microsoft windows.h require a pack of 8! */
#include <winioctl.h>
#pragma pack( pop, enter_im_nt_h)

#endif

#define IM_FTYPE     __cdecl        /* _stdcall can't be used because of varargs in inter */
#define IM_AFTYPE    __cdecl

/* Linux */
#define IM_LFTYPE
#define IM_LAFTYPE

/* On local code, the message on the stack must be 32 byte aligned */
#define IM_MSG_ALIGN
#if !defined(_IM_DRIVER_CODE) && !defined(_COMPILING_TRKSERVER) && !defined(TRK_SERVER_IN_USE)
#define IM_DLLEXPORT __declspec(dllexport)
#define IM_DLLIMPORT __declspec(dllimport)
#if defined(OBJ_FOR_DLL)
#define IM_DLLTYPE   IM_DLLEXPORT
#else
#define IM_DLLTYPE   IM_DLLIMPORT
#endif
#else
#define IM_DLLEXPORT
#define IM_DLLIMPORT
#define IM_DLLTYPE
#endif

#if !defined(IM_EXTC)
#if defined(__cplusplus) && !defined(_IM_DRIVER_CODE)
#define IM_EXTC      extern "C" IM_DLLTYPE
#define IM_EXTCPP    extern IM_DLLTYPE
#else
#define IM_EXTC      extern IM_DLLTYPE
#define IM_EXTCPP    extern IM_DLLTYPE
#endif
#endif

#endif


/* ---------------------------------------------------------------------- */
#define IM_VTYPE  volatile

#define SH_TYPE      IM_VTYPE

/*
 * Common typedefs used throughout source
 */


/* ---------------------------------------------------------------------- */
#if defined(_IM_DRIVER_CODE)

#undef  TIME_TYPE
#define TIME_TYPE    long

#if defined(_IM_COMP_MIL_PA)
extern "C"
{
#include <ntddk.h>
}
#endif

#else
typedef HANDLE       PID_HANDLE;
#endif   /* _IM_DRIVER_CODE */

#endif /*__IM_NT_H__*/
