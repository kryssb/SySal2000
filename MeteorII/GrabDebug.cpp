// GrabDebug.cpp : implementation file
//

#include "stdafx.h"
#include "meteorii.h"
#include "GrabDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrabDebug dialog


CGrabDebug::CGrabDebug(CWnd* pParent /*=NULL*/)
	: CDialog(CGrabDebug::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrabDebug)
	m_Frame = 0;
	m_Backlog = 0;
	//}}AFX_DATA_INIT
}


void CGrabDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrabDebug)
	DDX_Text(pDX, IDC_GD_FRAME, m_Frame);
	DDX_Text(pDX, IDC_GD_BACKLOG, m_Backlog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrabDebug, CDialog)
	//{{AFX_MSG_MAP(CGrabDebug)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrabDebug message handlers
