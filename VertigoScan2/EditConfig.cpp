// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditConfig.h"
#include "VertigoScanner.h"

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
	HPicture = 0;
	C.BaseThickness = 200.0f;
	C.ThicknessTolerance = 50.0f;
	C.BottomClusterParam = 900;
	C.BottomClusterThreshold = 1200;
	C.FocusTolerance = 100.0f;
	C.FramesPerSecond = 60.0f;
	C.HAcc = 100000.0f;
	C.HSpeed = 50000.0f;
	C.XStep = 330.0f;
	C.YStep = 330.0f;
	C.HTol = 5.0f;
	C.LightLevel = 10000;
	C.MaxClusters = 10000;
	C.MaxTracks = 100000;
	C.StageDelay = 0;
	C.TopClusterParam = 900;
	C.TopClusterThreshold = 1200;
	C.VAcc = 100000.0f;
	C.VLayers = 12;
	C.MinValidLayers = 8;
	C.FocusClusterParam = 900;
	C.VBaseSpeed = 50000.0f;
	C.VSpeed = 50000.0f;
	C.VStep = 20.0f;
	C.VTol = 2.0f;
	C.ScanningScheme = SCANNING_SCHEME_TOPSIDE;
	C.Shrinkage = 1.2;
	C.XFields = 11;
	C.YFields = 11;
	C.RefocusFields = 9;
	C.FocusLockModel = FOCUS_LOCK_BASE;
}


CEditConfig::~CEditConfig()
{
	if (HPicture) DeleteObject(HPicture);	
	};


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_BASETHICKNESS, C.BaseThickness);
	DDV_MinMaxFloat(pDX, C.BaseThickness, 10.f, 1000.f);
	DDX_Text(pDX, IDC_EC_THICKNESSTOLERANCE, C.ThicknessTolerance);
	DDV_MinMaxFloat(pDX, C.ThicknessTolerance, 10.f, 1000.f);
	DDX_Text(pDX, IDC_EC_BOTTOMCLCONTRAST, C.BottomClusterParam);
	DDV_MinMaxUInt(pDX, C.BottomClusterParam, 0, 32767);
	DDX_Text(pDX, IDC_EC_BOTTOMCLTHRESHOLD, C.BottomClusterThreshold);
	DDV_MinMaxUInt(pDX, C.BottomClusterThreshold, 1, 10000);
	DDX_Text(pDX, IDC_EC_FOCUSTOLERANCE, C.FocusTolerance);
	DDV_MinMaxFloat(pDX, C.FocusTolerance, 10.f, 5000.f);
	DDX_Text(pDX, IDC_EC_FPS, C.FramesPerSecond);
	DDV_MinMaxFloat(pDX, C.FramesPerSecond, 1.f, 1000.f);
	DDX_Text(pDX, IDC_EC_HACC, C.HAcc);
	DDV_MinMaxFloat(pDX, C.HAcc, 10.f, 1.e+007f);
	DDX_Text(pDX, IDC_EC_HSPEED, C.HSpeed);
	DDV_MinMaxFloat(pDX, C.HSpeed, 1.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_XSTEP, C.XStep);
	DDV_MinMaxFloat(pDX, C.XStep, 1.f, 3000.f);
	DDX_Text(pDX, IDC_EC_YSTEP, C.YStep);
	DDV_MinMaxFloat(pDX, C.YStep, 1.f, 3000.f);
	DDX_Text(pDX, IDC_EC_HTOL, C.HTol);
	DDV_MinMaxFloat(pDX, C.HTol, 0.1f, 100.f);
	DDX_Text(pDX, IDC_EC_LIGHTLEVEL, C.LightLevel);
	DDV_MinMaxUInt(pDX, C.LightLevel, 0, 32767);
	DDX_Text(pDX, IDC_EC_MAXCLUSTERS, C.MaxClusters);
	DDV_MinMaxUInt(pDX, C.MaxClusters, 100, 1000000);
	DDX_Text(pDX, IDC_EC_MAXTRACKS, C.MaxTracks);
	DDV_MinMaxUInt(pDX, C.MaxTracks, 10, 100000000);
	DDX_Text(pDX, IDC_EC_STAGEDELAY, C.StageDelay);
	DDV_MinMaxUInt(pDX, C.StageDelay, 0, 10000);
	DDX_Text(pDX, IDC_EC_LIMITERDELAY, C.LimiterDelay);
	DDV_MinMaxUInt(pDX, C.LimiterDelay, 0, 10000);
	DDX_Text(pDX, IDC_EC_TOPCLCONTRAST, C.TopClusterParam);
	DDV_MinMaxUInt(pDX, C.TopClusterParam, 0, 32767);
	DDX_Text(pDX, IDC_EC_TOPCLTHRESHOLD, C.TopClusterThreshold);
	DDV_MinMaxUInt(pDX, C.TopClusterThreshold, 1, 10000);
	DDX_Text(pDX, IDC_EC_VACC, C.VAcc);
	DDV_MinMaxFloat(pDX, C.VAcc, 10.f, 1.e+007f);
	DDX_Text(pDX, IDC_EC_VLAYERS, C.VLayers);
	DDV_MinMaxUInt(pDX, C.VLayers, 1, 200);
	DDX_Text(pDX, IDC_EC_VMINLAYERS, C.MinValidLayers);
	DDV_MinMaxUInt(pDX, C.MinValidLayers, 1, 100);
	DDX_Text(pDX, IDC_EC_VBASESPEED, C.VBaseSpeed);
	DDV_MinMaxFloat(pDX, C.VBaseSpeed, 1.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_VSPEED, C.VSpeed);
	DDV_MinMaxFloat(pDX, C.VSpeed, 1.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_VSTEP, C.VStep);
	DDV_MinMaxFloat(pDX, C.VStep, 1.f, 200.f);
	DDX_Text(pDX, IDC_EC_VTOL, C.VTol);
	DDV_MinMaxFloat(pDX, C.VTol, 0.1f, 100.f);
	DDX_Text(pDX, IDC_EC_SHRINKAGE, C.Shrinkage);
	DDV_MinMaxFloat(pDX, C.Shrinkage, 0.5f, 10.f);
	DDX_Text(pDX, IDC_EC_XFIELDS, C.XFields);
	DDV_MinMaxUInt(pDX, C.XFields, 1, 100);
	DDX_Text(pDX, IDC_EC_YFIELDS, C.YFields);
	DDV_MinMaxUInt(pDX, C.YFields, 1, 100);
	DDX_Text(pDX, IDC_EC_REFOCUSFIELDS, C.RefocusFields);
	DDV_MinMaxUInt(pDX, C.RefocusFields, 1, 100);
	DDX_Text(pDX, IDC_EC_FOCUSCLUSTERCONTRAST, C.FocusClusterParam);
	DDV_MinMaxUInt(pDX, C.FocusClusterParam, 0, 32767);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_LOCKONBASE, OnLockOnBase)
	ON_BN_CLICKED(IDC_EC_LOCKONCENTER, OnLockOnCenter)
	ON_BN_CLICKED(IDC_EC_SCANBOTHINFIELD, OnScanBothInField)
	ON_BN_CLICKED(IDC_EC_SCANBOTHTWOSIDES, OnScanBothTwoSides)
	ON_BN_CLICKED(IDC_EC_SCANBOTTOM, OnScanBottom)
	ON_BN_CLICKED(IDC_EC_SCANTOP, OnScanTop)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HPicture = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_WELCOME), IMAGE_BITMAP, 0, 0, 0);
	GetObject(HPicture, sizeof(PictInfo), &PictInfo);

	// TODO: Add extra initialization here
	switch (C.FocusLockModel)
	{
		case FOCUS_LOCK_CENTERLEVEL:			GetDlgItem(IDC_EC_LOCKONCENTER)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;

		case FOCUS_LOCK_BASE:					GetDlgItem(IDC_EC_LOCKONBASE)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;
		};

	switch (C.ScanningScheme)
	{
		case SCANNING_SCHEME_TOPSIDE:			GetDlgItem(IDC_EC_SCANTOP)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;

		case SCANNING_SCHEME_BOTTOMSIDE:		GetDlgItem(IDC_EC_SCANBOTTOM)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;

		case SCANNING_SCHEME_BOTH_IN_FIELD:		GetDlgItem(IDC_EC_SCANBOTHINFIELD)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;

		case SCANNING_SCHEME_TWO_SIDES:			GetDlgItem(IDC_EC_SCANBOTHTWOSIDES)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;
		};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::OnLockOnBase() 
{
	// TODO: Add your control notification handler code here
	C.FocusLockModel = FOCUS_LOCK_BASE;	
}

