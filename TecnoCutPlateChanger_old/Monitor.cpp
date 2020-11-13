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

