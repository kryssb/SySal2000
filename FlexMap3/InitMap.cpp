// InitMap.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "InitMap.h"
#include "AffineTransf.h"
#include "IntMarkMap.h"
#include "FieldMap.h"
#include <math.h>
#include "Stage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitMap dialog

#define CROSS_SIZE 31
#define LIMIT_SIN 0.5
#define Z_ACC 10000
#define ELLIPTICITY_LIMIT 100.

const double M_PI_4 = atan(1.);

UINT CInitMap::ExecThreadHook(void *pOwner)
{
	return ((CInitMap *)pOwner)->ExecThread();
	};

CInitMap::CInitMap(HWND *phwnd, HANDLE hstatusmutex, CString &name, IFrameGrabber *ifg, IVisionProcessor *ivp, IVisionProcessor2 *ivp2, IStage *ist, 
	IObjective *iob, ISySalDataIO *ico, FlexMapData *pConfig, IntMarkMap *pMap, bool recovery, CWnd* pParent /*=NULL*/)
	: CDialog(CInitMap::IDD, pParent), phWnd(phwnd), HStatusMutex(hstatusmutex), iFG(ifg), iVP(ivp), iVP2(ivp2), iSt(ist), iOb(iob), iCo(ico), pM(pMap), 
	Recovery(recovery), F(*pConfig), Name(name), CSpace(0), pZs(0), pImage(0)
{
	//{{AFX_DATA_INIT(CInitMap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	int i;
	ExtX = MinX = pMap->pMarks[0].Nominal.X;
	ExtY = MinY = pMap->pMarks[0].Nominal.Y;
	for (i = 1; i < pMap->Count; i++)
	{
		if (pMap->pMarks[i].Nominal.X > ExtX) ExtX = pMap->pMarks[i].Nominal.X;
		else if (pMap->pMarks[i].Nominal.X < MinX) MinX = pMap->pMarks[i].Nominal.X;
		if (pMap->pMarks[i].Nominal.Y > ExtY) ExtY = pMap->pMarks[i].Nominal.Y;
		else if (pMap->pMarks[i].Nominal.Y < MinY) MinY = pMap->pMarks[i].Nominal.Y;	
		};
	ExtX -= MinX;
	ExtY -= MinY;
	iOb->GetSpecs(&CAM);
	pMarkImages = 0;
	MarkShown = 0;
	Terminate = false;
	Working = false;
	Aborted = false;
	Pause = false;
	UseManualCoords = false;
	MarkStatusChanged = false;
	CurrentMark = 0;
	CSpace = (MyCluster *)GlobalAlloc(GMEM_FIXED, F.MaxClusters * sizeof(MyCluster));
	DZLayers = F.FocusSpeed / F.FramesPerSecond;
	Layers = ceil(2.f * F.FocusStroke / DZLayers);
	pZs = (float *)GlobalAlloc(GMEM_FIXED, sizeof(float) * Layers);
	pImage = (BYTE *)GlobalAlloc(GMEM_FIXED, CAM.Width * CAM.Height);
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	pExecThread = 0;
	iSt3 = 0;
	if (iSt->QueryInterface(IID_IStage3, (void **)&iSt3) != S_OK)
	{
		iSt3->Release();
		iSt3 = 0;
		}
}


CInitMap::~CInitMap()
{	
	if (iSt3) iSt3->Release();
	iStOb->Release();
	if (pImage) GlobalFree(pImage);
	if (pZs) GlobalFree(pZs);
	if (CSpace) GlobalFree(CSpace);
	if (pMarkImages) delete [] pMarkImages;
	delete [] pXCoding;
	delete [] pYCoding;
	};

void CInitMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitMap)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitMap, CDialog)
	//{{AFX_MSG_MAP(CInitMap)
	ON_BN_CLICKED(IDC_IM_ABORT, OnAbort)
	ON_BN_CLICKED(IDC_IM_CONTINUE, OnContinue)
	ON_BN_CLICKED(IDC_IM_NEXT, OnNext)
	ON_BN_CLICKED(IDC_IM_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_IM_PREV, OnPrev)
	ON_BN_CLICKED(IDC_IM_SKIP, OnSkip)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_IM_RESCAN, OnRescan)
	ON_BN_CLICKED(IDC_IM_SETXY, OnSetXY)
	ON_BN_CLICKED(IDC_IM_SETZ, OnSetZ)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitMap message handlers

void CInitMap::OnAbort() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Abort scanning?", "Confirmation Request", MB_YESNO) == IDYES)
	{
		SetButtonStates(false, false);
		Terminate = true;
		Aborted = false;
		pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING, 0);
		};
}

void CInitMap::OnContinue() 
{
	// TODO: Add your control notification handler code here
	SetButtonStates(false, false);
	Pause = false;
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUE, 0);
}

void CInitMap::OnNext() 
{
	// TODO: Add your control notification handler code here
	UseManualCoords = false;
	if (++MarkShown >= pM->Count) MarkShown = pM->Count - 1;
	ShowMarkInfo(MarkShown);
	GetDlgItem(IDC_IM_MARKVIEW)->RedrawWindow();	
}

void CInitMap::OnPause() 
{
	// TODO: Add your control notification handler code here
	SetButtonStates(false, false);
	Pause = true;
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSE, 0);
}

void CInitMap::OnPrev() 
{
	// TODO: Add your control notification handler code here
	UseManualCoords = false;
	if (--MarkShown < 0) MarkShown = 0;
	ShowMarkInfo(MarkShown);
	GetDlgItem(IDC_IM_MARKVIEW)->RedrawWindow();
}

void CInitMap::OnSkip() 
{
	// TODO: Add your control notification handler code here
	//SetButtonStates(false, false);
	//Pause = false;
	MarkStatusChanged = true;
	pM->pMarks[MarkShown].Status = MARK_STATUS_NOTFOUND;
	ShowMarkInfo(MarkShown);
	GetDlgItem(IDC_IM_MARKVIEW)->RedrawWindow();
}

