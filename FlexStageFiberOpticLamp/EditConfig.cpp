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
	C.BoardId = 1;
	C.XYStepsRev = 4;
	C.ZStepsRev = 4;
	C.XYLinesRev = 20;
	C.ZLinesRev = 20;
	C.XYEncoderToMicrons = 0.5f;
	C.ZEncoderToMicrons = 0.5f;
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
	C.LimPol = 0;
	C.CtlModeIsCWCCW = 1;
	C.InvertX = C.InvertY = C.InvertZ = FALSE;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_ACCELFACT, C.AccelFactor);
	DDV_MinMaxUInt(pDX, C.AccelFactor, 1, 1000);
	DDX_Text(pDX, IDC_EC_BOARDID, C.BoardId);
	DDV_MinMaxUInt(pDX, C.BoardId, 1, 16);
	DDX_Text(pDX, IDC_EC_CONSTSPEEDACCEL, C.ConstSpeedAccel);
	DDV_MinMaxFloat(pDX, C.ConstSpeedAccel, 1.f, 1.e+012f);
	DDX_Check(pDX, IDC_EC_INVLIMPOL, C.LimPol);
	DDX_Text(pDX, IDC_EC_XY_ACCEL, C.XYAccel);
	DDV_MinMaxFloat(pDX, C.XYAccel, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_ENC2MICRON, C.XYEncoderToMicrons);
	DDV_MinMaxFloat(pDX, C.XYEncoderToMicrons, 1.e-003f, 1000.f);
	DDX_Text(pDX, IDC_EC_XY_LINESREV, C.XYLinesRev);
	DDV_MinMaxUInt(pDX, C.XYLinesRev, 1, 100000);
	DDX_Text(pDX, IDC_EC_XY_MANMAXSPEED, C.XYManMaxSpeed);
	DDV_MinMaxFloat(pDX, C.XYManMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_MANMAXSPEEDCHANGE, C.XYSpeedChangeLimit);
	DDV_MinMaxFloat(pDX, C.XYSpeedChangeLimit, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_MANSPEEDMULT, C.XYManSpeedMultiplier);
	DDV_MinMaxFloat(pDX, C.XYManSpeedMultiplier, 1.e-003f, 1.e+009f);
	DDX_Text(pDX, IDC_EC_XY_MAXSPEED, C.XYMaxSpeed);
	DDV_MinMaxFloat(pDX, C.XYMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_XY_STEPSREV, C.XYStepsRev);
	DDV_MinMaxUInt(pDX, C.XYStepsRev, 1, 100000);
	DDX_Text(pDX, IDC_EC_Z_ACCEL, C.ZAccel);
	DDV_MinMaxFloat(pDX, C.ZAccel, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_ENC2MICRON, C.ZEncoderToMicrons);
	DDV_MinMaxFloat(pDX, C.ZEncoderToMicrons, 1.e-003f, 1000.f);
	DDX_Text(pDX, IDC_EC_Z_LINESREV, C.ZLinesRev);
	DDV_MinMaxUInt(pDX, C.ZLinesRev, 1, 100000);
	DDX_Text(pDX, IDC_EC_Z_MANMAXSPEED, C.ZManMaxSpeed);
	DDV_MinMaxFloat(pDX, C.ZManMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_MANMAXSPEEDCHANGE, C.ZSpeedChangeLimit);
	DDV_MinMaxFloat(pDX, C.ZSpeedChangeLimit, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_MANSPEEDMULT, C.ZManSpeedMultiplier);
	DDV_MinMaxFloat(pDX, C.ZManSpeedMultiplier, 1.e-003f, 1.e+009f);
	DDX_Text(pDX, IDC_EC_Z_MAXSPEED, C.ZMaxSpeed);
	DDV_MinMaxFloat(pDX, C.ZMaxSpeed, 1.f, 1.e+012f);
	DDX_Text(pDX, IDC_EC_Z_STEPSREV, C.ZStepsRev);
	DDV_MinMaxUInt(pDX, C.ZStepsRev, 1, 100000);
	DDX_Text(pDX, IDC_EC_LIGHTLIMIT, C.LightLimit);
	DDV_MinMaxUInt(pDX, C.LightLimit, 1, 100000);
	DDX_Check(pDX, IDC_EC_INVERTX, C.InvertX);
	DDX_Check(pDX, IDC_EC_INVERTY, C.InvertY);
	DDX_Check(pDX, IDC_EC_INVERTZ, C.InvertZ);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_STEPDIR, OnStepDir)
	ON_BN_CLICKED(IDC_EC_CWCCW, OnCWCCW)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (C.CtlModeIsCWCCW)
	{
		GetDlgItem(IDC_EC_STEPDIR)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
		GetDlgItem(IDC_EC_CWCCW)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
	else
	{
		GetDlgItem(IDC_EC_STEPDIR)->SendMessage(BM_SETCHECK, BST_CHECKED);
		GetDlgItem(IDC_EC_CWCCW)->SendMessage(BM_SETCHECK, BST_UNCHECKED);		
		};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::OnStepDir() 
{
	// TODO: Add your control notification handler code here
	C.CtlModeIsCWCCW = 0;
}

void CEditConfig::OnCWCCW() 
{
	// TODO: Add your control notification handler code here
	C.CtlModeIsCWCCW = 1;	
}
