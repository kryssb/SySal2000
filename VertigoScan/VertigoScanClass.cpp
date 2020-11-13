// VertigoScanClass.cpp : Implementation of CVertigoScanClass

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "stdafx.h"
#include "VertigoScan.h"
#include "VertigoScanClass.h"
#include "ums.h"
#include "..\Common\Fitter.h"
#include "..\Common\FrameGrabber.h"
#include "..\Common\IO.h"
#include "..\Common\Objective.h"
#include "..\Common\RemoteControlServer.h"
#include "..\Common\SheetMap.h"
#include "..\Common\Stage.h"
#include "..\Common\Tracker.h"
#include "..\Common\VisionProcessor2.h"
#include "EditConfig.h"
#include "Globals.h"
#include "MainSwitch.h"
#include "TestAndConfig.h"
#include "ManualChecks.h"
#include "MapInitString.h"
#include "ScanStart.h"
#include "Scan.h"
#include "..\Common\SySalObject2Structs.h"

const int ConfigDataN = 32;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataName[ConfigDataN] =
{
	{"FramesPerSecond",			"%f",   STRUCT_OFFSET(ConfigData, FramesPerSecond),			"60."},
	{"TopClusterParam",			"%d",   STRUCT_OFFSET(ConfigData, TopClusterParam),			"900"},
	{"TopClusterThreshold",		"%d",   STRUCT_OFFSET(ConfigData, TopClusterThreshold),		"1200"},
	{"BottomClusterParam",		"%d",   STRUCT_OFFSET(ConfigData, BottomClusterParam),		"900"},
	{"BottomClusterThreshold",	"%d",   STRUCT_OFFSET(ConfigData, BottomClusterThreshold),	"1200"},
	{"LightLevel",				"%d",   STRUCT_OFFSET(ConfigData, LightLevel),				"10000"},
	{"StageDelay",				"%d",   STRUCT_OFFSET(ConfigData, StageDelay),				"0"},
	{"LimiterDelay",			"%d",   STRUCT_OFFSET(ConfigData, LimiterDelay),			"3000"},
	{"VLayers",					"%d",   STRUCT_OFFSET(ConfigData, VLayers),					"12"},
	{"VStep",					"%f",   STRUCT_OFFSET(ConfigData, VStep),					"20."},
	{"VSpeed",					"%f",   STRUCT_OFFSET(ConfigData, VSpeed),					"50000."},
	{"VAcc",					"%f",   STRUCT_OFFSET(ConfigData, VAcc),					"100000."},
	{"VTol",					"%f",   STRUCT_OFFSET(ConfigData, VTol),					"2."},
	{"VBaseSpeed",				"%f",   STRUCT_OFFSET(ConfigData, VBaseSpeed),				"50000."},
	{"XStep",					"%f",   STRUCT_OFFSET(ConfigData, XStep),					"330."},
	{"YStep",					"%f",   STRUCT_OFFSET(ConfigData, YStep),					"330."},
	{"HSpeed",					"%f",   STRUCT_OFFSET(ConfigData, HSpeed),					"50000."},
	{"HAcc",					"%f",   STRUCT_OFFSET(ConfigData, HAcc),					"100000."},
	{"HTol",					"%f",   STRUCT_OFFSET(ConfigData, HTol),					"5."},
	{"MaxTracks",				"%d",   STRUCT_OFFSET(ConfigData, MaxTracks),				"100000"},
	{"MaxClusters",				"%d",   STRUCT_OFFSET(ConfigData, MaxClusters),				"10000"},
	{"BaseThickness",			"%f",   STRUCT_OFFSET(ConfigData, BaseThickness),			"200."},
	{"FocusTolerance",			"%f",   STRUCT_OFFSET(ConfigData, FocusTolerance),			"200."},
	{"ThicknessTolerance",		"%f",   STRUCT_OFFSET(ConfigData, ThicknessTolerance),		"50."},
	{"MinValidLayers",			"%d",   STRUCT_OFFSET(ConfigData, MinValidLayers),			"8"},
	{"FocusClusterParam",		"%d",   STRUCT_OFFSET(ConfigData, FocusClusterParam),		"900"},
	{"FocusLockModel",			"%d",   STRUCT_OFFSET(ConfigData, FocusLockModel),			"0"},
	{"XFields",					"%d",   STRUCT_OFFSET(ConfigData, XFields),					"11"},
	{"YFields",					"%d",   STRUCT_OFFSET(ConfigData, YFields),					"11"},
	{"RefocusFields",			"%d",   STRUCT_OFFSET(ConfigData, RefocusFields),			"9"},
	{"ScanningScheme",			"%d",   STRUCT_OFFSET(ConfigData, ScanningScheme),			"0"},
	{"Shrinkage",				"%f",   STRUCT_OFFSET(ConfigData, Shrinkage),				"1.2"}
	};

