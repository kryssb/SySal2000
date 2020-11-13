// Scan.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Scan.h"
#include <math.h>
#include "..\Common\Stage3.h"
#include "..\Common\SySalObj2.h"

#include "debug.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define DUMPTIME(op) { FILE *ftime = fopen("c:\\acq\\time.txt", "a+t"); fprintf(ftime, "%d %d\n", op, GetTickCount()); fclose(ftime); }
#define DUMPTIME(op)

void ShowString(System::String ^x);

/////////////////////////////////////////////////////////////////////////////
// CScan dialog

float CScan::ZSetDepot = 0.0f;

#define CHECK_AUTOZ(x) \
{ if (RemoteScan && (ZSetDepot != AutoZReset)) MessageBox(x, "Trap hit!", MB_OK); }

CScan::CScan(
#ifdef ENABLE_NET
			 SySal::DAQSystem::TrackingClient ^tkclient, 
#endif			 
			 HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
	ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
	ConfigData &c, Identifier id, float minx, float maxx, float miny, float maxy, 
	bool presetslope, float slopex, float slopey, float slopeaccx, float slopeaccy, CWnd* pParent,		
	bool *pFragmentResumeList, char *forcedname, bool remotescan, float autozreset, bool trustz)
	: CDialog(CScan::IDD, pParent), phWnd(phwnd), CVertigoScanner(iself, iio, ist, iob, 
		ifg, ivp, itk1, ift1, itk2, ift2, ism, c), Terminate(false), 
		ForcedName(forcedname), RemoteScan(remotescan), AutoZReset(autozreset), TrustZ(trustz)
#ifdef ENABLE_NET
		,TkClient(tkclient), m_NPFrag(nullptr)
#endif
{
	//{{AFX_DATA_INIT(CScan)
	//}}AFX_DATA_INIT
	pFocusInfo = (t_FocusInfo *)debug_Malloc(sizeof(t_FocusInfo) * (MaxFocusInfo = 1000));
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
	pScanFragment = (bool *)debug_Malloc(sizeof(bool) * Cat.Area.Fragments);
	if (pFragmentResumeList) memcpy(pScanFragment, pFragmentResumeList, sizeof(bool) * Cat.Area.Fragments);
	else 
	{
		int i;
		for (i = 0; i < Cat.Area.Fragments; pScanFragment[i++] = true);
		};
	iTk[0]->EnableSlopePresetting(presetslope);
	iTk[0]->PresetSlope(slopex, slopey, slopeaccx, slopeaccy);
	iTk[1]->EnableSlopePresetting(presetslope);
	iTk[1]->PresetSlope(slopex, slopey, slopeaccx, slopeaccy);
	if (PresetSlope = presetslope)
	{
		SlopeX = slopex;
		SlopeY = slopey;
		SlopeAccX = slopeaccx;
		SlopeAccY = slopeaccy;
	}
	else
	{
		SlopeX = SlopeY = SlopeAccX = SlopeAccY = 0.0f;
	}
#ifdef ENABLE_NET
	MakeBytes();
#endif
}

CScan::CScan(
#ifdef ENABLE_NET			 
			 SySal::DAQSystem::TrackingClient ^tkclient, 
#endif			 
			 HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
	ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
	ConfigData &c, CWnd* pParent, float autozreset, bool trustz)
	: CDialog(CScan::IDD, pParent), phWnd(phwnd), CVertigoScanner(iself, iio, ist, iob, 
		ifg, ivp, itk1, ift1, itk2, ift2, ism, c), Terminate(false), 
		ForcedName(0), RemoteScan(true), AutoZReset(autozreset), TrustZ(trustz)
#ifdef ENABLE_NET
		,TkClient(tkclient), m_NPFrag(nullptr)
