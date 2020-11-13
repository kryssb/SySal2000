// OdysseyClass.h : Declaration of the COdyssey

#ifndef __ODYSSEY_H_
#define __ODYSSEY_H_

#include "resource.h"       // main symbols
#include "OdysseyData.h"
#include "Odyssey1.h"
#include <imapi.h>
#include "Globals.h"
#include "AsyncVisionProcessorDefs.h"
#include "WndDisplay.h"

#define NUMBER_OF_SLOTS 2
#define COMMANDS_BEFORE_REFRESH 30000
#define MAX_CLUSTERS 10000

/////////////////////////////////////////////////////////////////////////////
// COdyssey
class ATL_NO_VTABLE COdyssey : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<COdyssey, &CLSID_Odyssey1>,
	public IVisionProcessor3,
	public IAutomaticLightControl,
	public IFrameGrabber,
	public ISySalObject
{
public:
	COdyssey();
	virtual ~COdyssey();

DECLARE_REGISTRY_RESOURCEID(IDR_ODYSSEY)
DECLARE_NOT_AGGREGATABLE(COdyssey)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(COdyssey)
	COM_INTERFACE_ENTRY(ISySalObject)	
	COM_INTERFACE_ENTRY(IFrameGrabber)
	COM_INTERFACE_ENTRY(IVisionProcessor)	
	COM_INTERFACE_ENTRY(IVisionProcessor2)	
	COM_INTERFACE_ENTRY(IVisionProcessor3)	
	COM_INTERFACE_ENTRY(IAutomaticLightControl)
END_COM_MAP()

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

// IAutomaticLightControl
public:
	STDMETHOD(SetLightLevel)();

// IVisionProcessor3
public:
	STDMETHOD(VPStartAsyncProcessing)();
	STDMETHOD(VPPrepareAsyncProcessing)(UINT Program, AsyncImageSequence ImageSeq);
	STDMETHOD(VPWaitForProcessingComplete)();
	STDMETHOD(VPGetCurrentImageSequenceDelay)(int *pDelay);
	STDMETHOD(VPWaitForClusters)();

protected:
	void ProgramProcessing(bool SkipImagePreprocessing = false, bool StoreConv = false);
	ConnectionName Name;
	HANDLE HStatusChangeEvent;

	SySalConnection Slots[NUMBER_OF_SLOTS];

	OdysseyData O;
	bool Initialization;

	void InvalidateCursorArea(int XL, int YT, int XR, int YB);
	void UpdateCursorArea();

	void SendProcessingCommands(UINT ActiveProgram, int SequenceIndex, int ImageCount, bool SkipImagePreprocessing = false, bool StoreConv = false);

	static int GetSegments(BYTE *ScanLine, unsigned Length, Segment *SegSpace, PrecompSegmentBlock *PrecData);
	static IntCluster *ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
		unsigned short SegNum2, unsigned short YLine, unsigned *PClusterNumber,
		IntCluster *NextFree);
	static DWORD GetClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, Cluster *pSpace, int *pMaxNumber, 
		unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, 
		unsigned short WinHeight, Segment *SegPointer1, Segment *SegPointer2);

	static UINT WINAPI ClusterThreadHook(void *ActRecord);
	static void GetClusters(OdysseyData::t_ActivationRecord *pAR);

	static UINT WINAPI RefreshThreadHook(void *owner);
	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

	CWndDisplay *pWndDisplay;
	HBRUSH m_BackgroundBrush;

	int CommandCount;

	HANDLE HRefreshDeviceMutex;
	void RefreshDevice();
	BYTE *pOvrSave;

public:
	double VP_Internal_MeasureProcessingTime(UINT program);
	static void FG_Internal_SetStill(DWORD Context);
	static void FG_Internal_SetLive(DWORD Context);
	static void FG_Internal_LoadGrabBuffer(DWORD Context, int bank, int number);
	static void FG_Internal_Clear(DWORD Context);
	static void FG_Internal_DrawCircles(DWORD Context);
	void VP_Internal_MakeFlatFieldImage(BYTE *pImg, int imgcount);
	bool LC_CanSetLightLevel();
	void LC_Get_LightInfo(float *pGrayLev, float *pSatLev, float *pGraySpread, int **pHisto);
	bool VP_Internal_GetProgramArea(unsigned program, unsigned *pOffX, unsigned *pOffY, unsigned *pWinWidth, unsigned *pWinHeight);
	float VP_Internal_GetFrameRate();
	int VP_Internal_GetCommandQueueLength();
	int VP_Internal_GetMaxAsyncFrames();
	bool VP_Internal_AsyncAcquireWithForcedCutOff(unsigned program, int cutoff, Cluster *pSpace, int *pMaxClusters);
	void VP_Internal_OptimizeLocalThreshold(int program, int xsamples, int ysamples, int w, int h, float minmult, float maxmult, int minarea, int steps, int *pcounts);
	bool VP_Internal_CanMoveStage();

	long GetProcThread() { return O.ProcThread; };
};

#endif //__ODYSSEY_H_
