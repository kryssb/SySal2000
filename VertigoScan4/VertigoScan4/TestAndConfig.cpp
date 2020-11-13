// TestAndConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TestAndConfig.h"
#include "..\Common\Connection.h"
#include "VertigoScan4Class.h"
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


CTestAndConfig::CTestAndConfig(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, ITracker3 *itk1, ITrackFitter3 *ift1, 
	ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, ConfigManagerInterface *pcmi, IRemoteControlServer *ircs, 
	ConfigData &c, CWnd* pParent /*=NULL*/)
	: CDialog(CTestAndConfig::IDD, pParent), phWnd(phwnd), CVertigoScanner(iself, iio, ist, iob, 
		ifg, ivp, itk1, ift1, itk2, ift2, ism, c), pCMI(pcmi), iRCS(ircs)
{
	//{{AFX_DATA_INIT(CTestAndConfig)
	m_GrainFile = _T("");
	m_DumpGrainsToASCII = FALSE;
	m_EnableRemoteControl = FALSE;
	m_AutoSave = FALSE;
	m_SaveImages = FALSE;
	m_ImageSequence = _T("");
	m_ImageQuality = 6;
	//}}AFX_DATA_INIT
	iVP4 = 0;
	ppImagesSaved = 0;
	iVP->QueryInterface(IID_IVisionProcessor4, (void **)&iVP4);
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
	pSavedClusters = 0;
	pSavedImageIndices = 0;
	SavedClusterCount = 0;
	SavedImageCount = 0;
	MaxSavedClusters = 0;
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
	DDX_Check(pDX, IDC_TC_SAVEIMAGES, m_SaveImages);
	DDX_Text(pDX, IDC_TC_IMAGESEQ, m_ImageSequence);
	DDX_Text(pDX, IDC_TC_IMAGEQUALITY, m_ImageQuality);
	DDV_MinMaxUInt(pDX, m_ImageQuality, 2, 8);
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
	if (!UpdateData()) return;
	if (!OkToRun)
	{
		MessageBox("Cannot run", "Error", MB_ICONERROR | MB_OK);
		return;
		};

	Frag.Fragment.StartView = 0;
	Frag.Fragment.CountOfViews = C.XFields() * C.YFields();
	Frag.Fragment.Index = 1;
	Frag.Fragment.CodingMode = VS_COMPRESSION_NULL;
	CCount[0] = CCount[1] = 0;
	ProcessVariables.Field = 0;
	ZeroMemory(pGrabStructs, sizeof(t_GrabStruct) * C.XFields() * C.YFields() * C.VLayers * 2);
	ZeroMemory(pTimeStructs, sizeof(t_TimeStruct) * C.XFields() * C.YFields() * 2);
	SendDlgItemMessage(IDC_TC_TESTPROGRESS, PBM_SETRANGE32, 0, C.XFields() * C.YFields() * ((C.ScanningScheme == SCANNING_SCHEME_TWO_SIDES) ? 2 : 1));
	SendDlgItemMessage(IDC_TC_TESTPROGRESS, PBM_SETPOS, 0, 0);
	RunStatus = true;
	EnableControls();
	Frag.Hdr.ID.Part[3]++;
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iStOb->EnableMonitor(true);
	MessageBox("Place the stage at the top surface of the plastic base and press OK", "Help Request", MB_ICONQUESTION | MB_OK);
	iStOb->EnableMonitor(false);
	iSt->FlushAsyncMotions();
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
			HRESULT HRes = (iObj == iSelf) ? EditConfig(iSt, &Temp, this) : iObj->EditConfig(&Temp, (HSySalHANDLE)m_hWnd);
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
	switch (Err = Init())
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
	pGrabStructs = (t_GrabStruct *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(t_GrabStruct) * C.VLayers * C.XFields() * C.YFields());
	if (!pGrabStructs) 
	{
		OkToRun = false;
		Temp = "Grab monitoring structs allocation error";
		};

	if (pTimeStructs) 
	{
		GlobalFree(pTimeStructs);
		};
	pTimeStructs = (t_TimeStruct *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(t_TimeStruct) * C.XFields() * C.YFields());
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
	GetDlgItem(IDC_TC_SAVEIMAGES)->EnableWindow(!RunStatus && iVP4);
	GetDlgItem(IDC_TC_IMAGEQUALITY)->EnableWindow(!RunStatus && iVP4);
	GetDlgItem(IDC_TC_IMAGESEQ)->EnableWindow(!RunStatus && iVP4);
}

void CTestAndConfig::OnShowStageMonitor() 
{
	// TODO: Add your control notification handler code here
	iStOb->EnableMonitor(true);	
}

bool CTestAndConfig::ShouldStop()
{
	MSG Msg;
	if (PeekMessage(&Msg, 0, 0, 0, PM_NOREMOVE))
		if (Msg.message == UM_CHANGE_STATUS && Msg.wParam == UM_STOP) return true;
		else PeekMessage(&Msg, 0, 0, 0, PM_REMOVE);
	return false;
}

UINT CTestAndConfig::ThreadHook(void *pOwner)
{
	CTestAndConfig *This = (CTestAndConfig *)pOwner;
	This->ProcessVariables.PreserveClusters = (This->m_DumpGrainsToASCII && This->m_GrainFile != "");
	float StartX, StartY;
	int i;
	for (i = 0; i < 2 * This->C.XFields() * This->C.YFields(); i++)
	{
		This->pTimeStructs[i].EndClustering = This->pTimeStructs[i].EndFitting = This->pTimeStructs[i].EndImageProcessing = 
			This->pTimeStructs[i].EndTracking = This->pTimeStructs[i].EndXYZMotion = This->pTimeStructs[i].EndZMotion = 
			This->pTimeStructs[i].StartField = -1;
		}
	for (i = 0; i < 2; i++)
	{
		This->CycleAverages.Clustering[i].max = This->CycleAverages.Clustering[i].min = This->CycleAverages.Clustering[i].samples = 0;
		This->CycleAverages.Fitting[i].max = This->CycleAverages.Fitting[i].min = This->CycleAverages.Fitting[i].samples = 0;
		This->CycleAverages.ImageProcessing[i].max = This->CycleAverages.ImageProcessing[i].min = This->CycleAverages.ImageProcessing[i].samples = 0;
		This->CycleAverages.Tracking[i].max = This->CycleAverages.Tracking[i].min = This->CycleAverages.Tracking[i].samples = 0;
		This->CycleAverages.XYZMotion[i].max = This->CycleAverages.XYZMotion[i].min = This->CycleAverages.XYZMotion[i].samples = 0;
		This->CycleAverages.ZScan[i].max = This->CycleAverages.ZScan[i].min = This->CycleAverages.ZScan[i].samples = 0;
		This->CCount[i] = 0;
		}
	This->iSt->GetPos(0, &StartX);
	This->iSt->GetPos(1, &StartY);
	This->VPLock();
	UINT Ret = This->Scan(StartX, StartY);
	This->VPUnlock();
	This->iStOb->EnableMonitor(true);
	if (Ret == VSSCAN_OK)
	{
		UINT ExtErrorInfo;
		if (This->m_AutoSave && This->iIO->Write2(0, (BYTE *)&This->Frag, &ExtErrorInfo, 0) != S_OK)
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
	int TotalFields = C.XFields() * C.YFields();
	if (ProcessVariables.Field >= TotalFields) return VSERR_OK;
	char string[64] = "";
	pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].StartField = GetTickCount();
	if (!ProcessVariables.Field && (ProcessVariables.IsTop || (C.ScanningScheme == SCANNING_SCHEME_BOTTOMSIDE))) 
		StartTime = pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].StartField;
	switch (C.ScanningScheme) 
	{
		case SCANNING_SCHEME_TOPSIDE:
		case SCANNING_SCHEME_BOTTOMSIDE:		
		case SCANNING_SCHEME_BOTH_IN_FIELD:		sprintf(string, "Field: %d/%d", ProcessVariables.Field, TotalFields);
												SendDlgItemMessage(IDC_TC_TESTPROGRESS, PBM_SETPOS, ProcessVariables.Field, 0);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			sprintf(string, "Field: %d/%d%c", ProcessVariables.Field, TotalFields, ProcessVariables.IsTop ? 'T' : 'B');
												SendDlgItemMessage(IDC_TC_TESTPROGRESS, PBM_SETPOS, ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields), 0);
												break;
		}
	SendDlgItemMessage(IDC_TC_FIELDN, WM_SETTEXT, 0, (LPARAM)(LPCSTR)string);	
	return VSERR_OK;
}

