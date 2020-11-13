// EditGridOptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditGridOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditGridOptions dialog


CEditGridOptions::CEditGridOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CEditGridOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditGridOptions)
	m_XStep = 0;
	m_YStep = 0;
	//}}AFX_DATA_INIT
}


void CEditGridOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditGridOptions)
	DDX_Text(pDX, IDC_EG_XSTEP, m_XStep);
	DDV_MinMaxUInt(pDX, m_XStep, 10, 1000);
	DDX_Text(pDX, IDC_EG_YSTEP, m_YStep);
	DDV_MinMaxUInt(pDX, m_YStep, 10, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditGridOptions, CDialog)
	//{{AFX_MSG_MAP(CEditGridOptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditGridOptions message handlers
