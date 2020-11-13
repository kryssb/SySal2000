// BBrain.h : Declaration of the CBBrain

#ifndef __BBRAIN_H_
#define __BBRAIN_H_

#include "resource.h"       // main symbols
#include "Connection.h"
#include "Config.h"
#include "IO.h"
#include "SheetMap.h"
#include "BrainStructs.h"

#define NUMBER_OF_SLOTS 11

/////////////////////////////////////////////////////////////////////////////
// CBBrain
struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

class ATL_NO_VTABLE CBBrain : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CBBrain, &CLSID_BetaBrain>,
	public ISySalObject
{
public:
	CBBrain();
	virtual ~CBBrain();

DECLARE_REGISTRY_RESOURCEID(IDR_BBRAIN)
DECLARE_NOT_AGGREGATABLE(CBBrain)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBBrain)
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
	HANDLE HTerminateEvent;

	SetupData SD;
	CScanner Scanner;

	static UINT WINAPI AsyncExecHook(void *pOwner);
	UINT AsyncExec();

	bool OkToRun;
	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);
};


#endif //__BBRAIN_H_
