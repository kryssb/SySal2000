// ManualChecks.cpp : implementation file
//

#include "stdafx.h"
#include "VertigoScan7.h"
#include "ManualChecks.h"
#include <afxdlgs.h>
#include <math.h>
#include <stdio.h>
#include "DBReferenceMap.h"
#include "ScanMapDetails.h"
#using "QuickMapper.dll"

#include "moviemaker.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManualChecks dialog


CManualChecks::CManualChecks(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IVisionProcessor3 *ivp, ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, IFrameGrabber *ifg, ISheetMap *ism, IStage2 *ist, IObjective *iob, ConfigData c, CWnd* pParent /*=NULL*/)
	: CDialog(CManualChecks::IDD, pParent), iFG(ifg), iSM(ism), iSt(ist), iOb(iob), C(c), phWnd(phwnd), iVP(ivp), iTk1(itk1), iTk2(itk2), iFt1(ift1), iFt2(ift2), iSelf(iself), iIO(iio)
	, m_Found(FALSE)	
{
	//{{AFX_DATA_INIT(CManualChecks)
	m_IX = 0.0f;
	m_IY = 0.0f;
	m_IZ = 0.0f;
	m_SX = 0.0f;
	m_SY = 0.0f;	
	m_Show = TRUE;
	m_CheckFile = _T("");
	m_FlagCode = 0;
	//}}AFX_DATA_INIT
	First.X = First.Y = First.Z = Second.X = Second.Y = Second.Z = Slope.X = Slope.Y = Slope.Z = 0.f;
	m_Auto = FALSE;
	MapTrackArray = nullptr;
	RefTrackArray = nullptr;
	OffsetX = OffsetY = 0.0;
	m_MapMaxOffset = 100;

	InitJoystick();
}

CManualChecks::CManualChecks(HWND *phwnd, IFrameGrabber *ifg, ISheetMap *ism, IStage2 *ist, IObjective *iob, ConfigData c, long id, float posx, float posy, float slopex, float slopey, float postol, float slopetol, CWnd* pParent)   // constructor for driven manual checks.
	: CDialog(CManualChecks::IDD, pParent), iFG(ifg), iSM(ism), iSt(ist), iOb(iob), C(c), phWnd(phwnd), iVP(0), iTk1(0), iTk2(0), iFt1(0), iFt2(0), iSelf(0), iIO(0)
{
	//{{AFX_DATA_INIT(CManualChecks)
	m_IX = posx;
	m_IY = posy;
	m_IZ = 0.0f;
	m_SX = slopex;
	m_SY = slopey;
	m_PosTol = postol;
	m_SlopeTol = slopetol;
	m_Show = TRUE;
	m_CheckFile = _T("");
	m_FlagCode = 0;
	//}}AFX_DATA_INIT
	First.X = First.Y = First.Z = Second.X = Second.Y = Second.Z = Slope.X = Slope.Y = Slope.Z = 0.f;
	m_Auto = TRUE;
	m_MapMaxOffset = 100;

	InitJoystick();
}

void CManualChecks::InitJoystick()
{
	if (joyGetNumDevs() >= 1)
	{
		for (JoystickN = 15; JoystickN >= 0; JoystickN--)
		{
			JOYINFO jinfo;			
			if (joyGetPos(JoystickN, &jinfo) == JOYERR_NOERROR) break;
		}						
		joyGetDevCaps((unsigned)JoystickN, &caps, sizeof(caps));
	}
	LastSet1 = 0;
	LastSet2 = 0;
	LastToggleFound = 0;
	LastSwitchEmuLayer = 0;
	LastGo = 0;
}

CManualChecks::~CManualChecks()
{
	
}

void CManualChecks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManualChecks)
	DDX_Control(pDX, IDC_MC_ACTIVATEMOUSE, m_MouseTrap);
	DDX_Control(pDX, IDC_MC_MYSY, m_SlopeY);
	DDX_Control(pDX, IDC_MC_MYSX, m_SlopeX);
	DDX_Control(pDX, IDC_MC_PY, m_MouseY);
	DDX_Control(pDX, IDC_MC_PX, m_MouseX);
	DDX_Control(pDX, IDC_MC_SPZ, m_SecondZ);
	DDX_Control(pDX, IDC_MC_SPY, m_SecondY);
	DDX_Control(pDX, IDC_MC_SPX, m_SecondX);
	DDX_Control(pDX, IDC_MC_FPZ, m_FirstZ);
	DDX_Control(pDX, IDC_MC_FPY, m_FirstY);
	DDX_Control(pDX, IDC_MC_FPX, m_FirstX);
	DDX_Control(pDX, IDC_MS_CHECKLIST, m_CheckList);
	DDX_Text(pDX, IDC_MC_IX, m_IX);
	DDX_Text(pDX, IDC_MC_IY, m_IY);
	DDX_Text(pDX, IDC_MC_IZ, m_IZ);
	DDX_Text(pDX, IDC_MC_SX, m_SX);
	DDX_Text(pDX, IDC_MC_SY, m_SY);
	DDX_Check(pDX, IDC_MC_SHOW, m_Show);
	DDX_Text(pDX, IDC_MC_CHECKFILE, m_CheckFile);
	DDX_Text(pDX, IDC_MC_FLAGCODE, m_FlagCode);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_MC_FOUND, m_Found);
	DDX_Text(pDX, IDC_MC_MAPPOSOFFSET, m_MapMaxOffset);
	DDV_MinMaxDouble(pDX, m_MapMaxOffset, 10, 100000);
}


