// ScanServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ScanServer.h"
#include "ScanServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScanServerApp

BEGIN_MESSAGE_MAP(CScanServerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CScanServerApp construction

CScanServerApp::CScanServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CScanServerApp object

CScanServerApp theApp;


// CScanServerApp initialization

BOOL CScanServerApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CAboutDlg SplashDlg;
	SplashDlg.DoModal();

	CScanServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
