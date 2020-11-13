// Fog.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Fog.h"
#include "FogDlg.h"

#include <objbase.h>
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HWND    ghDlg;          // Handle to main dialog box
HACCEL  ghAccelTable;   // Handle to accelerator table
CFogDlg * pFogDlg;

/////////////////////////////////////////////////////////////////////////////
// CFogApp

BEGIN_MESSAGE_MAP(CFogApp, CWinApp)
	//{{AFX_MSG_MAP(CFogApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFogApp construction

CFogApp::CFogApp()
{
	m_Instance = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFogApp object

CFogApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFogApp initialization

BOOL CFogApp::InitInstance()
{
	ghAccelTable = LoadAccelerators(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDR_ACCELERATOR_MAIN));
	m_Instance++;
	AfxEnableControlContainer();

	SFogInit F;
	CLSID CLSID_Ody = CLSID_Odyssey;
	CLSID CLSID_FS4 = CLSID_FlexStage4;
	F.IsEmbedded = false;
#ifndef FOG_HOME
	HRESULT HErr;
	{
		HRESULT CoResult;
		CoResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		HErr = CoCreateInstance(CLSID_Ody, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&F.iOdyOb);
		if(F.iOdyOb)
		{
			SySalConfig C;
			volatile HRESULT HRes;
			CString Name("OperaCS_N_Test");
			LoadConfig(C, Name);
			HRes = F.iOdyOb->SetConfig(&C);// iOd è un ISySalObject
			FreeConfig(C);
			F.iOdyOb->QueryInterface(IID_IFrameGrabber, (void **)&F.iFG);
		}
		else
		{
			MessageBox(NULL,"Odyssey is unavailable!","Fog",MB_OK);
			F.ScanningAvailable = false;
		}
	}
	HErr = CoCreateInstance(CLSID_FS4, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&F.iStOb);
//	ErrorMessage(HErr);
	if(F.iStOb)
	{
		ISySalObjectMachineDefaults *iMD = 0;
		F.iStOb->QueryInterface(IID_ISySalObjectMachineDefaults, (void **)&iMD);

		SySalConfig C;
		volatile HRESULT HRes;
		LoadMachineDefaults(C, CLSID_FS4);
		HRes = iMD->SetMachineDefaults(&C);
		iMD->Release();
		FreeConfig(C);
		CString Name("Stage_LNGS");
		LoadConfig(C, Name);
		HRes = F.iStOb->SetConfig(&C); // iSt è un ISySalObject
		FreeConfig(C);
		F.iStOb->QueryInterface(IID_IStage2, (void **)&F.iSt2);
		F.iSt2->EnableManualControl(true);
	}
	else
	{
		MessageBox(NULL,"Scanning is unavailable!","Fog",MB_OK);
		F.ScanningAvailable = false;
	}
#endif

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	F.IsEmbedded = false;
//	MessageBox(NULL,"Break","Break",MB_OK);
//	Sleep(10000);
	CFogDlg dlg(&F);
	pFogDlg = &dlg;
	Sleep(1000);
	CString Text;
	Text.Format("Instance : %d",m_Instance);
//	dlg.MessageBox(Text);
//	m_pMainWnd = &dlg;
	int i;
	SOperaAsked &O = dlg.m_Scanner.Opera;
	if(F.IsEmbedded)
	{
//		FILE * pScan = fopen("C:\\Sysal2000\\Fog4000\\ScanResults.txt","w");
		for(i = 0; i < 1; i++)
		{
			dlg.m_Scanner.mScanViewStruct1.ScanningFinished.ResetEvent();
			dlg.OnScannerscan();
			WaitForSingleObject(dlg.m_Scanner.mScanViewStruct1.ScanningFinished,INFINITE);
//			fprintf(pScan,"%g\t%g\t%g\t%g\t%g\t%g\n",O.SideUpFogDensity,O.SideUpMaxZ,O.SideUpMinZ,O.SideDwFogDensity,O.SideDwMaxZ,O.SideDwMinZ);
//			Sleep(1000);
		}
//		fclose(pScan);
//		dlg.m_Scanner.SetLight(0,false);
	}
	else 
	{
		int nResponse;
		nResponse = dlg.DoModal();
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
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


BOOL CFogApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
	int shack = false,shock = false,shick = false;
	if(code < 0)
	shack = CWinApp::ProcessMessageFilter(code, lpMsg);
	bool test = false;
	if(lpMsg->message == WM_KEYDOWN)
		test = ::IsChild(pFogDlg->Zoom.m_ZoomCombo.m_hWnd,lpMsg->hwnd);
	if(!test && ghDlg && ghAccelTable)
	{
		if (shock = ::TranslateAccelerator(ghDlg, ghAccelTable, lpMsg))
				return(TRUE);
	}
	shick = CWinApp::ProcessMessageFilter(code, lpMsg);
	return shack || shick;
	/* 
	if (code < 0)
		CWinApp::ProcessMessageFilter(code, lpMsg);
	if (ghDlg && ghAccelTable)
	{
		if (::TranslateAccelerator(ghDlg, ghAccelTable, lpMsg))
		return(TRUE);
	}
	return CWinApp::ProcessMessageFilter(code, lpMsg);*/
}
#ifndef FOG_HOME
bool CFogApp::LoadConfig(SySalConfig &C, CString &Name)
{
	C.pItems = 0;
	C.CountOfItems = 0;
	strncpy(C.Name, Name, SYSAL_MAXCONFIG_NAME_LEN);
	CRegKey MyKey;
	CString Temp = "Software\\SySal2\\Configs\\" + Name;
	if (MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ) != ERROR_SUCCESS)
	{
		MessageBox(NULL,"Mover","Error Opening RegKey!",MB_OK);
		return true;
	}
	int i;
	char tempname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	DWORD tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	DWORD tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
	for (i = 0; RegEnumValue(MyKey.m_hKey, i, tempname, &tempsize, 0, 0, 0, 0) == ERROR_SUCCESS; i++) tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	C.pItems = (char *)CoTaskMemAlloc(i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	for (C.CountOfItems = 0; RegEnumValue(MyKey.m_hKey, C.CountOfItems, 
		C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), &tempsize, 
		0, 0, (LPBYTE)(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN), 
		&tempvalsize) == ERROR_SUCCESS; C.CountOfItems++)
	{
		tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
		tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
		};
	MyKey.Close();
	return true;
}
bool CFogApp::LoadMachineDefaults(SySalConfig &C, CLSID &clsid)
{
	C.pItems = 0;
	C.CountOfItems = 0;

	char CLSIDString[64];
	wsprintf(CLSIDString, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		clsid.Data1, clsid.Data2, clsid.Data3, 
		clsid.Data4[0], clsid.Data4[1], clsid.Data4[2], clsid.Data4[3], 
		clsid.Data4[4], clsid.Data4[5], clsid.Data4[6], clsid.Data4[7]);
	HKEY HFindKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", 0, KEY_READ, &HFindKey) != ERROR_SUCCESS)
	{
		::MessageBox(0, "Can't enumerate classes\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	
	char KeyName[SYSAL_MAXCONFIG_NAME_LEN + 1];
	DWORD KeyNameLen;
	int cc = 0;
	bool Found = false;
	while (!Found)
	{
		KeyNameLen = SYSAL_MAXCONFIG_NAME_LEN + 1;
		if (RegEnumKeyEx(HFindKey, cc, KeyName, &KeyNameLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) break;
		HKEY HCheckKey;
		if (RegOpenKeyEx(HFindKey, KeyName, 0, KEY_READ, &HCheckKey) != ERROR_SUCCESS) break;
		DWORD keysize = 0;
		if (RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, NULL, &keysize) != ERROR_SUCCESS)
		{
			RegCloseKey(HCheckKey);
			break;
			}
		char *pK = (char *)malloc(++keysize);
		RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, (UCHAR *)pK, &keysize);
		Found = (strcmpi(pK, CLSIDString) == 0);
		if (pK) free(pK);
		RegCloseKey(HCheckKey);
		cc++;
		}
	RegCloseKey(HFindKey);
	if (!Found)
	{
		::MessageBox(0, "Can't access class information\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	

	strncpy(C.Name, KeyName, SYSAL_MAXCONFIG_NAME_LEN);
	CRegKey MyKey;
	CString Temp = "Software\\SySal2\\Classes\\";
	Temp += KeyName;
	Temp += "\\Defaults";
	if (MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ) != ERROR_SUCCESS) return true;
	int i;
	char tempname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	DWORD tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	DWORD tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
	for (i = 0; RegEnumValue(MyKey.m_hKey, i, tempname, &tempsize, 0, 0, 0, 0) == ERROR_SUCCESS; i++) tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	C.pItems = (char *)CoTaskMemAlloc(i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	for (C.CountOfItems = 0; RegEnumValue(MyKey.m_hKey, C.CountOfItems, 
		C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), &tempsize, 
		0, 0, (LPBYTE)(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN), 
		&tempvalsize) == ERROR_SUCCESS; C.CountOfItems++)
	{
		tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
		tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
		};
	MyKey.Close();
	return true;
}

void CFogApp::FreeConfig(SySalConfig &C)
{
	if (C.pItems)
	{
		CoTaskMemFree(C.pItems);
		C.pItems = 0;
		C.CountOfItems = 0;
		C.Name[0] = 0;
	};
}
#endif