void CInitMap::OnRescan() 
{
	// TODO: Add your control notification handler code here
	SetButtonStates(false, false);
	Pause = false;
	MarkStatusChanged = true;
	ShowMarkInfo(MarkShown);
	pM->pMarks[CurrentMark = MarkShown].Status = MARK_STATUS_NOTSEARCHED;
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUE, 0);
}

void CInitMap::OnSetXY() 
{
	// TODO: Add your control notification handler code here
	iSt->GetPos(0, &Expected.X);
	iSt->GetPos(1, &Expected.Y);
	UseManualCoords = true;
}

void CInitMap::OnSetZ() 
{
	// TODO: Add your control notification handler code here
	iSt->GetPos(2, &Expected.Z);
	UseManualCoords = true;
}

void CInitMap::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDCtl)
	{
		case IDC_IM_GRIDVIEW:	DrawGridView(lpDrawItemStruct);
								break;

		case IDC_IM_MARKVIEW:	DrawMarkView(lpDrawItemStruct);
								break;

		default: CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
		};
}

void CInitMap::DrawGridView(LPDRAWITEMSTRUCT lpDIS)
{
	CDC dc;
	dc.Attach(lpDIS->hDC);
	CBrush White(RGB(255, 255, 255));
	dc.FillRect(&lpDIS->rcItem, &White);
	double XW = lpDIS->rcItem.right - lpDIS->rcItem.left - 4;
	double YW = lpDIS->rcItem.bottom - lpDIS->rcItem.top - 4;
	int i;
	for (i = 0; i < pM->Count; i++)
	{
		CPoint P((pM->pMarks[i].Nominal.X - MinX) / ExtX * XW + 2, 
			YW - (pM->pMarks[i].Nominal.Y - MinY) / ExtY * YW + 2);
		switch (pM->pMarks[i].Status)
		{
			case MARK_STATUS_NOTSEARCHED:	dc.SetPixel(P, RGB(0, 0, 128));
											break;

			case MARK_STATUS_FOUND:			dc.SetPixel(P.x, P.y, RGB(0, 0, 255));
											dc.SetPixel(P.x - 1, P.y, RGB(0, 0, 255));
											dc.SetPixel(P.x + 1, P.y, RGB(0, 0, 255));
											dc.SetPixel(P.x, P.y - 1, RGB(0, 0, 255));
											dc.SetPixel(P.x, P.y + 1, RGB(0, 0, 255));
											break;

			case MARK_STATUS_NOTFOUND:		dc.SetPixel(P.x, P.y, RGB(255, 0, 0));
											dc.SetPixel(P.x - 1, P.y + 1, RGB(255, 0, 0));
											dc.SetPixel(P.x + 1, P.y + 1, RGB(255, 0, 0));
											dc.SetPixel(P.x + 1, P.y - 1, RGB(255, 0, 0));
											dc.SetPixel(P.x - 1, P.y - 1, RGB(255, 0, 0));
											break;
			};
		};
	dc.Detach();
}

void CInitMap::DrawMarkView(LPDRAWITEMSTRUCT lpDIS)
{
	if (pM->pMarks[MarkShown].Status == MARK_STATUS_FOUND)
		SetDIBitsToDevice(lpDIS->hDC, 1, 1, XCount, YCount, 0, 0, 0, YCount, pMarkImages + 
			MarkShown * XCount * YCount, &BMPInfo, DIB_RGB_COLORS);
	else
	{
		CDC dc;
		dc.Attach(lpDIS->hDC);
		CBrush White(RGB(255, 255, 255));
		dc.FillRect(&lpDIS->rcItem, &White);
		dc.Detach();
		};
}

BOOL CInitMap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	*phWnd = m_hWnd;
	ReleaseMutex(HStatusMutex);
	CRect ClRect;
	GetDlgItem(IDC_IM_MARKVIEW)->GetClientRect(&ClRect);
	XCount = ClRect.Width() / 4 * 4;
	YCount = ClRect.Height() /4 * 4;
	pXCoding = new int[XCount + 1];
	pYCoding = new int[YCount + 1];
	int i;
	for (i = 0; i <= XCount; i++)
	{
		pXCoding[i] = (i * CAM.Width / XCount);
		};
	for (i = 0; i <= YCount; i++)
	{
		pYCoding[i] = (i * CAM.Height / YCount);
		};
	BMPInfo.bmiHeader.biSize = sizeof(BMPInfo.bmiHeader);
	BMPInfo.bmiHeader.biWidth = XCount;
	BMPInfo.bmiHeader.biHeight = -YCount;
	BMPInfo.bmiHeader.biPlanes = 1;
	BMPInfo.bmiHeader.biBitCount = 8;
	BMPInfo.bmiHeader.biCompression = BI_RGB;
	BMPInfo.bmiHeader.biSizeImage = XCount * YCount;
	BMPInfo.bmiHeader.biXPelsPerMeter = BMPInfo.bmiHeader.biYPelsPerMeter = 1000;
	BMPInfo.bmiHeader.biClrUsed = BMPInfo.bmiHeader.biClrImportant = 256;
	for (i = 1; i < 256; i++)
	{
		BMPInfo.bmiColors[i].rgbRed = BMPInfo.bmiColors[i].rgbGreen = BMPInfo.bmiColors[i].rgbBlue = i;
		BMPInfo.bmiColors[i].rgbReserved = 0;
		};
	BMPInfo.bmiColors[0].rgbRed = 255;
	BMPInfo.bmiColors[0].rgbGreen = BMPInfo.bmiColors[0].rgbBlue = BMPInfo.bmiColors[0].rgbReserved = 0;
	SetButtonStates(true, false);
	pMarkImages = new BYTE[XCount * YCount * pM->Count];	
	pExecThread = AfxBeginThread((AFX_THREADPROC)ExecThreadHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInitMap::SaveImage(int MarkN, bool AddCross, int X, int Y)
{
	int i, j, x, y;
	int v;
	for (i = 0; i < XCount; i++)
		for (j = 0; j < YCount; j++)
		{
			v = 0;
			for (y = pYCoding[j]; y < pYCoding[j + 1]; y++)
				for (x = pXCoding[i]; x < pXCoding[i + 1]; x++)
					v += pImage[y * CAM.Width + x];
			if ((pMarkImages[MarkN * XCount * YCount + j * XCount + i] = 
				v / ((pYCoding[j + 1] - pYCoding[j]) * (pXCoding[i + 1] - pXCoding[i]))) == 0)
				pMarkImages[MarkN * XCount * YCount + j * XCount + i] = 1;
			};
	if (AddCross)
	{
		int XC = X * XCount / (int)CAM.Width;
		int YC = Y * YCount / (int)CAM.Height;
		for (i = -CROSS_SIZE; i <= CROSS_SIZE; i++)
			if ((YC + i) >= 0 && (YC + i) < YCount)
				pMarkImages[MarkN * XCount * YCount + (YC + i) * XCount + XC] = 0; 
		for (i = -CROSS_SIZE; i <= CROSS_SIZE; i++)
			if ((XC + i) >= 0 && (XC + i) < XCount)
				pMarkImages[MarkN * XCount * YCount + YC * XCount + XC + i] = 0; 
		};
}

void CInitMap::SetButtonStates(bool DisableAll, bool IsPaused)
{
	GetDlgItem(IDC_IM_PAUSE)->EnableWindow((!DisableAll) && !IsPaused);
	GetDlgItem(IDC_IM_CONTINUE)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_ABORT)->EnableWindow(!DisableAll);
	GetDlgItem(IDC_IM_PREV)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_NEXT)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_RESCAN)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_SKIP)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_SETXY)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_SETZ)->EnableWindow((!DisableAll) && IsPaused);
}