/////////////////////////////////////////////////////////////////////////////
// CVertigoScanClass
CVertigoScanClass::CVertigoScanClass()
{
	CMI.Context = 0;
	CMI.pSaveConfig = 0;
	CMI.pLoadConfig = 0;
	iSMCOb = 0;
	Name[0] = 0;
	HStatusChangeEvent = 0;		
	strcpy(Slots[0].Name, "Data I/O");
	strcpy(Slots[1].Name, "Objective");
	strcpy(Slots[2].Name, "Tracker #1 (Top)");
	strcpy(Slots[3].Name, "Track Fitter #1 (Top)");
	strcpy(Slots[4].Name, "Tracker #2 (Bottom)");
	strcpy(Slots[5].Name, "Track Fitter #2 (Bottom)");
	strcpy(Slots[6].Name, "Stage");
	strcpy(Slots[7].Name, "Frame Grabber");
	strcpy(Slots[8].Name, "Sheet Map");
	strcpy(Slots[9].Name, "Remote Control Server");
	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
		};
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	HStatusMutex = CreateMutex(0, FALSE, 0);
	pAsyncExec = 0;
	m_hDefWnd = 0;

	{
		SySalConfig VoidConfig = {"", 0, 0};
		int i;
		for (i = 0; i < ConfigDataN; i++)
			GetData(ConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
		};

}


CVertigoScanClass::~CVertigoScanClass()
{
	CloseHandle(HStatusMutex);
	if (iSMCOb) iSMCOb->Release();
}


STDMETHODIMP CVertigoScanClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < ConfigDataN) && (GetData(ConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < ConfigDataN) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::GetConfig(SySalConfig *pConfig)
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
		else if (!strcmp(ConfigDataName[i].Format, "%f"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%g", *(float *)((char *)&C + ConfigDataName[i].Position));		
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, ((char *)&C + ConfigDataName[i].Position));		
		};
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	HRESULT HRes = ::EditConfig(pConfig, &Owner);
	Owner.Detach();
	return HRes;
}

STDMETHODIMP CVertigoScanClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CVertigoScanClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
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

STDMETHODIMP CVertigoScanClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Vertigo Scan", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::SyncExec()
{
	// TODO: Add your implementation code here

//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	MessageBox(AfxGetMainWnd()->m_hWnd, "Simple Sync Exec Example!!!", "Cuckoo!", MB_OK);
	return S_OK;
}


