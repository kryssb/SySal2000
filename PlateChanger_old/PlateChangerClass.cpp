// FlexStage2.cpp : Implementation of CPlateChangerClass
#include "stdafx.h"
#include "PlateChanger.h"
#include "PlateChangerClass.h"

#include <math.h>
#include "EditConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CPlateChangerClass
const int ConfigDataN = 31;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataName[ConfigDataN] =
{
	{"COMPort",				"%d",   STRUCT_OFFSET(ConfigData, COMPort),			"1"},
	{"PickupTh",			"%d",   STRUCT_OFFSET(ConfigData, Pickup.Theta),	"0"},
	{"PickupZ",				"%d",   STRUCT_OFFSET(ConfigData, Pickup.Z),		"0"},
	{"WaitingTh",			"%d",   STRUCT_OFFSET(ConfigData, Waiting.Theta),	"0"},
	{"WaitingZ",			"%d",   STRUCT_OFFSET(ConfigData, Waiting.Z),		"0"},
	{"ScanningStageTh",		"%d",   STRUCT_OFFSET(ConfigData, ScanningStage.Theta),"0"},
	{"ScanningStageZ",		"%d",   STRUCT_OFFSET(ConfigData, ScanningStage.Z),	"0"},
	{"ReleaseTh",			"%d",   STRUCT_OFFSET(ConfigData, Release.Theta),	"0"},
	{"ReleaseZ",			"%d",   STRUCT_OFFSET(ConfigData, Release.Z),		"0"},
	{"SafeTh",				"%d",   STRUCT_OFFSET(ConfigData, Safe.Theta),		"0"},
	{"SafeZ",				"%d",   STRUCT_OFFSET(ConfigData, Safe.Z),			"0"},

	{"ToSafeSpeedTh",		"%d",   STRUCT_OFFSET(ConfigData, ToSafe.Speed.Theta),	"100"},
	{"ToSafeAccTh",			"%d",   STRUCT_OFFSET(ConfigData, ToSafe.Acc.Theta),	"100"},
	{"ToSafeSpeedZ",		"%d",   STRUCT_OFFSET(ConfigData, ToSafe.Speed.Z),		"100"},
	{"ToSafeAccZ",			"%d",   STRUCT_OFFSET(ConfigData, ToSafe.Acc.Z),		"100"},

	{"ToWaitSpeedTh",		"%d",   STRUCT_OFFSET(ConfigData, ToWait.Speed.Theta),	"100"},
	{"ToWaitAccTh",			"%d",   STRUCT_OFFSET(ConfigData, ToWait.Acc.Theta),	"100"},
	{"ToWaitSpeedZ",		"%d",   STRUCT_OFFSET(ConfigData, ToWait.Speed.Z),		"100"},
	{"ToWaitAccZ",			"%d",   STRUCT_OFFSET(ConfigData, ToWait.Acc.Z),		"100"},

	{"ToPickupSpeedTh",		"%d",   STRUCT_OFFSET(ConfigData, ToPickup.Speed.Theta),"100"},
	{"ToPickupAccTh",		"%d",   STRUCT_OFFSET(ConfigData, ToPickup.Acc.Theta),	"100"},
	{"ToPickupSpeedZ",		"%d",   STRUCT_OFFSET(ConfigData, ToPickup.Speed.Z),	"100"},
	{"ToPickupAccZ",		"%d",   STRUCT_OFFSET(ConfigData, ToPickup.Acc.Z),		"100"},

	{"ToStageSpeedTh",		"%d",   STRUCT_OFFSET(ConfigData, ToStage.Speed.Theta),	"100"},
	{"ToStageAccTh",		"%d",   STRUCT_OFFSET(ConfigData, ToStage.Acc.Theta),	"100"},
	{"ToStageSpeedZ",		"%d",   STRUCT_OFFSET(ConfigData, ToStage.Speed.Z),		"100"},
	{"ToStageAccZ",			"%d",   STRUCT_OFFSET(ConfigData, ToStage.Acc.Z),		"100"},
	
	{"ToReleaseSpeedTh",	"%d",   STRUCT_OFFSET(ConfigData, ToRelease.Speed.Theta),	"100"},
	{"ToReleaseAccTh",		"%d",   STRUCT_OFFSET(ConfigData, ToRelease.Acc.Theta),		"100"},
	{"ToReleaseSpeedZ",		"%d",   STRUCT_OFFSET(ConfigData, ToRelease.Speed.Z),		"100"},
	{"ToReleaseAccZ",		"%d",   STRUCT_OFFSET(ConfigData, ToRelease.Acc.Z),			"100"}
	

	};

