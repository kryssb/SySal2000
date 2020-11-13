// Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Monitor.h"

#include <math.h>
#include "Flexmotn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog


CMonitor::CMonitor(float *pxmanspeed, float *pymanspeed, float *pzmanspeed, WORD *plightlevel, ConfigData *pc, 
	HANDLE *phmonitormutex, HANDLE *phrun, void *pctx, void (*penabler)(void *, bool), CWnd* pParent /*=NULL*/)
	: CDialog(CMonitor::IDD, pParent), SpeedMultiplier(1), pHMonitorMutex(phmonitormutex), pHRun(phrun), pContext(pctx), pEnabler(penabler),
	m_XYSpeed(phmonitormutex, &SpeedMultiplier, pxmanspeed, pymanspeed, pc), 
	m_ZSpeed(phmonitormutex, &SpeedMultiplier, pzmanspeed, pc), pLightLevel(plightlevel), pC(pc)
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
	ON_WM_DRAWITEM()
	ON_MESSAGE(UM_REFRESH, OnRefresh)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitor message handlers

void CMonitor::OnHide() 
{
	// TODO: Add your control notification handler code here
	ResetEvent(*pHRun);
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
			WaitForSingleObject(*pHMonitorMutex, INFINITE);
			flex_reset_pos(pC->BoardId, 1, 0, 0, 0xFF);
			flex_reset_pos(pC->BoardId, 2, 0, 0, 0xFF);
			flex_reset_pos(pC->BoardId, 3, 0, 0, 0xFF);
			ReleaseMutex(*pHMonitorMutex);
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
	(*pEnabler)(pContext, bEnable);
	m_XYSpeed.EnableWindow(bEnable);
	m_ZSpeed.EnableWindow(bEnable);
	m_LightSlider.EnableWindow(bEnable);
	m_XYSpeed.RedrawWindow();
	m_ZSpeed.RedrawWindow();
	m_LightSlider.RedrawWindow();
}

LRESULT CMonitor::OnRefresh(WPARAM, LPARAM)
{
	char string[16];
	{
		float Pos;
		long retval;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		flex_read_pos_rtn(pC->BoardId, 1, &retval);
		if (pC->InvertX) retval = -retval;
		ReleaseMutex(*pHMonitorMutex);
		Pos = retval * (pC->XYEncoderToMicrons * pC->XYLinesRev) / pC->XYStepsRev;
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_XPOS)->SetWindowText(string);
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		flex_read_pos_rtn(pC->BoardId, 2, &retval);
		if (pC->InvertY) retval = -retval;
		ReleaseMutex(*pHMonitorMutex);
		Pos = retval * (pC->XYEncoderToMicrons * pC->XYLinesRev) / pC->XYStepsRev;
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_YPOS)->SetWindowText(string);
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		flex_read_pos_rtn(pC->BoardId, 3, &retval);
		if (pC->InvertZ) retval = -retval;
		ReleaseMutex(*pHMonitorMutex);
		Pos = retval * (pC->ZEncoderToMicrons * pC->ZLinesRev) / pC->ZStepsRev;
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_ZPOS)->SetWindowText(string);
		};
	{
		unsigned char fwdStatus, revStatus;
		DWORD a;
		a = 0;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		flex_read_limit_status_rtn(pC->BoardId, NIMC_LIMIT_INPUTS, &fwdStatus, &revStatus);
		ReleaseMutex(*pHMonitorMutex);
		if (revStatus & 0x02) a |= pC->InvertX ? 2 : 1;
		if (fwdStatus & 0x02) a |= pC->InvertX ? 1 : 2;
		DrawSemaphore(IDC_M_XRED, IDC_M_XGREEN, (bool)a);
		a = 0;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		flex_read_limit_status_rtn(pC->BoardId, NIMC_LIMIT_INPUTS, &fwdStatus, &revStatus);
		ReleaseMutex(*pHMonitorMutex);
		if (revStatus & 0x04) a |= pC->InvertY ? 2 : 1;
		if (fwdStatus & 0x04) a |= pC->InvertY ? 1 : 2;
		DrawSemaphore(IDC_M_YRED, IDC_M_YGREEN, (bool)a);
		a = 0;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		flex_read_limit_status_rtn(pC->BoardId, NIMC_LIMIT_INPUTS, &fwdStatus, &revStatus);
		ReleaseMutex(*pHMonitorMutex);
		if (revStatus & 0x08) a |= pC->InvertZ ? 2 : 1;
		if (fwdStatus & 0x08) a |= pC->InvertZ ? 1 : 2;
		DrawSemaphore(IDC_M_ZRED, IDC_M_ZGREEN, (bool)a);
		};
	return 0;
}

void CMonitor::DrawSemaphore(int IdRed, int IdGreen, bool Status)
{
	CWnd *pWnd;
	CRect ClRect;
	pWnd = GetDlgItem(IdRed);
	pWnd->GetClientRect(&ClRect);
	{	
		CClientDC dc(pWnd);
		CBrush Brush(Status ? RGB(255, 0, 0) : RGB(96, 0, 0));
		dc.FillRect(&ClRect, &Brush);
		};
	pWnd = GetDlgItem(IdGreen);
	pWnd->GetClientRect(&ClRect);
	{	
		CClientDC dc(pWnd);
		CBrush Brush(Status ? RGB(0, 96, 0) : RGB(0, 255, 0));
		dc.FillRect(&ClRect, &Brush);
		};
}

BOOL CMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_LightSlider.SetRange(0, pC->LightLimit, TRUE);
	m_LightSlider.SetPos(pC->LightLimit);
	m_LightSlider.SetLineSize(32);
	m_LightSlider.SetPageSize(1024);
	for (int i = 2048; i < pC->LightLimit; i += 2048) m_LightSlider.SetTic(i);

	ResyncLight();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitor::ResyncLight()
{
	char string[8];
	sprintf(string, "%d", *pLightLevel);
	GetDlgItem(IDC_M_LIGHTLEVEL)->SetWindowText(string);
	m_LightSlider.SetPos(pC->LightLimit - *pLightLevel);	
}



void CMonitor::ResyncLight(int LightLevel)
{
	char string[8];
	sprintf(string, "%d", LightLevel);
	GetDlgItem(IDC_M_LIGHTLEVEL)->SetWindowText(string);
	m_LightSlider.SetRange(0, pC->LightLimit);
	m_LightSlider.SetPos(pC->LightLimit - LightLevel);	
}

bool CMonitor::IsManualControlEnabled()
{
	return m_XYSpeed.IsWindowEnabled();
}

void CMonitor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	*pLightLevel = pC->LightLimit - m_LightSlider.GetPos();
	WaitForSingleObject(*pHMonitorMutex, INFINITE);
	flex_load_dac(pC->BoardId, 0x34, *pLightLevel, 0xFF);
	ReleaseMutex(*pHMonitorMutex);
	char string[8];
	sprintf(string, "%d", *pLightLevel);
	GetDlgItem(IDC_M_LIGHTLEVEL)->SetWindowText(string);

}

void CMonitor::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMonitor::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if (nID != SC_CLOSE) CDialog::OnSysCommand(nID, lParam);	
}
