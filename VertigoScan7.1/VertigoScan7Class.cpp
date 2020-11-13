// VertigoScan7Class.cpp : Implementation of CVertigoScan7Class

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "stdafx.h"
#include "VertigoScan7.h"
#include "VertigoScan7Class.h"
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
#include "PlateChanger2.h"	//GS
#include "PlateQualityDlg.h"
#include "FogInterface.h"
#include "PlateQualityInitDlg.h"
#include "EditMachineDefaults.h"

//#define DUMPTIME(op) { FILE *ftime = fopen("c:\\acq\\time.txt", "a+t"); fprintf(ftime, "%d %d\n", op, GetTickCount()); fclose(ftime); }
#define DUMPTIME(op)

const int ConfigDataN = 47;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataName[ConfigDataN] =
{
	{"FramesPerSecond",			"%f",   STRUCT_OFFSET(ConfigData, FramesPerSecond),			"60.", true},
	{"TopClusterParam",			"%d",   STRUCT_OFFSET(ConfigData, TopClusterParam),			"900", true},
	{"TopClusterThreshold",		"%d",   STRUCT_OFFSET(ConfigData, TopClusterThreshold),		"1200", true},
	{"TopExpectedClusters",		"%d",   STRUCT_OFFSET(ConfigData, TopExpectedClusters),		"2200", true},
	{"TopClustersFluctuation",	"%d",   STRUCT_OFFSET(ConfigData, TopClustersFluctuation),	"100", true},
	{"TopClustersMinArea",		"%d",   STRUCT_OFFSET(ConfigData, TopClustersMinArea),		"4", true},
	{"BottomClusterParam",		"%d",   STRUCT_OFFSET(ConfigData, BottomClusterParam),		"900", true},
	{"BottomClusterThreshold",	"%d",   STRUCT_OFFSET(ConfigData, BottomClusterThreshold),	"1200", true},
	{"BottomExpectedClusters",	"%d",   STRUCT_OFFSET(ConfigData, BottomExpectedClusters),	"2200", true},
	{"BottomClustersFluctuation","%d",   STRUCT_OFFSET(ConfigData, BottomClustersFluctuation),	"100", true},
	{"BottomClustersMinArea",	"%d",   STRUCT_OFFSET(ConfigData, BottomClustersMinArea),	"4", true},
	{"LightLevel",				"%d",   STRUCT_OFFSET(ConfigData, LightLevel),				"10000", true},	
	{"LimiterDelay",			"%d",   STRUCT_OFFSET(ConfigData, LimiterDelay),			"3000", true},
	{"VLayers",					"%d",   STRUCT_OFFSET(ConfigData, VLayers),					"12", true},
	{"VInactiveLayers",			"%d",   STRUCT_OFFSET(ConfigData, VInactiveLayers),			"0", true},
	{"TopStep",					"%f",   STRUCT_OFFSET(ConfigData, TopStep),					"40.", true},
	{"BottomStep",				"%f",   STRUCT_OFFSET(ConfigData, BottomStep),				"45.", true},
	{"VSpeed",					"%f",   STRUCT_OFFSET(ConfigData, VSpeed),					"50000.", true},
	{"VAcc",					"%f",   STRUCT_OFFSET(ConfigData, VAcc),					"100000.", true},
	{"VTol",					"%f",   STRUCT_OFFSET(ConfigData, VTol),					"2.", true},
	{"VBaseSpeed",				"%f",   STRUCT_OFFSET(ConfigData, VBaseSpeed),				"50000.", true},
	{"XStep",					"%f",   STRUCT_OFFSET(ConfigData, XStep),					"330.", true},
	{"YStep",					"%f",   STRUCT_OFFSET(ConfigData, YStep),					"330.", true},
	{"HSpeed",					"%f",   STRUCT_OFFSET(ConfigData, HSpeed),					"50000.", true},
	{"HAcc",					"%f",   STRUCT_OFFSET(ConfigData, HAcc),					"100000.", true},
	{"HTol",					"%f",   STRUCT_OFFSET(ConfigData, HTol),					"5.", true},
	{"MaxTracks",				"%d",   STRUCT_OFFSET(ConfigData, MaxTracks),				"100000", true},
	{"MaxClusters",				"%d",   STRUCT_OFFSET(ConfigData, MaxClusters),				"10000", true},
	{"BaseThickness",			"%f",   STRUCT_OFFSET(ConfigData, BaseThickness),			"200.", true},
	{"FocusTolerance",			"%f",   STRUCT_OFFSET(ConfigData, FocusTolerance),			"200.", true},
	{"SurfaceAdjustment",		"%f",   STRUCT_OFFSET(ConfigData, SurfaceAdjustment),		"10.", true},
	{"ThicknessTolerance",		"%f",   STRUCT_OFFSET(ConfigData, ThicknessTolerance),		"50.", true},
	{"MinValidLayers",			"%d",   STRUCT_OFFSET(ConfigData, MinValidLayers),			"10", true},
	{"FocusLockModel",			"%d",   STRUCT_OFFSET(ConfigData, FocusLockModel),			"0", true},
	{"XFields",					"%d",   STRUCT_OFFSET(ConfigData, TemplateXFields),			"11", true},
	{"YFields",					"%d",   STRUCT_OFFSET(ConfigData, TemplateYFields),			"11", true},
	{"ZSampleInterval",			"%d",   STRUCT_OFFSET(ConfigData, ZSampleInterval),			"10", true},
	{"FocusZSampleInterval",	"%d",   STRUCT_OFFSET(ConfigData, FocusZSampleInterval),	"10", true},
	{"ScanningScheme",			"%d",   STRUCT_OFFSET(ConfigData, ScanningScheme),			"0", true},
	{"Shrinkage",				"%f",   STRUCT_OFFSET(ConfigData, Shrinkage),				"1.2", true},
	{"ZScanDuration",			"%d",   STRUCT_OFFSET(ConfigData, ZScanDuration),			"450", true},
	{"XYZMotionDuration",		"%d",   STRUCT_OFFSET(ConfigData, XYZMotionDuration),		"120", true},
	{"EnableScanGrid",			"%d",   STRUCT_OFFSET(ConfigData, EnableScanGrid),			"0", false},
	{"SaveGrains",				"%d",   STRUCT_OFFSET(ConfigData, SaveGrains),				"1", false},
	{"FocusOffset",				"%f",   STRUCT_OFFSET(ConfigData, FocusOffset),				"0.0", false},
	{"PlateQualityWait",		"%d",   STRUCT_OFFSET(ConfigData, PlateQualityWait),		"300", false},
	{"AutoTuneFog",				"%d",	STRUCT_OFFSET(ConfigData, AutoTuneFog),				"0", false}
	};

