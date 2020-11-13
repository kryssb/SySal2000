// ManualChecks.cpp : implementation file
//

#include "stdafx.h"
#include "VertigoScan6.h"
#include "ManualChecks.h"
#include <afxdlgs.h>
#include <math.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManualChecks dialog


CManualChecks::CManualChecks(HWND *phwnd, IFrameGrabber *ifg, ISheetMap *ism, IStage *ist, IObjective *iob, ConfigData c, CWnd* pParent /*=NULL*/)
	: CDialog(CManualChecks::IDD, pParent), iFG(ifg), iSM(ism), iSt(ist), iOb(iob), C(c), phWnd(phwnd)
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
	DDX_Text(pDX, IDC_MS_FLAGCODE, m_FlagCode);
	//}}AFX_DATA_MAP
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
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;
	iFG->SetLiveGrab();
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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
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
		iSM->DirMapPoint(m_IX + m_SX * (C.VStep(true, false) - m_IZ), m_IY + m_SY * (C.VStep(true, false) - m_IZ), &TopExt.X, &TopExt.Y);
		iSM->DirMapPoint(m_IX + m_SX * ( - m_IZ), m_IY + m_SY * ( - m_IZ), &TopInt.X, &TopInt.Y);
		iSM->DirMapPoint(m_IX + m_SX * (- C.BaseThickness - m_IZ), m_IY + m_SY * (- C.BaseThickness - m_IZ), &BottomInt.X, &BottomInt.Y);
		iSM->DirMapPoint(m_IX + m_SX * (- C.BaseThickness - C.VStep(false, false) - m_IZ), m_IY + m_SY * (- C.BaseThickness - C.VStep(false, false) - m_IZ), &BottomExt.X, &BottomExt.Y);

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
	// TODO: Add your control notification handler code here
	UpdateData();
	char line[1024];
	int i = m_CheckList.GetSelectionMark();
	if (i >= 0)
	{
		sprintf(line, "%d", m_FlagCode);
		m_CheckList.SetItemText(i, 5, line);
		};
}

void CManualChecks::OnGoSel() 
{
	// TODO: Add your control notification handler code here
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
	static char temp[32];
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
	sprintf(temp, "%.1f", This->First.X);
	This->m_FirstX.SetWindowText(temp);
	sprintf(temp, "%.1f", This->First.Y);
	This->m_FirstY.SetWindowText(temp);
	sprintf(temp, "%.1f", This->First.Z);
	This->m_FirstZ.SetWindowText(temp);
	sprintf(temp, "%.1f", This->Second.X);
	This->m_SecondX.SetWindowText(temp);
	sprintf(temp, "%.1f", This->Second.Y);
	This->m_SecondY.SetWindowText(temp);
	sprintf(temp, "%.1f", This->Second.Z);
	This->m_SecondZ.SetWindowText(temp);
	sprintf(temp, "%.4f", This->Slope.X);
	This->m_SlopeX.SetWindowText(temp);
	sprintf(temp, "%.4f", This->Slope.Y);
	This->m_SlopeY.SetWindowText(temp);
	This->RedrawWindow(0, 0, RDW_UPDATENOW);
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
