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


CMainSwitch::CMainSwitch(HWND *phwnd, CWnd* pParent)
	: CDialog(CMainSwitch::IDD, pParent), phWnd(phwnd)
{
	//{{AFX_DATA_INIT(CMainSwitch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Selection = MS_SEL_EXIT;
	m_EnableTest = true;
	m_EnableScan = true;
	m_EnableRemoteScan = true;
}


CMainSwitch::~CMainSwitch()
{
	if (HPicture) DeleteObject(HPicture);	
	};


void CMainSwitch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainSwitch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainSwitch, CDialog)
	//{{AFX_MSG_MAP(CMainSwitch)
	ON_BN_CLICKED(IDC_MS_SCAN, OnScan)
	ON_BN_CLICKED(IDC_MS_TESTCONFIG, OnTestAndConfig)
	ON_BN_CLICKED(IDC_MS_INITMAP, OnInitMap)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_MS_MANUALCHECKS, OnManualChecks)
	ON_BN_CLICKED(IDC_MS_REMOTESCAN, OnRemoteScan)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch message handlers

void CMainSwitch::OnScan() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_SCAN;
	OnCancel();		
}

void CMainSwitch::OnTestAndConfig() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_TESTCONFIG;
	OnCancel();	
}

void CMainSwitch::OnInitMap() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_INITMAP;
	OnCancel();	
}

void CMainSwitch::OnManualChecks() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_MANUALCHECKS;
	OnCancel();		
}

void CMainSwitch::OnRemoteScan() 
{
	// TODO: Add your control notification handler code here
	m_Selection = MS_SEL_REMOTESCAN;
	OnCancel();		
}

BOOL CMainSwitch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;
	GetDlgItem(IDC_MS_TESTCONFIG)->EnableWindow(m_EnableTest);
	GetDlgItem(IDC_MS_SCAN)->EnableWindow(m_EnableScan);
	GetDlgItem(IDC_MS_MANUALCHECKS)->EnableWindow(m_EnableManualChecks);
	GetDlgItem(IDC_MS_REMOTESCAN)->EnableWindow(m_EnableRemoteScan);

	HPicture = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_WELCOME), IMAGE_BITMAP, 0, 0, 0);
	GetObject(HPicture, sizeof(PictInfo), &PictInfo);

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

void CMainSwitch::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDCtl == IDC_MS_PICTURE)
	{
		CRect Rect;
		GetDlgItem(IDC_MS_PICTURE)->GetClientRect(&Rect);
		HDC hDC = CreateCompatibleDC(lpDrawItemStruct->hDC);
		SelectObject(hDC, HPicture);
		StretchBlt(lpDrawItemStruct->hDC, 0, 0, Rect.Width(), Rect.Height(), hDC, 0, 0, PictInfo.bmWidth, abs(PictInfo.bmHeight), SRCCOPY);
		DeleteDC(hDC);
		}
	else CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

