// Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "time.h"
#include "resource.h"
#include "Monitor.h"
#include "../Common/Stage3.h"
//#include "PlateChangerClass.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog


CMonitor::CMonitor(VPlateChanger *pv, CWnd* pParent /*=NULL*/)
	: CDialog(CMonitor::IDD, pParent), pV(pv)
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
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MD_REFRESH, &CMonitor::OnBnClickedMdRefresh)
	ON_BN_CLICKED(IDC_MD_GOTOLOADPOSITION, &CMonitor::OnBnClickedMdGotoloadposition)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitor message handlers

void CMonitor::EnableManualControl(bool bEnable)
{
	
}

bool CMonitor::IsManualControlEnabled()
{
	// ??? dovrebbe sapere se è MANUALE o no...
	return false;
}

void CMonitor::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if (nID != SC_CLOSE) CDialog::OnSysCommand(nID, lParam);	
}


void CMonitor::OnBnClickedMdRefresh()
{
	// TODO: Add your control notification handler code here
	int ret = pV->GetStatusBits();
	SendDlgItemMessage(IDC_MD_ALARM, BM_SETCHECK, (ret & 0x1) ? BST_CHECKED : BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_MD_OUT_VOLUME, BM_SETCHECK, (ret & 0x2) ? BST_CHECKED : BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_MD_PLATE_LOCK, BM_SETCHECK, (ret & 0x4) ? BST_CHECKED : BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_MD_PLATE_RELEASED, BM_SETCHECK, (ret & 0x8) ? BST_CHECKED : BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_MD_VACUUM1, BM_SETCHECK, (ret & 0x10) ? BST_CHECKED : BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_MD_VACUUM2, BM_SETCHECK, (ret & 0x20) ? BST_CHECKED : BST_UNCHECKED, 0);
}

void CMonitor::OnBnClickedMdGotoloadposition()
{
	// TODO: Add your control notification handler code here
	if (pV->GoToLoadingPosition() == false)
		MessageBox("Failed to reach loading position!", "Plate Changer stage driving error!", MB_ICONERROR);
}