void CInitMap::ShowMarkInfo(int MarkN)
{
	CString T;
	T.Format("%d", pM->pMarks[MarkN].Id);
	GetDlgItem(IDC_IM_ID)->SetWindowText(T);
	T.Format("%d", MarkN + 1);
	GetDlgItem(IDC_IM_NUMBER)->SetWindowText(T);
	switch (pM->pMarks[MarkN].Status)
	{
		case MARK_STATUS_NOTSEARCHED:	T = "To be searched";
										break;

		case MARK_STATUS_FOUND:			T = "Found";
										break;

		case MARK_STATUS_NOTFOUND:		T = "Not found";
										break;

		default:						T = "Unknown!";
										break;
		};
	GetDlgItem(IDC_IM_STATUS)->SetWindowText(T);
	T.Format("%.1f", pM->pMarks[MarkN].Nominal.X);
	GetDlgItem(IDC_IM_NOMX)->SetWindowText(T);
	T.Format("%.1f", pM->pMarks[MarkN].Nominal.Y);
	GetDlgItem(IDC_IM_NOMY)->SetWindowText(T);
	if (pM->pMarks[MarkN].Status == MARK_STATUS_FOUND)
	{
		T.Format("%.1f", pM->pMarks[MarkN].Stage.X);
		GetDlgItem(IDC_IM_STAGEX)->SetWindowText(T);
		T.Format("%.1f", pM->pMarks[MarkN].Stage.Y);
		GetDlgItem(IDC_IM_STAGEY)->SetWindowText(T);
		T.Format("%.1f", pM->pMarks[MarkN].Z);
		GetDlgItem(IDC_IM_STAGEZ)->SetWindowText(T);
		}
	else
	{
		GetDlgItem(IDC_IM_STAGEX)->SetWindowText("");
		GetDlgItem(IDC_IM_STAGEY)->SetWindowText("");
		GetDlgItem(IDC_IM_STAGEZ)->SetWindowText("");
		};
}

LRESULT CInitMap::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) 
	{
		case SYSAL_ASYNC_STATUS_IDLE:		Terminate = true;
											Aborted = true;
											if (WaitForSingleObject(pExecThread->m_hThread, 0) == WAIT_OBJECT_0) EndDialog(IDCANCEL);
											else pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING, 0);
											break;

		case MSG_SCAN_THREAD_CLOSING:		EndDialog(Aborted ? IDABORT : IDCANCEL);
											break;

		case MSG_SCAN_THREAD_SUCCESS:		EndDialog(IDOK);
											break;

		case MSG_SCAN_THREAD_PAUSED:		SetButtonStates(true, true);
											break;

		case MSG_SCAN_THREAD_CONTINUING:	SetButtonStates(true, false);
											break;
		};
	return 0;
}

