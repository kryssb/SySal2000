// ReusePolicy.cpp : implementation file
//

#include "stdafx.h"
#include "FlexMap3.h"
#include "ReusePolicy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReusePolicy dialog


CReusePolicy::CReusePolicy(CWnd* pParent /*=NULL*/)
	: CDialog(CReusePolicy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReusePolicy)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReusePolicy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReusePolicy)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReusePolicy, CDialog)
	//{{AFX_MSG_MAP(CReusePolicy)
	ON_BN_CLICKED(IDC_RP_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_RP_NOREUSE, OnNoReuse)
	ON_BN_CLICKED(IDC_RP_REINTERPRET, OnReinterpret)
	ON_BN_CLICKED(IDC_RP_REPOSITION, OnReposition)
	ON_BN_CLICKED(IDC_RP_REINTERPRETLOAD, OnReinterpretLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReusePolicy message handlers

void CReusePolicy::OnLoad() 
{
	// TODO: Add your control notification handler code here
	m_ReusePolicy = RP_LOAD;	
}

void CReusePolicy::OnNoReuse() 
{
	// TODO: Add your control notification handler code here
	m_ReusePolicy = RP_NOREUSE;
}

void CReusePolicy::OnReinterpret() 
{
	// TODO: Add your control notification handler code here
	m_ReusePolicy = RP_REINTERPRET;
}

void CReusePolicy::OnReposition() 
{
	// TODO: Add your control notification handler code here
	m_ReusePolicy = RP_REPOSITION;
}

void CReusePolicy::OnReinterpretLoad() 
{
	// TODO: Add your control notification handler code here
	m_ReusePolicy = RP_REINTERPRETLOAD;
}

BOOL CReusePolicy::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_IsSameGrid)
	{
		GetDlgItem(IDC_RP_REINTERPRET)->EnableWindow(false);
		GetDlgItem(IDC_RP_REINTERPRETLOAD)->EnableWindow(false);
		SendDlgItemMessage(IDC_RP_REPOSITION, BM_SETCHECK, BST_CHECKED);
		m_ReusePolicy = RP_REPOSITION;
		}
	else
	{
		GetDlgItem(IDC_RP_REPOSITION)->EnableWindow(false);
		GetDlgItem(IDC_RP_LOAD)->EnableWindow(false);
		SendDlgItemMessage(IDC_RP_REINTERPRET, BM_SETCHECK, BST_CHECKED);
		m_ReusePolicy = RP_REINTERPRET;
		};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


