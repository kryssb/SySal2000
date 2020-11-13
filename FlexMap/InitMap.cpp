// InitMap.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "InitMap.h"
#include "AffineTransf.h"
#include "IntMarkMap.h"
#include "FieldMap.h"
#include <math.h>

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

CInitMap::CInitMap(CString &name, IFrameGrabber *ifg, IStage *ist, IObjective *iob, IClusterFinder *icl, ISySalDataIO *ico,
	FlexMapData *pConfig, IntMarkMap *pMap, HANDLE hEvent, CWnd* pParent /*=NULL*/)
	: CDialog(CInitMap::IDD, pParent), iFG(ifg), iSt(ist), iOb(iob), iCl(icl), iCo(ico), pM(pMap), F(*pConfig),
	hNotifyStatusChangeEvent(hEvent), Name(name), CSpace(0)
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
	iCl->SetCameraSpec(CAM);
	pMarkImages = 0;
	MarkShown = 0;
	Terminate = false;
	Working = false;
	Aborted = false;
	Pause = false;
	UseManualCoords = false;
	MarkStatusChanged = false;
	CurrentMark = 0;
	CSpace = (Cluster *)GlobalAlloc(GMEM_FIXED, F.MaxClusters * sizeof(Cluster));
	pExecThread = 0;
}


CInitMap::~CInitMap()
{	
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
		Aborted = true;
		};
}

void CInitMap::OnContinue() 
{
	// TODO: Add your control notification handler code here
	SetButtonStates(false, false);
	Pause = false;
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
	SetButtonStates(false, false);
	Pause = false;
	MarkStatusChanged = true;
	pM->pMarks[CurrentMark].Status = MARK_STATUS_NOTFOUND;
}

