// BBrain.cpp : Implementation of CBBrain
#include "stdafx.h"
#include "BetaBrain.h"
#include "BBrain.h"
#include "ums.h"
#include "MainSwitch.h"
#include "AssistedManualScanning.h"
#include "EditConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CBBrain
const int BetaBrainDataN = 72;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo BetaBrainDataName[BetaBrainDataN] =
{
	{"MaxClusters",				"%d",   STRUCT_OFFSET(SetupData, ModD.MaxClusters),			"10000"},
	{"MaxTracks",				"%d",   STRUCT_OFFSET(SetupData, ModD.MaxTracks),			"1000"},
	{"MaxFlatTracks",			"%d",   STRUCT_OFFSET(SetupData, ModD.MaxFlatTracks),		"1000"},

	{"BaseThickness",			"%f",   STRUCT_OFFSET(SetupData, EmuD.BaseThickness),		"90."},
	{"BottomThickness",			"%f",   STRUCT_OFFSET(SetupData, EmuD.BottomThickness),		"175."},
	{"TopThickness",			"%f",   STRUCT_OFFSET(SetupData, EmuD.TopThickness),		"175."},
	{"Shrinkage",				"%f",   STRUCT_OFFSET(SetupData, EmuD.Shrinkage),			"1.9"},
	{"DepthCoherenceLength",	"%f",   STRUCT_OFFSET(SetupData, EmuD.DepthCoherenceLength),"30000."},
	{"DistortionCellSize",		"%f",   STRUCT_OFFSET(SetupData, EmuD.DistortionCellSize),	"30000."},
	{"Width",					"%f",   STRUCT_OFFSET(SetupData, EmuD.Width),				"1000000."},
	{"Height",					"%f",   STRUCT_OFFSET(SetupData, EmuD.Height),				"1000000."},

	{"BaseCrossingSpeed",		"%f",   STRUCT_OFFSET(SetupData, StageD.BaseCrossingSpeed),	"200."},
	{"ScanningSpeed",			"%f",   STRUCT_OFFSET(SetupData, StageD.ScanningSpeed),		"105."},
	{"ScanningStep",			"%f",   STRUCT_OFFSET(SetupData, StageD.ScanningStep),		"3.5"},
	{"FocusTolerance",			"%f",   STRUCT_OFFSET(SetupData, StageD.FocusTolerance),	"1000."},
	{"ThicknessTolerance",		"%f",   STRUCT_OFFSET(SetupData, StageD.ThicknessTolerance),"100."},
	{"RewindSpeed",				"%f",   STRUCT_OFFSET(SetupData, StageD.RewindSpeed),		"1000."},
	{"SlowdownLength",			"%f",   STRUCT_OFFSET(SetupData, StageD.SlowdownLength),	"10."},
	{"HorizontalSpeed",			"%f",   STRUCT_OFFSET(SetupData, StageD.HorizontalSpeed),	"10000."},
	{"ShortDistAcc",			"%f",   STRUCT_OFFSET(SetupData, StageD.ShortDistAcc),		"10000."},
	{"LongDistAcc",				"%f",   STRUCT_OFFSET(SetupData, StageD.LongDistAcc),		"10000."},
	{"RelaxTime",				"%f",   STRUCT_OFFSET(SetupData, StageD.RelaxTime),			"100."},
	{"WaitLimiterReset",		"%f",   STRUCT_OFFSET(SetupData, StageD.WaitForLimiterResetTime),	"10000."},
	{"XStep",					"%f",   STRUCT_OFFSET(SetupData, StageD.XStep),				"175."},
	{"XTolerance",				"%f",   STRUCT_OFFSET(SetupData, StageD.XTolerance),		"10."},
	{"YStep",					"%f",   STRUCT_OFFSET(SetupData, StageD.YStep),				"175."},
	{"YTolerance",				"%f",   STRUCT_OFFSET(SetupData, StageD.YTolerance),		"10."},
	{"ZAcc",					"%f",   STRUCT_OFFSET(SetupData, StageD.ZAcc),				"10000."},
	{"ZTolerance",				"%f",   STRUCT_OFFSET(SetupData, StageD.ZTolerance),		"3."},
	{"ZStaticTolerance",		"%f",   STRUCT_OFFSET(SetupData, StageD.ZStaticTolerance),	"2."},

	{"AutoLightControl",		"%d",   STRUCT_OFFSET(SetupData, OptD.AutoLightControl),	"1"},
	{"MinLight",				"%d",   STRUCT_OFFSET(SetupData, OptD.MinLight),			"10000"},
	{"MaxLight",				"%d",   STRUCT_OFFSET(SetupData, OptD.MaxLight),			"20000"},
	{"MinGrayLevel",			"%d",   STRUCT_OFFSET(SetupData, OptD.MinGrayLev),			"100"},
	{"TargetGrayLevel",			"%d",   STRUCT_OFFSET(SetupData, OptD.TargetGrayLev),		"220"},
	{"LightIncrement",			"%d",   STRUCT_OFFSET(SetupData, OptD.LightIncrement),		"25"},
	{"LampDelay",				"%d",   STRUCT_OFFSET(SetupData, OptD.LampDelay),			"50"},
	{"CorrectPredictions",		"%d",   STRUCT_OFFSET(SetupData, OptD.CorrectPredictions),	"1"},
	{"MinSample",				"%d",   STRUCT_OFFSET(SetupData, OptD.MinSample),			"50"},
	{"PauseEachField",			"%d",   STRUCT_OFFSET(SetupData, OptD.PauseEachField),		"0"},
	{"RelativeClusterThreshold","%d",   STRUCT_OFFSET(SetupData, OptD.RelativeClusterThreshold),"0"},
	{"ScanBoth",				"%d",   STRUCT_OFFSET(SetupData, OptD.ScanBoth),			"1"},
	{"ScanBottom",				"%d",   STRUCT_OFFSET(SetupData, OptD.ScanBottom),			"0"},
	{"ScanTop",					"%d",   STRUCT_OFFSET(SetupData, OptD.ScanTop),				"0"},
	{"CenterScanBack",			"%d",   STRUCT_OFFSET(SetupData, OptD.CenterScanBack),		"1"},
	{"XCenterTolerance",		"%f",   STRUCT_OFFSET(SetupData, OptD.XCenterTol),			"50."},
	{"YCenterTolerance",		"%f",   STRUCT_OFFSET(SetupData, OptD.YCenterTol),			"50."},

	{"PathFileName",			"%s",   STRUCT_OFFSET(SetupData, PathD.PathFileName),		""},
	{"XFields",					"%d",   STRUCT_OFFSET(SetupData, PathD.XFields),			"1"},
	{"YFields",					"%d",   STRUCT_OFFSET(SetupData, PathD.YFields),			"1"},

	{"CheckBottom",				"%d",   STRUCT_OFFSET(SetupData, SeekerD.CheckBottom),		"1"},
	{"CheckTop",				"%d",   STRUCT_OFFSET(SetupData, SeekerD.CheckTop),			"0"},
	{"PosTolerance",			"%f",   STRUCT_OFFSET(SetupData, SeekerD.PosTolerance),		"50."},
	{"ZoneScanning",			"%d",   STRUCT_OFFSET(SetupData, SeekerD.ZoneScanning),		"1"},
	{"ZoneXFields",				"%d",   STRUCT_OFFSET(SetupData, SeekerD.ZoneXFields),		"2"},
	{"ZoneYFields",				"%d",   STRUCT_OFFSET(SetupData, SeekerD.ZoneYFields),		"2"},

	{"TopClusterContrast",		"%d",   STRUCT_OFFSET(SetupData, TopD.ClusterContrast),		"17"},
	{"TopClusterThreshold",		"%d",   STRUCT_OFFSET(SetupData, TopD.ClusterThreshold),	"100"},
	{"TopStartLayer",			"%d",   STRUCT_OFFSET(SetupData, TopD.StartLayer),			"2"},
	{"TopEndLayer",				"%d",   STRUCT_OFFSET(SetupData, TopD.EndLayer),			"30"},
	{"TopMaxLayers",			"%d",   STRUCT_OFFSET(SetupData, TopD.MaxLayers),			"80"},
	{"TopMaxFlatStripsPerTrack","%d",   STRUCT_OFFSET(SetupData, TopD.MaxFlatStripsPerTrack),"20"},
	{"TopPixMin",				"%d",   STRUCT_OFFSET(SetupData, TopD.PixMin),				"4"},
	{"TopPixMax",				"%d",   STRUCT_OFFSET(SetupData, TopD.PixMax),				"36"},

	{"BottomClusterContrast",		"%d",   STRUCT_OFFSET(SetupData, BottomD.ClusterContrast),		"17"},
	{"BottomClusterThreshold",		"%d",   STRUCT_OFFSET(SetupData, BottomD.ClusterThreshold),	"100"},
	{"BottomStartLayer",			"%d",   STRUCT_OFFSET(SetupData, BottomD.StartLayer),			"0"},
	{"BottomEndLayer",				"%d",   STRUCT_OFFSET(SetupData, BottomD.EndLayer),			"30"},
	{"BottomMaxLayers",			"%d",   STRUCT_OFFSET(SetupData, BottomD.MaxLayers),			"80"},
	{"BottomMaxFlatStripsPerTrack","%d",   STRUCT_OFFSET(SetupData, BottomD.MaxFlatStripsPerTrack),"20"},
	{"BottomPixMin",				"%d",   STRUCT_OFFSET(SetupData, BottomD.PixMin),				"4"},
	{"BottomPixMax",				"%d",   STRUCT_OFFSET(SetupData, BottomD.PixMax),				"36"}
	};

