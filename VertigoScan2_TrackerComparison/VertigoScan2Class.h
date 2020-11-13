// VertigoScan2Class.h : Declaration of the CVertigoScan2Class

#ifndef __VERTIGOSCAN_H_
#define __VERTIGOSCAN_H_

#include "resource.h"       // main symbols
#include "Connection.h"
#include "Config.h"
#include "SySalObject2Structs.h"
#include "VertigoScan2.h"
#include "ConfigData.h"
#include "ScanServerDefs.h"
#include "Stage.h"

#define NUMBER_OF_SLOTS 11

/////////////////////////////////////////////////////////////////////////////
// CVertigoScan2Class
class ATL_NO_VTABLE CVertigoScan2Class : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CVertigoScan2Class, &CLSID_VertigoScan2>,
	public ISySalObject2
{
public:
	CVertigoScan2Class();
	virtual ~CVertigoScan2Class();

DECLARE_REGISTRY_RESOURCEID(IDR_VERTIGOSCAN2)
DECLARE_NOT_AGGREGATABLE(CVertigoScan2Class)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVertigoScan2Class)
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
private:
	bool ExecLoadPlate(float *pAutoZReset, IStage *iSt, Identifier id, char *textid);
	bool ExecUnloadPlate(IStage *iSt);
};

#endif //__VERTIGOSCAN_H_