const int MachineConfigDataN = 11;

QueryDataInfo MachineConfigDataName[MachineConfigDataN] =
{
	{"DigXDec",					"%d",   STRUCT_OFFSET(ConfigData, DigXDec), "-1"},
    {"DigXInc",                 "%d",   STRUCT_OFFSET(ConfigData, DigXInc), "-1"},
    {"DigYDec",                 "%d",   STRUCT_OFFSET(ConfigData, DigYDec), "-1"},
    {"DigYInc",                 "%d",   STRUCT_OFFSET(ConfigData, DigYInc), "-1"},
    {"DigSet1",                 "%d",   STRUCT_OFFSET(ConfigData, DigSet1), "-1"},
    {"DigSet2",                 "%d",   STRUCT_OFFSET(ConfigData, DigSet2), "-1"},
    {"DigToggleFound",          "%d",   STRUCT_OFFSET(ConfigData, DigToggleFound), "-1"},
    {"DigSwitchEmuLayer",       "%d",   STRUCT_OFFSET(ConfigData, DigSwitchEmuLayer), "-1"},
    {"DigGo",                   "%d",   STRUCT_OFFSET(ConfigData, DigGo), "-1"},
    {"AxXAxis",                 "%d",   STRUCT_OFFSET(ConfigData, AxXAxis), "-1"},
    {"AxYAxis",                 "%d",   STRUCT_OFFSET(ConfigData, AxYAxis), "-1"}
};

