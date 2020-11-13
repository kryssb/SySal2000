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
	DDX_Text(pDX, IDC_EC_DELTAPOS, C.RecoveryDeltaPos);
	DDV_MinMaxFloat(pDX, C.RecoveryDeltaPos, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_DELTASLOPE, C.RecoveryDeltaSlope);
	DDV_MinMaxFloat(pDX, C.RecoveryDeltaSlope, 0.f, 0.2f);
	DDX_Check(pDX, IDC_EC_ENABLERECOVERY, C.RecoveryOn);
	DDX_Text(pDX, IDC_EC_MAXPOINTDELTA, C.DistanceLimit);
	DDV_MinMaxFloat(pDX, C.DistanceLimit, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_MAXSIGMA, C.SigmaLimit);
	DDV_MinMaxFloat(pDX, C.SigmaLimit, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_MINPOINTS, C.MinPointsN);
	DDV_MinMaxUInt(pDX, C.MinPointsN, 3, 100);
	DDX_Text(pDX, IDC_EC_MAXMEM, C.MaxMemoryOccupancy);
	DDV_MinMaxUInt(pDX, C.MaxMemoryOccupancy, 1, 8192);
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
	C.DiscardPoints = KEEP_ALL_POINTS;
}

void CEditConfig::OnIterateDiscarding() 
{
	// TODO: Add your control notification handler code here
	C.DiscardPoints = ITERATE_DISCARDING;
}

void CEditConfig::OnDiscardOnce() 
{
	// TODO: Add your control notification handler code here
	C.DiscardPoints = DISCARD_POINTS_ONCE;
}

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SendDlgItemMessage(IDC_EC_KEEPALL, BM_SETCHECK, C.DiscardPoints == KEEP_ALL_POINTS ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_EC_DISCARDONCE, BM_SETCHECK, C.DiscardPoints == DISCARD_POINTS_ONCE ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_EC_ITERATEDISCARDING, BM_SETCHECK, C.DiscardPoints == ITERATE_DISCARDING ? BST_CHECKED : BST_UNCHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