STDMETHODIMP CVertigoScanClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::AsyncWait()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CVertigoScanClass::AsyncPause()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		if (iSMCOb) iSMCOb->AsyncPause();
		else
		{
			if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
			else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
			};
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::AsyncStop()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		if (iSMCOb) iSMCOb->AsyncStop();
		else
		{
			if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
			else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
			};
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::AsyncResume()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{	
		if (iSMCOb) iSMCOb->AsyncResume();
		else
		{
			if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
			else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
			};
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	try
	{
		if (Slots[0].pUnknown)
		{
			ISySalDataIO *iIO;
			if (Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO) == S_OK) iIO->Release();
			else throw 0;
			};
		if (Slots[1].pUnknown)
		{
			IObjective *iOb;
			if (Slots[1].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb) == S_OK) iOb->Release();
			else throw 1;
			} 
		else throw 1;
		if (Slots[2].pUnknown)
		{
			ITracker *iTk1;
			if (Slots[2].pUnknown->QueryInterface(IID_ITracker, (void **)&iTk1) == S_OK) iTk1->Release();
			else throw 2;
			}
		else throw 2;
		if (Slots[3].pUnknown)
		{
			ITrackFitter *iFt1;
			if (Slots[3].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt1) == S_OK) iFt1->Release();
			else throw 3;
			}
		else throw 3;
		if (Slots[4].pUnknown)
		{
			ITracker *iTk2;
			if (Slots[4].pUnknown->QueryInterface(IID_ITracker, (void **)&iTk2) == S_OK) iTk2->Release();
			else throw 4;
			}
		else throw 4;
		if (Slots[5].pUnknown)
		{
			ITrackFitter *iFt2;
			if (Slots[5].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt2) == S_OK) iFt2->Release();
			else throw 5;
			}
		else throw 5;
		if (Slots[6].pUnknown)
		{
			IStage *iSt;
			if (Slots[6].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK) iSt->Release();
			else throw 6;
			}
		else throw 6;
		if (Slots[7].pUnknown)
		{
			IFrameGrabber *iFG;
			IVisionProcessor *iVP;
			if (Slots[7].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG) == S_OK) iFG->Release();
			else throw 7;
			if (Slots[7].pUnknown->QueryInterface(IID_IVisionProcessor, (void **)&iVP) == S_OK) iVP->Release();
			else throw 7;
			}
		else throw 7;
		if (Slots[8].pUnknown)
		{
			ISheetMap *iSM;
			if (Slots[8].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iSM) == S_OK) iSM->Release();
			else throw 8;
			}
		else throw 8;
		if (Slots[9].pUnknown)
		{
			IRemoteControlServer *iRCS;
			if (Slots[9].pUnknown->QueryInterface(IID_IRemoteControlServer, (void **)&iRCS) == S_OK) iRCS->Release();
			else throw 9;
			};
		}
	catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
		return S_OK;
		};

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

// ISySalObject2
STDMETHODIMP CVertigoScanClass::SetConfigManagerInterface(ConfigManagerInterface *pCMI)
{
	CMI = *pCMI;
	return S_OK;
}

STDMETHODIMP CVertigoScanClass::GetCLSID(CLSID *pCLSID)
{
	*pCLSID = CLSID_VertigoScan;
	return S_OK;	
}

UINT WINAPI CVertigoScanClass::AsyncExecHook(void *pOwner)
{
	return ((CVertigoScanClass *)pOwner)->AsyncExec();
}

