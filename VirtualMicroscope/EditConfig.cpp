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
	m_MarkFile = _T("");
	m_TksFile = _T("");
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Text(pDX, IDC_MARKFILE, m_MarkFile);
	DDV_MaxChars(pDX, m_MarkFile, 63);
	DDX_Text(pDX, IDC_TKSFILE, m_TksFile);
	DDV_MaxChars(pDX, m_TksFile, 63);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_MAXGRAINS, C.MaxGrains);
	DDX_Text(pDX, IDC_MAXGRAINSIZE, C.MaxGrainSize);
	DDV_MinMaxUInt(pDX, C.MaxGrainSize, 2, 20);
	DDX_Text(pDX, IDC_XY_MANMULT, C.XYSpeedMult);
	DDV_MinMaxFloat(pDX, C.XYSpeedMult, 1.f, 10000.f);
	DDX_Text(pDX, IDC_MINGRAINS, C.MinGrains);
	DDX_Text(pDX, IDC_MINGRAINSIZE, C.MinGrainSize);
	DDV_MinMaxUInt(pDX, C.MinGrainSize, 2, 100);
	DDX_Text(pDX, IDC_VP_FRAMEDELAY, C.FrameDelay);
	DDV_MinMaxUInt(pDX, C.FrameDelay, 0, 8);
	DDX_Text(pDX, IDC_XY_RES, C.XYRes);
	DDV_MinMaxFloat(pDX, C.XYRes, 0.1f, 10.f);
	DDX_Text(pDX, IDC_Z_MANMULT, C.ZSpeedMult);
	DDV_MinMaxFloat(pDX, C.ZSpeedMult, 1.f, 10000.f);
	DDX_Text(pDX, IDC_Z_RES, C.ZRes);
	DDV_MinMaxFloat(pDX, C.ZRes, 0.1f, 10.f);
	DDX_Text(pDX, IDC_FRAMESPERSECOND, C.FramesPerSecond);
	DDV_MinMaxFloat(pDX, C.FramesPerSecond, 1.f, 3000.f);
	DDX_Text(pDX, IDC_EMUTHICK, C.EmulsionThickness);
	DDV_MinMaxFloat(pDX, C.EmulsionThickness, 10.f, 1000.f);
	DDX_Text(pDX, IDC_BASETHICK, C.BaseThickness);
	DDV_MinMaxFloat(pDX, C.BaseThickness, 50.f, 1000.f);
	DDX_Text(pDX, IDC_MARKZRANGE, C.MarkZRange);
	DDV_MinMaxFloat(pDX, C.MarkZRange, 1.f, 500.f);
	DDX_Text(pDX, IDC_TRACKS_PER_FIELD, C.TracksPerField);
	DDV_MinMaxUInt(pDX, C.TracksPerField, 0, 100);
	DDX_Text(pDX, IDC_TRACKS_MAXSLOPE, C.TrackMaxSlope);
	DDV_MinMaxFloat(pDX, C.TrackMaxSlope, 0., 2.f);
	DDX_Text(pDX, IDC_TRACKS_XY_NOISE, C.TrackXYNoise);
	DDV_MinMaxFloat(pDX, C.TrackXYNoise, 0., 2.f);
	DDX_Text(pDX, IDC_TRACKS_GRAIN_PROB, C.TrackGrainProbability);
	DDV_MinMaxFloat(pDX, C.TrackGrainProbability, 0., 1.f);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_SELMARKFILE, OnSelMarkFile)
	ON_BN_CLICKED(IDC_SELTKSFILE, OnSelTksFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

BOOL CEditConfig::OnInitDialog() 
{
	m_MarkFile = C.MarkFile;
	m_TksFile = C.TrackFile;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	strncpy(C.MarkFile, m_MarkFile, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	strncpy(C.TrackFile, m_TksFile, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	CDialog::OnOK();
}

void CEditConfig::OnSelMarkFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "txt", m_MarkFile, OFN_FILEMUSTEXIST | OFN_EXPLORER, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_MarkFile = MyDlg.GetPathName().Left(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
		UpdateData(FALSE);
		};
}

void CEditConfig::OnSelTksFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, "txt", m_TksFile, OFN_PATHMUSTEXIST | OFN_EXPLORER, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_TksFile = MyDlg.GetPathName().Left(SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
		UpdateData(FALSE);
		};	
}
