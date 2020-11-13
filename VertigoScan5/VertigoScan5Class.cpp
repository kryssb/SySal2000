// VertigoScan5Class.cpp : Implementation of CVertigoScan5Class

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "stdafx.h"
#include "VertigoScan5.h"
#include "VertigoScan5Class.h"
#include "ums.h"
#include "Fitter.h"
#include "FrameGrabber.h"
#include "IO.h"
#include "Objective.h"
#include "RemoteControlServer.h"
#include "SheetMap.h"
#include "Stage.h"
#include "Tracker.h"
#include "VisionProcessor4.h"
#include "EditConfig.h"
#include "Globals.h"
#include "MainSwitch.h"
#include "TestAndConfig.h"
#include "ManualChecks.h"
#include "MapInitString.h"
#include "ScanStart.h"
#include "Scan.h"
#include "..\Common\SySalObject2Structs.h"
#include "IScanServer.h"
#include "RemoteScan.h"
#include "PlateChanger.h"


//#define DUMPTIME(op) { FILE *ftime = fopen("c:\\acq\\time.txt", "a+t"); fprintf(ftime, "%d %d\n", op, GetTickCount()); fclose(ftime); }
#define DUMPTIME(op)

const int ConfigDataN = 42;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataName[ConfigDataN] =
{
	{"FramesPerSecond",			"%f",   STRUCT_OFFSET(ConfigData, FramesPerSecond),			"60."},
	{"TopClusterParam",			"%d",   STRUCT_OFFSET(ConfigData, TopClusterParam),			"900"},
	{"TopClusterThreshold",		"%d",   STRUCT_OFFSET(ConfigData, TopClusterThreshold),		"1200"},
	{"TopExpectedClusters",		"%d",   STRUCT_OFFSET(ConfigData, TopExpectedClusters),		"2200"},
	{"TopClustersFluctuation",	"%d",   STRUCT_OFFSET(ConfigData, TopClustersFluctuation),	"100"},
	{"TopClustersMinArea",		"%d",   STRUCT_OFFSET(ConfigData, TopClustersMinArea),		"4"},
	{"BottomClusterParam",		"%d",   STRUCT_OFFSET(ConfigData, BottomClusterParam),		"900"},
	{"BottomClusterThreshold",	"%d",   STRUCT_OFFSET(ConfigData, BottomClusterThreshold),	"1200"},
	{"BottomExpectedClusters",	"%d",   STRUCT_OFFSET(ConfigData, BottomExpectedClusters),	"2200"},
	{"BottomClustersFluctuation","%d",   STRUCT_OFFSET(ConfigData, BottomClustersFluctuation),	"100"},
	{"BottomClustersMinArea",	"%d",   STRUCT_OFFSET(ConfigData, BottomClustersMinArea),	"4"},
	{"LightLevel",				"%d",   STRUCT_OFFSET(ConfigData, LightLevel),				"10000"},	
	{"LimiterDelay",			"%d",   STRUCT_OFFSET(ConfigData, LimiterDelay),			"3000"},
	{"VLayers",					"%d",   STRUCT_OFFSET(ConfigData, VLayers),					"12"},
	{"VInactiveLayers",			"%d",   STRUCT_OFFSET(ConfigData, VInactiveLayers),			"0"},
	{"TopStep",					"%f",   STRUCT_OFFSET(ConfigData, TopStep),					"40."},
	{"BottomStep",				"%f",   STRUCT_OFFSET(ConfigData, BottomStep),				"45."},
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
	{"SurfaceAdjustment",		"%f",   STRUCT_OFFSET(ConfigData, SurfaceAdjustment),		"10."},
	{"ThicknessTolerance",		"%f",   STRUCT_OFFSET(ConfigData, ThicknessTolerance),		"50."},
	{"MinValidLayers",			"%d",   STRUCT_OFFSET(ConfigData, MinValidLayers),			"10"},
	{"FocusLockModel",			"%d",   STRUCT_OFFSET(ConfigData, FocusLockModel),			"0"},
	{"XFields",					"%d",   STRUCT_OFFSET(ConfigData, TemplateXFields),			"11"},
	{"YFields",					"%d",   STRUCT_OFFSET(ConfigData, TemplateYFields),			"11"},
	{"ZSampleInterval",			"%d",   STRUCT_OFFSET(ConfigData, ZSampleInterval),			"10"},
	{"FocusZSampleInterval",	"%d",   STRUCT_OFFSET(ConfigData, FocusZSampleInterval),	"10"},
	{"ScanningScheme",			"%d",   STRUCT_OFFSET(ConfigData, ScanningScheme),			"0"},
	{"Shrinkage",				"%f",   STRUCT_OFFSET(ConfigData, Shrinkage),				"1.2"},
	{"ZScanDuration",			"%d",   STRUCT_OFFSET(ConfigData, ZScanDuration),			"450"},
	{"XYZMotionDuration",		"%d",   STRUCT_OFFSET(ConfigData, XYZMotionDuration),		"120"}
	};

