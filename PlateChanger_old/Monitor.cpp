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


CMonitor::CMonitor(ConfigData *pc, HANDLE *phmonitormutex, HANDLE *phrun, void *pctx, void (*penabler)(void *, bool), CWnd* pParent /*=NULL*/)
	: CDialog(CMonitor::IDD, pParent), pHMonitorMutex(phmonitormutex), pHRun(phrun), pContext(pctx), pEnabler(penabler), SpeedMultiplier(1)
{
	//{{AFX_DATA_INIT(CMonitor)
	//}}AFX_DATA_INIT
}


void CMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitor)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitor, CDialog)
	//{{AFX_MSG_MAP(CMonitor)
	ON_BN_CLICKED(IDC_M_HIDE, OnHide)
	ON_BN_CLICKED(IDC_M_RESET, OnReset)
	ON_BN_CLICKED(IDC_M_TOGGLEMANUAL, OnToggleManual)
	ON_BN_CLICKED(IDC_M_1, OnSpeedX1)
	ON_BN_CLICKED(IDC_M_10, OnSpeedX10)
	ON_BN_CLICKED(IDC_M_100, OnSpeedX100)
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
	if (MessageBox("Are you sure you want to reset the plate changer coordinates?", "Plate Changer Warning", MB_ICONQUESTION | MB_YESNO) == IDYES)
		if (MessageBox("Please confirm that you want to reset the plate changer coordinates", "Plate Changer Warning", MB_ICONASTERISK | MB_YESNO) == IDYES)
		{
			WaitForSingleObject(*pHMonitorMutex, INFINITE);
			// SAMUEL: Reset the plate changer coordinates
			ReleaseMutex(*pHMonitorMutex);
			};
}

void CMonitor::OnToggleManual() 
{
	// TODO: Add your control notification handler code here
	//SAMUEL: ??? EnableManualControl(!m_XYSpeed.IsWindowEnabled());
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

void CMonitor::OnSpeedX100() 
{
	// TODO: Add your control notification handler code here
	SpeedMultiplier = 100;
}

void CMonitor::EnableManualControl(bool bEnable)
{
	(*pEnabler)(pContext, bEnable);
	// SAMUEL: change the monitor dialog for manual control / software control
}

LRESULT CMonitor::OnRefresh(WPARAM, LPARAM)
{
	char string[16];
	{
		int Pos = 0;
		long retval;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		// SAMUEL: Read the Theta position into the "Pos" variable
		ReleaseMutex(*pHMonitorMutex);
		sprintf(string, "%d", Pos);
		GetDlgItem(IDC_M_THPOS)->SetWindowText(string);
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		// SAMUEL: Read the Z position into the "Pos" variable
		ReleaseMutex(*pHMonitorMutex);
		sprintf(string, "%d", Pos);
		GetDlgItem(IDC_M_ZPOS)->SetWindowText(string);
		};
	{
		unsigned char fwdStatus, revStatus;
		DWORD a;
		a = 0;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		// SAMUEL: read the limit switch for Theta
		ReleaseMutex(*pHMonitorMutex);
		/* SAMUEL: change the value of a... */
//		if (revStatus & 0x02) a |= pC->InvertX ? 2 : 1;
//		if (fwdStatus & 0x02) a |= pC->InvertX ? 1 : 2;
		DrawSemaphore(IDC_M_THRED, IDC_M_THGREEN, (bool)a);
		a = 0;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		// SAMUEL: read the limit switch for Z
		ReleaseMutex(*pHMonitorMutex);
		/* SAMUEL: change the value of a... */
//		if (revStatus & 0x04) a |= pC->InvertY ? 2 : 1;
//		if (fwdStatus & 0x04) a |= pC->InvertY ? 1 : 2;
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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CMonitor::IsManualControlEnabled()
{
	//SAMUEL: ???? return m_XYSpeed.IsWindowEnabled();
	return false;
}

void CMonitor::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if (nID != SC_CLOSE) CDialog::OnSysCommand(nID, lParam);	
}
