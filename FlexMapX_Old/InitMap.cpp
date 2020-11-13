// InitMap.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "InitMap.h"
#include "AffineTransf.h"
#include "IntMarkMap.h"
#include <math.h>
#include "Stage3.h"
#include "FrameGrabberDefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitMap dialog

#define CROSS_SIZE 31

UINT CInitMap::ExecThreadHook(void *pOwner)
{
	return ((CInitMap *)pOwner)->ExecThread();
	};

CInitMap::CInitMap(HWND *phwnd, HANDLE hstatusmutex, CMonitor *pmonitor, IFrameGrabber *ifg, IStage *ist, 
	IObjective *iob, ISySalDataIO *ico, FlexMapData *pConfig, IntMarkMap *pMap, float *pstageminx, float *pstageminy, CWnd* pParent /*=NULL*/)
	: CDialog(CInitMap::IDD, pParent), pMonitor(pmonitor), phWnd(phwnd), HStatusMutex(hstatusmutex), iFG(ifg), iSt(ist), iOb(iob), iCo(ico), pM(pMap), 
	F(*pConfig), pStageMinX(pstageminx), pStageMinY(pstageminy)
{
	//{{AFX_DATA_INIT(CInitMap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	int i;

	iOb->GetSpecs(&CAM);
	for (i = 0; i < pMap->Count; i++)
		pMonitor->SetImage(i, 0, CAM.Width, CAM.Height);

	Terminate = false;
	Working = false;
	Aborted = false;
	Pause = false;
	UseManualCoords = false;
	MarkStatusChanged = false;
	CurrentMark = 0;
	pExecThread = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	iSt3 = 0;
	if (iSt->QueryInterface(IID_IStage3, (void **)&iSt3) != S_OK)
	{
		if (iSt3)
		{
			iSt3->Release();
			iSt3 = 0;
			}
		}
	XBins = (CAM.Width + F.BinningSize - 1) / F.BinningSize;
	YBins = (CAM.Height + F.BinningSize - 1) / F.BinningSize;
	BinnedSize = XBins * YBins;
	GreyLevelBins = XBins * YBins * F.GreyLevelSampleFraction;
	if (GreyLevelBins < 3) GreyLevelBins = 3;
	pCandidates = (t_Candidate *)malloc(sizeof(t_Candidate) * F.MaxStripCandidates);
	pCandidateImages = (BYTE *)GlobalAlloc(GMEM_FIXED, CAM.Width * CAM.Height * F.MaxStripCandidates + sizeof(float) * (XBins * YBins + GreyLevelBins));
	pBinnedImage = (float *)(void *)(pCandidateImages + CAM.Width * CAM.Height * F.MaxStripCandidates);
	pGreyLevelBins = pBinnedImage + XBins * YBins;
}


CInitMap::~CInitMap()
{	
	if (pCandidates)
	{
		free(pCandidates);
		pCandidates = 0;
		}
	if (pExecThread) 
	{
		WaitForSingleObject(pExecThread->m_hThread, INFINITE);
		delete pExecThread;
		pExecThread = 0;
		}
	if (iSt3)
	{
		iSt3->Release();
		iSt3 = 0;
		}
	if (iStOb)
	{
		iStOb->Release();
		iStOb = 0;
		}
	if (pCandidateImages)
	{
		GlobalFree(pCandidateImages);
		pCandidateImages = 0;
		}
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
	ON_BN_CLICKED(IDC_IM_RESCAN, OnRescan)
	ON_BN_CLICKED(IDC_IM_SETMANUALLY, OnSetManually)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitMap message handlers

BOOL CInitMap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	*phWnd = m_hWnd;
	ReleaseMutex(HStatusMutex);
	SetButtonStates(true, false);
	pExecThread = AfxBeginThread((AFX_THREADPROC)ExecThreadHook, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	pExecThread->m_bAutoDelete = FALSE;
	pExecThread->ResumeThread();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CInitMap::SetButtonStates(bool DisableAll, bool IsPaused)
{
	GetDlgItem(IDC_IM_PAUSE)->EnableWindow((!DisableAll) && !IsPaused);
	GetDlgItem(IDC_IM_CONTINUE)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_ABORT)->EnableWindow(!DisableAll);
	GetDlgItem(IDC_IM_PREV)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_NEXT)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_RESCAN)->EnableWindow((!DisableAll) && IsPaused);
	GetDlgItem(IDC_IM_SETMANUALLY)->EnableWindow((!DisableAll) && IsPaused);
}

