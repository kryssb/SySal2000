#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "stdafx.h"
#include "Globals.h"
#include "EditConfig.h"

#include "Fitter.h"
#include "FrameGrabber.h"
#include "IO.h"
#include "Objective.h"
#include "RemoteControlServer.h"
#include "SheetMap.h"
#include "Stage2.h"
#include "Tracker.h"
#include "VisionProcessor4.h"
#include "IScanServer.h"
#include "AutomaticLightControl.h"
#include "PlateChanger.h"

#include "Fitter_i.c"
#include "FrameGrabber_i.c"
#include "IO_i.c"
#include "Objective_i.c"
#include "RemoteControlServer_i.c"
#include "SheetMap_i.c"
#include "Stage3_i.c"
#include "Tracker_i.c"
#include "VisionProcessor4_i.c"
#include "IScanServer_i.c"
#include "AutomaticLightControl_i.c"
#include "PlateChanger_i.c"
#include <eh.h>


// INTERNAL FUNCTIONS

int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
{  
	int Index;
	for (Index = 0; (Index < N) && (strncmp(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index, 
		DataName.Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN)); Index++);
	if (Index >= N)
	{
   		sscanf(DataName.Default, DataName.Format, (char *)StartPosition + DataName.Position);
   		return 0;
		};
	return sscanf(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
		SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataName.Format, (char *)StartPosition + DataName.Position);
	};

HRESULT EditConfig(IStage2 *iSt2, SySalConfig *pConfig, CWnd *pParent)
{
	ConfigData Temp;
	int i;
	for (i = 0; i < ConfigDataN; i++) 
		GetData(ConfigDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);	

	QueryDataInfo VStepQDI = {"VStep", "%f", 0, "-1"};
	float vstep = -1.0;
	GetData(VStepQDI, &vstep, pConfig->pItems, pConfig->CountOfItems);
	if (vstep > 0)
		Temp.TopStep = Temp.BottomStep = vstep;

	CEditConfig MyDlg(iSt2, pParent);

	MyDlg.C = Temp; 
	if (MyDlg.DoModal() == IDOK)
	{
		Temp = MyDlg.C; 
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(ConfigDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = ConfigDataN;
		int i;
		for (i = 0; i < ConfigDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				ConfigDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(ConfigDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(int *)((char *)&Temp + ConfigDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(float *)((char *)&Temp + ConfigDataName[i].Position));
			};
		return S_OK;
		};
	return S_FALSE;
}

#define MS_VC_EXCEPTION 0x406D1388

typedef struct tagTHREADNAME_INFO
{
   DWORD dwType; // Must be 0x1000.
   LPCSTR szName; // Pointer to name (in user addr space).
   DWORD dwThreadID; // Thread ID (-1=caller thread).
   DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;

void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName)
{
#ifndef _DEBUG
	return;
#else
	THREADNAME_INFO info;
	info.dwType = 0x1000;   
	info.szName = szThreadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}
#endif
}