// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LyonTracker.h"
#include "EditConfig.h"
#include "Config2.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog


CEditConfig::CEditConfig(CLyonTrackerClass *ptk, CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent), pTk(ptk)
{
	//{{AFX_DATA_INIT(CEditConfig)
	//}}AFX_DATA_INIT
	C.Sample_Float = 0.0f;
	C.Sample_Int = 5;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_SAMPLEFLOAT, C.Sample_Float);
	DDV_MinMaxFloat(pDX, C.Sample_Float, -1.5f, 1.5f);
	DDX_Text(pDX, IDC_EC_SAMPLEINT, C.Sample_Int);
	DDV_MinMaxInt(pDX, C.Sample_Int, 1, 100);

}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers


BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::OnHelp() 
{
	// TODO: Add your control notification handler code here
	HtmlHelp(this->m_hWnd, CLyonTrackerClass::pHelpPath, HH_DISPLAY_TOPIC, (DWORD)"HelpConfig.htm");	
}
