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
	m_HorizTolerance = 15.0f;
	m_LongDistAcc = 500.0f;
	m_LongDistSpeed = 10000.0f;
	m_RecoveryFileName = _T("");
	m_SheetIsRotatedBy180Deg = FALSE;
	m_ShortDistAcc = 200.0f;
	m_ShortDistSpeed = 500.0f;
	m_TimeOut = 5000.0f;
	m_VertTolerance = 15.0f;
	m_VertAcc = 0.0f;
	m_ZSetSpeed = 5000.0f;
	m_SearchFirstMark = TRUE;
	m_TotalThickness = 300.0f;
	m_BinningSize = 16;
	m_FIRString = _T("2,2,0,0,-1,-1,-1,-1,-1,-1,-1,-1,0,0,2,2");
	m_GreyLevelSampleFraction = 0.10f;
	m_InterstripDistTolerance = 100.0f;
	m_MaxStripCandidates = 10;
	m_StripPeakThreshold = 32;
	m_ScanTransverseTolerance = 1000.0f;
	m_SettlingTime = 100;
	m_StripWidth = 50.0f;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
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
	DDX_Text(pDX, IDC_EC_INTERSTRIPDISTTOL, m_InterstripDistTolerance);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_SELRECOVERYFILE, OnSelRecoveryFile)
	ON_EN_KILLFOCUS(IDC_EC_FIRSTRING, OnLeaveFIRString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::SetConfig(FlexMapData &F)
{	
	m_BinningSize = F.BinningSize;
	m_FIRString = F.FIRString;
	m_GreyLevelSampleFraction = F.GreyLevelSampleFraction;
	m_InterstripDistTolerance = F.InterstripDistTolerance;
	m_MaxStripCandidates = F.MaxStripCandidates;
	m_StripPeakThreshold = F.StripPeakThreshold;
	m_ScanTransverseTolerance = F.ScanTransverseTolerance;
	m_SettlingTime = F.SettlingTime;
	m_StripWidth = F.StripWidth;
	m_ZSetSpeed = F.ZSetSpeed;
	m_HorizTolerance = F.HorizTolerance;
	m_LongDistAcc = F.LongDistAcc;
	m_LongDistSpeed = F.LongDistSpeed;
	m_RecoveryFileName = F.RecoveryFileName;
	m_SheetIsRotatedBy180Deg = F.SheetIsRotatedBy180Deg;
	m_ShortDistAcc = F.ShortDistAcc;
	m_ShortDistSpeed = F.ShortDistSpeed;
	m_TimeOut = F.TimeOut;
	m_VertTolerance = F.VertTolerance;
	m_VertAcc = F.VertAcc;
	m_SearchFirstMark = F.SearchFirstMark;
	m_TotalThickness = F.TotalThickness;
}

void CEditConfig::GetConfig(FlexMapData &F)
{	
	F.BinningSize = m_BinningSize;
	strcpy(F.FIRString, m_FIRString.GetBuffer(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	m_FIRString.ReleaseBuffer();
	F.GreyLevelSampleFraction = m_GreyLevelSampleFraction;
	F.InterstripDistTolerance = m_InterstripDistTolerance;
	F.MaxStripCandidates = m_MaxStripCandidates;
	F.StripPeakThreshold = m_StripPeakThreshold;
	F.ScanTransverseTolerance = m_ScanTransverseTolerance;
	F.SettlingTime = m_SettlingTime;
	F.StripWidth = m_StripWidth;
	F.ZSetSpeed = m_ZSetSpeed;
	F.HorizTolerance = m_HorizTolerance;
	F.LongDistAcc = m_LongDistAcc;
	F.LongDistSpeed = m_LongDistSpeed;
	strcpy(F.RecoveryFileName, m_RecoveryFileName.GetBuffer(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	m_RecoveryFileName.ReleaseBuffer();
	F.SheetIsRotatedBy180Deg = m_SheetIsRotatedBy180Deg;
	F.ShortDistAcc = m_ShortDistAcc;
	F.ShortDistSpeed = m_ShortDistSpeed;
	F.TimeOut = m_TimeOut;
	F.VertTolerance = m_VertTolerance;
	F.VertAcc = m_VertAcc;
	F.SearchFirstMark = m_SearchFirstMark;
	F.TotalThickness = m_TotalThickness;
}

void CEditConfig::OnLeaveFIRString() 
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

void CEditConfig::OnSelRecoveryFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, "map", m_RecoveryFileName, OFN_PATHMUSTEXIST | OFN_EXPLORER, "Map Files (*.map)|*.map|All Files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_RecoveryFileName = MyDlg.GetPathName().Left(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		UpdateData(FALSE);
		};	
}
