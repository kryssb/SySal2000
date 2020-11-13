// ScanServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScanServer.h"
#include "ScanServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_MYCLOSE (WM_USER + 1)


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


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

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
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

void CAboutDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(IDOK);
	//CDialog::OnTimer(nIDEvent);
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(IDOK);
	//CDialog::OnLButtonDown(nFlags, point);
}



BOOL CAboutDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);
	return CDialog::DestroyWindow();
}


// CScanServerDlg dialog

CScanServerDlg::CScanServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanServerDlg::IDD, pParent), BkgndBrush(RGB(255, 255, 255))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	HMsgSync = CreateEvent(NULL, FALSE, FALSE, NULL);
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	try
	{
 		pNETSrv = SySal::DAQSystem::ScanServer::Create(this, CreateObjectInWndThread, DeleteObjectInWndThread, AddString);
		SySal::DAQSystem::ScanServer::RegisterChannelAndServer(pNETSrv);	
	}
	catch (System::Exception ^x)
	{
		::MessageBox(0, "Error creating server.\r\nPlease check whether another instance of ScanServer or OdcMon is running without window.\r\nTerminate running instances by:\r\ntaskkill /f /im ScanServer.exe\r\nor\r\ntaskkill /f /im OdcMon.exe", "Initialization error", MB_OK);
		::ExitProcess(0);
	}
}

CScanServerDlg::~CScanServerDlg()
{
	SySal::DAQSystem::ScanServer::UnregisterChannelAndServer(pNETSrv);
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
	ON_BN_CLICKED(IDC_TEST, OnBnClickedTest)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_CREATE_OBJECT, CreateObject)
	ON_MESSAGE(UM_DELETE_OBJECT, DeleteObject)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CLOSE, OnBnClickedClose)
	ON_BN_CLICKED(IDC_SHOWMONITORS, OnBnClickedShowMonitors)
	ON_WM_SYSCHAR()
END_MESSAGE_MAP()


// CScanServerDlg message handlers

BOOL CScanServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	MyThread = GetCurrentThreadId();	
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
	//System::AppDomain::CurrentDomain->SetData("$_SySalScanServer_$", (System::Object ^)((System::Int64)(long)(void *)m_hWnd));
	
	TestBench.Create(IDD_TESTMODE, 0);
	TestBench.SS = pNETSrv;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

#if 0
UINT _cdecl CScanServerDlg::TestBenchThread(void *par)
{
	CTestBench tb;
	tb.SS = ((CScanServerDlg *)par)->pNETSrv;
/*	System::IO::StreamReader ^r = gcnew System::IO::StreamReader("C:\\Documents and Settings\\administrator.OPERAGS\\Desktop\\Work\\test.xml");
	System::String ^str = r->ReadToEnd();
	r->Close();
	((CScanServerDlg *)par)->pNETSrv->SetScanLayout(str);
	return 0;*/
	return tb.DoModal();
}
#endif

void CScanServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID != SC_CLOSE)
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


// Begin Message Routing Map Entries

HRESULT CScanServerDlg::Connect(void *pOwner)
{
	CScanServerDlg *This = (CScanServerDlg *)pOwner;
	This->pNETSrv->Connect();
	return S_OK;
}
	
HRESULT CScanServerDlg::Disconnect(void *pOwner)
{
	CScanServerDlg *This = (CScanServerDlg *)pOwner;
	This->pNETSrv->Disconnect();
	return S_OK;
}
	
// End Message Routing Map Entries


void CScanServerDlg::OnBnClickedTest()
{
	// TODO: Add your control notification handler code here
	//MessageBox("No test available at this moment", "Debug Info", MB_ICONWARNING);
	TestBench.ShowWindow(SW_SHOW);
	//AfxBeginThread(TestBenchThread, this);
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

ISySalObject *CScanServerDlg::CreateObjectInWndThread(void *pContext, CLSID &clsid)
{
	CScanServerDlg *This = (CScanServerDlg *)pContext;
	This->ObjCLSID = clsid;
	if (This->MyThread == GetCurrentThreadId()) This->CreateObject((WPARAM)(void *)This, 0);
	else
	{
		This->PostMessage(UM_CREATE_OBJECT, (WPARAM)(void *)This);
		WaitForSingleObject(This->HMsgSync, INFINITE);
	}
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
	//temp.Format("%08X %08X", HWndThread, GetCurrentThread());
	//MessageBox(temp);
	SetEvent(HMsgSync);
	return 0;
}

void CScanServerDlg::DeleteObjectInWndThread(void *pContext, ISySalObject *iObj)
{
	CScanServerDlg *This = (CScanServerDlg *)pContext;	
	This->PostMessage(UM_DELETE_OBJECT, (WPARAM)(void *)This, (LPARAM)(void *)iObj);
	WaitForSingleObject(This->HMsgSync, INFINITE);
}

LRESULT CScanServerDlg::DeleteObject(WPARAM, LPARAM obj)
{
	ISySalObject *iObj = (ISySalObject *)(void *)obj;
	iObj->Release();
	SetEvent(HMsgSync);
	return 0;
}


void CScanServerDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (::MessageBox(0, "Are you really sure you want to close?", "Warning", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES) return;
	//pNETSrv->ResetLayoutForShutDown(pNETSrv);
	/*
	ISySalObject **objs;
	int count = pNETSrv->GetLayoutListAndResetForShutdown(pNETSrv, &objs);
	int i;
	for (i = 0; i < count; objs[i++]->Release());
	free(objs);
	*/
	CDialog::OnClose();
}

void CScanServerDlg::OnBnClickedClose()
{
	// TODO: Add your control notification handler code here
	//SendMessage(WM_CLOSE);
	AfxBeginThread(ClosingThread, this);
}

void CScanServerDlg::OnBnClickedShowMonitors()
{
	// TODO: Add your control notification handler code here
	pNETSrv->ShowMonitors();
}

BOOL CScanServerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	if (wParam == UM_MYCLOSE) 
	{
		::TerminateProcess(GetCurrentProcess(), 0);		
		return TRUE;
	}
	if (wParam != 2) return CDialog::OnCommand(wParam, lParam);
	else return TRUE;
}

UINT CScanServerDlg::ClosingThread(void *par)
{
	CScanServerDlg *This = (CScanServerDlg *)par;
	This->pNETSrv->ResetLayoutForShutDown();
	ScanServer::UnregisterChannelAndServer(This->pNETSrv);	
	This->pNETSrv = nullptr;
	This->PostMessage(WM_COMMAND, UM_MYCLOSE);	
	return 0;
}

#include "SySalObj2_i.c"