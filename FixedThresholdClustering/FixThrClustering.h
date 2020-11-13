// FixThrClustering.h : Declaration of the CFixThrClustering

#ifndef __FIXTHRCLUSTERING_H_
#define __FIXTHRCLUSTERING_H_

#include "resource.h"       // main symbols

// Internal structures

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

struct Segment
{
	IntCluster *ClusterPointer;
	unsigned short Left;
	unsigned short Right;
	unsigned GrayLevel;
	};

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CFixThrClustering
class ATL_NO_VTABLE CFixThrClustering : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFixThrClustering, &CLSID_FixedThresholdClustering>,
	public IClusterFinder,
	public ISySalObject
{
public:
	CFixThrClustering()
	{
		Name[0] = 0;
		HANDLE HStatusChangeEvent = 0;
		CamSpec.Width = CamSpec.Height = 0;
		CamSpec.WinWidth = CamSpec.WinHeight = 0;
		CamSpec.OffX = CamSpec.OffY = 0;
		CamSpec.PixelToMicronX = CamSpec.PixelToMicronY = 1.f;
		SegPointer1 = SegPointer2 = 0;
		LightBias = 0;
		EnableEq = false;
	}

	virtual ~CFixThrClustering()
	{
		if (LightBias) delete [] LightBias;
		if (SegPointer1) delete [] SegPointer1;
		if (SegPointer2) delete [] SegPointer2;
		};

DECLARE_REGISTRY_RESOURCEID(IDR_FIXTHRCLUSTERING)
DECLARE_NOT_AGGREGATABLE(CFixThrClustering)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFixThrClustering)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(IClusterFinder)
END_COM_MAP()

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
	bool EnableEq;
	void ResetLightBias();
	unsigned short GetSegments(BYTE *ScanLine, unsigned short Len, Segment *SegmentArray, WORD Threshold);
	IntCluster *ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1, unsigned short SegNum2, unsigned short YLine, int LightBias, unsigned *PClusterNumber, IntCluster *NextFree);

	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	CameraSpec CamSpec;
	Segment *SegPointer1;
	Segment *SegPointer2;
	BYTE *LightBias;

};

#endif //__FIXTHRCLUSTERING_H_
