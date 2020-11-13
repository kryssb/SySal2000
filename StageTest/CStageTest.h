// CStageTest.h : Declaration of the CStageTest

#ifndef __CSTAGETESTCLASS_H_
#define __CSTAGETESTCLASS_H_

#include "resource.h"       // main symbols
#include "ConfigData.h"
#include "SySalObject2Structs.h"

/////////////////////////////////////////////////////////////////////////////
// CStageTest
class ATL_NO_VTABLE CStageTest : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CStageTest, &CLSID_StageTest>,
	public ISySalObject2
{
public:
	CStageTest();
	virtual	~CStageTest();


DECLARE_REGISTRY_RESOURCEID(IDR_CSTAGETEST)
DECLARE_NOT_AGGREGATABLE(CStageTest)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStageTest)
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
	HANDLE HStatusChangeEvent;
	CWinThread *pAsyncExec;
	long AsyncStatus;
	HANDLE HStatusMutex;

	static UINT WINAPI AsyncExecHook(void *pOwner);
	UINT AsyncExec();


// SYSAL_OBJECT_SLOTS_DECLARATION_BEGIN

#define NUMBER_OF_SLOTS		1
	SySalConnection Slots[NUMBER_OF_SLOTS];

// SYSAL_OBJECT_SLOTS_DECLARATION_END

	ConfigData C;

	ConfigManagerInterface CMI;

};

#endif //__CSTAGETESTCLASS_H_