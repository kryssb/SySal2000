#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "stdafx.h"
#include "Globals.h"
#include "EditConfig.h"

#include "..\Common\Fitter.h"
#include "..\Common\FrameGrabber.h"
#include "..\Common\IO.h"
#include "..\Common\Objective.h"
#include "..\Common\RemoteControlServer.h"
#include "..\Common\SheetMap.h"
#include "..\Common\Stage.h"
#include "..\Common\Tracker.h"
#include "..\Common\VisionProcessor2.h"
#include "..\Common\IScanServer.h"
#include "..\Common\AutomaticLightControl.h"

#include "..\Common\Fitter_i.c"
#include "..\Common\FrameGrabber_i.c"
#include "..\Common\IO_i.c"
#include "..\Common\Objective_i.c"
#include "..\Common\RemoteControlServer_i.c"
#include "..\Common\SheetMap_i.c"
#include "..\Common\Stage_i.c"
#include "..\Common\Tracker_i.c"
#include "..\Common\VisionProcessor2_i.c"
#include "..\Common\IScanServer_i.c"
#include "..\Common\AutomaticLightControl_i.c"


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

HRESULT EditConfig(SySalConfig *pConfig, CWnd *pParent)
{
	ConfigData Temp;
	int i;
	for (i = 0; i < ConfigDataN; i++) 
		GetData(ConfigDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CEditConfig MyDlg(pParent);

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