void CInitMap::ShowMarkInfo(int MarkN)
{
	CString T;
	T.Format("%d", MarkN + 1);
	GetDlgItem(IDC_IM_NEXTMARK)->SetWindowText(T);
	T.Format("%d", pM->pMarks[MarkN].Id);
	GetDlgItem(IDC_IM_NEXTMARKID)->SetWindowText(T);
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
	GetDlgItem(IDC_IM_NEXTMARKSTATUS)->SetWindowText(T);
	T.Format("%.0f", pM->pMarks[MarkN].Nominal.X);
	GetDlgItem(IDC_IM_MAPPEDX)->SetWindowText(T);
	T.Format("%.0f", pM->pMarks[MarkN].Nominal.Y);
	GetDlgItem(IDC_IM_MAPPEDY)->SetWindowText(T);
	T.Format("%.0f", pM->pMarks[MarkN].Stage.X);
	GetDlgItem(IDC_IM_STAGEX)->SetWindowText(T);
	T.Format("%.0f", pM->pMarks[MarkN].Stage.Y);
	GetDlgItem(IDC_IM_STAGEY)->SetWindowText(T);
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

		case MSG_SCAN_THREAD_PAUSE: 		SetButtonStates(false, true);
											break;

		case MSG_SCAN_THREAD_SETREF:		SetButtonStates(true, false);
											GetDlgItem(IDC_IM_CONTINUE)->EnableWindow(true);
											GetDlgItem(IDC_IM_ABORT)->EnableWindow(true);
											break;

		case MSG_SCAN_THREAD_CONTINUE:		SetButtonStates(false, false);
											break;

		case MSG_SCAN_THREAD_SETMANUALLY:	SetButtonStates(false, false);
											break;
		};
	return 0;
}

UINT CInitMap::ExecThread()
{
#define PROLOG \
	{ \
	int colorcode; \
	iFG->SetLiveGrab();  \
	iFG->GetColorCode(VC_TRANSPARENT, &colorcode); \
	iFG->Clear(colorcode); \
	iFG->GetColorCode(VC_LTRED, &colorcode); \
	iFG->Line(CAM.Width / 2 - CROSS_SIZE, CAM.Height / 2, CAM.Width / 2 + CROSS_SIZE, CAM.Height / 2, colorcode); \
	iFG->Line(CAM.Width / 2, CAM.Height / 2 - CROSS_SIZE, CAM.Width / 2, CAM.Height / 2 + CROSS_SIZE, colorcode); \
	}

#define EPILOG(a) \
	{ \
	int colorcode; \
	iFG->GetColorCode(VC_TRANSPARENT, &colorcode); \
	iFG->Clear(colorcode); \
	return a; \
	}

	BYTE *pImage;
	MSG Msg;
	Pause = false;
	int i;
	
	PROLOG;

	bool AutoFirstMark = false;
	AutoFirstMark = (F.SearchFirstMark && iSt3);
	if (AutoFirstMark && iSt3->GetXYRef((BYTE *)"XYReference", pStageMinX, pStageMinY) != S_OK || iSt3->GetZRef((BYTE *)"Glass", SideZ + 1) != S_OK) AutoFirstMark = false;
	else SideZ[0] = SideZ[1] + F.TotalThickness;

	MarkStatusChanged = false;	
	if (!AutoFirstMark)
	{
		PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_SETREF);		
		SendDlgItemMessage(IDC_IM_ACTION, WM_SETTEXT, 0, (LPARAM)"Please put the reference corner of the plate under the cross and press CONTINUE.\r\nThe reference corner is the one for which the mapped coordinates (X,Y) are both minimum.\r\nPlease move the objective to focus on the top surface of the emulsion.");
		iStOb->EnableMonitor(true);
		do
		{
			WaitMessage();
			PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
			if (Msg.message == UM_CHANGE_STATUS && Msg.wParam != MSG_SCAN_THREAD_CONTINUE) 
			{
				Exit();
				EPILOG(0);
				}
			}
		while(Msg.message != UM_CHANGE_STATUS || Msg.wParam != MSG_SCAN_THREAD_CONTINUE);
		iSt->GetPos(0, pStageMinX);
		iSt->GetPos(1, pStageMinY);
		iSt->GetPos(2, &SideZ[0]);
		SideZ[1] = SideZ[0] - F.TotalThickness;
		}

