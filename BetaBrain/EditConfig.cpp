// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditConfig.h"
#include <afxdlgs.h>

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
	m_Path = _T("");
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Text(pDX, IDC_EC_PATH, m_Path);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_EC_MAXCLUSTERS, m_SD.ModD.MaxClusters);
	DDV_MinMaxUInt(pDX, m_SD.ModD.MaxClusters, 100, 10000000);
	DDX_Text(pDX, IDC_EC_MAXFLATTRACKS, m_SD.ModD.MaxFlatTracks);
	DDV_MinMaxUInt(pDX, m_SD.ModD.MaxFlatTracks, 10, 1000000);
	DDX_Text(pDX, IDC_EC_MAXTRACKS, m_SD.ModD.MaxTracks);
	DDV_MinMaxUInt(pDX, m_SD.ModD.MaxTracks, 100, 1000000);

	DDX_Text(pDX, IDC_EC_BASETHICK, m_SD.EmuD.BaseThickness);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.BaseThickness, 0.f, 10000.f);
	DDX_Text(pDX, IDC_EC_BOTTOMTHICK, m_SD.EmuD.BottomThickness);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.TopThickness, 1.f, 1000.f);
	DDX_Text(pDX, IDC_EC_TOPTHICK, m_SD.EmuD.TopThickness);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.TopThickness, 1.f, 1000.f);
	DDX_Text(pDX, IDC_EC_DEPTHCOHERLEN, m_SD.EmuD.DepthCoherenceLength);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.DepthCoherenceLength, 1000.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_DISTCELLSIZE, m_SD.EmuD.DistortionCellSize);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.DistortionCellSize, 1000.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_HEIGHT, m_SD.EmuD.Height);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.Height, 10000.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_WIDTH, m_SD.EmuD.Width);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.Width, 1000.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_SHRINKAGE, m_SD.EmuD.Shrinkage);
	DDV_MinMaxFloat(pDX, m_SD.EmuD.Shrinkage, 0.5f, 5.f);

	DDX_Text(pDX, IDC_EC_BASECROSSINGSPEED, m_SD.StageD.BaseCrossingSpeed);
	DDV_MinMaxFloat(pDX, m_SD.StageD.BaseCrossingSpeed, 1.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_SCANNINGSPEED, m_SD.StageD.ScanningSpeed);
	DDV_MinMaxFloat(pDX, m_SD.StageD.ScanningSpeed, 1.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_SCANNINGSTEP, m_SD.StageD.ScanningStep);
	DDV_MinMaxFloat(pDX, m_SD.StageD.ScanningStep, 0.1f, 100.f);
	DDX_Text(pDX, IDC_EC_ZREWINDSPEED, m_SD.StageD.RewindSpeed);
	DDV_MinMaxFloat(pDX, m_SD.StageD.RewindSpeed, 10.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_HORIZSPEED, m_SD.StageD.HorizontalSpeed);
	DDV_MinMaxFloat(pDX, m_SD.StageD.HorizontalSpeed, 10.f, 1.e+006f);
	DDX_Text(pDX, IDC_EC_SHORTDISTACC, m_SD.StageD.ShortDistAcc);
	DDV_MinMaxFloat(pDX, m_SD.StageD.ShortDistAcc, 10.f, 1.e+009f);
	DDX_Text(pDX, IDC_EC_LONGDISTACC, m_SD.StageD.LongDistAcc);
	DDV_MinMaxFloat(pDX, m_SD.StageD.LongDistAcc, 1.f, 1.e+009f);
	DDX_Text(pDX, IDC_EC_FOCUSTOL, m_SD.StageD.FocusTolerance);
	DDV_MinMaxFloat(pDX, m_SD.StageD.FocusTolerance, 1.f, 10000.f);
	DDX_Text(pDX, IDC_EC_THICKNESSTOL, m_SD.StageD.ThicknessTolerance);
	DDV_MinMaxFloat(pDX, m_SD.StageD.ThicknessTolerance, 1.f, 1000.f);
	DDX_Text(pDX, IDC_EC_SLOWDOWNLEN, m_SD.StageD.SlowdownLength);
	DDV_MinMaxFloat(pDX, m_SD.StageD.SlowdownLength, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_RELAXTIME, m_SD.StageD.RelaxTime);
	DDV_MinMaxFloat(pDX, m_SD.StageD.RelaxTime, 0.f, 10000.f);
	DDX_Text(pDX, IDC_EC_WAITLIMRESET, m_SD.StageD.WaitForLimiterResetTime);
	DDV_MinMaxFloat(pDX, m_SD.StageD.WaitForLimiterResetTime, 0.f, 100000.f);
	DDX_Text(pDX, IDC_EC_XSTEP, m_SD.StageD.XStep);
	DDV_MinMaxFloat(pDX, m_SD.StageD.XStep, 1.f, 100000.f);
	DDX_Text(pDX, IDC_EC_YSTEP, m_SD.StageD.YStep);
	DDV_MinMaxFloat(pDX, m_SD.StageD.YStep, 1.f, 100000.f);
	DDX_Text(pDX, IDC_EC_XTOLERANCE, m_SD.StageD.XTolerance);
	DDV_MinMaxFloat(pDX, m_SD.StageD.XTolerance, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_YTOLERANCE, m_SD.StageD.YTolerance);
	DDV_MinMaxFloat(pDX, m_SD.StageD.YTolerance, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_ZACC, m_SD.StageD.ZAcc);
	DDV_MinMaxFloat(pDX, m_SD.StageD.ZAcc, 1.f, 1.e+009f);
	DDX_Text(pDX, IDC_EC_ZSTATICTOLERANCE, m_SD.StageD.ZStaticTolerance);
	DDV_MinMaxFloat(pDX, m_SD.StageD.ZStaticTolerance, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_ZTOLERANCE, m_SD.StageD.ZTolerance);
	DDV_MinMaxFloat(pDX, m_SD.StageD.ZTolerance, 0.f, 100.f);

	DDX_Check(pDX, IDC_EC_AUTOLIGHTCONTROL, m_SD.OptD.AutoLightControl);
	DDX_Text(pDX, IDC_EC_MINLIGHT, m_SD.OptD.MinLight);
	DDV_MinMaxInt(pDX, m_SD.OptD.MinLight, 0, 32767);
	DDX_Text(pDX, IDC_EC_MAXLIGHT, m_SD.OptD.MaxLight);
	DDV_MinMaxInt(pDX, m_SD.OptD.MaxLight, 0, 32767);
	DDX_Text(pDX, IDC_EC_LIGHTINCREMENT, m_SD.OptD.LightIncrement);
	DDV_MinMaxInt(pDX, m_SD.OptD.LightIncrement, 0, 32767);
	DDX_Text(pDX, IDC_EC_TARGETGRAYLEV, m_SD.OptD.TargetGrayLev);
	DDV_MinMaxInt(pDX, m_SD.OptD.TargetGrayLev, 0, 255);
	DDX_Text(pDX, IDC_EC_MINGRAYLEV, m_SD.OptD.MinGrayLev);
	DDV_MinMaxInt(pDX, m_SD.OptD.MinGrayLev, 0, 255);
	DDX_Text(pDX, IDC_EC_LAMPDELAY, m_SD.OptD.LampDelay);
	DDV_MinMaxInt(pDX, m_SD.OptD.LampDelay, 0, 10000);
	DDX_Check(pDX, IDC_EC_CORRECTPREDS, m_SD.OptD.CorrectPredictions);
	DDX_Text(pDX, IDC_EC_MINSAMPLE, m_SD.OptD.MinSample);
	DDV_MinMaxUInt(pDX, m_SD.OptD.MinSample, 10, 10000);
	DDX_Check(pDX, IDC_EC_CENTERSB, m_SD.OptD.CenterScanBack);
	DDX_Text(pDX, IDC_EC_XCENTERTOL, m_SD.OptD.XCenterTol);
	DDV_MinMaxFloat(pDX, m_SD.OptD.XCenterTol, 0.f, 1000.f);
	DDX_Text(pDX, IDC_EC_YCENTERTOL, m_SD.OptD.YCenterTol);
	DDV_MinMaxFloat(pDX, m_SD.OptD.YCenterTol, 0.f, 1000.f);
	DDX_Check(pDX, IDC_EC_PAUSEEACHFIELD, m_SD.OptD.PauseEachField);

	DDV_MaxChars(pDX, m_Path, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	DDX_Text(pDX, IDC_EC_XFIELDS, m_SD.PathD.XFields);
	DDV_MinMaxUInt(pDX, m_SD.PathD.XFields, 1, 1000);
	DDX_Text(pDX, IDC_EC_YFIELDS, m_SD.PathD.YFields);
	DDV_MinMaxUInt(pDX, m_SD.PathD.YFields, 1, 1000);

	DDX_Check(pDX, IDC_EC_CHKBOTTOM, m_SD.SeekerD.CheckBottom);
	DDX_Check(pDX, IDC_EC_CHKTOP, m_SD.SeekerD.CheckTop);
	DDX_Text(pDX, IDC_EC_POSTOL, m_SD.SeekerD.PosTolerance);
	DDV_MinMaxFloat(pDX, m_SD.SeekerD.PosTolerance, 0.f, 1.e+006f);
	DDX_Check(pDX, IDC_EC_ZONESCANNING, m_SD.SeekerD.ZoneScanning);
	DDX_Text(pDX, IDC_EC_ZONEXFIELDS, m_SD.SeekerD.ZoneXFields);
	DDV_MinMaxUInt(pDX, m_SD.SeekerD.ZoneXFields, 1, 1000);
	DDX_Text(pDX, IDC_EC_ZONEYFIELDS, m_SD.SeekerD.ZoneYFields);
	DDV_MinMaxUInt(pDX, m_SD.SeekerD.ZoneYFields, 1, 1000);

	DDX_Text(pDX, IDC_EC_TOP_CLUSTERCONTRAST, m_SD.TopD.ClusterContrast);
	DDV_MinMaxUInt(pDX, m_SD.TopD.ClusterContrast, 0, 65535);
	DDX_Text(pDX, IDC_EC_TOP_CLUSTERTHRESH, m_SD.TopD.ClusterThreshold);
	DDV_MinMaxUInt(pDX, m_SD.TopD.ClusterThreshold, 0, 1000000);
	DDX_Text(pDX, IDC_EC_TOP_MAXFLATSTRIPS, m_SD.TopD.MaxFlatStripsPerTrack);
	DDV_MinMaxUInt(pDX, m_SD.TopD.MaxFlatStripsPerTrack, 10, 1000);
	DDX_Text(pDX, IDC_EC_TOP_MAXLAYERS, m_SD.TopD.MaxLayers);
	DDV_MinMaxUInt(pDX, m_SD.TopD.MaxLayers, 1, 100);
	DDX_Text(pDX, IDC_EC_TOP_MAXPIX, m_SD.TopD.PixMax);
	DDV_MinMaxUInt(pDX, m_SD.TopD.PixMax, 0, 1000000);
	DDX_Text(pDX, IDC_EC_TOP_STARTLAYER, m_SD.TopD.StartLayer);
	DDV_MinMaxUInt(pDX, m_SD.TopD.StartLayer, 0, 100);
	DDX_Text(pDX, IDC_EC_TOP_MINLAYERS, m_SD.TopD.EndLayer);
	DDV_MinMaxUInt(pDX, m_SD.TopD.EndLayer, 1, 100);
	DDX_Text(pDX, IDC_EC_TOP_MINPIX, m_SD.TopD.PixMin);
	DDV_MinMaxUInt(pDX, m_SD.TopD.PixMin, 0, 1000000);

	DDX_Text(pDX, IDC_EC_BOTTOM_CLUSTERCONTRAST, m_SD.BottomD.ClusterContrast);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.ClusterContrast, 0, 65535);
	DDX_Text(pDX, IDC_EC_BOTTOM_CLUSTERTHRESH, m_SD.BottomD.ClusterThreshold);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.ClusterThreshold, 0, 1000000);
	DDX_Text(pDX, IDC_EC_BOTTOM_MAXFLATSTRIPS, m_SD.BottomD.MaxFlatStripsPerTrack);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.MaxFlatStripsPerTrack, 10, 1000);
	DDX_Text(pDX, IDC_EC_BOTTOM_MAXLAYERS, m_SD.BottomD.MaxLayers);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.MaxLayers, 1, 100);
	DDX_Text(pDX, IDC_EC_BOTTOM_MAXPIX, m_SD.BottomD.PixMax);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.PixMax, 0, 1000000);
	DDX_Text(pDX, IDC_EC_BOTTOM_STARTLAYER, m_SD.BottomD.StartLayer);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.StartLayer, 0, 100);
	DDX_Text(pDX, IDC_EC_BOTTOM_MINLAYERS, m_SD.BottomD.EndLayer);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.EndLayer, 1, 100);
	DDX_Text(pDX, IDC_EC_BOTTOM_MINPIX, m_SD.BottomD.PixMin);
	DDV_MinMaxUInt(pDX, m_SD.BottomD.PixMin, 0, 1000000);

}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_SCANBOTH, OnScanBoth)
	ON_BN_CLICKED(IDC_EC_SCANBOTTOM, OnScanBottom)
	ON_BN_CLICKED(IDC_EC_SCANTOP, OnScanTop)
	ON_BN_CLICKED(IDC_EC_SELPATH, OnSelPath)
	ON_BN_CLICKED(IDC_EC_RESETPATH, OnResetPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers


BOOL CEditConfig::OnInitDialog() 
{
	m_Path = m_SD.PathD.PathFileName;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SendDlgItemMessage(IDC_EC_SCANBOTH, BM_SETCHECK, m_SD.OptD.ScanBoth ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_EC_SCANBOTTOM, BM_SETCHECK, m_SD.OptD.ScanBottom ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_EC_SCANTOP, BM_SETCHECK, m_SD.OptD.ScanTop ? BST_CHECKED : BST_UNCHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CEditConfig::OnScanBoth() 
{
	// TODO: Add your control notification handler code here
	m_SD.OptD.ScanTop = 0;
	m_SD.OptD.ScanBottom = 0;
	m_SD.OptD.ScanBoth = 1;		
}

void CEditConfig::OnScanBottom() 
{
	// TODO: Add your control notification handler code here
	m_SD.OptD.ScanTop = 0;
	m_SD.OptD.ScanBottom = 1;
	m_SD.OptD.ScanBoth = 0;	
}

void CEditConfig::OnScanTop() 
{
	// TODO: Add your control notification handler code here
	m_SD.OptD.ScanTop = 1;
	m_SD.OptD.ScanBottom = 0;
	m_SD.OptD.ScanBoth = 0;
}

void CEditConfig::OnSelPath() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, NULL, m_Path, OFN_EXPLORER, "Path files (*.path)|*.path|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK && MyDlg.GetPathName().GetLength() < SYSAL_MAXCONFIG_ENTRY_VALUE_LEN)
	{
		m_Path = MyDlg.GetPathName();		
		UpdateData(FALSE);
		};
}

void CEditConfig::OnResetPath() 
{
	// TODO: Add your control notification handler code here
	m_Path = "";
	UpdateData(FALSE);
}

void CEditConfig::OnOK() 
{
	// TODO: Add extra validation here
	strncpy(m_SD.PathD.PathFileName, m_Path, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	CDialog::OnOK();
}