CBBrain::CBBrain()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;		
	strcpy(Slots[0].Name, "Communications");
	strcpy(Slots[1].Name, "Data I/O");
	strcpy(Slots[2].Name, "Sheet Map #1");
	strcpy(Slots[3].Name, "Sheet Map #2");
	strcpy(Slots[4].Name, "Sheet Map #3");
	strcpy(Slots[5].Name, "Objective");
	strcpy(Slots[6].Name, "Cluster Finder");
	strcpy(Slots[7].Name, "Tracker");
	strcpy(Slots[8].Name, "Track Fitter");
	strcpy(Slots[9].Name, "Stage");
	strcpy(Slots[10].Name, "Frame Grabber");
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
		for (i = 0; i < BetaBrainDataN; i++)
			GetData(BetaBrainDataName[i], &SD, VoidConfig.pItems, VoidConfig.CountOfItems);
		};
	HTerminateEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	OkToRun = true;
}


CBBrain::~CBBrain()
{
	CloseHandle(HStatusMutex);
	CloseHandle(HTerminateEvent);
}


STDMETHODIMP CBBrain::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CBBrain::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CBBrain::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < BetaBrainDataN) && (GetData(BetaBrainDataName[i], &SD, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < BetaBrainDataN) 
	{
		OkToRun = false;
		return S_FALSE;
		};
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CBBrain::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(BetaBrainDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = BetaBrainDataN;
	int i;
	for (i = 0; i < BetaBrainDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			BetaBrainDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(BetaBrainDataName[i].Format, "%s"))
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, (char *)&SD + BetaBrainDataName[i].Position, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		else if (!strcmp(BetaBrainDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, BetaBrainDataName[i].Format, *(int *)((char *)&SD + BetaBrainDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, BetaBrainDataName[i].Format, *(float *)((char *)&SD + BetaBrainDataName[i].Position));		
		};
	return S_OK;
}

STDMETHODIMP CBBrain::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	SetupData Temp;
	int i;
	for (i = 0; i < BetaBrainDataN; i++) 
		GetData(BetaBrainDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

	MyDlg.m_SD = Temp;
	if (MyDlg.DoModal() == IDOK)
	{
		Temp = MyDlg.m_SD;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(BetaBrainDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = BetaBrainDataN;
		int i;
		for (i = 0; i < BetaBrainDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				BetaBrainDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(BetaBrainDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, BetaBrainDataName[i].Format, *(int *)((char *)&Temp + BetaBrainDataName[i].Position));
			else if (!strcmp(BetaBrainDataName[i].Format, "%f"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, BetaBrainDataName[i].Format, *(float *)((char *)&Temp + BetaBrainDataName[i].Position));
			else 
				strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, (char *)&Temp + BetaBrainDataName[i].Position, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CBBrain::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CBBrain::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CBBrain::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CBBrain::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CBBrain::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CBBrain::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Beta Brain", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CBBrain::SyncExec()
{
	// TODO: Add your implementation code here

//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	MessageBox(AfxGetMainWnd()->m_hWnd, "Simple Sync Exec Example!!!", "Cuckoo!", MB_OK);
	return S_OK;
}


STDMETHODIMP CBBrain::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	ResetEvent(HTerminateEvent);
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CBBrain::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return E_NOTIMPL;
}

STDMETHODIMP CBBrain::AsyncWait()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CBBrain::AsyncPause()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
		else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CBBrain::AsyncStop()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		SetEvent(HTerminateEvent);
		if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CBBrain::AsyncResume()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{	
		if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
		else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CBBrain::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	try
	{
		if (Slots[0].pUnknown)
		{
			ISySalDataIO *iCo;
			if (Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iCo) == S_OK) iCo->Release();
			else throw 0;
			};
		if (Slots[1].pUnknown)
		{
			ISySalDataIO *iIO;
			if (Slots[1].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO) == S_OK) iIO->Release();
			else throw 1;
			};
		if (Slots[2].pUnknown)
		{
			ISheetMap *iS1;
			if (Slots[2].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iS1) == S_OK) iS1->Release();
			else throw 2;
			};
		if (Slots[3].pUnknown)
		{
			ISheetMap *iS2;
			if (Slots[3].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iS2) == S_OK) iS2->Release();
			else throw 3;
			};
		if (Slots[4].pUnknown)
		{
			ISheetMap *iS3;
			if (Slots[4].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iS3) == S_OK) iS3->Release();
			else throw 4;
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

UINT WINAPI CBBrain::AsyncExecHook(void *pOwner)
{
	return ((CBBrain *)pOwner)->AsyncExec();
}

UINT CBBrain::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	ISySalDataIO *iCo = 0;
	ISySalDataIO *iIO = 0;
	ISheetMap *iS1 = 0;
	ISheetMap *iS2 = 0;
	ISheetMap *iS3 = 0;
	IFrameGrabber *iFG = 0;
	IStage *iSt = 0;
	IClusterFinder *iCl = 0;
	ITracker *iTk = 0;
	ITrackFitter *iFt = 0;
	IObjective *iOb = 0;

	if (Slots[0].pUnknown) Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iCo);
	if (Slots[1].pUnknown) Slots[1].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO);
	if (Slots[2].pUnknown) Slots[2].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iS1);
	if (Slots[3].pUnknown) Slots[3].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iS2);
	if (Slots[4].pUnknown) Slots[4].pUnknown->QueryInterface(IID_ISheetMap, (void **)&iS3);	
	if (Slots[5].pUnknown) Slots[5].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb);
	if (Slots[6].pUnknown) Slots[6].pUnknown->QueryInterface(IID_IClusterFinder, (void **)&iCl);
	if (Slots[7].pUnknown) Slots[7].pUnknown->QueryInterface(IID_ITracker, (void **)&iTk);
	if (Slots[8].pUnknown) Slots[8].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt);
	if (Slots[9].pUnknown) Slots[9].pUnknown->QueryInterface(IID_IStage, (void **)&iSt);
	if (Slots[10].pUnknown) Slots[10].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG);

	int Selection = MS_SEL_EXIT;
	do
	{
		CMainSwitch MyDlg(&m_hDefWnd);
		MyDlg.m_AssistedManualEnable = (iS1 != 0);
		MyDlg.m_UserEnable = (iIO != 0) && (iS1 != 0)/* && (iSc != 0)*/;
		MyDlg.m_ExternalEnable = MyDlg.m_UserEnable && (iCo != 0);
		if (MyDlg.DoModal() == (UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) Selection = MS_SEL_EXIT;
		else Selection = MyDlg.m_Selection;
		m_hDefWnd = 0;
		switch (Selection)
		{
			case MS_SEL_ABOUT:		
									{
										CDialog AboutDlg(IDD_ABOUT);
										AboutDlg.DoModal();
										};
									break;

			case MS_SEL_ASSISTEDMANUAL:
									{
										CAssistedManualScanning AssManDlg(iIO, iS1, &m_hDefWnd, (HSySalHANDLE)HStatusChangeEvent);
										if (AssManDlg.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_USERDRIVEN:
			case MS_SEL_USERJOB:
			case MS_SEL_EXTERNALJOB:
									{
										Scanner.Exec(&HTerminateEvent, &m_hDefWnd, Name, iFG, iSt, iOb, iCl, iTk, iFt, iS1, iS2, iS3, iIO, SD, Selection != MS_SEL_USERDRIVEN);
										m_hDefWnd = 0;
										};
									break;

			};
		}
	while (Selection != MS_SEL_EXIT);

	if (iFG) iFG->Release();
	if (iSt) iSt->Release();
	if (iFt) iFt->Release();
	if (iTk) iTk->Release();
	if (iCl) iCl->Release();
	if (iOb) iOb->Release();
	if (iS3) iS3->Release();
	if (iS2) iS2->Release();
	if (iS1) iS1->Release();
	if (iIO) iIO->Release();
	if (iCo) iCo->Release();
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	pAsyncExec = 0;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return 0;
}

// INTERNAL FUNCTIONS

int CBBrain::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
{  
	int Index;
	for (Index = 0; (Index < N) && (strncmp(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index, 
		DataName.Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN)); Index++);
	if (Index >= N)
	{

		if (!strcmp(DataName.Format, "%s")) strcpy((char *)StartPosition + DataName.Position, DataName.Default);
   		else sscanf(DataName.Default, DataName.Format, (char *)StartPosition + DataName.Position);
   		return 0;
		};
	if (!strcmp(DataName.Format, "%s")) 
	{
		strcpy((char *)StartPosition + DataName.Position, File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 
			SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		return 1;
		};
	return sscanf(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
		SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataName.Format, (char *)StartPosition + DataName.Position);
	};
