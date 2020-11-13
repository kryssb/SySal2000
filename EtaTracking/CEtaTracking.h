// CEtaTracking.h : Declaration of the CCEtaTracking

#ifndef __CETATRACKING_H_
#define __CETATRACKING_H_

#include "resource.h"       // main symbols
#include "..\Common\Objective.h"
#include "..\Common\IO.h"

#define NUMBER_OF_SLOTS 2

/////////////////////////////////////////////////////////////////////////////
// CCEtaTracking
class ATL_NO_VTABLE CCEtaTracking : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCEtaTracking, &CLSID_EtaTracking>,
	public ISySalObject
{
public:
	CCEtaTracking();
	~CCEtaTracking();

DECLARE_REGISTRY_RESOURCEID(IDR_CETATRACKING)
DECLARE_NOT_AGGREGATABLE(CCEtaTracking)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCEtaTracking)
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
	HWND m_hDefWnd;
	ConnectionName Name;
	SySalConnection Slots[NUMBER_OF_SLOTS];
	HANDLE HStatusChangeEvent;
	CWinThread *pAsyncExec;
	long AsyncStatus;
	HANDLE HStatusMutex;

	static UINT WINAPI AsyncExecHook(void *pOwner);
	UINT AsyncExec();

};

#endif //__CETATRACKING_H_
