// TitleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "TitleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleDlg dialog


CTitleDlg::CTitleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTitleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTitleDlg)
	m_TitleText = _T("");
	//}}AFX_DATA_INIT
}


void CTitleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTitleDlg)
	DDX_Text(pDX, IDC_PT_TITLETEXT, m_TitleText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTitleDlg, CDialog)
	//{{AFX_MSG_MAP(CTitleDlg)
	ON_BN_CLICKED(IDC_PT_SETFONT, OnSetfont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitleDlg message handlers

void CTitleDlg::OnSetfont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog MyDlg(&m_LogFont, CF_EFFECTS | CF_SCREENFONTS, NULL, this);
	MyDlg.DoModal();
}