UINT CTestAndConfig::EndNotify()
{
	int TotalFields = C.XFields() * C.YFields();
	char string[64] = "";
	EndTime = GetTickCount();
	switch (C.ScanningScheme) 
	{
		case SCANNING_SCHEME_TOPSIDE:
		case SCANNING_SCHEME_BOTTOMSIDE:		
		case SCANNING_SCHEME_BOTH_IN_FIELD:		sprintf(string, "Field: %d/%d", TotalFields, TotalFields);
												SendDlgItemMessage(IDC_TC_TESTPROGRESS, PBM_SETPOS, ProcessVariables.Field, 0);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			sprintf(string, "Field: %d/%d%c", TotalFields, TotalFields, ProcessVariables.IsTop ? 'T' : 'B');
												SendDlgItemMessage(IDC_TC_TESTPROGRESS, PBM_SETPOS, ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields() * C.YFields())), 0);
												break;
		}
	SendDlgItemMessage(IDC_TC_FIELDN, WM_SETTEXT, 0, (LPARAM)(LPCSTR)string);
	if (m_DumpGrainsToASCII && m_GrainFile != "")
	{
		int i, j, k;
		FILE *fout = fopen(m_GrainFile, "a+t");
		if (fout)
		{
			k = 0;
			for (i = 0; i < SavedImageCount; i++)
				for (j = 0; j < pSavedImageIndices[i].ClusterCount; j++)
				{
					fprintf(fout, "%d %d %d %f %d %d %f %f %d\n", 
						pSavedImageIndices[i].View, pSavedImageIndices[i].IsTop ? 1 : 0,
						pSavedImageIndices[i].Layer, pSavedImageIndices[i].Z, 
						pSavedImageIndices[i].ClusterCount, j,
						pSavedClusters[k].X, pSavedClusters[k].Y, pSavedClusters[k].Area);
					k++;
					}
			fclose(fout);
			};
		}

	return VSERR_OK;
}

UINT CTestAndConfig::GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop)
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
	F.TopExt = Z + C.VStep(true);
	F.BottomInt = Z - C.BaseThickness;
	F.BottomExt = F.BottomInt - C.VStep(false);
	Ret = CVertigoScanner::GetFocus(X, Y, F);
	IsFocusing = false;
	return Ret;
	};

