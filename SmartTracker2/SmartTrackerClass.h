// SmartTrackerClass.h : Declaration of the CSmartTrackerClass

#ifndef __SMARTTRACKERCLASS_H_
#define __SMARTTRACKERCLASS_H_

#include "resource.h"       // main symbols
#include "Config.h"
#include "Config2.h"
#include "Connection.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "CameraSpec.h"
#include "Vectors.h"
#include "TVectors.h"
#include "Track.h"
#include "Track2.h"
#include "ConfigData.h"

#pragma pack(push)
#pragma pack(4)

struct IntCluster
{
	float X;
	float Y;
	int Area;
	union
	{	IntCluster *NextFree;
		struct
		{
			double IXX;
			double IXY;
			double IYY;
			} Inertia;
		};
	float GrayLevel;
	};

struct IntGrain
{
	float Xcm;
	float Ycm;
	int Area;
	int TrackLength;
	union
	{
		Track *pTrack;
		Track2 *pTrack2;
		};
	};

union IntTrackVector
{
	TVector V;
	struct 
	{
		IntGrain *pG;
		float Z;
		} T;
	};

union IntTrackGrain
{
	Grain G;
	struct 
	{
		IntGrain *pG;
		float Z;
		} T;
	};

struct Cell
{
	union
	{	IntCluster *FirstC;
		IntGrain *FirstG;
		};
	int Free;

	IntGrain *FindGrain(float x, float y, float dirx, float diry, float dirtol, float normtol);
	};

struct Window
{
	float Xmin;
	float Xmax;
	float Ymin;
	float Ymax;
	};

#pragma pack(pop)

struct TrackerData : public ConfigData
{
	IntGrain *GrainSpace;
	float *ZLayer;
	IntGrain **LayerGrains;
	Cell *CellSpace;
	int CellsInLayer;
	Window Win;
	float DxCell;
	float DyCell;
	float PixelToMicronX;
	float PixelToMicronY;
	int NumGrains;
	int Layer;
	};

/////////////////////////////////////////////////////////////////////////////
// CSmartTrackerClass
class ATL_NO_VTABLE CSmartTrackerClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSmartTrackerClass, &CLSID_SmartTracker>,
	public ITracker3,	
	public ISySalObject
{
public:
	CSmartTrackerClass()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		Name[0] = 0;
		HStatusChangeEvent = 0;
		CamSpec.Width = CamSpec.Height = 0;
		CamSpec.WinWidth = CamSpec.WinHeight = 0;
		CamSpec.OffX = CamSpec.OffY = 0;
		CamSpec.PixelToMicronX = CamSpec.PixelToMicronY = 1.f;
		InitTrackerData();
		OkToRun = false;
	}	

	virtual ~CSmartTrackerClass()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		if (T.GrainSpace)
		{	GlobalFree(T.GrainSpace);
			T.GrainSpace = 0;
			};
		if (T.ZLayer)
		{	GlobalFree(T.ZLayer);
			T.ZLayer = 0;
			};
		if (T.LayerGrains)
		{	GlobalFree(T.LayerGrains);
			T.LayerGrains = 0;
			};
		if (T.CellSpace)
		{	GlobalFree(T.CellSpace);
			T.CellSpace = 0;
			};
		};

DECLARE_REGISTRY_RESOURCEID(IDR_SMARTTRACKER)
DECLARE_NOT_AGGREGATABLE(CSmartTrackerClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSmartTrackerClass)
	COM_INTERFACE_ENTRY(ITracker)
	COM_INTERFACE_ENTRY(ITracker2)
	COM_INTERFACE_ENTRY(ITracker3)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// ITracker3
public:
	STDMETHOD(GetTracks2)(Track2 *pSpace, int *pMaxNumber, int StartLayer, int EndLayer);

// ITracker2
public:
	STDMETHOD(GetFlatTracks)(FlatTrack *pSpace, int *pMaxNumber, int MaxStripsInTrack, int StartLayer, int EndLayer);
	STDMETHOD(GetFlatStrips)(int Layer, FlatStrip *pSpace, int *pMaxNumber, float *pZ);

// ITracker
public:
	STDMETHOD(GetSlopePresetStatus)(boolean *pSlPresEnable);
	STDMETHOD(EnableSlopePresetting)(boolean SlPresEnable);
	STDMETHOD(PresetSlope)(float SX, float SY, float AccX, float AccY);
	STDMETHOD(GetClusters)(int Layer, Cluster *pSpace, int *pMaxNumber, float *pZ);
	STDMETHOD(GetTracks)(Track *pSpace, int *pMaxNumber, int StartLayer, int EndLayer);
	STDMETHOD(PutClusters)(Cluster *pClusters, int CountOfClusters, float Z);
	STDMETHOD(GetCameraSpec)(CameraSpec *pSpec);
	STDMETHOD(SetCameraSpec)(CameraSpec Spec);
	STDMETHOD(StartFilling)();

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
	void InitTrackerData();
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	CameraSpec CamSpec;
	TrackerData T;
	bool OkToRun;

	int GetCell(float Xp, float Yp);
	IntGrain *FindGrain(float expx, float expy, Cell *pCellLayer, float dirx, float diry, float dirtol);
	void GetDirAndTol(float SlopeX, float SlopeY, float avgdz, float *pDirX, float *pDirY, float *pdirtol);
	void InsertNewTrack(IntGrain **pTempGrains, int Layers, int SequenceLength, Track *pTracks, int &NTracks);
	void InsertNewTrack(IntGrain **pTempGrains, int Layers, int SequenceLength, Track2 *pTracks, int &NTracks);
	int FinalizeTracks(int ntracks, Track *pspace);
	int FinalizeTracks(int ntracks, Track2 *pspace);
};

#endif //__THIN3DTRK_H_