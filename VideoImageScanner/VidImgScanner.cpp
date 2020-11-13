// VidImgScanner.cpp : Implementation of CVidImgScanner
#include "stdafx.h"
#include "VideoImageScanner.h"
#include "VidImgScanner.h"
#include "MainSwitch.h"
#include "ClusterAnalysis.h"
#include "InteractiveTracking.h"
#include "BatchProcessing.h"
#include "EditConfigDlg.h"

// Config stuff

const int VideoImageDataN = 13;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo VideoImageDataName[VideoImageDataN] =
{
	{"RelativeThreshold",   "%d",   STRUCT_OFFSET(VideoImageData, RelativeThreshold),	"0"},
	{"Equalization",		"%d",   STRUCT_OFFSET(VideoImageData, Equalization),		"0"},
	{"Threshold0",			"%d",	STRUCT_OFFSET(VideoImageData, Threshold[0]),		"0"},
	{"Threshold1",			"%d",	STRUCT_OFFSET(VideoImageData, Threshold[1]),		"0"},
	{"MaxGrains",			"%d",	STRUCT_OFFSET(VideoImageData, MaxGrains),			"100000"},
	{"StartLayer0",		"%d",   STRUCT_OFFSET(VideoImageData, StartLayer[0]),		"0"},
	{"StartLayer1",		"%d",   STRUCT_OFFSET(VideoImageData, StartLayer[1]),		"0"},
	{"EndLayer0",			"%d",   STRUCT_OFFSET(VideoImageData, EndLayer[0]),			"100"},
	{"EndLayer1",			"%d",   STRUCT_OFFSET(VideoImageData, EndLayer[1]),			"100"},
	{"MaxTracks",			"%d",   STRUCT_OFFSET(VideoImageData, MaxTracks),			"1000"},
	{"MaxFlatTracks",		"%d",   STRUCT_OFFSET(VideoImageData, MaxFlatTracks),		"100"},
	{"MaxFlatStripsInTrack",	"%d",   STRUCT_OFFSET(VideoImageData, MaxFlatStripsInTrack), "20"},
	{"Shrinkage",			"%f",   STRUCT_OFFSET(VideoImageData, Shrinkage),			"1.9"}
	};

/////////////////////////////////////////////////////////////////////////////
// CVidImgScanner

CVidImgScanner::CVidImgScanner()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;		
	strcpy(Slots[0].Name, "Objective");
	strcpy(Slots[1].Name, "Cluster Finder");
	strcpy(Slots[2].Name, "Tracker");
	strcpy(Slots[3].Name, "Track Fitter");
	strcpy(Slots[4].Name, "Data I/O");
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
		for (i = 0; i < VideoImageDataN; i++)
			GetData(VideoImageDataName[i], &V, VoidConfig.pItems, VoidConfig.CountOfItems);
		};
}

CVidImgScanner::~CVidImgScanner()
{
	CloseHandle(HStatusMutex);
}


