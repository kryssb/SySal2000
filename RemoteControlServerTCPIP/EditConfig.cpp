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
	C.ImageQuality = 7000;
	C.Port = 4555;
	C.TimeOut = 10000;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_IMAGEQUALITY, C.ImageQuality);
	DDV_MinMaxUInt(pDX, C.ImageQuality, 0, 10000);
	DDX_Text(pDX, IDC_EC_PORT, C.Port);
	DDV_MinMaxUInt(pDX, C.Port, 1, 65535);
	DDX_Text(pDX, IDC_EC_TIMEOUT, C.TimeOut);
	DDV_MinMaxUInt(pDX, C.TimeOut, 100, 10000000);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers
