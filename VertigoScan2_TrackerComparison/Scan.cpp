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

#include "AutomaticLightControl.h"

/////////////////////////////////////////////////////////////////////////////
// CScan dialog


CScan::CScan(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor *ivp, 
	ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
	ConfigData &c, Identifier id, float minx, float maxx, float miny, float maxy, CWnd* pParent /*=NULL*/,
	bool *pFragmentResumeList, char *forcedname, bool remotescan, float autozreset)
	: CDialog(CScan::IDD, pParent), phWnd(phwnd), CVertigoScanner(iself, iio, ist, iob, 
		ifg, ivp, itk1, ift1, itk2, ift2, ism, c), Terminate(false), 
		ForcedName(forcedname), RemoteScan(remotescan), AutoZReset(autozreset)
{
	//{{AFX_DATA_INIT(CScan)
	//}}AFX_DATA_INIT
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
	pFocusData = 0;
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


CScan::~CScan()
{
	Free();
	if (pScanFragment) free(pScanFragment);
	if (pFragmentData) GlobalFree(pFragmentData);
	if (pFocusData) GlobalFree(pFocusData);
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
	ON_BN_CLICKED(IDC_SM_SETFOCUS, OnSetFocus)
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
	RunStatus = true;
	EnableControls();
	pThread = AfxBeginThread((AFX_THREADPROC)ThreadHook, this, THREAD_PRIORITY_NORMAL, 65536, 0, NULL);	
}

void CScan::OnStop() 
{
	// TODO: Add your control notification handler code here
	pThread->PostThreadMessage(UM_CHANGE_STATUS, UM_STOP, 0);
}

void CScan::OnSetFocus() 
{
	// TODO: Add your control notification handler code here
	char str[2048];
	float X, Y, Z;
	iSt->GetPos(0, &X);
	iSt->GetPos(1, &Y);
	iSt->GetPos(2, &Z);
	sprintf(str, "X T %06.1f P %06.1f\r\nY T %06.1f P %06.1f\r\nZ T %06.1f P %06.1f\r\n", 
		ProcessVariables.TargetX, X, ProcessVariables.TargetY, Y, ProcessVariables.TargetZ, Z);
	MessageBox(str, "Debug Info", MB_ICONINFORMATION | MB_OK);
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
	GetDlgItem(IDC_SM_ID1)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Hdr.ID.Part[1]);
	GetDlgItem(IDC_SM_ID2)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Hdr.ID.Part[2]);
	GetDlgItem(IDC_SM_ID3)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Hdr.ID.Part[3]);
	GetDlgItem(IDC_SM_ID4)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	Temp.Format("%d", Cat.Area.Fragments);
	GetDlgItem(IDC_SM_TOTALFRAGMENTS)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Temp);
	GetDlgItem(IDC_SM_FRAGPROGRESS)->SendMessage(PBM_SETRANGE32, 0, Cat.Area.Fragments);
	GetDlgItem(IDC_SM_FRAGPROGRESS)->SendMessage(PBM_SETPOS, 0, 0);
	GetDlgItem(IDC_SM_VIEWPROGRESS)->SendMessage(PBM_SETRANGE32, 0, C.XFields * C.YFields);
	GetDlgItem(IDC_SM_VIEWPROGRESS)->SendMessage(PBM_SETPOS, 0, 0);
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
	GetDlgItem(IDC_SM_SETFOCUS)->EnableWindow(/*false && */RunStatus);
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
	switch ((Err = Init()))
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
	Cat.Area.XMax = Cat.Area.XMin + Cat.Area.XStep * Cat.Area.XViews;
	Cat.Area.YMax = Cat.Area.YMin + Cat.Area.YStep * Cat.Area.YViews;
	XFocusFields = C.XFields;//(C.XFields > C.RefocusFields) ? C.XFields : C.RefocusFields;
	XFocusSamples = XFragments + 1;//Cat.Area.XViews / XFocusFields + 1;
	YFocusFields = C.YFields;//(C.YFields > C.RefocusFields) ? C.YFields : C.RefocusFields;
	YFocusSamples = YFragments + 1;//Cat.Area.YViews / YFocusFields + 1;
	
	pFocusData = (t_FocusData *)GlobalAlloc(GMEM_FIXED, sizeof(t_FocusData) * XFocusSamples * YFocusSamples);
	if (!pFocusData) 
	{
		OkToRun = false;
		Temp = "Focus data allocation error";
		};

	{
		int i;

		for (i = 0; i < (XFocusSamples * YFocusSamples); i++)
		{
			pFocusData[i].TakenOnFragment = 0;
			pFocusData[i].RelevantZs.TopExt = pFocusData[i].RelevantZs.TopInt = pFocusData[i].RelevantZs.BottomInt = 
				pFocusData[i].RelevantZs.BottomExt = 0.f;
			};
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

UINT CScan::Thread()
{
	UINT ExtErrorInfo;
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

	StartTime = GetTickCount();
	FocusTime = SavingTime = ViewTime = 0;
	TotalFocusStrokes = TotalViews = 0;

	for (CurrentFragment = 1; !ShouldStop() && (CurrentFragment <= (XFragments * YFragments)); CurrentFragment++)
	{
		MsgString.Format("%d", CurrentFragment);

		GetDlgItem(IDC_SM_CURRENTFRAGMENT)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MsgString);
		GetDlgItem(IDC_SM_FRAGPROGRESS)->SendMessage(PBM_SETPOS, CurrentFragment - 1, 0);
		if (!(pScanFragment[CurrentFragment - 1])) continue;
		UINT Error;
		double StartX, StartY;
		float CurrX, CurrY;
		if (ShouldStop()) 
		{
			VPUnlock();
			PostMessage(UM_CHANGE_STATUS, UM_STOP);
			return VSERR_TERMINATED;
			};
		if ((Error = PrepareFocusInfo()) != VSERR_OK) 
		{
			VPUnlock();
			PostMessage(UM_CHANGE_STATUS, UM_ERROR);
			return Error;
			};
		StartX = pFragmentData[CurrentFragment - 1].XStart * C.XFields * Cat.Area.XStep + Cat.Area.XMin;
		StartY = pFragmentData[CurrentFragment - 1].YStart * C.YFields * Cat.Area.YStep + Cat.Area.YMin;
/* TODO: IMPROVE CHECKS!!! */
		iSM->DirFixPoint(StartX, StartY);
		iSM->DirMapPoint(StartX, StartY, &StartX, &StartY);
		iSt->GetPos(0, &CurrX);
		iSt->GetPos(1, &CurrY);
	
		Error = Scan(StartX, StartY, (2 * (CurrX - StartX) / C.XStep) < C.XFields, (2 * (CurrY - StartY) / C.YStep) < C.YFields);
		if (ShouldStop())
		{
			iSt->Stop(0);
			iSt->Stop(1);
			iSt->Stop(2);
			};
		if (Error == VSSCAN_OK)
		{
			int i;
			for (i = 0; i < Frag.Fragment.CountOfViews; i++)
			{
				Frag.Fragment.pViews[i].TileX += pFragmentData[CurrentFragment - 1].XStart * XFocusFields;		
				Frag.Fragment.pViews[i].TileY += pFragmentData[CurrentFragment - 1].YStart * YFocusFields;		
				};

			Frag.Fragment.StartView = pFragmentData[CurrentFragment - 1].XStart * C.XFields + pFragmentData[CurrentFragment - 1].YStart * C.YFields * Cat.Area.XViews;
			Frag.Hdr.ID = Cat.Hdr.ID;
			Frag.Fragment.Index = CurrentFragment;
			Time = GetTickCount();

			if (UseForced) sprintf(OutName, "%s.rwd.%08X", ForcedName, Frag.Fragment.Index);

			if (iIO->Write2(0, (BYTE *)&Frag, &Error, UseForced ? (UCHAR *)OutName : 0) != S_OK)
			{
				VPUnlock();
				PostMessage(UM_CHANGE_STATUS, UM_ERROR);
				return VSERR_IO_ERROR;
				};
			SavingTime += (GetTickCount() - Time);
			};
/* TODO: IMPROVE CHECKS!!! */
		};
	MsgString.Format("%d", CurrentFragment - 1);
	GetDlgItem(IDC_SM_CURRENTFRAGMENT)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MsgString);
	GetDlgItem(IDC_SM_FRAGPROGRESS)->SendMessage(PBM_SETPOS, CurrentFragment - 1, 0);
	VPUnlock();
	GetDlgItem(IDC_SM_TIMETOCOMPL)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"0:00:00");
	Time = GetTickCount() - StartTime;
	char temp[32];
	sprintf(temp, "%d:%02d:%02d", Time / 3600000, ((Time / 1000) / 60) % 60, (Time / 1000) % 60);
	GetDlgItem(IDC_SM_TOTALTIME)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	PostMessage(UM_CHANGE_STATUS, UM_END);
	return VSERR_OK;
}

