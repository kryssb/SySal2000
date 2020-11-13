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
	m_DeltaPos = 0.0f;
	m_DeltaSlope = 0.0f;
	m_DistWindowX = 0.0f;
	m_DistWindowY = 0.0f;
	m_EnableParabolicCorrection = FALSE;
	m_EnableTrackRecovery = FALSE;
	m_ExclusionDistance = 0.0f;
	m_GoodPoints = 0;
	m_MaxDistX = 0.0f;
	m_MaxDistY = 0.0f;
	m_MaxIterations = 0;
	m_MaxPointDelta = 0.0f;
	m_MaxSigma = 0.0f;
	m_MinPoints = 0;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Text(pDX, IDC_EC_DELTAPOS, m_DeltaPos);
	DDV_MinMaxFloat(pDX, m_DeltaPos, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_DELTASLOPE, m_DeltaSlope);
	DDV_MinMaxFloat(pDX, m_DeltaSlope, 0.f, 0.2f);
	DDX_Text(pDX, IDC_EC_DISTWINDOWX, m_DistWindowX);
	DDV_MinMaxFloat(pDX, m_DistWindowX, 0.f, 50.f);
	DDX_Text(pDX, IDC_EC_DISTWINDOWY, m_DistWindowY);
	DDV_MinMaxFloat(pDX, m_DistWindowY, 0.f, 50.f);
	DDX_Check(pDX, IDC_EC_ENABLEPARABOLICCORRECTION, m_EnableParabolicCorrection);
	DDX_Check(pDX, IDC_EC_ENABLERECOVERY, m_EnableTrackRecovery);
	DDX_Text(pDX, IDC_EC_EXCLUSIONDISTANCE, m_ExclusionDistance);
	DDV_MinMaxFloat(pDX, m_ExclusionDistance, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_GOODPOINTS, m_GoodPoints);
	DDV_MinMaxUInt(pDX, m_GoodPoints, 3, 100);
	DDX_Text(pDX, IDC_EC_MAXDISTX, m_MaxDistX);
	DDV_MinMaxFloat(pDX, m_MaxDistX, 1.f, 100.f);
	DDX_Text(pDX, IDC_EC_MAXDISTY, m_MaxDistY);
	DDV_MinMaxFloat(pDX, m_MaxDistY, 1.f, 100.f);
	DDX_Text(pDX, IDC_EC_MAXITERATIONS, m_MaxIterations);
	DDV_MinMaxUInt(pDX, m_MaxIterations, 1, 30);
	DDX_Text(pDX, IDC_EC_MAXPOINTDELTA, m_MaxPointDelta);
	DDV_MinMaxFloat(pDX, m_MaxPointDelta, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_MAXSIGMA, m_MaxSigma);
	DDV_MinMaxFloat(pDX, m_MaxSigma, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_MINPOINTS, m_MinPoints);
	DDV_MinMaxUInt(pDX, m_MinPoints, 3, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_KEEPALL, OnKeepAllPoints)
	ON_BN_CLICKED(IDC_EC_ITERATEDISCARDING, OnIterateDiscarding)
	ON_BN_CLICKED(IDC_EC_DISCARDONCE, OnDiscardOnce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::OnKeepAllPoints() 
{
	// TODO: Add your control notification handler code here
	m_DiscardPolicy = KEEP_ALL_POINTS;
}

void CEditConfig::OnIterateDiscarding() 
{
	// TODO: Add your control notification handler code here
	m_DiscardPolicy = ITERATE_DISCARDING;
}

void CEditConfig::OnDiscardOnce() 
{
	// TODO: Add your control notification handler code here
	m_DiscardPolicy = DISCARD_POINTS_ONCE;
}

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SendDlgItemMessage(IDC_EC_KEEPALL, BM_SETCHECK, m_DiscardPolicy == KEEP_ALL_POINTS ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_EC_DISCARDONCE, BM_SETCHECK, m_DiscardPolicy == DISCARD_POINTS_ONCE ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_EC_ITERATEDISCARDING, BM_SETCHECK, m_DiscardPolicy == ITERATE_DISCARDING ? BST_CHECKED : BST_UNCHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
