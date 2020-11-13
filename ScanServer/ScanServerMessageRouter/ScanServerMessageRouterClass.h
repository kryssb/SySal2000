// ScanServerMessageRouterClass.h : Declaration of the CScanServerMessageRouterClass
#ifndef SYSAL_SCANSERVER_MESSAGE_ROUTER_H
#define SYSAL_SCANSERVER_MESSAGE_ROUTER_H

#include "resource.h"       // main symbols

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "resource.h"       // main symbols
#include "ScanServerDefs.h"
#include "ScanServerMessageRouter.h"
#include "..\ScanServerMessageRouterData.h"

/////////////////////////////////////////////////////////////////////////////
// CScanServerMessageRouterClass
class ATL_NO_VTABLE CScanServerMessageRouterClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CScanServerMessageRouterClass, &CLSID_ScanServerMessageRouter>,
	public IScanServer, public ISySalObject, public IScanServerMessageRouter
{
public:
	CScanServerMessageRouterClass();

DECLARE_REGISTRY_RESOURCEID(IDR_SCANSERVERMESSAGEROUTER)
DECLARE_NOT_AGGREGATABLE(CScanServerMessageRouterClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CScanServerMessageRouterClass)
	COM_INTERFACE_ENTRY(IScanServerMessageRouter)
	COM_INTERFACE_ENTRY(IScanServer)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// IScanServerMessageRouter
public:
	STDMETHOD(SetMessageRoutingMap)(ScanServerMessageRoutingMap * pMap);

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
	ScanServerMessageRoutingMap RoutingMap;
};


#endif
