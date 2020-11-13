#include "debug.h"
#include "stdafx.h"
#include "stdio.h"

#ifndef DEBUG_TRACE_FILE
#define DEBUG_TRACE_FILE "c:\\acq\\vs6_trace.txt"
#endif

int debug_Trace_String(char *x, const char *file, const int line, int op)
{
	FILE *f = fopen(DEBUG_TRACE_FILE, "a+t");
	fprintf(f, "%s\t%d\t:\t%s\t%d\n", file, line, x, op);
	fclose(f);
	return 0;
}

int debug_Trace_Int(int x, const char *file, const int line, int op)
{
	FILE *f = fopen(DEBUG_TRACE_FILE, "a+t");
	fprintf(f, "%s\t%d\t:\t%d\t%d\n", file, line, x, op);
	fclose(f);
	return x;
}

void *debug_Trace_Hex(void *x, const char *file, const int line, int op)
{
	FILE *f = fopen(DEBUG_TRACE_FILE, "a+t");
	fprintf(f, "%s\t%d\t:\t%08X\t%d\n", file, line, x, op);
	fclose(f);
	return x;
}


