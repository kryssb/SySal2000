// GrainFinderParametersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "GrainFinderParametersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrainFinderParametersDlg dialog


CGrainFinderParametersDlg::CGrainFinderParametersDlg(SGrainFinderParameters * gfPa,CWnd* pParent /*=NULL*/)
	: CDialog(CGrainFinderParametersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrainFinderParametersDlg)
	m_RealSize = gfPa->RealSize;
	m_CellSize = gfPa->CellSize;
	m_Delta = gfPa->Delta;
	m_MaxImageOffset = gfPa->MaxImagesOffset;
	m_Threshold = gfPa->Threshold;
	m_XOffset = gfPa->XOffset;
	m_YOffset = gfPa->YOffset;
	m_ThreeFrames = gfPa->ThreeFrames;
	m_Statistics = gfPa->Statistics;
	m_Differential = gfPa->Differential;
	m_InvertXY = gfPa->InvertXY;
	//}}AFX_DATA_INIT
	m_pGfPa = gfPa;
	m_RealSizeChecked = m_RealSize == 1;
}


void CGrainFinderParametersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrainFinderParametersDlg)
	DDX_Check(pDX, IDC_CHK_GFPARAM_REALSIZE, m_RealSize);
	DDX_Text(pDX, IDC_EDT_GFPARAM_CELLSIZE, m_CellSize);
	DDX_Text(pDX, IDC_EDT_GFPARAM_DELTA, m_Delta);
	DDX_Text(pDX, IDC_EDT_GFPARAM_MAXIMAGEOFFSET, m_MaxImageOffset);
	DDX_Text(pDX, IDC_EDT_GFPARAM_THRESHOLD, m_Threshold);
	DDX_Text(pDX, IDC_EDT_GFPARAM_XOFFSET, m_XOffset);
	DDX_Text(pDX, IDC_EDT_GFPARAM_YOFFSET, m_YOffset);
	DDX_Check(pDX, IDC_CHK_GFPARAM_FRAMESTEP, m_ThreeFrames);
	DDX_Check(pDX, IDC_CHK_GFPARAM_STATISTICS, m_Statistics);
	DDX_Check(pDX, IDC_CHK_GFPARAM_DIFFERENTIAL, m_Differential);
	DDX_Check(pDX, IDC_CHK_GFPARAM_INVERTXY, m_InvertXY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrainFinderParametersDlg, CDialog)
	//{{AFX_MSG_MAP(CGrainFinderParametersDlg)
	ON_BN_CLICKED(IDC_CHK_GFPARAM_REALSIZE, OnCheckRealsize)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrainFinderParameterDlg message handlers

BOOL CGrainFinderParametersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(!m_RealSizeChecked)
	{
		GetDlgItem(IDC_EDT_GFPARAM_XOFFSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_GFPARAM_YOFFSET)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDT_GFPARAM_XOFFSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_GFPARAM_YOFFSET)->EnableWindow(TRUE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrainFinderParametersDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CGrainFinderParametersDlg::OnCheckRealsize() 
{
	if(m_RealSizeChecked)
	{
		GetDlgItem(IDC_EDT_GFPARAM_XOFFSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_GFPARAM_YOFFSET)->EnableWindow(FALSE);
		m_RealSizeChecked = false;
	}
	else
	{
		GetDlgItem(IDC_EDT_GFPARAM_XOFFSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_GFPARAM_YOFFSET)->EnableWindow(TRUE);
		m_RealSizeChecked = true;
	}
}

void CGrainFinderParametersDlg::OnOK() 
{
	UpdateData(TRUE);
	m_pGfPa->Delta = m_Delta;
	m_pGfPa->Threshold = m_Threshold;
	m_pGfPa->CellSize = m_CellSize;
	m_pGfPa->MaxImagesOffset = m_MaxImageOffset;
	m_pGfPa->XOffset = m_XOffset;
	m_pGfPa->YOffset = m_YOffset;
	m_pGfPa->RealSize = m_RealSize == 1;
	m_pGfPa->ThreeFrames = m_ThreeFrames == 1;
	m_pGfPa->Statistics = m_Statistics == 1;
	m_pGfPa->Differential = m_Differential == 1;
	m_pGfPa->InvertXY = m_InvertXY == 1;
	CDialog::OnOK();
}


