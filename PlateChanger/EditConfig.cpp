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
	C.NumberOfAttempt=10; //number of attempt to take emulsion from the stage
	C.PositionTimeout=50; //timeout in steps of 100ms for H and V movements
	C.VacuumTimeout=10; //same for vacuum
	C.BubbleTimeout=30000; //timeout before emulsion will stick to the table and all air under it is out
	C.NumberOfBanks=3; //number of banks to use
	C.WithSeparators=true; //default value for presence of separators
	C.SeparationAttempts=3;
	C.LimOffsetX=-100000.0; //Offset of LIM position wrt HOME (0,0)
	C.LimOffsetY=-30700.0;
	C.LimOffsetZ=-0.0;
	C.FMOffsetX=-44000.0; //Offset of first FM wrt HOME (0,0)
	C.FMOffsetY=30300.0;
	C.FMOffsetZ=-130.0;
	C.SpeedX=1e5;
	C.SpeedY=1e5;
	C.SpeedZ=1e3;
	C.AccX=1e5;
	C.AccY=1e5;
	C.AccZ=1e3;
	C.LightLevel=32767;
	C.LiftCorners=true;
	C.ComPort=2;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_NUMBEROFATTEMPT, C.NumberOfAttempt);
	DDV_MinMaxInt(pDX, C.NumberOfAttempt, 1, 30);
	DDX_Text(pDX, IDC_POSTIMEOUT, C.PositionTimeout);
	DDV_MinMaxInt(pDX, C.PositionTimeout, 1, 100);
	DDX_Text(pDX, IDC_VACTIMEOUT, C.VacuumTimeout);
	DDV_MinMaxInt(pDX, C.VacuumTimeout, 1, 100);
	DDX_Text(pDX, IDC_AIRTIMEOUT, C.BubbleTimeout);
	DDV_MinMaxInt(pDX, C.BubbleTimeout, 0, 120000);
	DDX_Text(pDX, IDC_NUMBEROFBANKS, C.NumberOfBanks);
	DDV_MinMaxInt(pDX, C.NumberOfBanks, 2, 4);
	DDX_Check(pDX, IDC_WITHSEPARATORS, C.WithSeparators);
	DDV_MinMaxInt(pDX, C.WithSeparators, 0, 2);
	DDX_Text(pDX, IDC_SEPATTEMPTS, C.SeparationAttempts);
	DDV_MinMaxInt(pDX, C.SeparationAttempts, 1, 30);
	DDX_Text(pDX, IDC_LIMOFFSETX, C.LimOffsetX);
	DDV_MinMaxFloat(pDX, C.LimOffsetX, -1e6, 1e6);
	DDX_Text(pDX, IDC_LIMOFFSETY, C.LimOffsetY);
	DDV_MinMaxFloat(pDX, C.LimOffsetY, -1e6, 1e6);
	DDX_Text(pDX, IDC_LIMOFFSETZ, C.LimOffsetZ);
	DDV_MinMaxFloat(pDX, C.LimOffsetZ, -1e6, 1e6);
	DDX_Text(pDX, IDC_FMOFFSETX, C.FMOffsetX);
	DDV_MinMaxFloat(pDX, C.FMOffsetX, -1e6, 1e6);
	DDX_Text(pDX, IDC_FMOFFSETY, C.FMOffsetY);
	DDV_MinMaxFloat(pDX, C.FMOffsetY, -1e6, 1e6);
	DDX_Text(pDX, IDC_FMOFFSETZ, C.FMOffsetZ);
	DDV_MinMaxFloat(pDX, C.FMOffsetZ, -1e6, 1e6);

	DDX_Text(pDX, IDC_SPEEDX2, C.SpeedX);
	DDV_MinMaxFloat(pDX, C.SpeedX, 0, 1e6);
	DDX_Text(pDX, IDC_SPEEDY2, C.SpeedY);
	DDV_MinMaxFloat(pDX, C.SpeedY, 0, 1e6);
	DDX_Text(pDX, IDC_SPEEDZ2, C.SpeedZ);
	DDV_MinMaxFloat(pDX, C.SpeedZ, 0, 1e6);
	DDX_Text(pDX, IDC_ACCX3, C.AccX);
	DDV_MinMaxFloat(pDX, C.AccX, 0, 1e6);
	DDX_Text(pDX, IDC_ACCY3, C.AccY);
	DDV_MinMaxFloat(pDX, C.AccY, 0, 1e6);
	DDX_Text(pDX, IDC_ACCZ3, C.AccZ);
	DDV_MinMaxFloat(pDX, C.AccZ, 0, 1e6);

	DDX_Text(pDX, IDC_LIGHTLEVEL, C.LightLevel);
	DDV_MinMaxInt(pDX, C.LightLevel, 0, 32767);
	DDX_Check(pDX, IDC_LIFTCORNERS, C.LiftCorners);
	DDV_MinMaxInt(pDX, C.LiftCorners, 0, 2);
	DDX_Text(pDX, IDC_COMPORT, C.ComPort);
	DDV_MinMaxInt(pDX, C.ComPort, 0, 7);


	}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

