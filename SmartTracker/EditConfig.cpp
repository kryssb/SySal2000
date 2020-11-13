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
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_ATTLIM, C.AttLim);
	DDV_MinMaxUInt(pDX, C.AttLim, 1, 10);
	DDX_Text(pDX, IDC_EC_CELLOVERFLOW, C.CellOverflow);
	DDV_MinMaxUInt(pDX, C.CellOverflow, 32, 1024);
	DDX_Text(pDX, IDC_EC_CELLSX, C.CellNumX);
	DDV_MinMaxUInt(pDX, C.CellNumX, 1, 100);
	DDX_Text(pDX, IDC_EC_CELLSY, C.CellNumY);
	DDV_MinMaxUInt(pDX, C.CellNumY, 1, 100);
	DDX_Text(pDX, IDC_EC_DHARD, C.DHard);
	DDV_MinMaxFloat(pDX, C.DHard, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_DLOOSE, C.DLoose);
	DDV_MinMaxFloat(pDX, C.DLoose, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_MAXGRAINS, C.MaxGrains);
	DDV_MinMaxUInt(pDX, C.MaxGrains, 1000, 500000);
	DDX_Text(pDX, IDC_EC_MAXLAYERS, C.LayerNum);
	DDV_MinMaxUInt(pDX, C.LayerNum, 10, 200);
	DDX_Text(pDX, IDC_EC_MAXPIXELS, C.PixMax);
	DDV_MinMaxUInt(pDX, C.PixMax, 1, 10000000);
	DDX_Text(pDX, IDC_EC_MAXSLOPE, C.MaxSlope);
	DDV_MinMaxFloat(pDX, C.MaxSlope, 0.f, 2.f);
	DDX_Text(pDX, IDC_EC_MINPIXELS, C.PixMin);
	DDV_MinMaxUInt(pDX, C.PixMin, 0, 10000000);
	DDX_Text(pDX, IDC_EC_MINPOINTS0, C.NptMin0);
	DDV_MinMaxFloat(pDX, C.NptMin0, 3.f, 200.f);
	DDX_Text(pDX, IDC_EC_MINPOINTSSLOPE, C.NptMinSlope);
	DDV_MinMaxFloat(pDX, C.NptMinSlope, -100.f, 100.f);
	DDX_Text(pDX, IDC_EC_MINSLOPE, C.MinSlope);
	DDV_MinMaxFloat(pDX, C.MinSlope, -1.e-003f, 2.f);
	DDX_Text(pDX, IDC_EC_RETRYGAP, C.RetryGap);
	DDV_MinMaxUInt(pDX, C.RetryGap, 1, 10);
	DDX_Text(pDX, IDC_EC_STARTGAP, C.StartGap);
	DDV_MinMaxUInt(pDX, C.StartGap, 2, 10);
	DDX_Text(pDX, IDC_EC_IDRADIUS, C.IdentityRadius);
	DDV_MinMaxUInt(pDX, C.IdentityRadius, 0.f, 2.f);
	DDX_Text(pDX, IDC_EC_GOODPIXELS, C.GoodPixels);
	DDV_MinMaxUInt(pDX, C.GoodPixels, 1, 1000000);
	DDX_Check(pDX, IDC_EC_DEPENDREDUCTION, C.DependencyReduction);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers


