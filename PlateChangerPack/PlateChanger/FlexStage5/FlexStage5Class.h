// FlexStage5.h : Declaration of the CFlexStage5

#ifndef __FLEXSTAGECLASS_H_
#define __FLEXSTAGECLASS_H_

#include "resource.h"       // main symbols
#include "Config.h"
#include "Monitor.h"
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CFlexStage5
struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

class ATL_NO_VTABLE CFlexStage5 : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFlexStage5, &CLSID_FlexStage5>,
	public IStage3,
	public ISySalObject, 
	public ISySalObjectMachineDefaults,
	public IDigitalIO
{
public:
	CFlexStage5();
	virtual ~CFlexStage5();

DECLARE_REGISTRY_RESOURCEID(IDR_FLEXSTAGE)
DECLARE_NOT_AGGREGATABLE(CFlexStage5)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFlexStage5)
	COM_INTERFACE_ENTRY(IDigitalIO)
	COM_INTERFACE_ENTRY(IStage3)
	COM_INTERFACE_ENTRY(IStage2)
	COM_INTERFACE_ENTRY(IStage)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ISySalObjectMachineDefaults)
END_COM_MAP()

// IDigitalIO
public:
	STDMETHOD(DigitalIOReset)();	
	STDMETHOD(GetDigitalIOPortCount)(int *pnumberofports);
	STDMETHOD(SetDigitalPortPolarity)(int port, boolean polarity);
	STDMETHOD(SetDigitalPortDirection)(int port, int input_bit_mask);
	STDMETHOD(DigitalOut)(int port, int mask_on, int mask_off);
	STDMETHOD(DigitalIn)(int port, int *pconfiguration);

// IStage3
public:
	STDMETHOD(FindHome)();
	STDMETHOD(IsHomeKnown)();
	STDMETHOD(SetXYRef)(BYTE *name, float x, float y);
	STDMETHOD(GetXYRef)(BYTE *name, float *px, float *py);
	STDMETHOD(GoToXYRef)(BYTE *name);
	STDMETHOD(SetZRef)(BYTE *name, float z);
	STDMETHOD(GetZRef)(BYTE *name, float *pz);
	STDMETHOD(GoToZRef)(BYTE *name);


// IStage2
public:
	STDMETHOD(GetMaxZScanZSamples)(int *pMaxZSamples);
	STDMETHOD(PrepareAsyncGoTo3DMotion)(AsyncGoTo3DTrajectory *pAGT);
	STDMETHOD(PrepareAsyncZScanMotion)(AsyncZScanTrajectory *pAST);
	STDMETHOD(WaitForAsyncMotionComplete)(DWORD pfnAbortCallback, DWORD Context);
	STDMETHOD(WaitForAsyncZScanZComplete)(DWORD pfnAbortCallback, DWORD Context);
	STDMETHOD(StartAsyncMotion)();

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


// ISySalObjectMachineDefaults
public:
	STDMETHOD(EditMachineDefaults)(SySalConfig *pConfig, HSySalHANDLE hWnd);
	STDMETHOD(GetMachineDefaults)(SySalConfig *pConfig);
	STDMETHOD(SetMachineDefaults)(SySalConfig *pConfig);

// ISySalObject
public:
	STDMETHOD(FlushAsyncMotions)();
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
	void ResetLampTimeout(bool force = false);
	static void ResetLampTimeoutHook(void *pcontext, bool force);
	bool SetBoard(bool InitLight = false);	
	static void HomeHook(void *powner);

	void EmptyRefPosList();
	void SetRefPos(RefPos &r);
	bool GetRefPos(RefPos &r);
	void DelRefPos(char *name, bool isz);

	int RefPosCount;
	RefPos *pRefPos;
	int MachineDefaultRefPosCount;
	RefPos *pMachineDefaultRefPos;

	HANDLE HTerminate;
	HANDLE HRun;
	UINT RefreshThread();
	CWinThread * pRefreshThread;
	int LampTimeoutEnd;

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
		float LastPos;
		int Time;
	   	} ReqX, ReqY, ReqZ;

	ConfigData C;

	struct t_AsyncMotion
	{
		struct t_Program
		{
			float StartZ;
			bool IsZScan;
			AsyncZScanTrajectory Traj;
			bool IsValid;
			bool IsRunning;
			int ZScanEndTime;
			int XYZMotionEndTime;
			} Programs[2];
		int ProgramIndex;
		} AM;

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);
	static bool AZSTest(DWORD Context, AsyncZScanTrajectory *pAZS, float *pSamples);

	bool TestModeOn;

private:

	//WARNING!!! DEBUGGING ONLY!!!
	static void ExecTestProfile();
	static CFlexStage5 *pSt;

	int Zero;
};

#endif //__FLEXSTAGECLASS_H_
