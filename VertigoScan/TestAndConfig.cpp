// TestAndConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TestAndConfig.h"
#include "..\Common\Connection.h"
#include "VertigoScanClass.h"
#include "Globals.h"
#include <afxdlgs.h>
#include "EditGridOptions.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAndConfig dialog


CTestAndConfig::CTestAndConfig(HWND *phwnd, ISySalObject *iself, ISySalDataIO *iio, IStage *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor *ivp, ITracker *itk1, ITrackFitter *ift1, 
	ITracker *itk2, ITrackFitter *ift2, ISheetMap *ism, ConfigManagerInterface *pcmi, IRemoteControlServer *ircs, 
	ConfigData &c, CWnd* pParent /*=NULL*/)
	: CDialog(CTestAndConfig::IDD, pParent), phWnd(phwnd), CVertigoScanner(iself, iio, ist, iob, 
		ifg, ivp, itk1, ift1, itk2, ift2, ism, c), pCMI(pcmi), iRCS(ircs)
{
	//{{AFX_DATA_INIT(CTestAndConfig)
	m_GrainFile = _T("");
	m_DumpGrainsToASCII = FALSE;
	m_EnableRemoteControl = FALSE;
	m_AutoSave = FALSE;
	//}}AFX_DATA_INIT
	GridXStep = GridYStep = 100;
	ShowGrid = false;
	HasRun = false;
	RunStatus = false;
	RemoteControlStatus = false;
	Terminate = false;
	pSF = 0;
	pGrabStructs = 0;
	pTimeStructs = 0;
	pFocusData = 0;
	CheckInit();
}


CTestAndConfig::~CTestAndConfig()
{
	Free();
	if (RemoteControlStatus && iRCS) iRCS->Disconnect();
	if (pSF) delete pSF;
	if (pGrabStructs) GlobalFree(pGrabStructs);
	if (pTimeStructs) GlobalFree(pTimeStructs);
	if (pFocusData) GlobalFree(pFocusData);
}


void CTestAndConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestAndConfig)
	DDX_Control(pDX, IDC_TC_OBJLIST, m_ObjList);
	DDX_Text(pDX, IDC_TC_GRAINFILE, m_GrainFile);
	DDX_Check(pDX, IDC_TC_DUMPALLGRAINSTOASCII, m_DumpGrainsToASCII);
	DDX_Check(pDX, IDC_TC_ENABLEREMOTECONTROL, m_EnableRemoteControl);
	DDX_Check(pDX, IDC_TC_AUTOSAVE, m_AutoSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestAndConfig, CDialog)
	//{{AFX_MSG_MAP(CTestAndConfig)
	ON_BN_CLICKED(IDC_TC_START, OnStart)
	ON_BN_CLICKED(IDC_TC_STOP, OnStop)
	ON_BN_CLICKED(IDC_TC_GOTOFIELD, OnGoToField)
	ON_BN_CLICKED(IDC_TC_REFRESH, OnRefresh)
	ON_BN_CLICKED(IDC_TC_DUMPTIMESTRUCT, OnDumpTimeStruct)
	ON_BN_CLICKED(IDC_TC_EDITCONFIG, OnEditConfig)
	ON_BN_CLICKED(IDC_TC_SAVECONFIG, OnSaveConfig)
	ON_BN_CLICKED(IDC_TC_SHOWSTAGEMON, OnShowStageMonitor)
	ON_BN_CLICKED(IDC_TC_DUMPGRABSTRUCT, OnDumpGrabStruct)
	ON_BN_CLICKED(IDC_TC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_TC_GRIDOPTIONS, OnGridOptions)
	ON_BN_CLICKED(IDC_TC_TOGGLEGRID, OnToggleGrid)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_TC_DUMPFOCUSDATA, OnDumpFocusData)
	ON_BN_CLICKED(IDC_TC_ENABLEREMOTECONTROL, OnEnableRemoteControl)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
	ON_MESSAGE(UM_RCS_CONNECT_DISCONNECT, OnRCSConnectDisconnect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAndConfig message handlers

BOOL CTestAndConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;	

	CRect ClRect;
	m_ObjList.GetClientRect(&ClRect);
	m_ObjList.DeleteColumn(0);
	m_ObjList.InsertColumn(0, "Connection", LVCFMT_LEFT, 200);
	m_ObjList.InsertColumn(1, "Class", LVCFMT_RIGHT, ClRect.Width() - 200 - GetSystemMetrics(SM_CXHTHUMB));
	int i;
	int NConn = 0;
	char ConnName[SYSAL_MAX_CONN_NAME_LEN + 1];
	char ClassName[SYSAL_MAX_CONN_NAME_LEN + 1];

	iSelf->GetClassName(ClassName);
	m_ObjList.InsertItem(0, "-- SELF --");
	m_ObjList.SetItemText(0, 1, ClassName);

	iSelf->GetNumberOfConnections(&NConn);
	for (i = 0; i < NConn; i++)
	{
		ConnName[SYSAL_MAX_CONN_NAME_LEN] = 0;
		ClassName[SYSAL_MAX_CONN_NAME_LEN] = 0;
		SySalConnection MyConn;
		iSelf->GetConnection(i, &MyConn);
		strncpy(ConnName, MyConn.Name, SYSAL_MAX_CONN_NAME_LEN);
		ISySalObject *iTempOb = 0;
		if (MyConn.pUnknown && MyConn.pUnknown->QueryInterface(IID_ISySalObject, (void **)&iTempOb) == S_OK)
		{
			iTempOb->GetClassName(ClassName);
			iTempOb->Release();
			}
		else
		{
			ConnName[0] = ClassName[0] = 0;
			};
		m_ObjList.InsertItem(i + 1, ConnName);
		m_ObjList.SetItemText(i + 1, 1, ClassName);
		};
	m_ObjList.SetSelectionMark(0);

	pSF = new CSelectField(ApplyField, this, &Frag, this);
	pSF->Create(IDD_SELECT_FIELD, this);
	pSF->ShowWindow(SW_HIDE);
	EnableControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CTestAndConfig::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) 
	{
		case SYSAL_ASYNC_STATUS_IDLE:	{
											Terminate = true;
											if (RunStatus)
											{
												pThread->PostThreadMessage(UM_CHANGE_STATUS, UM_STOP, 0);
												}
											else EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
											};
										break;

		case UM_STOP:					{		
											RunStatus = false;
											if (Terminate) EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
											else 
											{
												HasRun = true;
												EnableControls();
												ComputeStatistics();
												};
											};
										break;
		};
	return 0;
}

LRESULT CTestAndConfig::OnRCSConnectDisconnect(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		RemoteControlStatus = false;
		m_EnableRemoteControl = FALSE;
		}
	else
	{
		RemoteControlStatus = true;
		m_EnableRemoteControl = TRUE;
		}
	EnableControls();
	UpdateData(FALSE);
	return 0;
	};

