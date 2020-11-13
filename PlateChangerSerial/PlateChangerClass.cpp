// FlexStage2.cpp : Implementation of CPlateChangerClass
#include "stdafx.h"
#include "PlateChanger.h"
#include "PlateChangerClass.h"

#include <math.h>
#include "EditConfig.h"
//#include "..//Common//Stage.h"
//#include "..//Common//Stage2.h"

/////////////////////////////////////////////////////////////////////////////
// CPlateChangerClass
const int ConfigDataN = 22;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataName[ConfigDataN] =
{
	{"NumberOfAttempt",				"%d",   STRUCT_OFFSET(ConfigData, NumberOfAttempt),			"10"},
	{"PositionTimeout",				"%d",   STRUCT_OFFSET(ConfigData, PositionTimeout),			"50"},
	{"VacuumTimeout",				"%d",   STRUCT_OFFSET(ConfigData, VacuumTimeout),			"10"},
	{"BubbleTimeout",				"%d",   STRUCT_OFFSET(ConfigData, BubbleTimeout),			"600"},
	{"NumberOfBanks",				"%d",   STRUCT_OFFSET(ConfigData, NumberOfBanks),			"3"},
	{"WithSeparators",				"%d",   STRUCT_OFFSET(ConfigData, WithSeparators),			"2"},
	{"SeparationAttempts",			"%d",   STRUCT_OFFSET(ConfigData, SeparationAttempts),		"3"},
	{"LimOffsetX",			"%f",   STRUCT_OFFSET(ConfigData, LimOffsetX),		"-100000"},
	{"LimOffsetY",			"%f",   STRUCT_OFFSET(ConfigData, LimOffsetY),		"-30700"},
	{"FMOffsetX",			"%f",   STRUCT_OFFSET(ConfigData, FMOffsetX),		"-44000"},
	{"FMOffsetY",			"%f",   STRUCT_OFFSET(ConfigData, FMOffsetY),		"30300"},
	{"FMOffsetZ",			"%f",   STRUCT_OFFSET(ConfigData, FMOffsetZ),		"-130"},
	{"LimOffsetZ",			"%f",   STRUCT_OFFSET(ConfigData, LimOffsetZ),		"30000"},
	{"SpeedX",			"%f",   STRUCT_OFFSET(ConfigData, SpeedX),		"10000"},
	{"SpeedY",			"%f",   STRUCT_OFFSET(ConfigData, SpeedY),		"10000"},
	{"SpeedZ",			"%f",   STRUCT_OFFSET(ConfigData, SpeedZ),		"1000"},
	{"AccX",			"%f",   STRUCT_OFFSET(ConfigData, AccX),		"10000"},
	{"AccY",			"%f",   STRUCT_OFFSET(ConfigData, AccY),		"10000"},
	{"AccZ",			"%f",   STRUCT_OFFSET(ConfigData, AccZ),		"1000"},
	{"LightLevel",		"%d",   STRUCT_OFFSET(ConfigData, LightLevel), "32767"},
	{"LiftCorners",				"%d",   STRUCT_OFFSET(ConfigData, LiftCorners),			"1"},
	{"ComPort",		"%d",   STRUCT_OFFSET(ConfigData, ComPort), "2"}

	

	};

CPlateChangerClass::CPlateChangerClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	strcpy(Slots[0].Name, "Stage");
//	strcpy(Slots[1].Name, "SheetMap");
	strcpy(Slots[1].Name, "FrameGrabber");
	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
		};


	Name[0] = 0;
	HStatusChangeEvent = 0;
	pMonitor = 0;
	HMonitorMutex = 0;
	HRun = 0;
	HTerminate = 0;
	pRefreshThread = 0;
	pThread = 0;

//	for(int j=0;j<MAX_NUMBER_OF_PLATES;j++) EmulsionIsInBank[j]=-1; //-1 - not known


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
	//Here we assign powerup states

//	DAQmxSetDigitalPowerUpStates ("Dev1", "Dev1/port0/line0:7", DAQmx_Val_Low, NULL);
//	DAQmxSetDigitalPowerUpStates ("Dev1", "Dev1/port1/line0:7", DAQmx_Val_Low, NULL);

	CWnd OwnerWnd;
	OwnerWnd.Attach(::GetTopWindow(0));
	pMonitor = new CMonitor(&C, &HMonitorMutex, &HRun, this, Enabler);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);
//	pMonitor->pSt=iSt;

	OwnerWnd.Detach();
	CRect WndRect;
	CRect WorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
	pMonitor->GetWindowRect(&WndRect);
	pMonitor->SetWindowPos(0, WorkArea.right - WndRect.Width(), 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
	pMonitor->EnableManualControl(false);
//	pMonitor->ShowWindow(SW_HIDE);
//	pMonitor->EnableWindow(FALSE);
	pMonitor->ShowWindow(SW_SHOW);
	pMonitor->EnableWindow(TRUE);
	pRefreshThread = AfxBeginThread((AFX_THREADPROC)RefreshThreadHook, (void *)this);
	pRefreshThread->m_bAutoDelete = FALSE;
//	pThread = AfxBeginThread((AFX_THREADPROC)ThreadHook, (void *)this);
//	pThread->m_bAutoDelete = FALSE;

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
	if (pThread)
	{
		WaitForSingleObject(pThread->m_hThread, INFINITE);
		delete pThread;
		pThread = 0;
		};
	if (pMonitor) 
	{
		WaitForSingleObject(HMonitorMutex, INFINITE);
		pMonitor->OnReset();
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
     SetStage();
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

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CPlateChangerClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
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
	try
	{
		if (Slots[0].pUnknown)
		{
			IStage *iSt;
			if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK) iSt->Release();
			else throw 0;
			}
		else throw 0;
		}
	catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
		return S_OK;
		};

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


