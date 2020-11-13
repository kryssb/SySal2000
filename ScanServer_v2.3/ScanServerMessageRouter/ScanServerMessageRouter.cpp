// ScanServerMessageRouter.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
//[ module(dll, uuid = "{01842049-1c79-449a-8a0e-4cfe638dbd57}", 
//		 name = "ScanServerMessageRouter", 
//		 helpstring = "ScanServerMessageRouter 2.1 Type Library",
//		 resource_name = "IDR_SCANSERVERMESSAGEROUTER") ];
#include <initguid.h>
#include "ScanServerMessageRouter.h"
#include "ScanServerMessageRouterClass.h"
#include "ScanServerMessageRouter_i.c"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_ScanServerMessageRouter, CScanServerMessageRouterClass)
END_OBJECT_MAP()

class CScanServerMessageRouterApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanServerMessageRouterApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CScanServerMessageRouterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CScanServerMessageRouterApp, CWinApp)
	//{{AFX_MSG_MAP(CScanServerMessageRouterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CScanServerMessageRouterApp theApp;

BOOL CScanServerMessageRouterApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_ScanServerMessageRouter);
    return CWinApp::InitInstance();
}

int CScanServerMessageRouterApp::ExitInstance()
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
    return _Module.RegisterServer(FALSE/*TRUE*/);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(FALSE/*TRUE*/);
}


