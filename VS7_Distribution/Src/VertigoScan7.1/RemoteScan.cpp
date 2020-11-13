// RemoteScan.cpp : implementation file
//

#include "stdafx.h"
#include "VertigoScan6.h"
#include "RemoteScan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteScan dialog


CRemoteScan::CRemoteScan(SySal::DAQSystem::VSScanServer ^ss, bool *pshouldstop, CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteScan::IDD, pParent), SS(ss), PollTimer(0), pShouldStop(pshouldstop)
{
	//{{AFX_DATA_INIT(CRemoteScan)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRemoteScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteScan)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteScan, CDialog)
	//{{AFX_MSG_MAP(CRemoteScan)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteScan message handlers

BOOL CRemoteScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PollTimer = SetTimer(333, 50, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRemoteScan::OnDestroy() 
{
	KillTimer(PollTimer);
	CDialog::OnDestroy();
}

void CRemoteScan::OnTimer(UINT nIDEvent) 
{
	if (SS->HasRequest) EndDialog(IDOK);
	if (*pShouldStop) EndDialog(IDCANCEL);
	CDialog::OnTimer(nIDEvent);
	return;
}