BEGIN_MESSAGE_MAP(CManualChecks, CDialog)
	//{{AFX_MSG_MAP(CManualChecks)
	ON_BN_CLICKED(IDC_MC_GO, OnGo)
	ON_BN_CLICKED(IDC_MC_SHOW, OnShow)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MC_SELCHECKFILE, OnSelCheckFile)
	ON_BN_CLICKED(IDC_MC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_MC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_MC_FLAGSEL, OnFlagSel)
	ON_BN_CLICKED(IDC_MC_GOSEL, OnGoSel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
	ON_BN_CLICKED(IDC_MC_DBMAP, &CManualChecks::OnBnClickedMcDbmap)
	ON_BN_CLICKED(IDC_MC_REFMAPCLEAR, &CManualChecks::OnBnClickedMcRefmapclear)
	ON_BN_CLICKED(IDC_MC_MAPCLEAR, &CManualChecks::OnBnClickedMcMapclear)
	ON_BN_CLICKED(IDC_MC_SCANMAP, &CManualChecks::OnBnClickedMcScanmap)
	ON_BN_CLICKED(IDC_MC_RESETOFFSETS, &CManualChecks::OnResetOffsets)
    ON_BN_CLICKED(IDC_MC_MAKEMOVIE3060, &CManualChecks::OnBnClickedMcMakemovie3060)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualChecks message handlers

void CManualChecks::OnGo() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	double StageX, StageY;
	float X, Y;
	X = m_IX + m_SX * (- m_IZ - 0.5f * C.BaseThickness);
	Y = m_IY + m_SY * (- m_IZ - 0.5f * C.BaseThickness);
	if (iSM->DirFixPoint(X, Y) != S_OK || iSM->DirMapPoint(X, Y, &StageX, &StageY) != S_OK)
	{
		MessageBox("Can't map track position!", "Error", MB_ICONERROR);
		return;
		};
	iSt->EnableManualControl(false);
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);	
	iSt->PosMove(0, StageX, C.HSpeed, C.HAcc);
	iSt->PosMove(1, StageY, C.HSpeed, C.HAcc);
	ShowTrack(StageX, StageY, m_Show);
}

void CManualChecks::OnShow() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	float X, Y;
	iSt->GetPos(0, &X);
	iSt->GetPos(0, &Y);
	ShowTrack(X, Y, m_Show);
}

