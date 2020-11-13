/************************************************************************/
/*  
*
* Filename     :  MILOS.H
* Owner        :  Matrox Imaging dept.
* Rev          :  $Revision:   5.0  $
* Content      :  This file contains the defines necessary to use the
*                 Matrox Imaging Library (MIL 4.0 and up) "C" user interface.
*                 under different operating systems
* Comments     :  This file has first become necesary to support the unicode
*                 strings under Windows CE.
*
* COPYRIGHT (c) Matrox Electronic Systems Ltd.
* All Rights Reserved
*************************************************************************/

#ifndef __MILOS_H
#define __MILOS_H

/************************************************************************/
/* Note that this header file might be included as a stand alone version*/
/************************************************************************/
#ifndef M_MIL_USE_OS
#define M_MIL_USE_WINDOWS       1
#endif 

/************************************************************************/
/* STRINGS RELATED DEFINITIONS                                          */
/************************************************************************/
#if   M_MIL_USE_CE
   #define MIL_TEXT(quote)        L##quote
   #define MT(quote)              L##quote
   typedef unsigned short         MILTCHAR;
   typedef unsigned short *       LPMILSTR;
   typedef const unsigned short * LPCMILSTR;
#elif M_MIL_USE_WINDOWS
   #define MIL_TEXT(quote)        quote
   #define MT(quote)              quote
   typedef char                   MILTCHAR;
   typedef char *                 LPMILSTR;
   typedef const char *           LPCMILSTR;
#elif M_MIL_USE_DOS_32
   #define MIL_TEXT(quote)        quote
   #define MT(quote)              quote
   typedef char                   MILTCHAR;
   typedef char *                 LPMILSTR;
   typedef const char *           LPCMILSTR;
#endif  

// Regular string functions' definition
#if M_MIL_USE_CE
   #define     MOs_ltoa     _ltow
   #define     MOs_ultoa    _ultow
   #define     MOs_atoi     _wtoi
   #define     MOs_atol     _wtol
   #define     MOs_strcpy   wcscpy
   #define     MOs_strncpy  wcsncpy
   #define     MOs_strcmp   wcscmp
   #define     MOs_stricmp  wcsicmp
   #define     MOs_strncmp  wcsncmp
   #define     MOs_strnicmp wcsnicmp
   #define     MOs_strcat   wcscat
   #define     MOs_strncat  wcsncat
   #define     MOs_strchr   wcschr
   #define     MOs_strlen   wcslen
   #define     MOs_sprintf  swprintf
   #define     MOs_strstr   wcsstr
   #define     MOs_sscanf   swscanf
   #define     MOs_fprintf  fwprintf
   #define     MOs_strtod   wcstod
   #define     MOs_strupr   wcsupr
   #define     MOs_strlwr   wcslwr
   #define     MOs_printf   wprintf
   #define     MOs_fputs    fputws
   #define     MOs_strtok   wcstok
   #define     MOs_ungetc   ungetwc
#elif (M_MIL_USE_DOS_32 || M_MIL_USE_WINDOWS)
   #define     MOs_ltoa     _ltoa
   #define     MOs_ultoa    _ultoa
   #define     MOs_atoi     atoi
   #define     MOs_atol     atol
   #define     MOs_strcpy   strcpy
   #define     MOs_strncpy  strncpy
   #define     MOs_strcmp   strcmp
   #define     MOs_stricmp  stricmp
   #define     MOs_strncmp  strncmp
   #define     MOs_strnicmp strnicmp
   #define     MOs_strcat   strcat
   #define     MOs_strncat  strncat
   #define     MOs_strchr   strchr
   #define     MOs_strlen   strlen
   #define     MOs_sprintf  sprintf
   #define     MOs_strstr   strstr
   #define     MOs_sscanf   sscanf
   #define     MOs_fprintf  fprintf
   #define     MOs_strtod   strtod
   #define     MOs_strupr   strupr
   #define     MOs_strlwr   strlwr
   #define     MOs_printf   printf
   #define     MOs_fputs    fputs
   #define     MOs_strtok   strtok
   #define     MOs_ungetc   ungetc
#else
   #error Operating system not supported in Milos.h!
#endif

/************************************************************************/
/* FILES RELATED DEFINITIONS                                            */
/************************************************************************/

#include <stdio.h>   /* Required for definition of FILE */
typedef FILE *       MIL_FILE;
typedef unsigned int    MIL_SIZE_T;

#if M_MIL_USE_CE
   #include "mil.h"
   #define     MOs_hypot   _hypot

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif
   MFTYPE32 LPMILSTR    MFTYPE MOs_getenv(LPCMILSTR VarName);
   MFTYPE32 int         MFTYPE MOs_putenv(LPCMILSTR VarName);
/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

   #define     MOs_fopen    _wfopen
   #define     MOs_fclose   fclose
   #define     MOs_fwrite   fwrite
   #define     MOs_fread    fread
   #define     MOs_fseek    fseek
   #define     MOs_ftell    ftell
   #define     MOs_feof     feof
   #define     MOs_ferror   ferror
   #define     MOs_fflush   fflush
   #define     MOs_fgetc    fgetc
   #define     MOs_fgets    fgetws
   #define     MOs_clearerr clearerr
   #define     MOs_remove(n)  DeleteFile(n) ? 0 : 1
#elif (M_MIL_USE_DOS_32 || M_MIL_USE_WINDOWS)
   #define     MOs_fopen    fopen
   #define     MOs_fclose   fclose
   #define     MOs_fwrite   fwrite
   #define     MOs_fread    fread
   #define     MOs_fseek    fseek
   #define     MOs_ftell    ftell
   #define     MOs_feof     feof
   #define     MOs_ferror   ferror
   #define     MOs_fflush   fflush
   #define     MOs_fgetc    fgetc
   #define     MOs_fgets    fgets
   #define     MOs_clearerr clearerr
   #define     MOs_remove   remove
   #define     MOs_hypot   hypot
   #define     MOs_getenv  getenv
   #define     MOs_putenv  putenv
#else
   #error Operating system not supported in Milos.h!
#endif

#endif /* #ifndef __MILOS_H */

          