#define Z_INSIDE_STEP 10.0f

	SideZ[0] -= Z_INSIDE_STEP;
	SideZ[1] += Z_INSIDE_STEP;
	PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUE);

	SendDlgItemMessage(IDC_IM_ACTION, WM_SETTEXT, 0, (LPARAM)"Finding marks.");
	CurrentMark = 0;
	while (true)	
	{
		for (; CurrentMark < pM->Count && pM->pMarks[CurrentMark].Status != MARK_STATUS_NOTSEARCHED; CurrentMark++);
		if (CurrentMark == pM->Count) break;
		ShowMarkInfo(CurrentMark);
		if (Pause)
		{
			iStOb->EnableMonitor(true);
			WaitMessage();
			}
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (Msg.message == UM_CHANGE_STATUS)
			{
				if (Pause)
				{
					switch (Msg.wParam)
					{
						case MSG_SCAN_THREAD_NEXT:			CurrentMark++;
															if (CurrentMark == pM->Count) CurrentMark = pM->Count - 1;
															continue;

						case MSG_SCAN_THREAD_PREVIOUS:		CurrentMark--;
															if (CurrentMark < 0) CurrentMark = 0;
															continue;
													
						case MSG_SCAN_THREAD_RESCAN:		pM->pMarks[CurrentMark].Status = MARK_STATUS_NOTSEARCHED;
															pMonitor->SetImage(CurrentMark, 0, CAM.Width, CAM.Height);
															Pause = false;
															SendDlgItemMessage(IDC_IM_ACTION, WM_SETTEXT, 0, (LPARAM)"Finding marks.");
															continue;

						case MSG_SCAN_THREAD_CONTINUE:		Pause = false;
															SendDlgItemMessage(IDC_IM_ACTION, WM_SETTEXT, 0, (LPARAM)"Finding marks.");
															continue;

						case MSG_SCAN_THREAD_SETMANUALLY:	pM->pMarks[CurrentMark].Status = MARK_STATUS_FOUND;
															iStOb->EnableMonitor(false);
															iSt->GetPos(0, &pM->pMarks[CurrentMark].Stage.X);
															iSt->GetPos(1, &pM->pMarks[CurrentMark].Stage.Y);
															iFG->FreezeFrame(&pImage);
															SaveImage(pM->pMarks[CurrentMark].Type, CurrentMark, pImage, CAM.Width / 2, CAM.Height / 2);
															Pause = false;
															SendDlgItemMessage(IDC_IM_ACTION, WM_SETTEXT, 0, (LPARAM)"Finding marks.");
															continue;															

						case MSG_SCAN_THREAD_PAUSE:			continue;

						default:							Aborted = true;
															Exit();
															EPILOG(0);
						}
						
					}
				else
				{
					switch (Msg.wParam)
					{
						case MSG_SCAN_THREAD_PAUSE:			Pause = true;
															SendDlgItemMessage(IDC_IM_ACTION, WM_SETTEXT, 0, (LPARAM)"Pausing.");
															continue;


						case MSG_SCAN_THREAD_CLOSING:
															Aborted = true;
															Exit();
															EPILOG(0);
						}						
					}
				}
			
			}		
		if (Pause) continue;
		Expected.X = pM->pMarks[CurrentMark].Nominal.X - pM->PlateMinX + *pStageMinX;
		Expected.Y = pM->pMarks[CurrentMark].Nominal.Y - pM->PlateMinY + *pStageMinY;
		switch (pM->pMarks[CurrentMark].Side)
		{
			case 1:	Expected.Z = SideZ[0]; break;
			case 2: Expected.Z = SideZ[1]; break;
			default: Expected.Z = SideZ[0]; break;
			}
		switch (pM->pMarks[CurrentMark].Type)
		{
			case MARK_XRAY_TYPE_X:	Step.X = 0.0f;
									Step.Y = CAM.Height * fabs(CAM.PixelToMicronY) - 2.0f * F.StripWidth;
									Start.X = End.X = Expected.X;
									Start.Y = Expected.Y - F.ScanTransverseTolerance;
									End.Y = Expected.Y + F.ScanTransverseTolerance;
									break;

			case MARK_XRAY_TYPE_Y:	Step.X = CAM.Width * fabs(CAM.PixelToMicronX) - 2.0f * F.StripWidth;
									Step.Y = 0.0f;
									Start.Y = End.Y = Expected.Y;
									Start.X = Expected.X - F.ScanTransverseTolerance;
									End.X = Expected.X + F.ScanTransverseTolerance;
									break;
			
			default:				MessageBox("Unknown mark type!!!", "Fatal Error", MB_OK);
									Aborted = true;
									Exit();
									EPILOG(0);
			}
		iStOb->EnableMonitor(false);
		Candidates = 0;
		for ((Expected.X = Start.X), (Expected.Y = Start.Y); Expected.X <= End.X && Expected.Y <= End.Y; (Expected.X += Step.X), (Expected.Y += Step.Y))
		{
			float CurrX, CurrY, CurrZ;
			iSt->GetPos(0, &CurrX);
			iSt->GetPos(1, &CurrY);
			if (hypot(CurrX - Expected.X, CurrY - Expected.Y) < 2.0 * hypot(Step.X, Step.Y))
			{
				iSt->PosMove(0, Expected.X, F.ShortDistSpeed, F.ShortDistAcc);
				iSt->PosMove(1, Expected.Y, F.ShortDistSpeed, F.ShortDistAcc);				
				}
			else
			{
				iSt->PosMove(0, Expected.X, F.LongDistSpeed, F.LongDistAcc);
				iSt->PosMove(1, Expected.Y, F.LongDistSpeed, F.LongDistAcc);				
				}
			iSt->PosMove(2, Expected.Z, F.ZSetSpeed, F.VertAcc);
			bool Arrived = false;
			do
			{
				iSt->GetPos(0, &CurrX);
				iSt->GetPos(1, &CurrY);
				iSt->GetPos(2, &CurrZ);
				Arrived = fabs(CurrX - Expected.X) < F.HorizTolerance && fabs(CurrY - Expected.Y) < F.HorizTolerance && fabs(CurrZ - Expected.Z) < F.VertTolerance;
				if (!Arrived) Sleep(50);
				if (PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE) && Msg.message == UM_CHANGE_STATUS)
					switch (Msg.wParam)
					{
						case MSG_SCAN_THREAD_PAUSE:			Pause = true;
															break;


						case MSG_SCAN_THREAD_CLOSING:
															Aborted = true;
															Exit();
															EPILOG(0);

						}				
				}
			while (!Arrived && !Pause && Candidates < F.MaxStripCandidates);
			if (Pause) break;
			iSt->Stop(0);
			iSt->Stop(1);
			iSt->Stop(2);
			Sleep(F.SettlingTime);
			FindCandidates(pM->pMarks[CurrentMark].Type);
			}
		if (Pause == true) continue;
		if (Candidates == 0)
		{
			pM->pMarks[CurrentMark].Status = MARK_STATUS_NOTFOUND;
			pMonitor->SetImage(CurrentMark, 0, CAM.Width, CAM.Height);			
			//pMonitor->RedrawWindow(0, 0, RDW_UPDATENOW);
			pMonitor->RedrawWindow();
			}
		else
		{
			float BestPeakHeight = pCandidates[0].PeakHeight;
			int best = 0;
			
			for (i = 1; i < Candidates; i++)
				if (pCandidates[i].PeakHeight > BestPeakHeight)
				{
					BestPeakHeight = pCandidates[i].PeakHeight;
					best = i;
					}
			SaveImage(pM->pMarks[CurrentMark].Type, CurrentMark, pCandidateImages + best * CAM.Width * CAM.Height, pCandidates[best].pixX, pCandidates[best].pixY);
			pM->pMarks[CurrentMark].Stage.X = pCandidates[best].X;
			pM->pMarks[CurrentMark].Stage.Y = pCandidates[best].Y;
			pM->pMarks[CurrentMark].Status = MARK_STATUS_FOUND;
			}
		ShowMarkInfo(CurrentMark);
		}
	int goodmarks;
	for (i = goodmarks = 0; i < pM->Count; i++)
		if (pM->pMarks[i].Status == MARK_STATUS_FOUND)
			goodmarks++;	
	PostMessage(UM_CHANGE_STATUS, (goodmarks < 4) ? MSG_SCAN_THREAD_FAILURE : MSG_SCAN_THREAD_SUCCESS);
	EPILOG((goodmarks < 4) ? MSG_SCAN_THREAD_FAILURE : MSG_SCAN_THREAD_SUCCESS);
	};

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
	PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CLOSING);
	return 0;
}

