// Thin3DTrk.h : Declaration of the CThin3DTracker

#ifndef __THIN3DTRK_H_
#define __THIN3DTRK_H_

#include "resource.h"       // main symbols
#include "..\Common\Config.h"
#include "..\Common\Connection.h"
#include "..\Common\GUIdefs.h"
#include "..\Common\Cluster.h"
#include "..\Common\CameraSpec.h"
#include "..\Common\Vectors.h"
#include "..\Common\TVectors.h"
#include "..\Common\Track.h"

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
	};

/////////////////////////////////////////////////////////////////////////////
// CThin3DTracker
class ATL_NO_VTABLE CThin3DTracker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CThin3DTracker, &CLSID_Thin3DTrk>,
	public ITracker,	
	public ISySalObject
{
public:
	CThin3DTracker()
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

	virtual ~CThin3DTracker()
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

DECLARE_REGISTRY_RESOURCEID(IDR_THIN3DTRK)
DECLARE_NOT_AGGREGATABLE(CThin3DTracker)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CThin3DTracker)
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

};

#endif //__THIN3DTRK_H_
