// TSRecon.cpp : Implementation of CTSRecon
#include "stdafx.h"

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "ThetaTSReconstruct.h"
#include "ThetaTSRecon.h"
#include "MainSwitch.h"
#include "EditConfig.h"
#include "InteractiveReconstruction.h"
#include "BatchProcessing.h"
#include "ums.h"
#include "..\Common\SySalObject2Structs.h"

// Config stuff

const int TSReconDataN = 41;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo TSReconDataName[TSReconDataN] =
{
	{"InFieldDPos",				"%f",   STRUCT_OFFSET(TSReconData, InField_D_Pos),			"5.0"},
	{"InFieldDSlope",			"%f",   STRUCT_OFFSET(TSReconData, InField_D_Slope),		"0.02"},
	{"OffFieldDPos",			"%f",   STRUCT_OFFSET(TSReconData, OffField_D_Pos),			"10.0"},
	{"OffFieldDSlope",			"%f",   STRUCT_OFFSET(TSReconData, OffField_D_Slope),		"0.03"},
	{"MaxRemeasuresInSegment",	"%d",   STRUCT_OFFSET(TSReconData, MaxRemeasuresInSegment),	"4"},
	{"RemeasureHandling",		"%d",   STRUCT_OFFSET(TSReconData, RemeasureHandling),		"1"},
	{"LocalityCellSize",		"%f",   STRUCT_OFFSET(TSReconData, LocalityCellSize),		"200.0"},
	{"DPos",					"%f",   STRUCT_OFFSET(TSReconData, D_Pos),					"10.0"},
	{"DSlope",					"%f",   STRUCT_OFFSET(TSReconData, D_Slope),				"0.010"},
	{"GrossDPos",				"%f",	STRUCT_OFFSET(TSReconData, Gross_D_Pos),			"20.0"},
	{"GrossDSlope",				"%f",	STRUCT_OFFSET(TSReconData, Gross_D_Slope),			"0.02"},
	{"PrescanMode",				"%d",   STRUCT_OFFSET(TSReconData, PrescanMode),			"2"},
	{"PrescanExtents",			"%f",	STRUCT_OFFSET(TSReconData, PrescanExtents),			"3000."},
	{"PrescanZoneWidth",		"%f",	STRUCT_OFFSET(TSReconData, PrescanZoneWidth),		"3000."},
	{"PrescanLeverArm",			"%f",	STRUCT_OFFSET(TSReconData, PrescanLeverArm),		"1000."},
	{"AlignOnLinked",			"%d",	STRUCT_OFFSET(TSReconData, AlignOnLinked),			"0"},
	{"AlignBeamXSlope",			"%f",	STRUCT_OFFSET(TSReconData, AlignBeamXSlope),		"0."},
	{"AlignBeamYSlope",			"%f",	STRUCT_OFFSET(TSReconData, AlignBeamYSlope),		"0."},
	{"AlignBeamWidth",			"%f",	STRUCT_OFFSET(TSReconData, AlignBeamWidth),			"10."},
	{"MaxIters",				"%d",	STRUCT_OFFSET(TSReconData, MaxIters),				"5"},
	{"MaxMissingSegments",		"%d",   STRUCT_OFFSET(TSReconData, MaxMissingSegments),		"3"},
	{"MinSegments",				"%d",   STRUCT_OFFSET(TSReconData, MinSegments),			"3"},
	{"MinSegmentsRecovery",		"%d",   STRUCT_OFFSET(TSReconData, MinSegmentsRecovery),	"2"},
	{"PassingThroughRadius",	"%f",   STRUCT_OFFSET(TSReconData, PassingThrough_Radius),	"50"},
	{"PassingThroughAngle",		"%f",   STRUCT_OFFSET(TSReconData, PassingThrough_Angle),	"0.4"},
	{"PassingThroughOutLength",	"%f",   STRUCT_OFFSET(TSReconData, PassingThrough_OutLength),	"500"},
	{"VertexXYTol",				"%f",   STRUCT_OFFSET(TSReconData, Vertex_XYTol),			"5.0"},
	{"VertexXYTolIncrease",		"%f",   STRUCT_OFFSET(TSReconData, Vertex_XYTolIncrease),	"0.0"},
	{"VertexLowestZ",			"%f",   STRUCT_OFFSET(TSReconData, Vertex_LowestZ),			"-500.0"},
	{"VertexOverlength",		"%f",   STRUCT_OFFSET(TSReconData, Vertex_Overlength),		"60.0"},
	{"VertexMergeXYTol",		"%f",   STRUCT_OFFSET(TSReconData, Vertex_MergeXYTol),		"20.0"},
	{"VertexMergeZTol",			"%f",   STRUCT_OFFSET(TSReconData, Vertex_MergeZTol),		"60.0"},
	{"VertexZExtrapolation",	"%f",   STRUCT_OFFSET(TSReconData, Vertex_ZExtrapolation),	"10000.0"},
	{"VertexRecoveryZExtrapolation",	"%f",   STRUCT_OFFSET(TSReconData, Vertex_Recovery_ZExtrapolation),	"500.0"},
	{"FinalAlignmentEnable",		"%d",   STRUCT_OFFSET(TSReconData, FinalAlignment_Enable),	"1"},
	{"FinalAlignmentSlopeMeasures",	"%d",   STRUCT_OFFSET(TSReconData, FinalAlignment_SlopeMeasures),	"4"},
	{"FinalAlignmentMaxIters",		"%d",   STRUCT_OFFSET(TSReconData, FinalAlignment_MaxIters),"10"},
	{"FinalAlignmentMaxSlopeDiff","%f",   STRUCT_OFFSET(TSReconData, FinalAlignment_MaxSlopeDiff),	"3.0"},
	{"FinalAlignmentMinSlopeDiff","%f",   STRUCT_OFFSET(TSReconData, FinalAlignment_MinSlopeDiff),	"1.0"},
	{"FinalAlignmentMinEntries",	"%d",   STRUCT_OFFSET(TSReconData, FinalAlignment_MinEntries),	"20.0"},
	{"FinalAlignmentMaxRMS",		"%f",   STRUCT_OFFSET(TSReconData, FinalAlignment_MaxRMS),	"0.010"}
	};

/////////////////////////////////////////////////////////////////////////////
// CTSRecon

CTSRecon::CTSRecon()
{
	CMI.Context = 0;
	CMI.pSaveConfig = 0;
	CMI.pLoadConfig = 0;
	Name[0] = 0;	
	HStatusChangeEvent = 0;		
	strcpy(Slots[0].Name, "Data I/O");
	strcpy(Slots[1].Name, "Predictions Data Source");
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
		for (i = 0; i < TSReconDataN; i++)
			GetData(TSReconDataName[i], &T, VoidConfig.pItems, VoidConfig.CountOfItems);
		};
	OkToRun = true;
}

CTSRecon::~CTSRecon()
{
	CloseHandle(HStatusMutex);
}


STDMETHODIMP CTSRecon::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTSRecon::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTSRecon::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < TSReconDataN) && (GetData(TSReconDataName[i], &T, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < TSReconDataN) 
	{
		OkToRun = false;
		return S_FALSE;
		};
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CTSRecon::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(TSReconDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = TSReconDataN;
	int i;
	for (i = 0; i < TSReconDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			TSReconDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(TSReconDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TSReconDataName[i].Format, *(int *)((char *)&T + TSReconDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TSReconDataName[i].Format, *(float *)((char *)&T + TSReconDataName[i].Position));		
		};
	return S_OK;
}

STDMETHODIMP CTSRecon::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TSReconData Temp;
	int i;
	for (i = 0; i < TSReconDataN; i++) 
		GetData(TSReconDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

	MyDlg.m_InField_D_Pos = Temp.InField_D_Pos; 
	MyDlg.m_InField_D_Slope = Temp.InField_D_Slope;
	MyDlg.m_OffField_D_Pos = Temp.OffField_D_Pos;
	MyDlg.m_OffField_D_Slope = Temp.OffField_D_Slope;
	MyDlg.m_MaxRemeasuresInSegment = Temp.MaxRemeasuresInSegment;
	MyDlg.m_RemeasureHandling = Temp.RemeasureHandling;
	MyDlg.m_LocalityCellSize = Temp.LocalityCellSize;
	MyDlg.m_DPos = Temp.D_Pos;
	MyDlg.m_DSlope = Temp.D_Slope;
	MyDlg.m_GrossDPos = Temp.Gross_D_Pos;
	MyDlg.m_GrossDSlope = Temp.Gross_D_Slope;
	MyDlg.m_PrescanMode = Temp.PrescanMode;
	MyDlg.m_PrescanExtents = Temp.PrescanExtents;
	MyDlg.m_PrescanZoneWidth = Temp.PrescanZoneWidth;
	MyDlg.m_PrescanLeverArm = Temp.PrescanLeverArm;
	MyDlg.m_AlignOnLinked = Temp.AlignOnLinked;
	MyDlg.m_AlignBeamXSlope = Temp.AlignBeamXSlope;
	MyDlg.m_AlignBeamYSlope = Temp.AlignBeamYSlope;
	MyDlg.m_AlignBeamWidth = Temp.AlignBeamWidth;
	MyDlg.m_MaxIterations = Temp.MaxIters;
	MyDlg.m_MaxMissingSegments = Temp.MaxMissingSegments;
	MyDlg.m_MinSegments = Temp.MinSegments;
	MyDlg.m_MinSegmentsRecovery = Temp.MinSegmentsRecovery;
	MyDlg.m_FinalAlignment_Enable = Temp.FinalAlignment_Enable;
	MyDlg.m_FinalAlignment_SlopeMeasures = Temp.FinalAlignment_SlopeMeasures;
	MyDlg.m_FinalAlignment_MaxIters = Temp.FinalAlignment_MaxIters;
	MyDlg.m_FinalAlignment_MaxSlopeDiff = Temp.FinalAlignment_MaxSlopeDiff;
	MyDlg.m_FinalAlignment_MinSlopeDiff = Temp.FinalAlignment_MinSlopeDiff;
	MyDlg.m_FinalAlignment_MinEntries = Temp.FinalAlignment_MinEntries;
	MyDlg.m_FinalAlignment_MaxRMS = Temp.FinalAlignment_MaxRMS;
	MyDlg.m_PassingThrough_Radius = Temp.PassingThrough_Radius;
	MyDlg.m_PassingThrough_Angle = Temp.PassingThrough_Angle;
	MyDlg.m_PassingThrough_OutLength = Temp.PassingThrough_OutLength;
	MyDlg.m_Vertex_XYTol = Temp.Vertex_XYTol;
	MyDlg.m_Vertex_XYTolIncrease = Temp.Vertex_XYTolIncrease;
	MyDlg.m_Vertex_LowestZ = Temp.Vertex_LowestZ;
	MyDlg.m_Vertex_Overlength = Temp.Vertex_Overlength;
	MyDlg.m_Vertex_MergeXYTol = Temp.Vertex_MergeXYTol;
	MyDlg.m_Vertex_MergeZTol = Temp.Vertex_MergeZTol;
	MyDlg.m_Vertex_ZExtrapolation = Temp.Vertex_ZExtrapolation;
	MyDlg.m_Vertex_Recovery_ZExtrapolation = Temp.Vertex_Recovery_ZExtrapolation;
	if (MyDlg.DoModal() == IDOK)
	{
		Temp.InField_D_Pos = MyDlg.m_InField_D_Pos; 
		Temp.InField_D_Slope = MyDlg.m_InField_D_Slope;
		Temp.OffField_D_Pos = MyDlg.m_OffField_D_Pos;
		Temp.OffField_D_Slope = MyDlg.m_OffField_D_Slope;
		Temp.MaxRemeasuresInSegment = MyDlg.m_MaxRemeasuresInSegment;
		Temp.RemeasureHandling = MyDlg.m_RemeasureHandling;
		Temp.LocalityCellSize = MyDlg.m_LocalityCellSize;
		Temp.D_Pos = MyDlg.m_DPos;
		Temp.D_Slope = MyDlg.m_DSlope;
		Temp.Gross_D_Pos = MyDlg.m_GrossDPos;
		Temp.Gross_D_Slope = MyDlg.m_GrossDSlope;
		Temp.PrescanMode = MyDlg.m_PrescanMode;
		Temp.PrescanExtents = MyDlg.m_PrescanExtents;
		Temp.PrescanZoneWidth = MyDlg.m_PrescanZoneWidth;
		Temp.PrescanLeverArm = MyDlg.m_PrescanLeverArm;
		Temp.AlignOnLinked = MyDlg.m_AlignOnLinked;
		Temp.AlignBeamXSlope = MyDlg.m_AlignBeamXSlope;
		Temp.AlignBeamYSlope = MyDlg.m_AlignBeamYSlope;
		Temp.AlignBeamWidth = MyDlg.m_AlignBeamWidth;
		Temp.MaxIters = MyDlg.m_MaxIterations;
		Temp.MaxMissingSegments = MyDlg.m_MaxMissingSegments;
		Temp.MinSegments = MyDlg.m_MinSegments;
		Temp.MinSegmentsRecovery = MyDlg.m_MinSegmentsRecovery;
		Temp.FinalAlignment_Enable = MyDlg.m_FinalAlignment_Enable;
		Temp.FinalAlignment_SlopeMeasures = MyDlg.m_FinalAlignment_SlopeMeasures;
		Temp.FinalAlignment_MaxIters = MyDlg.m_FinalAlignment_MaxIters;
		Temp.FinalAlignment_MaxSlopeDiff = MyDlg.m_FinalAlignment_MaxSlopeDiff;
		Temp.FinalAlignment_MinSlopeDiff = MyDlg.m_FinalAlignment_MinSlopeDiff;
		Temp.FinalAlignment_MinEntries = MyDlg.m_FinalAlignment_MinEntries;
		Temp.FinalAlignment_MaxRMS = MyDlg.m_FinalAlignment_MaxRMS;
		Temp.PassingThrough_Radius = MyDlg.m_PassingThrough_Radius;
		Temp.PassingThrough_Angle = MyDlg.m_PassingThrough_Angle;
		Temp.PassingThrough_OutLength = MyDlg.m_PassingThrough_OutLength;
		Temp.Vertex_XYTol = MyDlg.m_Vertex_XYTol;
		Temp.Vertex_XYTolIncrease = MyDlg.m_Vertex_XYTolIncrease;
		Temp.Vertex_LowestZ = MyDlg.m_Vertex_LowestZ;
		Temp.Vertex_Overlength = MyDlg.m_Vertex_Overlength;
		Temp.Vertex_MergeXYTol = MyDlg.m_Vertex_MergeXYTol;
		Temp.Vertex_MergeZTol = MyDlg.m_Vertex_MergeZTol;
		Temp.Vertex_ZExtrapolation = MyDlg.m_Vertex_ZExtrapolation;
		Temp.Vertex_Recovery_ZExtrapolation = MyDlg.m_Vertex_Recovery_ZExtrapolation;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(TSReconDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = TSReconDataN;
		int i;
		for (i = 0; i < TSReconDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				TSReconDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(TSReconDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TSReconDataName[i].Format, *(int *)((char *)&Temp + TSReconDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TSReconDataName[i].Format, *(float *)((char *)&Temp + TSReconDataName[i].Position));
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CTSRecon::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CTSRecon::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CTSRecon::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CTSRecon::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CTSRecon::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CTSRecon::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Eta Tracking", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTSRecon::SyncExec()
{
	// TODO: Add your implementation code here

	//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


STDMETHODIMP CTSRecon::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CTSRecon::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return E_NOTIMPL;
}

STDMETHODIMP CTSRecon::AsyncWait()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CTSRecon::AsyncPause()
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

STDMETHODIMP CTSRecon::AsyncStop()
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

STDMETHODIMP CTSRecon::AsyncResume()
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

STDMETHODIMP CTSRecon::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	
	try
	{
		if (Slots[0].pUnknown)
		{
			ISySalDataIO *iIO;
			if (Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO) == S_OK) iIO->Release();
			else throw 0;
			}
		else throw 0;
		if (Slots[1].pUnknown)
		{
			ISySalDataIO *iPr;
			if (Slots[1].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iPr) == S_OK) iPr->Release();
			else throw 1;
			}
		}
	catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
		return S_OK;
		};

	*pWrongConn = -1;
	*pRetCode = (OkToRun) ? SYSAL_READYSTATUS_READY : SYSAL_READYSTATUS_INCOMPLETE_CONFIG;
	return S_OK;
}

UINT WINAPI CTSRecon::AsyncExecHook(void *pOwner)
{
	return ((CTSRecon *)pOwner)->AsyncExec();
}

UINT CTSRecon::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	ISySalDataIO *iIO = 0, *iPr = 0;

	if (Slots[0].pUnknown) Slots[0].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO);
	if (Slots[1].pUnknown) Slots[1].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iPr);

	UINT Selection = MS_SEL_EXIT;
	do
	{
		CMainSwitch MyDlg(&m_hDefWnd);
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

			case MS_SEL_INTERACTIVE:
									{
										CInteractiveReconstruction InteractiveReconstruction(&m_hDefWnd, iIO, iPr, &T, this, &CMI);
										if (InteractiveReconstruction.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_BATCH:
									{
										CBatchProcessing BatchProc(&m_hDefWnd, iIO, &T);
										if (BatchProc.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;
			};
		}
	while (Selection != MS_SEL_EXIT);

	if (iPr) iPr->Release();
	if (iIO) iIO->Release();
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	pAsyncExec = 0;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return 0;
}

// ISySalObject2
STDMETHODIMP CTSRecon::SetConfigManagerInterface(ConfigManagerInterface *pCMI)
{
	CMI = *pCMI;
	return S_OK;
}

STDMETHODIMP CTSRecon::GetCLSID(CLSID *pCLSID)
{
	*pCLSID = CLSID_ThetaTSReconstruct;
	return S_OK;	
}

// INTERNAL FUNCTIONS

int CTSRecon::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
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
