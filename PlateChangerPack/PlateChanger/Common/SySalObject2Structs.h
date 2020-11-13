#ifndef _SYSAL_OBJECT_2_STRUCTURES_H_
#define _SYSAL_OBJECT_2_STRUCTURES_H_

#include "Config.h"

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	DWORD Context;

#ifdef USE_MIDL_INCOMPATIBLE_STRUCTS

	bool (_stdcall *pSaveConfig)(DWORD context, SySalConfig *pC, char *name);
	bool (_stdcall *pLoadConfig)(DWORD context, SySalConfig *pC, char *name);

#else

	DWORD pFunctionPointers[2];

#endif

	} ConfigManagerInterface;

#pragma pack(pop)

#endif