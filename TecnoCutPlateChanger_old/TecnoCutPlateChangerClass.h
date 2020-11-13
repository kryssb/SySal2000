// TecnoCutPlateChanger.h : Declaration of the CTecnoCutPlateChanger

#ifndef __TECNOCUTPLATECHANGERCLASS_H_
#define __TECNOCUTPLATECHANGERCLASS_H_

#include "resource.h"       // main symbols


#include "VPlateChanger.h"
#include "Config.h"
#include "Monitor.h"
#include "ConfigData.h"
#include "id.h"
#include "Connection.h"
#include "Stage3.h"

#define NUMBER_OF_SLOTS 1


/////////////////////////////////////////////////////////////////////////////
// CTecnoCutPlateChanger
class ATL_NO_VTABLE CTecnoCutPlateChangerClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CTecnoCutPlateChangerClass, &CLSID_TecnoCutPlateChanger>,
	public IPlateChanger,
	public ISySalObject,
	public VPlateChanger
{
public:
	CTecnoCutPlateChangerClass();
	virtual ~CTecnoCutPlateChangerClass();

DECLARE_REGISTRY_RESOURCEID(IDR_PLATECHANGER)
DECLARE_NOT_AGGREGATABLE(CTecnoCutPlateChangerClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTecnoCutPlateChangerClass)
	COM_INTERFACE_ENTRY(IPlateChanger)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()


// ITecnoCutPlateChanger
public:
	STDMETHOD(LoadPlate)(Identifier id, BYTE* pData=NULL);
	STDMETHOD(UnloadPlate)();
	STDMETHOD(EnableManualControl)(boolean bEnable);
	STDMETHOD(IsManualControlEnabled)(boolean *pbEnable);

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
public:
	ConfigData C;

protected:
	SySalConnection Slots[NUMBER_OF_SLOTS];
	IStage *iSt;
	HANDLE HOperationMutex;


	CMonitor * pMonitor;
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	HANDLE HMonitorMutex;
};




#endif //__PLATECHANGERCLASS_H_
