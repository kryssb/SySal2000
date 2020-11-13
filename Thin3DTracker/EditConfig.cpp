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
	m_AttLim = 0;
	m_CellOverflow = 0;
	m_CellsX = 0;
	m_CellsY = 0;
	m_DHard = 0.0f;
	m_DLoose = 0.0f;
	m_MaxGrains = 0;
	m_MaxLayers = 0;
	m_MaxPixels = 0;
	m_MaxSlope = 0.0f;
	m_MinPixels = 0;
	m_MinPoints0 = 0.0f;
	m_MinPointsSlope = 0.0f;
	m_MinSlope = 0.0f;
	m_RetryGap = 0;
	m_StartGap = 0;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Text(pDX, IDC_EC_ATTLIM, m_AttLim);
	DDV_MinMaxUInt(pDX, m_AttLim, 1, 10);
	DDX_Text(pDX, IDC_EC_CELLOVERFLOW, m_CellOverflow);
	DDV_MinMaxUInt(pDX, m_CellOverflow, 32, 1024);
	DDX_Text(pDX, IDC_EC_CELLSX, m_CellsX);
	DDV_MinMaxUInt(pDX, m_CellsX, 1, 100);
	DDX_Text(pDX, IDC_EC_CELLSY, m_CellsY);
	DDV_MinMaxUInt(pDX, m_CellsY, 1, 100);
	DDX_Text(pDX, IDC_EC_DHARD, m_DHard);
	DDV_MinMaxFloat(pDX, m_DHard, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_DLOOSE, m_DLoose);
	DDV_MinMaxFloat(pDX, m_DLoose, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_MAXGRAINS, m_MaxGrains);
	DDV_MinMaxUInt(pDX, m_MaxGrains, 1000, 500000);
	DDX_Text(pDX, IDC_EC_MAXLAYERS, m_MaxLayers);
	DDV_MinMaxUInt(pDX, m_MaxLayers, 10, 200);
	DDX_Text(pDX, IDC_EC_MAXPIXELS, m_MaxPixels);
	DDV_MinMaxUInt(pDX, m_MaxPixels, 1, 10000000);
	DDX_Text(pDX, IDC_EC_MAXSLOPE, m_MaxSlope);
	DDV_MinMaxFloat(pDX, m_MaxSlope, 0.f, 2.f);
	DDX_Text(pDX, IDC_EC_MINPIXELS, m_MinPixels);
	DDV_MinMaxUInt(pDX, m_MinPixels, 0, 10000000);
	DDX_Text(pDX, IDC_EC_MINPOINTS0, m_MinPoints0);
	DDV_MinMaxFloat(pDX, m_MinPoints0, 3.f, 200.f);
	DDX_Text(pDX, IDC_EC_MINPOINTSSLOPE, m_MinPointsSlope);
	DDV_MinMaxFloat(pDX, m_MinPointsSlope, -100.f, 100.f);
	DDX_Text(pDX, IDC_EC_MINSLOPE, m_MinSlope);
	DDV_MinMaxFloat(pDX, m_MinSlope, -1.e-003f, 2.f);
	DDX_Text(pDX, IDC_EC_RETRYGAP, m_RetryGap);
	DDV_MinMaxUInt(pDX, m_RetryGap, 1, 10);
	DDX_Text(pDX, IDC_EC_STARTGAP, m_StartGap);
	DDV_MinMaxUInt(pDX, m_StartGap, 2, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers


