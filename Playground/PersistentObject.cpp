// PersistentObject.cpp: implementation of the CPersistentObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Playground.h"
#include "PersistentObject.h"
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <atlbase.h>

typedef HRESULT (WINAPI *Internal_pDllGetClassObject)(REFCLSID, REFIID, LPVOID *);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersistentObject::CPersistentObject() throw(CPersistentObject::XPersistentObject)
	: CountOfConnections(0), pConnections(0), Position(-1,-1), HIcon(0), iObject(0), HDLLInstance(0)
{
	Name[0] = ConfigName[0] = 0;
}

CPersistentObject::CPersistentObject(CPersistentObject &X) throw(CPersistentObject::XPersistentObject)
{
	InternalCopy(X);
	};

CPersistentObject::CPersistentObject(CLSID &rCLSID) throw(CPersistentObject::XPersistentObject)
	: CountOfConnections(0), pConnections(0), Position(-1,-1), HIcon(0), iObject(0), HDLLInstance(0)
{
	Name[0] = ConfigName[0] = 0;
	IClassFactory *iClF;
	if (SySal_CoGetClassObject(rCLSID, IID_IClassFactory, (void **)&iClF, &HDLLInstance) != S_OK) 
	{
		HIcon = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_MISSINGOBJ64), IMAGE_ICON, 64, 64, LR_SHARED);
//		throw XPersistentObject(0);
		}
	else
	{
		if (iClF->CreateInstance(NULL, IID_ISySalObject, (void **)&iObject) != S_OK)
		{
			iClF->Release();
			iClF = 0;
			throw XPersistentObject(1);	
			};
		iClF->Release();
		iObject->GetIcon(1, (HSySalHICON *)&HIcon);
		clsId = rCLSID;
		iObject->GetNumberOfConnections(&CountOfConnections);
		ResetConnections(CountOfConnections);
		};
	};
CPersistentObject::~CPersistentObject()
{
	if (iObject) 
	{
		iObject->Release();
		iObject = 0;
		if (HDLLInstance) CoFreeLibrary(HDLLInstance);
		};
	if (pConnections) delete [] pConnections;
}

CPersistentObject &CPersistentObject::operator=(CPersistentObject &X)
{
	InternalCopy(X);
	return *this;
	};

void CPersistentObject::InternalCopy(CPersistentObject &X)
{
	CountOfConnections = X.CountOfConnections;
	clsId = X.clsId;
	HIcon = X.HIcon;
	iObject = X.iObject;
	pConnections = X.pConnections;
	Position = X.Position;
	HDLLInstance = X.HDLLInstance;
	strncpy(Name, X.Name, SYSAL_MAX_CONN_NAME_LEN);
	strncpy(ConfigName, X.ConfigName, SYSAL_MAXCONFIG_NAME_LEN);
	X.pConnections = 0;
	X.iObject = 0;
	X.HDLLInstance = 0;
	};

///////////////////////////////////////////////////////////////////
// Custom implementation of CoGetClassObject                     //
///////////////////////////////////////////////////////////////////

HRESULT CPersistentObject::SySal_CoGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv, HINSTANCE *pHInst)
{
	char DLLPath[MAX_PATH + 1];
	wchar_t wDLLPath[MAX_PATH + 1];
	DWORD DLLNameLen = MAX_PATH;
	CRegKey ClassesKey;
	CString Temp;
	Temp.Format("Software\\Classes\\CLSID\\{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}\\InprocServer32", 
		rclsid.Data1, rclsid.Data2, rclsid.Data3, 
		rclsid.Data4[0], rclsid.Data4[1], rclsid.Data4[2], rclsid.Data4[3], 
		rclsid.Data4[4], rclsid.Data4[5], rclsid.Data4[6], rclsid.Data4[7]);
	if (ClassesKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ) != ERROR_SUCCESS) return REGDB_E_READREGDB;
	if (ClassesKey.QueryValue(DLLPath, "", &DLLNameLen) != ERROR_SUCCESS)
	{
		ClassesKey.Close();
		return REGDB_E_READREGDB;
		};
	ClassesKey.Close();
	int i;
	for (i = 0; i <= DLLNameLen; i++)
		wDLLPath[i] = (unsigned)DLLPath[i];
	HINSTANCE DLLInst = CoLoadLibrary((LPOLESTR)wDLLPath, FALSE);
	if (!DLLInst) return CO_E_DLLNOTFOUND;
	Internal_pDllGetClassObject pDllGetClassObject = (Internal_pDllGetClassObject)GetProcAddress(DLLInst, "DllGetClassObject");
	if (!pDllGetClassObject) 
	{
		CoFreeLibrary(DLLInst);
		return CO_E_DLLNOTFOUND;
		};
	*pHInst = DLLInst;
	return pDllGetClassObject(rclsid, riid, ppv);
	};
 

void CPersistentObject::ResetConnections(unsigned number)
{
	if (pConnections) 
	{
		delete [] pConnections;
		pConnections = 0;
		};
	CountOfConnections = number;
	if (number)
	{
		pConnections = new ConnectionName[CountOfConnections];
		int i;
		for (i = 0; i < CountOfConnections; i++) pConnections[i][0] = 0;
		};
}