STDMETHODIMP CVidImgScanner::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVidImgScanner::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVidImgScanner::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < VideoImageDataN) && (GetData(VideoImageDataName[i], &V, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < VideoImageDataN) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CVidImgScanner::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(VideoImageDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = VideoImageDataN;
	int i;
	for (i = 0; i < VideoImageDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			VideoImageDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(VideoImageDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, VideoImageDataName[i].Format, *(int *)((char *)&V + VideoImageDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, VideoImageDataName[i].Format, *(float *)((char *)&V + VideoImageDataName[i].Position));		
		};
	return S_OK;	
}

STDMETHODIMP CVidImgScanner::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VideoImageData Temp;
	int i;
	for (i = 0; i < VideoImageDataN; i++) 
		GetData(VideoImageDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfigDlg MyDlg(&Owner);
	MyDlg.m_RelativeThreshold = Temp.RelativeThreshold;
	MyDlg.m_Equalization = Temp.Equalization;
	MyDlg.m_Threshold0 = Temp.Threshold[0];
	MyDlg.m_Threshold1 = Temp.Threshold[1];
	MyDlg.m_MaxGrains = Temp.MaxGrains;
	MyDlg.m_StartLayer0 = Temp.StartLayer[0];
	MyDlg.m_StartLayer1 = Temp.StartLayer[1];
	MyDlg.m_EndLayer0 = Temp.EndLayer[0];
	MyDlg.m_EndLayer1 = Temp.EndLayer[1];
	MyDlg.m_Shrinkage = Temp.Shrinkage;
	MyDlg.m_MaxTracks = Temp.MaxTracks;
	MyDlg.m_MaxFlatTracks = Temp.MaxFlatTracks;
	MyDlg.m_MaxFlatStripsInTrack = Temp.MaxFlatStripsInTrack;
	if (MyDlg.DoModal() == IDOK)
	{
		Temp.RelativeThreshold = MyDlg.m_RelativeThreshold;
		Temp.Equalization = MyDlg.m_Equalization;
		Temp.Threshold[0] = MyDlg.m_Threshold0;
		Temp.Threshold[1] = MyDlg.m_Threshold1;
		Temp.MaxGrains = MyDlg.m_MaxGrains;
		Temp.StartLayer[0] = MyDlg.m_StartLayer0;
		Temp.StartLayer[1] = MyDlg.m_StartLayer1;
		Temp.EndLayer[0] = MyDlg.m_EndLayer0;
		Temp.EndLayer[1] = MyDlg.m_EndLayer1;
		Temp.Shrinkage = MyDlg.m_Shrinkage;
		Temp.MaxTracks = MyDlg.m_MaxTracks;
		Temp.MaxFlatTracks = MyDlg.m_MaxFlatTracks;
		Temp.MaxFlatStripsInTrack = MyDlg.m_MaxFlatStripsInTrack;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(VideoImageDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = VideoImageDataN;
		int i;
		for (i = 0; i < VideoImageDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				VideoImageDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(VideoImageDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, VideoImageDataName[i].Format, *(int *)((char *)&Temp + VideoImageDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, VideoImageDataName[i].Format, *(float *)((char *)&Temp + VideoImageDataName[i].Position));
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CVidImgScanner::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CVidImgScanner::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CVidImgScanner::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CVidImgScanner::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CVidImgScanner::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CVidImgScanner::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Video Image Scanner", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVidImgScanner::SyncExec()
{
	// TODO: Add your implementation code here

//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	MessageBox(AfxGetMainWnd()->m_hWnd, "Simple Sync Exec Example!!!", "Cuckoo!", MB_OK);
	return S_OK;
}


STDMETHODIMP CVidImgScanner::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CVidImgScanner::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return E_NOTIMPL;
}

STDMETHODIMP CVidImgScanner::AsyncWait()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CVidImgScanner::AsyncPause()
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

STDMETHODIMP CVidImgScanner::AsyncStop()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
		else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CVidImgScanner::AsyncResume()
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

STDMETHODIMP CVidImgScanner::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	try
	{
		if (Slots[0].pUnknown)
		{
			IObjective *iOb;
			if (Slots[0].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb) == S_OK) iOb->Release();
			else throw 0;
			}
		else throw 0;
		if (Slots[1].pUnknown)
		{
			IClusterFinder *iCl;
			if (Slots[1].pUnknown->QueryInterface(IID_IClusterFinder, (void **)&iCl) == S_OK) iCl->Release();
			else throw 1;
			}
		else throw 1;
		if (Slots[2].pUnknown)
		{
			ITracker *iTr;
			if (Slots[2].pUnknown->QueryInterface(IID_ITracker, (void **)&iTr) == S_OK) iTr->Release();
			else throw 2;
			};
		if (Slots[3].pUnknown)
		{
			ITrackFitter *iFt;
			if (Slots[3].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt) == S_OK) iFt->Release();
			else throw 3;
			};
		if (Slots[4].pUnknown)
		{
			ISySalDataIO *iIO;
			if (Slots[4].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO) == S_OK) iIO->Release();
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

UINT WINAPI CVidImgScanner::AsyncExecHook(void *pOwner)
{
	return ((CVidImgScanner *)pOwner)->AsyncExec();
}

UINT CVidImgScanner::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	IObjective *iOb = 0;
	IClusterFinder *iCl = 0;
	ITracker *iTr = 0;
	ITrackFitter *iFt = 0;
	ISySalDataIO *iIO = 0;

	if (Slots[0].pUnknown) Slots[0].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb);
	if (Slots[1].pUnknown) Slots[1].pUnknown->QueryInterface(IID_IClusterFinder, (void **)&iCl);
	if (Slots[2].pUnknown) Slots[2].pUnknown->QueryInterface(IID_ITracker, (void **)&iTr);
	if (Slots[3].pUnknown) Slots[3].pUnknown->QueryInterface(IID_ITrackFitter, (void **)&iFt);
	if (Slots[4].pUnknown) Slots[4].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO);

	int Selection = MS_SEL_EXIT;
	do
	{
		CMainSwitch MyDlg(&m_hDefWnd);
		MyDlg.m_BatchProcessingEnable = false;
		MyDlg.m_ClusterAnalysisEnable = (iCl != 0) && (iOb != 0);
		MyDlg.m_InteractiveTrackingEnable = (iTr != 0) && (iOb != 0);
		MyDlg.m_BatchProcessingEnable = (iIO != 0) && (iFt != 0) && (iTr != 0) && (iOb != 0);
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

			case MS_SEL_CLUSTERANALYSIS:
									{
										CClusterAnalysis ClAnDlg(&m_hDefWnd, iIO, iCl, iOb);
										if (ClAnDlg.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_INTERACTIVETRACKING:
									{
										CInteractiveTracking IntTkDlg(&m_hDefWnd, iIO, iCl, iOb, iTr, iFt);
										if (IntTkDlg.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_BATCHPROCESSING:
									{
										CBatchProcessing BatchProcDlg(&m_hDefWnd, &V, iIO, iCl, iOb, iTr, iFt);
										if (BatchProcDlg.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			};
		}
	while (Selection != MS_SEL_EXIT);

	if (iIO) iIO->Release();
	if (iFt) iFt->Release();
	if (iTr) iTr->Release();
	if (iCl) iCl->Release();
	if (iOb) iOb->Release();
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	pAsyncExec = 0;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return 0;
}

// INTERNAL FUNCTIONS

int CVidImgScanner::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
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