void CInitMap::OnRescan() 
{
	// TODO: Add your control notification handler code here
	SetButtonStates(false, false);
	Pause = false;
	MarkStatusChanged = true;
	ShowMarkInfo(MarkShown);
	pM->pMarks[CurrentMark = MarkShown].Status = MARK_STATUS_NOTSEARCHED;
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
	pMarkImages = new BYTE[XCount * YCount * pM->Count];
	pExecThread = AfxBeginThread((AFX_THREADPROC)ExecThreadHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInitMap::SaveImage(int MarkN, bool AddCross, int X, int Y)
{
	int i, j, x, y;
	BYTE *pImage;
	if (iFG->FreezeFrame(&pImage) == S_OK)
	{
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
			int XC = X * XCount / CAM.Width;
			int YC = Y * YCount / CAM.Height;
			for (i = -CROSS_SIZE; i <= CROSS_SIZE; i++)
				if ((YC + i) >= 0 && (YC + i) < YCount)
					pMarkImages[MarkN * XCount * YCount + (YC + i) * XCount + XC] = 0; 
			for (i = -CROSS_SIZE; i <= CROSS_SIZE; i++)
				if ((XC + i) >= 0 && (XC + i) < XCount)
					pMarkImages[MarkN * XCount * YCount + YC * XCount + XC + i] = 0; 
			};
		}
	else for (i = 0; i < (XCount * YCount); pMarkImages[MarkN * XCount * YCount + i] = 0);
}

void CInitMap::SetButtonStates(bool DisableAll, bool IsPaused)
{
	GetDlgItem(IDC_IM_PAUSE)->EnableWindow((!DisableAll) && !IsPaused);
	GetDlgItem(IDC_IM_CONTINUE)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_ABORT)->EnableWindow((!DisableAll) && !IsPaused);
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
											if (!Working) EndDialog(IDCANCEL);
											break;

		case MSG_SCAN_THREAD_CLOSING:		EndDialog(IDCANCEL);
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

#define ECHOMSG(m, c)\
{\
	if (iCo)\
	{\
		MsgString.Format(":%s: -INITMAP- %s %s", c, m);\
		iCo->Write((HSySalHANDLE)m_hWnd, (UCHAR *)MsgString.GetBuffer(1), &ExtErrInfo, 0);\
		MsgString.ReleaseBuffer();\
		};\
	MessageBox(m, c);\
	}
		 
#define ECHOMSGASK(m, c, a)\
{\
	if (iCo)\
	{\
		MsgString.Format(":%s: -INITMAP- %s %s", c, m);\
		iCo->Write((HSySalHANDLE)m_hWnd, (UCHAR *)MsgString.GetBuffer(1), &ExtErrInfo, 0);\
		MsgString.ReleaseBuffer();\
		};\
	a = MessageBox(m, c, MB_YESNO);\
	}

UINT CInitMap::ExecThread()
{
	CurrentMark = 0;
	MarkStatusChanged = false;
	SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUING);
	UINT ExtErrInfo;
	CString MsgString;
	do
	{
		GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
		ShowMarkInfo(CurrentMark);
		int Nearest[3];
		int CountOfNearest = (MarkStatusChanged && UseManualCoords) ? 4 : FindNearest(CurrentMark, Nearest);
		MarkStatusChanged = false;
		switch (CountOfNearest)
		{
			case 0:		{
							iSt->Stop(0);
							iSt->Stop(1);
							iSt->Stop(2);
							CString msg;
							msg.Format("Please put mark #%d, Id %d in the field of view.\n"
								"Press <Continue> when done.", CurrentMark, pM->pMarks[CurrentMark].Id);
							ECHOMSG(msg, "HELP REQUEST");
							iSt->EnableManualControl(true);
							Pause = true;
							SetButtonStates(false, true);
							while (Pause && !Terminate) Sleep(100);
							if (!Terminate)
							{
								if (MarkStatusChanged) continue;
								iSt->GetPos(0, &Expected.X);
								iSt->GetPos(1, &Expected.Y);
								iSt->GetPos(2, &Expected.Z);
								iSt->PosMove(2, Expected.Z + F.FocusStroke, F.FocusSpeed, Z_ACC);
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
									MarkShown = CurrentMark++;
									GetDlgItem(IDC_IM_MARKVIEW)->RedrawWindow();
									UseManualCoords = false;
									continue;
									// HERE WE CAN CHECK IF THERE'S A RECOVERY //
									}
								else
								{
									pM->pMarks[CurrentMark++].Status = MARK_STATUS_NOTFOUND;									
									continue;
									};
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
							Expected.Z = pM->pMarks[Nearest[0]].Z;
							};
						break;
		
			case 2:		{
							float Expansion = hypot(pM->pMarks[Nearest[0]].Stage.X - pM->pMarks[Nearest[1]].Stage.X, pM->pMarks[Nearest[0]].Stage.Y - pM->pMarks[Nearest[1]].Stage.Y) / 
								hypot(pM->pMarks[Nearest[0]].Nominal.X - pM->pMarks[Nearest[1]].Nominal.X, pM->pMarks[Nearest[0]].Nominal.Y - pM->pMarks[Nearest[1]].Nominal.Y);
							float Angle = atan2(pM->pMarks[Nearest[0]].Stage.X - pM->pMarks[Nearest[1]].Stage.X, pM->pMarks[Nearest[0]].Stage.Y - pM->pMarks[Nearest[1]].Stage.Y) - 
								atan2(pM->pMarks[Nearest[0]].Nominal.X - pM->pMarks[Nearest[1]].Nominal.X, pM->pMarks[Nearest[0]].Nominal.Y - pM->pMarks[Nearest[1]].Nominal.Y);
							float C = cos(Angle), S = sin(Angle);
							Expected.X = pM->pMarks[Nearest[0]].Stage.X + Expansion * (C * (pM->pMarks[CurrentMark].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X) - S * (pM->pMarks[CurrentMark].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y));
							Expected.Y = pM->pMarks[Nearest[0]].Stage.Y + Expansion * (C * (pM->pMarks[CurrentMark].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y) + S * (pM->pMarks[CurrentMark].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X));
							Expected.Z = pM->pMarks[Nearest[0]].Z;
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
							Expected.Z = pM->pMarks[Nearest[0]].Z;
							};
			};
		if (CountOfNearest)
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
			iSt->PosMove(2, Expected.Z + F.FocusStroke, F.FocusSpeed, Z_ACC);
			float NextTime = MaxTime * 1000.f + GetTickCount();
			bool TimedOut, Arrived, Limiter;

#define CHECK_TERMINATION \
{\
	if (Terminate)\
	{\
		PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING);\
		return MSG_SCAN_THREAD_CLOSING;\
		};\
	}

			do
			{
				if (Pause)
				{
					SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);
					while (Pause && !Terminate) Sleep(100);
					CHECK_TERMINATION;
					SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUING);
					if (MarkStatusChanged) 
					{
						if (UseManualCoords)
						{
							iSt->PosMove(0, Expected.X, F.LongDistSpeed, F.LongDistAcc);
							iSt->PosMove(1, Expected.Y, F.LongDistSpeed, F.LongDistAcc);
							iSt->PosMove(2, Expected.Z + F.FocusStroke, F.FocusSpeed, Z_ACC);
							}
						else continue;
						};
					}
				else CHECK_TERMINATION;
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
					iSt->PosMove(2, Expected.Z + F.FocusStroke, F.FocusSpeed, Z_ACC);
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
						if (Pause)
						{
							SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);
							while (Pause && !Terminate) Sleep(100);
							CHECK_TERMINATION;
							SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUING);
							if (MarkStatusChanged) break;
							}
						else CHECK_TERMINATION;
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
						}
					if (Ok = LookForMark(CurrentMark))
					{
						MarkShown = CurrentMark;
						GetDlgItem(IDC_IM_MARKVIEW)->RedrawWindow();
						};
					Field++;
					}
				while (!Ok && Field < FM.GetLength() && !MarkStatusChanged);
				if (MarkStatusChanged) continue;
				if (!Ok) pM->pMarks[CurrentMark].Status = MARK_STATUS_NOTFOUND;
				};
			};
		int i;
		for (i = 0; i < pM->Count && pM->pMarks[i].Status == MARK_STATUS_NOTSEARCHED; i++);
		CurrentMark = i;
		MarkStatusChanged = false;
		if (CurrentMark == pM->Count)
		{
			UINT Ans;
			ECHOMSGASK("Scanning finished.\nExit?", "HELP REQUEST", Ans);
			if (Ans != IDYES)
			{
				CurrentMark = MarkShown;
				Pause = true;
				SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSED);
				while (!Terminate && Pause) Sleep(100);
				CHECK_TERMINATION;
				SendMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUING);
				if (MarkStatusChanged)
				{
///????????
					};
				};
			};
		}
	while (!Terminate && CurrentMark < pM->Count);
	GetDlgItem(IDC_IM_GRIDVIEW)->RedrawWindow();
	PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_SUCCESS);
	return MSG_SCAN_THREAD_SUCCESS;
	};