void CEditConfig::OnLockOnCenter() 
{
	// TODO: Add your control notification handler code here
	C.FocusLockModel = FOCUS_LOCK_CENTERLEVEL;
}

void CEditConfig::OnScanBothInField() 
{
	// TODO: Add your control notification handler code here
	C.ScanningScheme = SCANNING_SCHEME_BOTH_IN_FIELD;
}

void CEditConfig::OnScanBothTwoSides() 
{
	// TODO: Add your control notification handler code here
	C.ScanningScheme = SCANNING_SCHEME_TWO_SIDES;
}

void CEditConfig::OnScanBottom() 
{
	// TODO: Add your control notification handler code here
	C.ScanningScheme = SCANNING_SCHEME_BOTTOMSIDE;
}

void CEditConfig::OnScanTop() 
{
	// TODO: Add your control notification handler code here
	C.ScanningScheme = SCANNING_SCHEME_TOPSIDE;
}

void CEditConfig::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDCtl == IDC_EC_PICTURE)
	{
		CRect Rect;
		GetDlgItem(IDC_EC_PICTURE)->GetClientRect(&Rect);
		HDC hDC = CreateCompatibleDC(lpDrawItemStruct->hDC);
		SelectObject(hDC, HPicture);
		StretchBlt(lpDrawItemStruct->hDC, 0, 0, Rect.Width(), Rect.Height(), hDC, 0, 0, PictInfo.bmWidth, abs(PictInfo.bmHeight), SRCCOPY);
		DeleteDC(hDC);
		}
	else CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
