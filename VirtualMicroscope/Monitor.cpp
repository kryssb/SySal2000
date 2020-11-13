// Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Monitor.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog


CMonitor::CMonitor(ConfigData *pc, bool *pisseeingmarks, StageEngine *pstgeng, HANDLE *phstageenginemutex, HANDLE *phmonitormutex, void *pctx, void (*penabler)(void *, bool), CWnd* pParent /*=NULL*/)
	: CDialog(/*CMonitor::IDD, pParent*/), pC(pc), pIsSeeingMarks(pisseeingmarks), SpeedMultiplier(1), pStgEng(pstgeng), pHStageEngineMutex(phstageenginemutex), pHMonitorMutex(phmonitormutex), pContext(pctx), pEnabler(penabler),
	m_XYSpeed(pc, pstgeng, phstageenginemutex, &SpeedMultiplier), m_ZSpeed(pc, pstgeng, phstageenginemutex, &SpeedMultiplier)
{
	//{{AFX_DATA_INIT(CMonitor)
	//}}AFX_DATA_INIT
}


void CMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitor)
	DDX_Control(pDX, IDC_M_ZSPEED, m_ZSpeed);
	DDX_Control(pDX, IDC_M_XYSPEED, m_XYSpeed);
	DDX_Control(pDX, IDC_M_LIGHT, m_LightSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitor, CDialog)
	//{{AFX_MSG_MAP(CMonitor)
	ON_BN_CLICKED(IDC_M_HIDE, OnHide)
	ON_BN_CLICKED(IDC_M_RESET, OnReset)
	ON_BN_CLICKED(IDC_M_TOGGLEMANUAL, OnToggleManual)
	ON_BN_CLICKED(IDC_M_1, OnSpeedX1)
	ON_BN_CLICKED(IDC_M_10, OnSpeedX10)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_M_MARKMODE, OnMarkMode)
	ON_BN_CLICKED(IDC_M_GRAINMODE, OnGrainMode)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitor message handlers

void CMonitor::OnHide() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	EnableWindow(FALSE);
	pEnabler(pContext, false);
}

void CMonitor::OnReset() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure you want to reset the stage coordinates?", "RemoteStage Warning", MB_ICONQUESTION | MB_YESNO) == IDYES)
		if (MessageBox("Please confirm that you want to reset the stage coordinates", "RemoteStage Warning", MB_ICONASTERISK | MB_YESNO) == IDYES)
		{
			WaitForSingleObject(*pHStageEngineMutex, INFINITE);
			pStgEng->Reset(0);
			pStgEng->Reset(1);
			pStgEng->Reset(2);
			ReleaseMutex(*pHStageEngineMutex);
			};
}

void CMonitor::OnToggleManual() 
{
	// TODO: Add your control notification handler code here
	EnableManualControl(!m_XYSpeed.IsWindowEnabled());
}

void CMonitor::OnSpeedX1() 
{
	// TODO: Add your control notification handler code here
	SpeedMultiplier = 1;
}

void CMonitor::OnSpeedX10() 
{
	// TODO: Add your control notification handler code here
	SpeedMultiplier = 10;
}

void CMonitor::EnableManualControl(bool bEnable)
{
	m_XYSpeed.EnableWindow(bEnable);
	m_ZSpeed.EnableWindow(bEnable);
	m_LightSlider.EnableWindow(bEnable);
	m_XYSpeed.RedrawWindow();
	m_ZSpeed.RedrawWindow();
	m_LightSlider.RedrawWindow();
	pEnabler(pContext, bEnable);
}