/////////////////////////////////////////////////////////////////////////////
// CVertigoScan5Class
CVertigoScan5Class::CVertigoScan5Class()
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
	strcpy(Slots[10].Name, "Scan Server");
	strcpy(Slots[11].Name, "Plate Changer");
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


CVertigoScan5Class::~CVertigoScan5Class()
{
	CloseHandle(HStatusMutex);
	if (iSMCOb) iSMCOb->Release();
}


STDMETHODIMP CVertigoScan5Class::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < ConfigDataN) && (GetData(ConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < ConfigDataN) return S_FALSE;
	QueryDataInfo VStepQDI = {"VStep", "%f", 0, "-1"};
	float vstep = -1.0;
	GetData(VStepQDI, &vstep, pConfig->pItems, pConfig->CountOfItems);
	if (vstep > 0)
		C.TopStep = C.BottomStep = vstep;
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::GetConfig(SySalConfig *pConfig)
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

STDMETHODIMP CVertigoScan5Class::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd Owner;
	Owner.Attach((HWND)hWnd);

	IStage2 *iSt = 0;
	if (Slots[6].pUnknown)
		Slots[6].pUnknown->QueryInterface(IID_IStage2, (void **)&iSt);
	HRESULT HRes = ::EditConfig(iSt, pConfig, &Owner);
	if (iSt) iSt->Release();
	Owner.Detach();
	return HRes;
}

STDMETHODIMP CVertigoScan5Class::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CVertigoScan5Class::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CVertigoScan5Class::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Vertigo Scan 5.0", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::SyncExec()
{
	// TODO: Add your implementation code here

//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	MessageBox(AfxGetMainWnd()->m_hWnd, "Simple Sync Exec Example!!!", "Cuckoo!", MB_OK);
	return S_OK;
}


STDMETHODIMP CVertigoScan5Class::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	WaitForSingleObject(HStatusMutex, INFINITE);
	ShouldStop = false;
	ReleaseMutex(HStatusMutex);
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::AsyncWait()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CVertigoScan5Class::AsyncPause()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		ShouldStop = true;
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

STDMETHODIMP CVertigoScan5Class::AsyncStop()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		ShouldStop = true;
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

STDMETHODIMP CVertigoScan5Class::AsyncResume()
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