BOOL CALLBACK myenum(HWND hwnd, LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// CVertigoScan7Class

CVertigoScan7Class::CVertigoScan7Class()
{	
	CMI.Context = 0;
	CMI.pSaveConfig = 0;
	CMI.pLoadConfig = 0;
	pMonitor = 0;
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
	strcpy(Slots[9].Name, "Plate Changer");
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
	SySal::BasicTypes::Identifier Id;
	Id.Part0 = Id.Part1 = Id.Part2 = Id.Part3 = 0;
	System::AppDomain::CurrentDomain->SetData("$_Plate_$", Id);
	System::AppDomain::CurrentDomain->SetData("$_Zone_$", Id);
	{
		SySalConfig VoidConfig = {"", 0, 0};
		int i;
		for (i = 0; i < ConfigDataN; i++)
			GetData(ConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
        for (i = 0; i < MachineConfigDataN; i++)
			GetData(MachineConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
		};
#ifdef ENABLE_NET
	try
	{
		TkClient = gcnew SySal::DAQSystem::TrackingClient();
	}
	catch(System::Exception ^x)
	{
		int len;
		System::String ^str = x->Message;
		len = str->Length;
		pin_ptr<const wchar_t> text = PtrToStringChars(str);
		char *t = (char *)malloc(len + 1);
		int i;
		for (i = 0; i < len; i++)
			t[i] = text[i];
		t[i] = 0;
		::MessageBox(0, t, "TkClient creation error", MB_OK);
		free(t);
		TkClient = nullptr;
	}
	CWnd OwnerWnd;
	volatile HWND hTop = ::GetTopWindow(0);
	::EnumThreadWindows(::GetCurrentThreadId(), myenum, (LPARAM)&hTop);
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	int res = OwnerWnd.Attach(hTop);
	pMonitor = new CScanGridMonitor(TkClient, &OwnerWnd);
	pMonitor->Create(IDD_SCANGRID, &OwnerWnd);	
	OwnerWnd.Detach();
#endif	
}


CVertigoScan7Class::~CVertigoScan7Class()
{
	CloseHandle(HStatusMutex);
	if (iSMCOb) iSMCOb->Release();
#ifdef ENABLE_NET
	if (pMonitor) 
	{		
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		pMonitor->ShowMonitor(false);
		delete pMonitor;
		pMonitor = 0;
	}
	if (System::Object::ReferenceEquals(TkClient, nullptr) == false)
	{
		TkClient->Free();
		TkClient = nullptr;
	}
#endif
}


STDMETHODIMP CVertigoScan7Class::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::SetConfig(SySalConfig *pConfig)
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
// KRYSS: THICKNESS	
	C.TunedBottomStep = C.BottomStep;
	C.TunedTopStep = C.TopStep;
// END KRYSS
	if (C.MaxClusters < 5 * max(C.TopClusterThreshold, C.BottomClusterThreshold))
		C.MaxClusters = 5 * max(C.TopClusterThreshold, C.BottomClusterThreshold);
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::GetConfig(SySalConfig *pConfig)
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

STDMETHODIMP CVertigoScan7Class::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
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

STDMETHODIMP CVertigoScan7Class::EnableMonitor(boolean bEnable)
{
	if (pMonitor) 
	{
		pMonitor->ShowMonitor(bEnable);
		return S_OK;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CVertigoScan7Class::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CVertigoScan7Class::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Vertigo Scan 7.1", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::SyncExec()
{
	// TODO: Add your implementation code here

//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	MessageBox(AfxGetMainWnd()->m_hWnd, "Simple Sync Exec Example!!!", "Cuckoo!", MB_OK);
	return S_OK;
}


STDMETHODIMP CVertigoScan7Class::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	WaitForSingleObject(HStatusMutex, INFINITE);
	ShouldStop = false;
	ReleaseMutex(HStatusMutex);
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::AsyncWait()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CVertigoScan7Class::AsyncPause()
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

STDMETHODIMP CVertigoScan7Class::AsyncStop()
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

STDMETHODIMP CVertigoScan7Class::AsyncResume()
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

STDMETHODIMP CVertigoScan7Class::IsReady(long *pWrongConn, long *pRetCode)
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
			ISySalObject2 *iOb2;
			if (Slots[2].pUnknown->QueryInterface(IID_ISySalObject2, (void **)&iOb2) == S_OK) iOb2->Release();
			else throw 2;
			}
		else throw 2;
		if (Slots[3].pUnknown)
		{
			ITrackFitter3 *iFt1;
			if (Slots[3].pUnknown->QueryInterface(IID_ITrackFitter3, (void **)&iFt1) == S_OK) iFt1->Release();
			else throw 3;
			ISySalObject2 *iOb2;
			if (Slots[3].pUnknown->QueryInterface(IID_ISySalObject2, (void **)&iOb2) == S_OK) iOb2->Release();
			else throw 3;
			}
		else throw 3;
		if (Slots[4].pUnknown)
		{
			ITracker *iTk2;
			if (Slots[4].pUnknown->QueryInterface(IID_ITracker, (void **)&iTk2) == S_OK) iTk2->Release();
			else throw 4;
			ISySalObject2 *iOb2;
			if (Slots[4].pUnknown->QueryInterface(IID_ISySalObject2, (void **)&iOb2) == S_OK) iOb2->Release();
			else throw 4;
			}
		else throw 4;
		if (Slots[5].pUnknown)
		{
			ITrackFitter *iFt2;
			if (Slots[5].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt2) == S_OK) iFt2->Release();
			else throw 5;
			ISySalObject2 *iOb2;
			if (Slots[5].pUnknown->QueryInterface(IID_ISySalObject2, (void **)&iOb2) == S_OK) iOb2->Release();
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
			IPlateChanger *iPC;
			if (Slots[9].pUnknown->QueryInterface(IID_IPlateChanger, (void **)&iPC) == S_OK) iPC->Release();
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
STDMETHODIMP CVertigoScan7Class::SetConfigManagerInterface(ConfigManagerInterface *pCMI)
{
	CMI = *pCMI;
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::GetCLSID(CLSID *pCLSID)
{
	*pCLSID = CLSID_VertigoScan7;
	return S_OK;	
}

UINT WINAPI CVertigoScan7Class::AsyncExecHook(void *pOwner)
{
	return ((CVertigoScan7Class *)pOwner)->AsyncExec();
}

BOOL CALLBACK myenum(HWND hwnd, LPARAM lParam)
{
	static char checktext[1024];
	::GetWindowText(hwnd, checktext, 1023);
	checktext[1023] = 0;
	if (strstr(checktext, "SySal 2000") && strstr(checktext, "ScanServer"))
	{
		*(HWND *)lParam = hwnd;
		return FALSE;
	}
	*(HWND *)lParam = 0;
	return TRUE;
}

char *CharFrom(System::String ^str)
{
	char *text = new char[str->Length + 1];
	int t;
	for (t = 0; t < str->Length; t++)
		text[t] = str[t];
	text[t] = 0;
	return text;
}

void CVertigoScan7Class::Answer(System::Threading::AutoResetEvent ^hSS, System::Object ^obj)
{
	System::AppDomain::CurrentDomain->SetData("$_SSID_$", nullptr);
	System::AppDomain::CurrentDomain->SetData("$_SSOD_$", obj);
	hSS->Set();				
}

Object ^CVertigoScan7Class::Request()
{
	return System::AppDomain::CurrentDomain->GetData("$_SSID_$");
}

UINT CVertigoScan7Class::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);	
	//SetThreadName(GetCurrentThreadId(), "VS6 AsyncExec");	
	ReleaseMutex(HStatusMutex);

	ISySalDataIO2 *iIO = 0;
	IObjective *iOb = 0;
	ITracker3 *iTk1 = 0, *iTk2 = 0;
	ITrackFitter3 *iFt1 = 0, *iFt2 = 0;
	IStage2 *iSt = 0;
	IFrameGrabber *iFG = 0;
	IVisionProcessor3 *iVP = 0;
	ISheetMap *iSM = 0;
    IPlateChanger *iPC = 0;
	IPlateChanger2 *iPC2 = 0; //GS

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
	if (Slots[9].pUnknown) Slots[9].pUnknown->QueryInterface(IID_IPlateChanger, (void **)&iPC);
	if (iPC) if (iPC->QueryInterface(IID_IPlateChanger2, (void **)&iPC2) != S_OK) iPC2 = 0;	//GS

	if (iFG) iFG->QueryInterface(IID_IVisionProcessor3, (void **)&iVP);

	System::Threading::AutoResetEvent ^hSS = nullptr;
	System::Threading::AutoResetEvent ^rSS = nullptr;
	if (System::AppDomain::CurrentDomain->GetData("$_SSOEv_$") != nullptr)
	{	
		rSS = gcnew System::Threading::AutoResetEvent(false);
		System::AppDomain::CurrentDomain->SetData("$_SSIEv_$", rSS);
		hSS = (System::Threading::AutoResetEvent ^)System::AppDomain::CurrentDomain->GetData("$_SSOEv_$");
		}

	if (hSS != nullptr)
	{
		float AutoZReset = 0.0f;
		bool ZSet = false;
		bool TrustZ = false;
		bool Continue = true;
		System::Boolean ReturnValue = false;			
			
		CScan Scan(
#ifdef ENABLE_NET
			C.EnableScanGrid ? TkClient : nullptr, 
#endif				
			&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, 
				iPC2, //GS
			C, 0, AutoZReset, TrustZ);

		DUMPTIME(-20);
		while (Continue)
		{			
			rSS->WaitOne();
			DUMPTIME(-19);
			System::Object ^reqobj = Request();
			if (reqobj == nullptr) 
			{
				Sleep(1000);
				continue;
			}

			if (reqobj->GetType() == System::Exception::typeid) Continue = false;
			else if (reqobj->GetType() == SySal::DAQSystem::Scanning::ZoneDesc::typeid || (reqobj->GetType() == System::Collections::ArrayList::typeid && ((System::Collections::ArrayList ^)reqobj)[0]->GetType() == SySal::DAQSystem::Scanning::ZoneDesc::typeid))
			{
				SySal::DAQSystem::Scanning::ZoneDesc ^zone = nullptr;
				SySal::BasicTypes::Rectangle ^nextrect = nullptr;
				if (reqobj->GetType() == System::Collections::ArrayList::typeid)
				{
					System::Collections::ArrayList ^arr = (System::Collections::ArrayList ^)reqobj;
					zone = (SySal::DAQSystem::Scanning::ZoneDesc ^)arr[0];
					nextrect = (SySal::BasicTypes::Rectangle ^)arr[1];
				}
				else zone = (SySal::DAQSystem::Scanning::ZoneDesc ^)reqobj;

				if (!ZSet)
				{
					Answer(hSS, ReturnValue = false);
					continue;
					};
						
				DUMPTIME(-18);
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", true);
				DUMPTIME(-17);

				if (nextrect != nullptr)
					Scan.PreloadNext(nextrect->MinX, nextrect->MinY, nextrect->MaxX, nextrect->MaxY);
				DUMPTIME(-16);

				DUMPTIME(-15);
						
				UINT Ret = 0;
				char *txtout = CharFrom(zone->Outname);
				Identifier Id;
				SySal::BasicTypes::Identifier Curr;
				try
				{
					Curr = (SySal::BasicTypes::Identifier)System::AppDomain::CurrentDomain->GetData("$_Plate_$");
					Id.Part[0] = Curr.Part0;
					Id.Part[1] = Curr.Part1;
				}
				catch (System::Exception ^)
				{
					Curr.Part0 = Id.Part[0] = 0;
					Curr.Part1 = Id.Part[1] = 0;
				}
				Curr.Part2 = Id.Part[2] = zone->Series / 1000000000L;
				Curr.Part3 = Id.Part[3] = zone->Series % 1000000000L;
				System::AppDomain::CurrentDomain->SetData("$_Zone_$", Curr);
				//GS BUG FIXED (Marilisa) Ret = Scan.ResetAndScan(Id, zone->MinX, zone->MaxX, zone->MinY, zone->MaxY, 0, txtout, TrustZ, true, 
				Ret = Scan.ResetAndScan(Id, zone->MinX, zone->MaxX, zone->MinY, zone->MaxY, 0, txtout, TrustZ, zone->UsePresetSlope, 
					zone->UsePresetSlope ? (zone->PresetSlope.X / C.Shrinkage) : 0.0, zone->UsePresetSlope ? (zone->PresetSlope.Y / C.Shrinkage) : 0.0, 
					zone->UsePresetSlope ? (zone->PresetSlopeAcc.X / C.Shrinkage) : 0.0, zone->UsePresetSlope ? (zone->PresetSlopeAcc.Y / C.Shrinkage) : 0.0);
				DUMPTIME(-14);
				delete [] txtout;
				Continue = (Ret != (UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE));
				ReturnValue = (Ret == UM_END);
				TrustZ = (Ret == UM_END);
				Answer(hSS, ReturnValue);
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", nullptr);
			}
			else if (reqobj->GetType() == SySal::DAQSystem::Scanning::MountPlateDesc::typeid)
			{
				TrustZ = false;
				SySal::DAQSystem::Scanning::MountPlateDesc ^mplate = (SySal::DAQSystem::Scanning::MountPlateDesc ^)reqobj;
				iVP->VPUnlock();
				Identifier Id;
				Id.Part[0] = mplate->BrickId;
				Id.Part[1] = mplate->PlateId;
				Id.Part[2] = Id.Part[3] = 0;
				char *text = CharFrom(mplate->TextDesc);
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", true);
				if (ExecLoadPlate(&AutoZReset, iSt, iFG, iPC, Id, text))
				{
					Scan.SetZAndTrust(TrustZ, AutoZReset);
					Scan.NotifyPlateLoaded();
					WaitForSingleObject(HStatusMutex, INFINITE);
					iSM->QueryInterface(IID_ISySalObject, (void **)&iSMCOb);
					ReleaseMutex(HStatusMutex);	
					char *textmap = CharFrom(mplate->MapInitString);
					HRESULT HRes = iSM->Init((BYTE *)textmap, 0, (HSySalHANDLE)HStatusChangeEvent);	
					delete [] textmap;
					WaitForSingleObject(HStatusMutex, INFINITE);
					iSMCOb->Release();
					iSMCOb = 0;
					ReleaseMutex(HStatusMutex);
					if (HRes == S_OK)
					{
						SySal::BasicTypes::Identifier Curr;
						Curr.Part0 = Id.Part[0];
						Curr.Part1 = Id.Part[1];
						Curr.Part2 = Id.Part[2];
						Curr.Part3 = Id.Part[3];
						System::AppDomain::CurrentDomain->SetData("$_Plate_$", Curr);
						ZSet = true;		
						ReturnValue = true;
						}
					else ReturnValue = false;
					}
				else ReturnValue = false;
				delete [] text;
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", nullptr);
				Answer(hSS, ReturnValue);
			}
			else if (reqobj->GetType() == System::Boolean::typeid)
			{
				iVP->VPUnlock();
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", true);
				if (ReturnValue = ExecUnloadPlate(iSt,iPC))
				{
					System::AppDomain::CurrentDomain->SetData("$_Plate_$", nullptr);
					Scan.SetZAndTrust(false, 0.0f);
					ZSet = false;
					ReturnValue = true;
					}
				else ReturnValue = false;	
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", nullptr);
				Answer(hSS, ReturnValue);
			}
			else if (reqobj->GetType() == System::Collections::ArrayList::typeid && ((System::Collections::ArrayList ^)reqobj)->Count == 3)
			{
				System::Collections::ArrayList ^arr = (System::Collections::ArrayList ^)reqobj;
				char *txtobj = CharFrom((System::String ^)arr[0]);
				char *txtparam = CharFrom((System::String ^)arr[1]);
				char *txtval = CharFrom((System::String ^)arr[2]);
				ReturnValue = ExecSetParam(txtobj, txtparam, txtval);
				delete [] txtval;
				delete [] txtparam;
				delete [] txtobj;
				Answer(hSS, ReturnValue);
			}
			else if (reqobj->GetType() == SySal::DAQSystem::Scanning::ManualCheck::InputBaseTrack::typeid)
			{
				iVP->VPUnlock();
				SySal::DAQSystem::Scanning::ManualCheck::InputBaseTrack mchki = (SySal::DAQSystem::Scanning::ManualCheck::InputBaseTrack)reqobj;
				FILE *d_f = fopen("c:\\acq\\vs7_mschk.txt", "a+t");
				fprintf(d_f, "MCHECK %f %f %f %f\n", mchki.Position.X, mchki.Position.Y, mchki.Slope.X, mchki.Slope.Y);
				fclose(d_f);
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", true);				
				CManualChecks ManualChecks(&m_hDefWnd, iFG, iSM, iSt, iOb, C, mchki.Id, mchki.Position.X, mchki.Position.Y, mchki.Slope.X, mchki.Slope.Y, mchki.PositionTolerance, mchki.SlopeTolerance);				
				SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack mchko;
				if (ManualChecks.DoModal() == IDOK) 
				{
					mchko.CheckDone = true;
					mchko.Found = ManualChecks.m_Found;
					mchko.Grains = 0;
					mchko.Id = mchki.Id;
					mchko.Position.X = ManualChecks.First.X;
					mchko.Position.Y = ManualChecks.First.Y;
					mchko.Slope.X = ManualChecks.Slope.X;
					mchko.Slope.Y = ManualChecks.Slope.Y;
					}
				else
				{
					mchko.CheckDone = false;
					mchko.Found = false;
					mchko.Grains = 0;
					mchko.Id = mchki.Id;
					mchko.Position.X = mchki.Position.X;
					mchko.Position.Y = mchki.Position.Y;
					mchko.Slope.X = mchki.Slope.X;
					mchko.Slope.Y = mchki.Slope.Y;
					}
				m_hDefWnd = 0;
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", nullptr);
				Answer(hSS, mchko);				
			}
			else if (reqobj->GetType() == SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet::typeid)
			{
				iVP->VPUnlock();
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", true);
				SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet fgthks;
				fgthks.BottomFogGrains_1000MicronCubed = fgthks.TopFogGrains_1000MicronCubed = 0.;
				fgthks.TopThickness = fgthks.BaseThickness = fgthks.BottomThickness = 0.;
				float zref;
				bool ok = ExecGetFogThickness(iSt, iFG, iPC2, fgthks, zref);
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", nullptr);
				Answer(hSS, fgthks);
			}
			else if (reqobj->GetType() == SySal::DAQSystem::Scanning::ImageDumpRequest::typeid)
			{
				iVP->VPUnlock();
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", true);				
				SySal::DAQSystem::Scanning::ImageDumpRequest imdumpreq = (SySal::DAQSystem::Scanning::ImageDumpRequest)reqobj;
				char *outpath = CharFrom(imdumpreq.OutputPath);
				Identifier id;
				id.Part[0] = imdumpreq.Id.Part0;
				id.Part[1] = imdumpreq.Id.Part1;
				id.Part[2] = imdumpreq.Id.Part2;
				id.Part[3] = imdumpreq.Id.Part3;
				bool ok = ExecTakeImages(iSt, iFG, iSM, outpath, imdumpreq.Position.X, imdumpreq.Position.Y, imdumpreq.Slope.X, imdumpreq.Slope.Y, id);
				delete [] outpath;
				System::AppDomain::CurrentDomain->SetData("$_IsBusy_$", nullptr);
				Answer(hSS, ok);
			}
			else
			{
				Answer(hSS, nullptr);
			}

			DUMPTIME(-13);
			};
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
			MyDlg.m_EnableRemoteScan = false; //(hSS != 0);
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
							
							
							CScan Scan(
#ifdef ENABLE_NET								
								C.EnableScanGrid ? TkClient : nullptr, 
#endif								
								&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, 
								iPC2, //GS
								C, Id, ScanStart.m_MinX, ScanStart.m_MaxX, ScanStart.m_MinY, ScanStart.m_MaxY, ScanStart.m_EnableSlopePreset, 
								ScanStart.m_SlopeX, ScanStart.m_SlopeY, ScanStart.m_SlopeAccX, ScanStart.m_SlopeAccY, 0, pResume);
							
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
					CTestAndConfig TestAndConfig(&m_hDefWnd, (ISySalObject *)this, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, 
						iPC2, //GS
						&CMI, C);
					if (TestAndConfig.DoModal() == 
						(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
						Selection = MS_SEL_EXIT;
					m_hDefWnd = 0;
					};
				break;
				
			case MS_SEL_MANUALCHECKS:
				{
					CManualChecks ManualChecks(&m_hDefWnd, this, iIO, iVP, iTk1, iFt1, iTk2, iFt2, iFG, iSM, iSt, iOb, C);
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
				MessageBox(0, "ScanServer was reported to be NULL.\r\nMemory corruption possible.", "Internal inconsistency!", MB_ICONERROR | MB_OK);
				break;

			case MS_SEL_FOGTHICKNESS:
				{
					SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet fgthks;
					float zref = 0.0f;
					if (!ExecGetFogThickness(iSt, iFG, iPC2, fgthks, zref)) ::MessageBox(0, "Fog/Thickness measurement failed.", "Measurement error.", MB_ICONERROR);
					else
					{
						CPlateQualityDlg pq;
						pq.SetResults(fgthks.TopFogGrains_1000MicronCubed, fgthks.BottomFogGrains_1000MicronCubed, fgthks.TopThickness, fgthks.BottomThickness, fgthks.BaseThickness);
						pq.DoModal();
					}
				}
				break;

			case MS_SEL_IMAGEDUMP:
				{
					CScanStart dlg(0, true);
					if (dlg.DoModal() == IDOK)
					{
						Identifier id;
						id.Part[0] = dlg.m_ID1;
						id.Part[1] = dlg.m_ID2;
						id.Part[2] = dlg.m_ID3;
						id.Part[3] = dlg.m_ID4;
						if (!ExecTakeImages(iSt, iFG, iSM, dlg.m_ImageDumpFile, dlg.m_ImDumpX, dlg.m_ImDumpY, dlg.m_SlopeX, dlg.m_SlopeY, id)) 
							::MessageBox(0, "Image acquisition failed.", "Acquisition Error", MB_OK | MB_ICONERROR);
					}
				}
				break;
			};
		}
		while (Selection != MS_SEL_EXIT);
	}

	System::AppDomain::CurrentDomain->SetData("$_SySalScanServerOEv_$", nullptr);
	System::AppDomain::CurrentDomain->SetData("$_SSIEv_$", nullptr);
	
	if (iPC2) iPC2->Release();	//GS
	if (iPC) iPC->Release();	//GS
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

bool CVertigoScan7Class::ExecGetFogThickness(IStage2 *iSt, IFrameGrabber *iFG, IPlateChanger2* iPC2, SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet &fgthks, float &zreference)
{
#define MAXREFS 31
	CPlateQualityInitDlg pqi(C.PlateQualityWait);
	float zref = 0.0f;	
	int xyrefcount = 0;
	float xyrefs[2 * MAXREFS];
	struct refmeas
	{
		float TopThickness;
		float BaseThickness;
		float BottomThickness;
		float ZRef;
		float TopFog;
		float BottomFog;
	} zfrefs[MAXREFS];
	bool validrefs[MAXREFS];
	if (C.PlateQualityWait <= 0 || pqi.DoModal() != IDOK)
	{
		IStage3 *iSt3 = 0;
		if (iSt->QueryInterface(IID_IStage3, (void **)&iSt3) != S_OK)
		{
			::MessageBox(0, "IStage3 interface must be supported by Stage control object.", "Configuration error.", MB_OK);
			if (iSt3) iSt3->Release();
			return false;
		}
		if (iSt3->GetZRef((BYTE *)"Glass", &zref) != S_OK)
		{
			::MessageBox(0, "Can't get \"Glass\" position for Z.", "Configuration error.", MB_OK);
			if (iSt3) iSt3->Release();
			return false;
		}
		zref += C.BaseThickness + C.BottomStep;
		xyrefcount = 0;  
		while(xyrefcount < MAXREFS)
		{
			char xyname[64];
			sprintf(xyname, "XYFog_%02d", xyrefcount);
			if (iSt3->GetXYRef((BYTE *)xyname, xyrefs + 2 * xyrefcount, xyrefs + 2 * xyrefcount + 1) != S_OK) break;			
			xyrefcount++;			
		}
	}
	else
	{
		xyrefcount = 1;
		iSt->GetPos(0, xyrefs);
		iSt->GetPos(1, xyrefs + 1);
		iSt->GetPos(2, &zref);
	}
	int valid = 0;
	int i;
	ISySalObject *iStOb = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	for (i = 0; i < xyrefcount; i++)
	{
		float topfog = 0.0f;
		float bottomfog = 0.0f;
		float topext = zref + C.TopStep;
		float topint = zref;
		float bottomint = zref - C.BaseThickness;
		float bottomext = zref - C.BaseThickness - C.BottomStep;
		float topquality, bottomquality;
		int toplight, bottomlight;
		float xref = xyrefs[i * 2];							 //GS
		float yref = xyrefs[i * 2 + 1];                      //GS	
		if (iPC2) iPC2->DispenseOil(xref, yref, xref, yref); //GS
		iSt->PosMove(0, xref, C.HSpeed, C.HAcc);
		iSt->PosMove(1, yref, C.HSpeed, C.HAcc);
		iSt->PosMove(2, zref, C.VSpeed, C.VAcc);
		float w;
		do
		{
			iSt->GetPos(0, &w);
		}
		while (fabs(w - xref) > C.HTol + 10.0);
		iSt->Stop(0);
		do
		{
			iSt->GetPos(1, &w);
		}
		while (fabs(w - yref) > C.HTol + 10.0);
		iSt->Stop(1);
		do
		{
			iSt->GetPos(2, &w);
		}
		while (fabs(w - zref) > C.VTol + 5.0f);
		iSt->Stop(2);
		if (validrefs[i] = FogGetQuantities(iSt, iStOb, iFG, topfog, topext, topint, topquality, toplight, bottomfog, bottomint, bottomext, bottomquality, bottomlight))
		{
			zfrefs[i].TopThickness = topext - topint;
			zfrefs[i].ZRef = topint;
			zfrefs[i].BaseThickness = topint - bottomint;
			zfrefs[i].BottomThickness = bottomint - bottomext;
			zfrefs[i].TopFog = topfog;
			zfrefs[i].BottomFog = bottomfog;
			valid++;
		}
	}
	iStOb->Release();
	if (valid == 0) return false;
	for (i = xyrefcount = 0; i < valid; i++)	
		if (validrefs[i])		
			zfrefs[xyrefcount++] = zfrefs[i];
	refmeas median_values;
	fgthks.TopThickness = FindMedian(&zfrefs[0].TopThickness, sizeof(refmeas), valid);
	fgthks.BaseThickness = FindMedian(&zfrefs[0].BaseThickness, sizeof(refmeas), valid);
	fgthks.BottomThickness = FindMedian(&zfrefs[0].BottomThickness, sizeof(refmeas), valid);
	fgthks.TopFogGrains_1000MicronCubed = FindMedian(&zfrefs[0].TopFog, sizeof(refmeas), valid);
	fgthks.BottomFogGrains_1000MicronCubed = FindMedian(&zfrefs[0].BottomFog, sizeof(refmeas), valid);		
	zreference = FindMedian(&zfrefs[0].ZRef, sizeof(refmeas), valid);
	return true;
}


bool CVertigoScan7Class::ExecTakeImages(IStage2 *iSt, IFrameGrabber *iFG, ISheetMap *iSM, const char *outpath, float px, float py, float sbsx, float sbsy, Identifier id)
{
	double mappedx, mappedy;
	double p_stagex, p_stagey;
	double imxx, imxy, imyx, imyy;
	iSM->DirFixPoint(px, py);
	iSM->DirMapPoint(px, py, &p_stagex, &p_stagey);
	iSM->InvMapVector(1, 0, &imxx, &imyx);
	iSM->InvMapVector(0, 1, &imxy, &imyy);

	IStage3 *iSt3 = 0;
	if (iSt->QueryInterface(IID_IStage3, (void **)&iSt3) != S_OK)
	{
		::MessageBox(0, "IStage3 interface must be supported by Stage control object.", "Configuration error.", MB_OK);
		if (iSt3) iSt3->Release();
		return false;
	}
	float zref = 0.0f;
	if (iSt3->GetZRef((BYTE *)"Glass", &zref) != S_OK)
	{
		::MessageBox(0, "Can't get \"Glass\" position for Z.", "Configuration error.", MB_OK);
		if (iSt3) iSt3->Release();
		return false;
	}
	zref += C.BaseThickness + C.BottomStep;
	int valid = 0;
	int i;
	ISySalObject *iStOb = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	float topext = zref + C.TopStep;
	float bottomint = zref - C.BaseThickness;
	iSt->PosMove(0, p_stagex, C.HSpeed, C.HAcc);
	iSt->PosMove(1, p_stagey, C.HSpeed, C.HAcc);
	iSt->PosMove(2, topext, C.VSpeed, C.VAcc);
	float w;
	do
	{
		iSt->GetPos(0, &w);
	}
	while (fabs(w - p_stagex) > C.HTol + 10.0);
	iSt->Stop(0);	
	p_stagex = w;
	do
	{
		iSt->GetPos(1, &w);
	}
	while (fabs(w - p_stagey) > C.HTol + 10.0);
	iSt->Stop(1);
	p_stagey = w;
	do
	{
		iSt->GetPos(2, &w);
	}
	while (fabs(w - topext) > C.VTol + 5.0f);	
	iSt->Stop(2);
	iSM->InvMapPoint(p_stagex, p_stagey, &mappedx, &mappedy);
	FogTakeImages(iSt, iStOb, iFG, outpath, px, py, topext, bottomint, imxx, imxy, imyx, imyy, imxx * sbsx + imxy * sbsy, imyx * sbsx + imyy * sbsy, id);
	iStOb->Release();
	return true;
}


float CVertigoScan7Class::FindMedian(float *px, int stride, int count)
{
	int place, scan, best;
	for (place = 0; place < count / 2 + 1; place++)
	{
		float minv = *(float *)(void *)(((char *)(void *)px) + stride * place);
		best = place;
		for (scan = place + 1; scan < count; scan++)
		{
			float v = *(float *)(void *)(((char *)(void *)px) + stride * scan);
			if (v < minv)
			{
				minv = v;
				best = scan;
			}
		}
		*(float *)(void *)(((char *)(void *)px) + stride * scan) = *(float *)(void *)(((char *)(void *)px) + stride * place);
		*(float *)(void *)(((char *)(void *)px) + stride * place) = minv;
	}
	if (count % 2 == 1) return *(float *)(void *)(((char *)(void *)px) + stride * (count / 2));
	return 0.5 *
		(*(float *)(void *)(((char *)(void *)px) + stride * (count / 2))) +
		(*(float *)(void *)(((char *)(void *)px) + stride * (count / 2) - 1));
}

bool CVertigoScan7Class::ExecLoadPlate(float *pAutoZReset, IStage *iSt, IFrameGrabber *iFG, IPlateChanger *iPc, Identifier id, char *textid)
{
	ISySalObject *iStOb = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iStOb->EnableMonitor(true);
	static char outtext[4096];
	IStage3 *iSt3 = 0;
	UINT Ret;
	if (iSt->QueryInterface(IID_IStage3, (void **)&iSt3) == S_OK)
	{
		sprintf(outtext, "Please load plate %d/%d/%d/%d - Text Id: %s\r\n\r\n",
			id.Part[0], id.Part[1], id.Part[2], id.Part[3], textid ? textid : "None");		
//Robot Related
	int LDres=0;
	if(iPc)  //load plate by robot
	{   
		if(!iSt) return false;
		LDres=iPc->LoadPlate(id,(BYTE*)textid);

      //- THIS BLOCK SHOULD CONTAIN ONLY THE FOLLOWING LINE:
      //-       if( LDres != S_OK  ) return false;
      //- HOWEVER, SINCE THE THE BERN PC and the TECNO PC have different standards,
      //- THE USE THE FOLLOWING CODE
      IPlateChanger2* iPC2 =0;
      if (iPc->QueryInterface(IID_IPlateChanger2, (void **)&iPC2) != S_OK) iPC2 = 0;	//GS
		if (iPC2)  {
			if( LDres != S_OK  ) return false;		//GS	S_OK, S_FALSE are the standard return value
		} else {
			if(!LDres) return false;				   //GS	non standard return value
		}
      //-
      Ret=IDOK;	
   } else
//End Robot Related

		Ret = MessageBox(0, outtext, "Help Request", MB_ICONINFORMATION | MB_OKCANCEL);
		if (Ret != IDOK) return false;
		if (iSt3->GetZRef((BYTE *)"Glass", pAutoZReset) == S_OK)
		{
			iSt3->Release();
			*pAutoZReset += C.BaseThickness + C.BottomStep;
			iStOb->EnableMonitor(false);
			iStOb->Release();
			Ret = IDOK;
		}		
	}
	else
	{
		if (iSt3) iSt3->Release();
		sprintf(outtext, "Please load plate %d/%d/%d/%d - Text Id: %s\r\n\r\n"
			"Please place the objective at the top surface of the plastic base.\r\n"
			"This Z position will be used as your hint for focusing for all next scanning tasks in this session.\r\n"
			"Press OK when the objective is at your suggested Z position.",
			id.Part[0], id.Part[1], id.Part[2], id.Part[3], textid ? textid : "None");
		Ret = MessageBox(0, outtext, "Help Request", MB_ICONINFORMATION | MB_OKCANCEL);

		iSt->GetPos(2, pAutoZReset);
		iStOb->EnableMonitor(false);
		iStOb->Release();
	}
	if (Ret == IDOK)
	{
		C.TunedTopStep = C.TopStep;
		C.TunedBottomStep = C.BottomStep;
		if (C.AutoTuneFog)
		{
			SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet fgthks;
			IStage2 *iSt2 = 0;
			if (iSt->QueryInterface(IID_IStage2, (void **)&iSt2) != S_OK)
			{
				if (iSt2) iSt2->Release();
				iSt2 = 0;
			}
			else 
			{
				IPlateChanger2* iPC2 =0;                                                         //GS
				if (iPc != 0 && iPc->QueryInterface(IID_IPlateChanger2, (void **)&iPC2) != S_OK) iPC2 = 0;	//GS
				if (ExecGetFogThickness(iSt2, iFG, iPC2, fgthks, *pAutoZReset))                  //GS
				{
					C.TunedTopStep = fgthks.TopThickness / (C.VLayers - C.VInactiveLayers) * (C.VLayers - C.VInactiveLayers + 2);
					C.TunedBottomStep = fgthks.BottomThickness / (C.VLayers - C.VInactiveLayers) * (C.VLayers - C.VInactiveLayers + 2);
				}
				iSt2->Release();
				iSt2 = 0;
			}
		}
	}
	return Ret == IDOK;
}

bool CVertigoScan7Class::ExecUnloadPlate(IStage *iSt, IPlateChanger *iPc)
{
	ISySalObject *iStOb = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iStOb->EnableMonitor(true);

//Robot related
	UINT Ret;
   if(iPc) {
      //- THIS BLOCK SHOULD CONTAIN ONLY THE FOLLOWING LINE:
      //-       Ret = ( iPc->UnloadPlate() == S_OK );
      //- HOWEVER, SINCE THE THE BERN PC and the TECNO PC have different standards,
      //- THE USE THE FOLLOWING CODE
      IPlateChanger2* iPC2 ;
      if (iPc->QueryInterface(IID_IPlateChanger2, (void **)&iPC2) != S_OK) iPC2 = 0;	//GS
		if (iPC2 ) {
         Ret = ( iPc->UnloadPlate() == S_OK );     //GS	S_OK, S_FALSE are the standard return value
		} else {
			iPc->UnloadPlate();                       //GS	non standard return value
		}
      //-
   } else
//end Robot related
	Ret = MessageBox(0, "Please unload the plate from the stage.", "Help Request", MB_ICONINFORMATION | MB_OKCANCEL);

	iStOb->EnableMonitor(false);
	iStOb->Release();
	return Ret == IDOK;
}

bool CVertigoScan7Class::ExecSetParam(char *objname, char *paramname, char *paramvalue)
{
	int i, j;
	ISySalObject *iOb = 0;
	if (!stricmp(objname, "VertigoScanner"))
		iOb = this;		
	else
		for (i = 0; i < NUMBER_OF_SLOTS; i++)		
			if (!stricmp(Slots[i].Name, objname))
			{
				if (Slots[i].pUnknown && Slots[i].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iOb) == S_OK) break;
				else return false;
			}

	if (iOb)
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
		if (iOb != this)
			iOb->Release();
		return j < T.CountOfItems;
		}
	return false;
}



STDMETHODIMP CVertigoScan7Class::IsSyncEnabled(boolean *pbIsEnabled)
{
	*pbIsEnabled = false;
	return S_OK;
}


//ISySalObjectMachineDefaults

STDMETHODIMP CVertigoScan7Class::SetMachineDefaults(SySalConfig *pConfig)
{	
	// TODO: Add your implementation code here
	int i;
	for (i = 0; i < MachineConfigDataN; i++) GetData(MachineConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems);
	if (i < MachineConfigDataN) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::GetMachineDefaults(SySalConfig *pConfig)
{	
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;
	int i;
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(MachineConfigDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = MachineConfigDataN;
	for (i = 0; i < MachineConfigDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			MachineConfigDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(MachineConfigDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(int *)((char *)&C + MachineConfigDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(float *)((char *)&C + MachineConfigDataName[i].Position));
		};
	return S_OK;
}

STDMETHODIMP CVertigoScan7Class::EditMachineDefaults(SySalConfig *pConfig, HSySalHANDLE hWnd)
{	
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	ConfigData TempC;
	int i, n;	
	for (i = 0; i < MachineConfigDataN; i++) 
		GetData(MachineConfigDataName[i], &TempC, pConfig->pItems, pConfig->CountOfItems);

	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditMachineDefaults MyDlg(&Owner);
	MyDlg.C = TempC; 

	if (MyDlg.DoModal() == IDOK)
	{
		TempC = MyDlg.C;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(n * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
		{
			Owner.Detach();
			return S_FALSE;
			}
		pConfig->CountOfItems = MachineConfigDataN;		
		for (i = 0; i < MachineConfigDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				MachineConfigDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(MachineConfigDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(int *)((char *)&TempC + MachineConfigDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(float *)((char *)&TempC + MachineConfigDataName[i].Position));
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

