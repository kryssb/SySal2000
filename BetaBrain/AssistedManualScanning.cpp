// AssistedManualScanning.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AssistedManualScanning.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAssistedManualScanning dialog


CAssistedManualScanning::CAssistedManualScanning(ISySalDataIO *iio, ISheetMap *is1, 
	HWND *phwnd, HSySalHANDLE hstatuschangeevent, CWnd* pParent /*=NULL*/)
	: CDialog(CAssistedManualScanning::IDD, pParent), phWnd(phwnd), iIO(iio), iS1(is1),
	HStatusChangeEvent(hstatuschangeevent)
{
	//{{AFX_DATA_INIT(CAssistedManualScanning)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAssistedManualScanning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssistedManualScanning)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssistedManualScanning, CDialog)
	//{{AFX_MSG_MAP(CAssistedManualScanning)
	ON_BN_CLICKED(IDC_AM_CONVERTEXT, OnConvertExt)
	ON_BN_CLICKED(IDC_AM_CONVERTSTG, OnConvertStage)
	ON_BN_CLICKED(IDC_AM_GOTOEXT, OnGotoExt)
	ON_BN_CLICKED(IDC_AM_GOTOSTG, OnGotoStage)
	ON_BN_CLICKED(IDC_AM_INITMAP, OnInitMap)
	ON_BN_CLICKED(IDC_AM_LOADCURRENT, OnLoadCurrent)
	ON_BN_CLICKED(IDC_AM_STOPSTG, OnStopStage)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssistedManualScanning message handlers

void CAssistedManualScanning::OnConvertExt() 
{
	// TODO: Add your control notification handler code here
	
}

void CAssistedManualScanning::OnConvertStage() 
{
	// TODO: Add your control notification handler code here
	
}

void CAssistedManualScanning::OnGotoExt() 
{
	// TODO: Add your control notification handler code here
	
}

void CAssistedManualScanning::OnGotoStage() 
{
	// TODO: Add your control notification handler code here
	
}

void CAssistedManualScanning::OnInitMap() 
{
	// TODO: Add your control notification handler code here
	CString MapFile;
	GetDlgItem(IDC_AM_INITFILE)->GetWindowText(MapFile);
	CFileDialog MyDlg(TRUE, "MAP", MapFile, OFN_EXPLORER | OFN_FILEMUSTEXIST, "Map initialization files|*.MAP|All files|*.*|||", this);
	if (MyDlg.DoModal() == IDOK) MapFile = MyDlg.GetPathName();
	else MapFile = "";
	GetDlgItem(IDC_AM_INITFILE)->SetWindowText(MapFile);
//	BYTE *pMapData = 0;
	UINT ExtErrInfo;
	HRESULT hRes;
/*	if (MapFile != "")
	{
		hRes = iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pMapData, &ExtErrInfo, (UCHAR *)MapFile.GetBuffer(1));
		MapFile.ReleaseBuffer();
		if (hRes != S_OK)
		{
			CString MsgString;
			MsgString.Format("Can't load map initialization data!\nError code: %08X", ExtErrInfo);
			MessageBox(MsgString, "I/O Error");
			if (pMapData) CoTaskMemFree(pMapData);
			return;
			};
		};*/
	hRes = iS1->Init((BYTE *)MapFile.GetBuffer(1)/*pMapData*/, (HSySalHWND)m_hWnd, HStatusChangeEvent);
	MapFile.ReleaseBuffer();
	if (hRes != S_OK)
	{
// Disable Stage Group		
		};
//	if (pMapData) CoTaskMemFree(pMapData);
}

void CAssistedManualScanning::OnLoadCurrent() 
{
	// TODO: Add your control notification handler code here
	
}

void CAssistedManualScanning::OnStopStage() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CAssistedManualScanning::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CAssistedManualScanning::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
//		*phWnd = 0;
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}