UINT CInitMap::ExecThread()
{
	UINT ExtErrInfo;
	CString MsgString;
	bool RecoverySuccessful = false;
	int goodmarks;
	int i;

	bool AutoFirstMark = false;
	AutoFirstMark = (F.SearchFirstMark && iSt3 && pM->ExtendedFormat == INTMARKMAP_FMT_SIDEEXTENTS);
	if (Recovery)
	{
		for (CurrentMark = 0; (CurrentMark < pM->Count) && (pM->pMarks[CurrentMark].Status != MARK_STATUS_NOTSEARCHED); CurrentMark++);
		if (CurrentMark == pM->Count)
		{
			Aborted = true;
			SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING);//PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING);
			return MSG_SCAN_THREAD_CLOSING;
			};
		}
	else CurrentMark = 0;
	MarkStatusChanged = false;	
	SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUING);//PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUING);
	VPLock();
	iStOb->EnableMonitor(false);
	SetButtonStates(false, false);
	GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
	UpdateGlobal();
	do
	{
		GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
		UpdateGlobal();
		ShowMarkInfo(MarkShown = CurrentMark);
		int Nearest[3];
		int CountOfNearest = (MarkStatusChanged && UseManualCoords) ? 4 : FindNearest(CurrentMark, Nearest);
		MarkStatusChanged = false;
		switch (CountOfNearest)
		{
			case 0:		
						if (AutoFirstMark)
						{
							float CornerX, CornerY;
							if (iSt3->GetXYRef((BYTE *)"XYReference", &CornerX, &CornerY) != S_OK) 
								AutoFirstMark = false;
							else
							{
								if (!F.SheetIsRotatedBy180Deg)
								{
						//			Expected.X = pM->pMarks[0].Nominal.X - pM->PlateMinX + CornerX;
						//			Expected.Y = pM->pMarks[0].Nominal.Y - pM->PlateMinY + CornerY;
									Expected.X = pM->pMarks[CurrentMark].Stage.X - pM->PlateMinX + CornerX;
									Expected.Y = pM->pMarks[CurrentMark].Stage.Y - pM->PlateMinY + CornerY;
									}
								else
								{
						//			Expected.X = pM->PlateMaxX - pM->pMarks[0].Nominal.X + CornerX;
						//			Expected.Y = pM->PlateMaxY - pM->pMarks[0].Nominal.Y + CornerY;
									Expected.X = pM->PlateMaxX - pM->pMarks[CurrentMark].Stage.X + CornerX;
									Expected.Y = pM->PlateMaxY - pM->pMarks[CurrentMark].Stage.Y + CornerY;
									};
								if (iSt3->GetZRef((BYTE *)"Glass", &Expected.Z) != S_OK) AutoFirstMark = false;
								Expected.Z += (pM->pMarks[CurrentMark].Side == 1) ? F.TotalThickness : 0;
								}
							};
						if (!AutoFirstMark)
						{
							
							iSt->Stop(0);
							iSt->Stop(1);
							iSt->Stop(2);
							CString msg;
							msg.Format("Please put mark #%d, Id %d in the field of view.\n"
								"Press <Continue> when done.", CurrentMark, pM->pMarks[CurrentMark].Id);
							EchoMessage(msg.GetBuffer(1), "HELP REQUEST");
							msg.ReleaseBuffer();
							if (PauseAndCheckTermination())
							{
								return Exit();
								}
							else 
							{
								if (MarkStatusChanged) continue;								
								iSt->GetPos(0, &Expected.X);
								iSt->GetPos(1, &Expected.Y);
								iSt->GetPos(2, &Expected.Z);
								iSt->PosMove(2, Expected.Z + F.FocusStroke, F.ZSetSpeed, Z_ACC);
								float SZ;
								int LimZ;
								do
								{
									iSt->GetLimiter(2, &LimZ);
									iSt->GetPos(2, &SZ);
									}
								while (!LimZ && fabs(SZ - (Expected.Z + F.FocusStroke)) > F.VertTolerance);
								if (LookForMark(CurrentMark))
								{
//									GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
//									ShowMarkInfo(CurrentMark);
//									MarkShown = CurrentMark++;
									UseManualCoords = false;
//									continue;
									// HERE WE CAN CHECK IF THERE'S A RECOVERY //
									if (Recovery) RecoverySuccessful = true;
									}
								else
								{
//									pM->pMarks[CurrentMark++].Status = MARK_STATUS_NOTFOUND;
									pM->pMarks[CurrentMark].Status = MARK_STATUS_NOTFOUND;
//									continue;
									};
								GetDlgItem(IDC_IM_MARKVIEW)->RedrawWindow();
								GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
								UpdateGlobal();
								ShowMarkInfo(MarkShown = CurrentMark);
								};
							};
						break;

			case 1:		{
							if (!F.SheetIsRotatedBy180Deg)
							{
								Expected.X = pM->pMarks[Nearest[0]].Stage.X + pM->pMarks[CurrentMark].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X;
								Expected.Y = pM->pMarks[Nearest[0]].Stage.Y + pM->pMarks[CurrentMark].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y;
								}
							else
							{
								Expected.X = pM->pMarks[Nearest[0]].Stage.X - pM->pMarks[CurrentMark].Nominal.X + pM->pMarks[Nearest[0]].Nominal.X;
								Expected.Y = pM->pMarks[Nearest[0]].Stage.Y - pM->pMarks[CurrentMark].Nominal.Y + pM->pMarks[Nearest[0]].Nominal.Y;
								};
							Expected.Z = pM->pMarks[Nearest[0]].Z + ((pM->pMarks[CurrentMark].Side == 1) ? F.TotalThickness : 0) - ((pM->pMarks[Nearest[0]].Side == 1) ? F.TotalThickness : 0);
							};
						break;
		
			case 2:		{
							float Expansion = hypot(pM->pMarks[Nearest[0]].Stage.X - pM->pMarks[Nearest[1]].Stage.X, pM->pMarks[Nearest[0]].Stage.Y - pM->pMarks[Nearest[1]].Stage.Y) / 
								hypot(pM->pMarks[Nearest[0]].Nominal.X - pM->pMarks[Nearest[1]].Nominal.X, pM->pMarks[Nearest[0]].Nominal.Y - pM->pMarks[Nearest[1]].Nominal.Y);
							float Angle = atan2(pM->pMarks[Nearest[1]].Stage.Y - pM->pMarks[Nearest[0]].Stage.Y, pM->pMarks[Nearest[1]].Stage.X - pM->pMarks[Nearest[0]].Stage.X) - 
								atan2(pM->pMarks[Nearest[1]].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y, pM->pMarks[Nearest[1]].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X);
							float C = cos(Angle), S = sin(Angle);
							Expected.X = pM->pMarks[Nearest[0]].Stage.X + Expansion * (C * (pM->pMarks[CurrentMark].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X) - S * (pM->pMarks[CurrentMark].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y));
							Expected.Y = pM->pMarks[Nearest[0]].Stage.Y + Expansion * (C * (pM->pMarks[CurrentMark].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y) + S * (pM->pMarks[CurrentMark].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X));
							Expected.Z = pM->pMarks[Nearest[0]].Z + ((pM->pMarks[CurrentMark].Side == 1) ? F.TotalThickness : 0) - ((pM->pMarks[Nearest[0]].Side == 1) ? F.TotalThickness : 0);
							};
						break;
				
			case 3:		{
							IntMark::t_Pos Nom[3], Stage[3];
							int i;
							for (i = 0; i < 3; i++)
							{
								Nom[i] = pM->pMarks[Nearest[i]].Nominal;
								Stage[i] = pM->pMarks[Nearest[i]].Stage;
								};
							AffineTransf A(Nom, Stage);
							double X = pM->pMarks[CurrentMark].Nominal.X, Y = pM->pMarks[CurrentMark].Nominal.Y;
							A.Transform(X, Y, &X, &Y);
							Expected.X = X;
							Expected.Y = Y;
							Expected.Z = pM->pMarks[Nearest[0]].Z + ((pM->pMarks[CurrentMark].Side == 1) ? F.TotalThickness : 0) - ((pM->pMarks[Nearest[0]].Side == 1) ? F.TotalThickness : 0);
							};
			};
		if (CountOfNearest || AutoFirstMark)
		{
			float PosX, PosY, PosZ;
			iSt->GetPos(0, &PosX);
			iSt->GetPos(1, &PosY);
			iSt->GetPos(2, &PosZ);
			float TimeNeeded = F.TimeOut + 2.f * ((PosX - Expected.X) * (1. / (F.LongDistSpeed) + 1. / (F.LongDistAcc * F.LongDistAcc)));
			float MaxTime = TimeNeeded;
			TimeNeeded = F.TimeOut + 2.f * ((PosY - Expected.Y) * (1. / (F.LongDistSpeed) + 1. / (F.LongDistAcc * F.LongDistAcc)));
			if (MaxTime < TimeNeeded) MaxTime = TimeNeeded;
			TimeNeeded = F.TimeOut + 2.f * ((PosZ - Expected.Z) / F.FocusSpeed);
			if (MaxTime < TimeNeeded) MaxTime = TimeNeeded;
			iSt->PosMove(0, Expected.X, F.LongDistSpeed, F.LongDistAcc);
			iSt->PosMove(1, Expected.Y, F.LongDistSpeed, F.LongDistAcc);
			iSt->PosMove(2, Expected.Z + F.FocusStroke, F.ZSetSpeed, Z_ACC);
			float NextTime = MaxTime * 1000.f + GetTickCount();
			bool TimedOut, Arrived, Limiter;

			do
			{
				CheckPauseAndTermination(&Pause, &Terminate);
				if (Terminate)
				{
					VPUnlock();
					return Exit();
					}
				else if (Pause)
				{
					if (PauseAndCheckTermination()) return Exit();
					if (MarkStatusChanged) 
					{
						if (UseManualCoords)
						{
							iSt->PosMove(0, Expected.X, F.LongDistSpeed, F.LongDistAcc);
							iSt->PosMove(1, Expected.Y, F.LongDistSpeed, F.LongDistAcc);
							iSt->PosMove(2, Expected.Z + F.FocusStroke, F.ZSetSpeed, Z_ACC);
							}
						else continue;
						};
					};
				iSt->GetPos(0, &PosX);
				iSt->GetPos(1, &PosY);
				iSt->GetPos(2, &PosZ);
				TimedOut = GetTickCount() > NextTime;
				Arrived = fabs(PosX - Expected.X) < F.HorizTolerance &&
					fabs(PosY - Expected.Y) < F.HorizTolerance &&
					fabs(PosZ - Expected.Z - F.FocusStroke) < F.VertTolerance;
				int LimX, LimY, LimZ;
				iSt->GetLimiter(0, &LimX);
				iSt->GetLimiter(0, &LimY);
				iSt->GetLimiter(0, &LimZ);
				Limiter = LimX || LimY || LimZ;
				}
			while (!TimedOut && !Arrived && !Limiter);
			if (TimedOut || Limiter)
			{
				pM->pMarks[CurrentMark].Status = MARK_STATUS_NOTFOUND;
				}
			else
			{
				int Field = 0;
				bool Ok;
				FieldMap FM(F.FieldMapFileName);
				FM.SetStart(Expected.X, Expected.Y);
				FM.SetStep(fabs(CAM.WinWidth * CAM.PixelToMicronX) - F.Diameter, fabs(CAM.WinHeight * CAM.PixelToMicronY) - F.Diameter);
				do
				{
					float X, Y;
					FM.GetFieldPos(Field, &X, &Y);
					iSt->PosMove(0, X, F.ShortDistSpeed, F.ShortDistAcc);
					iSt->PosMove(1, Y, F.ShortDistSpeed, F.ShortDistAcc);
					iSt->PosMove(2, Expected.Z + F.FocusStroke, F.ZSetSpeed, Z_ACC);
					do
					{
						iSt->GetPos(0, &PosX);
						iSt->GetPos(1, &PosY);
						iSt->GetPos(2, &PosZ);
						Arrived = fabs(PosX - X) < F.HorizTolerance &&
							fabs(PosY - Y) < F.HorizTolerance &&
							fabs(PosZ - Expected.Z - F.FocusStroke) < F.VertTolerance;
						int LimX, LimY, LimZ;
						iSt->GetLimiter(0, &LimX);
						iSt->GetLimiter(0, &LimY);
						iSt->GetLimiter(0, &LimZ);
						Limiter = LimX || LimY || LimZ;
						CheckPauseAndTermination(&Pause, &Terminate);
						if (Terminate)
						{
							VPUnlock();
							return Exit();
							};
						if (Pause && PauseAndCheckTermination()) return Exit();
						if (MarkStatusChanged) break;
						}
					while (!Arrived && !Limiter && !MarkStatusChanged);
					if (MarkStatusChanged) 
					{
						if (UseManualCoords)
						{
							FM.SetStart(Expected.X, Expected.Y);
							Field = -1;
							MarkStatusChanged = false;
							}
						else break;
						};
					Ok = LookForMark(CurrentMark);
					Field++;
					}
				while (!Ok && Field < FM.GetLength() && !MarkStatusChanged);
				if (MarkStatusChanged) continue;
				pM->pMarks[CurrentMark].Status = Ok ? MARK_STATUS_FOUND : MARK_STATUS_NOTFOUND;
				GetDlgItem(IDC_IM_MARKVIEW)->RedrawWindow();
				GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
				UpdateGlobal();
				ShowMarkInfo(MarkShown = CurrentMark);
				};
			};		
		if (!Recovery || !RecoverySuccessful) 
		{
			for (i = 0; i < pM->Count && pM->pMarks[i].Status != MARK_STATUS_NOTSEARCHED; i++);
			CurrentMark = i;
			MarkStatusChanged = false;
			};
		if ((Recovery && RecoverySuccessful) || (CurrentMark == pM->Count))
		{			
			for (i = goodmarks = 0; i < pM->Count; i++)
				if (pM->pMarks[i].Status == MARK_STATUS_FOUND)
					goodmarks++;
			if (goodmarks < 3)
			{
				if (!EchoMessageAsk("At least 3 good marks are required\r\nMap will be invalid if you exit now\r\nExit?", "HELP REQUEST"))
				{
					CurrentMark = MarkShown;
					Pause = true;
					SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);//PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);
					if (PauseAndCheckTermination()) return Exit();				
					if (MarkStatusChanged)
					{
///????????
						};
					}				
				}	
			else if (!AutoFirstMark && !EchoMessageAsk("Scanning finished.\nExit?", "HELP REQUEST"))
			{
				CurrentMark = MarkShown;
				Pause = true;
				SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);//PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);
				if (PauseAndCheckTermination()) return Exit();				
				if (MarkStatusChanged)
				{
///????????
					};
				};
			};
		}
	while (!Terminate && (CurrentMark < pM->Count) && !(Recovery && RecoverySuccessful));
	GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
	UpdateGlobal();
	VPUnlock();
	iStOb->EnableMonitor(true);	
	for (i = goodmarks = 0; i < pM->Count; i++)
		if (pM->pMarks[i].Status == MARK_STATUS_FOUND)
			goodmarks++;	
	SendMessage(UM_CHANGE_STATUS, (goodmarks < 3) ? MSG_SCAN_THREAD_FAILURE : MSG_SCAN_THREAD_SUCCESS);//PostMessage(UM_CHANGE_STATUS, (goodmarks < 3) ? MSG_SCAN_THREAD_FAILURE : MSG_SCAN_THREAD_SUCCESS);
	return (goodmarks < 3) ? MSG_SCAN_THREAD_FAILURE : MSG_SCAN_THREAD_SUCCESS;
	};


