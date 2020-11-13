#include "debug.h"
#include "stdio.h"

int debug_Trace_String(char *x, const char *file, const int line, int op)
{
	FILE *f = fopen("c:\\acq\\vs4_trace.txt", "a+t");
	fprintf(f, "%s\t%d\t:\t%s\t%d\n", file, line, x, op);
	fclose(f);
	return 0;
}

int debug_Trace_Int(int x, const char *file, const int line, int op)
{
	FILE *f = fopen("c:\\acq\\vs4_trace.txt", "a+t");
	fprintf(f, "%s\t%d\t:\t%d\t%d\n", file, line, x, op);
	fclose(f);
	return x;
}

void *debug_Trace_Hex(void *x, const char *file, const int line, int op)
{
	FILE *f = fopen("c:\\acq\\vs4_trace.txt", "a+t");
	fprintf(f, "%s\t%d\t:\t%08X\t%d\n", file, line, x, op);
	fclose(f);
	return x;
}


