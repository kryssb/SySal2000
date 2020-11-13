#include "Config2.h"
#include <windows.h>
#include <stdio.h>

int GetData(SySalConfig &C, int QueryDataCount, QueryDataInfo *pQDI, void *pC, bool UseDefault)
{
	int i, j;
	char *pD;
	for (i = 0; i < QueryDataCount; i++)
	{
		for (j = 0; (j < C.CountOfItems) && strcmp(pQDI[i].Name, C.pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN)); j++);
		if (j == C.CountOfItems)
		{
			if (UseDefault) pD = pQDI[i].Default;
			else return i;
			}
		else pD = C.pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
		switch (pQDI[i].Format)
		{
			case ST_INT:	if (sscanf(pD, "%d", (int *)((char *)pC + pQDI[i].Position)) != 1) return i;
							break;

			case ST_FLOAT:	if (sscanf(pD, "%f", (float *)((char *)pC + pQDI[i].Position)) != 1) return i;
							break;

			case ST_STRING:	strncpy(((char *)pC + pQDI[i].Position), pD, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
							break;

			default:		return i;			
			};
		};
	return i;
	};

int PutData(SySalConfig &C, int QueryDataCount, QueryDataInfo *pQDI, void *pC)
{
	if (C.pItems) CoTaskMemFree(C.pItems);
	C.pItems = 0;
	C.CountOfItems = 0;
	if (!QueryDataCount) return 0;
	if (!(C.pItems = (char *)CoTaskMemAlloc(QueryDataCount * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN)))) return 0;
	memset(C.pItems, 0, QueryDataCount * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	for (C.CountOfItems = 0; C.CountOfItems < QueryDataCount; C.CountOfItems++)
	{
		switch (pQDI[C.CountOfItems].Format)
		{
			case ST_INT:	sprintf(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
								"%d", *(int *)((char *)pC + pQDI[C.CountOfItems].Position));
							break;

			case ST_FLOAT:	sprintf(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
								"%g", *(float *)((char *)pC + pQDI[C.CountOfItems].Position));
							break;

			case ST_STRING:	strncpy(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
								((char *)pC + pQDI[C.CountOfItems].Position), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
							break;

			default:		return C.CountOfItems;
			};
		strncpy(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), pQDI[C.CountOfItems].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		};	
	return C.CountOfItems;
	};

int PutDataPreserve(SySalConfig &C, int QueryDataCount, QueryDataInfo *pQDI, void *pC)
{
	C.pItems = (char *)CoTaskMemRealloc(C.pItems, (QueryDataCount + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	memset(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 0, QueryDataCount * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	int OldCount = C.CountOfItems;
	for (; C.CountOfItems < (QueryDataCount + OldCount); C.CountOfItems++)
	{
		switch (pQDI[C.CountOfItems - OldCount].Format)
		{
			case ST_INT:	sprintf(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
								"%d", *(int *)((char *)pC + pQDI[C.CountOfItems - OldCount].Position));
							break;

			case ST_FLOAT:	sprintf(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
								"%g", *(float *)((char *)pC + pQDI[C.CountOfItems - OldCount].Position));
							break;

			case ST_STRING:	strncpy(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
								((char *)pC + pQDI[C.CountOfItems - OldCount].Position), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
							break;

			default:		return C.CountOfItems;
			};
		strncpy(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), pQDI[C.CountOfItems - OldCount].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		};	
	return C.CountOfItems;
	};
