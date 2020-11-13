// VirtualMicroscopeClass.h : Declaration of the CVirtualMicroscopeClass

#ifndef __VIRTUALMICROSCOPECLASS_H_
#define __VIRTUALMICROSCOPECLASS_H_

#include "resource.h"       // main symbols
#include "ConfigData.h"
#include "StageEngine.h"
#include "Monitor.h"
#include "..\Common\Objective.h"
#include "..\Common\CameraSpec2.h"
#include "Marks.h"
#include "SimTracks.h"
#include "..\Common\TVectors.h"

#define NUMBER_OF_SLOTS 1

/////////////////////////////////////////////////////////////////////////////
// CVirtualMicroscopeClass
class ATL_NO_VTABLE CVirtualMicroscopeClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CVirtualMicroscopeClass, &CLSID_VirtualMicroscope>,
	public IStage, public IFrameGrabber, public IVisionProcessor2, public ISySalObject,	public ILockUnlock,
	public IClusterFinder
{
public:
	CVirtualMicroscopeClass();
	~CVirtualMicroscopeClass();

DECLARE_REGISTRY_RESOURCEID(IDR_VIRTUALMICROSCOPECLASS)
DECLARE_NOT_AGGREGATABLE(CVirtualMicroscopeClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVirtualMicroscopeClass)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(IStage)
	COM_INTERFACE_ENTRY(IFrameGrabber)
	COM_INTERFACE_ENTRY(IVisionProcessor)
	COM_INTERFACE_ENTRY(IVisionProcessor2)
	COM_INTERFACE_ENTRY(IClusterFinder)
	COM_INTERFACE_ENTRY(ILockUnlock)
END_COM_MAP()

// IFrameGrabber
public:
	STDMETHOD(VideoInfo)(VIDEOINFOSTRUCT *VIS);
	STDMETHOD(GrabInfo)(GRABBERINFOSTRUCT *GIS);

	STDMETHOD(GetPalette)(PALETTESTRUCT *PS);
	STDMETHOD(SetPalette)(PALETTESTRUCT *PS);
	STDMETHOD(SetDefaultPalette)();
	STDMETHOD(GetColorCode)(int Color, int *pCode);

	STDMETHOD(Dot)(unsigned int X, unsigned int Y, DWORD C);
	STDMETHOD(Fill)(unsigned int X, unsigned int Y, DWORD C);
	STDMETHOD(Arc)(unsigned int XC, unsigned int YC, unsigned int XR,
			unsigned int YR, double SA, double EA, DWORD C);
	STDMETHOD(ArcFill)(unsigned int XC, unsigned int YC, unsigned int XR,
			unsigned int YR, double SA, double EA, DWORD C);
	STDMETHOD(Rect)(unsigned int XS, unsigned int YS, unsigned int XE,
			unsigned int YE, DWORD C);
	STDMETHOD(RectFill)(unsigned int XS, unsigned int YS, unsigned int XE,
			unsigned int YE, DWORD C);
	STDMETHOD(Line)(unsigned int XS, unsigned int YS, unsigned int XE,
			unsigned int YE, DWORD C);
	STDMETHOD(Text)(unsigned int XS, unsigned int YS, BYTE *S, DWORD C);
	STDMETHOD(TextFont)(unsigned int F);
	STDMETHOD(TextScale)(double XS, double YS);
	STDMETHOD(Clear)(unsigned int C);
	STDMETHOD(SetZoom)(int ZX, int ZY);
	STDMETHOD(SetOffset)(int X, int Y);

	STDMETHOD(LoadCursor)(BYTE *CursorFile);
	STDMETHOD(DeleteCursor)();
	STDMETHOD(HideCursor)();
	STDMETHOD(ShowCursor)();
	STDMETHOD(SetCursorPos)(int X, int Y);
	STDMETHOD(GetCursorPos)(int *X, int *Y);

	STDMETHOD(SetNoGrab)();
	STDMETHOD(SetLiveGrab)();
	STDMETHOD(ShowLive)();
	STDMETHOD(ShowFrozen)();
	STDMETHOD(FreezeFrame)(BYTE **ppImage);
	STDMETHOD(ClearFrozen)();
	STDMETHOD(SetSingleFrameGrab)();
	STDMETHOD(HoldFrame)(BYTE **ppImage);
	STDMETHOD(ShowHeldFrame)();
	STDMETHOD(ReleaseFrame)();

	STDMETHOD(GetCurrentFrameGrabDelay)(UINT *pDelay);
	STDMETHOD(FlushGrabBackBuffers)();
	STDMETHOD(IsGrabCycleLockable)(boolean *pAnswer);
	STDMETHOD(IsGrabCycleLocked)(boolean *pAnswer);
	STDMETHOD(LoadStockCursor)(int StockCursorId);

// ILockUnlock
public:
	STDMETHOD(Lock)();
	STDMETHOD(Unlock)();

// IClusterFinder
public:
	STDMETHOD(MakeEqualization)(BYTE *pImage, BYTE *pRefLevel);
	STDMETHOD(GetCameraSpec)(CameraSpec *pSpec);
	STDMETHOD(SetCameraSpec)(CameraSpec Spec);
	STDMETHOD(GetShapeParametersStatus)(boolean *pReturn);
	STDMETHOD(GetImageEqualizationStatus)(boolean *pReturn);
	STDMETHOD(GetGrayLevelStatus)(boolean *pReturn);
	STDMETHOD(GetClusters)(BYTE *pImage, Cluster *pSpace, int *pMaxNumber, BYTE Threshold, BYTE *pBinaryImage);
	STDMETHOD(EnableGrayLevel)(boolean bEnable);
	STDMETHOD(EnableShapeParameters)(boolean bEnable);
	STDMETHOD(EnableImageEqualization)(boolean bEnable);

// IVisionProcessor2
public:
	STDMETHOD(VPGetPrimaryImage)(BYTE *pImage);
	STDMETHOD(VPGetProgramCount)(UINT *pCount);
	STDMETHOD(VPGetProgram)(UINT *pProgram);
	STDMETHOD(VPSetProgram)(UINT Program);
	STDMETHOD(VPLock2)(DWORD pfnFrameStartCallBack, DWORD Context);

// IVisionProcessor
public:
	STDMETHOD(VPGetFrameDelay)(UINT *pDelay);
	STDMETHOD(VPFlush)(Cluster *pSpace, UINT *pMaxClusters);
	STDMETHOD(VPIterate)(Cluster *pSpace, UINT *pMaxClusters);
	STDMETHOD(VPStart)();
	STDMETHOD(VPUnlock)();
	STDMETHOD(VPLock)(UINT Threshold, UINT Width, UINT Height, UINT OffX, UINT OffY, UINT WinWidth, UINT WinHeight, DWORD PresetFrames, DWORD pfnFrameStartCallBack, DWORD Context);

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
	unsigned AddTrackGrains(float Z, Cluster *pSpace, unsigned Current, unsigned Max);
	void GenerateSimTracks(float Z);
	void ComputeViewBounds(float StageX, float StageY, float &MinX, float &MaxX, float &MinY, float &MaxY);
	void GetClusters(TVector V, Cluster *pSpace, UINT *pMaxClusters);
	HANDLE HTerminate;
	HANDLE HRun;

	static void Enabler(void *pContext, bool bEnable);

	CMonitor * pMonitor;
	ConnectionName Name;
	SySalConnection Slots[NUMBER_OF_SLOTS];
	HANDLE HStatusChangeEvent;
	HANDLE HMonitorMutex;
	HANDLE HStageEngineMutex;
		
	ConfigData C;

	StageEngine StgEng;

	struct t_StageStruct
	{
		struct t_RequestedMove
		{
			bool IsValid, IsSpeed;
			float Pos, Speed, Acc;
			} Req[3];
		bool ManualControl;
		} StageStruct;

	struct VisionProcessorStruct
	{
		CameraSpec2 CAM;
		float FrameCycleTime;
		float WidthRand, HeightRand;
		float GrainSizeRand, GrainNumberRand;
		unsigned GrainProbabilityRand;
		float XGrainNoiseRand, YGrainNoiseRand;
		TVector *pVs;
		unsigned StartTime;
		int FieldCount;
		int FrameCount;
		bool IsLocked;
		bool IsSeeingMarks;
		void (*pFrameStartCallBack)(DWORD);
		DWORD Context;

		float LastZ;
		float TrackSlopeRand;
		BYTE *pSimImage;
		SimTrack *pTracks;
		} VP;

	struct SimMarkStruct
	{
		int MarkCount;
		SimMark *pMarks;
		} SM;
};

#endif //__VIRTUALMICROSCOPECLASS_H_
