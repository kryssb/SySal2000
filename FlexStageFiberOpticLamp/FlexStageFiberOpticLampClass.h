// FlexStageFiberOpticLamp.h : Declaration of the CFlexStageFiberOpticLamp

#ifndef __FLEXSTAGEFIBEROPTICLAMPCLASS_H_
#define __FLEXSTAGEFIBEROPTICLAMPCLASS_H_

#include "resource.h"       // main symbols
#include "Config.h"
#include "Monitor.h"
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CFlexStageFiberOpticLamp
struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

class ATL_NO_VTABLE CFlexStageFiberOpticLamp : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFlexStageFiberOpticLamp, &CLSID_FlexStageFiberOpticLamp>,
	public IStage,
	public ISySalObject
{
public:
	CFlexStageFiberOpticLamp();
	virtual ~CFlexStageFiberOpticLamp();

DECLARE_REGISTRY_RESOURCEID(IDR_FLEXSTAGE)
DECLARE_NOT_AGGREGATABLE(CFlexStageFiberOpticLamp)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFlexStageFiberOpticLamp)
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
	bool SetBoard(bool InitLight = false);
	HANDLE HTerminate;
	HANDLE HRun;
	UINT RefreshThread();
	CWinThread * pRefreshThread;

	CMonitor * pMonitor;
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	HANDLE HMonitorMutex;

    WORD LightLevel;
	struct RequestedMove
	{
		bool Valid;
		bool IsSpeed;
      	float Pos, Speed, Acc;
        float ManSpeed;
	   	} ReqX, ReqY, ReqZ;

	ConfigData C;

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);
};

#endif //__FLEXSTAGECLASS_H_
