// EditConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "videoimagescanner.h"
#include "EditConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditConfigDlg dialog


CEditConfigDlg::CEditConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditConfigDlg)
	m_EndLayer1 = 0;
	m_Equalization = FALSE;
	m_MaxGrains = 0;
	m_MaxTracks = 0;
	m_RelativeThreshold = FALSE;
	m_Shrinkage = 0.0f;
	m_StartLayer0 = 0;
	m_StartLayer1 = 0;
	m_Threshold0 = 0;
	m_Threshold1 = 0;
	m_EndLayer0 = 0;
	m_MaxFlatTracks = 0;
	m_MaxFlatStripsInTrack = 0;
	//}}AFX_DATA_INIT
}


void CEditConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfigDlg)
	DDX_Text(pDX, IDC_EC_ENDLAYER1, m_EndLayer1);
	DDX_Check(pDX, IDC_EC_EQUALIZATION, m_Equalization);
	DDX_Text(pDX, IDC_EC_MAXGRAINS, m_MaxGrains);
	DDX_Text(pDX, IDC_EC_MAXTRACKS, m_MaxTracks);
	DDX_Check(pDX, IDC_EC_RELTHRESHOLD, m_RelativeThreshold);
	DDX_Text(pDX, IDC_EC_SHRINKAGE, m_Shrinkage);
	DDV_MinMaxFloat(pDX, m_Shrinkage, 1.f, 3.f);
	DDX_Text(pDX, IDC_EC_STARTLAYER0, m_StartLayer0);
	DDX_Text(pDX, IDC_EC_STARTLAYER1, m_StartLayer1);
	DDX_Text(pDX, IDC_EC_THRESHOLD0, m_Threshold0);
	DDX_Text(pDX, IDC_EC_THRESHOLD1, m_Threshold1);
	DDX_Text(pDX, IDC_EC_ENDLAYER0, m_EndLayer0);
	DDX_Text(pDX, IDC_EC_MAXFLATTRACKS, m_MaxFlatTracks);
	DDV_MinMaxUInt(pDX, m_MaxFlatTracks, 10, 1000);
	DDX_Text(pDX, IDC_EC_MAXFLATSTRIPSINTRACK, m_MaxFlatStripsInTrack);
	DDV_MinMaxUInt(pDX, m_MaxFlatStripsInTrack, 10, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CEditConfigDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfigDlg message handlers
