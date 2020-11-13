// ObjName.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "ObjName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjName dialog


CObjName::CObjName(CWnd* pParent /*=NULL*/)
	: CDialog(CObjName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjName)
	m_ObjName = _T("");
	//}}AFX_DATA_INIT
}


void CObjName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjName)
	DDX_Text(pDX, IDC_ON_OBJNAME, m_ObjName);
	DDV_MaxChars(pDX, m_ObjName, 63);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjName, CDialog)
	//{{AFX_MSG_MAP(CObjName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjName message handlers