#endif
{
	pFocusInfo = (t_FocusInfo *)debug_Malloc(sizeof(t_FocusInfo) * (MaxFocusInfo = 1000));
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
	
	PresetSlope = false;
	SlopeX = SlopeY = SlopeAccX = SlopeAccY = 0.0f;
#ifdef ENABLE_NET
	MakeBytes();
#endif
}
#ifdef ENABLE_NET
void CScan::ScanInit()
{
	if (C.EnableScanGrid && !System::Object::ReferenceEquals(TkClient, nullptr))
	{
		m_NPFrag = gcnew SySal::DAQSystem::NetPackagedFragment(CameraSpecBytes, TrackerCLSID_T, TrackerCLSID_B, TrackerConfig_T, TrackerConfig_B,
			FitterCLSID_T, FitterCLSID_B, FitterConfig_T, FitterConfig_B, 
			Frag.Fragment.Index, Frag.Fragment.CodingMode, Frag.Fragment.CountOfViews, Frag.Fragment.StartView,  
			"", C.MaxTracks, PresetSlope, SlopeX - SlopeAccX, SlopeX + SlopeAccX, SlopeY - SlopeAccY, SlopeY + SlopeAccY, C.Shrinkage);
	}
	else
	{
		m_NPFrag = nullptr;
		CVertigoScanner::ScanInit();
	}
}

void CScan::PageGrains(void *pPage, int clusters, Cluster *pClusters)
{
	if (C.EnableScanGrid && !System::Object::ReferenceEquals(TkClient, nullptr))
	{
		m_TempBytesW->Write(clusters);
		while (clusters--)
		{
			try
			{
				m_TempBytesW->Write(pClusters->X);
				m_TempBytesW->Write(pClusters->Y);
				m_TempBytesW->Write((int)(pClusters++->Area));
			}
			catch(System::Exception ^x)
			{
				ShowString("Debug Point D: " + x->Message);
			}
		}
	}
	else CVertigoScanner::PageGrains(pPage, clusters, pClusters);
}

void CScan::OpenGrainPage(int Field, int Side)
{
	if (C.EnableScanGrid && !System::Object::ReferenceEquals(TkClient, nullptr))
	{
		if (!System::Object::ReferenceEquals(m_TempBytesW, nullptr))
			m_TempBytesW->Close();		
		while(true)		
			try
			{
				m_TempBytes = gcnew System::IO::MemoryStream(C.VLayers * (C.MaxClusters * sizeof(SySal::DAQSystem::NetCluster) + sizeof(int)));
				m_TempBytesW = gcnew System::IO::BinaryWriter(m_TempBytes);
				break;
			}
			catch (System::OutOfMemoryException ^) 
			{ 
				Sleep(1000); 
			}
			catch (System::Exception ^x)
			{
				ShowString("Debug Point A: " + x->Message);
			}
		m_TempField = Field;
		m_TempSide = Side;
	}
	else CVertigoScanner::OpenGrainPage(Field, Side);
}

void CScan::CloseGrainPage()
{
	if (C.EnableScanGrid && !System::Object::ReferenceEquals(TkClient, nullptr))
	{
		m_TempBytesW->Flush();
		m_TempBytesW->Close();
		while(true)
			try
			{
				gcroot<SySal::DAQSystem::NetPackagedView ^> vw = gcnew SySal::DAQSystem::NetPackagedView();	
				VS_View2 VW2 = Frag.Fragment.pViews[m_TempField];
				int lay;	
				vw->Z = gcnew array<System::Single>(VW2.Layers[m_TempSide].Count);
				for (lay = 0; lay < VW2.Layers[m_TempSide].Count; lay++) vw->Z[lay] = VW2.Layers[m_TempSide].pLayerInfo[lay].Z;
				vw->Field = m_TempField;
				vw->IsTop = (m_TempSide == 0);
				vw->ClusterLayers = m_TempBytes->ToArray();
				vw->ZBase = m_TempSide ? VW2.RelevantZs.BottomInt : VW2.RelevantZs.TopInt;
				vw->ZTop = m_TempSide ? VW2.RelevantZs.BottomInt : VW2.RelevantZs.TopExt;
				vw->ZBottom = m_TempSide ? VW2.RelevantZs.BottomExt : VW2.RelevantZs.TopInt;
				vw->TileX = VW2.TileX;
				vw->TileY = VW2.TileY;
				vw->Shrinkage = C.Shrinkage;
				vw->PosX = VW2.X[m_TempSide];
				vw->PosY = VW2.Y[m_TempSide];
				vw->MapPosX = VW2.MapX[m_TempSide];
				vw->MapPosY = VW2.MapY[m_TempSide];
				vw->MapXX = VW2.ImageMat[m_TempSide][0][0];
				vw->MapXY = VW2.ImageMat[m_TempSide][0][1];
				vw->MapYX = VW2.ImageMat[m_TempSide][1][0];
				vw->MapYY = VW2.ImageMat[m_TempSide][1][1];	
				m_NPFrag->ViewInfo[m_TempField + (m_NPFrag->ViewInfo->Length / 2) * m_TempSide] = vw;
				break;
			}
			catch (System::OutOfMemoryException ^) 
			{ 
				Sleep(1000); 
			}
			catch (System::Exception ^x)
			{
				ShowString("Debug Point B: " + x->Message);
			}

		m_TempBytes = nullptr;
		m_TempBytesW = nullptr;
	}
	else CVertigoScanner::CloseGrainPage();
}