CPlateChangerClass::CPlateChangerClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Name[0] = 0;
	HStatusChangeEvent = 0;
	pMonitor = 0;
	HMonitorMutex = 0;
	HRun = 0;
	HTerminate = 0;
	pRefreshThread = 0;


	HMonitorMutex = CreateMutex(NULL, FALSE, 0);
	HRun = CreateEvent(NULL, TRUE, TRUE, 0);
	HTerminate = CreateEvent(NULL, TRUE, FALSE, 0);
	{
		SySalConfig VoidConfig = {"", 0, 0};
		int i;
		for (i = 0; i < ConfigDataN; i++)
			GetData(ConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
		};
	//SAMUEL: Call some initialization function
	CWnd OwnerWnd;
	OwnerWnd.Attach(::GetTopWindow(0));
	pMonitor = new CMonitor(&C, &HMonitorMutex, &HRun, this, Enabler);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);

	OwnerWnd.Detach();
	CRect WndRect;
	CRect WorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
	pMonitor->GetWindowRect(&WndRect);
	pMonitor->SetWindowPos(0, WorkArea.right - WndRect.Width(), 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
	pMonitor->EnableManualControl(false);
	pRefreshThread = AfxBeginThread((AFX_THREADPROC)RefreshThreadHook, (void *)this);
	pRefreshThread->m_bAutoDelete = FALSE;
};

CPlateChangerClass::~CPlateChangerClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (HTerminate) SetEvent(HTerminate);
	if (pRefreshThread)
	{
		WaitForSingleObject(pRefreshThread->m_hThread, INFINITE);
		delete pRefreshThread;
		pRefreshThread = 0;
		};
	if (pMonitor) 
	{
		WaitForSingleObject(HMonitorMutex, INFINITE);
		delete pMonitor;
		pMonitor = 0;
		};
	if (HMonitorMutex) CloseHandle(HMonitorMutex);
	if (HRun) CloseHandle(HRun);
	if (HTerminate) CloseHandle(HTerminate);
	};

//ISySalObject

STDMETHODIMP CPlateChangerClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < ConfigDataN) && (GetData(ConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < ConfigDataN) return S_FALSE;
	//SAMUEL: Call some initialization
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
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
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(int *)((char *)&C + ConfigDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(float *)((char *)&C + ConfigDataName[i].Position));		
		};
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ConfigData Temp;
	int i;
	for (i = 0; i < ConfigDataN; i++) 
		GetData(ConfigDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

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
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CPlateChangerClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!pMonitor) return (bEnable) ? S_FALSE : S_OK;
	pMonitor->ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
	pMonitor->EnableWindow(bEnable ? TRUE : FALSE);
	pMonitor->EnableManualControl(false);
	if (bEnable) SetEvent(HRun);
	else ResetEvent(HRun);
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CPlateChangerClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CPlateChangerClass::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HANDLE HTemp = 0;
	switch (n)
	{
		case 0:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON32), IMAGE_ICON, 32, 32, LR_SHARED);
					break;

		case 1:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON64), IMAGE_ICON, 64, 64, LR_SHARED);
					break;

		default:	return E_INVALIDARG;
		};
	*pHICON = (HSySalHICON)HTemp;
	return S_OK;	
}

STDMETHODIMP CPlateChangerClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Plate Changer", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::SyncExec()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPlateChangerClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CPlateChangerClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPlateChangerClass::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = (HTerminate && pMonitor && pRefreshThread && 
		HMonitorMutex && HRun) ? SYSAL_READYSTATUS_READY 
		: SYSAL_READYSTATUS_INCOMPLETE_CONFIG;
	return S_OK;
}

// IPlateChanger

STDMETHODIMP CPlateChangerClass::EnableManualControl(boolean bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!pMonitor) return S_FALSE;
	pMonitor->EnableManualControl(bEnable);
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::IsManualControlEnabled(boolean *pbEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pMonitor) return S_FALSE;
	*pbEnable = pMonitor->IsManualControlEnabled();
	return S_OK;
}


STDMETHODIMP CPlateChangerClass::LoadPlate(Identifier id)
{
	// SAMUEL: IMPLEMENT!!!!!!!!!!!!!!!!!
	return E_NOTIMPL;	
}


STDMETHODIMP CPlateChangerClass::UnloadPlate()
{
	// SAMUEL: IMPLEMENT!!!!!!!!!!!!!!!!!
	return E_NOTIMPL;	
}


// Non-exported methods

UINT CPlateChangerClass::RefreshThreadHook(void *pOwner)
{
	return ((CPlateChangerClass *)pOwner)->RefreshThread();
}

UINT CPlateChangerClass::RefreshThread()
{
	HANDLE HEvs[2];
	HEvs[0] = HTerminate;
	HEvs[1] = HRun;
	DWORD ExitCause;
	do
	{
		ExitCause = WaitForMultipleObjects(2, HEvs, FALSE, INFINITE);
		if (ExitCause == (WAIT_OBJECT_0 + 1) || ExitCause == (WAIT_ABANDONED_0 + 1)) 
		{
			pMonitor->PostMessage(UM_REFRESH);
			Sleep(50);
			};
		}
	while (ExitCause != WAIT_OBJECT_0);
	return 0;
}

void CPlateChangerClass::Enabler(void *pContext, bool bEnable)
{
	CPlateChangerClass *This = (CPlateChangerClass *)pContext;
	WaitForSingleObject(This->HMonitorMutex, INFINITE);
	if (!bEnable)
	{
		// SAMUEL: Go to software control
		}
	else
	{
		// SAMUEL: Go to manual control
        };
	ReleaseMutex(This->HMonitorMutex);
}

// INTERNAL FUNCTIONS

int CPlateChangerClass::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
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

