// SySalObject.h : Declaration of the CSySalObject

#ifndef __SYSALOBJECT_H_
#define __SYSALOBJECT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSySalObject
class ATL_NO_VTABLE CSySalObject : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSySalObject, &CLSID_SySalObject>,
	public ISySalObject
{
public:
	CSySalObject()
	{
		Name[0] = 0;
		HStatusChangeEvent = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYSALOBJECT)
DECLARE_NOT_AGGREGATABLE(CSySalObject)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSySalObject)
	COM_INTERFACE_ENTRY(ISySalObject)
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

protected:
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
};

#endif //__SYSALOBJECT_H_
