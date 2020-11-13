// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditConfig.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog


CEditConfig::CEditConfig(DWORD context, bool (*pazstest)(DWORD, AsyncZScanTrajectory *, float *), CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent), Context(context), pAZSTest(pazstest)
{
	//{{AFX_DATA_INIT(CEditConfig)
	//}}AFX_DATA_INIT
	C.XYManSpeedMultiplier = 0.1f;
	C.ZManSpeedMultiplier = 0.1f;
	C.XYSpeedChangeLimit = 300000.f;
	C.ZSpeedChangeLimit = 300000.f;
	C.XYAccel = 1000000.f;
	C.ZAccel = 1000000.f;
	C.XYMaxSpeed = 1000000;
	C.ZMaxSpeed = 1000000;
	C.XYManMaxSpeed = 100000;
	C.ZManMaxSpeed = 100000;
	C.ConstSpeedAccel = 1000000;
	C.AccelFactor = 10;
	C.ZParkDisplacement = 30000.0f;
	C.ZBaseThickness = 210.0f;
	C.InteractiveHome = 1;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_ACCELFACT, C.AccelFactor);
	DDV_MinMaxUInt(pDX, C.AccelFactor, 1, 1000);
	DDX_Text(pDX, IDC_EC_CONSTSPEEDACCEL, C.ConstSpeedAccel);
	DDV_MinMaxFloat(pDX, C.ConstSpeedAccel, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_ACCEL, C.XYAccel);
	DDV_MinMaxFloat(pDX, C.XYAccel, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_MANMAXSPEED, C.XYManMaxSpeed);
	DDV_MinMaxFloat(pDX, C.XYManMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_MANMAXSPEEDCHANGE, C.XYSpeedChangeLimit);
	DDV_MinMaxFloat(pDX, C.XYSpeedChangeLimit, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_MANSPEEDMULT, C.XYManSpeedMultiplier);
	DDV_MinMaxFloat(pDX, C.XYManSpeedMultiplier, 1.e-003f, 1.e+009f);
	DDX_Text(pDX, IDC_EC_XY_MAXSPEED, C.XYMaxSpeed);
	DDV_MinMaxFloat(pDX, C.XYMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_ACCEL, C.ZAccel);
	DDV_MinMaxFloat(pDX, C.ZAccel, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_MANMAXSPEED, C.ZManMaxSpeed);
	DDV_MinMaxFloat(pDX, C.ZManMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_MANMAXSPEEDCHANGE, C.ZSpeedChangeLimit);
	DDV_MinMaxFloat(pDX, C.ZSpeedChangeLimit, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_MANSPEEDMULT, C.ZManSpeedMultiplier);
	DDV_MinMaxFloat(pDX, C.ZManSpeedMultiplier, 1.e-003f, 1.e+009f);
	DDX_Text(pDX, IDC_EC_Z_MAXSPEED, C.ZMaxSpeed);
	DDV_MinMaxFloat(pDX, C.ZMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_PARKPOS, C.ZParkDisplacement);
	DDV_MinMaxFloat(pDX, C.ZParkDisplacement, 0.0f, 100000.0f);
	DDX_Text(pDX, IDC_EC_Z_BASETHICKNESS, C.ZBaseThickness);
	DDV_MinMaxFloat(pDX, C.ZBaseThickness, 100.0f, 300.0f);
	DDX_Check(pDX, IDC_INTERACTIVEHOME, C.InteractiveHome);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_TEST, OnTest)
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

void CEditConfig::OnTest() 
{
	// TODO: Add your control notification handler code here
	CTestDlg MyDlg(Context, pAZSTest, this);
	MyDlg.DoModal();
}
