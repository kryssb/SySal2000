// Scan.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Scan.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DUMPTIME(op) { FILE *ftime = fopen("c:\\acq\\time.txt", "a+t"); fprintf(ftime, "%d %d\n", op, GetTickCount()); fclose(ftime); }
//#define DUMPTIME(op)

/////////////////////////////////////////////////////////////////////////////
// CScan dialog

float CScan::ZSetDepot = 0.0f;

#define CHECK_AUTOZ(x) \
{ if (RemoteScan && (ZSetDepot != AutoZReset)) MessageBox(x, "Trap hit!", MB_OK); }

CScan::CScan(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
	ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
	ConfigData &c, Identifier id, float minx, float maxx, float miny, float maxy, CWnd* pParent /*=NULL*/,
	bool *pFragmentResumeList, char *forcedname, bool remotescan, float autozreset, bool trustz)
	: CDialog(CScan::IDD, pParent), phWnd(phwnd), CVertigoScanner(iself, iio, ist, iob, 
		ifg, ivp, itk1, ift1, itk2, ift2, ism, c), Terminate(false), 
		ForcedName(forcedname), RemoteScan(remotescan), AutoZReset(autozreset), TrustZ(trustz)
{
	//{{AFX_DATA_INIT(CScan)
	//}}AFX_DATA_INIT
	pFocusInfo = (t_FocusInfo *)malloc(sizeof(t_FocusInfo) * (MaxFocusInfo = 1000));
	CurrentFocusInfo = 0;

	pDWrHead = pDWrTail = 0;
	HDataWriteMutex = CreateMutex(NULL, FALSE, NULL);
	HDataWriteAvailableSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
	pDataWriteThread = AfxBeginThread((AFX_THREADPROC)DataWriteThreadHook, this, THREAD_PRIORITY_NORMAL, 65536, CREATE_SUSPENDED, NULL);
	pDataWriteThread->m_bAutoDelete = false;
	pDataWriteThread->ResumeThread();

	NextPreloaded = false;
	RunStatus = false;
	Reusable = false;
	Cat.Hdr.ID = id;
	Cat.Hdr.Type.InfoType = VS_HEADER_BYTES | VS_CATALOG_SECTION;
	Cat.Hdr.Type.HeaderFormat = VS_HEADER_TYPE;
	Cat.Area.XMin = minx;
	Cat.Area.XMax = maxx;
	Cat.Area.YMin = miny;
	Cat.Area.YMax = maxy;
	Cat.pFragmentIndices = 0;
	Cat.Config.pConfigs = 0;
	Cat.Config.CountOfConfigs = 0;
	pFragmentData = 0;
	DUMPTIME(0);
	CheckInit();
	DUMPTIME(1);
	pScanFragment = (bool *)malloc(sizeof(bool) * Cat.Area.Fragments);
	if (pFragmentResumeList) memcpy(pScanFragment, pFragmentResumeList, sizeof(bool) * Cat.Area.Fragments);
	else 
	{
		int i;
		for (i = 0; i < Cat.Area.Fragments; pScanFragment[i++] = true);
		};
}

CScan::CScan(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
	ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
	ConfigData &c, CWnd* pParent, float autozreset, bool trustz)
	: CDialog(CScan::IDD, pParent), phWnd(phwnd), CVertigoScanner(iself, iio, ist, iob, 
		ifg, ivp, itk1, ift1, itk2, ift2, ism, c), Terminate(false), 
		ForcedName(0), RemoteScan(true), AutoZReset(autozreset), TrustZ(trustz)
{
	pFocusInfo = (t_FocusInfo *)malloc(sizeof(t_FocusInfo) * (MaxFocusInfo = 1000));
	CurrentFocusInfo = 0;

	pDWrHead = pDWrTail = 0;
	HDataWriteMutex = CreateMutex(NULL, FALSE, NULL);
	HDataWriteAvailableSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
	pDataWriteThread = AfxBeginThread((AFX_THREADPROC)DataWriteThreadHook, this, THREAD_PRIORITY_NORMAL, 65536, CREATE_SUSPENDED, NULL);
	pDataWriteThread->m_bAutoDelete = false;
	pDataWriteThread->ResumeThread();

	NextPreloaded = false;
	RunStatus = false;
	Reusable = true;
	Cat.pFragmentIndices = 0;
	Cat.Config.pConfigs = 0;
	Cat.Config.CountOfConfigs = 0;
	pFragmentData = 0;
	pScanFragment = 0;
}

void CScan::SetZAndTrust(bool trustz, float autozreset)
{
	TrustZ = trustz;
	AutoZReset = autozreset;
	if (!trustz) CurrentFocusInfo = 0;
}

UINT CScan::ResetAndScan(Identifier id, float minx, float maxx, float miny, float maxy, bool *pFragmentResumeList, char *forcedname, bool trustz)
{
	Free();
	if (pScanFragment) free(pScanFragment);
	if (pFragmentData) GlobalFree(pFragmentData);
	if (Cat.pFragmentIndices) GlobalFree(Cat.pFragmentIndices);
	if (Cat.Config.pConfigs) 
	{
		int i;
		for (i = 0; i < Cat.Config.CountOfConfigs; i++)
			if (Cat.Config.pConfigs[i].Config.pItems) CoTaskMemFree(Cat.Config.pConfigs[i].Config.pItems);
		delete [] Cat.Config.pConfigs;
		};
	ForcedName = forcedname;
	TrustZ = trustz;
	Cat.Hdr.ID = id;
	Cat.Hdr.Type.InfoType = VS_HEADER_BYTES | VS_CATALOG_SECTION;
	Cat.Hdr.Type.HeaderFormat = VS_HEADER_TYPE;
	Cat.Area.XMin = minx;
	Cat.Area.XMax = maxx;
	Cat.Area.YMin = miny;
	Cat.Area.YMax = maxy;
	Cat.pFragmentIndices = 0;
	Cat.Config.pConfigs = 0;
	Cat.Config.CountOfConfigs = 0;
	pFragmentData = 0;
	DUMPTIME(0);
	CheckInit();
	DUMPTIME(1);
	pScanFragment = (bool *)malloc(sizeof(bool) * Cat.Area.Fragments);
	if (pFragmentResumeList) memcpy(pScanFragment, pFragmentResumeList, sizeof(bool) * Cat.Area.Fragments);
	else 
	{
		int i;
		for (i = 0; i < Cat.Area.Fragments; pScanFragment[i++] = true);
		};	
	return DoModal();
}

void CScan::EnsureUnlock()
{
	VPUnlock();
}


void CScan::PreloadNext(double nextminx, double nextminy, double nextmaxx, double nextmaxy)
{
	NextPreloaded = true;
	NextMinX = nextminx;
	NextMinY = nextminy;
	NextMaxX = nextmaxx;
	NextMaxY = nextmaxy;	
	iSM->DirFixPoint((NextMinX + NextMaxX) * 0.5, (NextMinY + NextMaxY) * 0.5);
	if (iSM->DirMapPoint((NextMinX + NextMaxX) * 0.5, (NextMinY + NextMaxY) * 0.5, &NextTargetX, &NextTargetY) != S_OK)
		NextPreloaded = false;	
	}

UINT CScan::Scan(float startx, float starty, bool xforward, bool yforward)
{
	if (SingleViewMode)
		return CVertigoScanner::ScanSingleView(startx, starty, NextPreloaded, NextTargetX, NextTargetY);
	else
	{
		UINT Ret = CVertigoScanner::Scan(startx, starty, xforward, yforward);
		if (NextPreloaded)
		{
			iSt->PosMove(0, NextTargetX, C.HSpeed, C.HAcc);
			iSt->PosMove(1, NextTargetY, C.HSpeed, C.HAcc);
			}
		return Ret;
		}
	}

CScan::~CScan()
{
	EnsureUnlock();
	Free();
	if (pScanFragment) free(pScanFragment);
	if (pFragmentData) GlobalFree(pFragmentData);
	if (Cat.pFragmentIndices) GlobalFree(Cat.pFragmentIndices);
	if (Cat.Config.pConfigs) 
	{
		int i;
		for (i = 0; i < Cat.Config.CountOfConfigs; i++)
			if (Cat.Config.pConfigs[i].Config.pItems) CoTaskMemFree(Cat.Config.pConfigs[i].Config.pItems);
		delete [] Cat.Config.pConfigs;
		};
	Terminate = true;
	SetEvent(HDataWriteAvailableSignal);
	WaitForSingleObject(pDataWriteThread->m_hThread, INFINITE);
	delete pDataWriteThread;
	CloseHandle(HDataWriteAvailableSignal);
	CloseHandle(HDataWriteMutex);
	free(pFocusInfo);
	};


void CScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScan)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScan, CDialog)
	//{{AFX_MSG_MAP(CScan)
	ON_BN_CLICKED(IDC_SM_CONTINUE, OnContinue)
	ON_BN_CLICKED(IDC_SM_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_SM_START, OnStart)
	ON_BN_CLICKED(IDC_SM_STOP, OnStop)
	ON_BN_CLICKED(IDC_SM_CNTRS_BOTTOMAVGGRAINS, OnCntrsBottomAvgGrains)
	ON_BN_CLICKED(IDC_SM_CNTRS_BOTTOMIMAGEHOM, OnCntrsBottomImageHom)
	ON_BN_CLICKED(IDC_SM_CNTRS_BOTTOMTRACKDENSITY, OnCntrsBottomTrackDensity)
	ON_BN_CLICKED(IDC_SM_CNTRS_BOTTOMVALIDLAYERS, OnCntrsBottomValidLayers)
	ON_BN_CLICKED(IDC_SM_CNTRS_FOCUSFAULTS, OnCntrsFocusFaults)
	ON_BN_CLICKED(IDC_SM_CNTRS_STAGEFAULTS, OnCntrsStageFaults)
	ON_BN_CLICKED(IDC_SM_CNTRS_TOPAVGGRAINS, OnCntrsTopAvgGrains)
	ON_BN_CLICKED(IDC_SM_CNTRS_TOPIMAGEHOM, OnCntrsTopImageHom)
	ON_BN_CLICKED(IDC_SM_CNTRS_TOPTRACKDENSITY, OnCntrsTopTrackDensity)
	ON_BN_CLICKED(IDC_SM_CNTRS_TOPVALIDLAYERS, OnCntrsTopValidLayers)
	ON_BN_CLICKED(IDC_SM_EXIT, OnExit)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

LRESULT CScan::OnStatusChange(WPARAM wParam, LPARAM lParam)
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

		case UM_END:					
		case UM_ERROR:
		case UM_STOP:
										{		
											RunStatus = false;
											if (Terminate) EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
											else if (RemoteScan) EndDialog(wParam);
											else
											{
												EnableControls();
												};
											};
										break;
		};
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CScan message handlers

void CScan::OnContinue() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnPause() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnStart() 
{
	// TODO: Add your control notification handler code here
	ZSetDepot = AutoZReset;
	RunStatus = true;
	EnableControls();
	pThread = AfxBeginThread((AFX_THREADPROC)ThreadHook, this, THREAD_PRIORITY_NORMAL, 65536, 0, NULL);	
}

void CScan::OnStop() 
{
	// TODO: Add your control notification handler code here
	pThread->PostThreadMessage(UM_CHANGE_STATUS, UM_STOP, 0);
}

void CScan::OnCntrsBottomAvgGrains() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsBottomImageHom() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsBottomTrackDensity() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsBottomValidLayers() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsFocusFaults() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsStageFaults() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsTopAvgGrains() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsTopImageHom() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsTopTrackDensity() 
{
	// TODO: Add your control notification handler code here
	
}

void CScan::OnCntrsTopValidLayers() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;	

	CString Temp;
	Temp.Format("%d", Cat.Hdr.ID.Part[0]);
	SendDlgItemMessage(IDC_SM_ID1, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Hdr.ID.Part[1]);
	SendDlgItemMessage(IDC_SM_ID2, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Hdr.ID.Part[2]);
	SendDlgItemMessage(IDC_SM_ID3, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Hdr.ID.Part[3]);
	SendDlgItemMessage(IDC_SM_ID4, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Area.Fragments);
	SendDlgItemMessage(IDC_SM_TOTALFRAGMENTS, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	SendDlgItemMessage(IDC_SM_FRAGPROGRESS, PBM_SETRANGE32, 0, Cat.Area.Fragments);
	SendDlgItemMessage(IDC_SM_FRAGPROGRESS, PBM_SETPOS, 0, 0);
	SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETRANGE32, 0, C.XFields * C.YFields);
	SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, 0, 0);
	SendDlgItemMessage(IDC_SM_VALIDLAYERS, PBM_SETBKCOLOR, 0, (LPARAM)RGB(255, 255, 255));
	SendDlgItemMessage(IDC_SM_VALIDLAYERS, PBM_SETBARCOLOR, 0, (LPARAM)RGB(0, 224, 0));
	SendDlgItemMessage(IDC_SM_VALIDLAYERS, PBM_SETRANGE32, 0, C.VLayers - C.VInactiveLayers);
	SendDlgItemMessage(IDC_SM_VALIDLAYERS, PBM_SETPOS, 0, 0);
	SendDlgItemMessage(IDC_SM_TOPTRACKS, PBM_SETBKCOLOR, 0, (LPARAM)RGB(255, 255, 255));
	SendDlgItemMessage(IDC_SM_TOPTRACKS, PBM_SETBARCOLOR, 0, (LPARAM)RGB(0, 224, 0));
	SendDlgItemMessage(IDC_SM_TOPTRACKS, PBM_SETRANGE32, 0, C.MaxTracks);
	SendDlgItemMessage(IDC_SM_TOPTRACKS, PBM_SETPOS, 0, 0);
	SendDlgItemMessage(IDC_SM_BOTTOMTRACKS, PBM_SETBKCOLOR, 0, (LPARAM)RGB(255, 255, 255));
	SendDlgItemMessage(IDC_SM_BOTTOMTRACKS, PBM_SETBARCOLOR, 0, (LPARAM)RGB(0, 224, 0));
	SendDlgItemMessage(IDC_SM_BOTTOMTRACKS, PBM_SETRANGE32, 0, C.MaxTracks);
	SendDlgItemMessage(IDC_SM_BOTTOMTRACKS, PBM_SETPOS, 0, 0);	
	EnableControls();

	if (RemoteScan) OnStart();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CScan::ThreadHook(void *pOwner)
{
	return ((CScan *)pOwner)->Thread();
}

UINT CScan::DataWriteThreadHook(void *pOwner)
{
	return ((CScan *)pOwner)->DataWriteThread();
}

void CScan::EnableControls()
{
	GetDlgItem(IDC_SM_START)->EnableWindow(!RunStatus);
	GetDlgItem(IDC_SM_PAUSE)->EnableWindow(false && RunStatus);
	GetDlgItem(IDC_SM_CONTINUE)->EnableWindow(false && RunStatus);
	GetDlgItem(IDC_SM_STOP)->EnableWindow(RunStatus);
	GetDlgItem(IDC_SM_EXIT)->EnableWindow(!RunStatus);
}

void CScan::CheckInit()
{
	OkToRun = false;
	CString Temp;
	UINT Err;
	Free();

	Cat.Area.XStep = C.XStep;
	Cat.Area.YStep = C.YStep;
	Cat.Area.XViews = ceil((Cat.Area.XMax - Cat.Area.XMin) / C.XStep);
	Cat.Area.YViews = ceil((Cat.Area.YMax - Cat.Area.YMin) / C.YStep);
	XFragments = (Cat.Area.XViews + C.XFields - 1) / C.XFields;
	YFragments = (Cat.Area.YViews + C.YFields - 1) / C.YFields;
	Cat.Area.Fragments = XFragments * YFragments;
	Cat.Area.XViews = C.XFields * XFragments;
	Cat.Area.YViews = C.YFields * YFragments;
	//CHANGED!!!
#if 1
	double catcx = (Cat.Area.XMin + Cat.Area.XMax) * 0.5;
	double catcy = (Cat.Area.YMin + Cat.Area.YMax) * 0.5;
	Cat.Area.XMin = catcx - Cat.Area.XStep * Cat.Area.XViews * 0.5;
	Cat.Area.XMax = Cat.Area.XMin + Cat.Area.XStep * Cat.Area.XViews;
	Cat.Area.YMin = catcy - Cat.Area.YStep * Cat.Area.YViews * 0.5;
	Cat.Area.YMax = Cat.Area.YMin + Cat.Area.YStep * Cat.Area.YViews;
	if (Cat.Area.XViews == 1 && Cat.Area.YViews == 1 &&
		(C.ScanningScheme == SCANNING_SCHEME_BOTH_IN_FIELD || C.ScanningScheme == SCANNING_SCHEME_TWO_SIDES)) SingleViewMode = true;
#else
	Cat.Area.XMax = Cat.Area.XMin + Cat.Area.XStep * Cat.Area.XViews;
	Cat.Area.YMax = Cat.Area.YMin + Cat.Area.YStep * Cat.Area.YViews;
#endif

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
	
	
	pFragmentData = (t_FragmentData *)GlobalAlloc(GMEM_FIXED, sizeof(t_FragmentData) * XFragments * YFragments);
	if (!pFragmentData) 
	{
		OkToRun = false;
		Temp = "Fragment indexing data allocation error";
		};

	Cat.pFragmentIndices = (int *)GlobalAlloc(GMEM_FIXED, sizeof(int) * Cat.Area.XViews * Cat.Area.YViews);
	if (!Cat.pFragmentIndices)
	{
		OkToRun = false;
		Temp = "Catalog view indices allocation error";
		};

	if (pFragmentData && Cat.pFragmentIndices)
	{
		int i, j, k;
		if (C.YFields % 2)
		{
			for (i = 0; i < YFragments; i++)
				for (j = 0; j < XFragments; j++)
				{
					t_FragmentData *pFrag = pFragmentData + i * XFragments + j;
					pFrag->XStart = (i % 2) ? (XFragments - 1 - j) : j;
					pFrag->YStart = i;
					};
			}
		else
		{
			for (j = 0; j < XFragments; j++)
				for (i = 0; i < YFragments; i++)
				{
					t_FragmentData *pFrag = pFragmentData + j * YFragments + i;
					pFrag->YStart = (j % 2) ? (YFragments - 1 - i) : i;
					pFrag->XStart = j;
					};
			};


		for (k = 0; k < (XFragments * YFragments); k++)
		{
			int xsize, ysize;
			xsize = Cat.Area.XViews - pFragmentData[k].XStart * C.XFields;
			if (xsize > C.XFields) xsize = C.XFields;
			ysize = Cat.Area.YViews - pFragmentData[k].YStart * C.YFields;
			if (ysize > C.YFields) ysize = C.YFields;
			for (i = 0; i < ysize; i++)
				for (j = 0; j < xsize; j++)
					Cat.pFragmentIndices[(i + pFragmentData[k].YStart * C.YFields) * Cat.Area.XViews + j + pFragmentData[k].XStart * C.XFields] = k + 1;
			};
		};

	{
		Cat.Config.CountOfConfigs = 0;
		iSelf->GetNumberOfConnections(&Cat.Config.CountOfConfigs);
		Cat.Config.pConfigs = new VS_Config[++Cat.Config.CountOfConfigs];

		int i;
		for (i = 0; i < Cat.Config.CountOfConfigs; i++)
		{
			ISySalObject *iTempOb = 0;
			Cat.Config.pConfigs[i].Config.pItems = 0;
			Cat.Config.pConfigs[i].Config.CountOfItems = 0;
			Cat.Config.pConfigs[i].Config.Name[0] = 0;

			if (!i)	
			{
				iTempOb = iSelf;
				iTempOb->AddRef();
				}
			else
			{
				SySalConnection MyConn;
				iSelf->GetConnection(i - 1, &MyConn);
				strncpy(Cat.Config.pConfigs[i].ClassName, MyConn.Name, SYSAL_MAX_CONN_NAME_LEN);
				if (MyConn.pUnknown) MyConn.pUnknown->QueryInterface(IID_ISySalObject, (void **)&iTempOb);
				};
			if (iTempOb)
			{
				char ClassName[SYSAL_MAX_CONN_NAME_LEN];
				iTempOb->GetConfig(&Cat.Config.pConfigs[i].Config);
				iTempOb->GetClassName(ClassName);
				strncpy(Cat.Config.pConfigs[i].Config.Name, ClassName, SYSAL_MAXCONFIG_NAME_LEN);
				iTempOb->Release();
				};
			};
		};

	if (!OkToRun)
		MessageBox(Temp, "Initialization error", MB_ICONERROR | MB_OK);
}

