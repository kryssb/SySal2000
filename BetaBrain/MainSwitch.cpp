// MainSwitch.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainSwitch.h"
#include "..\Common\Connection.h"

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
	m_AssistedManualEnable = false;
	m_UserEnable = false;
	m_ExternalEnable = false;
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
	ON_BN_CLICKED(IDC_MS_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_MS_ASSISTEDMANUAL, OnAssistedManual)
	ON_BN_CLICKED(IDC_MS_EXIT, OnExit)
	ON_BN_CLICKED(IDC_MS_EXTERNALCONTROLJOB, OnExternalControlJob)
	ON_BN_CLICKED(IDC_MS_USERDRIVEN, OnUserDriven)
	ON_BN_CLICKED(IDC_MS_USERJOB, OnUserJob)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch message handlers

void CMainSwitch::OnAbout() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_ABOUT;
	CDialog::OnCancel();
}

void CMainSwitch::OnAssistedManual() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_ASSISTEDMANUAL;
	CDialog::OnCancel();	
}

void CMainSwitch::OnExit() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_EXIT;
	CDialog::OnCancel();		
}

void CMainSwitch::OnExternalControlJob() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_EXTERNALJOB;
	CDialog::OnCancel();			
}

void CMainSwitch::OnUserDriven() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_USERDRIVEN;
	CDialog::OnCancel();				
}

void CMainSwitch::OnUserJob() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_USERJOB;
	CDialog::OnCancel();					
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

BOOL CMainSwitch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;
	m_Selection = 0;
	GetDlgItem(IDC_MS_ASSISTEDMANUAL)->EnableWindow(m_AssistedManualEnable);
	GetDlgItem(IDC_MS_USERDRIVEN)->EnableWindow(m_UserEnable);
	GetDlgItem(IDC_MS_USERJOB)->EnableWindow(m_UserEnable);
	GetDlgItem(IDC_MS_EXTERNALCONTROLJOB)->EnableWindow(m_ExternalEnable);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
