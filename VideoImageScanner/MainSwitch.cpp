// MainSwitch.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainSwitch.h"
#include "..\Common\Connection.h"
#include "ExWinThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch dialog


CMainSwitch::CMainSwitch(HWND *phwnd, CWnd* pParent /*=NULL*/)
	: CDialog(CMainSwitch::IDD, pParent), phWnd(phwnd)
{
	//{{AFX_DATA_INIT(CMainSwitch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_ClusterAnalysisEnable = false;
	m_InteractiveTrackingEnable = false;
	m_BatchProcessingEnable = false;
}


void CMainSwitch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainSwitch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainSwitch, CDialog)
	//{{AFX_MSG_MAP(CMainSwitch)
	ON_BN_CLICKED(IDC_MS_ABOUT, OnMSAbout)
	ON_BN_CLICKED(IDC_MS_BATCHPROCESSING, OnMSBatchProcessing)
	ON_BN_CLICKED(IDC_MS_CLUSTERANALYSIS, OnMSClusterAnalysis)
	ON_BN_CLICKED(IDC_MS_EXIT, OnMSExit)
	ON_BN_CLICKED(IDC_MS_HELP, OnMSHelp)
	ON_BN_CLICKED(IDC_MS_INTERACTIVETRACKING, OnMSInteractiveTracking)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch message handlers

void CMainSwitch::OnMSAbout() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_ABOUT;
	CDialog::OnCancel();	
}

void CMainSwitch::OnMSBatchProcessing() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_BATCHPROCESSING;
	CDialog::OnCancel();	
}

void CMainSwitch::OnMSClusterAnalysis() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_CLUSTERANALYSIS;
	CDialog::OnCancel();	
}

void CMainSwitch::OnMSExit() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_EXIT;
	CDialog::OnCancel();	
}

void CMainSwitch::OnMSHelp() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_HELP;
	CDialog::OnCancel();	
}

void CMainSwitch::OnMSInteractiveTracking() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_INTERACTIVETRACKING;
	CDialog::OnCancel();	
}



BOOL CMainSwitch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;
	m_Selection = 0;
	GetDlgItem(IDC_MS_CLUSTERANALYSIS)->EnableWindow(m_ClusterAnalysisEnable);
	GetDlgItem(IDC_MS_INTERACTIVETRACKING)->EnableWindow(m_InteractiveTrackingEnable);
	GetDlgItem(IDC_MS_BATCHPROCESSING)->EnableWindow(m_BatchProcessingEnable);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CMainSwitch::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
		*phWnd = 0;
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}