bool CScan::MyShouldStopCallback(DWORD Context)
{
	return ((CScan *)Context)->ShouldStop();
}

UINT CScan::Thread()
{
	UINT ExtErrorInfo;
	UINT Error;
	CString MsgString;
	DataToWrite dwr;
	int i;

	bool UseForced = false;
	char OutName[MAX_FORCED_NAME];
	if (ForcedName)
	{
		if (strlen(ForcedName) < (MAX_FORCED_NAME - 16))
		{
			UseForced = true;
			sprintf(OutName, "%s.rwc", ForcedName);
			}
		}
	DUMPTIME(2);	
	dwr.IsCatalog = true;
	dwr.pCat = Duplicate(Cat);
	if (UseForced) strcpy(dwr.OutName, OutName);
	else dwr.OutName[0] = 0;
	EnqueueDataToWrite(dwr);
/*
	if (iIO->Write2((HSySalHANDLE)m_hWnd, (BYTE *)&Cat, &ExtErrorInfo, UseForced ? (UCHAR *)OutName : 0) != S_OK)
	{
		if (!RemoteScan)
		{
			MsgString.Format("Error creating catalog file!\r\nError code: %08X\r\nAborting batch.", ExtErrorInfo);
			::MessageBox(0, MsgString, "I/O Error", MB_ICONERROR | MB_OK);
			};
		PostMessage(UM_CHANGE_STATUS, UM_ERROR);
		return VSERR_IO_CATALOG;
		};
*/
	DUMPTIME(3);

	VPLock();

	DUMPTIME(4);

	UINT Time;

	iStOb->EnableMonitor(false);
	DUMPTIME(5);
	iSt->EnableManualControl(false);
	DUMPTIME(6);

	iSt->FlushAsyncMotions();
	DUMPTIME(7);

	if (!SingleViewMode)
	{
		AsyncGoTo3DTrajectory AGT;
		AGT.DeadBand.X = AGT.DeadBand.Y = C.HTol;
		AGT.DeadBand.Z = C.VTol;
		AGT.NewAcc.X = AGT.NewAcc.Y = C.HAcc;
		AGT.NewAcc.Z = C.VAcc;
		double MX = Cat.Area.XMin;
		double MY = Cat.Area.YMin;
		iSM->DirFixPoint(MX, MY);
		iSM->DirMapPoint(MX, MY, &MX, &MY);
		AGT.NewPos.X = MX;
		AGT.NewPos.Y = MY;
		CHECK_AUTOZ("Z1A");
		iSt->GetPos(2, &AGT.NewPos.Z);
		AGT.NewSpeed.X = AGT.NewSpeed.Y = C.HSpeed;
		AGT.NewSpeed.Z = C.VSpeed;
		AGT.StopDelay = C.XYZMotionDuration;
		iSt->PrepareAsyncGoTo3DMotion(&AGT);
		iSt->StartAsyncMotion();
		if (iSt->WaitForAsyncMotionComplete((DWORD)MyShouldStopCallback, (DWORD)this) != S_OK)
		{
			VPUnlock();
			PostMessage(UM_CHANGE_STATUS, UM_ERROR);
			return VSERR_UNKNOWN;
			}
		}	
	if ((Error = PrepareFocusInfo()) != VSERR_OK) 
	{
		VPUnlock();
		PostMessage(UM_CHANGE_STATUS, UM_ERROR);
		return Error;
		};

	StartTime = GetTickCount();
	TotalViews = 0;

	CHECK_AUTOZ("Z1B");

	DUMPTIME(8);
	for (CurrentFragment = 1; !ShouldStop() && (CurrentFragment <= (XFragments * YFragments)); CurrentFragment++)
	{
		DUMPTIME(9);
		MsgString.Format("%d", CurrentFragment);

		SendDlgItemMessage(IDC_SM_CURRENTFRAGMENT, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MsgString);
		SendDlgItemMessage(IDC_SM_FRAGPROGRESS, PBM_SETPOS, CurrentFragment - 1, 0);
		CHECK_AUTOZ("Z1C");
		if (!(pScanFragment[CurrentFragment - 1])) continue;
		double StartX, StartY;
		float CurrX, CurrY;
		if (ShouldStop()) 
		{
			VPUnlock();
			PostMessage(UM_CHANGE_STATUS, UM_STOP);
			return VSERR_TERMINATED;
			};
		CHECK_AUTOZ("Z1D");
		//CHANGED!!!
#if 1
		StartX = pFragmentData[CurrentFragment - 1].XStart * C.XFields * Cat.Area.XStep + Cat.Area.XMin + Cat.Area.XStep * 0.5;
		StartY = pFragmentData[CurrentFragment - 1].YStart * C.YFields * Cat.Area.YStep + Cat.Area.YMin + Cat.Area.YStep * 0.5;
#else
		StartX = pFragmentData[CurrentFragment - 1].XStart * C.XFields * Cat.Area.XStep + Cat.Area.XMin;
		StartY = pFragmentData[CurrentFragment - 1].YStart * C.YFields * Cat.Area.YStep + Cat.Area.YMin;
#endif
/* TODO: IMPROVE CHECKS!!! */
		iSM->DirFixPoint(StartX, StartY);
		iSM->DirMapPoint(StartX, StartY, &StartX, &StartY);
		iSt->GetPos(0, &CurrX);
		iSt->GetPos(1, &CurrY);
		CHECK_AUTOZ("Z1E");
/*
		VPUnlock(); // for odyssey stabilization
		VPLock(); // for odyssey stabilization
*/		
		DUMPTIME(10);
		Error = Scan(StartX, StartY, (2 * (CurrX - StartX) / C.XStep) < C.XFields, (2 * (CurrY - StartY) / C.YStep) < C.YFields);
		DUMPTIME(11);
		CHECK_AUTOZ("Z1F");
		if (ShouldStop())
		{
			iSt->Stop(0);
			iSt->Stop(1);
			iSt->Stop(2);
			};
		CHECK_AUTOZ("Z1G");
		if (Error == VSSCAN_OK)
		{
			CurrentRelevantZs = Frag.Fragment.pViews[Frag.Fragment.CountOfViews - 1].RelevantZs;
// IMAD BUG #1
			CurrentRelevantZs.TopExt /= CSP.RefractiveShrinkage;
			CurrentRelevantZs.TopInt /= CSP.RefractiveShrinkage;
			CurrentRelevantZs.BottomInt /= CSP.RefractiveShrinkage;
			CurrentRelevantZs.BottomExt /= CSP.RefractiveShrinkage;
// END IMAD BUG #1

			AddFocusInfo(Frag.Fragment.pViews[Frag.Fragment.CountOfViews - 1].MapX[0], Frag.Fragment.pViews[Frag.Fragment.CountOfViews - 1].MapY[0], CurrentRelevantZs);

			for (i = 0; i < Frag.Fragment.CountOfViews; i++)
			{
				Frag.Fragment.pViews[i].TileX += pFragmentData[CurrentFragment - 1].XStart * C.XFields;		
				Frag.Fragment.pViews[i].TileY += pFragmentData[CurrentFragment - 1].YStart * C.YFields;		
				};
			CHECK_AUTOZ("Z1H");

			Frag.Fragment.StartView = pFragmentData[CurrentFragment - 1].XStart * C.XFields + pFragmentData[CurrentFragment - 1].YStart * C.YFields * Cat.Area.XViews;
			Frag.Hdr.ID = Cat.Hdr.ID;
			Frag.Fragment.Index = CurrentFragment;			

			if (UseForced) sprintf(OutName, "%s.rwd.%08X", ForcedName, Frag.Fragment.Index);

			CHECK_AUTOZ("Z1I");

			dwr.IsCatalog = false;
			dwr.pFrag = Duplicate(Frag);
			if (UseForced) strcpy(dwr.OutName, OutName);
			else dwr.OutName[0] = 0;
			EnqueueDataToWrite(dwr);

/*
			if (iIO->Write2(0, (BYTE *)&Frag, &Error, UseForced ? (UCHAR *)OutName : 0) != S_OK)
			{
				VPUnlock();
				PostMessage(UM_CHANGE_STATUS, UM_ERROR);
				Error = VSERR_IO_ERROR;
				break;
				};
*/
			};
		DUMPTIME(12);
/* TODO: IMPROVE CHECKS!!! */
		};
	DUMPTIME(13);
	CHECK_AUTOZ("Z1J");
	MsgString.Format("%d", CurrentFragment - 1);
	SendDlgItemMessage(IDC_SM_CURRENTFRAGMENT, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MsgString);
	SendDlgItemMessage(IDC_SM_FRAGPROGRESS, PBM_SETPOS, CurrentFragment - 1, 0);
	if (!Reusable) VPUnlock();
	else
	{
		for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
		{
			iVP->VPStartAsyncProcessing();
			iVP->VPWaitForProcessingComplete();
			}
		}
	SendDlgItemMessage(IDC_SM_TIMETOCOMPL, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"0:00:00");
	Time = GetTickCount() - StartTime;
	char temp[32];
	sprintf(temp, "%d:%02d:%02d", Time / 3600000, ((Time / 1000) / 60) % 60, (Time / 1000) % 60);
	SendDlgItemMessage(IDC_SM_TOTALTIME, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	PostMessage(UM_CHANGE_STATUS, (Error == VSSCAN_OK) ? UM_END : UM_ERROR);
	CHECK_AUTOZ("Z1K");
	DUMPTIME(14);
	return (Error == VSSCAN_OK) ? VSERR_OK : VSERR_SCANNING_ERROR;
}

UINT CScan::GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop)
{
	F = CurrentRelevantZs;
	return VSSCAN_OK;
	};

