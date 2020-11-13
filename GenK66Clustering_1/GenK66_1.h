// GenK66_1.h : Declaration of the CGenK66_1

#ifndef __GENK66_1_H_
#define __GENK66_1_H_

#include "resource.h"       // main symbols
#include "Genesis.h"
#include <mil.h>
#include <imapi.h>
#include "Globals.h"
#include "GenesisData.h"
#include "Cluster.h"
#include "Cluster2.h"
#include "ConfigData.h"

#pragma pack(push)
#pragma pack(1)

struct IntCluster
{
	union
	{  
		float X;
		unsigned XSum;
		};
	union
	{  
		float Y;
		unsigned YSum;
		};
	int Area;
	union
	{  
		IntCluster *NextFree;
		struct
		{  
			double IXX;
      		double IXY;
			double IYY;
			} Inertia;
		};
	union
	{  
		float GrayLevel;
		unsigned GrayLevelSum;
		};
	};

struct IntBoundedCluster
{
	union
	{  
		float X;
		unsigned XSum;
		};
	union
	{  
		float Y;
		unsigned YSum;
		};
	int Area;
	union
	{  
		IntBoundedCluster *NextFree;
		struct
		{  
			double IXX;
      		double IXY;
			double IYY;
			} Inertia;
		};
	union
	{  
		float GrayLevel;
		unsigned GrayLevelSum;
		};
	struct
	{
		int MinX;
		int MaxX;
		int MinY;
		int MaxY;
		} BoundingBox;
	};


struct Segment
{
	unsigned short Left;
	unsigned short Right;
	union
	{
		IntCluster *ClusterPointer;
		IntBoundedCluster *BoundedClusterPointer;
		};
	};

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CGenK66_1

#define NUMBER_OF_SLOTS 1

class ATL_NO_VTABLE CGenK66_1 : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGenK66_1, &CLSID_GenK66_1>,
	public ILockUnlock,
	public IClusterFinder,
	public IBoundedClusterFinder,
	public ISySalObject
{
public:
	CGenK66_1(); 
	virtual ~CGenK66_1();

	ConfigData C;

DECLARE_REGISTRY_RESOURCEID(IDR_GENK66_1)
DECLARE_NOT_AGGREGATABLE(CGenK66_1)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGenK66_1)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(IClusterFinder)
	COM_INTERFACE_ENTRY(IBoundedClusterFinder)
	COM_INTERFACE_ENTRY(ILockUnlock)
END_COM_MAP()

// ILockUnlock
public:
	STDMETHOD(Lock)();
	STDMETHOD(Unlock)();

// IBoundedClusterFinder
public:
	STDMETHOD(GetBoundedClusters)(BYTE *pImage, BoundedCluster *pSpace, int *pMaxNumber, BYTE Threshold, BYTE *pBinaryImage);

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
	static HRESULT WriteConfig(SySalConfig *pConfig, ConfigData &C);
	static void WriteThresholdBuffer(SySalConfig *pC, int buffindex, ConfigData::t_ThresholdZone Z);
	static bool ReadThresholdBuffer(SySalConfig *pC, int buffindex, ConfigData::t_ThresholdZone &Z);
	static int GetSegments(BYTE *ScanLine, unsigned Length, Segment *SegSpace, PrecompSegmentBlock *PrecData);
	static IntCluster *ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1, unsigned short SegNum2, 
		unsigned short YLine, unsigned *PClusterNumber, IntCluster *NextFree);
	static IntBoundedCluster *ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1, unsigned short SegNum2, 
		unsigned short YLine, unsigned *PClusterNumber, IntBoundedCluster *NextFree);
	DWORD GetClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, Cluster *pSpace, int *pMaxNumber, 
		unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, unsigned short WinHeight);
	DWORD GetBoundedClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, BoundedCluster *pSpace, int *pMaxNumber, 
		unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, unsigned short WinHeight);

	static BYTE *cgenk66HoldFrame(void *data);
	static DWORD cgenk66ShowHeldFrame(void *data);
	static DWORD cgenk66ReleaseFrame(void *data);
	static DWORD cgenk66GetCurrentFrameGrabDelay(void *data);
	static DWORD cgenk66FlushGrabBackBuffers(void *data);

	SySalConnection Slots[NUMBER_OF_SLOTS];
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	CameraSpec CamSpec;

	double W2LLimit;
		
	Segment *SegPointer1;
	Segment *SegPointer2;

	GenesisData *pGenesisData;
	bool Locked;

	long NatFIRKernelId;
	long NatGrabCtlId;
	long SysOSB;	
	long GrabOSB[2];
	long NatGrabBufId[2];
	MIL_ID HostBinBufId[2];
	BYTE *HostBinBuf[2];
	long NatHostBinBufId[2];

	long NatSysThreadId;
	long NatDigCameraId;
	long NatDigControlId;
	long NatDigId;
	long NatBufId;
	long NatDevId;
	long NatGrabThreadId;
	long NatConvBufId;
	long NatBinBufId;

	struct BufDesc
	{
		long NatBinChildBufId;
		long NatConvChildBufId;
		} Children[MAX_THRESHOLD_ZONES];

	int CycleParity;
	unsigned CutOff;

	int HoldCount;

};

#endif //__GENK66_1_H_