BOOL CInitMap::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam == 2 && lParam == 0) return TRUE;	
	return CDialog::OnCommand(wParam, lParam);
}


void CInitMap::OnAbort() 
{
	// TODO: Add your control notification handler code here
	Aborted = true;
	Terminate = true;
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_FAILURE, 0);
}

void CInitMap::OnContinue() 
{
	// TODO: Add your control notification handler code here
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_CONTINUE, 0);
	SetButtonStates(false, false);
}

void CInitMap::OnNext() 
{
	// TODO: Add your control notification handler code here
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_NEXT, 0);
}

void CInitMap::OnPause() 
{
	// TODO: Add your control notification handler code here
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PAUSE, 0);
	SetButtonStates(false, true);
}

void CInitMap::OnPrev() 
{
	// TODO: Add your control notification handler code here
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_PREVIOUS, 0);	
}

void CInitMap::OnRescan() 
{
	// TODO: Add your control notification handler code here
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_RESCAN, 0);
	SetButtonStates(false, false);
}

void CInitMap::OnSetManually() 
{
	// TODO: Add your control notification handler code here
	pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_SETMANUALLY, 0);
	SetButtonStates(false, false);
}

void CInitMap::SaveImage(int MarkType, int Index, BYTE *pImg, int x, int y)
{
	int i;
	int size = CAM.Width * CAM.Height;
	BYTE *pEnd = pImg + size;
	BYTE *pS;
	for (pS = pImg; pS < pEnd; pS++)
		if (*pS == 0) 
			*pS = 1;
	pMonitor->SetImage(Index, pImg, CAM.Width, CAM.Height);
	ImageLibrary::ImageDescriptor Desc = pMonitor->GetImageDescriptor(Index);
	float xscale = (float)Desc.Width / (float)CAM.Width;
	float yscale = (float)Desc.Height / (float)CAM.Height;
	switch (MarkType)
	{
		case MARK_XRAY_TYPE_X:
								for (i = 0; i < Desc.Width; i++)
									Desc.pStart[((int)(y * yscale)) * Desc.Width + i] = 0;
								break;

		case MARK_XRAY_TYPE_Y:
								for (i = 0; i < Desc.Height; i++)
									Desc.pStart[i * Desc.Width + ((int)(x * xscale))] = 0;
								break;
		}
	//pMonitor->RedrawWindow(0, 0, RDW_UPDATENOW);
	pMonitor->RedrawWindow();
}