UINT CScan::PrepareFocusInfo()
{
	float Z;
	//CHANGED!!!
#if 1
	if (RemoteScan)
	{		
		if (TrustZ && SingleViewMode && GetNearestFocusInfo(Cat.Area.XMin, Cat.Area.YMin, CurrentRelevantZs)) return VSSCAN_OK;
		Z = AutoZReset;		
		if (TrustZ && SingleViewMode)
		{
			CurrentRelevantZs.TopInt = Z;
			CurrentRelevantZs.TopExt = Z + C.VStep(true);
			CurrentRelevantZs.BottomInt = Z - C.BaseThickness;
			CurrentRelevantZs.BottomExt = CurrentRelevantZs.BottomInt - C.VStep(false);
			return VSSCAN_OK;
			}
		}			
#else
	if (RemoteScan) Z = AutoZReset;
#endif
	else
	{
		VPUnlock();
		iStOb->EnableMonitor(true);
		::MessageBox(0, "Place the stage at the top surface of the plastic base and press OK", "Help Request", MB_ICONQUESTION | MB_OK);
		iSt->GetPos(2, &Z);
		iStOb->EnableMonitor(false);		
		iSt->EnableManualControl(false);
		VPLock();
		}
	
	CurrentRelevantZs.TopInt = Z;
	CurrentRelevantZs.TopExt = Z + C.VStep(true);
	CurrentRelevantZs.BottomInt = Z - C.BaseThickness;
	CurrentRelevantZs.BottomExt = CurrentRelevantZs.BottomInt - C.VStep(false);

	double X = Cat.Area.XMin;
	double Y = Cat.Area.YMin;
	iSM->DirFixPoint(X, Y);
	iSM->DirMapPoint(X, Y, &X, &Y);
/*
	float X, Y;
	iSt->GetPos(0, &X);
	iSt->GetPos(1, &Y);
*/
	return CVertigoScanner::GetFocus(X, Y, CurrentRelevantZs);
	};

