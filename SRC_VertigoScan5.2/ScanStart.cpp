// ScanStart.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScanStart.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanStart dialog


CScanStart::CScanStart(CWnd* pParent /*=NULL*/)
	: CDialog(CScanStart::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanStart)
	m_ID1 = 0;
	m_ID2 = 0;
	m_ID3 = 0;
	m_ID4 = 0;
	m_MaxX = 0.0f;
	m_MaxY = 0.0f;
	m_MinX = 0.0f;
	m_MinY = 0.0f;
	m_Catalog = _T("");
	m_RestoreConfigs = FALSE;
	//}}AFX_DATA_INIT
	m_NewBatch = TRUE;
}


void CScanStart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanStart)
	DDX_Control(pDX, IDC_SS_TAB, m_Tab);
	DDX_Text(pDX, IDC_SS_ID1, m_ID1);
	DDX_Text(pDX, IDC_SS_ID2, m_ID2);
	DDX_Text(pDX, IDC_SS_ID3, m_ID3);
	DDX_Text(pDX, IDC_SS_ID4, m_ID4);
	DDX_Text(pDX, IDC_SS_MAXX, m_MaxX);
	DDX_Text(pDX, IDC_SS_MAXY, m_MaxY);
	DDX_Text(pDX, IDC_SS_MINX, m_MinX);
	DDX_Text(pDX, IDC_SS_MINY, m_MinY);
	DDX_Text(pDX, IDC_SS_CATALOG, m_Catalog);
	DDX_Check(pDX, IDC_SS_RESTORECONFIGS, m_RestoreConfigs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanStart, CDialog)
	//{{AFX_MSG_MAP(CScanStart)
	ON_BN_CLICKED(IDC_SS_SELCATALOG, OnSelCatalog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_SS_TAB, OnSelChangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanStart message handlers

void CScanStart::OnSelCatalog() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "rwc", m_Catalog, OFN_FILEMUSTEXIST | OFN_EXPLORER, "Catalog files (*.rwc)|*.rwc|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal())
	{
		m_Catalog = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

BOOL CScanStart::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		
	m_Tab.InsertItem(0, "New Batch");
/*	'RESUME BATCH' IS CURRENTLY DISABLED 
	m_Tab.InsertItem(1, "Resume Batch");*/
	m_Tab.SetCurSel(0);
	EnableGroups(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScanStart::OnSelChangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	EnableGroups(m_Tab.GetCurSel());
	m_NewBatch = (m_Tab.GetCurSel() == 0);
	*pResult = 0;
}

void CScanStart::EnableGroups(int index)
{
	bool NewBatch = (index == 0);
	bool ResumeBatch = (index == 1);
	GetDlgItem(IDC_SS_CATALOG)->ShowWindow(ResumeBatch);
	GetDlgItem(IDC_SS_SELCATALOG)->ShowWindow(ResumeBatch);
	GetDlgItem(IDC_SS_RESTORECONFIGS)->ShowWindow(ResumeBatch);
	GetDlgItem(IDC_SS_ID1)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_ID2)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_ID3)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_ID4)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_STATIC_BATCHID)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_MINX)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_MAXX)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_MINY)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_MAXY)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_STATIC_MAXY)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_STATIC_MINX)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_STATIC_MAXX)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_STATIC_MINY)->ShowWindow(NewBatch);
	GetDlgItem(IDC_SS_STATIC_MAXY)->ShowWindow(NewBatch);

}
