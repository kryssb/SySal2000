#ifndef _DB_CONFIG_DATA_
#define _DB_CONFIG_DATA_

#include "..\Common\Connection.h"
#include "..\Common\Config.h"
#include "..\Common\GUIdefs.h"
#include "..\Common\datastructs.h"

struct ConfigData
{
	char DSN[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	char UserName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	char Password[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	BOOL InputEnabled;
	BOOL OutputEnabled;
	struct t_DBQueryData
	{
		char TableName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
		struct t_LinkId
		{
			bool IsLinked;
			char Name[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
			} Links[4];
		int CountOfAdditionalFields;
		struct t_AdditionalField
		{
			int Type;
			char Name[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
			} AdditionalField[DBP_MAX_ADDITIONAL_DATA_SIZE];
		} TrackPrediction;
	};

#endif