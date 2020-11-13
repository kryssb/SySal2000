#ifndef _SYSAL_CONFIG_2_
#define _SYSAL_CONFIG_2_

#include "Config.h"

#define ST_NULL		0
#define ST_INT		1
#define ST_FLOAT	2
#define ST_STRING	3

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format;
	int Position;
	char Default[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	};

int GetData(SySalConfig &C, int QueryDataCount, QueryDataInfo *pQDI, void *pC, bool UseDefault);
int PutData(SySalConfig &C, int QueryDataCount, QueryDataInfo *pQDI, void *pC);
int PutDataPreserve(SySalConfig &C, int QueryDataCount, QueryDataInfo *pQDI, void *pC);

#endif