void CScan::MakeBytes()
{
	if (System::Object::ReferenceEquals(TkClient, nullptr))
	{
		CameraSpecBytes = nullptr;
		FitterCLSID_T = nullptr;
		FitterCLSID_B = nullptr;
		FitterConfig_T = nullptr;
		FitterConfig_B = nullptr;
		TrackerCLSID_T = nullptr;
		TrackerCLSID_B = nullptr;
		TrackerConfig_T = nullptr;
		TrackerConfig_B = nullptr;
	}
	else
	{			
		int i;
		CameraSpecBytes = gcnew array<System::Byte>(sizeof(CSP));
		for (i = 0; i < sizeof(CSP); i++)
			CameraSpecBytes[i] = ((char *)(void *)&CSP)[i];
		CLSID clsid;
		SySalConfig T;
		T.pItems = 0;
		T.Name[0] = 0;
		T.CountOfItems = 0;
		ISySalObject2 *iOb = 0;		
		iFt[0]->QueryInterface(IID_ISySalObject2, (void **)&iOb);
		iOb->GetCLSID(&clsid);
		FitterCLSID_T = BytesFromCLSID(clsid);
		iOb->GetConfig(&T);
		FitterConfig_T = BytesFromConfig(&T);
		CoTaskMemFree(T.pItems);
		iOb->Release();
		T.pItems = 0;
		T.CountOfItems = 0;
		iFt[1]->QueryInterface(IID_ISySalObject2, (void **)&iOb);
		iOb->GetCLSID(&clsid);
		FitterCLSID_B = BytesFromCLSID(clsid);
		iOb->GetConfig(&T);
		FitterConfig_B = BytesFromConfig(&T);
		CoTaskMemFree(T.pItems);
		iOb->Release();
		T.pItems = 0;
		T.CountOfItems = 0;
		iTk[0]->QueryInterface(IID_ISySalObject2, (void **)&iOb);
		iOb->GetCLSID(&clsid);
		TrackerCLSID_T = BytesFromCLSID(clsid);
		iOb->GetConfig(&T);
		TrackerConfig_T = BytesFromConfig(&T);
		CoTaskMemFree(T.pItems);
		iOb->Release();
		T.pItems = 0;
		T.CountOfItems = 0;
		iTk[1]->QueryInterface(IID_ISySalObject2, (void **)&iOb);
		iOb->GetCLSID(&clsid);
		TrackerCLSID_B = BytesFromCLSID(clsid);
		iOb->GetConfig(&T);
		TrackerConfig_B = BytesFromConfig(&T);
		CoTaskMemFree(T.pItems);
		iOb->Release();
		T.pItems = 0;
		T.CountOfItems = 0;
	}
}

