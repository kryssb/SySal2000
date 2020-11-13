// RemoteScan.cpp : implementation file
//

#include "stdafx.h"
#include "VertigoScan4.h"
#include "RemoteScan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteScan dialog


CRemoteScan::CRemoteScan(IScanServer *iss, HANDLE hStatusMutex, bool *pshouldstop, CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteScan::IDD, pParent), iSS(iss), PollTimer(0), HStatusMutex(hStatusMutex), pShouldStop(pshouldstop)
{
	//{{AFX_DATA_INIT(CRemoteScan)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	M.ZS.Id.Part[0] = M.ZS.Id.Part[1] = M.ZS.Id.Part[2] = M.ZS.Id.Part[3] = 0;
	M.ZS.MinX = M.ZS.MinY = M.ZS.MaxX = M.ZS.MaxY = 0;
	M.ZS.OutName[0] = 0;
	M.ZS.OpCode = SCANSRV_NULL;
	M.ZS.Size = sizeof(M.ZS);
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
	
	// TODO: Add extra initialization here
	PollTimer = SetTimer(333, 50, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRemoteScan::OnDestroy() 
{
	KillTimer(PollTimer);
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CRemoteScan::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	M.M.Size = sizeof(M);
	if (iSS->Receive((BYTE *)&M) != E_NOTIMPL)
	{
		switch (M.M.OpCode)
		{
			case SCANSRV_SET_PARAMETER:
			case SCANSRV_SCAN_ZONE_START:
			case SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT:
			case SCANSRV_LOAD_PLATE:
			case SCANSRV_UNLOAD_PLATE:		EndDialog(IDOK);
											break;

			default:						M.M.OpCode = SCANSRV_NOTACKNOWLEDGED;
											M.M.Size = sizeof(M.M);
											iSS->Send((BYTE *)&M);			
			}
		}
	WaitForSingleObject(HStatusMutex, INFINITE);
	if (*pShouldStop) 
	{
		ReleaseMutex(HStatusMutex);
		EndDialog(IDCANCEL);
		}
	else ReleaseMutex(HStatusMutex);
	CDialog::OnTimer(nIDEvent);
}