BOOL CManualChecks::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	*phWnd = m_hWnd;
	iFG->SetLiveGrab();	
	{
		ISySalObject *iStOb = 0;
		iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
		iStOb->EnableMonitor(true);
		iStOb->Release();
	}
	IObjective2 *iOb2 = 0;
	if (iOb->QueryInterface(IID_IObjective2, (void **)&iOb2) == S_OK)
	{
		iOb2->GetSpecs2(&CSP);
		iOb2->Release();
		}
	else
	{
		iOb->GetSpecs((CameraSpec *)&CSP);
		CSP.RefractiveShrinkage = 1.f;
		};
	CRect ClRect;
	m_CheckList.GetClientRect(ClRect);
	char tempstr[2048];
	if (m_Auto)
	{
		sprintf(tempstr, "Manual Check for track %d", m_Id);
		SetWindowText(tempstr);
		sprintf(tempstr, "%.1f", m_PosTol);
		SendDlgItemMessage(IDC_MC_IX, EM_SETREADONLY, TRUE, 0);
		SendDlgItemMessage(IDC_MC_IY, EM_SETREADONLY, TRUE, 0);
		SendDlgItemMessage(IDC_MC_SX, EM_SETREADONLY, TRUE, 0);
		SendDlgItemMessage(IDC_MC_SY, EM_SETREADONLY, TRUE, 0);
		GetDlgItem(IDC_MC_POSTOL)->SetWindowText(tempstr);		
		GetDlgItem(IDC_MC_POSTOL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MC_POSTOLLABEL)->ShowWindow(SW_SHOW);
		sprintf(tempstr, "%.4f", m_SlopeTol);
		GetDlgItem(IDC_MC_SLOPETOL)->SetWindowText(tempstr);
		GetDlgItem(IDC_MC_SLOPETOL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MC_SLOPETOLLABEL)->ShowWindow(SW_SHOW);		
		GetDlgItem(IDC_MC_LOAD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_SAVE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_GOSEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_FOUND)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MC_CHECKFILE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_SELCHECKFILE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_FLAGCODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_FLAGSEL)->SetWindowText("Send result");
		GetDlgItem(IDC_MC_TRACKPOS)->SetWindowText("First position (X, Y, Z) (position output)");
		GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
		GetDlgItem(IDC_MC_REFMAPCLEAR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_DBMAP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_MAPCLEAR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_SCANMAP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_MAPOFFSETLABEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_MAPPOSOFFSET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_OFFSETSLABEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_OFFSETS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MC_RESETOFFSETS)->ShowWindow(SW_HIDE);
		m_CheckList.ShowWindow(SW_HIDE);
		UpdateData(FALSE);
	};	
	double w = ClRect.Width() - GetSystemMetrics(SM_CXVSCROLL);
	m_CheckList.InsertColumn(0, "ID", LVCFMT_RIGHT, w * 4. / 36., 0);
	m_CheckList.InsertColumn(1, "IX", LVCFMT_RIGHT, w * 8. / 36., 1);
	m_CheckList.InsertColumn(2, "IY", LVCFMT_RIGHT, w * 8. / 36., 2);
	m_CheckList.InsertColumn(3, "SX", LVCFMT_RIGHT, w * 6. / 36., 3);
	m_CheckList.InsertColumn(4, "SY", LVCFMT_RIGHT, w * 6. / 36., 4);
	m_CheckList.InsertColumn(5, "Flag", LVCFMT_RIGHT, w * 4. / 36., 5);
	m_CheckList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_MouseTrap.NotifyContext = this;
	m_MouseTrap.pNotifyMove = NotifyMove;
	m_MouseTrap.pNotifyKeyDown = NotifyKeyDown;
	iFG->VideoInfo(&VIS);
	iFG->LoadStockCursor(VC_STOCKCURSORS_CROSS);
	iFG->SetCursorPos(VIS.Width / 2, VIS.Height / 2);
	m_MouseTrap.SetBounds(0, 0, VIS.Width, VIS.Height);	
	m_MouseTrap.X = VIS.Width / 2;
	m_MouseTrap.Y = VIS.Height / 2;	
	if (m_Auto) OnGo();
	if (JoystickN >= 0) 
	{
		CString str = "";
		if (C.AxXAxis != -1 && C.AxYAxis != -1) str += "Use joystick lever to move pointer on display.";
		else str += "Use joystick to move pointer on display.";
		if (C.DigSet1 != -1 && C.DigSet2 != -1) str += "\r\nUse joystick buttons to define top and bottom point of tracks.";
		if (C.DigSwitchEmuLayer != -1) str += "\r\nUse joystick button to quickly switch between emulsion layers.";
		if (C.DigToggleFound != -1) str += "\r\nUse joystick button to mark track as found/not found.";
		if (C.DigGo != -1) str += "\r\nUse joystick button to return to expected track position.";
		GetDlgItem(IDC_MC_ACTIVATEMOUSE)->SetWindowText(str);
		GetDlgItem(IDC_MC_ACTIVATEMOUSE)->EnableWindow(FALSE);
		StartTimer();
	}
	NotifyMove(this, m_MouseTrap.X, m_MouseTrap.Y);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CManualChecks::StartTimer()
{
	SetTimer(55, 50, 0);
}

void CManualChecks::StopTimer()
{
	KillTimer(55);
}

LRESULT CManualChecks::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) 
	{
		case SYSAL_ASYNC_STATUS_IDLE:	EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
										break;
		};
	return 0;
}

void CManualChecks::ShowTrack(float CurrX, float CurrY, bool bShow)
{
	int col;
	iFG->GetColorCode(VC_TRANSPARENT, &col);
	iFG->Clear(col);
	if (bShow)
	{
		struct t_V2
		{
			double X, Y;
			} TopExt, TopInt, BottomInt, BottomExt;

		CPoint PTopExt, PTopInt, PBottomInt, PBottomExt;
	
		iSM->InvFixPoint(CurrX, CurrY);
		iSM->DirMapPoint(m_IX + OffsetX + m_SX * (C.VStep(true, false) - m_IZ), m_IY + OffsetY + m_SY * (C.VStep(true, false) - m_IZ), &TopExt.X, &TopExt.Y);
		iSM->DirMapPoint(m_IX + OffsetX + m_SX * ( - m_IZ), m_IY + OffsetY + m_SY * ( - m_IZ), &TopInt.X, &TopInt.Y);
		iSM->DirMapPoint(m_IX + OffsetX + m_SX * (- C.BaseThickness - m_IZ), m_IY + OffsetY + m_SY * (- C.BaseThickness - m_IZ), &BottomInt.X, &BottomInt.Y);
		iSM->DirMapPoint(m_IX + OffsetX + m_SX * (- C.BaseThickness - C.VStep(false, false) - m_IZ), m_IY + OffsetY + m_SY * (- C.BaseThickness - C.VStep(false, false) - m_IZ), &BottomExt.X, &BottomExt.Y);

		PTopExt.x = (TopExt.X - CurrX) / CSP.PixelToMicronX + CSP.Width / 2;
		PTopExt.y = (TopExt.Y - CurrY) / CSP.PixelToMicronY + CSP.Height / 2;
		PTopInt.x = (TopInt.X - CurrX) / CSP.PixelToMicronX + CSP.Width / 2;
		PTopInt.y = (TopInt.Y - CurrY) / CSP.PixelToMicronY + CSP.Height / 2;
		PBottomInt.x = (BottomInt.X - CurrX) / CSP.PixelToMicronX + CSP.Width / 2;
		PBottomInt.y = (BottomInt.Y - CurrY) / CSP.PixelToMicronY + CSP.Height / 2;
		PBottomExt.x = (BottomExt.X - CurrX) / CSP.PixelToMicronX + CSP.Width / 2;
		PBottomExt.y = (BottomExt.Y - CurrY) / CSP.PixelToMicronY + CSP.Height / 2;
	
		iFG->GetColorCode(VC_LTRED, &col);
		iFG->Line(PTopExt.x, PTopExt.y, PTopInt.x, PTopInt.y, col);
		iFG->GetColorCode(VC_LTGREEN, &col);
		iFG->Line(PTopInt.x, PTopInt.y, PBottomInt.x, PBottomInt.y, col);
		iFG->GetColorCode(VC_LTBLUE, &col);
		iFG->Line(PBottomInt.x, PBottomInt.y, PBottomExt.x, PBottomExt.y, col);
		};
}

void CManualChecks::OnDestroy() 
{
	if (JoystickN >= 0) StopTimer();
	iFG->DeleteCursor();
	ShowTrack(0., 0., false);
	*phWnd = 0;

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

void CManualChecks::OnSelCheckFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "txt", m_CheckFile, OFN_PATHMUSTEXIST, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_CheckFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CManualChecks::OnLoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_CheckFile != "")
	{
		FILE *f = fopen(m_CheckFile, "rt");
		if (f)
		{
			char line[1024];
			m_CheckList.DeleteAllItems();
			int i = 0;
			while (!feof(f))
			{
				int v;
				struct t_track
				{
					int id;
					float ix, iy, sx, sy;
					int flag;
				} track;
				fgets(line, 1023, f);
				v = sscanf(line, "%d %f %f %f %f %d", &track.id, &track.ix, &track.iy, &track.sx, &track.sy, &track.flag);
				if (v == 5) track.flag = -1;
				else if (v < 5) break;
				sprintf(line, "%d", track.id);
				m_CheckList.InsertItem(i, line);
				sprintf(line, "%.1f", track.ix);
				m_CheckList.SetItemText(i, 1, line);
				sprintf(line, "%.1f", track.iy);
				m_CheckList.SetItemText(i, 2, line);
				sprintf(line, "%.4f", track.sx);
				m_CheckList.SetItemText(i, 3, line);
				sprintf(line, "%.4f", track.sy);
				m_CheckList.SetItemText(i, 4, line);
				sprintf(line, "%d", track.flag);
				m_CheckList.SetItemText(i, 5, line);
				i++;
				};
			fclose(f);
			}
		else MessageBox("Can't open input file!\r\nAborting.", "File Error", MB_ICONERROR);
		};
}

void CManualChecks::OnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_CheckFile != "")
	{
		FILE *f = fopen(m_CheckFile, "wt");
		if (f)
		{
			char line[1024];
			int i;
			for (i = 0; i < m_CheckList.GetItemCount(); i++)
			{
				m_CheckList.GetItemText(i, 0, line, 1023);
				fprintf(f, "%s ", line);
				m_CheckList.GetItemText(i, 1, line, 1023);
				fprintf(f, "%s ", line);
				m_CheckList.GetItemText(i, 2, line, 1023);
				fprintf(f, "%s ", line);
				m_CheckList.GetItemText(i, 3, line, 1023);
				fprintf(f, "%s ", line);
				m_CheckList.GetItemText(i, 4, line, 1023);
				fprintf(f, "%s ", line);
				m_CheckList.GetItemText(i, 5, line, 1023);
				fprintf(f, "%s\n", line);
				};
			fclose(f);
			}
		else MessageBox("Can't open output file!\r\nAborting.", "File Error", MB_ICONERROR);
		};
	
}

void CManualChecks::OnFlagSel() 
{
	UpdateData();
	if (m_Auto)
	{
		if (m_Found == TRUE)
		{
			if (First.Z <= Second.Z)
			{
				TVector Third = First;
				First = Second;
				Second = Third;
				TypePoints();
				}
			if (fabs(m_IX - First.X) > m_PosTol) 
			{
				MessageBox("Position out of tolerance in X.", "Incorrect candidate", MB_OK);
				return;
				}
			if (fabs(m_IY - First.Y) > m_PosTol) 
			{
				MessageBox("Position out of tolerance in Y.", "Incorrect candidate", MB_OK);
				return;
				}
			if (fabs(m_SX - Slope.X) > m_SlopeTol) 
			{
				MessageBox("Slope out of tolerance in X.", "Incorrect candidate", MB_OK);
				return;
				}
			if (fabs(m_SY - Slope.Y) > m_SlopeTol) 
			{
				MessageBox("Slope out of tolerance in Y.", "Incorrect candidate", MB_OK);
				return;
				}
			}
		EndDialog(IDOK);
		}
	else
	{
		char line[1024];
		int i = m_CheckList.GetSelectionMark();
		if (i >= 0)
		{
			sprintf(line, "%d", m_FlagCode);
			m_CheckList.SetItemText(i, 5, line);
			};
		}
}

void CManualChecks::OnGoSel() 
{
	UpdateData();
	int i = m_CheckList.GetSelectionMark();
	if (i < 0) return;
	char line[1024];
	m_CheckList.GetItemText(i, 1, line, 1023);
	m_IX = atof(line);
	m_CheckList.GetItemText(i, 2, line, 1023);
	m_IY = atof(line);
	m_CheckList.GetItemText(i, 3, line, 1023);
	m_SX = atof(line);
	m_CheckList.GetItemText(i, 4, line, 1023);
	m_SY = atof(line);
	m_IZ = 0.;
	UpdateData(FALSE);
	OnGo();
}

void CManualChecks::NotifyMove(void *pOwner, int x, int y)
{
	CManualChecks *This = (CManualChecks *)pOwner;
	float X, Y;
	This->iFG->SetCursorPos(x, y);
	This->MouseToWorld(x, y, &X, &Y);
	X -= This->OffsetX;
	Y -= This->OffsetY;
	static char temp[32];
	sprintf(temp, "%.1f", X);
	This->m_MouseX.SetWindowText(temp);
	sprintf(temp, "%.1f", Y);
	This->m_MouseY.SetWindowText(temp);
	This->RedrawWindow(0, 0, RDW_UPDATENOW);
}	

void CManualChecks::NotifyKeyDown(void *pOwner, int key)
{
	CManualChecks *This = (CManualChecks *)pOwner;	
	TVector *pV = 0;
	switch (key)
	{
		case '1':		pV = &This->First;
						break;

		case '2':		pV = &This->Second;
						break;

		default:		return;
		};
	This->MouseToWorld(This->m_MouseTrap.X, This->m_MouseTrap.Y, &pV->X, &pV->Y);
	This->iSt->GetPos(2, &pV->Z);
	pV->Z *= This->CSP.RefractiveShrinkage;
	pV->X -= This->OffsetX;
	pV->Y -= This->OffsetY;
	This->Slope.Z = This->First.Z - This->Second.Z;
	if (fabs(This->Slope.Z) < 2.f)
	{
		This->Slope.X = This->Slope.Y = 0.f;
		}
	else
	{
		This->Slope.X = (This->First.X - This->Second.X) / This->Slope.Z;
		This->Slope.Y = (This->First.Y - This->Second.Y) / This->Slope.Z;
		};
	This->TypePoints();
}	

void CManualChecks::TypePoints()
{
	static char temp[32];
	sprintf(temp, "%.1f", First.X);
	m_FirstX.SetWindowText(temp);
	sprintf(temp, "%.1f", First.Y);
	m_FirstY.SetWindowText(temp);
	sprintf(temp, "%.1f", First.Z);
	m_FirstZ.SetWindowText(temp);
	sprintf(temp, "%.1f", Second.X);
	m_SecondX.SetWindowText(temp);
	sprintf(temp, "%.1f", Second.Y);
	m_SecondY.SetWindowText(temp);
	sprintf(temp, "%.1f", Second.Z);
	m_SecondZ.SetWindowText(temp);
	sprintf(temp, "%.4f", Slope.X);
	m_SlopeX.SetWindowText(temp);
	sprintf(temp, "%.4f", Slope.Y);
	m_SlopeY.SetWindowText(temp);
	RedrawWindow(0, 0, RDW_UPDATENOW);
}

void CManualChecks::MouseToWorld(int mx, int my, float *px, float *py)
{
	double MX, MY;
	float StageX, StageY;
	double X, Y;
	iSt->GetPos(0, &StageX);
	iSt->GetPos(1, &StageY);
	MX = (mx - VIS.Width / 2) * CSP.PixelToMicronX + StageX;
	MY = (my - VIS.Height / 2) * CSP.PixelToMicronY + StageY;
	iSM->InvMapPoint(MX, MY, &X, &Y);
	*px = X;
	*py = Y;
}

void CManualChecks::OnBnClickedMcDbmap()
{
	CDBReferenceMap dbrm;
	dbrm.m_HasX = m_IX;
	dbrm.m_HasY = m_IY;
	if (dbrm.DoModal() == IDOK)	RefTrackArray = dbrm.TrackArray;
	else RefTrackArray = nullptr;
	GetDlgItem(IDC_MC_REFMAPCLEAR)->EnableWindow(!(RefTrackArray == nullptr));
	if (RefTrackArray != nullptr && MapTrackArray != nullptr) FindOffsets();
}

void CManualChecks::OnBnClickedMcRefmapclear()
{
	RefTrackArray = nullptr;
	GetDlgItem(IDC_MC_REFMAPCLEAR)->EnableWindow(FALSE);
}

