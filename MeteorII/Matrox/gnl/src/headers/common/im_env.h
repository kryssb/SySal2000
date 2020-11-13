/*******************************************************************
 *
 * COPYRIGHT (c) 1994-1996 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IM_ENV_H__
#define __IM_ENV_H__

#if !defined(_IM_LOCAL_CODE) && defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif

// Need auto-config ?
#if (defined(__IMAPI_H__) || defined(__IMAGE2_H__)) && !defined(_IM_HOST_OS_DOS) && !defined(_IM_HOST_OS_NT) && !defined(_IM_HOST_OS_QNX4) && !defined(_IM_HOST_OS_LINUX) && !defined(_IM_HOST_OS_NTO) && !defined(_IM_LOCAL_CODE) && !defined(_IM_HOST_OS_VPLUS)
// Auto-config compiler settings because no known compile mode setting defines

#define PROD_NAME             "GENESIS"

#if defined(_MVP_MP) || defined(_MVP_PP)

#define _IM_COMP_MVP
#define _IM_LOCAL_CODE
#define _IM_LITTLE_ENDIAN
#if !defined(NDEBUG) && !defined(_DEBUG)
#define NDEBUG          /* Disable assert */
#endif

#elif defined(__WATCOMC__) && !defined(__QNX__)

#define _IM_COMP_WATCOM
#define _IM_HOST_X86_CODE
#define _IM_HOST_OS_DOS
#define _IM_LITTLE_ENDIAN
#if !defined(NDEBUG)
#define NDEBUG          /* Disable assert */
#endif

#elif defined(__WATCOMC__) && defined(__QNX__)

#define _IM_COMP_WATCOM
#define _IM_HOST_X86_CODE
#define _IM_HOST_OS_QNX4
#define _IM_LITTLE_ENDIAN
#if !defined(NDEBUG)
#define NDEBUG          /* Disable assert */
#endif
#if !defined(I_UNIX)
#define I_UNIX
#endif

#elif defined(__GNUC__) && defined(__LINUX__) && defined(__i386__)

#define _IM_COMP_GNUC
#define _IM_HOST_X86_CODE
#define _IM_HOST_OS_LINUX
#define _IM_LITTLE_ENDIAN
#if !defined(NDEBUG)
#define NDEBUG          /* Disable assert */
#endif
#if !defined(I_UNIX)
#define I_UNIX
#endif

#elif defined(__GNUC__) && defined(__NTO__) && defined(__i386__)

#define _IM_COMP_GNUC
#define _IM_HOST_OS_X86_CODE
#define _IM_HOST_OS_NTO
#define _IM_LITTLE_ENDIAN
#if !defined(NDEBUG) /* Disable assert */
#define NDEBUG
#endif
#if !defined(I_UNIX)
#define I_UNIX
#endif

#elif defined(_MSC_VER)

#define _IM_COMP_MICROSOFT
#define _IM_HOST_X86_CODE
#define _IM_HOST_OS_NT
#define _IM_LITTLE_ENDIAN
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
#if !defined(NDEBUG)
#define NDEBUG          /* Disable assert */
#endif

#elif defined(_VPLUS_)

#ifndef REG_FIELD_TYPE
#define REG_FIELD_TYPE unsigned long int
#endif

#define _IM_COMP_VPLUS
#define _IM_HOST_68030_CODE
#define _IM_HOST_OS_VPLUS
#define _SLIM_GENLIB
#define _IM_BIG_ENDIAN
#define HOST_BUFFER_ALLOWED      0
#define USE_EMBEDDED_DCF         1
#if !defined(NDEBUG) && !defined(_DEBUG)
#define NDEBUG          /* Disable assert */
#endif
#if !defined(I_UNIX)
#define I_UNIX
#endif

#endif   // End compiler choice

#endif   // End auto-config


#if !defined(__IMAPI_H__) && !defined(__IMAGE2_H__)
/* In some case im_env.h is included alone.
 * Neither by imapi.h and image2.h.
 * Be sure to define the proper packing in that case.
 * push & pop are not required for this special case.
 */

#if defined(_IM_COMP_WATCOM) || defined(_IM_COMP_GNUC) || defined(_IM_COMP_MICROSOFT)
#pragma pack( 1 )
#endif

