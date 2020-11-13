// SWK66Clustering_1.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f SWK66Clustering_1ps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "SWK66Clustering_1.h"

#include "SWK66Clustering_1_i.c"
#include "SWK66Clustering.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_SWK66Clustering_1, CSWK66Clustering)
END_OBJECT_MAP()

class CSWK66Clustering_1App : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSWK66Clustering_1App)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSWK66Clustering_1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CSWK66Clustering_1App, CWinApp)
	//{{AFX_MSG_MAP(CSWK66Clustering_1App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSWK66Clustering_1App theApp;

BOOL CSWK66Clustering_1App::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_SWK66CLUSTERING_1Lib);
    return CWinApp::InitInstance();
}

int CSWK66Clustering_1App::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
	CRegKey MyKey;
	try
	{
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ) != ERROR_SUCCESS) throw 0;
		MyKey.Close();
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software\\SySal2", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ) != ERROR_SUCCESS) throw 1;
		MyKey.Close();
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ) != ERROR_SUCCESS) throw 2;
		MyKey.Close();
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes\\SWK66Clustering_1", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ) != ERROR_SUCCESS) throw 3;
		MyKey.Close();
		MyKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes\\SWK66Clustering_1", KEY_WRITE | KEY_READ);
		char CLSIDString[64];
		wsprintf(CLSIDString, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
			CLSID_SWK66Clustering_1.Data1, CLSID_SWK66Clustering_1.Data2, CLSID_SWK66Clustering_1.Data3, 
			CLSID_SWK66Clustering_1.Data4[0], CLSID_SWK66Clustering_1.Data4[1], CLSID_SWK66Clustering_1.Data4[2], CLSID_SWK66Clustering_1.Data4[3], 
			CLSID_SWK66Clustering_1.Data4[4], CLSID_SWK66Clustering_1.Data4[5], CLSID_SWK66Clustering_1.Data4[6], CLSID_SWK66Clustering_1.Data4[7]);
		MyKey.SetValue(CLSIDString, "CLSID");
		MyKey.Close();
		}
	catch (...)
	{
		MyKey.Close();
		MyKey.Open(HKEY_LOCAL_MACHINE, "", KEY_WRITE | KEY_READ);
		MyKey.RecurseDeleteKey("Software\\SySal2\\Classes\\SWK66Clustering_1");
		MyKey.Close();
		};
    return _Module.RegisterServer(FALSE/*TRUE*/);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	CRegKey MyKey;
	MyKey.Open(HKEY_LOCAL_MACHINE, "", KEY_WRITE | KEY_READ);
	MyKey.RecurseDeleteKey("Software\\SySal2\\Classes\\SWK66Clustering_1");
	MyKey.Close();
    return _Module.UnregisterServer(TRUE);
}