void CManualChecks::OnBnClickedMcMapclear()
{
	GetDlgItem(IDC_MC_MAPCLEAR)->EnableWindow(FALSE);
}

void CManualChecks::TrackCollectorHook(void *pctx, CScan::DataToWrite *d)
{
	if (d->IsCatalog) return;
	CManualChecks *This = (CManualChecks *)pctx;
	int v, i;
	for (v = 0; v < d->pFrag->Fragment.CountOfViews; v++)
	{
		VS_View2 &w = d->pFrag->Fragment.pViews[v];
		double mxx, mxy, myx, myy, mpx, mpy;
		mxx = w.ImageMat[0][0][0];
		mxy = w.ImageMat[0][0][1];
		myx = w.ImageMat[0][1][0];
		myy = w.ImageMat[0][1][1];
		mpx = w.MapX[0];
		mpy = w.MapY[0];
		for (i = 0; i < w.TCount[0]; i++)
		{
			Track2 &tk = w.pTracks[0][i];
			if (tk.Grains < This->TrackCollectorMinGrains) continue;
			double sl2 = tk.Slope.X * tk.Slope.X + tk.Slope.Y * tk.Slope.Y;
			if (sl2 < This->TrackCollectorMinSlope) continue;
			if (sl2 > This->TrackCollectorMaxSlope) continue;
			SySal::Tracking::MIPEmulsionTrackInfo ^info = gcnew SySal::Tracking::MIPEmulsionTrackInfo();
			info->Slope.X = tk.Slope.X;
			info->Slope.Y = tk.Slope.Y;
			info->Intercept.X = mxx * tk.Intercept.X + mxy * tk.Intercept.Y + mpx;
			info->Intercept.Y = myx * tk.Intercept.Y + myy * tk.Intercept.Y + mpy;
			This->TrackCollector->Add(info);
		}
	}
}

char *CManualChecks::String2Char(System::String ^s)
{
	int i;
	char *c = new char[s->Length + 1];
	for (i = 0; i < s->Length; i++)
		c[i] = s[i];
	c[i] = 0;
	return c;
}

void CManualChecks::OnBnClickedMcScanmap()
{
	ISySalObject *iStOb = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	iStOb->EnableMonitor(true);	
	try
	{
		UpdateData();
		CScanMapDetails scd;
		scd.m_MinX = m_IX - 1000.0;
		scd.m_MaxX = m_IX + 1000.0;
		scd.m_MinY = m_IY - 1000.0;
		scd.m_MaxY = m_IY + 1000.0;
		if (scd.DoModal() == IDOK)
		{
			Identifier Id;
			Id.Part[0] = Id.Part[1] = Id.Part[2] = Id.Part[3] = 0;
			MessageBox("Please put the objective at the surface of the top plastic base, then press OK.", "Help Request", MB_OK);			
			float autozreset;
			iSt->GetPos(2, &autozreset);
			iStOb->EnableMonitor(false);			
			CScan Scan(nullptr, phWnd, iSelf, iIO, iSt, iOb, iFG, iVP, iTk1, iFt1, iTk2, iFt2, iSM, 
				0, //GS
				C, 0, autozreset, true);			
			TrackCollector = gcnew System::Collections::ArrayList();
			TrackCollectorMinGrains = scd.m_MinGrains;
			TrackCollectorMinSlope = scd.m_MinS * scd.m_MinS;
			TrackCollectorMaxSlope = scd.m_MaxS * scd.m_MaxS;
			Scan.InstallDataConsumer(this, TrackCollectorHook);
			if (Scan.ResetAndScan(Id, scd.m_MinX, scd.m_MaxX, scd.m_MinY, scd.m_MaxY, 0, "consumer:trackcollector", true, false, 0.0, 0.0, 0.0, 0.0) == UM_END)
			{
				MapTrackArray = (array<SySal::Tracking::MIPEmulsionTrackInfo ^> ^)TrackCollector->ToArray(SySal::Tracking::MIPEmulsionTrackInfo::typeid);
				if (RefTrackArray != nullptr && MapTrackArray != nullptr) FindOffsets();
			}
			else MapTrackArray = nullptr;
			TrackCollector = nullptr;
		}
		else MapTrackArray = nullptr;
		TrackCollector = nullptr;
	}
	catch (System::Exception ^x)
	{
		TrackCollector = nullptr;
		MapTrackArray = nullptr;
		char *c = String2Char(x->ToString());
		::MessageBox(0, c, "Error scanning track map", MB_ICONERROR | MB_OK);
		delete [] c;
	}
	GetDlgItem(IDC_MC_MAPCLEAR)->EnableWindow(!(MapTrackArray == nullptr));
	iStOb->EnableMonitor(true);
	iStOb->Release();
}