int CInitMap::FindNearest(int MarkN, int Nearest[])
{
	double VX, VY, WX, WY, V, W, Det;
	int i, j, k;
	for (j = 0; j < 3; j++)
	{
		double SmallestDist, Dist;
		bool Found = false;
		SmallestDist = 0.;
		for (i = 0; i < pM->Count; i++)
		{			
			Dist = hypot(pM->pMarks[i].Nominal.X - pM->pMarks[MarkN].Nominal.X, pM->pMarks[i].Nominal.Y - pM->pMarks[MarkN].Nominal.Y);
			if (Dist > SmallestDist) SmallestDist = Dist;
			};
		SmallestDist = 2. * SmallestDist + 1.;
		for (i = 0; i < pM->Count; i++)
		{
			if (i == MarkN || pM->pMarks[i].Status != MARK_STATUS_FOUND) continue;
			for (k = 0; (k < j) && (Nearest[k] != i); k++);
			if (k < j) continue;
			Dist = hypot(pM->pMarks[i].Nominal.X - pM->pMarks[MarkN].Nominal.X, 
				pM->pMarks[i].Nominal.Y - pM->pMarks[MarkN].Nominal.Y);
			if (Dist < SmallestDist)
			{
				if (j == 2)
				{
					WX = pM->pMarks[i].Nominal.X - pM->pMarks[Nearest[1]].Nominal.X;
					WY = pM->pMarks[i].Nominal.Y - pM->pMarks[Nearest[1]].Nominal.Y;
					W = 1. / hypot(WX, WY);
					Det = fabs(WX * VY - WY * VX) * V * W;
					if (Det < LIMIT_SIN) continue;
					};
				Nearest[j] = i;
				SmallestDist = Dist;
				Found = true;
				};
			};		
		if (!Found) break;
		if (j == 1)
		{
			VX = pM->pMarks[Nearest[1]].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X;
			VY = pM->pMarks[Nearest[1]].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y;
			V = 1. / hypot(VX, VY);			
			};
		};
	return j;
}