UINT CScan::GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop)
{
	switch (ValidCorners)
	{
		case 0:			return VSERR_CANTRUN;

		case 1:			F = pCorners[0]->RelevantZs;
						return VSERR_OK;

		case 2:			{
							double w0, w1, d;
							double X, Y, DX, DY;
							X = Frag.Fragment.pViews[field].X[istop ? 0 : 1];
							Y = Frag.Fragment.pViews[field].Y[istop ? 0 : 1];
							d = hypot(DX = (pCorners[1]->X - pCorners[0]->X), DY = (pCorners[1]->Y - pCorners[0]->Y));
							if (d <= 0.) 
							{
								F = pCorners[0]->RelevantZs;
								return VSERR_OK;
								};
							DX = DX / d;
							DY = DY / d;
							w0 = (pCorners[1]->X - X) * DX + (pCorners[1]->Y - Y) * DY;
							if (w0 >= 1.)
							{
								w0 = 1.;
								w1 = 0.;
								}
							else if (w0 <= 0.)
							{
								w0 = 0.;
								w1 = 1.;
								}
							else
							{
								w1 = 1. - w0;
								};
							F.TopInt = w0 * pCorners[0]->RelevantZs.TopInt + w1 * pCorners[1]->RelevantZs.TopInt;
							F.TopExt = w0 * pCorners[0]->RelevantZs.TopExt + w1 * pCorners[1]->RelevantZs.TopExt;
							F.BottomInt = w0 * pCorners[0]->RelevantZs.BottomInt + w1 * pCorners[1]->RelevantZs.BottomInt;
							F.BottomExt = w0 * pCorners[0]->RelevantZs.BottomExt + w1 * pCorners[1]->RelevantZs.BottomExt;
							};
						return VSERR_OK;

		case 3:			{
							int i;
							double d;
							double X, Y, DX[2], DY[2], W[2];
							VS_View2::t_RelevantZs2 DF[2];
							X = Frag.Fragment.pViews[field].X[istop ? 0 : 1] - pCorners[0]->X;
							Y = Frag.Fragment.pViews[field].Y[istop ? 0 : 1] - pCorners[0]->Y;
							for (i = 1; i < 3; i++)
							{
								DX[i - 1] = pCorners[i]->X - pCorners[0]->X;
								DY[i - 1] = pCorners[i]->Y - pCorners[0]->Y;
								DF[i - 1].TopExt = pCorners[i]->RelevantZs.TopExt - pCorners[0]->RelevantZs.TopExt;
								DF[i - 1].TopInt = pCorners[i]->RelevantZs.TopInt - pCorners[0]->RelevantZs.TopInt;
								DF[i - 1].BottomExt = pCorners[i]->RelevantZs.BottomExt - pCorners[0]->RelevantZs.BottomExt;
								DF[i - 1].BottomInt = pCorners[i]->RelevantZs.BottomInt - pCorners[0]->RelevantZs.BottomInt;
								};
							d = DX[0] * DY[1] - DX[1] * DY[0];
							if (d == 0.) 
							{
								F = pCorners[0]->RelevantZs;
								return VSERR_OK;
								};
							W[0] = (X * DY[1] - Y * DX[1]) / d;
							W[1] = (Y * DX[0] - X * DY[0]) / d;
							F.TopExt = pCorners[0]->RelevantZs.TopExt + W[0] * DF[0].TopExt + W[1] * DF[1].TopExt;
							F.TopInt = pCorners[0]->RelevantZs.TopInt + W[0] * DF[0].TopInt + W[1] * DF[1].TopInt;
							F.BottomExt = pCorners[0]->RelevantZs.BottomExt + W[0] * DF[0].BottomExt + W[1] * DF[1].BottomExt;
							F.BottomInt = pCorners[0]->RelevantZs.BottomInt + W[0] * DF[0].BottomInt + W[1] * DF[1].BottomInt;
							};
						return VSERR_OK;

		case 4:			{
							int i;
							double X, Y, D[4], W[4], DD, WW;
							DD = WW = 0.;
							X = Frag.Fragment.pViews[field].X[istop ? 0 : 1];
							Y = Frag.Fragment.pViews[field].Y[istop ? 0 : 1];
							for (i = 0; i < 4; i++)	D[i] = hypot(X - pCorners[i]->X, Y - pCorners[i]->Y);
							W[0] = D[1] * D[2] * D[3];
							W[1] = D[0] * D[2] * D[3];
							W[2] = D[0] * D[1] * D[3];
							W[3] = D[0] * D[1] * D[2];
							WW = W[0] + W[1] + W[2] + W[3];
							for (i = 0; i < 4; i++)	W[i] /= WW;
							F.TopExt = W[0] * pCorners[0]->RelevantZs.TopExt + W[1] * pCorners[1]->RelevantZs.TopExt + W[2] * pCorners[2]->RelevantZs.TopExt + W[3] * pCorners[3]->RelevantZs.TopExt;
							F.TopInt = W[0] * pCorners[0]->RelevantZs.TopInt + W[1] * pCorners[1]->RelevantZs.TopInt + W[2] * pCorners[2]->RelevantZs.TopInt + W[3] * pCorners[3]->RelevantZs.TopInt;
							F.BottomExt = W[0] * pCorners[0]->RelevantZs.BottomExt + W[1] * pCorners[1]->RelevantZs.BottomExt + W[2] * pCorners[2]->RelevantZs.BottomExt + W[3] * pCorners[3]->RelevantZs.BottomExt;
							F.BottomInt = W[0] * pCorners[0]->RelevantZs.BottomInt + W[1] * pCorners[1]->RelevantZs.BottomInt + W[2] * pCorners[2]->RelevantZs.BottomInt + W[3] * pCorners[3]->RelevantZs.BottomInt;
							};
						return VSERR_OK;
		};
	return VSERR_OK;
	};