void CTestAndConfig::OnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!OkToRun)
	{
		MessageBox("Cannot run", "Error", MB_ICONERROR | MB_OK);
		return;
		};

	Frag.Fragment.StartView = 0;
	Frag.Fragment.CountOfViews = C.XFields * C.YFields;
	Frag.Fragment.Index = 1;
	Frag.Fragment.CodingMode = VS_COMPRESSION_NULL;
	CCount[0] = CCount[1] = 0;
	ProcessVariables.Field = 0;
	ZeroMemory(pGrabStructs, sizeof(t_GrabStruct) * C.XFields * C.YFields * C.VLayers * 2);
	ZeroMemory(pTimeStructs, sizeof(t_TimeStruct) * C.XFields * C.YFields * 2);
	GetDlgItem(IDC_TC_TESTPROGRESS)->SendMessage(PBM_SETRANGE32, 0, C.XFields * C.YFields * ((C.ScanningScheme == SCANNING_SCHEME_TWO_SIDES) ? 2 : 1));
	GetDlgItem(IDC_TC_TESTPROGRESS)->SendMessage(PBM_SETPOS, 0, 0);
	RunStatus = true;
	EnableControls();
	Frag.Hdr.ID.Part[3]++;
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iStOb->EnableMonitor(true);
	MessageBox("Place the stage at the top surface of the plastic base and press OK", "Help Request", MB_ICONQUESTION | MB_OK);
	iStOb->EnableMonitor(false);
	pThread = AfxBeginThread((AFX_THREADPROC)ThreadHook, this, THREAD_PRIORITY_NORMAL, 65536, 0, NULL);
}

void CTestAndConfig::OnStop() 
{
	// TODO: Add your control notification handler code here
	pThread->PostThreadMessage(UM_CHANGE_STATUS, UM_STOP, 0);	
}

void CTestAndConfig::OnGoToField() 
{
	// TODO: Add your control notification handler code here
	pSF->ShowWindow(SW_SHOW);
}

void CTestAndConfig::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	int Transp;
	iFG->GetColorCode(VC_TRANSPARENT, &Transp);
	iFG->Clear(Transp);	
	if (ShowGrid) ShowAlignmentGrid(true);
}

void CTestAndConfig::OnEditConfig() 
{
	// TODO: Add your control notification handler code here
	int idsel = m_ObjList.GetSelectionMark();
	if (idsel >= 0)
	{
		ISySalObject *iObj = 0;
		if (idsel) 
		{
			SySalConnection Conn;
			iSelf->GetConnection(idsel - 1, &Conn);
			Conn.pUnknown->QueryInterface(IID_ISySalObject, (void **)&iObj);
			}
		else 
		{
			iObj = iSelf;
			iObj->AddRef();
			};
		SySalConfig Temp;
		Temp.pItems = 0;
		Temp.CountOfItems = 0;
		Temp.Name[0] = 0;
		if (iObj->GetConfig(&Temp) == S_OK)
		{
			HRESULT HRes = (iObj == iSelf) ? EditConfig(&Temp, this) : iObj->EditConfig(&Temp, (HSySalHANDLE)m_hWnd);
			if (HRes == S_OK) 
			{
				iObj->SetConfig(&Temp);
				if (iObj == iSelf) CheckInit();
				};
			}
		else MessageBox("Can't get object configuration", "Error", MB_ICONERROR | MB_OK);
		if (Temp.pItems) CoTaskMemFree(Temp.pItems);
		iObj->Release();
		};
}

void CTestAndConfig::OnSaveConfig() 
{
	// TODO: Add your control notification handler code here
	if (!pCMI->pSaveConfig) return;
	int idsel = m_ObjList.GetSelectionMark();
	if (idsel >= 0)
	{
		HRESULT HRes;
		ISySalObject *iObj = 0;
		if (idsel) 
		{
			SySalConnection Conn;
			iSelf->GetConnection(idsel - 1, &Conn);
			Conn.pUnknown->QueryInterface(IID_ISySalObject, (void **)&iObj);
			}
		else 
		{
			iObj = iSelf;
			iObj->AddRef();
			};
		SySalConfig Temp;
		Temp.pItems = 0;
		Temp.CountOfItems = 0;
		Temp.Name[0] = 0;
		HRes = iObj->GetConfig(&Temp);
		iObj->Release();

		if (HRes == S_OK) pCMI->pSaveConfig(pCMI->Context, &Temp, Temp.Name);

		if (Temp.pItems) CoTaskMemFree(Temp.pItems);
		};	
}


void CTestAndConfig::CheckInit()
{
	HasRun = false;
	OkToRun = false;
	CString Temp;
	UINT Err;
	Free();
	switch ((Err = Init(true)))
	{
		case VSERR_OK:				OkToRun = true;
									break;

		case VSERR_WRONG_CONN:		Temp.Format("Connection error\r\nError code: %X", Err & 0x00FFFFFF);
									break;

		case VSERR_WRONG_CONFIG:	Temp.Format("Configuration error\r\nError code: %X", Err & 0x00FFFFFF);
									break;

		case VSERR_MEMORY_ALLOC:	Temp.Format("Memory allocation error\r\nError code: %X", Err & 0x00FFFFFF);
									break;

		case VSERR_SCANNING_ERROR:	Temp.Format("Scanning error\r\nError code: %X", Err & 0x00FFFFFF);
									break;

		case VSERR_CANTRUN:			Temp.Format("Cannot run\r\nError code: %X", Err & 0x00FFFFFF);
									break;

		default:					Temp.Format("Unknown Error");
									break;
		};

	if (pGrabStructs) 
	{
		GlobalFree(pGrabStructs);
		};
	pGrabStructs = (t_GrabStruct *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(t_GrabStruct) * C.VLayers * C.XFields * C.YFields);
	if (!pGrabStructs) 
	{
		OkToRun = false;
		Temp = "Grab monitoring structs allocation error";
		};

	if (pTimeStructs) 
	{
		GlobalFree(pTimeStructs);
		};
	pTimeStructs = (t_TimeStruct *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(t_TimeStruct) * C.XFields * C.YFields);
	if (!pTimeStructs) 
	{
		OkToRun = false;
		Temp = "Time monitoring structs allocation error";
		};
	
	if (pFocusData) 
	{
		GlobalFree(pFocusData);
		};
	pFocusData = (t_ProcessVariables::t_Rec *)GlobalAlloc(GMEM_FIXED, sizeof(t_ProcessVariables::t_Rec) * ProcessVariables.FocusSamples);
	if (!pFocusData) 
	{
		OkToRun = false;
		Temp = "Focus monitoring data allocation error";
		};

	if (!OkToRun)
		MessageBox(Temp, "Initialization error", MB_ICONERROR | MB_OK);
}

void CTestAndConfig::EnableControls()
{
	if (RunStatus || RemoteControlStatus) pSF->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TC_ENABLEREMOTECONTROL)->EnableWindow(!RunStatus && iRCS);
	GetDlgItem(IDC_TC_START)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_STOP)->EnableWindow(RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_GOTOFIELD)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_AUTOSAVE)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_REFRESH)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_SHOWSTAGEMON)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_SAVE)->EnableWindow(!RunStatus && HasRun && !RemoteControlStatus);
	GetDlgItem(IDC_TC_TOGGLEGRID)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_GRIDOPTIONS)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_DUMPTIMESTRUCT)->EnableWindow(!RunStatus && HasRun && !RemoteControlStatus);
	GetDlgItem(IDC_TC_DUMPGRABSTRUCT)->EnableWindow(!RunStatus && HasRun && !RemoteControlStatus);
	GetDlgItem(IDC_TC_DUMPFOCUSDATA)->EnableWindow(!RunStatus && HasRun && !RemoteControlStatus);
	GetDlgItem(IDC_TC_EDITCONFIG)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDC_TC_SAVECONFIG)->EnableWindow(!RunStatus && !RemoteControlStatus);
	GetDlgItem(IDCANCEL)->EnableWindow(!RunStatus && !RemoteControlStatus);
}

