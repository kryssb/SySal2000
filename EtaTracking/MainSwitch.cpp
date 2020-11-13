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
	m_Selection = MS_SEL_EXIT;
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
	ON_BN_CLICKED(IDC_ADDKINKS, OnAddKinks)
	ON_BN_CLICKED(IDC_BUILDINDEX, OnBuildIndex)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_CHECKKINKS, OnCheckKinks)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch message handlers

void CMainSwitch::OnAddKinks() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_ADDKINKS;
	OnCancel();
}

void CMainSwitch::OnCheckKinks() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_CHECKKINKS;
	OnCancel();	
}

void CMainSwitch::OnBuildIndex() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_BUILDINDEX;	
	OnCancel();	
}

void CMainSwitch::OnAbout() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_ABOUT;	
	OnCancel();		
}

BOOL CMainSwitch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;
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