bool CManualChecks::FindOffsets()
{
	if (UpdateData())
	{
		SySal::Processing::QuickMapping::QuickMapper ^Q = gcnew SySal::Processing::QuickMapping::QuickMapper();
		SySal::Processing::QuickMapping::Configuration ^C = (SySal::Processing::QuickMapping::Configuration ^)(Q->Config);
		C->PosTol = 20.0;
		C->SlopeTol = 0.02;
		C->FullStatistics = false;
		C->UseAbsoluteReference = true;
		Q->Config = C;
		HCURSOR HCur = GetCursor();
		try
		{
			SetCursor(LoadCursor(0, IDC_WAIT));
			array<SySal::Scanning::PostProcessing::PatternMatching::TrackPair ^> ^pairs = Q->Match(RefTrackArray, MapTrackArray, 0.0, m_MapMaxOffset, m_MapMaxOffset);
			if (pairs->Length < 5) throw gcnew System::Exception();
			{
				double avgx = 0.0, avgy = 0.0;
				int i;
				for (i = 0; i < pairs->Length; i++)
				{
					avgx += pairs[i]->Second.Info->Intercept.X - pairs[i]->First.Info->Intercept.X;
					avgy += pairs[i]->Second.Info->Intercept.Y - pairs[i]->First.Info->Intercept.Y;
				}
				avgx /= pairs->Length;
				avgy /= pairs->Length;
				int n = 0;
				double offx = 0.0, offy = 0.0;
				double dx, dy;
				for (i = 0; i < pairs->Length; i++)
				{
					dx = pairs[i]->Second.Info->Intercept.X - pairs[i]->First.Info->Intercept.X;
					if (fabs(dx - avgx) > 10.0) continue;
					dy = pairs[i]->Second.Info->Intercept.Y - pairs[i]->First.Info->Intercept.Y;					
					if (fabs(dy - avgy) > 10.0) continue;
					offx += dx;
					offy += dy;
					n++;
				}
				if (n < 5) throw gcnew System::Exception();
				OffsetX = offx / n;
				OffsetY = offy / n;
				char tempstr[256];
				sprintf(tempstr, "%.1f,%.1f", OffsetX, OffsetY);
				GetDlgItem(IDC_MC_OFFSETS)->SetWindowText(tempstr);				
			}
		}
		catch (System::Exception ^x)
		{
			SetCursor(HCur);
			return false;
		}
		SetCursor(HCur);
		return true;
	}
	return false;
}
void CManualChecks::OnResetOffsets()
{
	OffsetX = OffsetY = 0.0;
	GetDlgItem(IDC_MC_OFFSETS)->SetWindowText("");
}

void CManualChecks::OnBnClickedMcMakemovie3060()
{
	if (AfxMessageBox("Put the microscope on the lower surface of the emulsion layer.\n\rPress OK to continue (wait 30 s).", MB_OKCANCEL) == IDOK)
    {
		MovieMaker(iSt, iFG, iOb, 30, 2) ;
        AfxMessageBox("Images stored.");
	}
}

#define JXY_FAST 8.0f
#define JXY_SLOW 0.25f

