// Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Monitor.h"

#include "COMIO.h"
#include <math.h>
#include "SlOpCodes.h"

using namespace SlaveOperation;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog


CMonitor::CMonitor(HANDLE *phcom, HANDLE *phcommutex, HANDLE *phmonitormutex, void *pctx, void (*penabler)(void *, bool), CWnd* pParent /*=NULL*/)
	: CDialog(CMonitor::IDD, pParent), SpeedMultiplier(1), pHCOM(phcom), pHCOMMutex(phcommutex), pHMonitorMutex(phmonitormutex), pContext(pctx), pEnabler(penabler),
	m_XYSpeed(&SpeedMultiplier, phcom, phcommutex), m_ZSpeed(&SpeedMultiplier, phcom, phcommutex)
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
	ON_MESSAGE(UM_REFRESH, OnRefresh)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitor message handlers

void CMonitor::OnHide() 
{
	// TODO: Add your control notification handler code here
	pEnabler(pContext, false);
}

void CMonitor::OnReset() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure you want to reset the stage coordinates?", "RemoteStage Warning", MB_ICONQUESTION | MB_YESNO) == IDYES)
		if (MessageBox("Please confirm that you want to reset the stage coordinates", "RemoteStage Warning", MB_ICONASTERISK | MB_YESNO) == IDYES)
		{
			WaitForSingleObject(*pHCOMMutex, INFINITE);
			OpSWReset Temp(0);
			WriteToCom(*pHCOM, &Temp, sizeof(Temp));
			Temp.Axis = 1;
			WriteToCom(*pHCOM, &Temp, sizeof(Temp));
			Temp.Axis = 2;
			WriteToCom(*pHCOM, &Temp, sizeof(Temp));
			ReleaseMutex(*pHCOMMutex);
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
	BYTE Temp = bEnable ? SLOP_SWITCH_TO_MANUAL : SLOP_SWITCH_TO_SOFTWARE;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
}

LRESULT CMonitor::OnRefresh(WPARAM, LPARAM)
{
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	char string[16];
	{
		OpGetPos Temp(0);
		float Pos;
		WriteToCom(*pHCOM, &Temp, sizeof(Temp));
		ReadFromCom(*pHCOM, &Pos, sizeof(Pos));
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_XPOS)->SetWindowText(string);
		Temp.Axis = 1;
		WriteToCom(*pHCOM, &Temp, sizeof(Temp));
		ReadFromCom(*pHCOM, &Pos, sizeof(Pos));
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_YPOS)->SetWindowText(string);
		Temp.Axis = 2;
		WriteToCom(*pHCOM, &Temp, sizeof(Temp));
		ReadFromCom(*pHCOM, &Pos, sizeof(Pos));
		sprintf(string, "%.1f", Pos);
		GetDlgItem(IDC_M_ZPOS)->SetWindowText(string);
		};
	{
		OpGetLim Temp(0);
		BYTE retval = 1;
		WriteToCom(*pHCOM, &Temp, sizeof(Temp));
		ReadFromCom(*pHCOM, &retval, sizeof(retval));
		DrawSemaphore(IDC_M_XRED, IDC_M_XGREEN, (bool)retval);
		Temp.Axis = 1;
		WriteToCom(*pHCOM, &Temp, sizeof(Temp));
		ReadFromCom(*pHCOM, &retval, sizeof(retval));
		DrawSemaphore(IDC_M_YRED, IDC_M_YGREEN, (bool)retval);
		Temp.Axis = 2;
		WriteToCom(*pHCOM, &Temp, sizeof(Temp));
		ReadFromCom(*pHCOM, &retval, sizeof(retval));
		DrawSemaphore(IDC_M_ZRED, IDC_M_ZGREEN, (bool)retval);
		};
	RefreshProcessed = true;
	ReleaseMutex(*pHCOMMutex);	
	return 0;
}

void CMonitor::DrawSemaphore(int IdRed, int IdGreen, bool Status)
{
	CWnd *pWnd;
	CRect ClRect;
	pWnd = GetDlgItem(IdRed);
	pWnd->GetClientRect(&ClRect);
//	ClRect.DeflateRect(1, 1);
	{	
		CClientDC dc(pWnd);
		CBrush Brush(Status ? RGB(255, 0, 0) : RGB(96, 0, 0));
		dc.FillRect(&ClRect, &Brush);
		};
	pWnd = GetDlgItem(IdGreen);
	pWnd->GetClientRect(&ClRect);
//	ClRect.DeflateRect(1, 1);
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

	m_LightSlider.SetRange(0, 32767, TRUE);
	m_LightSlider.SetPos(32767);
	m_LightSlider.SetLineSize(32);
	m_LightSlider.SetPageSize(1024);
	for (int i = 2048; i < 32768L; i += 2048) m_LightSlider.SetTic(i);

	ResyncLight();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitor::ResyncLight()
{
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	BYTE Temp = SLOP_GET_LIGHT;
	WORD wretval = 0;
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReadFromCom(*pHCOM, &wretval, sizeof(wretval));
	ReleaseMutex(*pHCOMMutex);
	char string[8];
	sprintf(string, "%d", wretval);
	GetDlgItem(IDC_M_LIGHTLEVEL)->SetWindowText(string);
	m_LightSlider.SetPos(32767 - wretval);	
}



void CMonitor::ResyncLight(int LightLevel)
{
	char string[8];
	sprintf(string, "%d", LightLevel);
	GetDlgItem(IDC_M_LIGHTLEVEL)->SetWindowText(string);
	m_LightSlider.SetRange(0, 32767);
	m_LightSlider.SetPos(32767 - LightLevel);	
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
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	OpSWLight Temp(LightLevel);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
	char string[8];
	sprintf(string, "%d", LightLevel);
	GetDlgItem(IDC_M_LIGHTLEVEL)->SetWindowText(string);

}
