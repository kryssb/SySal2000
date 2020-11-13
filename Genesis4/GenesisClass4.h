// GenesisClass.h : Declaration of the CGenesis

#ifndef __GENESIS_H_
#define __GENESIS_H_

#include "resource.h"       // main symbols
#include "GenesisData.h"
#include "GenesisData4.h"
#include "Genesis4.h"
#include <mil.h>
#include <imapi.h>
#include "Globals.h"
#include "AsyncVisionProcessorDefs.h"

#define NUMBER_OF_SLOTS 1

/////////////////////////////////////////////////////////////////////////////
// CGenesis
class ATL_NO_VTABLE CGenesis : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGenesis, &CLSID_Genesis4>,
	public IVisionProcessor3,
	public IAutomaticLightControl,
	public IFrameGrabber,
	public IGenesis,
	public ISySalObject
{
public:
	CGenesis();
	virtual ~CGenesis();

DECLARE_REGISTRY_RESOURCEID(IDR_GENESIS)
DECLARE_NOT_AGGREGATABLE(CGenesis)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGenesis)
	COM_INTERFACE_ENTRY(ISySalObject)	
	COM_INTERFACE_ENTRY(IFrameGrabber)
	COM_INTERFACE_ENTRY(IGenesis)
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

// IGenesis
public:
	STDMETHOD(UnlockInternalData)(BYTE *pData);
	STDMETHOD(LockInternalData)(BYTE **pData);

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

protected:
	ConnectionName Name;
	HANDLE HStatusChangeEvent;

	SySalConnection Slots[NUMBER_OF_SLOTS];

	GenesisData2 G;
	bool Initialization;

	void InvalidateCursorArea(int XL, int YT, int XR, int YB);
	void UpdateCursorArea();

	struct VisionProcessorData
	{
		int TotalNodes;
		int UsedNodes;
		long Devs[MAX_PROC_NODES], Threads[MAX_PROC_NODES], GrabThread[MAX_PROC_NODES], KBuf[MAX_PROC_NODES],
			ProgramKBuf[MAX_PROGRAMS][MAX_PROC_NODES], SrcBuf[3][MAX_PROC_NODES], ConvBuf[MAX_PROC_NODES], BinBuf[MAX_PROC_NODES],
			OSB[2][MAX_PROC_NODES], GrabOSB[2][MAX_PROC_NODES], Camera[MAX_PROC_NODES], GrabCtrlBuf[MAX_PROC_NODES],
			HostBuf[2][MAX_PROC_NODES], AstygCompBuf[MAX_PROGRAMS][MAX_PROC_NODES];
		BYTE *pHostBuf[2][MAX_PROC_NODES];

		long DispBuf;

		int ActiveProgram;
		int CycleParity;
		int CutOff;
		unsigned Width, Height, OffX, OffY, WinWidth, WinHeight;
		bool Locked;

		Segment *SegPointer1;
		Segment *SegPointer2;
		UINT FrameCount;

		void (*pFrameStartCallBack)(DWORD);
		DWORD Context;

		t_ExtendedOperation ExtendedOperation;
		t_VisionProcessorLibrary ProgramLibrary;

		struct t_FrameRoutingInfo
		{
			int Node;
			int LocalFrameNumber;
			double TimeStamp[2];
			} FrameRouting[MAX_PROC_NODES * MAX_FRAMES_PER_NODE];

		struct t_SequenceProgram
		{
			int FrameCount;
			int ActiveProgram;
			int LastFrame[MAX_PROC_NODES];

#define VP_PROGRAM_NULL			0
#define VP_PROGRAM_VALID		1
#define VP_PROGRAM_RUNNING		2
#define VP_PROGRAM_CLUSTERING	3

			int Status;
			AsyncImageSequence AIS;
			} SequencePrograms[3];

		int MaxAsyncFrames;
		long AsyncCtlThread;
		long AsyncGrabStartOSB[MAX_PROC_NODES];
		long AsyncGrabFrameEndOSB[MAX_PROC_NODES][MAX_FRAMES_PER_NODE];
		long AsyncProcEndOSB[MAX_PROC_NODES];
		long AsyncHostBinBuf[2][MAX_PROC_NODES][MAX_FRAMES_PER_NODE];
		BYTE *pAsyncHostBinBuf[2][MAX_PROC_NODES][MAX_FRAMES_PER_NODE];

		double AsyncTimeZero[2];
		double AsyncTimeOffset[MAX_PROC_NODES];

		int AsyncSequenceParity;

		int CommandQueueLength;
		} VP;

	struct LightControlData : public t_LightControlSettings
	{
		long OSB;
		long CamId;
		long GrabBuf;
		long HistoBuf;
		long NatThreadId;
		int *pHisto;
		} LC;
			
	int GetSegments(BYTE *ScanLine, unsigned Length, Segment *SegSpace, PrecompSegmentBlock *PrecData);
	IntCluster *ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
		unsigned short SegNum2, unsigned short YLine, unsigned *PClusterNumber,
		IntCluster *NextFree);
	DWORD GetClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, Cluster *pSpace, int *pMaxNumber, 
		unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, 
		unsigned short WinHeight);

public:
	bool LC_CanSetLightLevel();
	void LC_Get_LightInfo(float *pGrayLev, float *pSatLev, bool RestoreState = true);
	STDMETHOD(VPWaitForClusters)();
	bool VP_Internal_GetProgramArea(unsigned program, unsigned *pOffX, unsigned *pOffY, unsigned *pWinWidth, unsigned *pWinHeight);
	int VP_Internal_GetAvailableProcessors();
	int VP_Internal_GetMaxAsyncFrames();
	float VP_Internal_GetFrameRate();
	int VP_Internal_GetCommandQueueLength();

};

#endif //__GENESIS_H_