void CInitMap::TransformClusters(int Count)
{
	float Px = fabs(CAM.PixelToMicronX);
	float Py = fabs(CAM.PixelToMicronY);
	float Pxy = Px * Py;
	float Px3y = Px * Px * Pxy;
	float Pxy3 = Py * Py * Pxy;
	float Px2y2 = Pxy * Pxy;	
	int Partial;
	int i;
	for (i = 0; i < Count; i++)
	{
		CSpace[i].Area.f = Pxy * CSpace[i].Area.i;
		CSpace[i].Inertia.IXX *= Px3y;
		CSpace[i].Inertia.IYY *= Pxy3;
		CSpace[i].Inertia.IXY *= Px2y2;
		};
	};

float CInitMap::QualityFactor(float AvgDiam, float Ellipticity)
{  
	float DDiam = fabs(AvgDiam - F.Diameter) / F.Diameter;
	return (1.) / (1. + fabs(Ellipticity) + DDiam);
   };

void CInitMap::GetShape(MyCluster *Cand, float *SAvgDiam, float *SEllipticity, float *SQF)
{
	float Ixx_Iyy = (Cand->Inertia.IXX - Cand->Inertia.IYY);
	float Ixy = Cand->Inertia.IXY;
	float Ixxyy = (Cand->Inertia.IXX + Cand->Inertia.IYY) * .5f;
	Ixx_Iyy *= Ixx_Iyy;
	Ixy *= Ixy;
	float Id = sqrt(Ixy + Ixx_Iyy * 0.25f);
	float Ixx = Ixxyy + Id;
	float Iyy = Ixxyy - Id;
	*SAvgDiam = sqrt(Cand->Area.f / M_PI_4);
	*SEllipticity = (Iyy > (Ixx / (ELLIPTICITY_LIMIT * ELLIPTICITY_LIMIT))) ? (sqrt(Ixx / Iyy) - 1.f) : ELLIPTICITY_LIMIT;
	*SQF = QualityFactor(*SAvgDiam, *SEllipticity);
	};

