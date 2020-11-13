#include "comtest\comtestdlg.h"
#include "comtest\comtestdlg.h"
#include "comtest\comtestdlg.h"
// ScanServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScanServer.h"
#include "ScanServerDlg.h"
#include "SySalObj2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "..\VirtualMicroscope\VirtualMicroscope.h"



CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(IDOK);
	//CDialog::OnLButtonDown(nFlags, point);
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(IDOK);
	//CDialog::OnTimer(nIDEvent);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int XScreenSize = GetSystemMetrics(SM_CXSCREEN);
	int YScreenSize = GetSystemMetrics(SM_CYSCREEN);
	CBitmap TempBMP;
	BITMAP Info;
	TempBMP.LoadBitmap(IDB_BANNER);
	TempBMP.GetBitmap(&Info);
	MoveWindow((XScreenSize - Info.bmWidth) / 2, (YScreenSize - abs(Info.bmHeight)) / 2, 
		Info.bmWidth, abs(Info.bmHeight));

	SetTimer(1, 5000, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAboutDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);
	return CDialog::DestroyWindow();
}


// CScanServerDlg dialog

CScanServerDlg::CScanServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanServerDlg::IDD, pParent), pCOMSrv(0), BkgndBrush(RGB(255, 255, 255))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	HWndThread = GetCurrentThread();
	HMsgSync = CreateEvent(NULL, FALSE, FALSE, NULL);
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (CoCreateInstance(CLSID_SySalScanServer, NULL, CLSCTX_INPROC_SERVER, IID_IScanServer, (void **)&pCOMSrv) != S_OK)
	{
		::MessageBox(0, "Can't create remote scanning server COM object.\r\nAborting.", "COM Error", MB_ICONERROR);
		PostQuitMessage(0);
	}
	ISySalObject *iCOMSrv = 0;
	pCOMSrv->QueryInterface(IID_ISySalObject, (void **)&iCOMSrv);
	pNETSrv = SySal::DAQSystem::ScanServer::Create(this, CreateObjectInWndThread, SetScanLayout, AddString, iCOMSrv);
	iCOMSrv->Release();
	pChannel = SySal::DAQSystem::ScanServer::RegisterChannelAndServer(pNETSrv);
}

CScanServerDlg::~CScanServerDlg()
{
	SySal::DAQSystem::ScanServer::UnregisterChannelAndServer(pChannel, pNETSrv);
	if (pCOMSrv) pCOMSrv->Release();
	pCOMSrv = 0;
	CloseHandle(HMsgSync);
}

void CScanServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_LOGBOX, m_LogBox);
}

BEGIN_MESSAGE_MAP(CScanServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_CREATE_OBJECT, CreateObject)
	ON_BN_CLICKED(IDC_MAIN_TEST, OnBnClickedMainTest)
END_MESSAGE_MAP()


// CScanServerDlg message handlers

BOOL CScanServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScanServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScanServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScanServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CScanServerDlg::SetScanLayout(void *pcontext, System::String *xmllayout)
{
	CScanServerDlg *This = (CScanServerDlg *)pcontext;
	return false;
}

void CScanServerDlg::AddString(void *pcontext, char *msgstr)
{
	CScanServerDlg *This = (CScanServerDlg *)pcontext;
	This->m_LogBox.SetRedraw(FALSE);
	This->m_LogBoxText += msgstr;
	if (This->m_LogBoxText.GetLength() > This->m_LogBox.GetLimitText())
		This->m_LogBoxText.Delete(0, This->m_LogBoxText.GetLength() - This->m_LogBox.GetLimitText());
	This->m_LogBox.SetWindowText(This->m_LogBoxText);
	int lines = This->m_LogBox.GetLineCount();
	CRect ClRect;
	This->m_LogBox.GetClientRect(&ClRect);
	int i;
	int yscrollbarsize = GetSystemMetrics(SM_CYHSCROLL);
	This->m_LogBox.LineScroll(0);
	for (i = 0; i < lines; i++)
	{
		CPoint p = This->m_LogBox.PosFromChar(This->m_LogBox.LineIndex(i));
		if (p.y >= (ClRect.Height() - yscrollbarsize)) break;
	}
	if (i < lines)
	{
		i--;
		This->m_LogBox.LineScroll(lines - i);
	}
	This->m_LogBox.SetRedraw(TRUE);
}
HBRUSH CScanServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (/*(nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX)
		&&*/ pWnd->GetDlgCtrlID() == IDC_MAIN_LOGBOX)
	{
		pDC->SelectObject(&BkgndBrush);
		pDC->SetBkColor(RGB(255, 255, 255));
		return (HBRUSH)BkgndBrush.m_hObject;
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

ISySalObject *CScanServerDlg::CreateObjectInWndThread(void *pContext, CLSID &clsid)
{
	CScanServerDlg *This = (CScanServerDlg *)pContext;
	This->ObjCLSID = clsid;
	This->PostMessage(UM_CREATE_OBJECT, (WPARAM)(void *)This);
	WaitForSingleObject(This->HMsgSync, INFINITE);
	CString temp;
	temp.Format("%08X", This->iCreatedObj);
	This->MessageBox(temp);
	return This->iCreatedObj;
}

LRESULT CScanServerDlg::CreateObject(WPARAM, LPARAM)
{
	HRESULT HRES;	
	if ((HRES = CoCreateInstance(ObjCLSID, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&iCreatedObj)) != S_OK)
	{
LPVOID lpMsgBuf;
FormatMessage( 
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM | 
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    HRES,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &lpMsgBuf,
    0,
    NULL 
);
// Process any inserts in lpMsgBuf.
// ...
// Display the string.
MessageBox((LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
// Free the buffer.
LocalFree( lpMsgBuf );
	}
	CString temp;
	temp.Format("%08X %08X", HWndThread, GetCurrentThread());
	MessageBox(temp);
	SetEvent(HMsgSync);
	return 0;
}

void CScanServerDlg::OnBnClickedMainTest()
{
	// TODO: Add your control notification handler code here
	ISySalObject *iOb = 0;
	IUnknown *iUnk = 0;
	HRESULT HRes;
	if ((HRes = CoCreateInstance(CLSID_VirtualMicroscope, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown /*IID_ISySalObject*/, (void **)&iUnk/*&iOb*/)) != S_OK)
	{
LPVOID lpMsgBuf;
FormatMessage( 
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM | 
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    HRes,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &lpMsgBuf,
    0,
    NULL 
);
// Process any inserts in lpMsgBuf.
// ...
// Display the string.
MessageBox((LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
// Free the buffer.
LocalFree( lpMsgBuf );		
	}
}

#include "..\VirtualMicroscope\VirtualMicroscope_i.c"
