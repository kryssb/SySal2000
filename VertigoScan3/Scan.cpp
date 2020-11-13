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
	NextPreloaded = false;
	RunStatus = false;
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
	CheckInit();
	pScanFragment = (bool *)malloc(sizeof(bool) * Cat.Area.Fragments);
	if (pFragmentResumeList) memcpy(pScanFragment, pFragmentResumeList, sizeof(bool) * Cat.Area.Fragments);
	else 
	{
		int i;
		for (i = 0; i < Cat.Area.Fragments; pScanFragment[i++] = true);
		};
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
	UINT Ret = CVertigoScanner::Scan(startx, starty, xforward, yforward);
	if (NextPreloaded)
	{
		iSt->PosMove(0, NextTargetX, C.HSpeed, C.HAcc);
		iSt->PosMove(1, NextTargetY, C.HSpeed, C.HAcc);
		}
	return Ret;
	}

CScan::~CScan()
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
#else
	Cat.Area.XMax = Cat.Area.XMin + Cat.Area.XStep * Cat.Area.XViews;
	Cat.Area.YMax = Cat.Area.YMin + Cat.Area.YStep * Cat.Area.YViews;
#endif
	
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
#define MAX_FORCED_NAME 1024
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

	VPLock();

	UINT Time;

	iStOb->EnableMonitor(false);
	iSt->EnableManualControl(false);

	iSt->FlushAsyncMotions();

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

	if ((Error = PrepareFocusInfo()) != VSERR_OK) 
	{
		VPUnlock();
		PostMessage(UM_CHANGE_STATUS, UM_ERROR);
		return Error;
		};

	StartTime = GetTickCount();
	TotalViews = 0;

	CHECK_AUTOZ("Z1B");

	for (CurrentFragment = 1; !ShouldStop() && (CurrentFragment <= (XFragments * YFragments)); CurrentFragment++)
	{
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
*/		Error = Scan(StartX, StartY, (2 * (CurrX - StartX) / C.XStep) < C.XFields, (2 * (CurrY - StartY) / C.YStep) < C.YFields);
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

			int i;
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

			if (iIO->Write2(0, (BYTE *)&Frag, &Error, UseForced ? (UCHAR *)OutName : 0) != S_OK)
			{
				VPUnlock();
				PostMessage(UM_CHANGE_STATUS, UM_ERROR);
				return VSERR_IO_ERROR;
				};
			};
/* TODO: IMPROVE CHECKS!!! */
		};
	CHECK_AUTOZ("Z1J");
	MsgString.Format("%d", CurrentFragment - 1);
	SendDlgItemMessage(IDC_SM_CURRENTFRAGMENT, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MsgString);
	SendDlgItemMessage(IDC_SM_FRAGPROGRESS, PBM_SETPOS, CurrentFragment - 1, 0);
	VPUnlock();
	SendDlgItemMessage(IDC_SM_TIMETOCOMPL, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"0:00:00");
	Time = GetTickCount() - StartTime;
	char temp[32];
	sprintf(temp, "%d:%02d:%02d", Time / 3600000, ((Time / 1000) / 60) % 60, (Time / 1000) % 60);
	SendDlgItemMessage(IDC_SM_TOTALTIME, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	PostMessage(UM_CHANGE_STATUS, UM_END);
	CHECK_AUTOZ("Z1K");
	return VSERR_OK;
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
		Z = AutoZReset;
		if (TrustZ && Frag.Fragment.CountOfViews == 1) return VSSCAN_OK;
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

	float X, Y;
	iSt->GetPos(0, &X);
	iSt->GetPos(1, &Y);
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
