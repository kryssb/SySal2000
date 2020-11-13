// VSScanServer.h : Declaration of the CVSScanServer

#ifndef __VSSCANSERVERCLASS_H_
#define __VSSCANSERVERCLASS_H_

#include "resource.h"       // main symbols
#include "ScanServerDefs.h"
#include "VSScanServerNET.h"


/////////////////////////////////////////////////////////////////////////////
// CRCtlSrv
class ATL_NO_VTABLE CVSScanServerNET : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CVSScanServerNET, &CLSID_VSScanServerNET>,
	public IScanServer, public ISySalObject
{
public:
	CVSScanServerNET();

DECLARE_REGISTRY_RESOURCEID(IDR_VSSCANSERVER)
DECLARE_NOT_AGGREGATABLE(CVSScanServerNET)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVSScanServerNET)
	COM_INTERFACE_ENTRY(IScanServer)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

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
};

#endif //__VSSCANSERVER_H_
