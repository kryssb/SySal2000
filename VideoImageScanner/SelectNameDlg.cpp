// SelectNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "videoimagescanner.h"
#include "SelectNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectNameDlg dialog


CSelectNameDlg::CSelectNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectNameDlg)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CSelectNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectNameDlg)
	DDX_Text(pDX, IDC_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectNameDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectNameDlg message handlers