UINT CScan::PrepareFocusInfo()
{
	int i, j, fi, fj;
	double XC, YC;

	ValidCorners = 0;
	fi = (pFragmentData[CurrentFragment - 1].XStart * C.XFields) / XFocusFields;
	fj = (pFragmentData[CurrentFragment - 1].YStart * C.YFields) / YFocusFields;
	
	XC = Cat.Area.XMin + fi * Cat.Area.XStep * XFocusFields;
	YC = Cat.Area.YMin + fj * Cat.Area.YStep * YFocusFields;
	iSM->DirFixPoint(XC, YC);
	iSM->DirMapPoint(XC, YC, &XC, &YC);
	pCorners[0] = pFocusData + fj * XFocusSamples + fi;
	pCorners[0]->X = XC;
	pCorners[0]->Y = YC;

	XC = Cat.Area.XMin + (fi + 1) * Cat.Area.XStep * XFocusFields;
	YC = Cat.Area.YMin + fj * Cat.Area.YStep * YFocusFields;
	iSM->DirFixPoint(XC, YC);
	iSM->DirMapPoint(XC, YC, &XC, &YC);
	pCorners[1] = pFocusData + fj * XFocusSamples + fi + 1;
	pCorners[1]->X = XC;
	pCorners[1]->Y = YC;

	XC = Cat.Area.XMin + (fi + 1) * Cat.Area.XStep * XFocusFields;
	YC = Cat.Area.YMin + (fj + 1) * Cat.Area.YStep * YFocusFields;
	iSM->DirFixPoint(XC, YC);
	iSM->DirMapPoint(XC, YC, &XC, &YC);
	pCorners[2] = pFocusData + (fj + 1) * XFocusSamples + fi + 1;
	pCorners[2]->X = XC;
	pCorners[2]->Y = YC;

	XC = Cat.Area.XMin + fi * Cat.Area.XStep * XFocusFields;
	YC = Cat.Area.YMin + (fj + 1) * Cat.Area.YStep * YFocusFields;
	iSM->DirFixPoint(XC, YC);
	iSM->DirMapPoint(XC, YC, &XC, &YC);
	pCorners[3] = pFocusData + (fj + 1) * XFocusSamples + fi;
	pCorners[3]->X = XC;
	pCorners[3]->Y = YC;

	for (i = 0; i < 4; i++)
	{
		if ((!pCorners[i]->TakenOnFragment) || ((CurrentFragment - pCorners[i]->TakenOnFragment) > 1))
		{
			iSt->PosMove(0, pCorners[i]->X, C.HSpeed, C.HAcc);
			iSt->PosMove(1, pCorners[i]->Y, C.HSpeed, C.HAcc);
			float X, Y;
			do
			{
				iSt->GetPos(0, &X);
				iSt->GetPos(1, &Y);
				if (ShouldStop())
				{
					iSt->Stop(0);
					iSt->Stop(1);
					return VSSCAN_TERMINATED;
					};
				int LimX, LimY;
				iSt->GetLimiter(0, &LimX);
				iSt->GetLimiter(1, &LimY);
				if (LimX || LimY)
				{
					iSt->Stop(0);
					iSt->Stop(1);
					return ((LimX) ? VSSCAN_XLIMITER : 0) | ((LimY) ? VSSCAN_YLIMITER : 0);
					};
				}
			while ((fabs(X - pCorners[i]->X) > C.HTol) || (fabs(Y - pCorners[i]->Y) > C.HTol));
			iSt->Stop(2);
			for (j = 0; (j < 4) && ((!pCorners[j]->TakenOnFragment) || ((CurrentFragment - pCorners[j]->TakenOnFragment) > 1)); j++);
			if (j < 4) pCorners[i]->RelevantZs = pCorners[j]->RelevantZs;
			else
			{
				float Z;

				if (RemoteScan) Z = AutoZReset;
				else
				{
					VPUnlock();
					iStOb->EnableMonitor(true);
					::MessageBox(0, "Place the stage at the top surface of the plastic base and press OK", "Help Request", MB_ICONQUESTION | MB_OK);
					iSt->GetPos(2, &Z);
					iStOb->EnableMonitor(false);
					VPLock();
					}
	
				pCorners[i]->RelevantZs.TopInt = Z;
				pCorners[i]->RelevantZs.TopExt = Z + C.VStep;
				pCorners[i]->RelevantZs.BottomInt = Z - C.BaseThickness;
				pCorners[i]->RelevantZs.BottomExt = pCorners[i]->RelevantZs.BottomInt - C.VStep;
				};

			VS_View2::t_RelevantZs2 F = pCorners[i]->RelevantZs;
			UINT Time = GetTickCount();
			UINT Ret = CVertigoScanner::GetFocus(pCorners[i]->X, pCorners[i]->Y, F);
			FocusTime += (GetTickCount() - Time);
			TotalFocusStrokes++;
			if (Ret == VSSCAN_OK)
			{
				pCorners[i]->TakenOnFragment = CurrentFragment;
				pCorners[i]->RelevantZs = F;
				}
			else pCorners[i]->TakenOnFragment = 0;
			};
		};

	for (ValidCorners = i = 0; ValidCorners < 4; ValidCorners++)
	{
		t_FocusData *pT;
		for (; (i < 4) && (!pCorners[i]->TakenOnFragment); i++);
		if (i < 4)
		{
			pT = pCorners[ValidCorners];
			pCorners[ValidCorners] = pCorners[i];
			pCorners[i] = pT;
			}
		else break;
		};

	if (!ValidCorners) return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;

	return VSSCAN_OK;
	};