bool CScan::ShouldStop()
{
	MSG Msg;
	if (PeekMessage(&Msg, 0, 0, 0, PM_NOREMOVE))
		if (Msg.message == UM_CHANGE_STATUS && Msg.wParam == UM_STOP) 
		{
			PostThreadMessage(pThread->m_nThreadID, UM_CHANGE_STATUS, UM_STOP, 0);
			return true;
			}
		else PeekMessage(&Msg, 0, 0, 0, PM_REMOVE);
	return false;
}

void CScan::OnExit() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

UINT CScan::FittingNotify()
{
	unsigned Time;
	unsigned vmult;
	Time = GetTickCount() - StartTime;	
	char temp[32];
	switch (C.ScanningScheme) 
	{
		case SCANNING_SCHEME_TOPSIDE:			
		case SCANNING_SCHEME_BOTTOMSIDE:		TotalViews = (CurrentFragment - 1) * C.XFields * C.YFields + ProcessVariables.Field;
												vmult = 1;												
												sprintf(temp, "%d", ProcessVariables.Field + 1);
												SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, ProcessVariables.Field + 1, 0);
												break;
												
												
		case SCANNING_SCHEME_BOTH_IN_FIELD:		TotalViews = ((CurrentFragment - 1) * C.XFields * C.YFields + ProcessVariables.Field) * 2 + (ProcessVariables.IsTop ? 0 : 1);
												vmult = 2;
												sprintf(temp, "%d", ProcessVariables.Field + 1);
												SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, ProcessVariables.Field + 1, 0);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			TotalViews = ((CurrentFragment - 1) * 2 + (ProcessVariables.IsTop ? 0 : 1)) * C.XFields * C.YFields + ProcessVariables.Field;
												vmult = 2;
												sprintf(temp, "%d", ProcessVariables.Field + (C.XFields * C.YFields) * (ProcessVariables.IsTop ? 0 : 1) + 1);
												SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, ProcessVariables.Field + 1 + (C.XFields * C.YFields) * (ProcessVariables.IsTop ? 0 : 1), 0);
												break;
		}

	SendDlgItemMessage(IDC_SM_CURRENTVIEW, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);

	unsigned TimeToCompletion = Time * (float)(Cat.Area.XViews * Cat.Area.YViews * vmult - TotalViews) / TotalViews;	
	sprintf(temp, "%d:%02d:%02d", TimeToCompletion / 3600000, ((TimeToCompletion / 1000) / 60) % 60, (TimeToCompletion / 1000) % 60);
	SendDlgItemMessage(IDC_SM_TIMETOCOMPL, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	sprintf(temp, "%d:%02d:%02d", Time / 3600000, ((Time / 1000) / 60) % 60, (Time / 1000) % 60);
	SendDlgItemMessage(IDC_SM_TOTALTIME, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	SendDlgItemMessage(IDC_SM_TOPTRACKS, PBM_SETBARCOLOR, 0, (ProcessVariables.TCount[0] > 0.9 * C.MaxTracks) ? (LPARAM)RGB(255, 0, 0) : (LPARAM)RGB(0, 224, 0));
	SendDlgItemMessage(IDC_SM_TOPTRACKS, PBM_SETPOS, ProcessVariables.TCount[0], 0);
	SendDlgItemMessage(IDC_SM_BOTTOMTRACKS, PBM_SETBARCOLOR, 0, (ProcessVariables.TCount[0] > 0.9 * C.MaxTracks) ? (LPARAM)RGB(255, 0, 0) : (LPARAM)RGB(0, 224, 0));
	SendDlgItemMessage(IDC_SM_BOTTOMTRACKS, PBM_SETPOS, ProcessVariables.TCount[1], 0);
	return VSERR_OK;
}

UINT CScan::StartNotify()
{
	char temp[32];
	UINT CountOfViews = Frag.Fragment.CountOfViews;
	if (C.ScanningScheme == SCANNING_SCHEME_TWO_SIDES) CountOfViews *= 2;
	sprintf(temp, "%d", CountOfViews);

	SendDlgItemMessage(IDC_SM_TOTALVIEWS, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	SendDlgItemMessage(IDC_SM_CURRENTVIEW, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"0");
	SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETRANGE32, 0, CountOfViews);
	SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, 0, 0);
	SendDlgItemMessage(IDC_SM_VALIDLAYERS, PBM_SETPOS, 0, 0);
	SendDlgItemMessage(IDC_SM_TOPTRACKS, PBM_SETPOS, 0, 0);
	SendDlgItemMessage(IDC_SM_BOTTOMTRACKS, PBM_SETPOS, 0, 0);
	return VSERR_OK;
}