MyCluster *CInitMap::SelectBest(MyCluster *CSp, int CC)
{
	MyCluster *Best = 0, *Scan, *End;
	float QF, BQF;
	float AvD, El;

	for ((Scan = CSp), (End = CSp + CC); Scan < End; Scan++)
	{
		GetShape(Scan, &AvD, &El, &QF);
   		if ((fabs(AvD - F.Diameter) < F.DiameterTolerance) && (El < F.Ellipticity))
	   		if (!Best || (QF > BQF))
   			{	
				BQF = QF;
	      		Best = Scan;
		      	};
		};
	return Best;
	};

bool CInitMap::LookForMark(int MarkN)
{
	bool Found = false;
	float BestZ, BestX, BestY, BestQF;
	float SX, SY, SQF, SAvgDiam, SEllipticity;
	float StageX, StageY;
	
	UINT CCount;
	MyCluster *BestCand;
	int LimZ = 0;
	UINT FrameDelay = 0;

	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iVP->VPStart();
	iVP->VPGetFrameDelay(&FrameDelay);
	iSt->GetPos(0, &StageX);
	iSt->GetPos(1, &StageY);
	iSt->PosMove(2, Expected.Z - F.FocusStroke, F.FocusSpeed, F.VertAcc);
	int frames;
	iSt->GetLimiter(2, &LimZ);
	for (frames = 0; (frames < (Layers + FrameDelay)) && !LimZ; frames++)
	{
		CCount = F.MaxClusters;
		if (frames >= Layers) iVP->VPFlush((Cluster *)CSpace, &CCount);
		else 
		{
			iVP->VPIterate((Cluster *)CSpace, &CCount);
			pZs[frames] = Z;
			};
		if (frames >= FrameDelay)
		{		
			TransformClusters(CCount);
			//DebugDump(pZs[frames - FrameDelay], frames - FrameDelay, CSpace, CCount);
			if (BestCand = SelectBest(CSpace, CCount))
			{
	      		SX = BestCand->X;
		  		SY = BestCand->Y;
				GetShape(BestCand, &SAvgDiam, &SEllipticity, &SQF);
				if (!Found || (SQF > BestQF))
				{
         			Found = true;
					BestZ = pZs[frames - FrameDelay];
					BestX = SX;
					BestY = SY;
					BestQF = SQF;
					};
      			};
			};
		iSt->GetLimiter(2, &LimZ);
   		};
	if (Found)
	{
		//BestZ -= 2.f * F.FocusStroke / frames;
		iSt->PosMove(2, BestZ, F.ZSetSpeed, F.VertAcc);
		float CX, CY;
//		if (hypot(CX = (BestX - CAM.Width / 2) * CAM.PixelToMicronX, 
//			CY = (BestY - CAM.Height / 2) * CAM.PixelToMicronY) > F.CenterTolerance)
		while (hypot(CX = (BestX - CAM.Width / 2) * CAM.PixelToMicronX, 
			CY = (BestY - CAM.Height / 2) * CAM.PixelToMicronY) > F.CenterTolerance)
		{
			iSt->PosMove(0, CX + StageX, F.ShortDistSpeed, F.ShortDistAcc);
			iSt->PosMove(1, CY + StageY, F.ShortDistSpeed, F.ShortDistAcc);
			int LimX, LimY;
			float PX, PY, PZ;
			do
			{
				iSt->GetLimiter(0, &LimX);
				iSt->GetLimiter(1, &LimY);
				iSt->GetPos(0, &PX);
				iSt->GetPos(1, &PY);
				iSt->GetPos(2, &PZ);
				}
			while (!Terminate && !LimX && !LimY && (fabs(PX - StageX - CX) > F.HorizTolerance || 
				fabs(PY - StageY - CY) > F.HorizTolerance || fabs(PZ - BestZ) > F.VertTolerance));
			if (Terminate || LimX || LimY) return false;
			iSt->Stop(0);
			iSt->Stop(1);
			iSt->GetPos(0, &StageX);
			iSt->GetPos(1, &StageY);
			do
			{
				iSt->GetLimiter(2, &LimZ);
				iSt->GetPos(2, &PZ);
				}
			while (!Terminate && !LimZ && (fabs(PZ - BestZ) > F.VertTolerance));
			if (Terminate || LimZ) return false;
			iSt->Stop(2);
			iVP->VPStart();
			for (frames = 0; frames <= FrameDelay; frames++)
			{
				CCount = F.MaxClusters;
				iVP->VPIterate((Cluster *)CSpace, &CCount);
				};			
			TransformClusters(CCount);
			if (BestCand = SelectBest(CSpace, CCount))
			{
      			BestX = BestCand->X;
      			BestY = BestCand->Y;
				}
			else return false;
			};		
		float PZ;
		do
		{
			iSt->GetLimiter(2, &LimZ);
			iSt->GetPos(2, &PZ);
			}
		while (!Terminate && !LimZ && (fabs(PZ - BestZ) > F.VertTolerance));
		if (Terminate || LimZ) return false;
		iSt->Stop(2);
		iVP->VPStart();
		for (frames = 0; frames <= FrameDelay; frames++)
		{
			CCount = F.MaxClusters;
			iVP->VPIterate((Cluster *)CSpace, &CCount);
			};			
		if (iVP2) 
		{
			iVP2->VPGetPrimaryImage(pImage);
			SaveImage(MarkN, true, BestX, BestY);
			};
		pM->pMarks[MarkN].Stage.X = StageX + (BestX - CAM.Width / 2) * CAM.PixelToMicronX;
		pM->pMarks[MarkN].Stage.Y = StageY + (BestY - CAM.Height / 2) * CAM.PixelToMicronY;
		pM->pMarks[MarkN].Z = BestZ;
		pM->pMarks[MarkN].Status = MARK_STATUS_FOUND;
   		};
	return Found;
	};