bool CScan::ShouldStop()
{
	MSG Msg;
	if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
		if (Msg.message == UM_CHANGE_STATUS && Msg.wParam == UM_STOP) 
		{
			PostThreadMessage(pThread->m_nThreadID, UM_CHANGE_STATUS, UM_STOP, 0);
			return true;
			};
	return false;
}

void CScan::OnExit() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

UINT CScan::FittingNotify()
{
	//return VSERR_OK;
	unsigned Time;
	unsigned vmult = 2;
	ViewTime = (Time = GetTickCount()) - StartTime - /*FocusTime -*/ SavingTime;
	Time -= StartTime;
	TotalViews++;
	char temp[32];
	switch (C.ScanningScheme) 
	{
		case SCANNING_SCHEME_TOPSIDE:
		case SCANNING_SCHEME_BOTTOMSIDE:		vmult = 1;
												
		case SCANNING_SCHEME_BOTH_IN_FIELD:		sprintf(temp, "%d", ProcessVariables.Field + 1);
												GetDlgItem(IDC_SM_VIEWPROGRESS)->SendMessage(PBM_SETPOS, ProcessVariables.Field + 1, 0);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			sprintf(temp, "%d", ProcessVariables.Field + (C.XFields * C.YFields) * (ProcessVariables.IsTop ? 0 : 1) + 1);
												GetDlgItem(IDC_SM_VIEWPROGRESS)->SendMessage(PBM_SETPOS, ProcessVariables.Field + 1 + (C.XFields * C.YFields) * (ProcessVariables.IsTop ? 0 : 1), 0);
												break;
		}

	GetDlgItem(IDC_SM_CURRENTVIEW)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);

	unsigned TimeToCompletion = ViewTime * (float)(Cat.Area.XViews * Cat.Area.YViews * vmult - TotalViews) / TotalViews/* + FocusTime * (float)(XFocusSamples * YFocusSamples - TotalFocusStrokes) / TotalFocusStrokes*/;
	if (CurrentFragment > 1) TimeToCompletion += SavingTime * (float)(Cat.Area.Fragments - CurrentFragment + 1) / (CurrentFragment - 1); 
	sprintf(temp, "%d:%02d:%02d", TimeToCompletion / 3600000, ((TimeToCompletion / 1000) / 60) % 60, (TimeToCompletion / 1000) % 60);
	GetDlgItem(IDC_SM_TIMETOCOMPL)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	sprintf(temp, "%d:%02d:%02d", Time / 3600000, ((Time / 1000) / 60) % 60, (Time / 1000) % 60);
	GetDlgItem(IDC_SM_TOTALTIME)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	return VSERR_OK;
}

UINT CScan::StartNotify()
{
	char temp[32];
	UINT CountOfViews = Frag.Fragment.CountOfViews;
	if (C.ScanningScheme == SCANNING_SCHEME_TWO_SIDES) CountOfViews *= 2;
	sprintf(temp, "%d", CountOfViews);

	GetDlgItem(IDC_SM_TOTALVIEWS)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	GetDlgItem(IDC_SM_CURRENTVIEW)->SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"0");
	GetDlgItem(IDC_SM_VIEWPROGRESS)->SendMessage(PBM_SETRANGE32, 0, CountOfViews);
	GetDlgItem(IDC_SM_VIEWPROGRESS)->SendMessage(PBM_SETPOS, 0, 0);
	return VSERR_OK;
}

BOOL CScan::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam == 2 /* ESC Key Trap */) return TRUE;
	return CDialog::OnCommand(wParam, lParam);
}
