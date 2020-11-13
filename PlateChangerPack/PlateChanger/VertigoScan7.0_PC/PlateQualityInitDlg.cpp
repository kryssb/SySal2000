// PlateQualityInitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlateQualityInitDlg.h"


// CPlateQualityInitDlg dialog

IMPLEMENT_DYNAMIC(CPlateQualityInitDlg, CDialog)

CPlateQualityInitDlg::CPlateQualityInitDlg(int timetowait, CWnd* pParent /*=NULL*/)
	: CDialog(CPlateQualityInitDlg::IDD, pParent)
{
	EndTime = GetTickCount() + timetowait * 1000;
}

CPlateQualityInitDlg::~CPlateQualityInitDlg()
{
}

void CPlateQualityInitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPlateQualityInitDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPlateQualityInitDlg message handlers

void CPlateQualityInitDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int timetorun = EndTime - GetTickCount();
	if (timetorun <= 0)
	{
		timetorun = 0;
		EndDialog(IDCANCEL);
	}
	char timestr[32];
	wsprintf(timestr, "%02d:%02d", timetorun / 60000, ((timetorun / 1000) % 60));
	GetDlgItem(IDC_QI_TIME)->SetWindowText(timestr);
	CDialog::OnTimer(nIDEvent);
}

BOOL CPlateQualityInitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetTimer(876, 1000, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPlateQualityInitDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(876);
	CDialog::OnClose();
}
