// MeteorIIClass.h : Declaration of the CMeteorII

#ifndef __METEORII_H_
#define __METEORII_H_

#include "resource.h"       // main symbols
#include "MeteorIIData.h"
#include "MeteorII.h"
#include <mil.h>
#include <imapi.h>
#include "Globals.h"

/////////////////////////////////////////////////////////////////////////////
// CMeteorII
class ATL_NO_VTABLE CMeteorII : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMeteorII, &CLSID_MeteorII>,
	public IVisionProcessor2,
	public IFrameGrabber,
	public ISySalObject
{
public:
	CMeteorII();
	virtual ~CMeteorII();

DECLARE_REGISTRY_RESOURCEID(IDR_METEORII)
DECLARE_NOT_AGGREGATABLE(CMeteorII)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMeteorII)
	COM_INTERFACE_ENTRY(ISySalObject)	
	COM_INTERFACE_ENTRY(IFrameGrabber)
	COM_INTERFACE_ENTRY(IVisionProcessor)	
	COM_INTERFACE_ENTRY(IVisionProcessor2)	
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

protected:
	ConnectionName Name;
	HANDLE HStatusChangeEvent;

	MeteorIIData M;
	bool Initialization;

	void InvalidateCursorArea(int XL, int YT, int XR, int YB);
	void UpdateCursorArea();

	struct VisionProcessorData
	{
		int TotalNodes;
		int UsedNodes;
		long MeteorSrcBuf[METEORII_GRAB_PAGE_NUM];
		long Devs[MAX_PROC_NODES], Threads[MAX_PROC_NODES], KBuf[MAX_PROC_NODES],
			ProgramKBuf[MAX_PROGRAMS][MAX_PROC_NODES], SrcBuf[3][MAX_PROC_NODES], ConvBuf[MAX_PROC_NODES], BinBuf[MAX_PROC_NODES],
			OSB[2][MAX_PROC_NODES], GrabCtrlBuf[MAX_PROC_NODES], HostBuf[2][MAX_PROC_NODES];
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

		long MeteorThread, MeteorDev, MeteorCam, MeteorGrabCtlBuf, MeteorGrabOSB[2];
		} VP;
			
	int GetSegments(BYTE *ScanLine, unsigned Length, Segment *SegSpace, PrecompSegmentBlock *PrecData);
	IntCluster *ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
		unsigned short SegNum2, unsigned short YLine, unsigned *PClusterNumber,
		IntCluster *NextFree);
	DWORD GetClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, Cluster *pSpace, int *pMaxNumber, 
		unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, 
		unsigned short WinHeight);

public:
	bool VP_Internal_GetProgramArea(unsigned program, unsigned *pOffX, unsigned *pOffY, unsigned *pWinWidth, unsigned *pWinHeight);


};

#endif //__GENESIS_H_
