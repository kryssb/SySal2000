// SelectObject.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "SelectObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectObject dialog


CSelectObject::CSelectObject(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectObject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectObject)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDoc = 0;
}


void CSelectObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectObject)
	DDX_Control(pDX, IDC_SO_LIST, m_ObjectList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectObject, CDialog)
	//{{AFX_MSG_MAP(CSelectObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectObject message handlers

void CSelectObject::OnOK() 
{
	// TODO: Add extra validation here
	int index = m_ObjectList.GetCurSel();
	if (index < 0 || index >= m_ObjectList.GetCount()) CDialog::OnCancel();
	m_ObjectList.GetText(index, m_Result);
	CDialog::OnOK();
}

BOOL CSelectObject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_pDoc)
	{
		POSITION POS = m_pDoc->Layout.GetHeadPosition();

		while (POS)
		{
			CPersistentObject &rObj = m_pDoc->Layout.GetNext(POS);
			m_ObjectList.AddString(rObj.Name);
			};
		};
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
