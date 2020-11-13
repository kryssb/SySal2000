// RawSpecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "RawSpecDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRawSpecDlg dialog


CRawSpecDlg::CRawSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRawSpecDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRawSpecDlg)
	m_Height = 0;
	m_Width = 0;
	//}}AFX_DATA_INIT
}


void CRawSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRawSpecDlg)
	DDX_Text(pDX, IDC_RS_HEIGHT, m_Height);
	DDV_MinMaxUInt(pDX, m_Height, 1, 2048);
	DDX_Text(pDX, IDC_RS_WIDTH, m_Width);
	DDV_MinMaxUInt(pDX, m_Width, 1, 2048);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRawSpecDlg, CDialog)
	//{{AFX_MSG_MAP(CRawSpecDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRawSpecDlg message handlers