array<System::Byte> ^CScan::BytesFromConfig(SySalConfig *pC)
{
	int i, len = (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * pC->CountOfItems;
	array<System::Byte> ^arr = gcnew array<System::Byte>(sizeof(pC->CountOfItems) + len);
	arr[0] = ((char *)(void *)&pC->CountOfItems)[0];
	arr[1] = ((char *)(void *)&pC->CountOfItems)[1];
	arr[2] = ((char *)(void *)&pC->CountOfItems)[2];
	arr[3] = ((char *)(void *)&pC->CountOfItems)[3];
	for (i = 0; i < len; i++)
		arr[i + sizeof(int)] = pC->pItems[i];
	return arr;
}

array<System::Byte> ^CScan::BytesFromCLSID(CLSID &clsid)
{
	array<System::Byte> ^arr = gcnew array<System::Byte>(sizeof(clsid));
	int i;
	for (i = 0; i < sizeof(clsid); i++)
		arr[i] = ((byte *)(void *)&clsid)[i];
	return arr;
}
#endif
void CScan::SetZAndTrust(bool trustz, float autozreset)
{
	TrustZ = trustz;
	AutoZReset = autozreset;
	if (!trustz) CurrentFocusInfo = 0;
}

UINT CScan::ResetAndScan(Identifier id, float minx, float maxx, float miny, float maxy, bool *pFragmentResumeList, char *forcedname, bool trustz, bool presetslope, float slopex, float slopey, float slopeaccx, float slopeaccy)
{
	Free();
	if (pScanFragment)
	{
		debug_Free(pScanFragment);
		pScanFragment = 0;
	}
	if (pFragmentData)
	{
		GlobalFree(pFragmentData);
		pFragmentData = 0;
	}
	if (Cat.pFragmentIndices)
	{
		GlobalFree(Cat.pFragmentIndices);
		Cat.pFragmentIndices = 0;
	}
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
	pScanFragment = (bool *)debug_Malloc(sizeof(bool) * Cat.Area.Fragments);
	if (pFragmentResumeList) memcpy(pScanFragment, pFragmentResumeList, sizeof(bool) * Cat.Area.Fragments);
	else 
	{
		int i;
		for (i = 0; i < Cat.Area.Fragments; pScanFragment[i++] = true);
		};	
	iTk[0]->EnableSlopePresetting(presetslope);
	iTk[0]->PresetSlope(slopex, slopey, slopeaccx, slopeaccy);
	iTk[1]->EnableSlopePresetting(presetslope);
	iTk[1]->PresetSlope(slopex, slopey, slopeaccx, slopeaccy);
	{
		char tempstr[2048];
		sprintf(tempstr, "%d %f %f %f %f", presetslope, slopex, slopey, slopeaccx, slopeaccy);
		//MessageBox(tempstr, "Debug Info", MB_OK);
	}
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
#ifdef ENABLE_NET
		MakeBytes();
#endif
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
	if (pScanFragment) debug_Free(pScanFragment);
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
	debug_Free(pFocusInfo);
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
	SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETRANGE32, 0, C.XFields() * C.YFields());
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
	bool singleview = (Cat.Area.XViews == 1) && (Cat.Area.YViews == 1);
	XFragments = (Cat.Area.XViews + C.XFields(singleview) - 1) / C.XFields(singleview);
	YFragments = (Cat.Area.YViews + C.YFields(singleview) - 1) / C.YFields(singleview);
	Cat.Area.Fragments = XFragments * YFragments;
	Cat.Area.XViews = C.XFields(singleview) * XFragments;
	Cat.Area.YViews = C.YFields(singleview) * YFragments;
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
	else SingleViewMode = false;
#else
	Cat.Area.XMax = Cat.Area.XMin + Cat.Area.XStep * Cat.Area.XViews;
	Cat.Area.YMax = Cat.Area.YMin + Cat.Area.YStep * Cat.Area.YViews;
#endif

	switch ((Err = Init()) & 0xFF000000)
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
	
	
	if (pFragmentData) 
	{
		GlobalFree(pFragmentData);
		pFragmentData = 0;
	}
	pFragmentData = (t_FragmentData *)GlobalAlloc(GMEM_FIXED, sizeof(t_FragmentData) * XFragments * YFragments);
	if (!pFragmentData) 
	{
		OkToRun = false;
		Temp = "Fragment indexing data allocation error";
		};

	if (Cat.pFragmentIndices)
	{
		GlobalFree(Cat.pFragmentIndices);
		Cat.pFragmentIndices = 0;
	}
	Cat.pFragmentIndices = (int *)GlobalAlloc(GMEM_FIXED, sizeof(int) * Cat.Area.XViews * Cat.Area.YViews);
	if (!Cat.pFragmentIndices)
	{
		OkToRun = false;
		Temp = "Catalog view indices allocation error";
		};

	if (pFragmentData && Cat.pFragmentIndices)
	{
		int i, j, k;

		for (i = 0; i < YFragments; i++)
			for (j = 0; j < XFragments; j++)
			{
				t_FragmentData *pFrag = pFragmentData + i * XFragments + j;
				pFrag->XStart = (i % 2) ? (XFragments - 1 - j) : j;
				pFrag->YStart = i;
				};

/*
		if (C.YFields(singleview) % 2)
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

*/

		for (k = 0; k < (XFragments * YFragments); k++)
		{
			int xsize, ysize;
			xsize = Cat.Area.XViews - pFragmentData[k].XStart * C.XFields(singleview);
			if (xsize > C.XFields(singleview)) xsize = C.XFields(singleview);
			ysize = Cat.Area.YViews - pFragmentData[k].YStart * C.YFields(singleview);
			if (ysize > C.YFields(singleview)) ysize = C.YFields(singleview);
			for (i = 0; i < ysize; i++)
				for (j = 0; j < xsize; j++)
					Cat.pFragmentIndices[(i + pFragmentData[k].YStart * C.YFields(singleview)) * Cat.Area.XViews + j + pFragmentData[k].XStart * C.XFields(singleview)] = k + 1;
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

	if (!System::Object::ReferenceEquals(TkClient, nullptr) && C.EnableScanGrid)
		TracksPageGrains = true;

	if (!OkToRun)
		MessageBox(Temp, "Initialization error", MB_ICONERROR | MB_OK);
	VPLock();
	VPUnlock();
}

bool CScan::MyShouldStopCallback(DWORD Context)
{
	return ((CScan *)Context)->ShouldStop();
}

void stackcheck(char debug_1, char debug_2, char debug_3, char debug_4, char debug_5, char *point)
{
	if (debug_1 != 'K' || debug_2 != 'R' || debug_3 != 'Y' || debug_4 != 'S' || debug_5 != 'S')
	{
		::MessageBox(0, point, "Debug Info - Stack Corruption Detected - check point in message", MB_OK);
	}
}

UINT CScan::Thread()
{
	char debug_1 = 'K';
	UINT ExtErrorInfo;
	char debug_2 = 'R';
	UINT Error;
	char debug_3 = 'Y';
	CString MsgString;
	char debug_4 = 'S';
	DataToWrite dwr;
	char debug_5 = 'S';
	int i;

	
	bool UseForced = false;
	char OutName[MAX_FORCED_NAME];
	SetThreadName(GetCurrentThreadId(), "VS6 Scan Thread");
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
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point A");
	EnqueueDataToWrite(dwr);
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point B");
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
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point C");

	DUMPTIME(4);

	UINT Time;

	iStOb->EnableMonitor(false);
	DUMPTIME(5);
	iSt->EnableManualControl(false);
	DUMPTIME(6);

	iSt->FlushAsyncMotions();
	DUMPTIME(7);

	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point D");
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
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point E");
	if ((Error = PrepareFocusInfo()) != VSERR_OK) 
	{
		stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point F");
		VPUnlock();
		PostMessage(UM_CHANGE_STATUS, UM_ERROR);
		return Error;
		};
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point G");

	StartTime = GetTickCount();
	TotalViews = 0;

	CHECK_AUTOZ("Z1B");

	DUMPTIME(8);
	for (CurrentFragment = 1; !ShouldStop() && (CurrentFragment <= (XFragments * YFragments)); CurrentFragment++)
	{
		stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point H");
		DUMPTIME(9);
		MsgString.Format("%d", CurrentFragment);

		SendDlgItemMessage(IDC_SM_CURRENTFRAGMENT, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MsgString);
		SendDlgItemMessage(IDC_SM_FRAGPROGRESS, PBM_SETPOS, CurrentFragment - 1, 0);
		CHECK_AUTOZ("Z1C");
		stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point I");
		if (!(pScanFragment[CurrentFragment - 1])) continue;
		double StartX, StartY;
		float CurrX, CurrY;
		if (ShouldStop()) 
		{
			stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point J");
			VPUnlock();
			PostMessage(UM_CHANGE_STATUS, UM_STOP);
			return VSERR_TERMINATED;
			};
		stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point K");
		CHECK_AUTOZ("Z1D");
		//CHANGED!!!
#if 1
		StartX = pFragmentData[CurrentFragment - 1].XStart * C.XFields() * Cat.Area.XStep + Cat.Area.XMin + Cat.Area.XStep * 0.5;
		StartY = pFragmentData[CurrentFragment - 1].YStart * C.YFields() * Cat.Area.YStep + Cat.Area.YMin + Cat.Area.YStep * 0.5;
#else
		StartX = pFragmentData[CurrentFragment - 1].XStart * C.XFields() * Cat.Area.XStep + Cat.Area.XMin;
		StartY = pFragmentData[CurrentFragment - 1].YStart * C.YFields() * Cat.Area.YStep + Cat.Area.YMin;
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
		stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point L");
		Error = Scan(StartX, StartY, (2 * (CurrX - StartX) / C.XStep) < C.XFields(), (2 * (CurrY - StartY) / C.YStep) < C.YFields());
		stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point M");
		DUMPTIME(11);
		CHECK_AUTOZ("Z1F");
		if (ShouldStop())
		{
			iSt->Stop(0);
			iSt->Stop(1);
			iSt->Stop(2);
			};
		stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point N");
		CHECK_AUTOZ("Z1G");
		if (Error == VSSCAN_OK)
		{
			stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point O");
			CurrentRelevantZs = Frag.Fragment.pViews[Frag.Fragment.CountOfViews - 1].RelevantZs;
			CurrentRelevantZs.TopExt /= CSP.RefractiveShrinkage;
			CurrentRelevantZs.TopInt /= CSP.RefractiveShrinkage;
			CurrentRelevantZs.BottomInt /= CSP.RefractiveShrinkage;
			CurrentRelevantZs.BottomExt /= CSP.RefractiveShrinkage;

			/*KRYSS - disable zone focus data recording -
			AddFocusInfo(Frag.Fragment.pViews[Frag.Fragment.CountOfViews - 1].MapX[0], Frag.Fragment.pViews[Frag.Fragment.CountOfViews - 1].MapY[0], CurrentRelevantZs);
			*/

			for (i = 0; i < Frag.Fragment.CountOfViews; i++)
			{
				Frag.Fragment.pViews[i].TileX += pFragmentData[CurrentFragment - 1].XStart * C.XFields();		
				Frag.Fragment.pViews[i].TileY += pFragmentData[CurrentFragment - 1].YStart * C.YFields();		
				};
			CHECK_AUTOZ("Z1H");

			Frag.Fragment.StartView = pFragmentData[CurrentFragment - 1].XStart * C.XFields() + pFragmentData[CurrentFragment - 1].YStart * C.YFields() * Cat.Area.XViews;
			Frag.Hdr.ID = Cat.Hdr.ID;
			Frag.Fragment.Index = CurrentFragment;			

			stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point P");
			if (UseForced) sprintf(OutName, "%s.rwd.%08X", ForcedName, Frag.Fragment.Index);

			CHECK_AUTOZ("Z1I");

			stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point Q");
			dwr.IsCatalog = false;
			dwr.pFrag = Duplicate(Frag);
			stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point R");
			if (UseForced) strcpy(dwr.OutName, OutName);
			else dwr.OutName[0] = 0;
			stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point S");
			EnqueueDataToWrite(dwr);
			stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point T");

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
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point U");
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
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point V");
	SendDlgItemMessage(IDC_SM_TIMETOCOMPL, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"0:00:00");
	Time = GetTickCount() - StartTime;
	char temp[32];
	sprintf(temp, "%d:%02d:%02d", Time / 3600000, ((Time / 1000) / 60) % 60, (Time / 1000) % 60);
	SendDlgItemMessage(IDC_SM_TOTALTIME, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	PostMessage(UM_CHANGE_STATUS, (Error == VSSCAN_OK) ? UM_END : UM_ERROR);
	CHECK_AUTOZ("Z1K");
	DUMPTIME(14);
/*
	if (!System::Object::ReferenceEquals(TkClient, nullptr))
		while (TkClient->IsActive && !ShouldStop()) Sleep(1000);
*/	
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point W");
	if (!System::Object::ReferenceEquals(TkClient, nullptr))
	{
		if (TkClient->IsOK == false) return VSERR_IO_ERROR;
	}
	stackcheck(debug_1, debug_2, debug_3, debug_4, debug_5, "Point X");
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
		if (TrustZ && /*SingleViewMode && */GetNearestFocusInfo(Cat.Area.XMin, Cat.Area.YMin, CurrentRelevantZs)) return VSSCAN_OK;
		Z = AutoZReset;		
		pSafetyTopIntZ = &AutoZReset;
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
		AutoZReset = Z;
		pSafetyTopIntZ = &AutoZReset;
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
		case SCANNING_SCHEME_BOTTOMSIDE:		TotalViews = (CurrentFragment - 1) * C.XFields() * C.YFields() + ProcessVariables.Field;
												vmult = 1;												
												sprintf(temp, "%d", ProcessVariables.Field + 1);
												SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, ProcessVariables.Field + 1, 0);
												break;
												
												
		case SCANNING_SCHEME_BOTH_IN_FIELD:		TotalViews = ((CurrentFragment - 1) * C.XFields() * C.YFields() + ProcessVariables.Field) * 2 + (ProcessVariables.IsTop ? 0 : 1);
												vmult = 2;
												sprintf(temp, "%d", ProcessVariables.Field + 1);
												SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, ProcessVariables.Field + 1, 0);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			TotalViews = ((CurrentFragment - 1) * 2 + (ProcessVariables.IsTop ? 0 : 1)) * C.XFields() * C.YFields() + ProcessVariables.Field;
												vmult = 2;
												sprintf(temp, "%d", ProcessVariables.Field + (C.XFields() * C.YFields()) * (ProcessVariables.IsTop ? 0 : 1) + 1);
												SendDlgItemMessage(IDC_SM_VIEWPROGRESS, PBM_SETPOS, ProcessVariables.Field + 1 + (C.XFields() * C.YFields()) * (ProcessVariables.IsTop ? 0 : 1), 0);
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
	sprintf(temp, "%.2f", C.TunedTopStep);
	SendDlgItemMessage(IDC_SM_TOPTHICKNESS, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
	sprintf(temp, "%.2f", C.TunedBottomStep);
	SendDlgItemMessage(IDC_SM_BOTTOMTHICKNESS, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)temp);
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
	pCat->pFragmentIndices = (int *)malloc(sizeof(int) * Cat.Area.XViews * Cat.Area.YViews);
	memcpy(pCat->pFragmentIndices, Cat.pFragmentIndices, sizeof(int) * Cat.Area.XViews * Cat.Area.YViews);
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
#ifdef ENABLE_NET	
	if (!System::Object::ReferenceEquals(TkClient, nullptr) && C.EnableScanGrid && !SingleViewMode)
	{
		IO_VS_Fragment2 *pFrag = (IO_VS_Fragment2 *)malloc(sizeof(IO_VS_Fragment2));
		pFrag->Hdr = Frag.Hdr;
		memcpy(pFrag->Reserved, Frag.Reserved, sizeof(Frag.Reserved));
		pFrag->Fragment.CodingMode = Frag.Fragment.CodingMode;
		pFrag->Fragment.CountOfViews = Frag.Fragment.CountOfViews;
		pFrag->Fragment.FitCorrectionDataSize = Frag.Fragment.FitCorrectionDataSize;
		pFrag->Fragment.Index = Frag.Fragment.Index;
		pFrag->Fragment.StartView = Frag.Fragment.StartView;
		pFrag->Fragment.pViews = 0;
		int i;
		for (i = 0; i < Frag.Fragment.CountOfViews; i++)
		{
			m_NPFrag->ViewInfo[i]->ZTop = Frag.Fragment.pViews[i].RelevantZs.TopExt;
			m_NPFrag->ViewInfo[i]->ZBottom = Frag.Fragment.pViews[i].RelevantZs.TopInt;
			m_NPFrag->ViewInfo[Frag.Fragment.CountOfViews + i]->ZTop = Frag.Fragment.pViews[i].RelevantZs.BottomInt;
			m_NPFrag->ViewInfo[Frag.Fragment.CountOfViews + i]->ZBottom = Frag.Fragment.pViews[i].RelevantZs.BottomExt;
			m_NPFrag->ViewInfo[i]->TileX = m_NPFrag->ViewInfo[Frag.Fragment.CountOfViews + i]->TileX = Frag.Fragment.pViews[i].TileX;
			m_NPFrag->ViewInfo[i]->TileY = m_NPFrag->ViewInfo[Frag.Fragment.CountOfViews + i]->TileY =Frag.Fragment.pViews[i].TileY;
			};

		return pFrag;
	}
#endif
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
	if (pFrag->Fragment.FitCorrectionDataSize == 99999999)
	{
		::MessageBox(0, "Double deallocation attempt detected!", "Debug Info", MB_OK);
	}
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
					{
						if (pT[j].pGrains) free(pT[j].pGrains);
						if (pT[j].pCorrection) free(pT[j].pCorrection);
						}
					free(pT);
					}
				}
			}
		free(pV);
		}
	/* debug check */
	pFrag->Fragment.FitCorrectionDataSize = 99999999;
	/* debug check */
	free(pFrag);
}

