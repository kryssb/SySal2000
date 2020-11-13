// ObjInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "ObjInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjInfo dialog


CObjInfo::CObjInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CObjInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjInfo)
	m_Class = _T("");
	m_CLSID = _T("");
	m_DLLPath = _T("");
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CObjInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjInfo)
	DDX_Text(pDX, IDC_OI_CLASS, m_Class);
	DDX_Text(pDX, IDC_OI_CLSID, m_CLSID);
	DDX_Text(pDX, IDC_OI_DLLPATH, m_DLLPath);
	DDX_Text(pDX, IDC_OI_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjInfo, CDialog)
	//{{AFX_MSG_MAP(CObjInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjInfo message handlers