void CTestAndConfig::ComputeStatistics()
{
	if ((ProcessVariables.Field == C.XFields() * C.YFields()) && (C.XFields() * C.YFields() - 1 > ProcessVariables.FieldDelay))
	{
		char Temp[512];
//NOTE: StartTime/EndTime are not good for cycle speed estimates, so we override it
		switch (C.ScanningScheme)
		{
			case SCANNING_SCHEME_TOPSIDE:		StartTime = pTimeStructs[ProcessVariables.FieldDelay].StartField;
												EndTime = pTimeStructs[ProcessVariables.Field - 1].StartField;
												break;

			case SCANNING_SCHEME_BOTTOMSIDE:	StartTime = pTimeStructs[C.XFields() * C.YFields() + ProcessVariables.FieldDelay].StartField;
												EndTime = pTimeStructs[ProcessVariables.Field + C.XFields() * C.YFields() - 1].StartField;
												break;

			case SCANNING_SCHEME_BOTH_IN_FIELD: 
			case SCANNING_SCHEME_TWO_SIDES:		StartTime = pTimeStructs[ProcessVariables.FieldDelay].StartField;
												EndTime = pTimeStructs[ProcessVariables.Field + C.XFields() * C.YFields() - 1].StartField;
												break;
			};		

		float Time = (EndTime - StartTime) * .001f;
		float CycleTime = Time / (C.XFields() * C.YFields() - 1 - ProcessVariables.FieldDelay) * 1000.f;
		float ScanSpeed = C.XStep * C.YStep / CycleTime * 3.6e-2;
		sprintf(Temp, "%.0f", Time);
		GetDlgItem(IDC_TC_TOTALTIME)->SetWindowText(Temp);
		sprintf(Temp, "%.1f", CycleTime);
		GetDlgItem(IDC_TC_CYCLETIME)->SetWindowText(Temp);
		sprintf(Temp, "%.2f", ScanSpeed);
		GetDlgItem(IDC_TC_SCANSPEED)->SetWindowText(Temp);
		sprintf(Temp, "%d", C.XFields());
		GetDlgItem(IDC_TC_XFIELDS)->SetWindowText(Temp);
		sprintf(Temp, "%d", C.YFields());
		GetDlgItem(IDC_TC_YFIELDS)->SetWindowText(Temp);
		sprintf(Temp, "%d", ProcessVariables.TCount[0]);
		GetDlgItem(IDC_TC_TOPTKS)->SetWindowText(Temp);
		sprintf(Temp, "%d", ProcessVariables.TCount[1]);
		GetDlgItem(IDC_TC_BOTTOMTKS)->SetWindowText(Temp);
		sprintf(Temp, "%d", CCount[0] / (C.XFields() * C.YFields() * C.VLayers));
		GetDlgItem(IDC_TC_TOPAVGCLUSTERS)->SetWindowText(Temp);
		sprintf(Temp, "%d", CCount[1] / (C.XFields() * C.YFields() * C.VLayers));
		GetDlgItem(IDC_TC_BOTTOMAVGCLUSTERS)->SetWindowText(Temp);
		CycleAverages.Total = 0.f;
		int s;
		for (s = 0; s < 2; s++)
		{
			if (CycleAverages.Clustering[s].samples > 0) CycleAverages.Clustering[s].max /= CycleAverages.Clustering[s].samples;
			if (CycleAverages.ImageProcessing[s].samples > 0) CycleAverages.ImageProcessing[s].max /= CycleAverages.ImageProcessing[s].samples;
			if (CycleAverages.Tracking[s].samples > 0) CycleAverages.Tracking[s].max /= CycleAverages.Tracking[s].samples;
			if (CycleAverages.Fitting[s].samples > 0) CycleAverages.Fitting[s].max /= CycleAverages.Fitting[s].samples;
			if (CycleAverages.XYZMotion[s].samples > 0) CycleAverages.XYZMotion[s].max /= CycleAverages.XYZMotion[s].samples;
			if (CycleAverages.ZScan[s].samples > 0) CycleAverages.ZScan[s].max /= CycleAverages.ZScan[s].samples;
			};
		switch (C.ScanningScheme)
		{
			case SCANNING_SCHEME_TOPSIDE:
											CycleAverages.Clustering[0].min = 0.f;
											CycleAverages.Tracking[0].min += CycleAverages.Clustering[0].max;
											CycleAverages.Fitting[0].min += CycleAverages.Tracking[0].max;
											CycleAverages.ImageProcessing[0].min = 0.f;
											CycleAverages.XYZMotion[0].min += CycleAverages.ImageProcessing[0].max;
											CycleAverages.ZScan[0].min = 0.f;
											break;

			case SCANNING_SCHEME_BOTTOMSIDE:
											CycleAverages.Clustering[1].min = 0.f;
											CycleAverages.Tracking[1].min += CycleAverages.Clustering[1].max;
											CycleAverages.Fitting[1].min += CycleAverages.Tracking[1].max;
											CycleAverages.ImageProcessing[1].min = 0.f;
											CycleAverages.XYZMotion[1].min += CycleAverages.ImageProcessing[1].max;
											CycleAverages.ZScan[1].min = 0.f;
											break;

			case SCANNING_SCHEME_BOTH_IN_FIELD:
											CycleAverages.Clustering[0].min = 0.f;
											CycleAverages.Tracking[0].min += CycleAverages.Clustering[0].max;
											CycleAverages.Fitting[0].min += CycleAverages.Tracking[0].max;
											CycleAverages.ImageProcessing[0].min = 0.f;
											CycleAverages.XYZMotion[0].min += CycleAverages.ImageProcessing[0].max;
											CycleAverages.ZScan[0].min = 0.f;

											CycleAverages.Clustering[1].min = CycleAverages.XYZMotion[0].max;
											CycleAverages.Clustering[1].max += CycleAverages.XYZMotion[0].max;
											CycleAverages.Tracking[1].min += CycleAverages.Clustering[1].max + CycleAverages.XYZMotion[0].max;
											CycleAverages.Tracking[1].max += CycleAverages.XYZMotion[0].max;
											CycleAverages.Fitting[1].min += CycleAverages.Tracking[1].max + CycleAverages.XYZMotion[0].max;
											CycleAverages.Fitting[1].max += CycleAverages.XYZMotion[0].max;
											CycleAverages.ImageProcessing[1].min = CycleAverages.XYZMotion[0].max;
											CycleAverages.ImageProcessing[1].max += CycleAverages.XYZMotion[0].max;
											CycleAverages.XYZMotion[1].min += CycleAverages.ImageProcessing[1].max;
											CycleAverages.XYZMotion[1].max += CycleAverages.XYZMotion[0].max;
											CycleAverages.ZScan[1].min = CycleAverages.XYZMotion[0].max;
											CycleAverages.ZScan[1].max += CycleAverages.XYZMotion[0].max;													
											break;
	
			case SCANNING_SCHEME_TWO_SIDES:
											for (s = 0; s < 2; s++)
											{
												CycleAverages.Clustering[s].min = 0.f;
												CycleAverages.Tracking[s].min += CycleAverages.Clustering[s].max;
												CycleAverages.Fitting[s].min += CycleAverages.Tracking[s].max;
												CycleAverages.ImageProcessing[s].min = 0.f;
												CycleAverages.XYZMotion[s].min += CycleAverages.ImageProcessing[s].max;
												CycleAverages.ZScan[s].min = 0.f;
												};
											CycleAverages.Clustering[0].min = 0.5f * (CycleAverages.Clustering[0].min + CycleAverages.Clustering[1].min);
											CycleAverages.Clustering[0].max = 0.5f * (CycleAverages.Clustering[0].max + CycleAverages.Clustering[1].max);
											CycleAverages.Tracking[0].min = 0.5f * (CycleAverages.Tracking[0].min + CycleAverages.Tracking[1].min);
											CycleAverages.Tracking[0].max = 0.5f * (CycleAverages.Tracking[0].max + CycleAverages.Tracking[1].max);
											CycleAverages.Fitting[0].min = 0.5f * (CycleAverages.Fitting[0].min + CycleAverages.Fitting[1].min);
											CycleAverages.Fitting[0].max = 0.5f * (CycleAverages.Fitting[0].max + CycleAverages.Fitting[1].max);
											CycleAverages.ImageProcessing[0].min = 0.5f * (CycleAverages.ImageProcessing[0].min + CycleAverages.ImageProcessing[1].min);
											CycleAverages.ImageProcessing[0].max = 0.5f * (CycleAverages.ImageProcessing[0].max + CycleAverages.ImageProcessing[1].max);
											CycleAverages.XYZMotion[0].min = 0.5f * (CycleAverages.XYZMotion[0].min + CycleAverages.XYZMotion[1].min);
											CycleAverages.XYZMotion[0].max = 0.5f * (CycleAverages.XYZMotion[0].max + CycleAverages.XYZMotion[1].max);
											CycleAverages.ZScan[0].min = 0.5f * (CycleAverages.ZScan[0].min + CycleAverages.ZScan[1].min);
											CycleAverages.ZScan[0].max = 0.5f * (CycleAverages.ZScan[0].max + CycleAverages.ZScan[1].max);
											break;
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
		CycleAverages.Total = CycleAverages.XYZMotion[s].max;

		sprintf(Temp, "%.0f", CycleAverages.Clustering[0].max - CycleAverages.Clustering[0].min + CycleAverages.Clustering[1].max - CycleAverages.Clustering[1].min);
		GetDlgItem(IDC_TC_TT_GRAB)->SetWindowText(Temp);			
		sprintf(Temp, "%.0f", CycleAverages.ImageProcessing[0].max - CycleAverages.ImageProcessing[0].min + CycleAverages.ImageProcessing[1].max - CycleAverages.ImageProcessing[1].min);
		GetDlgItem(IDC_TC_TT_PROC)->SetWindowText(Temp);			
		sprintf(Temp, "%.0f", CycleAverages.Tracking[0].max - CycleAverages.Tracking[0].min + CycleAverages.Tracking[1].max - CycleAverages.Tracking[1].min);
		GetDlgItem(IDC_TC_TT_TRACK)->SetWindowText(Temp);			
		sprintf(Temp, "%.0f", CycleAverages.Fitting[0].max - CycleAverages.Fitting[0].min + CycleAverages.Fitting[1].max - CycleAverages.Fitting[1].min);
		GetDlgItem(IDC_TC_TT_FIT)->SetWindowText(Temp);			
		sprintf(Temp, "%.0f", CycleAverages.XYZMotion[0].max - CycleAverages.XYZMotion[0].min + CycleAverages.XYZMotion[1].max - CycleAverages.XYZMotion[1].min);
		GetDlgItem(IDC_TC_TT_XY)->SetWindowText(Temp);			
		sprintf(Temp, "%.0f", CycleAverages.ZScan[0].max - CycleAverages.ZScan[0].min + CycleAverages.ZScan[1].max - CycleAverages.ZScan[1].min);
		GetDlgItem(IDC_TC_TT_Z)->SetWindowText(Temp);			
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
	int TotalFields = C.XFields() * C.YFields();
	if (ProcessVariables.Field >= TotalFields) return VSERR_OK;
	CycleAverages.ImageProcessing[ProcessVariables.IsTop ? 0 : 1].max += (pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].EndImageProcessing = GetTickCount()) - 
		pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].StartField;
	CycleAverages.ImageProcessing[ProcessVariables.IsTop ? 0 : 1].samples++;
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

		VS_View2 *pView = &This->Frag.Fragment.pViews[This->pSF->m_Field - This->Frag.Fragment.StartView];
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
					LastX = (pView->pTracks[k][i].pGrains[0].X + pView->X[k] - X) / This->CSP.PixelToMicronX + This->CSP.Width / 2;
					LastY = (pView->pTracks[k][i].pGrains[0].Y + pView->Y[k] - Y) / This->CSP.PixelToMicronY + This->CSP.Height / 2;
					for (l = 1; l < pView->pTracks[k][i].Grains; l++)
					{
						NewX = (pView->pTracks[k][i].pGrains[l].X + pView->X[k] - X) / This->CSP.PixelToMicronX + This->CSP.Width / 2;
						NewY = (pView->pTracks[k][i].pGrains[l].Y + pView->Y[k] - Y) / This->CSP.PixelToMicronY + This->CSP.Height / 2;
						This->iFG->Line(LastX, LastY, NewX, NewY, k ? BottomCol : TopCol);
						LastX = NewX;
						LastY = NewY;
						};
					};
		};
	if (This->ShowGrid) This->ShowAlignmentGrid(true);
}

UINT CTestAndConfig::ClusteringNotify()
{
	int imindex = (ProcessVariables.AsyncImageIndex + 1) % (1 + ProcessVariables.FieldDelay);
	int s = ProcessVariables.pFieldSideRec[imindex].Side;
	int f = ProcessVariables.pFieldSideRec[imindex].Field;

	int TotalFields = C.XFields() * C.YFields();
	pTimeStructs[f + (s * TotalFields)].EndClustering = GetTickCount();
	if (ProcessVariables.Field < TotalFields)
	{
		CycleAverages.Clustering[s].max += pTimeStructs[f + (s * TotalFields)].EndClustering - pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].StartField;
		CycleAverages.Clustering[s].samples++;
		}
	int i, j;
	imindex = (ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % (1 + ProcessVariables.FieldDelay);	
	s = ProcessVariables.pFieldSideRec[imindex].Side;
	f = ProcessVariables.pFieldSideRec[imindex].Field;
	for (i = 0; i < C.VLayers; i++)
	{
		t_GrabStruct &r = pGrabStructs[(f + (s * TotalFields)) * C.VLayers + i];
		r.CCount = ProcessVariables.pAIS[imindex].pImages[i].ClusterCount;//ProcessVariables.pRec[i].Count;
		r.Z = Frag.Fragment.pViews[f].Layers[s].pLayerInfo[i].Z;
		CCount[s] += ProcessVariables.pAIS[imindex].pImages[i].ClusterCount;
		};
	
	if (ProcessVariables.PreserveClusters)
	{
		for (i = 0; i < C.VLayers; i++)
		{
			if (ProcessVariables.pAIS[imindex].pImages[i].ClusterCount > (MaxSavedClusters - SavedClusterCount)) 
			{
				MaxSavedClusters = 0;
				pSavedImageIndices[(s * TotalFields + f) * C.VLayers + i].ClusterCount = 0;
				}
			else
			{
				memcpy(pSavedClusters + SavedClusterCount, ProcessVariables.pAIS[imindex].pImages[i].pClusters, ProcessVariables.pAIS[imindex].pImages[i].ClusterCount * sizeof(Cluster));
				pSavedImageIndices[(s * TotalFields + f) * C.VLayers + i].ClusterCount = ProcessVariables.pAIS[imindex].pImages[i].ClusterCount;
				SavedClusterCount += ProcessVariables.pAIS[imindex].pImages[i].ClusterCount;
				}
			pSavedImageIndices[(s * TotalFields + f) * C.VLayers + i].Z = Frag.Fragment.pViews[f].Layers[s].pLayerInfo[i].Z;
			pSavedImageIndices[(s * TotalFields + f) * C.VLayers + i].View = f;
			pSavedImageIndices[(s * TotalFields + f) * C.VLayers + i].IsTop = (s == 0);
			pSavedImageIndices[(s * TotalFields + f) * C.VLayers + i].Layer = i;			
			}
		SavedImageCount = (s * TotalFields + f + 1) * C.VLayers;
/*

		FILE *fout = fopen(m_GrainFile, "a+t");
		if (fout)
		{
			for (i = 0; i < C.VLayers; i++)
				for (j = 0; j < ProcessVariables.pAIS[imindex].pImages[i].ClusterCount; j++)
					fprintf(fout, "%d %d %d %f %d %d %f %f %d\n", f, 1 - s, i, Frag.Fragment.pViews[f].Layers[s].pLayerInfo[i].Z, 
						ProcessVariables.pAIS[imindex].pImages[i].ClusterCount, j, 
						ProcessVariables.pAIS[imindex].pImages[i].pClusters[j].X, ProcessVariables.pAIS[imindex].pImages[i].pClusters[j].Y, 
						ProcessVariables.pAIS[imindex].pImages[i].pClusters[j].Area);
			fclose(fout);
			};
*/		};
	return VSERR_OK;
}

UINT CTestAndConfig::TrackingNotify()
{
	int imindex = (ProcessVariables.AsyncImageIndex + 1) % (1 + ProcessVariables.FieldDelay);
	int s = ProcessVariables.pFieldSideRec[imindex].Side;
	int f = ProcessVariables.pFieldSideRec[imindex].Field;

	int TotalFields = C.XFields() * C.YFields();
	pTimeStructs[f + (s * TotalFields)].EndTracking = GetTickCount();
	if (ProcessVariables.Field < TotalFields)
	{
		CycleAverages.Tracking[s].max += pTimeStructs[f + (s * TotalFields)].EndTracking - pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].StartField;
		CycleAverages.Tracking[s].samples++;
		}
	return VSERR_OK;
}

UINT CTestAndConfig::FittingNotify()
{
	int imindex = (ProcessVariables.AsyncImageIndex + 1) % (1 + ProcessVariables.FieldDelay);
	int s = ProcessVariables.pFieldSideRec[imindex].Side;
	int f = ProcessVariables.pFieldSideRec[imindex].Field;

	int TotalFields = C.XFields() * C.YFields();
	pTimeStructs[f + (s * TotalFields)].EndFitting = GetTickCount();
	if (ProcessVariables.Field < TotalFields)
	{
		CycleAverages.Fitting[s].max += pTimeStructs[f + (s * TotalFields)].EndFitting - pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].StartField;
		CycleAverages.Fitting[s].samples++;
		}
	return VSERR_OK;
}