void CManualChecks::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	//CDialog::OnTimer(nIDEvent);
	if (JoystickN >= 0)
	{
		JOYINFOEX jinfo;
		jinfo.dwSize = sizeof(jinfo);
		jinfo.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(JoystickN, &jinfo) == JOYERR_NOERROR)
		{
			unsigned MaskXDec = (C.DigXDec >= 0) ? (1 << C.DigXDec) : 0;
			unsigned MaskXInc = (C.DigXInc >= 0) ? (1 << C.DigXInc) : 0;
			unsigned MaskYDec = (C.DigYDec >= 0) ? (1 << C.DigYDec) : 0;
			unsigned MaskYInc = (C.DigYInc >= 0) ? (1 << C.DigYInc) : 0;
			unsigned MaskSet1 = (C.DigSet1 >= 0) ? (1 << C.DigSet1) : 0;
			unsigned MaskSet2 = (C.DigSet2 >= 0) ? (1 << C.DigSet2) : 0;
			unsigned MaskToggleFound = (C.DigToggleFound >= 0) ? (1 << C.DigToggleFound) : 0;
			unsigned MaskSwitchEmuLayer = (C.DigSwitchEmuLayer >= 0) ? (1 << C.DigSwitchEmuLayer) : 0;
			unsigned MaskGo = (C.DigGo >= 0) ? (1 << C.DigGo) : 0;

			float xy[2] = { 0.0f, 0.0f };
			int AxisMap[2] = { C.AxXAxis, C.AxYAxis };
			float AxisInvRange[2] = { 0, 0 };
			int AxisCenter[2] = { 0, 0 };
			int i;
			long v;
			for (i = 0; i < 2; i++)
			{
				int amin, amax;
				switch (AxisMap[i])
				{
				case 0:	v = jinfo.dwXpos; amin = caps.wXmin; amax = caps.wXmax; break;
				case 1:	v = jinfo.dwYpos; amin = caps.wYmin; amax = caps.wYmax; break;
				case 2:	v = jinfo.dwZpos; amin = caps.wZmin; amax = caps.wZmax; break;
				case 3:	v = jinfo.dwRpos; amin = caps.wRmin; amax = caps.wRmax; break;
				case 4:	v = jinfo.dwUpos; amin = caps.wUmin; amax = caps.wUmax; break;
				case 5:	v = jinfo.dwVpos; amin = caps.wVmin; amax = caps.wVmax; break;
				default: xy[i] = 0; continue;
				}
				AxisCenter[i] = (amin + amax) / 2;
				AxisInvRange[i] = (amax > amin) ? (2.0f / (amax - amin)) : 0.0f;
				xy[i] = (abs(v - AxisCenter[i]) < 4) ? 0 : ((v - AxisCenter[i]) * AxisInvRange[i]);
			}
			if (xy[0] != 0.0f)
			{
				if (fabs(xy[0]) > 0.9f) xy[0] = xy[0] / fabs(xy[0]) * JXY_FAST;
				else xy[0] = xy[0] / fabs(xy[0]) * JXY_SLOW;
			}
			if (xy[1] != 0.0f)
			{
				if (fabs(xy[1]) > 0.9f) xy[1] = xy[1] / fabs(xy[1]) * JXY_FAST;
				else xy[1] = xy[1] / fabs(xy[1]) * JXY_SLOW;
			}
			if (MaskXDec & jinfo.dwButtons) xy[0] = -1.0f;
			if (MaskXInc & jinfo.dwButtons) xy[0] =  1.0f;
			if (MaskYDec & jinfo.dwButtons) xy[1] =  1.0f;
			if (MaskYInc & jinfo.dwButtons) xy[1] = -1.0f;
			if ((MaskSet1 & jinfo.dwButtons) == 0 && (LastSet1 != 0)) NotifyKeyDown(this, '1');
			LastSet1 = (MaskSet1 & jinfo.dwButtons);
			if ((MaskSet2 & jinfo.dwButtons) == 0 && (LastSet2 != 0)) NotifyKeyDown(this, '2');
			LastSet2 = (MaskSet2 & jinfo.dwButtons);
			if ((MaskToggleFound & jinfo.dwButtons) == 0 && (LastToggleFound != 0)) 
			{
				StopTimer();
				SendDlgItemMessage(IDC_MC_FOUND, BM_CLICK);
				StartTimer();
			}
			LastToggleFound = (MaskToggleFound & jinfo.dwButtons);
			if ((MaskSwitchEmuLayer & jinfo.dwButtons) == 0 && (LastSwitchEmuLayer != 0)) 
			{
				StopTimer();
				SwitchEmuLayer();
				StartTimer();
			}
			LastSwitchEmuLayer = (MaskSwitchEmuLayer & jinfo.dwButtons);
			if ((MaskGo & jinfo.dwButtons) == 0 && (LastGo != 0)) 
			{	
				StopTimer();
				OnGo();
				StartTimer();
			}
			LastGo = (MaskGo & jinfo.dwButtons);			
			m_MouseTrap.X += xy[0];
			m_MouseTrap.Y += xy[1];
			if (m_MouseTrap.X < 0) m_MouseTrap.X = 0; else if (m_MouseTrap.X >= VIS.Width) m_MouseTrap.X = VIS.Width;
			if (m_MouseTrap.Y < 0) m_MouseTrap.Y = 0; else if (m_MouseTrap.Y >= VIS.Height) m_MouseTrap.Y = VIS.Height;
			NotifyMove(this, m_MouseTrap.X, m_MouseTrap.Y);
		}
	}
}

void CManualChecks::SwitchEmuLayer()
{
	float ZHalf = 0.0f;
	IStage3 *iSt3 = 0;
	if (iSt->QueryInterface(IID_IStage3, (void **)&iSt3) != S_OK)
	{
		MessageBox("IStage3 interface not supported by current Stage.\r\nCannot provide \"SwitchEmuLayer\" feature.", "Error", MB_ICONERROR | MB_OK);
		if (iSt3) iSt3->Release();
		return;
	}
	if (iSt3->IsHomeKnown() != S_OK)
	{
		if (MessageBox("The \"SwitchEmuLayer\" feature requires stage homing, but the current Stage has no home reference.\r\nHoming can be performed now, but it will disrupt coordinate mapping.\r\nProceed (if no, \"SwitchEmuLayer\" will be ignored)?", "Warning", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2 | MB_SETFOREGROUND) != IDYES)
		{
			iSt3->Release();
			return;
		}
	}
	if (iSt3->GetZRef((BYTE *)"Glass", &ZHalf) != S_OK)
	{
		MessageBox("\"Glass\" reference position not present in Stage.\r\nCannot provide \"SwitchEmuLayer\" feature.", "Error", MB_ICONERROR | MB_OK);
		iSt3->Release();
		return;
	}
	ZHalf += C.VStep(false, false) + C.BaseThickness * 0.5f;
	float z = 0.0f;
	iSt3->EnableManualControl(false);
	iSt3->Stop(0);
	iSt3->Stop(1);
	iSt3->Stop(2);
	iSt3->GetPos(2, &z);
	iSt3->PosMove(2, ZHalf + ((z > ZHalf) ? -0.5f : 0.5f) * C.BaseThickness, C.VBaseSpeed, C.VAcc);
	iSt3->Release();
}