void CInitMap::VPLock()
{
	if (iVP2)
	{
		iVP2->VPLock2((DWORD)(void *)ReadPosCallBack, (DWORD)(void *)this);
		iVP2->VPSetProgram(F.ClusteringParameter);
		}
	else 
	{
		iVP->VPLock(F.ClusteringParameter, CAM.Width, CAM.Height, CAM.OffX, CAM.OffY, CAM.WinWidth, CAM.WinHeight, Layers, (DWORD)(void *)ReadPosCallBack, (DWORD)(void *)this);
		};
}

void CInitMap::VPUnlock()
{
	iVP->VPUnlock();
}

void CInitMap::ReadPosCallBack(DWORD Owner)
{
	CInitMap *pOwner = ((CInitMap *)(void *)Owner);
	pOwner->iSt->GetPos(2, &pOwner->Z);
}

bool CInitMap::PauseAndCheckTermination()
{
	MSG Msg;
	SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);//PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);
	VPUnlock();
	iFG->SetLiveGrab();
	iStOb->EnableMonitor(true);
	SetButtonStates(false, true);

	do
	{
		if (WaitMessage()) 
		{
			PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
			if (Msg.message == UM_CHANGE_STATUS)
			{
				if (Msg.wParam == MSG_SCAN_THREAD_CONTINUE)
				{
					SetButtonStates(false, false);
					VPLock();
					iStOb->EnableMonitor(false);
					return false;
					}
				else if (Msg.wParam == MSG_SCAN_THREAD_CLOSING)
				{
					SetButtonStates(true, false);
					return true;
					};
				};
			}
		}
	while (true);

	return false;
}

void CInitMap::CheckPauseAndTermination(bool *pPause, bool *pTerminate)
{
	MSG Msg;

	*pPause = *pTerminate = false;
	if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		if (Msg.message == UM_CHANGE_STATUS)
		{
			*pPause = (Msg.wParam == MSG_SCAN_THREAD_PAUSE);
			*pTerminate = (Msg.wParam == MSG_SCAN_THREAD_CLOSING);
			};
		};
}

void CInitMap::EchoMessage(char *c, char *m)
{		
	if (iCo)
	{
		UINT ExtErrInfo;
		CString MsgString;
		MsgString.Format(":SM: -INITMAP- %s %s", c, m);
		iCo->Write((HSySalHANDLE)m_hWnd, (UCHAR *)MsgString.GetBuffer(1), &ExtErrInfo, 0);
		MsgString.ReleaseBuffer();
		};
	MessageBox(c, m);
}

bool CInitMap::EchoMessageAsk(char *c, char *m)
{
	if (iCo)
	{
		UINT ExtErrInfo;
		CString MsgString;
		MsgString.Format(":SM: -INITMAP- %s %s", c, m);
		iCo->Write((HSySalHANDLE)m_hWnd, (UCHAR *)MsgString.GetBuffer(1), &ExtErrInfo, 0);
		MsgString.ReleaseBuffer();
		};
	return MessageBox(c, m, MB_YESNO) == IDYES;
}



UINT CInitMap::Exit()
{
	iStOb->EnableMonitor(true);
	SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING);//PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING);
	return 0;
}

BOOL CInitMap::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam == 2 && lParam == 0) return TRUE;	
	return CDialog::OnCommand(wParam, lParam);
}

void CInitMap::DebugDump(float z, int frame, MyCluster *pC, int CCount)
{
	FILE *f = fopen("c:\\t.txt", "at");
	int i;
	for (i = 0; i < CCount; i++)
		fprintf(f, "%f %d %f %f %f\n", z, frame, pC[i].Area.f, pC[i].X, pC[i].Y);
	fclose(f);
}

void CInitMap::UpdateGlobal()
{
	int i, scanned, bad;
	for (i = scanned = bad = 0; i < pM->Count; i++)
		if (pM->pMarks[i].Status != MARK_STATUS_NOTSEARCHED)
		{
			scanned++;
			if (pM->pMarks[i].Status == MARK_STATUS_NOTFOUND) bad++;
			};
	CString T;
	T.Format("%d", pM->Count);
	GetDlgItem(IDC_IM_TOTALMARKS)->SetWindowText(T);
	T.Format("%d", scanned);
	GetDlgItem(IDC_IM_MARKSSCANNED)->SetWindowText(T);
	T.Format("%d", bad);
	GetDlgItem(IDC_IM_BADMARKS)->SetWindowText(T);
}

#include "Stage3_i.c"