// EditField.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditField dialog


CEditField::CEditField(CWnd* pParent /*=NULL*/)
	: CDialog(CEditField::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditField)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CEditField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditField)
	DDX_Control(pDX, IDC_EF_CTYPE, m_TypeCombo);
	DDX_Text(pDX, IDC_EF_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditField, CDialog)
	//{{AFX_MSG_MAP(CEditField)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditField message handlers

BOOL CEditField::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TypeCombo.SetCurSel(m_Type);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditField::OnOK() 
{
	// TODO: Add extra validation here
	m_Type = m_TypeCombo.GetCurSel();
	CDialog::OnOK();
}