STDMETHODIMP CVertigoScan5Class::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	try
	{
		if (Slots[0].pUnknown)
		{
			ISySalDataIO2 *iIO;
			if (Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO2, (void **)&iIO) == S_OK) iIO->Release();
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
			ITracker3 *iTk1;
			if (Slots[2].pUnknown->QueryInterface(IID_ITracker3, (void **)&iTk1) == S_OK) iTk1->Release();
			else throw 2;
			}
		else throw 2;
		if (Slots[3].pUnknown)
		{
			ITrackFitter3 *iFt1;
			if (Slots[3].pUnknown->QueryInterface(IID_ITrackFitter3, (void **)&iFt1) == S_OK) iFt1->Release();
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
			IStage2 *iSt;
			if (Slots[6].pUnknown->QueryInterface(IID_IStage2, (void **)&iSt) == S_OK) iSt->Release();
			else throw 6;
			}
		else throw 6;
		if (Slots[7].pUnknown)
		{
			IFrameGrabber *iFG;
			IVisionProcessor *iVP;
			if (Slots[7].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG) == S_OK) iFG->Release();
			else throw 7;
			if (Slots[7].pUnknown->QueryInterface(IID_IVisionProcessor3, (void **)&iVP) == S_OK) iVP->Release();
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
		if (Slots[10].pUnknown)
		{
			IScanServer *iSS;
			if (Slots[10].pUnknown->QueryInterface(IID_IScanServer, (void **)&iSS) == S_OK) iSS->Release();
			else throw 10;
			};
		if (Slots[11].pUnknown)
		{
			IPlateChanger *iPC;
			if (Slots[11].pUnknown->QueryInterface(IID_IPlateChanger, (void **)&iPC) == S_OK) iPC->Release();
			else throw 11;
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
STDMETHODIMP CVertigoScan5Class::SetConfigManagerInterface(ConfigManagerInterface *pCMI)
{
	CMI = *pCMI;
	return S_OK;
}

STDMETHODIMP CVertigoScan5Class::GetCLSID(CLSID *pCLSID)
{
	*pCLSID = CLSID_VertigoScan5;
	return S_OK;	
}

UINT WINAPI CVertigoScan5Class::AsyncExecHook(void *pOwner)
{
	return ((CVertigoScan5Class *)pOwner)->AsyncExec();
}

UINT CVertigoScan5Class::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	ISySalDataIO2 *iIO = 0;
	IObjective *iOb = 0;
	ITracker3 *iTk1 = 0, *iTk2 = 0;
	ITrackFitter3 *iFt1 = 0, *iFt2 = 0;
	IStage2 *iSt = 0;
	IFrameGrabber *iFG = 0;
	IVisionProcessor3 *iVP = 0;
	ISheetMap *iSM = 0;
	IRemoteControlServer *iRCS = 0;
	IScanServer *iSS = 0;
    IPlateChanger *iPC = 0;

	if (Slots[0].pUnknown) Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO2, (void **)&iIO);
	if (Slots[1].pUnknown) Slots[1].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb);
	if (Slots[2].pUnknown) Slots[2].pUnknown->QueryInterface(IID_ITracker3, (void **)&iTk1);
	if (Slots[3].pUnknown) Slots[3].pUnknown->QueryInterface(IID_ITrackFitter3, (void **)&iFt1);
	if (Slots[4].pUnknown) Slots[4].pUnknown->QueryInterface(IID_ITracker, (void **)&iTk2);
	else iTk2 = iTk1;
	if (Slots[5].pUnknown) Slots[5].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt2);
	else iFt2 = iFt1;
	if (Slots[6].pUnknown) Slots[6].pUnknown->QueryInterface(IID_IStage2, (void **)&iSt);
	if (Slots[7].pUnknown) Slots[7].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG);
	if (Slots[8].pUnknown) Slots[8].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iSM);
	if (Slots[9].pUnknown) Slots[9].pUnknown->QueryInterface(IID_IRemoteControlServer, (void **)&iRCS);
	if (Slots[10].pUnknown) Slots[10].pUnknown->QueryInterface(IID_IScanServer, (void **)&iSS);
	if (Slots[11].pUnknown) Slots[11].pUnknown->QueryInterface(IID_IPlateChanger, (void **)&iPC);

	if (iFG) iFG->QueryInterface(IID_IVisionProcessor3, (void **)&iVP);

	if (iSS)
	{

		if (iSS->Connect() != S_OK) MessageBox(0, "Cannot connect to Remote Scan Server.\nAborting remotely controlled scanning.", "Unknown Error", MB_ICONERROR | MB_OK);
		else
		{
			float AutoZReset = 0.0f;
			bool ZSet = false;
			bool Continue = true;
			bool ReturnValue = false;
			bool TrustZ = false;
			
			CRemoteScan CommDlg(iSS, HStatusMutex, &ShouldStop);
			CScan Scan(&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, C, 0, AutoZReset, TrustZ);

			DUMPTIME(-20);
			while (Continue && (CommDlg.DoModal() == IDOK))
			{
				DUMPTIME(-19);
				switch (CommDlg.M.M.OpCode)
				{
					case SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT:
					case SCANSRV_SCAN_ZONE_START:	
						{
							if (!ZSet)
							{
								ReturnValue = false;
								break;
								};
							
							SetBusyState zmsg;
							zmsg.Size = sizeof(zmsg);
							zmsg.OpCode = SCANSRV_SET_BUSYSTATE;
							zmsg.Busy = true;
							zmsg.ZoneId = CommDlg.M.ZS.Id;
							DUMPTIME(-18);
							iSS->Send((BYTE *)&zmsg);
							DUMPTIME(-17);

//							CScan Scan(&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, C, 
//								CommDlg.M.ZS.Id, CommDlg.M.ZS.MinX, CommDlg.M.ZS.MaxX, CommDlg.M.ZS.MinY, CommDlg.M.ZS.MaxY, 0, 0, CommDlg.M.ZS.OutName, true, AutoZReset, TrustZ);
							if (CommDlg.M.M.OpCode == SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT)															
								Scan.PreloadNext(CommDlg.M.ZSPN.NextMinX, CommDlg.M.ZSPN.NextMinY, CommDlg.M.ZSPN.NextMaxX, CommDlg.M.ZSPN.NextMaxY);
							DUMPTIME(-16);
							
							zmsg.Busy = false;
							iSS->Send((BYTE *)&zmsg);
							DUMPTIME(-15);
							
							//UINT Ret = Scan.DoModal();
							UINT Ret = Scan.ResetAndScan(CommDlg.M.ZS.Id, CommDlg.M.ZS.MinX, CommDlg.M.ZS.MaxX, CommDlg.M.ZS.MinY, CommDlg.M.ZS.MaxY, 0, CommDlg.M.ZS.OutName, TrustZ);
							DUMPTIME(-14);

							Continue = (Ret != (UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE));
							ReturnValue = (Ret == UM_END);
							TrustZ = (Ret == UM_END);
							};
						break;
						
					case SCANSRV_LOAD_PLATE:
						{
							TrustZ = false;
							SetLoadedState pmsg;
							pmsg.Size = sizeof(pmsg);
							pmsg.OpCode = SCANSRV_SET_LOADEDSTATE;
							ReturnValue = pmsg.Loaded = false;			
							if (ExecLoadPlate(&AutoZReset, iSt, iPC, CommDlg.M.LS.Id, CommDlg.M.LS.TextId))
							{
								Scan.SetZAndTrust(TrustZ, AutoZReset);
								WaitForSingleObject(HStatusMutex, INFINITE);
								iSM->QueryInterface(IID_ISySalObject, (void **)&iSMCOb);
								ReleaseMutex(HStatusMutex);	
								HRESULT HRes = iSM->Init((BYTE *)CommDlg.M.LS.MapInitString, 0, (HSySalHANDLE)HStatusChangeEvent);	
								WaitForSingleObject(HStatusMutex, INFINITE);
								iSMCOb->Release();
								iSMCOb = 0;
								ReleaseMutex(HStatusMutex);
								if (HRes == S_OK)
								{
									ReturnValue = pmsg.Loaded = true;
									pmsg.PlateId = CommDlg.M.LS.Id;
									ZSet = true;									
									}
								}
							iSS->Send((BYTE *)&pmsg);							
							};
						break;
						
					case SCANSRV_UNLOAD_PLATE:
						{
							if (ReturnValue = ExecUnloadPlate(iSt,iPC))
							{
								Scan.SetZAndTrust(false, 0.0f);
								SetLoadedState pmsg;
								pmsg.Size = sizeof(pmsg);
								pmsg.OpCode = SCANSRV_SET_LOADEDSTATE;
								pmsg.Loaded = false;
								iSS->Send((BYTE *)&pmsg);
								ZSet = false;
								}
							};
						break;
						
					case SCANSRV_SET_PARAMETER:
						{
							ReturnValue = ExecSetParam(CommDlg.M.SP.ObjName, CommDlg.M.SP.ParamName, CommDlg.M.SP.ParamValue);
							};
						break;
						
					case SCANSRV_SET_CONFIG:
						{
							ReturnValue = false;
							};
						break;
						
					};
				
				CommDlg.M.M.OpCode = ReturnValue ? SCANSRV_OK : SCANSRV_FAILED;
				CommDlg.M.M.Size = sizeof(ScanSrvMessage);
				iSS->Send((BYTE *)&CommDlg.M.M);
				DUMPTIME(-13);
				};
					
			iSS->Disconnect();
			}

		}
	else
	{
		UINT Selection = MS_SEL_EXIT;
		do
		{
			CMainSwitch MyDlg(&m_hDefWnd);
			BOOL Valid = FALSE; 
			iSM->IsValid(&Valid);
			MyDlg.m_EnableTest = MyDlg.m_EnableScan = MyDlg.m_EnableManualChecks = Valid;
			MyDlg.m_EnableRemoteScan = (iSS != 0);
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
				
			case MS_SEL_REMOTESCAN:
				{
					if (iSS->Connect() != S_OK)
					{
						MessageBox(0, "Cannot connect to Remote Scan Server.\nAborting remotely controlled scanning.", "Unknown Error", MB_ICONERROR | MB_OK);
						break;
						};
					float AutoZReset = 0.0f;
					bool ZSet = false;
					bool Continue = true;
					bool ReturnValue = false;
					
					CRemoteScan CommDlg(iSS, HStatusMutex, &ShouldStop);
					while (Continue && (CommDlg.DoModal() == IDOK))
					{
						switch (CommDlg.M.M.OpCode)
						{
							case SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT:
							case SCANSRV_SCAN_ZONE_START:	
								{
									if (!ZSet)
									{
										SetLoadedState pmsg;
										pmsg.Size = sizeof(pmsg);
										pmsg.OpCode = SCANSRV_SET_LOADEDSTATE;
										Identifier Id;
										Id.Part[0] = Id.Part[1] = Id.Part[2] = Id.Part[3] = 0;
										if (ExecLoadPlate(&AutoZReset, iSt, iPC, Id, 0))
										{
											pmsg.Loaded = true;
											pmsg.PlateId = Id;
											ZSet = true;
											}
										else pmsg.Loaded = false;
										iSS->Send((BYTE *)&pmsg);
										};
									
									SetBusyState zmsg;
									zmsg.Size = sizeof(zmsg);
									zmsg.OpCode = SCANSRV_SET_BUSYSTATE;
									zmsg.Busy = true;
									zmsg.ZoneId = CommDlg.M.ZS.Id;
									iSS->Send((BYTE *)&zmsg);
									
									CScan Scan(&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, C, 
										CommDlg.M.ZS.Id, CommDlg.M.ZS.MinX, CommDlg.M.ZS.MaxX, CommDlg.M.ZS.MinY, CommDlg.M.ZS.MaxY, 0, 0, CommDlg.M.ZS.OutName, true, AutoZReset);
									if (CommDlg.M.M.OpCode == SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT)																						
										Scan.PreloadNext(CommDlg.M.ZSPN.NextMinX, CommDlg.M.ZSPN.NextMinY, CommDlg.M.ZSPN.NextMaxX, CommDlg.M.ZSPN.NextMaxY);
									
									zmsg.Busy = false;
									iSS->Send((BYTE *)&zmsg);
									
									UINT Ret = Scan.DoModal();
									Continue = (Ret != (UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE));
									ReturnValue = (Ret == UM_END);
									};
								break;
								
							case SCANSRV_LOAD_PLATE:
								{
									SetLoadedState pmsg;
									pmsg.Size = sizeof(pmsg);
									pmsg.OpCode = SCANSRV_SET_LOADEDSTATE;
									
									if (pmsg.Loaded = ZSet = ReturnValue = ExecLoadPlate(&AutoZReset, iSt, iPC, CommDlg.M.LS.Id, CommDlg.M.LS.TextId))
										pmsg.PlateId = CommDlg.M.LS.Id;
									
									iSS->Send((BYTE *)&pmsg);
									};
								break;
								
							case SCANSRV_UNLOAD_PLATE:
								{
									if (ReturnValue = ExecUnloadPlate(iSt,iPC))
									{
										SetLoadedState pmsg;
										pmsg.Size = sizeof(pmsg);
										pmsg.OpCode = SCANSRV_SET_LOADEDSTATE;
										pmsg.Loaded = false;
										iSS->Send((BYTE *)&pmsg);
										}
									};
								break;
								
							case SCANSRV_SET_PARAMETER:
								{
									ReturnValue = ExecSetParam(CommDlg.M.SP.ObjName, CommDlg.M.SP.ParamName, CommDlg.M.SP.ParamValue);
									};
								break;
								
							case SCANSRV_SET_CONFIG:
								{
									ReturnValue = false;
									};
								break;
								
							};
						
						CommDlg.M.M.OpCode = ReturnValue ? SCANSRV_OK : SCANSRV_FAILED;
						CommDlg.M.M.Size = sizeof(ScanSrvMessage);
						iSS->Send((BYTE *)&CommDlg.M.M);
						};
					
					if (!Continue)
					{
						Selection = MS_SEL_EXIT;
						m_hDefWnd = 0;
						};
					
					iSS->Disconnect();
					}
				break;
			};
		}
		while (Selection != MS_SEL_EXIT);
	}

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


