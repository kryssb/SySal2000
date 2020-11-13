#ifndef _VERTIGOSCAN_GLOBALS_H_
#define _VERTIGOSCAN_GLOBALS_H_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

extern "C" const CLSID CLSID_VertigoScanEx;

extern "C" const CLSID CLSID_NULL;

#include <windows.h>
#include "Config.h"
#include "Stage2.h"

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

extern const int ConfigDataN;

extern QueryDataInfo ConfigDataName[];

int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

HRESULT EditConfig(IStage2 *iSt2, SySalConfig *pConfig, CWnd *pParent = NULL);

#endif