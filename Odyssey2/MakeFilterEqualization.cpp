// MakeFilterEqualization.cpp : implementation file
//

#include "stdafx.h"
#include "odyssey2.h"
#include "MakeFilterEqualization.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMakeFilterEqualization dialog


CMakeFilterEqualization::CMakeFilterEqualization(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeFilterEqualization::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeFilterEqualization)
	m_CompFact = 0.0;
	m_XCenter = 0;
	m_YCenter = 0;
	//}}AFX_DATA_INIT
}


void CMakeFilterEqualization::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeFilterEqualization)
	DDX_Text(pDX, IDC_FE_COMPFACT, m_CompFact);
	DDX_Text(pDX, IDC_FE_XCENTER, m_XCenter);
	DDX_Text(pDX, IDC_FE_YCENTER, m_YCenter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMakeFilterEqualization, CDialog)
	//{{AFX_MSG_MAP(CMakeFilterEqualization)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeFilterEqualization message handlers