UINT CTestAndConfig::XYZMotionNotify()
{
	int TotalFields = C.XFields() * C.YFields();
	if (ProcessVariables.Field >= TotalFields) return VSERR_OK;
	CycleAverages.XYZMotion[ProcessVariables.IsTop ? 0 : 1].max += (pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].EndXYZMotion = GetTickCount()) - 
		pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields() * C.YFields()))].StartField;
	CycleAverages.XYZMotion[ProcessVariables.IsTop ? 0 : 1].samples++;
	return VSERR_OK;
}

UINT CTestAndConfig::ZScanNotify()
{
	int TotalFields = C.XFields() * C.YFields();
	if (ProcessVariables.Field >= TotalFields) return VSERR_OK;
	CycleAverages.ZScan[ProcessVariables.IsTop ? 0 : 1].max += (pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].EndZMotion = GetTickCount()) - 
		pTimeStructs[ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : TotalFields)].StartField;
	CycleAverages.ZScan[ProcessVariables.IsTop ? 0 : 1].samples++;
	return VSERR_OK;
}

UINT CTestAndConfig::FrameNotify()
{	
	if (!IsFocusing) pGrabStructs[(ProcessVariables.Field + (ProcessVariables.IsTop ? 0 : (C.XFields() * C.YFields()))) * C.VLayers + ProcessVariables.Layer].Time = GetTickCount();
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
				for (i = 0; i < C.XFields() * C.YFields(); i++)
					for (l = 0; l < C.VLayers; l++)
					{
						t_GrabStruct &r = pGrabStructs[(k * C.XFields() * C.YFields() + i) * C.VLayers + l];
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
				for (i = 0; i < C.XFields() * C.YFields(); i++)
				{
					t_TimeStruct &r = pTimeStructs[k * C.XFields() * C.YFields() + i];
					fprintf(fout, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", k, i, 
						r.StartField - StartTime, r.EndClustering - StartTime, r.EndImageProcessing - StartTime, 
						r.EndTracking - StartTime, r.EndFitting - StartTime, r.EndXYZMotion - StartTime, r.EndZMotion - StartTime);
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
		HRESULT HRes = iIO->Write2((HSySalHANDLE)m_hWnd, (BYTE *)&Frag, &ExtErrorInfo, (UCHAR *)Temp.GetBuffer(1));
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
		case IDC_TC_TS_GRAB:	if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 0, 0), n, CycleAverages.Clustering + o);
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

		case IDC_TC_TS_XY:		if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(0, 0, 255), n, CycleAverages.XYZMotion + o);
								else DrawTimeStructBar(&MyDC, nIDCtl, RGB(255, 255, 255), 0, 0);
								break;

		case IDC_TC_TS_Z:		if (!RunStatus && HasRun) DrawTimeStructBar(&MyDC, nIDCtl, RGB(0, 0, 128), n, CycleAverages.ZScan + o);
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


