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
	m_FSDirAgreement = 0.0f;
	m_MaxFlatStrips = 0;
	m_FSWidth2Length = 0.0f;
	m_FSTkRange = 0.0f;
	m_MinFlatStrips = 0;
	m_MinFlatStripsPixels = 0;
	m_FSTkSectorWidth = 0.0f;
	m_MaxFSEmptyLayers = 0;
	m_MinFlatTrackLength = 0.0f;
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
	DDX_Text(pDX, IDC_EC_FSDIRAGREEMENT, m_FSDirAgreement);
	DDV_MinMaxFloat(pDX, m_FSDirAgreement, 0.f, 30.f);
	DDX_Text(pDX, IDC_EC_MAXFLATSTRIPS, m_MaxFlatStrips);
	DDV_MinMaxUInt(pDX, m_MaxFlatStrips, 0, 10000);
	DDX_Text(pDX, IDC_EC_MAXFSWIDTH2LENGTH, m_FSWidth2Length);
	DDV_MinMaxFloat(pDX, m_FSWidth2Length, 0.f, 0.8f);
	DDX_Text(pDX, IDC_EC_MAXPLANEDISTANCE, m_FSTkRange);
	DDV_MinMaxFloat(pDX, m_FSTkRange, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_MINFLATSTRIPS, m_MinFlatStrips);
	DDV_MinMaxUInt(pDX, m_MinFlatStrips, 4, 60);
	DDX_Text(pDX, IDC_EC_MINFSPIXELS, m_MinFlatStripsPixels);
	DDV_MinMaxUInt(pDX, m_MinFlatStripsPixels, 8, 500);
	DDX_Text(pDX, IDC_EC_TKSECTOROPENINGANGLE, m_FSTkSectorWidth);
	DDV_MinMaxFloat(pDX, m_FSTkSectorWidth, 0.f, 30.f);
	DDX_Text(pDX, IDC_EC_MAXFSEMPTYLAYERS, m_MaxFSEmptyLayers);
	DDV_MinMaxUInt(pDX, m_MaxFSEmptyLayers, 0, 10);
	DDX_Text(pDX, IDC_EC_MINFLATTRACKLENGTH, m_MinFlatTrackLength);
	DDV_MinMaxFloat(pDX, m_MinFlatTrackLength, 1.f, 200.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers


