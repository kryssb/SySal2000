/*******************************************************************
 *
 * COPYRIGHT (c) 1994 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

/*******************************************************************
 *
 * Synopsis:
 *
 * Bugs:
 *
 * Designed:         ETAPUCU
 *                   06/30/94   10:28:52
 *
 * Reviewed:
 *
 * Last modified:    06/30/94
 *
 * Notes:
 *
 *******************************************************************/

#ifndef __IM_NT_H__
#define __IM_NT_H__


#define TIME_TYPE    double

/* ---------------------------------------------------------------------- */
#if defined(_IM_COMP_MICROSOFT)

#if !defined(_IM_HOST_OS_NT_KERNEL)

#if 0 && defined(D_EXCEPTION)
#define _DEBUG_MSDEV_CRT
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

#if defined(_DEBUG_MSDEV_CRT) && defined(D_EXCEPTION)
#include <crtdbg.h>
#endif

#define _WIN32_WINNT 0x0400
#include <string.h>
#include <windows.h>    /* Microsoft windows.h require a pack of 8! */
#include <winioctl.h>
#pragma pack( pop, enter_im_nt_h)

#endif

#define IM_FTYPE     __cdecl        /* _stdcall can't be used because of varargs in inter */
#define IM_AFTYPE    __cdecl
#define IM_PTYPE
#define IM_HTYPE

#if !defined(_IM_HOST_OS_NT_KERNEL)
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

#if defined(__cplusplus) && !defined(_IM_HOST_OS_NT_KERNEL)
#define IM_EXTC      extern "C" IM_DLLTYPE
#define IM_EXTCPP    extern IM_DLLTYPE
#else
#define IM_EXTC      extern IM_DLLTYPE
#define IM_EXTCPP    extern IM_DLLTYPE
#endif

/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_WATCOM)
#if !defined(_IM_HOST_OS_NT_KERNEL)
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#endif

#error ERROR: __IM_NT_H__ TBD for _IM_COMP_WATCOM
#define IM_FTYPE
#define IM_AFTYPE
#define IM_PTYPE
#define IM_HTYPE

#define IM_DLLEXPORT
#define IM_DLLIMPORT
#define IM_DLLTYPE

#define IM_EXTC
#define IM_EXTCPP

/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_BC)
#if !defined(_IM_HOST_OS_NT_KERNEL)
#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#endif

#error ERROR: __IM_NT_H__ TBD for _IM_COMP_BC
#define IM_FTYPE
#define IM_AFTYPE
#define IM_PTYPE
#define IM_HTYPE

#define IM_DLLEXPORT
#define IM_DLLIMPORT
#define IM_DLLTYPE

#define IM_EXTC
#define IM_EXTCPP

#endif


/* ---------------------------------------------------------------------- */
#define IM_VTYPE  volatile

#define SH_TYPE      IM_VTYPE


/* ---------------------------------------------------------------------- */
#if defined(_IM_HOST_OS_NT_KERNEL)

#undef  TIME_TYPE
#define TIME_TYPE    long

extern "C"
{
#include <ntddk.h>
}

#if !defined(DDK_VERSION4)
#define MmNonCached           FALSE
#endif


#endif   /* _IM_HOST_OS_NT_KERNEL */

/* ---------------------------------------------------------------------- */
#if !defined(M_MTXSERVICE)
#include <im_irqio.h>      /* Host general interrupt and IO mechanism */
#endif

#endif /*__IM_NT_H__*/