STDMETHODIMP CPlateChangerClass::LoadPlate(Identifier id, BYTE* pData)
{
	int res;
//	AfxMessageBox("LoadPlate is called..");
try {
	if (!pMonitor) return 0;
	SetStage();
	pMonitor->OnInitialize2();
	//if (!pMonitor->InitDone) pMonitor->OnInitialize2();
	if (!pMonitor->ReadyToScan) return 0;
	if (!pMonitor->IsStageHomed) return 0;
//	ISheetMap2 *iSM;
	IFrameGrabber *iFG;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
//			IVisionProcessor *iVP;
	IAutomaticLightControl *iLC; //now try to set light

//		if (Slots[1].pUnknown)
//		{ if (Slots[1].pUnknown->QueryInterface(IID_ISheetMap2, (void **)&iSM) != S_OK) iSM=0; }
//		else iSM=0; //No sheet map is connected

		if (Slots[0].pUnknown)
//		{ if (Slots[0].pUnknown->QueryInterface(IID_IStage2, (void **)&iSt) != S_OK) iSt=0;	}		
		{ if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) != S_OK) iSt=0;	}		
		else iSt=0; //No stage connected
 
		if (Slots[1].pUnknown)
		{
			if (Slots[1].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG) != S_OK) iFG->Release();
			if (Slots[1].pUnknown->QueryInterface(IID_IAutomaticLightControl, (void **)&iLC) != S_OK) iLC->Release();
			}
		else { iFG=0; iLC=0;}


   	res=pMonitor->LoadPlate(id);

	//TODO: Set Zposition and light
	if(res==1) { 

//        if(iSt) iSt->PosMove(2,0,C.SpeedZ,C.AccZ);
	iStOb->EnableMonitor(false);
		if (iLC) iLC->SetLightLevel();
		else iSt->SetLight(C.LightLevel);

		Sleep(C.BubbleTimeout);  
	iStOb->EnableMonitor(true);
/*        if(!iSM) return 0; 
		if(iSM->Init(0, 0, 0)!=S_OK) return 0; //Scan fiducial marks if new plate is loaded
        if(iSt) iSt->PosMove(2,0,C.SpeedZ,C.AccZ);
		BOOL SMValid;
		iSM->IsValid(&SMValid);
		if(!SMValid) return 0; //no valid sheet map is scanned
*/		Sleep(100);
		return 1; 
	} //is plate is loaded from the bank
	else if(res==2) { 
			if (iLC) iLC->SetLightLevel();
		else iSt->SetLight(C.LightLevel);
//	        if(iSt) iSt->PosMove(2,0,C.SpeedZ,C.AccZ);
				Sleep(100);
  /*              if(!iSM) return 0; 
				BOOL SMValid;
				iSM->IsValid(&SMValid);
				if(!SMValid) return 0; //no valid sheet map is scanned
	*/			return 2; //if plate was already on the stage
				}
	else return 0; //Failed///	
}
catch (int ex)
{
	char mess[128];
	sprintf(mess,"Exception caught: %d",ex);
	 AfxMessageBox(mess);
	 return 0;
}

}


STDMETHODIMP CPlateChangerClass::UnloadPlate()
{
	int res;
//	AfxMessageBox("UnloadPlate is called..");
	if (!pMonitor) return S_FALSE;
    SetStage();
	pMonitor->OnInitialize2();
   // if (!pMonitor->InitDone) pMonitor->OnInitialize2();
	if (!pMonitor->ReadyToScan) return S_FALSE;
	if (!pMonitor->IsStageHomed) return S_FALSE;
	res=pMonitor->UnloadPlate();
	if(res>=0) return true; else return false;	

}


// Non-exported methods

UINT CPlateChangerClass::RefreshThreadHook(void *pOwner)
{
	return ((CPlateChangerClass *)pOwner)->RefreshThread();
}

UINT CPlateChangerClass::ThreadHook(void *pOwner)
{
	return ((CPlateChangerClass *)pOwner)->Thread();
}

UINT CPlateChangerClass::Thread()
{
 return 0;
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


void CPlateChangerClass::SetStage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	iSt=(IStage2*)p;
		if (Slots[0].pUnknown)
		{
			if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) != S_OK) iSt=0;
			}
		else iSt=0;

//	pMonitor->pSt=(IStage2*)p;
	pMonitor->pSt=iSt;
//	return true;
}

//DEL int CPlateChangerClass::ReadLabel(char *labext)
//DEL {
//DEL  	ISheetMap2 *iSM;
//DEL 	int label;
//DEL 		if (Slots[1].pUnknown)
//DEL 		{ if (Slots[1].pUnknown->QueryInterface(IID_ISheetMap2, (void **)&iSM) != S_OK) iSM=0; }
//DEL 		else iSM=0; //No sheet map is connected
//DEL if(iSM==0) return 0;
//DEL return iSM->ReadLabels((BYTE*)labext,0,0,&label);
//DEL }