BOOL CMonitor::OnInitDialog() 
{
	CRect WndRect;
	CRect WorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
	GetWindowRect(&WndRect);
	SetWindowPos(0, WorkArea.right - WndRect.Width(), WorkArea.bottom - WndRect.Height(), 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);

	CDialog::OnInitDialog();	
	
	// TODO: Add extra initialization here

	m_LightSlider.SetRange(0, 32767, TRUE);
	m_LightSlider.SetPos(32767);
	m_LightSlider.SetLineSize(32);
	m_LightSlider.SetPageSize(1024);
	for (int i = 2048; i < 32768L; i += 2048) m_LightSlider.SetTic(i);

	SyncMode();

	TimerID = SetTimer(100, 50, NULL);

	EnableManualControl(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CMonitor::IsManualControlEnabled()
{
	return m_XYSpeed.IsWindowEnabled();
}

void CMonitor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	int LightLevel = 32767 - m_LightSlider.GetPos();
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->SetLight(LightLevel);
	ReleaseMutex(*pHStageEngineMutex);
}


void CMonitor::SyncMode()
{
	SendDlgItemMessage(IDC_M_MARKMODE, BM_SETCHECK, (*pIsSeeingMarks) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_M_GRAINMODE, BM_SETCHECK, (*pIsSeeingMarks) ? BST_UNCHECKED : BST_CHECKED);
}

void CMonitor::OnMarkMode() 
{
	// TODO: Add your control notification handler code here
	*pIsSeeingMarks = true;
}

void CMonitor::OnGrainMode() 
{
	// TODO: Add your control notification handler code here
	*pIsSeeingMarks = false;
}

void CMonitor::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	char string[16];
	{
		float Pos;
		pStgEng->GetPos(0, Pos);
		Pos = floor(Pos / pC->XYRes) * pC->XYRes;
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_XPOS)->SetWindowText(string);
		pStgEng->GetPos(1, Pos);
		Pos = floor(Pos / pC->XYRes) * pC->XYRes;
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_YPOS)->SetWindowText(string);
		pStgEng->GetPos(2, Pos);
		Pos = floor(Pos / pC->ZRes) * pC->ZRes;
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_ZPOS)->SetWindowText(string);
		unsigned short light;
		pStgEng->GetLight(light);
		sprintf(string, "%d", light);
		GetDlgItem(IDC_M_LIGHTLEVEL)->SetWindowText(string);
		m_LightSlider.SetPos(32767 - light);

		StageEngine::AxisInfo::t_Target T;
		pStgEng->GetTarget(0, T);
		if (T.IsValid)
		{
			GetDlgItem(IDC_M_ISXSPEED)->SendMessage(BM_SETCHECK, T.IsSpeed ? BST_CHECKED : BST_UNCHECKED);
			if (T.IsSpeed) GetDlgItem(IDC_M_XTARGETPOS)->SetWindowText("");
			else
			{
				sprintf(string, "%.1f", T.Pos);
				GetDlgItem(IDC_M_XTARGETPOS)->SetWindowText(string);
				};
			sprintf(string, "%.1f", T.Speed);
			GetDlgItem(IDC_M_XTARGETSPEED)->SetWindowText(string);
			}
		else
		{
			GetDlgItem(IDC_M_ISXSPEED)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
			GetDlgItem(IDC_M_XTARGETPOS)->SetWindowText("");
			GetDlgItem(IDC_M_XTARGETSPEED)->SetWindowText("");
			};
		pStgEng->GetTarget(1, T);
		if (T.IsValid)
		{
			GetDlgItem(IDC_M_ISYSPEED)->SendMessage(BM_SETCHECK, T.IsSpeed ? BST_CHECKED : BST_UNCHECKED);
			if (T.IsSpeed) GetDlgItem(IDC_M_YTARGETPOS)->SetWindowText("");
			else
			{
				sprintf(string, "%.1f", T.Pos);
				GetDlgItem(IDC_M_YTARGETPOS)->SetWindowText(string);
				};
			sprintf(string, "%.1f", T.Speed);
			GetDlgItem(IDC_M_YTARGETSPEED)->SetWindowText(string);
			}
		else
		{
			GetDlgItem(IDC_M_ISYSPEED)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
			GetDlgItem(IDC_M_YTARGETPOS)->SetWindowText("");
			GetDlgItem(IDC_M_YTARGETSPEED)->SetWindowText("");
			};
		pStgEng->GetTarget(2, T);
		if (T.IsValid)
		{
			GetDlgItem(IDC_M_ISZSPEED)->SendMessage(BM_SETCHECK, T.IsSpeed ? BST_CHECKED : BST_UNCHECKED);
			if (T.IsSpeed) GetDlgItem(IDC_M_ZTARGETPOS)->SetWindowText("");
			else
			{
				sprintf(string, "%.1f", T.Pos);
				GetDlgItem(IDC_M_ZTARGETPOS)->SetWindowText(string);
				};
			sprintf(string, "%.1f", T.Speed);
			GetDlgItem(IDC_M_ZTARGETSPEED)->SetWindowText(string);
			}
		else
		{
			GetDlgItem(IDC_M_ISZSPEED)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
			GetDlgItem(IDC_M_ZTARGETPOS)->SetWindowText("");
			GetDlgItem(IDC_M_ZTARGETSPEED)->SetWindowText("");
			};

		SyncMode();
		};
	ReleaseMutex(*pHStageEngineMutex);	
}

void CMonitor::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if (nID != SC_CLOSE) CDialog::OnSysCommand(nID, lParam);	
}
