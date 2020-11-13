/*******************************************************************
 *
 * COPYRIGHT (c) 2000 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IM_ENV_H__
#define __IM_ENV_H__


#if !defined(_IM_LOCAL_CODE) && defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif

// Need auto-config ?
#if (defined(__IMAPI_H__) || defined(__IMAGE2_H__)) && !defined(ODC_PROD_NAME)
// Auto-config compiler settings because no known compile mode setting defines

#define ODC_PROD_NAME         "ODYSSEY"

// Get the default Odyssey defines
#include <im_ddefn.h>

#endif   // End auto-config


#if !defined(__IMAPI_H__) && !defined(__IMAGE2_H__)
/* In some case im_env.h is included alone.
 * Neither by imapi.h and image2.h.
 * Be sure to define the proper packing in that case.
 * push & pop are not required for this special case.
 */

#if defined(_IM_COMP_GNUC) || defined(_IM_COMP_MICROSOFT)
#pragma pack( 1 )
#endif

#endif

#ifndef INLINE_FUNCTION
#if defined(_IM_COMP_MICROSOFT)
#define INLINE_FUNCTION                __inline

typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#if defined(_IM_COMP_MIL_PA)
#undef double
#define double __int64
#endif

#if defined(_IM_COMP_MIL_PA_NO_INLINE)
#undef INLINE_FUNCTION
#define INLINE_FUNCTION
#endif

#elif defined(_IM_LOCAL_CODE)
#define INLINE_FUNCTION                inline
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;

#elif defined(_IM_COMP_GNUC)

#if defined(__NEUTRINO__)
#define INLINE_FUNCTION                inline
#elif defined(_IM_HOST_OS_LINUX) && defined(_IM_DRIVER_CODE)
#define INLINE_FUNCTION                static inline
#else
#define INLINE_FUNCTION                __inline
#endif

typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;

#else
#define INLINE_FUNCTION                inline
#endif
#endif


#ifndef ASM_FUNCTION
#if defined(__MWERKS__)
#define ASM_FUNCTION                   asm
#define FORCE_DATA_IN_TEXT_SECTION     __declspec(section ".text") extern
#define INTERRUPT_FUNCTION

#else
#define ASM_FUNCTION
#define FORCE_DATA_IN_TEXT_SECTION     extern
#define INTERRUPT_FUNCTION

#endif
#endif

/* NT OS */
#if defined(_IM_HOST_OS_NT)
#include <im_nt.h>

/* PPC OS */
#elif defined(_IM_LOCAL_CODE)
#include <im_ppc.h>

/* LINUX OS */
#elif defined(_IM_HOST_OS_LINUX)
#include <im_linux.h>

/* NEUTRINO OS */
#elif defined(_IM_HOST_OS_NEUTRINO)
#include <im_nto.h>

/* Error Condition */
#else
#error IM_WARNING: Operating system and/or processor type not specified (Refer to image2.h header for compiler switch settings!)
#endif

#if defined(_IM_HOST_CODE)
// Typedef and define for _beginthread OS variant
   #if defined(_IM_HOST_OS_NT)
      #if defined(__cplusplus)
         #define ThreadReturnType      extern "C" void
      #else
         #define ThreadReturnType      void
      #endif
      #define ThreadExReturnType       unsigned __stdcall

      #define CreateThreadReturnType   unsigned long WINAPI
      #define retFromThread(x)
   #else
      typedef unsigned int ThreadReturnType         ;
      typedef unsigned int ThreadExReturnType       ;
      typedef unsigned int CreateThreadReturnType   ;

      #define retFromThread(x)         return(x)
   #endif
#endif

#if defined(_IM_LOCAL_CODE) || defined(_IM_HOST_OS_LINUX)
#define UNUSED_ARG(X)   X = X
#else
#define UNUSED_ARG(X)   X
#endif

#if defined(_IM_LOCAL_CODE)
#define ALIGN_ON_CACHE_LINE __attribute__((aligned(32)))
#else
#define ALIGN_ON_CACHE_LINE
#endif

#if defined(_IM_HOST_OS_LINUX) || defined(_IM_HOST_OS_NEUTRINO)
#define DIRECTORY_SEPARATOR      "/"
#define PATHSEPARATOR            ":"
#else
#define DIRECTORY_SEPARATOR      "\\"
#define PATHSEPARATOR            ";"
#endif

// add 64 bit pointer helper type from MSDEV
// for now, the values are in 32 bits
#ifndef _IM_HOST_OS_NT
typedef unsigned int UINT_PTR;
typedef int INT_PTR;
#endif

// define integer values that are fix size regardless of OS and compiler

typedef char               IM_INT8;
typedef unsigned char      IM_UINT8;
typedef short              IM_INT16;
typedef unsigned short     IM_UINT16;
typedef int                IM_INT32;
typedef unsigned int       IM_UINT32;
#if defined(_IM_HOST_OS_NT) && (_MSC_VER < 1310)
typedef __int64            IM_INT64;
typedef unsigned __int64   IM_UINT64;
#else
typedef long long          IM_INT64;
typedef unsigned long long IM_UINT64;
#endif

#if defined(_IM_HOST_OS_NT)
typedef INT_PTR            IM_INTPTR;
typedef UINT_PTR           IM_UINTPTR;
#else
#ifdef _IM_64BIT_CODE
typedef IM_INT64           IM_INTPTR;
typedef IM_UINT64          IM_UINTPTR;
#else
typedef IM_INT32           IM_INTPTR;
typedef IM_UINT32          IM_UINTPTR;
#endif
#endif

#ifndef  TRUE
#define  TRUE                                   1
#define  FALSE                                  0
#endif

#if !defined(_IM_DRIVER_CODE) && !defined(_IM_LOCAL_CODE)
#include <im_irqio.h>   /* Host general interrupt and io mechanism */
#endif

#endif /* __IM_ENV_H__ */