void CTestAndConfig::OnShowStageMonitor() 
{
	// TODO: Add your control notification handler code here
	iStOb->EnableMonitor(true);	
}

bool CTestAndConfig::ShouldStop()
{
	MSG Msg;
	if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
		if (Msg.message == UM_CHANGE_STATUS && Msg.wParam == UM_STOP) return true;
	return false;
}

UINT CTestAndConfig::ThreadHook(void *pOwner)
{
	CTestAndConfig *This = (CTestAndConfig *)pOwner;
	float StartX, StartY;
	This->iSt->GetPos(0, &StartX);
	This->iSt->GetPos(1, &StartY);
	This->VPLock();
	UINT Ret = This->Scan(StartX, StartY);
	This->VPUnlock();
	This->iStOb->EnableMonitor(true);
	if (Ret == VSSCAN_OK)
	{
		UINT ExtErrorInfo;
		if (This->m_AutoSave && This->iIO->Write(0, (BYTE *)&This->Frag, &ExtErrorInfo, 0) != S_OK)
		{
			CString Temp;
			Temp.Format("Error in AutoSave.\r\nError code: %08X", ExtErrorInfo);
			::MessageBox(0, Temp, "File Error", MB_ICONERROR | MB_OK);
			};
		};
	((CTestAndConfig *)pOwner)->PostMessage(UM_CHANGE_STATUS, UM_STOP);
	return Ret;
}

UINT CTestAndConfig::FieldStartNotify()
{
	char string[64] = "";
	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].StartField = GetTickCount();
	if (!ProcessVariables.Field && (ProcessVariables.IsTop || (C.ScanningScheme == SCANNING_SCHEME_BOTTOMSIDE))) StartTime = pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].StartField;
	switch (C.ScanningScheme) 
	{
		case SCANNING_SCHEME_TOPSIDE:
		case SCANNING_SCHEME_BOTTOMSIDE:		
		case SCANNING_SCHEME_BOTH_IN_FIELD:		sprintf(string, "Field: %d/%d", ProcessVariables.Field, C.XFields * C.YFields);
												GetDlgItem(IDC_TC_TESTPROGRESS)->SendMessage(PBM_SETPOS, ProcessVariables.Field, 0);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			sprintf(string, "Field: %d/%d%c", ProcessVariables.Field, C.XFields * C.YFields, ProcessVariables.IsTop ? 'T' : 'B');
												GetDlgItem(IDC_TC_TESTPROGRESS)->SendMessage(PBM_SETPOS, ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields)), 0);
												break;
		}
	GetDlgItem(IDC_TC_FIELDN)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCSTR)string);	
	return VSERR_OK;
}

UINT CTestAndConfig::EndNotify()
{
	char string[64] = "";
	EndTime = GetTickCount();
	switch (C.ScanningScheme) 
	{
		case SCANNING_SCHEME_TOPSIDE:
		case SCANNING_SCHEME_BOTTOMSIDE:		
		case SCANNING_SCHEME_BOTH_IN_FIELD:		sprintf(string, "Field: %d/%d", ProcessVariables.Field, C.XFields * C.YFields);
												GetDlgItem(IDC_TC_TESTPROGRESS)->SendMessage(PBM_SETPOS, ProcessVariables.Field, 0);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			sprintf(string, "Field: %d/%d%c", ProcessVariables.Field, C.XFields * C.YFields, ProcessVariables.IsTop ? 'T' : 'B');
												GetDlgItem(IDC_TC_TESTPROGRESS)->SendMessage(PBM_SETPOS, ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields)), 0);
												break;
		}
	GetDlgItem(IDC_TC_FIELDN)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCSTR)string);	
	return VSERR_OK;
}

UINT CTestAndConfig::GetRelevantZs(VS_View::t_RelevantZs &F, UINT field, bool istop)
{
	static UINT Ret = VSSCAN_OK;
	if (field != 0) return Ret;
	if (!istop && (C.ScanningScheme != SCANNING_SCHEME_BOTTOMSIDE)) return Ret;
	float X, Y, Z;
	IsFocusing = true;
	iSt->GetPos(0, &X);
	iSt->GetPos(1, &Y);
	iSt->GetPos(2, &Z);
	F.TopInt = Z;
	F.TopExt = Z + C.VStep;
	F.BottomInt = Z - C.BaseThickness;
	F.BottomExt = F.BottomInt - C.VStep;
	Ret = CVertigoScanner::GetFocus(X, Y, F);
	IsFocusing = false;
	return Ret;
	};

void CTestAndConfig::ComputeStatistics()
{
	if ((ProcessVariables.Field == C.XFields * C.YFields) && (C.XFields * C.YFields > 1))
	{
		char Temp[512];
//NOTE: StartTime/EndTime are not good for cycle speed estimates, so we override it
		switch (C.ScanningScheme)
		{
			case SCANNING_SCHEME_TOPSIDE:		StartTime = pTimeStructs[0].EndFitting;
												EndTime = pTimeStructs[ProcessVariables.Field - 1].EndFitting;
												break;

			case SCANNING_SCHEME_BOTTOMSIDE:	StartTime = pTimeStructs[C.XFields * C.YFields].EndFitting;
												EndTime = pTimeStructs[ProcessVariables.Field + C.XFields * C.YFields - 1].EndFitting;
												break;

			case SCANNING_SCHEME_BOTH_IN_FIELD: 
			case SCANNING_SCHEME_TWO_SIDES:		StartTime = pTimeStructs[0].EndFitting;
												EndTime = pTimeStructs[ProcessVariables.Field + C.XFields * C.YFields - 1].EndFitting;
												break;
			};		

		float Time = (EndTime - StartTime) * .001f;
		float CycleTime = Time / (C.XFields * C.YFields - 1) * 1000.f;
		float ScanSpeed = C.XStep * C.YStep / CycleTime * 3.6e-2;
		sprintf(Temp, "%.0f", Time);
		GetDlgItem(IDC_TC_TOTALTIME)->SetWindowText(Temp);
		sprintf(Temp, "%.1f", CycleTime);
		GetDlgItem(IDC_TC_CYCLETIME)->SetWindowText(Temp);
		sprintf(Temp, "%.2f", ScanSpeed);
		GetDlgItem(IDC_TC_SCANSPEED)->SetWindowText(Temp);
		sprintf(Temp, "%d", C.XFields);
		GetDlgItem(IDC_TC_XFIELDS)->SetWindowText(Temp);
		sprintf(Temp, "%d", C.YFields);
		GetDlgItem(IDC_TC_YFIELDS)->SetWindowText(Temp);
		sprintf(Temp, "%d", ProcessVariables.TCount[0]);
		GetDlgItem(IDC_TC_TOPTKS)->SetWindowText(Temp);
		sprintf(Temp, "%d", ProcessVariables.TCount[1]);
		GetDlgItem(IDC_TC_BOTTOMTKS)->SetWindowText(Temp);
		sprintf(Temp, "%d", CCount[0] / (C.XFields * C.YFields));
		GetDlgItem(IDC_TC_TOPAVGCLUSTERS)->SetWindowText(Temp);
		sprintf(Temp, "%d", CCount[1] / (C.XFields * C.YFields));
		GetDlgItem(IDC_TC_BOTTOMAVGCLUSTERS)->SetWindowText(Temp);
		CycleAverages.Total = 0.f;
		int i, s;
		for (s = 0; s < 2; s++)
		{
			CycleAverages.Grabbing[s].min = CycleAverages.Grabbing[s].max = 
				CycleAverages.ImageProcessing[s].min = CycleAverages.ImageProcessing[s].max = 
				CycleAverages.Tracking[s].min = CycleAverages.Tracking[s].max = 
				CycleAverages.Fitting[s].min = CycleAverages.Fitting[s].max = 
				CycleAverages.XYMotion[s].min = CycleAverages.XYMotion[s].max = 
				CycleAverages.ZMotion[s].min = CycleAverages.ZMotion[s].max = 0.f;
			};
		if (ProcessVariables.Field > 1)
		{
			for (i = 1; i < ProcessVariables.Field; i++)
				switch (C.ScanningScheme)
				{
					case SCANNING_SCHEME_TOPSIDE:
	
													CycleAverages.Grabbing[0].min += 0.;
													CycleAverages.Grabbing[0].max += pTimeStructs[i].EndGrabbing - pTimeStructs[i].StartField;
													CycleAverages.ImageProcessing[0].min += (C.FramesPerSecond >= 0) ? (1.f / C.FramesPerSecond) : 0.f;
													CycleAverages.ImageProcessing[0].max += pTimeStructs[i].EndImageProcessing - pTimeStructs[i].StartField;
													CycleAverages.Tracking[0].min += pTimeStructs[i].EndImageProcessing - pTimeStructs[i].StartField;
													CycleAverages.Tracking[0].max += pTimeStructs[i].EndTracking - pTimeStructs[i].StartField;
													CycleAverages.Fitting[0].min += pTimeStructs[i].EndTracking - pTimeStructs[i].StartField;
													CycleAverages.Fitting[0].max += pTimeStructs[i].EndFitting - pTimeStructs[i].StartField;
													CycleAverages.XYMotion[0].min += pTimeStructs[i - 1].EndGrabbing - pTimeStructs[i - 1].StartField;
													CycleAverages.XYMotion[0].max += pTimeStructs[i].EndXYMotion - pTimeStructs[i - 1].StartField;
													CycleAverages.ZMotion[0].min += pTimeStructs[i - 1].EndGrabbing - pTimeStructs[i - 1].StartField;
													CycleAverages.ZMotion[0].max += pTimeStructs[i].EndZMotion - pTimeStructs[i - 1].StartField;
													break;

					case SCANNING_SCHEME_BOTTOMSIDE:
	
													CycleAverages.Grabbing[1].min += 0.;
													CycleAverages.Grabbing[1].max += pTimeStructs[i + C.XFields * C.YFields].EndGrabbing - pTimeStructs[i + C.XFields * C.YFields].StartField;
													CycleAverages.ImageProcessing[1].min += (C.FramesPerSecond >= 1) ? (1.f / C.FramesPerSecond) : 1.f;
													CycleAverages.ImageProcessing[1].max += pTimeStructs[i + C.XFields * C.YFields].EndImageProcessing - pTimeStructs[i + C.XFields * C.YFields].StartField;
													CycleAverages.Tracking[1].min += pTimeStructs[i + C.XFields * C.YFields].EndImageProcessing - pTimeStructs[i + C.XFields * C.YFields].StartField;
													CycleAverages.Tracking[1].max += pTimeStructs[i + C.XFields * C.YFields].EndTracking - pTimeStructs[i + C.XFields * C.YFields].StartField;
													CycleAverages.Fitting[1].min += pTimeStructs[i + C.XFields * C.YFields].EndTracking - pTimeStructs[i + C.XFields * C.YFields].StartField;
													CycleAverages.Fitting[1].max += pTimeStructs[i + C.XFields * C.YFields].EndFitting - pTimeStructs[i + C.XFields * C.YFields].StartField;
													CycleAverages.XYMotion[1].min += pTimeStructs[i + C.XFields * C.YFields - 1].EndGrabbing - pTimeStructs[i + C.XFields * C.YFields - 1].StartField;
													CycleAverages.XYMotion[1].max += pTimeStructs[i + C.XFields * C.YFields].EndXYMotion - pTimeStructs[i + C.XFields * C.YFields - 1].StartField;
													CycleAverages.ZMotion[1].min += pTimeStructs[i + C.XFields * C.YFields - 1].EndGrabbing - pTimeStructs[i + C.XFields * C.YFields - 1].StartField;
													CycleAverages.ZMotion[1].max += pTimeStructs[i + C.XFields * C.YFields].EndZMotion - pTimeStructs[i + C.XFields * C.YFields - 1].StartField;
													break;

					case SCANNING_SCHEME_BOTH_IN_FIELD:
	
													CycleAverages.Grabbing[0].min += 0.;
													CycleAverages.Grabbing[0].max += pTimeStructs[i].EndGrabbing - pTimeStructs[i].StartField;
													CycleAverages.ImageProcessing[0].min += (C.FramesPerSecond >= 0) ? (1.f / C.FramesPerSecond) : 0.f;
													CycleAverages.ImageProcessing[0].max += pTimeStructs[i].EndImageProcessing - pTimeStructs[i].StartField;
													CycleAverages.Tracking[0].min += pTimeStructs[i].EndImageProcessing - pTimeStructs[i].StartField;
													CycleAverages.Tracking[0].max += pTimeStructs[i].EndTracking - pTimeStructs[i].StartField;
													CycleAverages.Fitting[0].min += pTimeStructs[i].EndTracking - pTimeStructs[i].StartField;
													CycleAverages.Fitting[0].max += pTimeStructs[i].EndFitting - pTimeStructs[i].StartField;
													CycleAverages.XYMotion[0].min += pTimeStructs[i].EndGrabbing - pTimeStructs[i].StartField;
													CycleAverages.XYMotion[0].max += pTimeStructs[i + C.XFields * C.YFields].EndXYMotion - pTimeStructs[i].StartField;
													CycleAverages.ZMotion[0].min += pTimeStructs[i].EndGrabbing - pTimeStructs[i].StartField;
													CycleAverages.ZMotion[0].max += pTimeStructs[i + C.XFields * C.YFields].EndZMotion - pTimeStructs[i].StartField;
													CycleAverages.Grabbing[1].min += pTimeStructs[i + C.XFields * C.YFields].StartField - pTimeStructs[i].StartField;
													CycleAverages.Grabbing[1].max += pTimeStructs[i + C.XFields * C.YFields].EndGrabbing - pTimeStructs[i].StartField;
													CycleAverages.ImageProcessing[1].min += ((C.FramesPerSecond >= 1) ? (1.f / C.FramesPerSecond) : 1.f) + pTimeStructs[i + C.XFields * C.YFields].StartField - pTimeStructs[i].StartField;
													CycleAverages.ImageProcessing[1].max += pTimeStructs[i + C.XFields * C.YFields].EndImageProcessing - pTimeStructs[i].StartField;
													CycleAverages.Tracking[1].min += pTimeStructs[i + C.XFields * C.YFields].EndImageProcessing - pTimeStructs[i].StartField;
													CycleAverages.Tracking[1].max += pTimeStructs[i + C.XFields * C.YFields].EndTracking - pTimeStructs[i].StartField;
													CycleAverages.Fitting[1].min += pTimeStructs[i + C.XFields * C.YFields].EndTracking - pTimeStructs[i].StartField;
													CycleAverages.Fitting[1].max += pTimeStructs[i + C.XFields * C.YFields].EndFitting - pTimeStructs[i].StartField;
													CycleAverages.XYMotion[1].min += pTimeStructs[i + C.XFields * C.YFields].EndGrabbing - pTimeStructs[i].StartField;
													CycleAverages.XYMotion[1].max += pTimeStructs[i].EndXYMotion - pTimeStructs[i - 1].StartField;
													CycleAverages.ZMotion[1].min += pTimeStructs[i + C.XFields * C.YFields].EndGrabbing - pTimeStructs[i].StartField;
													CycleAverages.ZMotion[1].max += pTimeStructs[i].EndZMotion - pTimeStructs[i - 1].StartField;
													break;
	
					case SCANNING_SCHEME_TWO_SIDES:
	
													for (s = 0; s < 2; s++)
													{
														CycleAverages.Grabbing[0].min += 0.;
														CycleAverages.Grabbing[0].max += pTimeStructs[i + s * C.XFields * C.YFields].EndGrabbing - pTimeStructs[i + s * C.XFields * C.YFields].StartField;
														CycleAverages.ImageProcessing[0].min += (C.FramesPerSecond >= 0) ? (1.f / C.FramesPerSecond) : 0.f;
														CycleAverages.ImageProcessing[0].max += pTimeStructs[i + s * C.XFields * C.YFields].EndImageProcessing - pTimeStructs[i + s * C.XFields * C.YFields].StartField;
														CycleAverages.Tracking[0].min += pTimeStructs[i + s * C.XFields * C.YFields].EndImageProcessing - pTimeStructs[i + s * C.XFields * C.YFields].StartField;
														CycleAverages.Tracking[0].max += pTimeStructs[i + s * C.XFields * C.YFields].EndTracking - pTimeStructs[i + s * C.XFields * C.YFields].StartField;
														CycleAverages.Fitting[0].min += pTimeStructs[i + s * C.XFields * C.YFields].EndTracking - pTimeStructs[i + s * C.XFields * C.YFields].StartField;
														CycleAverages.Fitting[0].max += pTimeStructs[i + s * C.XFields * C.YFields].EndFitting - pTimeStructs[i + s * C.XFields * C.YFields].StartField;
														CycleAverages.XYMotion[0].min += pTimeStructs[i + s * C.XFields * C.YFields - 1].EndGrabbing - pTimeStructs[i + s * C.XFields * C.YFields - 1].StartField;
														CycleAverages.XYMotion[0].max += pTimeStructs[i + s * C.XFields * C.YFields].EndXYMotion - pTimeStructs[i + s * C.XFields * C.YFields - 1].StartField;
														CycleAverages.ZMotion[0].min += pTimeStructs[i + s * C.XFields * C.YFields - 1].EndGrabbing - pTimeStructs[i + s * C.XFields * C.YFields - 1].StartField;
														CycleAverages.ZMotion[0].max += pTimeStructs[i + s * C.XFields * C.YFields].EndZMotion - pTimeStructs[i + s * C.XFields * C.YFields - 1].StartField;
														};
													break;
					};
			for (s = 0; s < 2; s++)
			{
				CycleAverages.Grabbing[s].min /= (ProcessVariables.Field - 1);
				CycleAverages.Grabbing[s].max /= (ProcessVariables.Field - 1);
				CycleAverages.ImageProcessing[s].min /= (ProcessVariables.Field - 1);
				CycleAverages.ImageProcessing[s].max /= (ProcessVariables.Field - 1);
				CycleAverages.Tracking[s].min /= (ProcessVariables.Field - 1);
				CycleAverages.Tracking[s].max /= (ProcessVariables.Field - 1);
				CycleAverages.Fitting[s].min /= (ProcessVariables.Field - 1);
				CycleAverages.Fitting[s].max /= (ProcessVariables.Field - 1);
				CycleAverages.XYMotion[s].min /= (ProcessVariables.Field - 1);
				CycleAverages.XYMotion[s].max /= (ProcessVariables.Field - 1);
				CycleAverages.ZMotion[s].min /= (ProcessVariables.Field - 1);
				CycleAverages.ZMotion[s].max /= (ProcessVariables.Field - 1);
				};

			switch (C.ScanningScheme)
			{
				case SCANNING_SCHEME_TOPSIDE:		s = 0;
													break;

				case SCANNING_SCHEME_BOTTOMSIDE:	s = 1;
													break;

				case SCANNING_SCHEME_BOTH_IN_FIELD: s = 1;
													break;

				case SCANNING_SCHEME_TWO_SIDES:		s = 0;
													break;
				};
			CycleAverages.Total = CycleAverages.XYMotion[s].max;
			if (CycleAverages.ZMotion[s].max > CycleAverages.Total) CycleAverages.Total = CycleAverages.ZMotion[s].max;
			if (CycleAverages.Fitting[s].max > CycleAverages.Total) CycleAverages.Total = CycleAverages.Fitting[s].max;

			sprintf(Temp, "%.0f", CycleAverages.Grabbing[0].max - CycleAverages.Grabbing[0].min + CycleAverages.Grabbing[1].max - CycleAverages.Grabbing[1].min);
			GetDlgItem(IDC_TC_TT_GRAB)->SetWindowText(Temp);			
			sprintf(Temp, "%.0f", CycleAverages.ImageProcessing[0].max - CycleAverages.ImageProcessing[0].min + CycleAverages.ImageProcessing[1].max - CycleAverages.ImageProcessing[1].min);
			GetDlgItem(IDC_TC_TT_PROC)->SetWindowText(Temp);			
			sprintf(Temp, "%.0f", CycleAverages.Tracking[0].max - CycleAverages.Tracking[0].min + CycleAverages.Tracking[1].max - CycleAverages.Tracking[1].min);
			GetDlgItem(IDC_TC_TT_TRACK)->SetWindowText(Temp);			
			sprintf(Temp, "%.0f", CycleAverages.Fitting[0].max - CycleAverages.Fitting[0].min + CycleAverages.Fitting[1].max - CycleAverages.Fitting[1].min);
			GetDlgItem(IDC_TC_TT_FIT)->SetWindowText(Temp);			
			sprintf(Temp, "%.0f", CycleAverages.XYMotion[0].max - CycleAverages.XYMotion[0].min + CycleAverages.XYMotion[1].max - CycleAverages.XYMotion[1].min);
			GetDlgItem(IDC_TC_TT_XY)->SetWindowText(Temp);			
			sprintf(Temp, "%.0f", CycleAverages.ZMotion[0].max - CycleAverages.ZMotion[0].min + CycleAverages.ZMotion[1].max - CycleAverages.ZMotion[1].min);
			GetDlgItem(IDC_TC_TT_Z)->SetWindowText(Temp);			
			};
		}
	else
	{
		GetDlgItem(IDC_TC_TOTALTIME)->SetWindowText("");
		GetDlgItem(IDC_TC_CYCLETIME)->SetWindowText("");
		GetDlgItem(IDC_TC_SCANSPEED)->SetWindowText("");
		GetDlgItem(IDC_TC_XFIELDS)->SetWindowText("");
		GetDlgItem(IDC_TC_YFIELDS)->SetWindowText("");
		GetDlgItem(IDC_TC_TOPTKS)->SetWindowText("");
		GetDlgItem(IDC_TC_BOTTOMTKS)->SetWindowText("");
		GetDlgItem(IDC_TC_TOPAVGCLUSTERS)->SetWindowText("");
		GetDlgItem(IDC_TC_BOTTOMAVGCLUSTERS)->SetWindowText("");
		GetDlgItem(IDC_TC_TT_GRAB)->SetWindowText("");
		GetDlgItem(IDC_TC_TT_PROC)->SetWindowText("");
		GetDlgItem(IDC_TC_TT_TRACK)->SetWindowText("");
		GetDlgItem(IDC_TC_TT_FIT)->SetWindowText("");
		GetDlgItem(IDC_TC_TT_XY)->SetWindowText("");
		GetDlgItem(IDC_TC_TT_Z)->SetWindowText("");
		};

	GetDlgItem(IDC_TC_TS_GRAB)->Invalidate();
	GetDlgItem(IDC_TC_TS_PROC)->Invalidate();
	GetDlgItem(IDC_TC_TS_TRACK)->Invalidate();
	GetDlgItem(IDC_TC_TS_FIT)->Invalidate();
	GetDlgItem(IDC_TC_TS_XY)->Invalidate();
	GetDlgItem(IDC_TC_TS_Z)->Invalidate();
	RedrawWindow(NULL, NULL, RDW_UPDATENOW);
}

UINT CTestAndConfig::ImageProcessingNotify()
{
	int i;

	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].EndImageProcessing = GetTickCount();
	UINT TCCount = 0;
	for (i = 0; i < C.VLayers; i++)
	{
		t_GrabStruct &r = pGrabStructs[(ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields)))* C.VLayers + i];
		r.CCount = ProcessVariables.pRec[i].Count;
		r.Z = ProcessVariables.pRec[i].Z;
		TCCount += ProcessVariables.pRec[i].Count;
		};
	CCount[ProcessVariables.IsTop ? 0 : 1] += TCCount / C.VLayers;
	return VSERR_OK;
}

void CTestAndConfig::ApplyField(void *pOwner)
{
	CTestAndConfig *This = (CTestAndConfig *)pOwner;
	if (This->HasRun)
	{
		int i, k, l;
		float DZ, X, Y, LastX, LastY;
		int Lim = 0;

		VS_View *pView = &This->Frag.Fragment.pViews[This->pSF->m_Field - This->Frag.Fragment.StartView];
		This->iStOb->EnableMonitor(false);
		This->iSt->GetPos(0, &LastX);
		This->iSt->GetPos(1, &LastY);
		This->iSt->PosMove(0, pView->X[0], This->C.HSpeed, This->C.HAcc);
		This->iSt->PosMove(1, pView->Y[0], This->C.HSpeed, This->C.HAcc);

		do
		{
			This->iSt->GetPos(0, &X);
			This->iSt->GetPos(1, &Y);

			This->iSt->GetLimiter(0, &Lim);
			if (Lim) break;
			This->iSt->GetLimiter(1, &Lim);
			if (Lim) break;
			}
		while ((fabs(X - pView->X[0]) > This->C.HTol) || (fabs(Y - pView->Y[0]) > This->C.HTol));	
		if (Lim)
		{
			This->iSt->PosMove(0, LastX, This->C.HSpeed, This->C.HAcc);
			This->iSt->PosMove(1, LastY, This->C.HSpeed, This->C.HAcc);
			This->MessageBox("Limiter reached!\r\nReturning to previous position.", "Stage Error", MB_ICONERROR | MB_OK);
			return;
			};
		This->iSt->Stop(0);
		This->iSt->Stop(1);
		Sleep(1000);
		This->iSt->GetPos(0, &X);
		This->iSt->GetPos(1, &Y);

		int Transp, TopCol, BottomCol, TopExtrCol, BottomExtrCol;
		This->iFG->GetColorCode(VC_TRANSPARENT, &Transp);
		This->iFG->GetColorCode(VC_DKRED, &TopCol);
		This->iFG->GetColorCode(VC_DKBLUE, &BottomCol);
		This->iFG->GetColorCode(VC_DKYELLOW, &TopExtrCol);
		This->iFG->GetColorCode(VC_DKGREEN, &BottomExtrCol);
		This->iFG->Clear(Transp);
		for (k = 0; k < 2; k++)			
			for (i = 0; i < pView->TCount[k]; i++)
			{
				DZ = k ? (pView->RelevantZs.TopInt - pView->RelevantZs.BottomInt) : (pView->RelevantZs.BottomInt - pView->RelevantZs.TopInt);
				if (pView->pTracks[k][i].Valid)
				{
					int LastX, LastY, NewX, NewY;
					LastX = (pView->pTracks[k][i].Intercept.X + pView->X[k] - X) / This->CSP.PixelToMicronX + This->CSP.Width / 2;
					LastY = (pView->pTracks[k][i].Intercept.Y + pView->Y[k] - Y) / This->CSP.PixelToMicronY + This->CSP.Height / 2;
					NewX = LastX + pView->pTracks[k][i].Slope.X / This->CSP.PixelToMicronX * DZ;
					NewY = LastY + pView->pTracks[k][i].Slope.Y / This->CSP.PixelToMicronY * DZ;
					This->iFG->Line(LastX, LastY, NewX, NewY, k ? BottomExtrCol : TopExtrCol);
					};
				};
		for (k = 0; k < 2; k++)			
			for (i = 0; i < pView->TCount[k]; i++)
				if (pView->pTracks[k][i].Valid)
				{
					int LastX, LastY, NewX, NewY;
					LastX = (pView->pTracks[k][i].pPoints[0].X + pView->X[k] - X) / This->CSP.PixelToMicronX + This->CSP.Width / 2;
					LastY = (pView->pTracks[k][i].pPoints[0].Y + pView->Y[k] - Y) / This->CSP.PixelToMicronY + This->CSP.Height / 2;
					for (l = 1; l < pView->pTracks[k][i].PointsN; l++)
					{
						NewX = (pView->pTracks[k][i].pPoints[l].X + pView->X[k] - X) / This->CSP.PixelToMicronX + This->CSP.Width / 2;
						NewY = (pView->pTracks[k][i].pPoints[l].Y + pView->Y[k] - Y) / This->CSP.PixelToMicronY + This->CSP.Height / 2;
						This->iFG->Line(LastX, LastY, NewX, NewY, k ? BottomCol : TopCol);
						LastX = NewX;
						LastY = NewY;
						};
					};
		};
	if (This->ShowGrid) This->ShowAlignmentGrid(true);
}

UINT CTestAndConfig::GrabbingNotify()
{
	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].EndGrabbing = GetTickCount();
	if (m_DumpGrainsToASCII && m_GrainFile != "")
	{
		FILE *f = fopen(m_GrainFile, "a+t");
		if (f)
		{
			int i, j;
			for (i = 0; i < C.VLayers; i++)
				for (j = 0; j < ProcessVariables.pRec[i].Count; j++)
					fprintf(f, "%d %d %d %f %d %d %f %f %d\n", ProcessVariables.Field, ProcessVariables.IsTop, i, ProcessVariables.pRec[i].Z, ProcessVariables.pRec[i].Count, j, ProcessVariables.pTempCSpace[i * C.MaxClusters + j].X, ProcessVariables.pTempCSpace[i * C.MaxClusters + j].Y, ProcessVariables.pTempCSpace[i * C.MaxClusters + j].Area);
			fclose(f);
			};
		};
	return VSERR_OK;
}

UINT CTestAndConfig::TrackingNotify()
{
	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].EndTracking = GetTickCount();
	return VSERR_OK;
}

UINT CTestAndConfig::FittingNotify()
{
	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].EndFitting = GetTickCount();
	return VSERR_OK;
}

UINT CTestAndConfig::XYMotionNotify()
{
	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].EndXYMotion = GetTickCount();
	return VSERR_OK;
}

UINT CTestAndConfig::ZRewindNotify()
{
	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))].EndZMotion = GetTickCount();
	return VSERR_OK;
}

UINT CTestAndConfig::FrameNotify()
{	
	if (!IsFocusing) pGrabStructs[(ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields * C.YFields))) * C.VLayers + ProcessVariables.Layer].Time = GetTickCount();
	return VSERR_OK;
}

void CTestAndConfig::OnDumpGrabStruct() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(FALSE, "txt", NULL, OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_OVERWRITEPROMPT, "Tabbed Text Files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		FILE *fout = fopen(MyDlg.GetPathName(), "wt");
		if (!fout) MessageBox("Can't open output file", "File Error", MB_ICONERROR | MB_OK);
		else
		{
			fprintf(fout, "Side\tField\tLayer\tTime\tZ\tCount\n");
			int i, l, k;
			for (k = 0; k < 2; k++)
				for (i = 0; i < C.XFields * C.YFields; i++)
					for (l = 0; l < C.VLayers; l++)
					{
						t_GrabStruct &r = pGrabStructs[(k * C.XFields * C.YFields + i) * C.VLayers + l];
						fprintf(fout, "%d\t%d\t%d\t%d\t%.2f\t%d\n", k, i, l, r.Time - StartTime, r.Z, r.CCount);
						};
			fclose(fout);
			};
		};
}

void CTestAndConfig::OnDumpTimeStruct() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(FALSE, "txt", NULL, OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_OVERWRITEPROMPT, "Tabbed Text Files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		FILE *fout = fopen(MyDlg.GetPathName(), "wt");
		if (!fout) MessageBox("Can't open output file", "File Error", MB_ICONERROR | MB_OK);
		else
		{
			fprintf(fout, "Side\tField\tStart\tGrab\tImProc\tTrack\tFit\tXY\tZ\n");
			int i, k;
			for (k = 0; k < 2; k++)
				for (i = 0; i < C.XFields * C.YFields; i++)
				{
					t_TimeStruct &r = pTimeStructs[k * C.XFields * C.YFields + i];
					fprintf(fout, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", k, i, 
						r.StartField - StartTime, r.EndGrabbing - StartTime, r.EndImageProcessing - StartTime, 
						r.EndTracking - StartTime, r.EndFitting - StartTime, r.EndXYMotion - StartTime, r.EndZMotion - StartTime);
					};
			fclose(fout);
			};
		};	
}

void CTestAndConfig::OnDumpFocusData() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(FALSE, "txt", NULL, OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_OVERWRITEPROMPT, "Tabbed Text Files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		FILE *fout = fopen(MyDlg.GetPathName(), "wt");
		if (!fout) MessageBox("Can't open output file", "File Error", MB_ICONERROR | MB_OK);
		else
		{
			fprintf(fout, "Layer\tZ\tCount\n");
			int i;
			for (i = 0; i < ProcessVariables.FocusSamples; i++)
			{
				t_ProcessVariables::t_Rec &r = pFocusData[i];
				fprintf(fout, "%d\t%.02f\t%d\n", i, r.Z, r.Count);
				};
			fclose(fout);
			};
		};	
}

void CTestAndConfig::OnSave() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(FALSE, "rwd", NULL, OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_OVERWRITEPROMPT, "Fragment Raw Data Files (*.rwd)|*.rwd|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		CString Temp = MyDlg.GetPathName();
		UINT ExtErrorInfo;
		HRESULT HRes = iIO->Write((HSySalHANDLE)m_hWnd, (BYTE *)&Frag, &ExtErrorInfo, (UCHAR *)Temp.GetBuffer(1));
		Temp.ReleaseBuffer();
		if (HRes != S_OK)
		{
			Temp.Format("Error saving fragment.\r\nError code: %08X", ExtErrorInfo);
			MessageBox(Temp, "File Error", MB_ICONERROR | MB_OK);
			}
		else MessageBox("Fragment saved!", "Success", MB_ICONINFORMATION | MB_OK);
		};			
}

void CTestAndConfig::OnGridOptions() 
{
	// TODO: Add your control notification handler code here
	CEditGridOptions MyDlg(this);
	MyDlg.m_XStep = GridXStep;
	MyDlg.m_YStep = GridYStep;
	if (MyDlg.DoModal() == IDOK)
	{
		if (ShowGrid) ShowAlignmentGrid(false);
		GridXStep = MyDlg.m_XStep;
		GridYStep = MyDlg.m_YStep;
		if (ShowGrid) ShowAlignmentGrid(true);
		};
}

void CTestAndConfig::OnToggleGrid() 
{
	// TODO: Add your control notification handler code here
	ShowGrid ^= true;
	ShowAlignmentGrid(ShowGrid);
}

void CTestAndConfig::ShowAlignmentGrid(bool show)
{
	int EdgeCol, TickCol;
	int i;

	iFG->GetColorCode(show ? VC_DKBLUE : VC_TRANSPARENT, &EdgeCol);
	iFG->GetColorCode(show ? VC_DKRED : VC_TRANSPARENT, &TickCol);

	iFG->Line(CSP.Width / 2, 0, CSP.Width / 2, CSP.Height - 1, EdgeCol);
	iFG->Line(0, CSP.Height / 2, CSP.Width - 1, CSP.Height / 2, EdgeCol);

	iFG->Line(CSP.OffX, CSP.OffY, CSP.OffX + CSP.WinWidth, CSP.OffY, EdgeCol);
	iFG->Line(CSP.OffX + CSP.WinWidth, CSP.OffY, CSP.OffX + CSP.WinWidth, CSP.OffY + CSP.WinHeight, EdgeCol);
	iFG->Line(CSP.OffX + CSP.WinWidth, CSP.OffY + CSP.WinHeight, CSP.OffX, CSP.OffY + CSP.WinHeight, EdgeCol);
	iFG->Line(CSP.OffX, CSP.OffY + CSP.WinHeight, CSP.OffX, CSP.OffY, EdgeCol);	

	for (i = CSP.Width / 2 - GridXStep; i >= 0; i -= GridXStep) iFG->Line(i, 0, i, CSP.Height - 1, TickCol);
	for (i = CSP.Width / 2 + GridXStep; i < CSP.Width; i += GridXStep) iFG->Line(i, 0, i, CSP.Height - 1, TickCol);
	for (i = CSP.Height / 2 - GridYStep; i >= 0; i -= GridYStep) iFG->Line(0, i, CSP.Width - 1, i, TickCol);
	for (i = CSP.Height / 2 + GridYStep; i < CSP.Width; i += GridYStep) iFG->Line(0, i, CSP.Width - 1, i, TickCol);
}

