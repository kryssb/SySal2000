// TSRecon.h : Declaration of the CTSRecon

#ifndef __TSRECON_H_
#define __TSRECON_H_

#include "resource.h"       // main symbols
#define USE_MIDL_INCOMPATIBLE_STRUCTS
#include "..\Common\IO.h"
#include "EditConfig.h"
#include "TSReconData.h"
#include "..\Common\SySalObject2Structs.h"

#define NUMBER_OF_SLOTS 2

/////////////////////////////////////////////////////////////////////////////
// CTSRecon
struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

class ATL_NO_VTABLE CTSRecon : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CTSRecon, &CLSID_TSReconstruct>,
	public ISySalObject2
{
public:
	CTSRecon();
	~CTSRecon();

DECLARE_REGISTRY_RESOURCEID(IDR_TSRECON)
DECLARE_NOT_AGGREGATABLE(CTSRecon)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTSRecon)
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

	TSReconData T;
	bool OkToRun;

	ConfigManagerInterface CMI;

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);
};

#endif //__TSRECON_H_