UINT CScan::DataWriteThread()
{
	DataToWrite d;
	UINT ExtErrorInfo;
	SetThreadName(GetCurrentThreadId(), "VS6 DataWriteThread");
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
#ifdef ENABLE_NET	
	if (!System::Object::ReferenceEquals(TkClient, nullptr) && C.EnableScanGrid)
	{
		if (d.OutName[0] == 0)
		{
			TkClient->GetDefaultOutName(d.OutName);
			char idstr[64];
			if (d.IsCatalog)
				sprintf(idstr, "%08X%08X%08X%08X.rwc", d.pCat->Hdr.ID.Part[0], d.pCat->Hdr.ID.Part[1], d.pCat->Hdr.ID.Part[2], d.pCat->Hdr.ID.Part[3]);
			else
				sprintf(idstr, "%08X%08X%08X%08X.rwd.%08X", d.pFrag->Hdr.ID.Part[0], d.pFrag->Hdr.ID.Part[1], d.pFrag->Hdr.ID.Part[2], d.pFrag->Hdr.ID.Part[3], d.pFrag->Fragment.Index);
			strcat(d.OutName, idstr);
		}
	}
	if (!d.IsCatalog && !System::Object::ReferenceEquals(TkClient, nullptr) && !d.pFrag->Fragment.pViews)
	{				
		bool Retry = true;
		m_NPFrag->FilePath = gcnew System::String(d.OutName);
		m_NPFrag->StartView = d.pFrag->Fragment.StartView;
		m_NPFrag->Index = d.pFrag->Fragment.Index;
		m_NPFrag->CamSpec = this->CameraSpecBytes;
		m_NPFrag->FitterCLSID_B = this->FitterCLSID_B;
		m_NPFrag->FitterCLSID_T = this->FitterCLSID_T;
		m_NPFrag->FitterConfig_T = this->FitterConfig_T;
		m_NPFrag->TrackerCLSID_B = this->TrackerCLSID_B;
		m_NPFrag->TrackerCLSID_T = this->TrackerCLSID_T;
		m_NPFrag->TrackerConfig_B = this->TrackerConfig_B;
		m_NPFrag->TrackerConfig_T = this->TrackerConfig_T;
		m_NPFrag->SaveGrains = C.SaveGrains;
		m_NPFrag->MaxTracks = C.MaxTracks;	
		m_NPFrag->UseSlopePreset = this->PresetSlope;
		m_NPFrag->SlopePresetMaxX = this->SlopeX + this->SlopeAccX;
		m_NPFrag->SlopePresetMaxY = this->SlopeY + this->SlopeAccY;
		m_NPFrag->SlopePresetMinX = this->SlopeX - this->SlopeAccX;
		m_NPFrag->SlopePresetMinY = this->SlopeY - this->SlopeAccY;		
		gcroot<SySal::DAQSystem::NetPackagedFragment ^>m_QueueNPFrag = m_NPFrag;
		m_NPFrag = nullptr;
		while (Retry)
			try
			{
				TkClient->AddFragment(m_QueueNPFrag);
				Retry = false;
			}
			catch (System::OutOfMemoryException ^)
			{
				Retry = true;
				Sleep(1000);
			}
			catch (System::Exception ^x)
			{
				ShowString("Debug Point C: " + x->Message);
				Retry = true;
				Sleep(1000);
			}
/*
		if (d.IsCatalog) Delete(d.pCat);
		else Delete(d.pFrag);		
*/
		Delete(d.pFrag);
		return;
	}	
#endif
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
		t_FocusInfo *p = (t_FocusInfo *)debug_Realloc(pFocusInfo, sizeof(t_FocusInfo) * (MaxFocusInfo += 10000));
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

void ShowString(System::String ^x)
{
	int len = x->Length;
	char *ptemp = new char[len + 1];
	int i;
	for (i = 0; i < len; i++)
		ptemp[i] = x[i];
	::MessageBox(0, ptemp, "Debug Info", MB_OK);
	delete [] ptemp;
}