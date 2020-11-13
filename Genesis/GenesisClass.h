// GenesisClass.h : Declaration of the CGenesis

#ifndef __GENESIS_H_
#define __GENESIS_H_

#include "resource.h"       // main symbols
#include "GenesisData.h"
#include "Genesis.h"
#include <mil.h>
#include <imapi.h>
#include "Globals.h"

/////////////////////////////////////////////////////////////////////////////
// CGenesis
class ATL_NO_VTABLE CGenesis : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGenesis, &CLSID_Genesis>,
	public IVisionProcessor,
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
END_COM_MAP()



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
	STDMETHOD(Text)(unsigned int XS, unsigned int YS, unsigned char *S, DWORD C);
	STDMETHOD(TextFont)(unsigned int F);
	STDMETHOD(TextScale)(double XS, double YS);
	STDMETHOD(Clear)(unsigned int C);
	STDMETHOD(SetZoom)(int ZX, int ZY);
	STDMETHOD(SetOffset)(int X, int Y);

	STDMETHOD(LoadCursor)(unsigned char *CursorFile);
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

	GenesisData G;
	bool Initialization;

	void InvalidateCursorArea(int XL, int YT, int XR, int YB);
	void UpdateCursorArea();

	struct VisionProcessorData
	{
		long NatFIRKernelId;
		long NatGrabCtlId;
		long SysOSB;	
		long GrabOSB[2];
		long NatGrabBufId[2];
		MIL_ID HostBinBufId[2];
		BYTE *HostBinBuf[2];
		long NatHostBinBufId[2];
		long NatBinBuf;

		long NatSysThreadId;
		long NatDigCameraId;
		long NatDigControlId;
		long NatDigId;
		long NatBufId;
		long NatDevId;
		long NatGrabThreadId;
		long NatConvBufId;

		int CycleParity;
		unsigned CutOff;
		unsigned Width, Height, OffX, OffY, WinWidth, WinHeight;
		bool Locked;

		Segment *SegPointer1;
		Segment *SegPointer2;
		UINT FrameCount;

		void (*pFrameStartCallBack)(DWORD);
		DWORD Context;
		} VP;
			
	int GetSegments(BYTE *ScanLine, unsigned Length, Segment *SegSpace, PrecompSegmentBlock *PrecData);
	IntCluster *ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
		unsigned short SegNum2, unsigned short YLine, unsigned *PClusterNumber,
		IntCluster *NextFree);
	DWORD GetClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, Cluster *pSpace, int *pMaxNumber, 
		unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, 
		unsigned short WinHeight);


};

#endif //__GENESIS_H_