UINT CVertigoScanClass::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	ISySalDataIO *iIO = 0;
	IObjective *iOb = 0;
	ITracker *iTk1 = 0, *iTk2 = 0;
	ITrackFitter *iFt1 = 0, *iFt2 = 0;
	IStage *iSt = 0;
	IFrameGrabber *iFG = 0;
	IVisionProcessor *iVP = 0;
	ISheetMap *iSM = 0;
	IRemoteControlServer *iRCS = 0;

	if (Slots[0].pUnknown) Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO);
	if (Slots[1].pUnknown) Slots[1].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb);
	if (Slots[2].pUnknown) Slots[2].pUnknown->QueryInterface(IID_ITracker, (void **)&iTk1);
	if (Slots[3].pUnknown) Slots[3].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt1);
	if (Slots[4].pUnknown) Slots[4].pUnknown->QueryInterface(IID_ITracker, (void **)&iTk2);
	else iTk2 = iTk1;
	if (Slots[5].pUnknown) Slots[5].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt2);
	else iFt2 = iFt1;
	if (Slots[6].pUnknown) Slots[6].pUnknown->QueryInterface(IID_IStage, (void **)&iSt);
	if (Slots[7].pUnknown) Slots[7].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG);
	if (Slots[8].pUnknown) Slots[8].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iSM);
	if (Slots[9].pUnknown) Slots[9].pUnknown->QueryInterface(IID_IRemoteControlServer, (void **)&iRCS);

	if (iFG) iFG->QueryInterface(IID_IVisionProcessor, (void **)&iVP);

	UINT Selection = MS_SEL_EXIT;
	do
	{
		CMainSwitch MyDlg(&m_hDefWnd);
		BOOL Valid = FALSE; 
		iSM->IsValid(&Valid);
		MyDlg.m_EnableTest = MyDlg.m_EnableScan = MyDlg.m_EnableManualChecks = Valid;
		if (MyDlg.DoModal() == (UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) Selection = MS_SEL_EXIT;
		else Selection = MyDlg.m_Selection;
		m_hDefWnd = 0;
		switch (Selection)
		{
			case MS_SEL_SCAN:		
									{
										CScanStart ScanStart;
										if (ScanStart.DoModal() == IDOK)
										{
											Identifier Id;
											bool *pResume = 0;
											if (ScanStart.m_NewBatch)
											{
												if (ScanStart.m_MinX >= ScanStart.m_MaxX || ScanStart.m_MinY >= ScanStart.m_MaxY)
												{
													MessageBox(0, "Null area selected.\r\nScanning aborted.", "Input Error", MB_ICONERROR | MB_OK);
													break;
													};
												Id.Part[0] = ScanStart.m_ID1;
												Id.Part[1] = ScanStart.m_ID2;
												Id.Part[2] = ScanStart.m_ID3;
												Id.Part[3] = ScanStart.m_ID4;
												}
											else
											{


												UINT ExtErrInfo;
												IO_VS_Catalog *pCat = 0;												
												int RecCount, i;
												if (iIO->Read(NULL, (BYTE *)(&pCat), &ExtErrInfo, (UCHAR *)ScanStart.m_Catalog.GetBuffer(1)) != S_OK)
												{
													ScanStart.m_Catalog.ReleaseBuffer();
													MessageBox(0, "Can't resume from catalog.\r\nScanning aborted.", "Input Error", MB_ICONERROR | MB_OK);
													break;
													};
												ScanStart.m_Catalog.ReleaseBuffer();

												if (ScanStart.m_RestoreConfigs)
												{
													try
													{
														if (pCat->Config.CountOfConfigs != (NUMBER_OF_SLOTS + 1)) throw 1;
														ISySalObject *iOb = 0;
														for (i = 0; i < pCat->Config.CountOfConfigs; i++)
														{					
															iOb = 0;
															char ClassName[SYSAL_MAX_CONN_NAME_LEN + 1];
															if (i == 0) 
															{
																GetClassName(ClassName);
																iOb = (ISySalObject *)this;
																iOb->AddRef();
																}
															else 
															{															
																if (Slots[i - 1].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iOb) != S_OK) throw 2;
																if (iOb->GetClassName(ClassName) != S_OK) throw 3;
																};
															if (strcmp(ClassName, pCat->Config.pConfigs[i].ClassName)) throw 4;
															if (iOb->SetConfig(&pCat->Config.pConfigs[i].Config) != S_OK) throw 5;
															iOb->Release();
															iOb = 0;
															};
														}
													catch (...)
													{
														if (iOb) iOb->Release();
														CoTaskMemFree(pCat);
														MessageBox(0, "Configuration cannot be restored.\r\nScanning aborted.\r\nExit execution and apply configuration again.", "Input Error", MB_ICONERROR | MB_OK);
														break;
														};
													};

												Id = pCat->Hdr.ID;
												ScanStart.m_MinX = pCat->Area.XMin;
												ScanStart.m_MinY = pCat->Area.YMin;
												ScanStart.m_MaxX = pCat->Area.XMax;
												ScanStart.m_MaxY = pCat->Area.YMax;												

												pResume = (bool *)malloc(sizeof(bool) * pCat->Area.Fragments);
												char *temp = (char *)malloc(sizeof(char) * (ScanStart.m_Catalog.GetLength() + 14));
												strcpy(temp, ScanStart.m_Catalog);
												char *dotpos = strrchr(temp, '.');

												if (dotpos == temp) dotpos = temp + ScanStart.m_Catalog.GetLength();
												else if (dotpos - temp > 1) dotpos--;												
												for (i = RecCount = 0; i < pCat->Area.Fragments; i++)
												{
													HANDLE HTest = INVALID_HANDLE_VALUE;
													WIN32_FIND_DATA FD;
													sprintf(dotpos, "c.%08X", i);
													if ((HTest = FindFirstFile(temp, &FD)) != INVALID_HANDLE_VALUE)
													{
														pResume[i] = false;
														FindClose(HTest);
														}
													else 
													{
														pResume[i] = true;
														RecCount++;
														};
													};
												CString TempMsg;
												TempMsg.Format("Resuming %d fragments out of %d.", RecCount, pCat->Area.Fragments);
												MessageBox(0, TempMsg, "Fragment Recovery", MB_ICONINFORMATION | MB_OK);
												if (temp) free(temp);
												CoTaskMemFree(pCat);
												};


											CScan Scan(&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, C, 
												Id, ScanStart.m_MinX, ScanStart.m_MaxX, ScanStart.m_MinY, ScanStart.m_MaxY, 0, pResume);

											if (pResume)
											{
												free(pResume);
												pResume = 0;
												};

											if (Scan.DoModal() == 
												(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
													Selection = MS_SEL_EXIT;
											m_hDefWnd = 0;
											};
										};
									break;

			case MS_SEL_TESTCONFIG:
									{
										CTestAndConfig TestAndConfig(&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, &CMI, iRCS, C);
										if (TestAndConfig.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_MANUALCHECKS:
									{
										CManualChecks ManualChecks(&m_hDefWnd, iFG, iSM, iSt, iOb, C);
										if (ManualChecks.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_INITMAP:
									{
										WaitForSingleObject(HStatusMutex, INFINITE);
										CMapInitString MyDlg;
										if (MyDlg.DoModal() == IDOK)
										{
											iSM->QueryInterface(IID_ISySalObject, (void **)&iSMCOb);
											ReleaseMutex(HStatusMutex);	
											HRESULT HRes = iSM->Init((BYTE *)MyDlg.m_InitString.GetBuffer(1), 0, (HSySalHANDLE)HStatusChangeEvent);
											MyDlg.m_InitString.ReleaseBuffer();							
											WaitForSingleObject(HStatusMutex, INFINITE);
											iSMCOb->Release();
											iSMCOb = 0;
											ReleaseMutex(HStatusMutex);
											if (HRes != S_OK) 
											{
												if (HRes == E_ABORT) Selection = MS_SEL_EXIT;
												else MessageBox(0, "Map Initialization failed!", "Initialization Error", MB_ICONERROR | MB_OK);
												};
											}
										else ReleaseMutex(HStatusMutex);

										};
									break;
			};
		}
	while (Selection != MS_SEL_EXIT);

	if (iRCS) iRCS->Release();
	if (iSM) iSM->Release();
	if (iVP) iVP->Release();
	if (iFG) iFG->Release();
	if (iSt) iSt->Release();
	if (iFt2) iFt2->Release();
	if (iTk2) iTk2->Release();
	if (iFt1) iFt1->Release();
	if (iTk1) iTk1->Release();
	if (iOb) iOb->Release();
	if (iIO) iIO->Release();
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	pAsyncExec = 0;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return 0;
}

