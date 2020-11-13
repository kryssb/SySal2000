// Default Odyssey #defines used to control code behavior for OS and compiler
// variant.

// Used for Microsoft Windows
#if defined(_MSC_VER)

   #ifndef _IM_COMP_MICROSOFT
   #define _IM_COMP_MICROSOFT
   #endif

   #ifndef _IM_HOST_OS_NT
   #define _IM_HOST_OS_NT
   #endif

   #ifndef _IM_HOST_CODE
   #define _IM_HOST_CODE
   #endif

   // check to see if we compile for 64 bit target
   #if defined(_WIN64)
   #define _IM_64BIT_CODE
   #endif

// Used for Linux and QNX Neutrino host OS
#elif defined(__GNUC__)

   #ifndef _IM_COMP_GNUC
   #define _IM_COMP_GNUC
   #endif

   #if defined(__linux__)  // predefine for GCC on Linux

      #ifndef _IM_HOST_OS_LINUX
      #define _IM_HOST_OS_LINUX
      #endif

   #elif defined(__NEUTRINO__)

      #ifndef _IM_HOST_OS_NEUTRINO
      #define _IM_HOST_OS_NEUTRINO
      #endif

   #endif   // end of OS variant

   // check to see if we compile for 64 bit target
   #ifdef __LP64__
   #define _IM_64BIT_CODE
   #endif

   #ifndef _IM_HOST_CODE
   #define _IM_HOST_CODE
   #endif

// Used for Odyssey embedded PowerPC
#elif defined(__MWERKS__)

   #ifndef _IM_COMP_PPC
   #define _IM_COMP_PPC
   #endif

   #ifndef _IM_LOCAL_CODE
   #define _IM_LOCAL_CODE
   #endif

#endif   // end of Compiler types
