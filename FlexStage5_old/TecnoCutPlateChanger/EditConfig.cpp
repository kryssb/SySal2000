// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog


CEditConfig::CEditConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditConfig)	
	//}}AFX_DATA_INIT
	C.CHANGEME = 0;
	C.CHANGEME2 = 0;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_CHANGEME, C.CHANGEME);
	DDV_MinMaxInt(pDX, C.CHANGEME, 1, 8);
	DDX_Text(pDX, IDC_EC_CHANGEME2, C.CHANGEME2);
	DDV_MinMaxFloat(pDX, C.CHANGEME2, 0.1, 0.8);
	}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

