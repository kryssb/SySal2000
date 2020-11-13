// RemStage.h : Declaration of the CRemoteStage

#ifndef __REMOTESTAGE_H_
#define __REMOTESTAGE_H_

#include "resource.h"       // main symbols
#include "Monitor.h"

/////////////////////////////////////////////////////////////////////////////
// CRemoteStage
class ATL_NO_VTABLE CRemoteStage : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRemoteStage, &CLSID_RemoteStage>,
	public IStage,
	public ISySalObject
{
public:
	CRemoteStage();
	virtual ~CRemoteStage();

DECLARE_REGISTRY_RESOURCEID(IDR_REMOTESTAGE)
DECLARE_NOT_AGGREGATABLE(CRemoteStage)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRemoteStage)
	COM_INTERFACE_ENTRY(IStage)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// IStage
public:
	STDMETHOD(Reset)(int Axis);
	STDMETHOD(IsManualControlEnabled)(boolean *pReturn);
	STDMETHOD(EnableManualControl)(boolean Enable);
	STDMETHOD(GetLimiter)(int Axis, int *pLim);
	STDMETHOD(GetPos)(int Axis, float *pPos);
	STDMETHOD(Stop)(int Axis);
	STDMETHOD(SpeedMove)(int Axis, float Speed, float Acc);
	STDMETHOD(PosMove)(int Axis, float Pos, float Speed, float Acc);
	STDMETHOD(SetLight)(int LightLevel);
	STDMETHOD(GetLight)(int *pLightLevel);

// ISySalObject
public:
	static void Enabler(void *pContext, bool bEnable);
	static UINT RefreshThreadHook(void *pOwner);
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
	HANDLE HTerminate;
	HANDLE HRun;
	UINT RefreshThread();
	CWinThread * pRefreshThread;
	HANDLE HCOM;
	HANDLE HCOMMutex;

	CMonitor * pMonitor;
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	HANDLE HMonitorMutex;

};

#endif //__REMOTESTAGE_H_
