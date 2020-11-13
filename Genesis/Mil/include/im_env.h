/*******************************************************************
 *
 * COPYRIGHT (c) 1994-1996 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IM_ENV_H__
#define __IM_ENV_H__

#if defined(__IMAPI_H__) && !defined(_IM_HOST_OS_DOS) && !defined(_IM_HOST_OS_NT) && !defined(_IM_HOST_OS_QNX4) && !defined(_IM_LOCAL_CODE)

#define PROD_NAME             "GENESIS"

#if defined(_MVP_MP) || defined(_MVP_PP)

#define _IM_COMP_MVP
#define _IM_LOCAL_CODE
#define _IM_LITTLE_ENDIAN
#define _MVP_REV              200
#define NDEBUG

#elif defined(__WATCOMC__) && !defined(__QNX__)    /* QNX4MARKER 1 */

#define _IM_COMP_WATCOM
#define _IM_HOST_X86_CODE
#define _IM_HOST_OS_DOS
#define NDEBUG

#pragma pack( push, 1 )             /* pop is in imapi.h */

#elif defined(__WATCOMC__) && defined(__QNX__)   /* QNX4MARKER 2 */

#define _IM_COMP_WATCOM
#define _IM_HOST_X86_CODE
#define _IM_HOST_OS_QNX4     /* QNX4MARKER 3 */
#define NDEBUG
#if !defined(I_UNIX)
#define I_UNIX
#endif

#pragma pack( push, 1 )             /* pop is in imapi.h */

#elif defined(_MSC_VER)

#define _IM_COMP_MICROSOFT
#define _IM_HOST_X86_CODE
#define _IM_HOST_OS_NT
#if !defined(_X86_)
#define _X86_
#endif
#if !defined(NT)
#define NT
#endif
#if !defined(WIN)
#define WIN
#endif
#if !defined(WIN32)
#define WIN32
#endif
#define NDEBUG

#pragma pack( push, enter_imapi_h)  /* pop is in imapi.h */
#pragma pack( 1 )

#endif

#endif

#ifndef INLINE_FUNCTION

#if defined(_IM_COMP_MVP)
#define INLINE_FUNCTION             static inline
#elif defined(_IM_COMP_BC)
#define INLINE_FUNCTION             inline
#elif defined(_IM_COMP_MICROSOFT)
#define INLINE_FUNCTION             __inline
#elif defined(_IM_COMP_WATCOM)
#define INLINE_FUNCTION             inline
#else
#define INLINE_FUNCTION             inline
#endif

#endif

/* DOS OS */
#if defined(_IM_HOST_OS_DOS)
#include <im_dos.h>

/* NT OS */
#elif defined(_IM_HOST_OS_NT)
#include <im_nt.h>

/* MVP OS */
#elif defined(_IM_LOCAL_CODE)
#include <im_mvp.h>

/* QNX 4 OS */       /* QNX4MARKER 4 */
#elif defined(_IM_HOST_OS_QNX4)
#include <im_qnx4.h>

/* Error Condition */
#else
#error IM_WARNING: Operating system and/or processor type not specified (Refer to image2.h header for compiler switch settings!)
#endif

#if   defined(I_UNIX)
#define DIRECTORY_SEPARATOR      "/"
#define PATHSEPARATOR            ":"
#else
#define DIRECTORY_SEPARATOR      "\\"
#define PATHSEPARATOR            ";"
#endif

#endif /*__IM_ENV_H__*/
