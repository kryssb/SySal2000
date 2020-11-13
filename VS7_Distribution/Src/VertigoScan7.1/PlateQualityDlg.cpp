// PlateQualityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlateQualityDlg.h"


// CPlateQualityDlg dialog

IMPLEMENT_DYNAMIC(CPlateQualityDlg, CDialog)

CPlateQualityDlg::CPlateQualityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlateQualityDlg::IDD, pParent)
{

}

CPlateQualityDlg::~CPlateQualityDlg()
{
}

void CPlateQualityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPlateQualityDlg, CDialog)
END_MESSAGE_MAP()


// CPlateQualityDlg message handlers

void CPlateQualityDlg::SetResults(float topfog, float bottomfog, float topthickness, float bottomthickness, float basethickness)
{	
	sprintf(TempStr, "Top Fog (grains/1000 \xB5m\xB3): %.1f\r\n"
		"Bottom Fog (grains/1000 \xB5m\xB3): %.1f\r\n"
		"Top Thickness (\xB5m): %.1f\r\n"
		"Bottom Thickness (\xB5m): %.1f\r\n"
		"Base Thickness (\xB5m): %.1f",
		topfog, bottomfog, topthickness, bottomthickness, basethickness);	
}

BOOL CPlateQualityDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	SendDlgItemMessage(IDC_PQ_TEXT, WM_SETTEXT, 0, (LPARAM)(void *)TempStr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
