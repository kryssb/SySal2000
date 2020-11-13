
// DlgEditConfig.cpp : implementation file
//
#define _CRT_SECURE_NO_DEPRECATE //disable deprecation warnings

#include <afxdlgs.h>
#include "stdafx.h"
#include "resource.h"

#include "DlgEditConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditConfig dialog


CDlgEditConfig::CDlgEditConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditConfig)
	m_HorizTolerance           =     15.0f ;
	m_LongDistAcc              =    500.0f ;
	m_LongDistSpeed            =  20000.0f ;
	m_ShortDistAcc             =    200.0f ;
	m_ShortDistSpeed           =    500.0f ;
	m_TimeOut                  =   5000.0f ;
	m_VertTolerance            =     15.0f ;
	m_VertAcc                  =      0.0f ;
	m_ZSetSpeed                =   5000.0f ;
	m_TotalThickness           =    300.0f ;
	m_BinningSize              =     16    ;
	m_GreyLevelSampleFraction  =      0.1f ;
	m_StripSamplingDistance    =    100.0f ;
	m_MaxStripCandidates       =     10    ;
	m_StripPeakThreshold       =     32    ;
	m_ScanTransverseTolerance  =   1000.0f ;
	m_SettlingTime             =    100    ;
	m_StripWidth               =     50.0f ;
   m_FramesPerSecond          =    376    ;
	m_ClusteringParameter      =      0    ;
	m_MaxClusters              =  10000    ;
	m_Diameter                 =     70.0f ;
	m_DiameterTolerance        =     15.0f ;
	m_MaxEllipticity           =      0.1f ;
	m_FocusSpeed               =    150.0f ;
	m_FocusStroke              =     40.0f ;
	m_CenterTolerance          =    200.0f ;

	m_SheetIsRotatedBy180Deg   = false  ;
	m_SearchFirstMark          = TRUE   ;
   m_ForceLateralMark         = FALSE  ;
   m_PauseIfCloneNotFound     = FALSE  ;

	m_RecoveryFileName         = _T("") ;
	m_FIRString                = _T("2,2,0,0,-1,-1,-1,-1,-1,-1,-1,-1,0,0,2,2");

	//}}AFX_DATA_INIT
}


void CDlgEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditConfig)
	DDX_Text(pDX, IDC_EC_HORZTOL, m_HorizTolerance);
	DDV_MinMaxFloat(pDX, m_HorizTolerance, 1.f, 100.f);
	DDX_Text(pDX, IDC_EC_LONGDISTACC, m_LongDistAcc);
	DDV_MinMaxFloat(pDX, m_LongDistAcc, 50.f, 100000.f);
	DDX_Text(pDX, IDC_EC_LONGDISTSPEED, m_LongDistSpeed);
	DDV_MinMaxFloat(pDX, m_LongDistSpeed, 10.f, 100000.f);
	DDX_Text(pDX, IDC_EC_RECOVERYFILE, m_RecoveryFileName);
	DDV_MaxChars(pDX, m_RecoveryFileName, 63);
	DDX_Check(pDX, IDC_EC_SHEETROTATEDBY180, m_SheetIsRotatedBy180Deg);
	DDX_Text(pDX, IDC_EC_SHORTDISTACC, m_ShortDistAcc);
	DDV_MinMaxFloat(pDX, m_ShortDistAcc, 100.f, 100000.f);
	DDX_Text(pDX, IDC_EC_SHORTDISTSPEED, m_ShortDistSpeed);
	DDV_MinMaxFloat(pDX, m_ShortDistSpeed, 10.f, 100000.f);
	DDX_Text(pDX, IDC_EC_TIMEOUT, m_TimeOut);
	DDV_MinMaxFloat(pDX, m_TimeOut, 1.f, 100000.f);
	DDX_Text(pDX, IDC_EC_VERTTOL, m_VertTolerance);
	DDV_MinMaxFloat(pDX, m_VertTolerance, 0.5f, 100.f);
	DDX_Text(pDX, IDC_EC_VERTACC, m_VertAcc);
	DDV_MinMaxFloat(pDX, m_VertAcc, 50.f, 100000.f);
	DDX_Text(pDX, IDC_EC_ZSETSPEED, m_ZSetSpeed);
	DDV_MinMaxFloat(pDX, m_ZSetSpeed, 10.f, 100000.f);
	DDX_Check(pDX, IDC_EC_SEARCHFIRSTMARK, m_SearchFirstMark);
	DDX_Text(pDX, IDC_EC_TOTALTHICKNESS, m_TotalThickness);
	DDV_MinMaxFloat(pDX, m_TotalThickness, 100.f, 800.f);
	DDX_Text(pDX, IDC_EC_BINSIZE, m_BinningSize);
	DDV_MinMaxUInt(pDX, m_BinningSize, 1, 32);
	DDX_Text(pDX, IDC_EC_FIRSTRING, m_FIRString);
	DDV_MaxChars(pDX, m_FIRString, 63);
	DDX_Text(pDX, IDC_EC_GREYSAMPLE, m_GreyLevelSampleFraction);
	DDX_Text(pDX, IDC_EC_STRIPSAMPLINGDISTANCE, m_StripSamplingDistance);
	DDX_Text(pDX, IDC_EC_MAXSTRIPCANDIDATES, m_MaxStripCandidates);
	DDV_MinMaxUInt(pDX, m_MaxStripCandidates, 2, 100);
	DDX_Text(pDX, IDC_EC_PEAKTHRESHOLD, m_StripPeakThreshold);
	DDV_MinMaxUInt(pDX, m_StripPeakThreshold, 5, 50000);
	DDX_Text(pDX, IDC_EC_SCANTRANSVTOL, m_ScanTransverseTolerance);
	DDV_MinMaxFloat(pDX, m_ScanTransverseTolerance, 10.f, 10000.f);
	DDX_Text(pDX, IDC_EC_SETTLINGTIME, m_SettlingTime);
	DDV_MinMaxUInt(pDX, m_SettlingTime, 1, 1000);
	DDX_Text(pDX, IDC_EC_STRIPWIDTH, m_StripWidth);
	DDV_MinMaxFloat(pDX, m_StripWidth, 5.f, 150.f);

   DDX_Text(pDX, IDC_EC_FRAMERATE   , m_FramesPerSecond     );
   DDX_Text(pDX, IDC_EC_VPPROGRAM   , m_ClusteringParameter );
   DDX_Text(pDX, IDC_EC_MAXCLUSTERS , m_MaxClusters         );
   DDX_Text(pDX, IDC_EC_DIAMETER    , m_Diameter            );
   DDX_Text(pDX, IDC_EC_DIAMETERTOL , m_DiameterTolerance   );
   DDX_Text(pDX, IDC_EC_ECCENTRICITY, m_MaxEllipticity      );
   DDX_Text(pDX, IDC_EC_FOCUSSPEED  , m_FocusSpeed          );
   DDX_Text(pDX, IDC_EC_FOCUSPATHLENGTH , m_FocusStroke     );
   DDX_Text(pDX, IDC_EC_CENTERTOL   , m_CenterTolerance     );

   DDX_Check(pDX, IDC_EC_FORCELATERALMARKFINDING , m_ForceLateralMark     );
   DDX_Check(pDX, IDC_EC_PAUSENOTFOUNDCLONE      , m_PauseIfCloneNotFound );


	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgEditConfig)
	ON_BN_CLICKED(IDC_EC_SELRECOVERYFILE, OnSelRecoveryFile)
	ON_EN_KILLFOCUS(IDC_EC_FIRSTRING, OnLeaveFIRString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditConfig message handlers

void CDlgEditConfig::SetConfig(FlexMapData &F)
{	
	m_BinningSize              = F.BinningSize               ;
	m_FIRString                = F.FIRString                 ;
	m_GreyLevelSampleFraction  = F.GreyLevelSampleFraction   ;
	m_StripSamplingDistance    = F.StripSamplingDistance     ;
	m_MaxStripCandidates       = F.MaxStripCandidates        ;
	m_StripPeakThreshold       = F.StripPeakThreshold        ;
	m_ScanTransverseTolerance  = F.ScanTransverseTolerance   ;
	m_SettlingTime             = F.SettlingTime              ;
	m_StripWidth               = F.StripWidth                ;
	m_ZSetSpeed                = F.ZSetSpeed                 ;
	m_HorizTolerance           = F.HorizTolerance            ;
	m_LongDistAcc              = F.LongDistAcc               ;
	m_LongDistSpeed            = F.LongDistSpeed             ;
	m_RecoveryFileName         = F.RecoveryFileName          ;
	m_SheetIsRotatedBy180Deg   = F.SheetIsRotatedBy180Deg    ;
	m_ShortDistAcc             = F.ShortDistAcc              ;
	m_ShortDistSpeed           = F.ShortDistSpeed            ;
	m_TimeOut                  = F.TimeOut                   ;
	m_VertTolerance            = F.VertTolerance             ;
	m_VertAcc                  = F.VertAcc                   ;
	m_SearchFirstMark          = F.SearchFirstMark           ;
	m_TotalThickness           = F.TotalThickness            ;

   m_FramesPerSecond          = F.FramesPerSecond          ;
   m_ClusteringParameter      = F.ClusteringParameter      ;
   m_MaxClusters              = F.MaxClusters              ;
   m_Diameter                 = F.Diameter                 ;
   m_DiameterTolerance        = F.DiameterTolerance        ;
   m_MaxEllipticity           = F.MaxEllipticity           ;
   m_FocusSpeed               = F.FocusSpeed               ;
   m_FocusStroke              = F.FocusStroke              ;
   m_CenterTolerance          = F.CenterTolerance          ;

   m_ForceLateralMark         = F.ForceLateralMark         ;
//   m_PauseIfCloneNotFound     = F.PauseIfCloneNotFound     ;

}

void CDlgEditConfig::GetConfig(FlexMapData &F)
{	
	F.BinningSize              = m_BinningSize               ;
	
   strcpy(F.FIRString, m_FIRString.GetBuffer(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	m_FIRString.ReleaseBuffer();
	
   F.GreyLevelSampleFraction  = m_GreyLevelSampleFraction   ;
	F.StripSamplingDistance    = m_StripSamplingDistance     ;
	F.MaxStripCandidates       = m_MaxStripCandidates        ;
	F.StripPeakThreshold       = m_StripPeakThreshold        ;
	F.ScanTransverseTolerance  = m_ScanTransverseTolerance   ;
	F.SettlingTime             = m_SettlingTime              ;
	F.StripWidth               = m_StripWidth                ;
	F.ZSetSpeed                = m_ZSetSpeed                 ;
	F.HorizTolerance           = m_HorizTolerance            ;
	F.LongDistAcc              = m_LongDistAcc               ;
	F.LongDistSpeed            = m_LongDistSpeed             ;

	strcpy(F.RecoveryFileName, m_RecoveryFileName.GetBuffer(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	m_RecoveryFileName.ReleaseBuffer();
	
   F.SheetIsRotatedBy180Deg   = m_SheetIsRotatedBy180Deg ;
	F.ShortDistAcc             = m_ShortDistAcc           ;
	F.ShortDistSpeed           = m_ShortDistSpeed         ;
	F.TimeOut                  = m_TimeOut                ;
	F.VertTolerance            = m_VertTolerance          ;
	F.VertAcc                  = m_VertAcc                ;
	F.SearchFirstMark          = m_SearchFirstMark        ;
	F.TotalThickness           = m_TotalThickness         ;

   F.FramesPerSecond          = m_FramesPerSecond        ;
   F.ClusteringParameter      = m_ClusteringParameter    ;
   F.MaxClusters              = m_MaxClusters            ;
   F.Diameter                 = m_Diameter               ;
   F.DiameterTolerance        = m_DiameterTolerance      ;
   F.MaxEllipticity           = m_MaxEllipticity         ;
   F.FocusSpeed               = m_FocusSpeed             ;
   F.FocusStroke              = m_FocusStroke            ;
   F.CenterTolerance          = m_CenterTolerance        ;

   F.ForceLateralMark         = m_ForceLateralMark       ;
//   F.PauseIfCloneNotFound     = m_PauseIfCloneNotFound   ;

}

void CDlgEditConfig::OnLeaveFIRString() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int FIR[MAXFIRSIZE];
	int FIRSize = MAXFIRSIZE;
	if (FlexMapData::StringToFIR(m_FIRString.GetBuffer(1), &FIRSize, FIR) == false)
	{
		MessageBox("FIR items must be integers separated by comma (',').", "Input Error", MB_OK);
		GetDlgItem(IDC_EC_FIRSTRING)->SetFocus();
		}
	m_FIRString.ReleaseBuffer();	
}

void CDlgEditConfig::OnSelRecoveryFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(false, "map", m_RecoveryFileName, OFN_PATHMUSTEXIST | OFN_EXPLORER, "Map Files (*.map)|*.map|All Files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_RecoveryFileName = MyDlg.GetPathName().Left(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		UpdateData(false);
		};	
}
