// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditConfig.h"
#include "TSReconData.h"

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
	m_InPlate_D_Pos = 10.0f;
	m_InPlate_D_Slope = 0.015f;
	m_InPlate_Gross_D_Pos = 10.0f;
	m_InPlate_Gross_D_Slope = 0.03f;
	m_InPlate_Pos_Prescan = 40.0f;
	m_InPlate_MaxIters = 5;	
	m_MaxMissingSegments = 3;
	m_MinSegments = 3;
	m_OffPlate_D_Pos = 10.0f;
	m_OffPlate_D_Slope = 0.015f;
	m_OffPlate_Gross_D_Pos = 20.0f;
	m_OffPlate_Gross_D_Slope = 0.03f;
	m_OffPlate_Pos_Prescan = 100.0f;
	m_OffPlate_MaxIters = 7;
	m_RequireOffPlateLinking = FALSE;
	m_InField_D_Pos = 5.f;
	m_InField_D_Slope = 0.02f;
	m_OffField_D_Pos = 10.f;
	m_OffField_D_Slope = 0.03f;
	m_PassingThrough_Angle = 0.4f;
	m_PassingThrough_OutLength = 500.0f;
	m_PassingThrough_Radius = 50.0f;
	m_Vertex_XYTol = 5.0f;
	m_Vertex_XYTolIncrease = 0.0f;
	m_Vertex_LowestZ = -500.0f;
	m_Vertex_Overlength = 60.0f;
	m_Vertex_MergeXYTol = 20.0f;
	m_Vertex_MergeZTol = 60.0f;
	m_Vertex_ZExtrapolation = 1500.0f;
	m_Vertex_Recovery_ZExtrapolation = 500.0f;
	m_MaxRemeasuresInSegment = 4;	
	m_LowestPrescanPeak = 0.5f;
	m_MinSegmentsRecovery = 2;
	m_FinalAlignment_Enable = FALSE;
	m_FinalAlignment_MaxIters = 10;
	m_FinalAlignment_SlopeMeasures = 4;
	m_FinalAlignment_MaxSlopeDiff = 3.f;
	m_FinalAlignment_MinSlopeDiff = 2.f;
	m_FinalAlignment_MinEntries = 50;
	m_FinalAlignment_MaxRMS = 0.003f;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Text(pDX, IDC_EC_INPLATEDPOS, m_InPlate_D_Pos);
	DDV_MinMaxFloat(pDX, m_InPlate_D_Pos, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_INPLATEDSLOPE, m_InPlate_D_Slope);
	DDV_MinMaxFloat(pDX, m_InPlate_D_Slope, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EC_INPLATEGROSSDPOS, m_InPlate_Gross_D_Pos);
	DDV_MinMaxFloat(pDX, m_InPlate_Gross_D_Pos, 1.f, 100.f);
	DDX_Text(pDX, IDC_EC_INPLATEGROSSDSLOPE, m_InPlate_Gross_D_Slope);
	DDV_MinMaxFloat(pDX, m_InPlate_Gross_D_Slope, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EC_INPLATEPOSPRESCAN, m_InPlate_Pos_Prescan);
	DDV_MinMaxFloat(pDX, m_InPlate_Pos_Prescan, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_INPLATEMAXITERS, m_InPlate_MaxIters);
	DDV_MinMaxUInt(pDX, m_InPlate_MaxIters, 1, 10);
	DDX_Text(pDX, IDC_EC_MAXMISSINGSEGS, m_MaxMissingSegments);
	DDV_MinMaxUInt(pDX, m_MaxMissingSegments, 0, 10);
	DDX_Text(pDX, IDC_EC_MINSEGS, m_MinSegments);
	DDV_MinMaxUInt(pDX, m_MinSegments, 1, 100);
	DDX_Text(pDX, IDC_EC_OFFPLATEDPOS, m_OffPlate_D_Pos);
	DDV_MinMaxFloat(pDX, m_OffPlate_D_Pos, 0.f, 200.f);
	DDX_Text(pDX, IDC_EC_OFFPLATEDSLOPE, m_OffPlate_D_Slope);
	DDV_MinMaxFloat(pDX, m_OffPlate_D_Slope, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EC_OFFPLATEGROSSDPOS, m_OffPlate_Gross_D_Pos);
	DDV_MinMaxFloat(pDX, m_OffPlate_Gross_D_Pos, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_OFFPLATEGROSSDSLOPE, m_OffPlate_Gross_D_Slope);
	DDV_MinMaxFloat(pDX, m_OffPlate_Gross_D_Slope, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EC_OFFPLATEPOSPRESCAN, m_OffPlate_Pos_Prescan);
	DDV_MinMaxFloat(pDX, m_OffPlate_Pos_Prescan, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_OFFPLATEMAXITERS, m_OffPlate_MaxIters);
	DDV_MinMaxUInt(pDX, m_OffPlate_MaxIters, 1, 10);
	DDX_Check(pDX, IDC_EC_PLATECROSSING, m_RequireOffPlateLinking);
	DDX_Text(pDX, IDC_EC_INFIELDDPOS, m_InField_D_Pos);
	DDV_MinMaxFloat(pDX, m_InField_D_Pos, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_INFIELDDSLOPE, m_InField_D_Slope);
	DDV_MinMaxFloat(pDX, m_InField_D_Slope, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EC_OFFFIELDDPOS, m_OffField_D_Pos);
	DDV_MinMaxFloat(pDX, m_OffField_D_Pos, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_OFFFIELDDSLOPE, m_OffField_D_Slope);
	DDV_MinMaxFloat(pDX, m_OffField_D_Slope, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EC_PASSTHRU_ANGLE, m_PassingThrough_Angle);
	DDV_MinMaxFloat(pDX, m_PassingThrough_Angle, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_PASSTHRU_OUTLENGTH, m_PassingThrough_OutLength);
	DDV_MinMaxFloat(pDX, m_PassingThrough_OutLength, 0.f, 5000.f);
	DDX_Text(pDX, IDC_EC_PASSTHRU_RADIUS, m_PassingThrough_Radius);
	DDV_MinMaxFloat(pDX, m_PassingThrough_Radius, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_VERTEX_XYTOL, m_Vertex_XYTol);
	DDV_MinMaxFloat(pDX, m_Vertex_XYTol, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_VERTEX_XYTOLINCREASE, m_Vertex_XYTolIncrease);
	DDV_MinMaxFloat(pDX, m_Vertex_XYTolIncrease, 0.f, 1.f);
	DDX_Text(pDX, IDC_EC_VERTEX_LOWESTZ, m_Vertex_LowestZ);
	DDV_MinMaxFloat(pDX, m_Vertex_LowestZ, -5000.f, 0.f);
	DDX_Text(pDX, IDC_EC_VERTEX_OVERLENGTH, m_Vertex_Overlength);
	DDV_MinMaxFloat(pDX, m_Vertex_Overlength, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_VERTEX_MERGEXYTOL, m_Vertex_MergeXYTol);
	DDV_MinMaxFloat(pDX, m_Vertex_MergeXYTol, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_VERTEX_MERGEZTOL, m_Vertex_MergeZTol);
	DDV_MinMaxFloat(pDX, m_Vertex_MergeZTol, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_VERTEX_EXTRAPOLATION, m_Vertex_ZExtrapolation);
	DDV_MinMaxFloat(pDX, m_Vertex_ZExtrapolation, 0.f, 10000.f);
	DDX_Text(pDX, IDC_EC_VERTEX_REC_EXTRAPOLATION, m_Vertex_Recovery_ZExtrapolation);
	DDV_MinMaxFloat(pDX, m_Vertex_Recovery_ZExtrapolation, 0.f, 10000.f);
	DDX_Text(pDX, IDC_EC_MAXREMEASURESINSEG, m_MaxRemeasuresInSegment);
	DDV_MinMaxUInt(pDX, m_MaxRemeasuresInSegment, 1, 10);
	DDX_Text(pDX, IDC_EC_LOWESTPRESCANPEAK, m_LowestPrescanPeak);
	DDV_MinMaxFloat(pDX, m_LowestPrescanPeak, 0.1f, 1.f);
	DDX_Text(pDX, IDC_EC_MINSEGSRECOVERY, m_MinSegmentsRecovery);
	DDV_MinMaxUInt(pDX, m_MinSegmentsRecovery, 1, 100);
	DDX_Check(pDX, IDC_EC_FINALALIGNMENTENABLE, m_FinalAlignment_Enable);
	DDX_Text(pDX, IDC_EC_FINALITERATIONS, m_FinalAlignment_MaxIters);
	DDV_MinMaxUInt(pDX, m_FinalAlignment_MaxIters, 1, 10);
	DDX_Text(pDX, IDC_EC_FINALMAXDIFF, m_FinalAlignment_MaxSlopeDiff);
	DDV_MinMaxFloat(pDX, m_FinalAlignment_MaxSlopeDiff, 0.f, 5.f);
	DDX_Text(pDX, IDC_EC_FINALMINDIFF, m_FinalAlignment_MinSlopeDiff);
	DDV_MinMaxFloat(pDX, m_FinalAlignment_MinSlopeDiff, 0.f, 5.f);
	DDX_Text(pDX, IDC_EC_FINALMINENTRIES, m_FinalAlignment_MinEntries);
	DDV_MinMaxUInt(pDX, m_FinalAlignment_MinEntries, 8, 100);
	DDX_Text(pDX, IDC_EC_FINALMAXACCRMS, m_FinalAlignment_MaxRMS);
	DDV_MinMaxFloat(pDX, m_FinalAlignment_MaxRMS, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EC_FINALSLOPEMEASURES, m_FinalAlignment_SlopeMeasures);
	DDV_MinMaxUInt(pDX, m_FinalAlignment_SlopeMeasures, 4, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_MERGE, OnMerge)
	ON_BN_CLICKED(IDC_EC_DISCARDSHORTER, OnDiscardShorter)
	ON_BN_CLICKED(IDC_EC_DISCARDWORSE, OnDiscardWorse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::OnMerge() 
{
	// TODO: Add your control notification handler code here
	m_RemeasureHandling = TSRD_REMEASURE_MERGE;	
}

void CEditConfig::OnDiscardShorter() 
{
	// TODO: Add your control notification handler code here
	m_RemeasureHandling = TSRD_REMEASURE_DISCARDSHORTER;
}

void CEditConfig::OnDiscardWorse() 
{
	// TODO: Add your control notification handler code here
	m_RemeasureHandling = TSRD_REMEASURE_DISCARDWORSE;			
}

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	switch (m_RemeasureHandling)
	{
		case TSRD_REMEASURE_MERGE:				GetDlgItem(IDC_EC_MERGE)->SendMessage(BM_SETCHECK, BST_CHECKED);
														break;

		case TSRD_REMEASURE_DISCARDSHORTER:		GetDlgItem(IDC_EC_DISCARDSHORTER)->SendMessage(BM_SETCHECK, BST_CHECKED);
														break;

		case TSRD_REMEASURE_DISCARDWORSE:	GetDlgItem(IDC_EC_DISCARDWORSE)->SendMessage(BM_SETCHECK, BST_CHECKED);
														break;		
		};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