void CTestAndConfig::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CDC MyDC;
	MyDC.Attach(lpDrawItemStruct->hDC);
	int n, o;
	switch (C.ScanningScheme)
	{
		case SCANNING_SCHEME_TOPSIDE:		n = 1; o = 0;
											break;

		case SCANNING_SCHEME_BOTTOMSIDE:	n = 1; o = 1;
											break;

		case SCANNING_SCHEME_BOTH_IN_FIELD: n = 2; o = 0;
											break;

		case SCANNING_SCHEME_TWO_SIDES:		n = 1; o = 0;
											break;
		};
	switch (nIDCtl)
	{
		case IDC_TC_TS_GRAB:	if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 0, 0), n, CycleAverages.Grabbing + o);
								else DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 255, 255), 0, 0);
								break;

		case IDC_TC_TS_PROC:	if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 128, 0), n, CycleAverages.ImageProcessing + o);
								else DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 255, 255), 0, 0);
								break;

		case IDC_TC_TS_TRACK:	if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(0, 192, 0), n, CycleAverages.Tracking + o);
								else DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 255, 255), 0, 0);
								break;

		case IDC_TC_TS_FIT:		if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(0, 128, 192), n, CycleAverages.Fitting + o);
								else DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 255, 255), 0, 0);
								break;

		case IDC_TC_TS_XY:		if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(0, 0, 255), n, CycleAverages.XYMotion + o);
								else DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 255, 255), 0, 0);
								break;

		case IDC_TC_TS_Z:		if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(0, 0, 128), n, CycleAverages.ZMotion + o);
								else DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 255, 255), 0, 0);
								break;

		default:			CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
		};
	MyDC.Detach();
}

void CTestAndConfig::DrawTimeStructBar(CDC *pDC, UINT id, COLORREF color, UINT count, t_CycleAverages::t_Interval *pIntervals)
{
	CRect ClRect;
	CWnd *pWnd = GetDlgItem(id);
	pWnd->GetClientRect(ClRect);
	ClRect.DeflateRect(1, 1);
	COLORREF OldBkColor = pDC->GetBkColor();
	pDC->FillSolidRect(&ClRect, RGB(255, 255, 255));
	int i;
	float scale = ClRect.Width() / ((CycleAverages.Total <= 0) ? 1.f : CycleAverages.Total);
	for (i = 0; i < count; i++)
		pDC->FillSolidRect(pIntervals[i].min * scale + ClRect.left, ClRect.top, (pIntervals[i].max - pIntervals[i].min) * scale + ClRect.left, ClRect.bottom - ClRect.top, color);
	pDC->SetBkColor(OldBkColor);
}

UINT CTestAndConfig::FocusEndNotify()
{
	memcpy(pFocusData, ProcessVariables.pRec, sizeof(t_ProcessVariables::t_Rec) * ProcessVariables.FocusSamples);
	return VSERR_OK;
}


void CTestAndConfig::OnEnableRemoteControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (iRCS) 
	{
		if (m_EnableRemoteControl) 
		{
			RemoteControlInterface RCI;
			RCI.Context = (DWORD)(void *)this;
			GRABBERINFOSTRUCT GIS;
			iFG->GrabInfo(&GIS);
			if (GIS.DataSize != 1 || GIS.Planes != 1) return;
			RCI.ImageWidth = GIS.Width;
			RCI.ImageHeight = GIS.Height;
			RCI.ImageFormat = RC_VIDEO_GRAYSCALE_256;
			RCI.ImageOverlayColors = 4;
			RCI.pConnect = RCS_Connect;
			RCI.pDisconnect = RCS_Disconnect;
			RCI.pGetDisplayList = RCS_GetDisplayList;
			RCI.pGetDisplayListLength = RCS_GetDisplayListLength;
			RCI.pGetImage = RCS_GetImage;
			RCI.pGetPos = RCS_GetPos;
			RCI.pMoveToPos = RCS_MoveToPos;
			RCI.pShowMessage = RCS_ShowMessage;
			RCI.pStop = RCS_Stop;
			iRCS->Connect(&RCI);
			}
		else iRCS->Disconnect();
		};
}


// Remote Control Interface Functions

void _stdcall CTestAndConfig::RCS_Connect(DWORD context)
{
	CTestAndConfig *pThis = (CTestAndConfig *)(void *)context;
	HWND thisWnd = pThis->m_hWnd;
	if (thisWnd) ::PostMessage(thisWnd, UM_RCS_CONNECT_DISCONNECT, 1, 0);
	};

void _stdcall CTestAndConfig::RCS_MoveToPos(DWORD context, int axis, float pos, float speed, float acc)
{
	CTestAndConfig *pThis = (CTestAndConfig *)(void *)context;
	pThis->iSt->PosMove(axis, pos, speed, acc);
	};

void _stdcall CTestAndConfig::RCS_Stop(DWORD context, int axis)
{
	CTestAndConfig *pThis = (CTestAndConfig *)(void *)context;
	pThis->iSt->Stop(axis);	
	};

float _stdcall CTestAndConfig::RCS_GetPos(DWORD context, int axis)
{
	float pos = 0.f;
	CTestAndConfig *pThis = (CTestAndConfig *)(void *)context;
	pThis->iSt->GetPos(axis, &pos);	
	return pos;
	};

BYTE * _stdcall CTestAndConfig::RCS_GetImage(DWORD context)
{
	CTestAndConfig *pThis = (CTestAndConfig *)(void *)context;
	BYTE *pImage = 0;
	pThis->iFG->FreezeFrame(&pImage);
	return pImage;
	};

UINT _stdcall CTestAndConfig::RCS_GetDisplayListLength(DWORD context)
{
// HERE!!! TO BE IMPLEMENTED
	return 0;
	};

BYTE * _stdcall CTestAndConfig::RCS_GetDisplayList(DWORD context)
{
// HERE!!! TO BE IMPLEMENTED
	return 0;
	};

void _stdcall CTestAndConfig::RCS_ShowMessage(DWORD context, UCHAR *pMsg)
{
// HERE!!! TO BE IMPLEMENTED
	pMsg = 0;	
	};

void _stdcall CTestAndConfig::RCS_Disconnect(DWORD context)
{
	CTestAndConfig *pThis = (CTestAndConfig *)(void *)context;
	HWND thisWnd = pThis->m_hWnd;
	if (thisWnd) ::PostMessage(thisWnd, UM_RCS_CONNECT_DISCONNECT, 0, 0);
	};
