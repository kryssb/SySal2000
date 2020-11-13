#ifndef _VS4_DEBUG_H_
#define _VS4_DEBUG_H_

int debug_Trace_String(char *x, const char *file, const int line, int op);

int debug_Trace_Int(int x, const char *file, const int line, int op);

void *debug_Trace_Hex(void *x, const char *file, const int line, int op);

#ifdef _DEBUG

#define debug_Malloc(a) debug_Trace_Hex(malloc(a), __FILE__, __LINE__, 8)

#define debug_Realloc(a, b) debug_Trace_Hex(realloc(a, b), __FILE__, __LINE__, 9)

#define debug_Free(a) free(debug_Trace_Hex(a, __FILE__, __LINE__, 10))

#define debug_GlobalAlloc(a, b) debug_Trace_Hex(GlobalAlloc(a, b), __FILE__, __LINE__, 16)

#define debug_GlobalFree(a) GlobalFree(debug_Trace_Hex(a, __FILE__, __LINE__, 18))

#else

#define debug_Malloc malloc

#define debug_Realloc realloc

#define debug_Free free

#define debug_GlobalAlloc GlobalAlloc

#define debug_GlobalFree GlobalFree

#endif

#endif