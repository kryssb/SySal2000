// Thick3DTrk.h : Declaration of the CThick3DTracker

#ifndef __THICK3DTRK_H_
#define __THICK3DTRK_H_

#include "resource.h"       // main symbols
#include "..\Common\Config.h"
#include "..\Common\Connection.h"
#include "..\Common\GUIdefs.h"
#include "..\Common\Cluster.h"
#include "..\Common\CameraSpec.h"
#include "..\Common\Vectors.h"
#include "..\Common\TVectors.h"
#include "..\Common\Track.h"
#include "..\Common\FlatTrack.h"

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

struct Grain
{
	float Xcm;
	float Ycm;
	void *Used;
	};

struct Cell
{
	union
	{	IntCluster *FirstC;
		Grain *FirstG;
		};
	int Free;
	};

struct Window
{
	float Xmin;
	float Xmax;
	float Ymin;
	float Ymax;
	};

#pragma pack(pop)

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

struct TrackerData
{
	Grain *GrainSpace;
	int MaxGrains;
	int LayerNum;
	int NumGrains;
	int Layer;
	int CellOverflow;
	float *ZLayer;
	Grain **LayerGrains;

	FlatStrip *pStripSpace;
	FlatStrip **pLayerStrips;
	int *pLayerStripsCount;
	int NumStrips;
	FlatTrack **pFlatStripUsedBy;
	
	float DxCell;
	float DyCell;
	int CellNumX;
	int CellNumY;
	int PixMin;
	int PixMax;
	float PixelToMicronX;
	float PixelToMicronY;
	Cell *CellSpace;
	int CellsInLayer;
	Window Win;

	int StartGap;
	int RetryGap;   
	int AttLim;
	float NptMin0;
	float NptMinSlope;
	float DHard;
	float DLoose;
	float MinSlope;
	float MaxSlope;

	float FSDirAgreement;
	int MaxFlatStrips;
	float FSWidth2Length;
	float FSTkRange;
	int MaxFSEmptyLayers;
	int MinFlatStrips;
	int MinFlatStripsPixels;
	float FSTkSectorWidth;
	float MinFlatTrackLength;
	};

/////////////////////////////////////////////////////////////////////////////
// CThick3DTracker
class ATL_NO_VTABLE CThick3DTracker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CThick3DTracker, &CLSID_Thick3DTrk>,
	public ITracker2,	
	public ISySalObject
{
public:
	CThick3DTracker()
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

	virtual ~CThick3DTracker()
	{
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
		if (T.pStripSpace) 
		{
			GlobalFree(T.pStripSpace);
			T.pStripSpace = 0;
			};
		if (T.pLayerStrips)
		{
			GlobalFree(T.pLayerStrips);
			T.pLayerStrips = 0;
			};
		if (T.pLayerStripsCount)
		{
			GlobalFree(T.pLayerStripsCount);
			T.pLayerStripsCount = 0;
			};
		if (T.pFlatStripUsedBy)
		{
			GlobalFree(T.pFlatStripUsedBy);
			T.pFlatStripUsedBy = 0;
			};
		};

DECLARE_REGISTRY_RESOURCEID(IDR_THICK3DTRK)
DECLARE_NOT_AGGREGATABLE(CThick3DTracker)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CThick3DTracker)
	COM_INTERFACE_ENTRY(ITracker2)
	COM_INTERFACE_ENTRY(ITracker)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

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

// ITracker2
public:
	STDMETHOD(GetFlatStrips)(int Layer, FlatStrip *pSpace, int *pMaxNumber, float *pZ);
	STDMETHOD(GetFlatTracks)(FlatTrack *pSpace, int *pMaxNumber, int MaxStripsInTrack, int StartLayer, int EndLayer);

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

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

	Grain *NextGrain(Cell *PCell, Grain **TempGrain, Vector Expect);

	int MergeTracks(Track *Id, int LastLay, int Npts, Track *Tracks, int NTracks, Grain **TempGrain, int MaxTracks);

	int GetCell(float Xp, float Yp);

	int TryChainTopForward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer);
	int TryChainBottomBackward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer);
	int TryChainTopBackward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer);
	int TryChainBottomForward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer);

};

#endif //__THICK3DTRK_H_
