// VertigoScan6Class.h : Declaration of the CVertigoScan6Class

#ifndef __VERTIGOSCAN_H_
#define __VERTIGOSCAN_H_

#include "resource.h"       // main symbols
#include "Connection.h"
#include "Config.h"
#include "SySalObject2Structs.h"
#include "VertigoScan6.h"
#include "ConfigData.h"
#include "ScanServerDefs.h"
#include "Stage.h"
#include "PlateChanger.h"
#ifdef ENABLE_NET
#include "Client.h"
#include <vcclr.h>
#endif

#define NUMBER_OF_SLOTS 12

/////////////////////////////////////////////////////////////////////////////
// CVertigoScan6Class
class ATL_NO_VTABLE CVertigoScan6Class : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CVertigoScan6Class, &CLSID_VertigoScan6>,
	public ISySalObject2,
	public IDAQSynchronize
{
public:
	CVertigoScan6Class();
	virtual ~CVertigoScan6Class();

DECLARE_REGISTRY_RESOURCEID(IDR_VERTIGOSCAN6)
DECLARE_NOT_AGGREGATABLE(CVertigoScan6Class)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVertigoScan6Class)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ISySalObject2)
	COM_INTERFACE_ENTRY(IDAQSynchronize)
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

// IDAQSynchronize
public:
	STDMETHOD(IsSyncEnabled)(boolean *pbIsEnabled);

protected:
	HWND m_hDefWnd;
	ConnectionName Name;
	SySalConnection Slots[NUMBER_OF_SLOTS];
	HANDLE HStatusChangeEvent;
	CWinThread *pAsyncExec;
	long AsyncStatus;
	HANDLE HStatusMutex;
	bool ShouldStop;

	static UINT WINAPI AsyncExecHook(void *pOwner);
	UINT AsyncExec();	

	ConfigData C;

	ConfigManagerInterface CMI;

	ISySalObject *iSMCOb;
#ifdef ENABLE_NET
	gcroot<SySal::DAQSystem::TrackingClient ^> TkClient;
#endif
private:
	bool ExecLoadPlate(float *pAutoZReset, IStage *iSt, IPlateChanger *iPc, Identifier id, char *textid);
	bool ExecUnloadPlate(IStage *iSt, IPlateChanger *iPc);
	bool ExecSetParam(char *objname, char *paramname, char *paramvalue);
};

#endif //__VERTIGOSCAN_H_
