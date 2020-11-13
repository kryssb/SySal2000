// VSScanServer.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
/*
// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{E451513E-8C80-44EF-AA75-B62DA45FDEAE}", 
		 name = "VSScanServer", 
		 helpstring = "VSScanServer 1.0 Type Library",
		 resource_name = "IDR_VSSCANSERVER") ];
*/
#include <initguid.h>
#include "VSScanServer.h"
#include "VSScanServerNET.h"
#include "VSScanServerNET_i.c"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VSScanServerNET, CVSScanServerNET)
END_OBJECT_MAP()

class CVSScanServerNETApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSScanServerNETApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CVSScanServerNETApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CVSScanServerNETApp, CWinApp)
	//{{AFX_MSG_MAP(CVSScanServerNETApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CVSScanServerNETApp theApp;

BOOL CVSScanServerNETApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_VSSCANSERVERLib);
    return CWinApp::InitInstance();
}

int CVSScanServerNETApp::ExitInstance()
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
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE) != ERROR_SUCCESS) throw 0;
		MyKey.Close();
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software\\SySal2", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE) != ERROR_SUCCESS) throw 1;
		MyKey.Close();
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE) != ERROR_SUCCESS) throw 2;
		MyKey.Close();
		if (MyKey.Create(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes\\VSScanServerNET", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE) != ERROR_SUCCESS) throw 3;
		MyKey.Close();
		MyKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes\\VSScanServerNET", KEY_READ | KEY_WRITE);
		char CLSIDString[64];
		wsprintf(CLSIDString, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
			CLSID_VSScanServerNET.Data1, CLSID_VSScanServerNET.Data2, CLSID_VSScanServerNET.Data3, 
			CLSID_VSScanServerNET.Data4[0], CLSID_VSScanServerNET.Data4[1], CLSID_VSScanServerNET.Data4[2], CLSID_VSScanServerNET.Data4[3], 
			CLSID_VSScanServerNET.Data4[4], CLSID_VSScanServerNET.Data4[5], CLSID_VSScanServerNET.Data4[6], CLSID_VSScanServerNET.Data4[7]);
		MyKey.SetValue(CLSIDString, "CLSID");
		MyKey.Close();
		}
	catch (...)
	{
		MyKey.Close();
		MyKey.Open(HKEY_LOCAL_MACHINE, "", KEY_READ | KEY_WRITE);
		MyKey.RecurseDeleteKey("Software\\SySal2\\Classes\\VSScanServerNET");
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
	MyKey.RecurseDeleteKey("Software\\SySal2\\Classes\\VSScanServerNET");
	MyKey.Close();
    return _Module.UnregisterServer(TRUE);
}


