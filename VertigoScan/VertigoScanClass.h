// VertigoScanClass.h : Declaration of the CVertigoScanClass

#ifndef __VERTIGOSCAN_H_
#define __VERTIGOSCAN_H_

#include "resource.h"       // main symbols
#include "..\Common\Connection.h"
#include "..\Common\Config.h"
#include "..\Common\SySalObject2Structs.h"
#include "VertigoScan.h"
#include "ConfigData.h"

#define NUMBER_OF_SLOTS 10

/////////////////////////////////////////////////////////////////////////////
// CVertigoScanClass
class ATL_NO_VTABLE CVertigoScanClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CVertigoScanClass, &CLSID_VertigoScan>,
	public ISySalObject2
{
public:
	CVertigoScanClass();
	virtual ~CVertigoScanClass();

DECLARE_REGISTRY_RESOURCEID(IDR_VERTIGOSCAN)
DECLARE_NOT_AGGREGATABLE(CVertigoScanClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVertigoScanClass)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ISySalObject2)
END_COM_MAP()

		
// ISySalObject
public:
	STDMETHOD(IsReady)(long *pWrongConn, long *pRetCode);
	STDMETHOD(AsyncResume)();
	STDMETHOD(AsyncStop)();
	STDMETHOD(AsyncPause)();
	STDMETHOD(AsyncWait)();
	STDMETHOD(AsyncCheckStatus)(long *pStatus);
	STDMETHOD(AsyncExec)(HSySalHANDLE HNotifyStatusChangeEvent);
	STDMETHOD(SyncExec)();
	STDMETHOD(GetClassName)(ConnectionName name);
	STDMETHOD(GetIcon)(int n, HSySalHICON *pHICON);
	STDMETHOD(GetConnection)(int n, SySalConnection *pConnection);
	STDMETHOD(SetConnection)(int n, SySalConnection connection);
	STDMETHOD(GetNumberOfConnections)(int *pNumber);
	STDMETHOD(EnableMonitor)(boolean bEnable);
	STDMETHOD(EditConfig)(SySalConfig *pConfig, HSySalHANDLE hWnd);
	STDMETHOD(GetConfig)(SySalConfig *pConfig);
	STDMETHOD(SetConfig)(SySalConfig *pConfig);
	STDMETHOD(GetName)(ConnectionName name);
	STDMETHOD(SetName)(ConnectionName name);

// ISySalObject2
public:

	STDMETHOD(SetConfigManagerInterface)(ConfigManagerInterface *pCMI);
	STDMETHOD(GetCLSID)(CLSID *pCLSID);

protected:
	HWND m_hDefWnd;
	ConnectionName Name;
	SySalConnection Slots[NUMBER_OF_SLOTS];
	HANDLE HStatusChangeEvent;
	CWinThread *pAsyncExec;
	long AsyncStatus;
	HANDLE HStatusMutex;

	static UINT WINAPI AsyncExecHook(void *pOwner);
	UINT AsyncExec();

	ConfigData C;

	ConfigManagerInterface CMI;

	ISySalObject *iSMCOb;
};

#endif //__VERTIGOSCAN_H_
