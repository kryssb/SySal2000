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
 *                   06/14/94   09:58:52
 *
 * Reviewed:
 *
 * Last Modified:    ETAPUCU
 *                   10/07/94   Header Upkeep!
 *
 * Notes:
 *
 *******************************************************************/

#ifndef __IM_DOS_H__
#define __IM_DOS_H__

#define TIME_TYPE    double

#include <ctype.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ---------------------------------------------------------------------- */
#if defined(_IM_COMP_MICROSOFT)
#error ERROR: __IM_DOS_H__ TBD for _IM_COMP_MICROSOFT
#define IM_FTYPE
#define IM_AFTYPE
#define IM_PTYPE
#define IM_HTYPE

#define IM_DLLEXPORT
#define IM_DLLIMPORT
#define IM_DLLTYPE

#ifdef __cplusplus
#define IM_EXTC      extern "C"
#define IM_EXTCPP    extern
#else
#define IM_EXTC      extern
#define IM_EXTCPP    extern
#endif


/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_WATCOM)

#ifdef __cplusplus
#pragma warning 604 9;
#pragma warning 594 9;
#if !defined(D_EXCEPTION)
#pragma warning 726 9;     /* no reference to formal parameter ... */
#endif
#endif

#include <malloc.h>

#define IM_FTYPE     cdecl
#define IM_AFTYPE    cdecl
#define IM_PTYPE
#define IM_HTYPE

#define IM_DLLEXPORT
#define IM_DLLIMPORT
#define IM_DLLTYPE

#ifdef __cplusplus
#define IM_EXTC      extern "C"
#define IM_EXTCPP    extern
#else
#define IM_EXTC      extern
#define IM_EXTCPP    extern
#endif

IM_EXTC unsigned char __WD_Present;

/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_BC)
#include <alloc.h>

/* Pharlap-specific section */
#if defined(DOSX286)
#include <phapi.h>

/* Defines */
#define IM_FTYPE
#define IM_AFTYPE
#define IM_PTYPE     far
#define IM_HTYPE     huge
#else
#define IM_FTYPE
#define IM_AFTYPE
#define IM_PTYPE
#define IM_HTYPE
#endif

#define IM_DLLEXPORT
#define IM_DLLIMPORT
#define IM_DLLTYPE

#ifdef __cplusplus
#define IM_EXTC      extern "C"
#define IM_EXTCPP    extern
#else
#define IM_EXTC      extern
#define IM_EXTCPP    extern
#endif

#endif



/* ---------------------------------------------------------------------- */
#define IM_VTYPE     volatile

#define SH_TYPE      IM_VTYPE


/* ---------------------------------------------------------------------- */
#include <im_irqio.h>      /* Host general interrupt and IO mechanism */

#endif /*__IM_DOS_H__*/
