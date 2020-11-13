// PlateChanger.h : Declaration of the CPlateChanger

#ifndef __PLATECHANGERCLASS_H_
#define __PLATECHANGERCLASS_H_

#include "resource.h"       // main symbols
#include "Config.h"
#include "Monitor.h"
#include "ConfigData.h"
#include "id.h"

/////////////////////////////////////////////////////////////////////////////
// CPlateChanger
struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

class ATL_NO_VTABLE CPlateChangerClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CPlateChangerClass, &CLSID_PlateChanger>,
	public IPlateChanger,
	public ISySalObject
{
public:
	CPlateChangerClass();
	virtual ~CPlateChangerClass();

DECLARE_REGISTRY_RESOURCEID(IDR_PLATECHANGER)
DECLARE_NOT_AGGREGATABLE(CPlateChangerClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPlateChangerClass)
	COM_INTERFACE_ENTRY(IPlateChanger)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()


// IPlateChanger
public:
	STDMETHOD(LoadPlate)(Identifier id);
	STDMETHOD(UnloadPlate)();
	STDMETHOD(EnableManualControl)(boolean bEnable);
	STDMETHOD(IsManualControlEnabled)(boolean *pbEnable);

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

	CMonitor * pMonitor;
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	HANDLE HMonitorMutex;

	ConfigData C;

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

};

#endif //__PLATECHANGERCLASS_H_