bool CVertigoScan5Class::ExecLoadPlate(float *pAutoZReset, IStage *iSt, IPlateChanger *iPc, Identifier id, char *textid)
{
	ISySalObject *iStOb = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iStOb->EnableMonitor(true);
	static char outtext[4096];
	IStage3 *iSt3 = 0;
	if (iSt->QueryInterface(IID_IStage3, (void **)&iSt3) == S_OK)
	{
		sprintf(outtext, "Please load plate %d/%d/%d/%d - Text Id: %s\r\n\r\n",
			id.Part[0], id.Part[1], id.Part[2], id.Part[3], textid ? textid : "None");
UINT Ret;
//Robot Related
	int LDres=0;
	if(iPc)  //load plate by robot
		{   
		if(!iSt) return false;
		LDres=iPc->LoadPlate(id,(BYTE*)textid);
		if(!LDres) return false;
		Ret=true;
	} else
//End Robot Related

		UINT Ret = MessageBox(0, outtext, "Help Request", MB_ICONINFORMATION | MB_OKCANCEL);
		if (Ret == false) return false;
		if (iSt3->GetZRef((BYTE *)"Glass", pAutoZReset) == S_OK)
		{
			iSt3->Release();
			*pAutoZReset += C.BaseThickness + C.BottomStep;
			iStOb->EnableMonitor(false);
			iStOb->Release();
			return true;				
		}		
	}
	if (iSt3) iSt3->Release();
	sprintf(outtext, "Please load plate %d/%d/%d/%d - Text Id: %s\r\n\r\n"
		"Please place the objective at the top surface of the plastic base.\r\n"
		"This Z position will be used as your hint for focusing for all next scanning tasks in this session.\r\n"
		"Press OK when the objective is at your suggested Z position.",
		id.Part[0], id.Part[1], id.Part[2], id.Part[3], textid ? textid : "None");
	UINT Ret = MessageBox(0, outtext, "Help Request", MB_ICONINFORMATION | MB_OKCANCEL);

	iSt->GetPos(2, pAutoZReset);
	iStOb->EnableMonitor(false);
	iStOb->Release();
	return Ret == IDOK;
}

