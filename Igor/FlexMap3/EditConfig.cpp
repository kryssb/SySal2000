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
	m_Diameter = 70.0f;
	m_DiameterTolerance = 15.0f;
	m_Ellipticity = 0.1f;
	m_FieldMapFileName = _T("");
	m_FocusSpeed = 150.0f;
	m_FocusStroke = 150.0f;
	m_HorizTolerance = 15.0f;
	m_LongDistAcc = 500.0f;
	m_LongDistSpeed = 10000.0f;
	m_MaxClusters = 10000;
	m_RecoveryFileName = _T("");
	m_SheetIsRotatedBy180Deg = FALSE;
	m_ShortDistAcc = 200.0f;
	m_ShortDistSpeed = 500.0f;
	m_TimeOut = 5000.0f;
	m_VertTolerance = 15.0f;
	m_CenterTolerance = 200.0f;
	m_ClusteringParameter = 0;
	m_FramesPerSecond = 60.0f;
	m_VertAcc = 0.0f;
	m_ZSetSpeed = 5000.0f;
	m_SearchFirstMark = TRUE;
	m_TotalThickness = 300.0f;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Text(pDX, IDC_EC_DIAMETER, m_Diameter);
	DDV_MinMaxFloat(pDX, m_Diameter, 5.f, 2000.f);
	DDX_Text(pDX, IDC_EC_DIAMETERTOL, m_DiameterTolerance);
	DDV_MinMaxFloat(pDX, m_DiameterTolerance, 5.f, 2000.f);
	DDX_Text(pDX, IDC_EC_ELLIPTICITY, m_Ellipticity);
	DDV_MinMaxFloat(pDX, m_Ellipticity, 0.f, 100.f);
	DDX_Text(pDX, IDC_EC_FIELDMAPFILE, m_FieldMapFileName);
	DDV_MaxChars(pDX, m_FieldMapFileName, 63);
	DDX_Text(pDX, IDC_EC_FOCUSSPEED, m_FocusSpeed);
	DDV_MinMaxFloat(pDX, m_FocusSpeed, 10.f, 10000.f);
	DDX_Text(pDX, IDC_EC_FOCUSSTROKE, m_FocusStroke);
	DDV_MinMaxFloat(pDX, m_FocusStroke, 10.f, 2000.f);
	DDX_Text(pDX, IDC_EC_HORZTOL, m_HorizTolerance);
	DDV_MinMaxFloat(pDX, m_HorizTolerance, 1.f, 100.f);
	DDX_Text(pDX, IDC_EC_LONGDISTACC, m_LongDistAcc);
	DDV_MinMaxFloat(pDX, m_LongDistAcc, 50.f, 100000.f);
	DDX_Text(pDX, IDC_EC_LONGDISTSPEED, m_LongDistSpeed);
	DDV_MinMaxFloat(pDX, m_LongDistSpeed, 10.f, 100000.f);
	DDX_Text(pDX, IDC_EC_MAXCLUSTERS, m_MaxClusters);
	DDV_MinMaxUInt(pDX, m_MaxClusters, 100, 10000);
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
	DDX_Text(pDX, IDC_EC_CENTERTOL, m_CenterTolerance);
	DDV_MinMaxFloat(pDX, m_CenterTolerance, 1.f, 1000.f);
	DDX_Text(pDX, IDC_EC_CLUSTERPARAM, m_ClusteringParameter);
	DDV_MinMaxUInt(pDX, m_ClusteringParameter, 0, 32767);
	DDX_Text(pDX, IDC_EC_FRAMESPERSECOND, m_FramesPerSecond);
	DDV_MinMaxFloat(pDX, m_FramesPerSecond, 1.f, 10000.f);
	DDX_Text(pDX, IDC_EC_VERTACC, m_VertAcc);
	DDV_MinMaxFloat(pDX, m_VertAcc, 50.f, 100000.f);
	DDX_Text(pDX, IDC_EC_ZSETSPEED, m_ZSetSpeed);
	DDV_MinMaxFloat(pDX, m_ZSetSpeed, 10.f, 100000.f);
	DDX_Check(pDX, IDC_EC_SEARCHFIRSTMARK, m_SearchFirstMark);
	DDX_Text(pDX, IDC_EC_TOTALTHICKNESS, m_TotalThickness);
	DDV_MinMaxFloat(pDX, m_TotalThickness, 100.f, 800.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_SELFIELDMAPFILE, OnSelFieldMapFile)
	ON_BN_CLICKED(IDC_EC_SELRECOVERYFILE, OnSelRecoveryFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::SetConfig(FlexMapData &F)
{	
	m_CenterTolerance = F.CenterTolerance;
	m_Diameter = F.Diameter;
	m_DiameterTolerance = F.DiameterTolerance;
	m_Ellipticity = F.Ellipticity;
	m_FieldMapFileName = F.FieldMapFileName;
	m_FocusSpeed = F.FocusSpeed;
	m_FocusStroke = F.FocusStroke;
	m_ZSetSpeed = F.ZSetSpeed;
	m_FramesPerSecond = F.FramesPerSecond;
	m_ClusteringParameter = F.ClusteringParameter;
	m_HorizTolerance = F.HorizTolerance;
	m_LongDistAcc = F.LongDistAcc;
	m_LongDistSpeed = F.LongDistSpeed;
	m_MaxClusters = F.MaxClusters;
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
	F.CenterTolerance = m_CenterTolerance;
	F.Diameter = m_Diameter;
	F.DiameterTolerance = m_DiameterTolerance;
	F.Ellipticity = m_Ellipticity;
	strcpy(F.FieldMapFileName, m_FieldMapFileName.GetBuffer(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	m_FieldMapFileName.ReleaseBuffer();
	F.FocusSpeed = m_FocusSpeed;
	F.FocusStroke = m_FocusStroke;
	F.ZSetSpeed = m_ZSetSpeed;
	F.FramesPerSecond = m_FramesPerSecond;
	F.ClusteringParameter = m_ClusteringParameter;
	F.HorizTolerance = m_HorizTolerance;
	F.LongDistAcc = m_LongDistAcc;
	F.LongDistSpeed = m_LongDistSpeed;
	F.MaxClusters = m_MaxClusters;
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



void CEditConfig::OnSelFieldMapFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "path", m_FieldMapFileName, OFN_FILEMUSTEXIST | OFN_EXPLORER, "Path Files (*.path)|*.path|All Files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_FieldMapFileName = MyDlg.GetPathName().Left(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		UpdateData(FALSE);
		};
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
