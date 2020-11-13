#ifndef _SYSAL_DISPATCHER_CONFIG_DATA_
#define _SYSAL_DISPATCHER_CONFIG_DATA_

#include "Config.h"

struct ConfigData
{
	struct t_CommOptions
	{
		BOOL Enable;
		char ServerName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
		char PipeName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
		int TimeOut;
		} Input, Output;
	UINT InBufferSize;
	BOOL Duplex;
	};

#endif