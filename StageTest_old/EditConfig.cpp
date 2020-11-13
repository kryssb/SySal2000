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
// SYSAL_OBJECT_PROPERTY_INIT_BEGIN

	C.XStep = 300;
	C.YStep = 300;
	C.ZStep = 50;
	C.XAcc = 10000;
	C.YAcc = 10000;
	C.ZAcc = 10000;
	C.XSpeed = 10000;
	C.YSpeed = 10000;
	C.ZSpeed = 1000;
	C.XLongRange = 100000;
	C.YLongRange = 100000;
	C.ZLongRange = 10000;
	C.XStopTol = 5;
	C.YStopTol = 5;
	C.ZStopTol = 2;
	C.XDampTol = 0.3;
	C.YDampTol = 0.3;
	C.ZDampTol = 0.3;
	C.UseStop = true;

// SYSAL_OBJECT_PROPERTY_INIT_END
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP

// SYSAL_OBJECT_PROPERTY_EXCHANGE_BEGIN

	DDX_Text(pDX, IDC_EC_XSTEP, C.XStep);
	DDV_MinMaxFloat(pDX, C.XStep, 10, 2000);
	DDX_Text(pDX, IDC_EC_YSTEP, C.YStep);
	DDV_MinMaxFloat(pDX, C.YStep, 10, 2000);
	DDX_Text(pDX, IDC_EC_ZSTEP, C.ZStep);
	DDV_MinMaxFloat(pDX, C.ZStep, 5, 500);
	DDX_Text(pDX, IDC_EC_XACC, C.XAcc);
	DDV_MinMaxFloat(pDX, C.XAcc, 100, 1e+009);
	DDX_Text(pDX, IDC_EC_YACC, C.YAcc);
	DDV_MinMaxFloat(pDX, C.YAcc, 100, 1e+009);
	DDX_Text(pDX, IDC_EC_ZACC, C.ZAcc);
	DDV_MinMaxFloat(pDX, C.ZAcc, 100, 1e+009);
	DDX_Text(pDX, IDC_EC_XSPEED, C.XSpeed);
	DDV_MinMaxFloat(pDX, C.XSpeed, 100, 100000);
	DDX_Text(pDX, IDC_EC_YSPEED, C.YSpeed);
	DDV_MinMaxFloat(pDX, C.YSpeed, 100, 100000);
	DDX_Text(pDX, IDC_EC_ZSPEED, C.ZSpeed);
	DDV_MinMaxFloat(pDX, C.ZSpeed, 100, 100000);
	DDX_Text(pDX, IDC_EC_XLONGRANGE, C.XLongRange);
	DDV_MinMaxFloat(pDX, C.XLongRange, 100, 1e+007);
	DDX_Text(pDX, IDC_EC_YLONGRANGE, C.YLongRange);
	DDV_MinMaxFloat(pDX, C.YLongRange, 100, 1e+007);
	DDX_Text(pDX, IDC_EC_ZLONGRANGE, C.ZLongRange);
	DDV_MinMaxFloat(pDX, C.ZLongRange, 100, 100000);
	DDX_Text(pDX, IDC_EC_XSTOPTOL, C.XStopTol);
	DDV_MinMaxFloat(pDX, C.XStopTol, 0, 100);
	DDX_Text(pDX, IDC_EC_YSTOPTOL, C.YStopTol);
	DDV_MinMaxFloat(pDX, C.YStopTol, 0, 100);
	DDX_Text(pDX, IDC_EC_ZSTOPTOL, C.ZStopTol);
	DDV_MinMaxFloat(pDX, C.ZStopTol, 0, 30);
	DDX_Text(pDX, IDC_EC_XDAMPTOL, C.XDampTol);
	DDV_MinMaxFloat(pDX, C.XDampTol, 0, 2);
	DDX_Text(pDX, IDC_EC_YDAMPTOL, C.YDampTol);
	DDV_MinMaxFloat(pDX, C.YDampTol, 0, 2);
	DDX_Text(pDX, IDC_EC_ZDAMPTOL, C.ZDampTol);
	DDV_MinMaxFloat(pDX, C.ZDampTol, 0, 2);
	DDX_Check(pDX, IDC_EC_USESTOP, C.UseStop);

// SYSAL_OBJECT_PROPERTY_EXCHANGE_END
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