UINT CTestAndConfig::Init()
{
	UINT Err = CVertigoScanner::Init();
	if (Err != VSERR_OK) return Err;
	GRABBERINFOSTRUCT GIS;
	iFG->GrabInfo(&GIS);
	if (GIS.Planes == 1) 
	{
		ppImagesSaved = (BYTE **)malloc(GIS.Width * GIS.Height * C.VLayers + sizeof(BYTE *) * C.VLayers);
		int i;
		for (i = 0; i < C.VLayers; i++)
			ppImagesSaved[i] = (BYTE *)((BYTE *)(void *)ppImagesSaved + C.VLayers * sizeof(BYTE *) + i * GIS.Width * GIS.Height);
		}
	pSavedImageIndices = (SavedImageIndex *)malloc(sizeof(SavedImageIndex) * 2 * C.XFields() * C.YFields() * C.VLayers);
	MaxSavedClusters = 30 * 1048576 / sizeof(Cluster);
	while (MaxSavedClusters > 0 && !(pSavedClusters = (Cluster *)GlobalAlloc(GMEM_FIXED, sizeof(Cluster) * MaxSavedClusters))) MaxSavedClusters /= 2;
	SavedImageCount = SavedClusterCount = 0;
	return VSERR_OK;
	}

UINT CTestAndConfig::Free()
{
	if (ppImagesSaved)
	{
		free(ppImagesSaved);
		}
	if (pSavedClusters)
	{
		GlobalFree(pSavedClusters);
		pSavedClusters = 0;
		}
	if (pSavedImageIndices)
	{
		free(pSavedImageIndices);
		pSavedImageIndices = 0;
		}
	return CVertigoScanner::Free();
	}

void CTestAndConfig::WaitForProcessingComplete()
{
	if (ppImagesSaved && m_SaveImages)
	{
		iVP4->VPWaitForProcessingCompleteAndExtractImages(ppImagesSaved);
		}
	else iVP->VPWaitForProcessingComplete();
	ImageProcessingNotify();

}