int CInitMap::FindNearest(int MarkN, int Nearest[])
{
	double VX, VY, WX, WY, V, W, Det;
	int i, j, k;
	for (j = 0; j < 3; j++)
	{
		double SmallestDist, Dist;
		for (i = 0; i < pM->Count; i++)
		{
			if (i == MarkN || pM->pMarks[i].Status != MARK_STATUS_FOUND) continue;
			for (k = 0; (k < j) && (Nearest[k] != i); k++);
			if (k < j) continue;
//			SmallestDist = 2. * hypot(pM->pMarks[i].Nominal.X - pM->pMarks[MarkN].Nominal.X, 
//				pM->pMarks[i].Nominal.Y - pM->pMarks[MarkN].Nominal.Y) + 1.;
			SmallestDist = hypot(pM->pMarks[i].Nominal.X - pM->pMarks[MarkN].Nominal.X, 
				pM->pMarks[i].Nominal.Y - pM->pMarks[MarkN].Nominal.Y);
			Nearest[j] = i;
			break;
			};
		if (i == pM->Count) return j;
		for (; i < pM->Count; i++)
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
				};
			};
		if (j == 1)
		{
			VX = pM->pMarks[Nearest[1]].Nominal.X - pM->pMarks[Nearest[0]].Nominal.X;
			VY = pM->pMarks[Nearest[1]].Nominal.Y - pM->pMarks[Nearest[0]].Nominal.Y;
			V = 1. / hypot(VX, VY);			
			};
		};
	return j;
}

int CInitMap::GetMultiThresholdClusters(BYTE *Image)
{
	float Px = fabs(CAM.PixelToMicronX);
	float Py = fabs(CAM.PixelToMicronY);
	float Pxy = Px * Py;
	float Px3y = Px * Px * Pxy;
	float Pxy3 = Py * Py * Pxy;
	float Px2y2 = Pxy * Pxy;
	int Count = 0;
	int Partial;
	int i, j;
	for (i = 0; i < F.Thresholds; i++)
	{	
		Partial = F.MaxClusters - Count;
		if (iCl->GetClusters(Image, CSpace + Count, &Partial, F.GrayThreshold + i * F.ThresholdStep, 0) != S_OK) continue;
   		if (Partial >= 0)
		{
      		for (j = 0; j < Partial; j++)
			{
				CSpace[Count + j].Area *= Pxy;
				CSpace[Count + j].Inertia.IXX *= Px3y;
				CSpace[Count + j].Inertia.IYY *= Pxy3;
				CSpace[Count + j].Inertia.IXY *= Px2y2;
         		};
      		Count += Partial;
			}
		};
	return Count;
	};

float CInitMap::QualityFactor(float AvgDiam, float Ellipticity)
{  
	float DDiam = (AvgDiam - F.Diameter) / F.Diameter;
	return (AvgDiam / F.Diameter) / (1. + fabs(Ellipticity));
   };