BOOL CScan::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam == 2 /* ESC Key Trap */) return TRUE;
	return CDialog::OnCommand(wParam, lParam);
}

UINT CScan::ClusteringNotify()
{
	SendDlgItemMessage(IDC_SM_VALIDLAYERS, PBM_SETBARCOLOR, 0, (ProcessVariables.ValidLayers >= C.MinValidLayers) ? (LPARAM)RGB(0, 224, 0) : (LPARAM)RGB(255, 0, 0));
	SendDlgItemMessage(IDC_SM_VALIDLAYERS, PBM_SETPOS, ProcessVariables.ValidLayers, 0);
	return VSERR_OK;
}

IO_VS_Catalog *CScan::Duplicate(IO_VS_Catalog &Cat)
{
	IO_VS_Catalog *pCat = (IO_VS_Catalog *)malloc(sizeof(IO_VS_Catalog));
	pCat->Area = Cat.Area;
	pCat->Hdr = Cat.Hdr;
	pCat->pFragmentIndices = (int *)malloc(sizeof(int) * Cat.Area.Fragments);
	memcpy(pCat->pFragmentIndices, Cat.pFragmentIndices, sizeof(int) * Cat.Area.Fragments);
	memcpy(pCat->Reserved, Cat.Reserved, sizeof(Cat.Reserved));
	pCat->Config.CountOfConfigs = Cat.Config.CountOfConfigs;
	pCat->Config.pConfigs = (VS_Config *)malloc(sizeof(VS_Config) * Cat.Config.CountOfConfigs);
	int i;
	for (i = 0; i < Cat.Config.CountOfConfigs; i++)
	{
		memcpy(pCat->Config.pConfigs[i].ClassName, Cat.Config.pConfigs[i].ClassName, sizeof(Cat.Config.pConfigs[i].ClassName));
		memcpy(pCat->Config.pConfigs[i].Config.Name, Cat.Config.pConfigs[i].Config.Name, sizeof(Cat.Config.pConfigs[i].Config.Name));
		pCat->Config.pConfigs[i].Config.CountOfItems = Cat.Config.pConfigs[i].Config.CountOfItems;
		pCat->Config.pConfigs[i].Config.pItems = (char *)malloc(Cat.Config.pConfigs[i].Config.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		memcpy(pCat->Config.pConfigs[i].Config.pItems, Cat.Config.pConfigs[i].Config.pItems, Cat.Config.pConfigs[i].Config.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	}
	return pCat;
}

IO_VS_Fragment2 *CScan::Duplicate(IO_VS_Fragment2 &Frag)
{
	IO_VS_Fragment2 *pFrag = (IO_VS_Fragment2 *)malloc(sizeof(IO_VS_Fragment2));
	pFrag->Hdr = Frag.Hdr;
	memcpy(pFrag->Reserved, Frag.Reserved, sizeof(Frag.Reserved));
	pFrag->Fragment.CodingMode = Frag.Fragment.CodingMode;
	pFrag->Fragment.CountOfViews = Frag.Fragment.CountOfViews;
	pFrag->Fragment.FitCorrectionDataSize = Frag.Fragment.FitCorrectionDataSize;
	pFrag->Fragment.Index = Frag.Fragment.Index;
	pFrag->Fragment.StartView = Frag.Fragment.StartView;
	pFrag->Fragment.pViews = (VS_View2 *)malloc(sizeof(VS_View2) * Frag.Fragment.CountOfViews);
	int v, s, i;
	for (v = 0; v < Frag.Fragment.CountOfViews; v++)
	{
		VS_View2 &rv = pFrag->Fragment.pViews[v];
		VS_View2 &orv = Frag.Fragment.pViews[v];
		rv.TileX = orv.TileX;
		rv.TileY = orv.TileY;
		rv.RelevantZs = orv.RelevantZs;
		for (s = 0; s < 2; s++)
		{
			rv.X[s] = orv.X[s];
			rv.Y[s] = orv.Y[s];
			rv.MapX[s] = orv.MapX[s];
			rv.MapY[s] = orv.MapY[s];
			rv.ImageMat[s][0][0] = orv.ImageMat[s][0][0];
			rv.ImageMat[s][0][1] = orv.ImageMat[s][0][1];
			rv.ImageMat[s][1][0] = orv.ImageMat[s][1][0];
			rv.ImageMat[s][1][1] = orv.ImageMat[s][1][1];
			rv.Status[s] = orv.Status[s];
			rv.TCount[s] = orv.TCount[s];
			rv.Layers[s].Count = orv.Layers[s].Count;
			rv.Layers[s].pLayerInfo = (VS_View2::t_LayerInfo *)malloc(sizeof(VS_View2::t_LayerInfo) * rv.Layers[s].Count);
			memcpy(rv.Layers[s].pLayerInfo, orv.Layers[s].pLayerInfo, sizeof(VS_View2::t_LayerInfo) * rv.Layers[s].Count);
			rv.pTracks[s] = (Track2 *)malloc(sizeof(Track2) * rv.TCount[s]);
			for (i = 0; i < rv.TCount[s]; i++)
			{
				rv.pTracks[s][i] = orv.pTracks[s][i];
				if (rv.pTracks[s][i].pGrains)
				{
					rv.pTracks[s][i].pGrains = (Grain *)malloc(sizeof(Grain) * rv.pTracks[s][i].Grains);
					memcpy(rv.pTracks[s][i].pGrains, orv.pTracks[s][i].pGrains, sizeof(Grain) * rv.pTracks[s][i].Grains);
					}
				if (rv.pTracks[s][i].pCorrection)
				{
					rv.pTracks[s][i].pCorrection = (BYTE *)malloc(Frag.Fragment.FitCorrectionDataSize);
					memcpy(rv.pTracks[s][i].pCorrection, orv.pTracks[s][i].pCorrection, Frag.Fragment.FitCorrectionDataSize);
					}
				}
			}
		}
	return pFrag;
}

void CScan::Delete(IO_VS_Catalog *pCat)
{
	if (pCat->pFragmentIndices) free(pCat->pFragmentIndices);
	if (pCat->Config.pConfigs)
	{
		int i;
		for (i = 0; i < pCat->Config.CountOfConfigs; i++)		
			if (pCat->Config.pConfigs[i].Config.pItems)
				free(pCat->Config.pConfigs[i].Config.pItems);
		free(pCat->Config.pConfigs);			
		}
	free(pCat);
}

void CScan::Delete(IO_VS_Fragment2 *pFrag)
{
	if (pFrag->Fragment.pViews)
	{
		VS_View2 *pV = pFrag->Fragment.pViews;
		int i, j, s;
		for (i = 0; i < pFrag->Fragment.CountOfViews; i++)
		{
			VS_View2 &rv = pV[i];
			for (s = 0; s < 2; s++)
			{
				if (rv.Layers[s].pLayerInfo)
					free(rv.Layers[s].pLayerInfo);
				if (rv.pTracks[s])
				{
					Track2 *pT = rv.pTracks[s];
					for (j = 0; j < rv.TCount[s]; j++)
						if (pT[j].pGrains) free(pT[j].pGrains);
					free(pT);
					}
				}
			}
		free(pV);
		}
	free(pFrag);
}

UINT CScan::DataWriteThread()
{
	DataToWrite d;
	UINT ExtErrorInfo;
	do
	{
		WaitForSingleObject(HDataWriteAvailableSignal, INFINITE);
		while (DequeueDataToWrite(d))
		{
			if (d.IsCatalog)
			{
				iIO->Write2(0, (BYTE *)d.pCat, &ExtErrorInfo, d.OutName[0] ? (UCHAR *)d.OutName : 0);
				Delete(d.pCat);
				}
			else
			{
				iIO->Write2(0, (BYTE *)d.pFrag, &ExtErrorInfo, d.OutName[0] ? (UCHAR *)d.OutName : 0);
				Delete(d.pFrag);
				}
			}				
		}
	while (!Terminate);
	while (DequeueDataToWrite(d))
	{
		if (d.IsCatalog)
		{
			iIO->Write2(0, (BYTE *)d.pCat, &ExtErrorInfo, d.OutName[0] ? (UCHAR *)d.OutName : 0);
			Delete(d.pCat);
			}
		else
		{
			iIO->Write2(0, (BYTE *)&d.pFrag, &ExtErrorInfo, d.OutName[0] ? (UCHAR *)d.OutName : 0);
			Delete(d.pFrag);
			}
		}
	return 0;
}

bool CScan::DequeueDataToWrite(DataToWrite &d)
{
	WaitForSingleObject(HDataWriteMutex, INFINITE);
	if (!pDWrTail)
	{
		ResetEvent(HDataWriteAvailableSignal);
		ReleaseMutex(HDataWriteMutex);
		return false;
		}
	d = *pDWrTail;
	delete pDWrTail;
	if (!d.pPrevious)
	{
		pDWrTail = pDWrHead = 0;
		}
	else
	{
		pDWrTail = d.pPrevious;
		pDWrTail->pNext = 0;
		}
	ResetEvent(HDataWriteAvailableSignal);
	ReleaseMutex(HDataWriteMutex);
	return true;
	}

void CScan::EnqueueDataToWrite(DataToWrite d)
{
	WaitForSingleObject(HDataWriteMutex, INFINITE);
	if (!pDWrHead)
	{
		DataToWrite *p = new DataToWrite;
		*p = d;
		p->pNext = p->pPrevious = 0;
		pDWrHead = pDWrTail = p;
	}
	else
	{
		DataToWrite *p = new DataToWrite;
		*p = d;
		p->pNext = pDWrHead;
		p->pPrevious = 0;
		p->pNext->pPrevious = p;
		pDWrHead = p;
	}
	SetEvent(HDataWriteAvailableSignal);
	ReleaseMutex(HDataWriteMutex);
	}

void CScan::AddFocusInfo(float x, float y, VS_View2::t_RelevantZs2 info)
{
	pFocusInfo[CurrentFocusInfo].Pos.X = x;
	pFocusInfo[CurrentFocusInfo].Pos.Y = y;
	pFocusInfo[CurrentFocusInfo].Pos.Z = info.TopInt;
	pFocusInfo[CurrentFocusInfo].Info = info;
	if (++CurrentFocusInfo >= MaxFocusInfo)
	{
		t_FocusInfo *p = (t_FocusInfo *)realloc(pFocusInfo, sizeof(t_FocusInfo) * (MaxFocusInfo += 10000));
		if (!p) MaxFocusInfo -= 10000;
		else pFocusInfo = p;
		}
}

bool CScan::GetNearestFocusInfo(float x, float y, VS_View2::t_RelevantZs2 &info)
{
	if (CurrentFocusInfo == 0) return false;
	double dist, bestdist;
	int i, best;
	bestdist = hypot(x - pFocusInfo[0].Pos.X, y - pFocusInfo[0].Pos.Y);
	best = 0;
	for (i = 1; i < CurrentFocusInfo; i++)
	{
		dist = hypot(x - pFocusInfo[i].Pos.X, y - pFocusInfo[i].Pos.Y);
		if (bestdist > dist)
		{
			bestdist = dist;
			best = i;
			}
		}
	info = pFocusInfo[best].Info;
	return true;
}