/*******************************************************************
 *
 * COPYRIGHT (c) 1994-1997 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IMAPI_H__
#define __IMAPI_H__

#if !defined(_IM_LOCAL_CODE) && defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif

#if defined(_IM_HOST_OS_NT) && defined(_IM_COMP_MICROSOFT)
#pragma pack( push, enter_imapi_h)
#pragma pack( 1 )
#elif defined(_IM_HOST_OS_DOS) && defined(_IM_COMP_WATCOM)
#pragma pack( push, 1 )
#endif

#include <im_env.h>     /* Genesis Operating System and Processor environment configuration header */

#include <imapitef.h>   /* Genesis API Type Definitions   */
#include <imapidef.h>   /* Genesis API Defines            */
#include <imapipro.h>   /* Genesis API Prototypes         */


#if defined(_IM_HOST_OS_NT) && defined(_IM_COMP_MICROSOFT)
#pragma pack( pop, enter_imapi_h)
#elif (defined(_IM_HOST_OS_DOS) || defined(_IM_HOST_OS_QNX4)) && defined(_IM_COMP_WATCOM)
#pragma pack( pop )
#elif defined(_IM_HOST_OS_LINUX) || defined(_IM_HOST_OS_NTO)
#pragma pack()
#endif

#endif /* __IMAPI_H__ */
