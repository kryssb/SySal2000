// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Playground.h"

#include "PlaygroundDoc.h"
#include "PlaygroundView.h"
#include "MainFrm.h"
#include "SelectClassDlg.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_FILE_REGISTERCLASS, OnFileRegisterClass)
	ON_COMMAND(IDM_FILE_UNREGISTERCLASS, OnFileUnregisterClass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFileRegisterClass() 
{
	// TODO: Add your command handler code here
	CFileDialog MyDlg(TRUE, "DLL", "", OFN_FILEMUSTEXIST, 
		"Dynamic Linking Libraries|*.dll|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		HINSTANCE HInst = LoadLibrary(MyDlg.GetPathName());
		if (!HInst)
		{
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
			MessageBox((LPCTSTR)lpMsgBuf, "File Error", MB_ICONERROR | MB_OK);
			LocalFree( lpMsgBuf );
			return;
			};
		FARPROC pDllRegisterServer = GetProcAddress(HInst, "DllRegisterServer");
		if (!pDllRegisterServer)
		{
			FreeLibrary(HInst);
			MessageBox("The specified library does not contain registration information", "File Error", MB_ICONERROR | MB_OK);
			return;
			};
		pDllRegisterServer();
		FreeLibrary(HInst);
		MessageBox("Registration Ok!", "Success", MB_ICONINFORMATION | MB_OK);
		UpdateClassCombo();
		};
}

void CMainFrame::OnFileUnregisterClass() 
{
	// TODO: Add your command handler code here
	CSelectClassDlg MyDlg(this);
	if (MyDlg.DoModal() == IDOK)
	{
		CRegKey MyKey;
		CString KeyString = "Software\\SySal2\\Classes\\" + MyDlg.m_ClassName;
		if (MyKey.Open(HKEY_LOCAL_MACHINE, KeyString, KEY_READ) != ERROR_SUCCESS)
		{
			MessageBox("Unable to unregister the specified class\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
			return;
			};
		DWORD size = 256;
		CString CLSIDString;
		if (MyKey.QueryValue(CLSIDString.GetBuffer(size), "CLSID", &size) != ERROR_SUCCESS)
		{
			CLSIDString.ReleaseBuffer();
			MyKey.Close();
			MessageBox("Corrupt registry entry for the specified class\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
			return;
			};
		CLSIDString.ReleaseBuffer();
		MyKey.Close();
		KeyString = "Software\\CLASSES\\CLSID\\" + CLSIDString + "\\InprocServer32";
		if (MyKey.Open(HKEY_LOCAL_MACHINE, KeyString, KEY_READ) != ERROR_SUCCESS)
		{
			MessageBox("Unable to find the InprocServer32 entry for the specified class\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
			return;
			};
		size = MAX_PATH + 1;
		CString FileString;
		if (MyKey.QueryValue(FileString.GetBuffer(size), "", &size) != ERROR_SUCCESS)
		{
			FileString.ReleaseBuffer();
			MyKey.Close();
			MessageBox("Unable to find the server path info for the specified class\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
			return;
			};
		FileString.ReleaseBuffer();
		MyKey.Close();
		HINSTANCE HInst = LoadLibrary(FileString);
		if (!HInst)
		{
			MessageBox("Can't find the server file", "File Error", MB_ICONERROR | MB_OK);
			return;
			};
		FARPROC pDllUnregisterServer = GetProcAddress(HInst, "DllUnregisterServer");
		if (!pDllUnregisterServer)
		{
			FreeLibrary(HInst);
			MessageBox("The specified library does not contain un-registration information", "File Error", MB_ICONERROR | MB_OK);
			return;
			};
		pDllUnregisterServer();
		FreeLibrary(HInst);
		MessageBox("Un-Registration Ok!", "Success", MB_ICONINFORMATION | MB_OK);
		UpdateClassCombo();
		};
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (HIWORD(wParam) == CBN_SELCHANGE)
	{		
		CWnd *pComboWnd = m_wndDlgBar.GetDlgItem(IDC_CLASSCOMBO);
		if (LOWORD(wParam) == IDC_CLASSCOMBO && 
			(HWND)lParam == pComboWnd->m_hWnd)
		{
			CString Selection = "";
			int index = pComboWnd->SendMessage(CB_GETCURSEL);
			if (index != CB_ERR)
			{
				pComboWnd->SendMessage(CB_GETLBTEXT, index, (LPARAM)(LPCTSTR)Selection.GetBuffer(257));
				Selection.ReleaseBuffer();
				};
			((CPlaygroundView *)GetActiveView())->SetClassSel(Selection);
			};
		};		
	return CFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::UpdateClassCombo()
{
	CWnd *pComboWnd = m_wndDlgBar.GetDlgItem(IDC_CLASSCOMBO);
	pComboWnd->SendMessage(CB_RESETCONTENT);
	CRegKey MyKey;
	if (MyKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", KEY_READ) != ERROR_SUCCESS)
	{
		MessageBox("Unable to find\nHKEY_LOCAL_MACHINE\\Software\\SySal2\\Classes\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		MyKey.Close();
		return;
		};
	CString Temp;
	DWORD size = 256;
	FILETIME filetime;
	int i = 0;	
	while (RegEnumKeyEx(MyKey.m_hKey, i++, Temp.GetBuffer(size), &size, NULL, NULL, NULL, &filetime) == ERROR_SUCCESS)
	{
		Temp.ReleaseBuffer();
		pComboWnd->SendMessage(CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Temp);
		size = 256;
		};
	Temp.ReleaseBuffer();	
	MyKey.Close();		
}

void CMainFrame::UpdateDialogControls()
{
	CWnd::UpdateDialogControls(&m_wndDlgBar, TRUE);
	CWnd::UpdateDialogControls(&m_wndToolBar, TRUE);
}

