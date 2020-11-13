// ScanServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ScanServer.h"
#include "ScanServerDlg.h"
#include <initguid.h>
#include "ScanServer_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScanServerApp


class CScanServerModule :
	public CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_ScanServerLib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SCANSERVER, "{A03AA408-1260-4A63-87C5-12949BF07C7E}");};

CScanServerModule _AtlModule;

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
	AfxOleInit();
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Register class factories via CoRegisterClassObject().
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Don't show the main window
		return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		return FALSE;
	}
	// App was launched with /Register or /Regserver switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(FALSE, &CLSID_SySalScanServer);
		return FALSE;
	}

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

BOOL CScanServerApp::ExitInstance(void)
{
	_AtlModule.RevokeClassObjects();
	return CWinApp::ExitInstance();
}
