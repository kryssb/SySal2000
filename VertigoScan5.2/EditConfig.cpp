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


CEditConfig::CEditConfig(IStage2 *ist2, CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent), iSt2(ist2)
{
	//{{AFX_DATA_INIT(CEditConfig)
	//}}AFX_DATA_INIT
	HPicture = 0;
	C.BaseThickness = 200.0f;
	C.ThicknessTolerance = 50.0f;
	C.BottomClusterParam = 2;
	C.BottomClusterThreshold = 1200;
	C.BottomExpectedClusters = 2200;
	C.BottomClustersFluctuation = 100;
	C.BottomClustersMinArea = 4;
	C.FocusTolerance = 100.0f;
	C.SurfaceAdjustment = 10.0f;
	C.FramesPerSecond = 60.0f;
	C.HAcc = 100000.0f;
	C.HSpeed = 50000.0f;
	C.XStep = 330.0f;
	C.YStep = 330.0f;
	C.HTol = 5.0f;
	C.LightLevel = 10000;
	C.MaxClusters = 10000;
	C.MaxTracks = 100000;
	C.TopClusterParam = 1;
	C.TopClusterThreshold = 1200;
	C.TopExpectedClusters = 2200;
	C.TopClustersFluctuation = 100;
	C.TopClustersMinArea = 4;
	C.VAcc = 100000.0f;
	C.VLayers = 12;
	C.VInactiveLayers = 0;
	C.MinValidLayers = 8;
	C.VBaseSpeed = 50000.0f;
	C.VSpeed = 50000.0f;
	C.TopStep = 40.0f;
	C.BottomStep = 45.0f;
	C.VTol = 2.0f;
	C.ScanningScheme = SCANNING_SCHEME_TOPSIDE;
	C.Shrinkage = 1.2;
	C.TemplateXFields = 11;
	C.TemplateYFields = 11;
	C.ZSampleInterval = 10;
	C.FocusZSampleInterval = 10;
	C.FocusLockModel = FOCUS_LOCK_BASE;
	C.ZScanDuration = 450;
	C.XYZMotionDuration = 120;
	WarningScanSamples = false;
	WarningFocusSamples = false;
	BkBrush = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}


CEditConfig::~CEditConfig()
{
	if (HPicture) DeleteObject(HPicture);
	if (BkBrush) DeleteObject(BkBrush);
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
	DDX_Text(pDX, IDC_EC_BOTTOMEXPCLUSTERS, C.BottomExpectedClusters);
	DDV_MinMaxUInt(pDX, C.BottomExpectedClusters, 0, 10000);
	DDX_Text(pDX, IDC_EC_BOTTOMCLUSTERSFLUCT, C.BottomClustersFluctuation);
	DDV_MinMaxUInt(pDX, C.BottomClustersFluctuation, 0, 1000);
	DDX_Text(pDX, IDC_EC_BOTTOMCLUSTERSMINAREA, C.BottomClustersMinArea);
	DDV_MinMaxUInt(pDX, C.BottomClustersMinArea, 1, 64);
	DDX_Text(pDX, IDC_EC_FOCUSTOLERANCE, C.FocusTolerance);
	DDV_MinMaxFloat(pDX, C.FocusTolerance, 10.f, 500.f);
	DDX_Text(pDX, IDC_EC_SURFACEADJUSTMENT, C.SurfaceAdjustment);
	DDV_MinMaxFloat(pDX, C.SurfaceAdjustment, 5.f, 100.f);
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
	DDX_Text(pDX, IDC_EC_LIMITERDELAY, C.LimiterDelay);
	DDV_MinMaxUInt(pDX, C.LimiterDelay, 0, 10000);
	DDX_Text(pDX, IDC_EC_TOPCLCONTRAST, C.TopClusterParam);
	DDV_MinMaxUInt(pDX, C.TopClusterParam, 0, 32767);
	DDX_Text(pDX, IDC_EC_TOPCLTHRESHOLD, C.TopClusterThreshold);
	DDV_MinMaxUInt(pDX, C.TopClusterThreshold, 1, 10000);
	DDX_Text(pDX, IDC_EC_TOPEXPCLUSTERS, C.TopExpectedClusters);
	DDV_MinMaxUInt(pDX, C.TopExpectedClusters, 0, 10000);
	DDX_Text(pDX, IDC_EC_TOPCLUSTERSFLUCT, C.TopClustersFluctuation);
	DDV_MinMaxUInt(pDX, C.TopClustersFluctuation, 0, 1000);
	DDX_Text(pDX, IDC_EC_TOPCLUSTERSMINAREA, C.TopClustersMinArea);
	DDV_MinMaxUInt(pDX, C.TopClustersMinArea, 1, 64);
	DDX_Text(pDX, IDC_EC_VACC, C.VAcc);
	DDV_MinMaxFloat(pDX, C.VAcc, 10.f, 1.e+007f);
	DDX_Text(pDX, IDC_EC_VLAYERS, C.VLayers);
	DDV_MinMaxUInt(pDX, C.VLayers, 1, 200);
	DDX_Text(pDX, IDC_EC_VINACTIVELAYERS, C.VInactiveLayers);
	DDV_MinMaxUInt(pDX, C.VInactiveLayers, 0, 8);
	DDX_Text(pDX, IDC_EC_VMINLAYERS, C.MinValidLayers);
	DDV_MinMaxUInt(pDX, C.MinValidLayers, 1, 200);
	DDX_Text(pDX, IDC_EC_VBASESPEED, C.VBaseSpeed);
	DDV_MinMaxFloat(pDX, C.VBaseSpeed, 1.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_VSPEED, C.VSpeed);
	DDV_MinMaxFloat(pDX, C.VSpeed, 1.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_TOPVSTEP, C.TopStep);
	DDV_MinMaxFloat(pDX, C.TopStep, 1.f, 200.f);
	DDX_Text(pDX, IDC_EC_BOTTOMVSTEP, C.BottomStep);
	DDV_MinMaxFloat(pDX, C.BottomStep, 1.f, 200.f);
	DDX_Text(pDX, IDC_EC_VTOL, C.VTol);
	DDV_MinMaxFloat(pDX, C.VTol, 0.1f, 100.f);
	DDX_Text(pDX, IDC_EC_SHRINKAGE, C.Shrinkage);
	DDV_MinMaxFloat(pDX, C.Shrinkage, 0.5f, 10.f);
	DDX_Text(pDX, IDC_EC_XFIELDS, C.TemplateXFields);
	DDV_MinMaxUInt(pDX, C.TemplateXFields, 1, 100);
	DDX_Text(pDX, IDC_EC_YFIELDS, C.TemplateYFields);
	DDV_MinMaxUInt(pDX, C.TemplateYFields, 1, 100);
	DDX_Text(pDX, IDC_EC_ZSAMPLEINTERVAL, C.ZSampleInterval);
	DDV_MinMaxUInt(pDX, C.ZSampleInterval, 1, 100);
	DDX_Text(pDX, IDC_EC_FOCUSZSAMPLEINTERVAL, C.FocusZSampleInterval);
	DDV_MinMaxUInt(pDX, C.FocusZSampleInterval, 1, 100);
	DDX_Text(pDX, IDC_EC_XYZMOTIONDURATION, C.XYZMotionDuration);
	DDV_MinMaxUInt(pDX, C.XYZMotionDuration, 0, 1000);
	DDX_Text(pDX, IDC_EC_ZSCANDURATION, C.ZScanDuration);
	DDV_MinMaxUInt(pDX, C.ZScanDuration, 0, 1000);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_LOCKONBASE, OnLockOnBase)
	ON_BN_CLICKED(IDC_EC_LOCKONCENTER, OnLockOnCenter)
	ON_BN_CLICKED(IDC_EC_LOCKONCENTERVALLEY, OnLockOnCenterValley)
	ON_BN_CLICKED(IDC_EC_SCANBOTHINFIELD, OnScanBothInField)
	ON_BN_CLICKED(IDC_EC_SCANBOTHTWOSIDES, OnScanBothTwoSides)
	ON_BN_CLICKED(IDC_EC_SCANBOTTOM, OnScanBottom)
	ON_BN_CLICKED(IDC_EC_SCANTOP, OnScanTop)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_EC_COMPUTEZSAMPLES, OnComputeZSamples)
	ON_MESSAGE(WM_CTLCOLORSTATIC, OnCtlColorStatic)
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
		case FOCUS_LOCK_CENTERVALLEY:			GetDlgItem(IDC_EC_LOCKONCENTERVALLEY)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;

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

void CEditConfig::OnLockOnCenterValley() 
{
	// TODO: Add your control notification handler code here
	C.FocusLockModel = FOCUS_LOCK_CENTERVALLEY;
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

LRESULT CEditConfig::OnCtlColorStatic(WPARAM wp, LPARAM lp)
{
	HWND hWnd = (HWND)lp;
	HDC hdc = (HDC)wp;
	if (hWnd == GetDlgItem(IDC_EC_TEST_SCANZSAMPLES)->m_hWnd)
	{
		if (WarningScanSamples)
		{
			::SetTextColor(hdc, RGB(255, 0, 0));
			::SetBkColor(hdc, GetSysColor(COLOR_3DFACE));
			return (LRESULT)BkBrush;
			}
		else return FALSE;
		}
	else if (hWnd == GetDlgItem(IDC_EC_TEST_FOCUSZSAMPLES)->m_hWnd)
	{
		if (WarningFocusSamples) 
		{
			::SetTextColor(hdc, RGB(255, 0, 0));
			::SetBkColor(hdc, GetSysColor(COLOR_3DFACE));
			return (LRESULT)BkBrush;
			}
		else return FALSE;
		}
	return FALSE;
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

void CEditConfig::OnComputeZSamples() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	static char tempstr[128];
	int maxsamples;

	if (iSt2)
	{
		iSt2->GetMaxZScanZSamples(&maxsamples);
		sprintf(tempstr, "Max Z samples = %d", maxsamples);
		GetDlgItem(IDC_EC_TEST_MAXZSAMPLES)->SetWindowText(tempstr);
		};
	sprintf(tempstr, "Scan samples = %d (%.2f\xb5m/smp)", C.ScanZSamples(), C.DAQSpeed(true) * C.ZSampleInterval *.001f);
	WarningScanSamples = (!iSt2 || (C.ScanZSamples() > maxsamples));
	GetDlgItem(IDC_EC_TEST_SCANZSAMPLES)->SetWindowText(tempstr);	
	sprintf(tempstr, "Focus samples = %d (%.2f\xb5m/smp)", C.FocusZSamples(), C.DAQSpeed(true) * C.FocusZSampleInterval * .001f);
	WarningFocusSamples = (!iSt2 || (C.FocusZSamples() > maxsamples));
	GetDlgItem(IDC_EC_TEST_FOCUSZSAMPLES)->SetWindowText(tempstr);
}

void CEditConfig::OnOK() 
{
	// TODO: Add extra validation here
	
	UpdateData();
	if (C.ThicknessTolerance > C.FocusTolerance)
		MessageBox("Thickness tolerance must be smaller than Focus tolerance", "Error", MB_ICONWARNING | MB_OK);
	else
		CDialog::OnOK();
}

