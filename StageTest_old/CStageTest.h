// CStageTest.h : Declaration of the CStageTest

#ifndef __CSTAGETEST_H_
#define __CSTAGETEST_H_

#include "resource.h"       // main symbols
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CStageTest
class ATL_NO_VTABLE CStageTest : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CStageTest, &CLSID_StageTest>,
	public ISySalObject
{
public:
	CStageTest();
	virtual	~CStageTest();


DECLARE_REGISTRY_RESOURCEID(IDR_CSTAGETEST)
DECLARE_NOT_AGGREGATABLE(CStageTest)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStageTest)
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

// SYSAL_OBJECT_SLOTS_DECLARATION_BEGIN

#define NUMBER_OF_SLOTS		1
	SySalConnection Slots[NUMBER_OF_SLOTS];

// SYSAL_OBJECT_SLOTS_DECLARATION_END

	ConfigData C;
};

#endif //__CSTAGETEST_H_