bool CVertigoScan5Class::ExecUnloadPlate(IStage *iSt, IPlateChanger *iPc)
{
	ISySalObject *iStOb = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iStOb->EnableMonitor(true);

//Robot related
	UINT Ret;
    if(iPc) iPc->UnloadPlate();
	else
//end Robot related
	Ret = MessageBox(0, "Please unload the plate from the stage.", "Help Request", MB_ICONINFORMATION | MB_OKCANCEL);

	iStOb->EnableMonitor(false);
	iStOb->Release();
	return Ret == IDOK;
}

bool CVertigoScan5Class::ExecSetParam(char *objname, char *paramname, char *paramvalue)
{
	int i, j;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		ISySalObject *iOb;
		if (Slots[i].pUnknown && Slots[i].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iOb) == S_OK)
		{
			if (!stricmp(Slots[i].Name, objname))
			{
				SySalConfig T;
				T.CountOfItems = 0;
				T.Name[0] = 0;
				T.pItems = 0;
				iOb->GetConfig(&T);
				for (j = 0; j < T.CountOfItems; j++)
					if (!strnicmp(paramname, T.pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN)) break;
				if (j < T.CountOfItems)
				{
					strncpy(T.pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, paramvalue, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
					iOb->SetConfig(&T);
					}
				if (T.pItems) CoTaskMemFree(T.pItems);
				iOb->Release();
				return j < T.CountOfItems;
				}
			iOb->Release();			
			}
		}
	return false;
}