#endif


#ifndef INLINE_FUNCTION
#if defined(_IM_COMP_MVP) || defined(_IM_COMP_VPLUS)
#define INLINE_FUNCTION             static inline

#elif defined(_IM_COMP_BC)
#define INLINE_FUNCTION             inline

#elif defined(_IM_COMP_MICROSOFT)
#define INLINE_FUNCTION             __inline

#elif defined(_IM_COMP_WATCOM)
#define INLINE_FUNCTION             inline

#elif defined(_IM_COMP_PPC) && defined(__HIGHC__)
#define INLINE_FUNCTION             _Inline

#elif defined(_IM_COMP_GNUC) && defined(__LINUX__)
#define INLINE_FUNCTION             static inline

#elif defined(_IM_COMP_GNUC) && defined(__NTO__)
#define INLINE_FUNCTION             inline

#else
#define INLINE_FUNCTION             inline

#endif
#endif


#ifndef ASM_FUNCTION
#if defined(__MWERKS__)
#define ASM_FUNCTION                   asm
#define FORCE_DATA_IN_TEXT_SECTION     __declspec(section ".text") extern
#define INTERRUPT_FUNCTION

#elif defined(__HIGHC__)
#define ASM_FUNCTION
/* #define FORCE_DATA_IN_TEXT_SECTION     __declspec(section ".text") extern */
#define INTERRUPT_FUNCTION              _Interrupt
#define FORCE_DATA_IN_TEXT_SECTION     extern
#ifdef __ALTIVEC
#undef __ALTIVEC
#endif
#include <ppc/asm.h>

#else
#define ASM_FUNCTION
#define FORCE_DATA_IN_TEXT_SECTION     extern
#define INTERRUPT_FUNCTION

#endif
#endif

/* DOS OS */
#if defined(_IM_HOST_OS_DOS)
#include <im_dos.h>

/* NT OS */
#elif defined(_IM_HOST_OS_NT)
#include <im_nt.h>

/* C80 OS */
#elif defined(_IM_COMP_MVP)
#include <im_mvp.h>

/* PPC OS */
#elif defined(_IM_LOCAL_CODE) && defined(_IM_COMP_PPC)
#include <im_ppc.h>

/* QNX 4 OS */
#elif defined(_IM_HOST_OS_QNX4)
#include <im_qnx4.h>

/* To make sure it is set, in Watcom 11 under NT, doesn't seem to be set */
#if !defined(I_UNIX)
#define I_UNIX
#endif

/* LINUX OS */
#elif defined(_IM_HOST_OS_LINUX)
#include <im_linux.h>

/* NEUTRINO OS */
#elif defined(_IM_HOST_OS_NTO)
#include <im_nto.h>

/* V+ OS */
#elif defined(_IM_HOST_OS_VPLUS)
#include <im_vplus.h>

/* Error Condition */
#else
#error IM_WARNING: Operating system and/or processor type not specified (Refer to image2.h header for compiler switch settings!)
#endif

#if !defined(_IM_HOST_OS_VPLUS) || defined(_IM_COMP_MICROSOFT)
#define  SWAP_BYTES_LONG(val)             (val)
#define  SWAP_BYTES_LCONST(lcnst)         (lcnst)
#define  SWAP_BYTES_SCONST(scnst)         (scnst)
#define  SWAP_BYTES_IF_BIG_ENDIAN(val)    (val)
#endif

#if   defined(I_UNIX)
#define DIRECTORY_SEPARATOR      "/"
#define PATHSEPARATOR            ":"
#else
#define DIRECTORY_SEPARATOR      "\\"
#define PATHSEPARATOR            ";"
#endif

IM_EXTC void IM_FTYPE mp_sys_dbg_set_marker(char *file, int line);
IM_EXTC void IM_FTYPE mp_sys_dbg_dump_markers(void);
#if defined(D_EXCEPTION) && defined(DBG_MARKER_ENABLED)
#define MtxDbgSetMarker()  mp_sys_dbg_set_marker(__FILE__, __LINE__)
#else
#define MtxDbgSetMarker()
#endif

#endif /*__IM_ENV_H__*/