void CInitMap::FindCandidates(int MarkType)
{
#ifdef _DEBUG
	static int debugrun = 0;
	static char debugfilename[256];
	sprintf(debugfilename, "c:\\acq\\fx_binned_%d.txt", ++debugrun);
	FILE *fbin = fopen(debugfilename, "wt");
	sprintf(debugfilename, "c:\\acq\\fx_general_%d.txt", debugrun);
	FILE *fgen = fopen(debugfilename, "wt");
	sprintf(debugfilename, "c:\\acq\\fx_filter_%d.txt", debugrun);
	FILE *ffilt = fopen(debugfilename, "wt");
#endif

	BYTE *pImage;
	iFG->FreezeFrame(&pImage);

	int ix, iy, jx, jy, ex, ey;
	int esum, gsum;
	for (iy = 0; iy < CAM.Height; iy = ey)
	{
		ey = iy + F.BinningSize;
		if (ey > CAM.Height) ey = CAM.Height;
		for (ix = 0; ix < CAM.Width; ix = ex)
		{
			ex = ix + F.BinningSize;
			if (ex > CAM.Width) ex = CAM.Width;
			esum = (ey - iy) * (ex - ix);
			gsum = 0;
			for (jy = iy; jy < ey; jy++)
			{
				BYTE *pS = pImage + jy * CAM.Width;
				for (jx = ix; jx < ex; jx++)
					gsum += (unsigned int)(unsigned char)pS[jx];
				}
			pBinnedImage[(iy / F.BinningSize) * XBins + (ix / F.BinningSize)] = (float)gsum / (float)esum;
#ifdef _DEBUG
			fprintf(fbin, "%f\t", pBinnedImage[(iy / F.BinningSize) * XBins + (ix / F.BinningSize)]);
#endif
			}
#ifdef _DEBUG
		fprintf(fbin, "\n");
#endif
		}						
#ifdef _DEBUG
	fclose(fbin);
#endif
	
	int binsfill;
	for (ix = binsfill = 0; ix < BinnedSize; ix++)
	{
		float g = pBinnedImage[ix];
		for (iy = binsfill - 1; iy >= 0 && g > pGreyLevelBins[iy]; iy--);
		if (iy <= binsfill - 1)
		{
			iy++;
			for (jy = binsfill - 1; jy > iy; jy--)
				pGreyLevelBins[jy] = pGreyLevelBins[jy - 1];
			pGreyLevelBins[iy] = g;			
			if (binsfill < GreyLevelBins) binsfill++;
			}
		}
	float lightscale;
	for ((ix = 0), (lightscale = 0.0f); ix < GreyLevelBins; lightscale += pGreyLevelBins[ix++]);
	lightscale = GreyLevelBins / lightscale;
	for (ix = 0; ix < BinnedSize; pBinnedImage[ix++] *= lightscale);

#ifdef _DEBUG
	fprintf(fgen, "binsfill: %d lightscale: %f", binsfill, lightscale);
	fclose(fgen);
#endif

	float bestpeak = F.StripPeakThreshold;
	float bestpos = -1;
	switch (MarkType)
	{
		case MARK_XRAY_TYPE_X:
								for (jy = 0; jy < YBins - F.FIRSize; jy++)
								{
									float fsum = 0.0;
									for (ey = 0; ey < F.FIRSize; ey++)
									{
										int f = F.FIR[ey];
										if (f == 0) continue;
										float sum = 0.0f;
										float *pB = pBinnedImage + (jy + ey) * XBins;
										for (ix = 0; ix < XBins; sum += pB[ix++]);
										fsum += sum * f;
										}
#ifdef _DEBUG
									fprintf(ffilt, "X %d %f\n", jy, fsum);
#endif
									if (fsum > bestpeak)
									{
										bestpos = jy + F.FIRSize * 0.5;
										bestpeak = fsum;
										pCandidates[Candidates].pixX = CAM.Width / 2;
										pCandidates[Candidates].pixY = bestpos * F.BinningSize;
										iSt->GetPos(0, &pCandidates[Candidates].X);
										iSt->GetPos(1, &pCandidates[Candidates].Y);
										pCandidates[Candidates].Y + (pCandidates[Candidates].pixY - CAM.Height / 2) * CAM.PixelToMicronY;
										}
									}
								break;

		case MARK_XRAY_TYPE_Y:
								for (jx = 0; jx < XBins - F.FIRSize; jx++)
								{
									float fsum = 0.0;
									for (ex = 0; ex < F.FIRSize; ex++)
									{
										int f = F.FIR[ex];
										if (f == 0) continue;
										float sum = 0.0f;
										float *pB = pBinnedImage + (jx + ex);
										for (iy = 0; iy < BinnedSize; iy += XBins)
											sum += pB[iy];
										fsum += sum * f;
										}
#ifdef _DEBUG
									fprintf(ffilt, "Y %d %f\n", jx, fsum);
#endif
									if (fsum > bestpeak)
									{
										bestpos = jx + F.FIRSize * 0.5;
										bestpeak = fsum;
										pCandidates[Candidates].pixY = CAM.Height / 2;
										pCandidates[Candidates].pixX = bestpos * F.BinningSize;
										iSt->GetPos(0, &pCandidates[Candidates].X);
										iSt->GetPos(1, &pCandidates[Candidates].Y);
										pCandidates[Candidates].X + (pCandidates[Candidates].pixX - CAM.Width / 2) * CAM.PixelToMicronX;
										}
									}
								break;
		}
	if (bestpos >= 0.0f)
	{
		memcpy(pCandidateImages + CAM.Width * CAM.Height * Candidates, pImage, CAM.Width * CAM.Height);
		pCandidates[Candidates].PeakHeight = bestpeak;		
		Candidates++;
		}
#ifdef _DEBUG
	fclose(ffilt);
#endif
}
