// COMScanServer.h : Declaration of the CCOMScanServer

#pragma once
#include "resource.h"       // main symbols

#include "ScanServer.h"
#include "ScanServerDefs.h"


// CCOMScanServer

class ATL_NO_VTABLE CCOMScanServer : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCOMScanServer, &CLSID_SySalScanServer>,
	public IScanServer, public ISySalObject
{
public:
	CCOMScanServer();
	virtual ~CCOMScanServer();

DECLARE_REGISTRY_RESOURCEID(IDR_COMSCANSERVER)
DECLARE_NOT_AGGREGATABLE(CCOMScanServer)

BEGIN_COM_MAP(CCOMScanServer)
	COM_INTERFACE_ENTRY(IScanServer)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

// IScanServer
public:
	STDMETHOD(Connect)();
	STDMETHOD(Disconnect)();
	STDMETHOD(Send)(BYTE* pMessage);
	STDMETHOD(Receive)(BYTE* pMessageSpace);

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

protected:
	ConnectionName Name;
	HANDLE HStatusChangeEvent;

public:
	static void WINAPI ObjectMain(bool bStarting);
};

OBJECT_ENTRY_AUTO(__uuidof(SySalScanServer), CCOMScanServer)