void CInitMap::GetShape(Cluster *Cand, float *SAvgDiam, float *SEllipticity, float *SQF)
{
	float Ixx_Iyy = (Cand->Inertia.IXX - Cand->Inertia.IYY);
	float Ixy = Cand->Inertia.IXY;
	float Ixxyy = (Cand->Inertia.IXX + Cand->Inertia.IYY) * .5f;
	Ixx_Iyy *= Ixx_Iyy;
	Ixy *= Ixy;
	float Id = sqrt(Ixy + Ixx_Iyy * 0.25f);
	float Ixx = Ixxyy + Id;
	float Iyy = Ixxyy - Id;
	*SAvgDiam = sqrt(Cand->Area / M_PI_4);
	*SEllipticity = (Iyy > (Ixx / (ELLIPTICITY_LIMIT * ELLIPTICITY_LIMIT))) ? (sqrt(Ixx / Iyy) - 1.f) : ELLIPTICITY_LIMIT;
	*SQF = QualityFactor(*SAvgDiam, *SEllipticity);
	};

Cluster *CInitMap::SelectBest(Cluster *CSp, int CC)
{
	Cluster *Best = 0, *Scan, *End;
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
	float SZ, SX, SY, SQF, SAvgDiam, SEllipticity;

	BYTE *pImage;
	int CCount;
	Cluster *BestCand;
	int LimZ = 0;

	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	iFG->FreezeFrame(&pImage);
	iSt->PosMove(2, Expected.Z - F.FocusStroke, F.FocusSpeed, Z_ACC);
	int frames = 1;
	iSt->GetLimiter(2, &LimZ);
	iSt->GetPos(2, &SZ);
	while (!LimZ && SZ > (Expected.Z - F.FocusStroke + F.VertTolerance))
	{
		iFG->FreezeFrame(&pImage);
		CCount = GetMultiThresholdClusters(pImage);
		if (BestCand = SelectBest(CSpace, CCount))
		{
      		SX = BestCand->X;
      		SY = BestCand->Y;
			GetShape(BestCand, &SAvgDiam, &SEllipticity, &SQF);
			if (!Found || (SQF > BestQF))
			{
         		Found = true;
				BestZ = SZ;
				BestX = SX;
				BestY = SY;
				BestQF = SQF;
				};
      		};
   		frames++;
		iSt->GetLimiter(2, &LimZ);
		iSt->GetPos(2, &SZ);
   		};
	if (Found)
	{
		BestZ -= 2.f * F.FocusStroke / frames;
		iSt->PosMove(2, BestZ, F.FocusSpeed, Z_ACC);
		float CX, CY;
		if (hypot(CX = (BestX - CAM.Width / 2) * CAM.PixelToMicronX, 
			CY = (BestY - CAM.Height / 2) * CAM.PixelToMicronY) > F.CenterTolerance)
		{
			iSt->PosMove(0, CX + Expected.X, F.ShortDistSpeed, F.ShortDistAcc);
			iSt->PosMove(1, CY + Expected.Y, F.ShortDistSpeed, F.ShortDistAcc);
			int LimX, LimY;
			float PX, PY, PZ;
			do
			{
				iSt->GetLimiter(0, &LimX);
				iSt->GetLimiter(1, &LimX);
				iSt->GetPos(0, &PX);
				iSt->GetPos(1, &PY);
				iSt->GetPos(2, &PZ);
				}
			while (!Terminate && !LimX && !LimY && (fabs(PX - Expected.X - CX) > F.HorizTolerance || 
				fabs(PX - Expected.Y - CY) > F.HorizTolerance || fabs(PZ - BestZ) > F.VertTolerance));
			if (Terminate || LimX || LimY) return false;
			iSt->Stop(0);
			iSt->Stop(1);
			do
			{
				iSt->GetLimiter(2, &LimZ);
				iSt->GetPos(2, &PZ);
				}
			while (!Terminate && !LimZ && (fabs(PZ - BestZ) > F.VertTolerance));
			if (Terminate || LimZ) return false;
			iSt->Stop(2);
			iFG->FreezeFrame(&pImage);
			CCount = GetMultiThresholdClusters(pImage);
			if (BestCand = SelectBest(CSpace, CCount))
			{
      			BestX = (BestCand->X - CAM.Width / 2) * CAM.PixelToMicronX;
      			BestY = (BestCand->Y - CAM.Height / 2) * CAM.PixelToMicronY;
				};
			};
		SaveImage(MarkN, true, BestX, BestY);
		pM->pMarks[MarkN].Stage.X = Expected.X + (BestX - CAM.Width / 2) * CAM.PixelToMicronX;
		pM->pMarks[MarkN].Stage.Y = Expected.Y + (BestY - CAM.Height / 2) * CAM.PixelToMicronY;
		pM->pMarks[MarkN].Z = BestZ;
		pM->pMarks[MarkN].Status = MARK_STATUS_FOUND;
   		};
	return Found;
	};
