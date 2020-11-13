// MapInitString.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MapInitString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CMapInitString dialog


CMapInitString::CMapInitString(CWnd* pParent /*=NULL*/)
	: CDialog(CMapInitString::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapInitString)
	m_InitString = _T("");
	//}}AFX_DATA_INIT
}


void CMapInitString::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapInitString)
	DDX_Text(pDX, IDC_IM_INITSTRING, m_InitString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapInitString, CDialog)
	//{{AFX_MSG_MAP(CMapInitString)
	ON_BN_CLICKED(IDC_IM_SELPATH, OnSelPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapInitString message handlers

void CMapInitString::OnSelPath() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, NULL, m_InitString, OFN_FILEMUSTEXIST | OFN_EXPLORER, "Mark Map Files (*.map)|*.map|All Files (*.*)|*.*|||", this);	
	if (MyDlg.DoModal() == IDOK)
	{
		m_InitString = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}
